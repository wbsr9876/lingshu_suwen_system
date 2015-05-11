#ifndef _AOI_LIST_H_
#define _AOI_LIST_H_

#include "AOINode.h"
#include "AOIChecker.h"
#include <vector>

enum AOI_STEP
{
	AOI_STEP_INIT = 0x1,
	AOI_STEP_CEHCK = 0x2,
	AOI_STEP_OUTPUT = 0x4,

};

template<int nDims> class AOIList
{
protected:
	int m_nDim;
	int m_nCount;
	AOINode<nDims>* m_pHead;
	AOINode<nDims>* m_pTail;
	std::vector<AOINode<nDims>*>* m_pResult;
public:
	AOIList(int nDim)
		: m_nDim(nDim)
		, m_nCount(0)
		, m_pHead(NULL)
		, m_pTail(NULL)
		, m_pResult(NULL)
	{

	}
	AOIList()
		: m_nDim(-1)
		, m_nCount(0)
		, m_pHead(NULL)
		, m_pTail(NULL)
		, m_pResult(NULL)
	{

	}
	~AOIList()
	{

	}

	void SetDim(int nDim)
	{
		m_nDim = nDim;
	}

	void SetResult(std::vector<AOINode<nDims>*>* pResult)
	{
		m_pResult = pResult;
	}
	void InsertAfter(AOINode<nDims>* pAfter, AOINode<nDims>* pNode)
	{
		AOINode<nDims>* pTemp = pNode->m_pNext[m_nDim];
		pNode->m_pNext[m_nDim] = pAfter;
		pAfter->m_pPrev[m_nDim] = pNode;
		pAfter->m_pNext[m_nDim] = pTemp;
		if (pTemp)
		{
			pTemp->m_pPrev[m_nDim] = pAfter;
		}
		if (pNode == m_pTail)
		{
			m_pTail = pAfter;
		}
		m_nCount++;
	}
	void Pushback(AOINode<nDims>* pNode)
	{
		if (m_pTail)
		{
			InsertAfter(pNode, m_pTail);
			return;
		}
	}

	void FirstInsert(AOINode<nDims>* pNode)
	{
		m_pTail = pNode;
		m_pHead = pNode;
		m_nCount = 1;
	}
	void InsertBefore(AOINode<nDims>* pBefore, AOINode<nDims>* pNode)
	{
		AOINode<nDims>* pTemp = pNode->m_pPrev[m_nDim];
		pNode->m_pPrev[m_nDim] = pBefore;
		pBefore->m_pNext[m_nDim] = pNode;
		pBefore->m_pPrev[m_nDim] = pTemp;
		if (pTemp)
		{
			pTemp->m_pNext[m_nDim] = pBefore;
		}
		if (pNode == m_pHead)
		{
			m_pHead = pBefore;
		}
		m_nCount++;
	}
	void Remove(AOINode<nDims>* pNode)
	{
		if (m_pHead == m_pTail)
		{
			if (m_pHead == pNode)
			{
				m_pHead = NULL;
				m_pTail = NULL;
				m_nCount = 0;
			}
			return;
		}
		AOINode<nDims>* pPrev = pNode->m_pPrev[m_nDim];
		AOINode<nDims>* pNext = pNode->m_pNext[m_nDim];
		if (pPrev)
		{
			pPrev->m_pNext[m_nDim] = pNext;
		}
		if (pNext)
		{
			pNext->m_pPrev[m_nDim] = pPrev;
		}
		m_nCount--;
	}
	void CheckStep(AOINode<nDims>* pNode,int nStep,uint64_t uKey,AOINode<nDims>* pSender)
	{
		if (pNode->m_bInvaild)
		{
			return;
		}
		if (nStep & AOI_STEP_INIT)
		{
			pNode->m_stCounter.uKey = uKey;
			pNode->m_stCounter.nMask = 0;
		}
		if ((nStep & AOI_STEP_CEHCK) && pNode->m_stCounter.uKey == uKey)
		{
			pNode->m_stCounter.nMask |= 1 << m_nDim;
		}
		if ((nStep & AOI_STEP_OUTPUT) && pNode->m_stCounter.nMask == (1 << nDims) - 1)
		{
			if (AOIChecker<nDims>::ListenChecker(pSender, pNode))
			{
				m_pResult->push_back(pNode);
			}	
		}
	}
	void Add_LH(AOINode<nDims>* pNode, float fBroadcastMin, float fBroadcastMax, uint64_t uKey, int nStep = AOI_STEP_CEHCK, bool bUndo = true, bool bSelf = false, AOINode<nDims>* pStart = NULL)
	{
		if (bSelf)
		{
			if (nStep == AOI_STEP_OUTPUT)
			{
				m_pResult->push_back(pNode);
			}
		}

		if (!m_pHead)
		{
			FirstInsert(pNode);
			return;
		}

		//bool bUndo = true;

		AOINode<nDims>* pIter = pStart ? pStart : m_pHead;
		while (pIter)
		{
			float fDist = pNode->Bigger(pIter, m_nDim);
			if (bUndo && fDist < 0)
			{
				InsertBefore(pNode, pIter);
				bUndo = false;
			}
			if (fDist >= -fBroadcastMax && fDist <= fBroadcastMin)
			{
				CheckStep(pIter, nStep, uKey,pNode);			
			}
			else if (fDist < -fBroadcastMax)
			{
				return;

			}
			pIter = pIter->m_pNext[m_nDim];
		}

		if (bUndo)
		{
			InsertAfter(pNode, m_pTail);
		}
	}
	void Add_HL(AOINode<nDims>* pNode, float fBroadcastMin, float fBroadcastMax, uint64_t uKey, int nStep = AOI_STEP_CEHCK, bool bUndo = true, bool bSelf = false, AOINode<nDims>* pStart = NULL)
	{
		if (bSelf)
		{
			if (nStep == AOI_STEP_OUTPUT)
			{
				m_pResult->push_back(pNode);
			}
		}

		if (!m_pHead)
		{
			FirstInsert(pNode);
			return;
		}

		//bool bUndo = true;

		AOINode<nDims>* pIter = pStart ? pStart : m_pTail;
		while (pIter)
		{
			float fDist = pNode->Bigger(pIter, m_nDim);
			if (bUndo && fDist > 0)
			{
				InsertAfter(pNode, pIter);
				bUndo = false;
			}
			if (fDist >= -fBroadcastMax && fDist <= fBroadcastMin)
			{
				CheckStep(pIter, nStep, uKey, pNode);
			}
			else if (fDist > fBroadcastMin)
			{
				return;

			}
			pIter = pIter->m_pPrev[m_nDim];
		}

		if (bUndo)
		{
			InsertBefore(pNode, m_pHead);
		}
	}
	
	void Del(AOINode<nDims>* pNode, float fBroadcastMin, float fBroadcastMax, uint64_t uKey, int nStep = AOI_STEP_CHECK, bool bSelf = false)
	{
		if (bSelf)
		{
			if (nStep == AOI_STEP_OUTPUT)
			{
				m_pResult->push_back(pNode);
			}
		}
		float fDist = 0.0f;
		AOINode<nDims>* pIter = pNode->m_pNext[m_nDim];
		while (pIter)
		{
			fDist = pIter->Bigger(pNode, m_nDim);
			if (fDist > fBroadcastMax)
			{
				break;
			}
			CheckStep(pIter, nStep, uKey, pNode);
			pIter = pIter->m_pNext[m_nDim];
		}
		pIter = pNode->m_pPrev[m_nDim];
		while (pIter)
		{
			fDist = pNode->Bigger(pIter, m_nDim);
			if (fDist > fBroadcastMin)
			{
				break;
			}
			CheckStep(pIter, nStep, uKey, pNode);
			pIter = pIter->m_pPrev[m_nDim];
		}
		Remove(pNode);
	}

	void Splite(const AOIVector<nDims>& midPoint, AOIList<nDims>** pList)
	{
		AOINode<nDims>* pIter = m_pHead;
		while (pIter)
		{
			int nMask = 0;
			for (int i = 0; i < nDims;i++)
			{
				nMask |= pIter->Bigger(midPoint, i) > 0.0f? (1 << i) : 0;
			}
			AOINode<nDims>* pTemp = pIter->m_pNext[m_nDim];
			pList[nMask][m_nDim].Pushback(pIter);
			if (pIter == m_pTail)
			{
				break;
			}
			pIter = pTemp;
		}
		m_pHead = NULL;
		m_pTail = NULL;
	}

};
#endif