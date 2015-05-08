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
	AOINode<nDims> m_midNode;
	AOIList<nDims> m_coordinate[nDims];
	int m_nType;
	AOIBlock<nDims>* m_pSubBlockList[1<<nDims];
	AOIBlock<nDims>* m_pParent;
	uint64_t m_uKey;
public:
	AOIBlock(const AOIVector<nDims>& min, const AOIVector<nDims>& max, AOIBlock<nDims>* pParent)
		: m_min(min)
		, m_max(max)
		, m_midNode((m_max + m_min) / 2)
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
		uint64_t uKey = GenerateKey();
		for (int i = 0; i < nDims; i++)
		{
			m_coordinate[i].Add_LH(&m_midNode, 0, 0, uKey);
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
		AOIVector<nDims> center = (m_max + m_min) / 2;
		AOIVector<nDims> vec = center - m_min;
		m_pSubBlockList[0] = new AOIBlock<nDims>(m_min, center, this);
		for (int i = 0; i < nDims; i++)
		{
			int mid = 1 << i;
			for (int j = 0; j < mid; j++)
			{
				AOIVector<nDims> temp = m_pSubBlockList[j]->m_min;
				temp[i] = center[i];
				m_pSubBlockList[j + mid] = new AOIBlock<nDims>(temp, temp + vec,this);
			}
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
				if (pos[i] > m_midNode.m_pos[i])
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
			if (m_midNode.Bigger(pNode,i))
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