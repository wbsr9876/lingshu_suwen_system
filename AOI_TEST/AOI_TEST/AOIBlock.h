#ifndef _AOI_BLOCK_H_
#define _AOI_BLOCK_H_

#include "AOIList.h"
enum COORDINATE_NAME
{
	X_COORDINATE,
	Y_COORDINATE,
	Z_COORDINATE
};
enum BLOCK_TYPE
{
	INVAILD_BLOCK = 0x1,
	PARENT_BLOCK = 0x2,
};

template<int nDims> AOIVector<nDims>* GetVertex(const AOIVector<nDims>& max, const AOIVector<nDims>& min)
{
	AOIVector<nDims>* pResult = new AOIVector<nDims>[1 << nDims];
	pResult[0] = max;
	for (int i = 0; i < nDims;i++)
	{
		int mid = 1 << i;
		for (int j = 0; j < mid; j++)
		{
			pResult[j + mid] = pResult[j];
			pResult[j + mid][i] = min[i];
		}
	}
	return pResult;
}
template<int nDims> class AOIBlock
{
protected:
	AOIVector<nDims> m_min;
	AOIVector<nDims> m_max;
	AOIVector<nDims> m_midVector;
	AOIList<nDims> m_coordinate[nDims];
	int m_nType;
	AOIBlock<nDims>* m_pSubBlockList[1<<nDims];
	AOIBlock<nDims>* m_pParent;
	uint64_t m_uKey;
public:
	AOIBlock(const AOIVector<nDims>& min, const AOIVector<nDims>& max, AOIBlock<nDims>* pParent)
		: m_min(min)
		, m_max(max)
		, m_midVector((m_max + m_min) / 2)
		, m_nType(0)
		, m_pParent(pParent)
		, m_uKey(0)
	{
		if (pParent)
		{
			m_uKey = pParent->m_uKey;
		}
		for (int i = 0;i < nDims;i++)
		{
			m_coordinate[i].SetDim(i);
		}
	}
	~AOIBlock()
	{

	}

	uint64_t GenerateKey()
	{
		return ++m_uKey;
	}
	void Splite()
	{
		AOIList<nDims>* pList[1 << nDims];
		AOIVector<nDims> center = (m_max + m_min) / 2;
		AOIVector<nDims> vec = center - m_min;
		m_pSubBlockList[0] = new AOIBlock<nDims>(m_min, center, this);
		pList[0] = m_pSubBlockList[0]->m_coordinate;
		for (int i = 0; i < nDims; i++)
		{
			int mid = 1 << i;
			for (int j = 0; j < mid; j++)
			{
				AOIVector<nDims> temp = m_pSubBlockList[j]->m_min;
				temp[i] = center[i];
				m_pSubBlockList[j + mid] = new AOIBlock<nDims>(temp, temp + vec,this);
				pList[j + mid] = m_pSubBlockList[j + mid]->m_coordinate;
			}
		}
		for (int i = 0; i < nDims;i++)
		{
			m_coordinate[i].Splite(m_midVector, pList);
		}
	}

	AOINode<nDims>* Add(const AOIVector<nDims>& pos, float fBroadcastMin, float fBroadcastMax, std::vector<AOINode<3>*>* pResult)
	{
		if (m_nType & INVAILD_BLOCK)
		{
			return NULL;
		}
		if (m_nType & PARENT_BLOCK)
		{
			int nMask = 0;
			for (int i = 0; i < nDims;i++)
			{
				if (pos[i] > m_midVector[i])
					nMask |= 1 << i;
			}
			return m_pSubBlockList[nMask]->Add(pos, fBroadcastMin, fBroadcastMax, pResult);
		}
		AOINode<nDims>* pNode = new AOINode<nDims>(pos);
		uint64_t uKey = GenerateKey();
		m_coordinate[nDims - 1].SetResult(pResult);
		for (int i = 0; i < nDims;i++)
		{
			int nCheck = AOI_STEP_CEHCK;
			if (i == 0)
			{
				nCheck |= AOI_STEP_INIT;
			}
			if (i == nDims - 1)
			{
				nCheck |= AOI_STEP_OUTPUT;

			}
			if (pNode->Bigger(m_midVector,i) <= 0.0f)
			{
				m_coordinate[i].Add_LH(pNode, fBroadcastMin, fBroadcastMax, uKey, nCheck);
			}
			else
			{
				m_coordinate[i].Add_HL(pNode, fBroadcastMin, fBroadcastMax, uKey, nCheck);
			}
		}
		m_coordinate[nDims - 1].SetResult(NULL);
		//extern
		return pNode;
	}
};
#endif