#ifndef _AOI_NODE_H_
#define _AOI_NODE_H_

#include <memory>
#include "AOIPoint.h"

template<int nDims> class AOINode
{
public:
	AOINode<nDims>* m_pPrev[nDims];
	AOINode<nDims>* m_pNext[nDims];
	AOIPoint<nDims> m_pos;
	struct COUNTER
	{
		uint64_t uKey;
		int nCount;
	}m_stCounter;
	
public:
	AOINode(const AOIPoint<nDims>& pos)
		: m_pos(pos)
	{
		memset(m_pPrev, 0, sizeof(m_pPrev));
		memset(m_pNext, 0, sizeof(m_pNext));
		memset(&m_stCounter, 0, sizeof(COUNTER));
	}
	AOINode()
	{
		memset(m_pPrev, 0, sizeof(m_pPrev));
		memset(m_pNext, 0, sizeof(m_pNext));
		memset(&m_stCounter, 0, sizeof(COUNTER));
	}
	~AOINode()
	{

	}
	void SetPos(const AOIPoint<nDims>& pos)
	{
		m_pos = pos;
	}
	float Bigger(const AOINode<nDims>* pNode, int nDim)
	{
		return m_pos[nDim] - pNode->m_pos[nDim];
	}
};
#endif