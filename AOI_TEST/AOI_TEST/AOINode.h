#ifndef _AOI_NODE_H_
#define _AOI_NODE_H_

#include <memory>
#include "AOIVector.h"

template<int nDims> class AOINode
{
public:
	AOINode<nDims>* m_pPrev[nDims];
	AOINode<nDims>* m_pNext[nDims];
	AOIVector<nDims> m_pos;
	int m_nDeafLevel;
	int m_nQuietLevel;
	bool m_bInvaild;
	struct COUNTER
	{
		uint64_t uKey;
		int nMask;
	}m_stCounter;
	
public:
	AOINode(const AOIVector<nDims>& pos)
		: m_pos(pos)
		, m_nDeafLevel(0)
		, m_nQuietLevel(0)
		, m_bInvaild(false)
	{
		memset(m_pPrev, 0, sizeof(m_pPrev));
		memset(m_pNext, 0, sizeof(m_pNext));
		memset(&m_stCounter, 0, sizeof(COUNTER));
	}
	AOINode()
		: m_nDeafLevel(0)
		, m_nQuietLevel(0)
		, m_bInvaild(false)
	{
		memset(m_pPrev, 0, sizeof(m_pPrev));
		memset(m_pNext, 0, sizeof(m_pNext));
		memset(&m_stCounter, 0, sizeof(COUNTER));
	}
	~AOINode()
	{

	}

	void SetPos(const AOIVector<nDims>& pos)
	{
		m_pos = pos;
	}
	float Bigger(const AOINode<nDims>* pNode, int nDim)
	{
		return m_pos[nDim] - pNode->m_pos[nDim];
	}
	float Bigger(const AOIVector<nDims>& pPos, int nDim)
	{
		return m_pos[nDim] - pPos[nDim];
	}
};
#endif