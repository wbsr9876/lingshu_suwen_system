#ifndef _AOI_CHECKER_
#define _AOI_CHECKER_

#include "AOINode.h"

template<int nDims> class AOIChecker
{
public:
	static bool ListenChecker(const AOINode<nDims>* pSender, const AOINode<nDims>* pReceiver)
	{
		//if you like you can add some direction info
		if (!pSender->m_nQuietLevel)
		{
			return true;
		}
		return pReceiver->m_nDeafLevel <= pSender->m_nQuietLevel + (pReceiver->m_pos - pSender->m_pos).SquaredMagnitude();
	}
};
#endif