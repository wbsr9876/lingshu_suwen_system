#ifndef _AOI_BLOCK_H_
#define _AOI_BLOCK_H_

#include "AOIList.h"
#include "AOICube.h"

template<int nDims> class AOIBlock
{
protected:
	AOICube<nDims> m_cube;
	AOIList<nDims> m_coordinate[nDims];
	int m_nType;
	AOIBlock<nDims>* m_pSubBlockList[1<<nDims];
	AOIBlock<nDims>* m_pParent;
	uint64_t m_uKey;

	void Lock()
	{

	}

	void Unlock()
	{

	}

	uint64_t GenerateKey()
	{
		Lock();
		return ++m_uKey;
	}
	void ReleaseKey()
	{
		Unlock();
	}
public:
	AOIBlock(const AOIVector<nDims>& min, const AOIVector<nDims>& max, AOIBlock<nDims>* pParent)
		: m_cube(min,max)
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
	
	AOIBlock<nDims>* GetSubBlock(int nIndex)
	{
		if (m_nType & PARENT_BLOCK)
		{
			if (nIndex < 0 || nIndex > 1 << nDims)
			{
				return NULL;
			}
			return m_pSubBlockList[nIndex];
		}
		return NULL;
	}
	void Splite()
	{
		Lock();
		if (m_nType & INVAILD_BLOCK)
		{
			return;
		}
		if (m_nType & PARENT_BLOCK)
		{
			return;
		}
		AOIList<nDims>* pList[1 << nDims];
		AOIVector<nDims> center = (m_cube.m_max + m_cube.m_min) / 2;
		AOIVector<nDims> vec = center - m_cube.m_min;
		m_pSubBlockList[0] = new AOIBlock<nDims>(m_cube.m_min, center, this);
		pList[0] = m_pSubBlockList[0]->m_coordinate;
		for (int i = 0; i < nDims; i++)
		{
			int mid = 1 << i;
			for (int j = 0; j < mid; j++)
			{
				AOIVector<nDims> temp = m_pSubBlockList[j]->m_cube.m_min;
				temp[i] = center[i];
				m_pSubBlockList[j + mid] = new AOIBlock<nDims>(temp, temp + vec,this);
				pList[j + mid] = m_pSubBlockList[j + mid]->m_coordinate;
			}
		}
		for (int i = 0; i < nDims;i++)
		{
			m_coordinate[i].Splite(m_cube.m_mid, pList);
		}
		m_nType |= PARENT_BLOCK;
		Unlock();
	}
	AOINode<nDims>* __Notify(const AOIVector<nDims>& pos, float fBroadcastMin, float fBroadcastMax, std::vector<AOINode<3>*>* pResult,bool bAdd = false)
	{
		if (m_nType & INVAILD_BLOCK)
		{
			return NULL;
		}
		if (m_nType & PARENT_BLOCK)
		{
			return NULL;
			/*
			int nMask = 0;
			for (int i = 0; i < nDims; i++)
			{
				if (pos[i] > m_cube.m_mid[i])
					nMask |= 1 << i;
			}
			return m_pSubBlockList[nMask]->__Notify(pos, fBroadcastMin, fBroadcastMax, pResult,bAdd);
			*/
		}
// 		if (bAdd)
// 		{
// 			printf("Add %.2f,%.2f,%.2f In %.2f,%.2f,%.2f To %.2f,%.2f,%.2f\n", pos[0], pos[1], pos[2], m_cube.m_max[0], m_cube.m_max[1], m_cube.m_max[2], m_cube.m_min[0], m_cube.m_min[1], m_cube.m_min[2]);
// 		}
		AOINode<nDims>* pNode = new AOINode<nDims>(pos);
		uint64_t uKey = GenerateKey();
		m_coordinate[nDims - 1].SetResult(pResult);
		for (int i = 0; i < nDims; i++)
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
			if (pNode->Bigger(m_cube.m_mid, i) <= 0.0f)
			{
				m_coordinate[i].Add_LH(pNode, fBroadcastMin, fBroadcastMax, uKey, nCheck, bAdd);
			}
			else
			{
				m_coordinate[i].Add_HL(pNode, fBroadcastMin, fBroadcastMax, uKey, nCheck, bAdd);
			}
		}
		m_coordinate[nDims - 1].SetResult(NULL);
		ReleaseKey();
		if (!bAdd)
		{
			delete pNode;
			pNode = NULL;
		}
		return pNode;
	}
	AOINode<nDims>* __Add(const AOIVector<nDims>& pos, float fBroadcastMin, float fBroadcastMax, std::vector<AOINode<3>*>* pResult)
	{
		return __Notify(pos, fBroadcastMin, fBroadcastMax, pResult, true);
	}

	AOINode<nDims>* __Del(AOINode<nDims>* pNode, float fBroadcastMin, float fBroadcastMax, std::vector<AOINode<3>*>* pResult)
	{
		if (m_nType & INVAILD_BLOCK)
		{
			return NULL;
		}
		if (m_nType & PARENT_BLOCK)
		{
			return NULL;
			/*
			int nMask = 0;
			for (int i = 0; i < nDims; i++)
			{
				if (pNode->Bigger(m_cube.m_mid, i) > 0.0f)
					nMask |= 1 << i;
			}
			return m_pSubBlockList[nMask]->Del(pNode, fBroadcastMin, fBroadcastMax, pResult);
			*/
		}

// 		{
// 			printf("Del %.2f,%.2f,%.2f In %.2f,%.2f,%.2f To %.2f,%.2f,%.2f\n", pNode->m_pos[0], pNode->m_pos[1], pNode->m_pos[2], m_cube.m_max[0], m_cube.m_max[1], m_cube.m_max[2], m_cube.m_min[0], m_cube.m_min[1], m_cube.m_min[2]);
// 		}
		uint64_t uKey = GenerateKey();
		m_coordinate[nDims - 1].SetResult(pResult);
		for (int i = 0; i < nDims; i++)
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
			m_coordinate[i].Del(pNode, fBroadcastMin, fBroadcastMax, uKey, nCheck);
		}
		m_coordinate[nDims - 1].SetResult(NULL);
		ReleaseKey();
		return pNode;
	}
	AOINode<nDims>* Add(const AOIVector<nDims>& pos, float fBroadcastMin, float fBroadcastMax, std::vector<AOINode<3>*>* pResult)
	{
		AOICube<nDims> cube(pos, fBroadcastMin, fBroadcastMax);
		return Add(pos, fBroadcastMin, fBroadcastMax, pResult, cube);

	}
	AOINode<nDims>* Add(const AOIVector<nDims>& pos, float fBroadcastMin, float fBroadcastMax, std::vector<AOINode<3>*>* pResult, const AOICube<nDims>& cube)
	{
		if (m_nType & INVAILD_BLOCK)
		{
			return NULL;
		}
		if (m_cube.Cross(cube))
		{
			if (m_nType & PARENT_BLOCK)
			{
				AOINode<nDims>* pRet = NULL;
				AOINode<nDims>* pTemp = NULL;
				for (int i = 0; i < 1 << nDims;i++)
				{
					pTemp = m_pSubBlockList[i]->Add(pos, fBroadcastMin, fBroadcastMax, pResult, cube);
						pRet = pRet ? pRet : pTemp;
				}
				return pRet;
			}
			else
			{
				if (m_cube.Inside(pos))
				{
					return __Add(pos, fBroadcastMin, fBroadcastMax, pResult);
				}
				else
				{
					return __Notify(pos, fBroadcastMin, fBroadcastMax, pResult);
				}	
			}
		}
		return NULL;
	}
	void Del(AOINode<nDims>* pNode, float fBroadcastMin, float fBroadcastMax, std::vector<AOINode<3>*>* pResult)
	{
		AOICube<nDims> cube(pNode->m_pos, fBroadcastMin, fBroadcastMax);
		Del(pNode, fBroadcastMin, fBroadcastMax, pResult,cube);

	}
	void Del(AOINode<nDims>* pNode, float fBroadcastMin, float fBroadcastMax, std::vector<AOINode<3>*>* pResult, const AOICube<nDims>& cube)
	{
		if (m_nType & INVAILD_BLOCK)
		{
			return;
		}
		if (m_cube.Cross(cube))
		{
			if (m_nType & PARENT_BLOCK)
			{
				for (int i = 0; i < 1 << nDims; i++)
				{
					m_pSubBlockList[i]->Del(pNode, fBroadcastMin, fBroadcastMax, pResult, cube);
				}
				return;
			}
			else
			{
				if (m_cube.Inside(pNode->m_pos))
				{
					__Del(pNode, fBroadcastMin, fBroadcastMax, pResult);
				}
				else
				{
					__Notify(pNode->m_pos, fBroadcastMin, fBroadcastMax, pResult);
				}
			}
		}
		return;
	}
};
#endif