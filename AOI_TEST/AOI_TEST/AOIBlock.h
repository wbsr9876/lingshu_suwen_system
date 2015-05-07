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
	AOIVector<nDims> m_max;
	AOIVector<nDims> m_min;
	AOIList<nDims> m_coordinate[nDims];
	int m_nType;
	AOIBlock<nDims>* m_pSubBlockList[1<<nDims];
	AOIBlock<nDims>* m_pParent;
public:
	AOIBlock(const AOIVector<nDims>& max, const AOIVector<nDims>& min, AOIBlock<nDims>* pParent)
		: m_max(max)
		, m_min(min)
		, m_nType(0)
		, m_pParent(pParent)
	{
		for (int i = 0;i < nDims;i++)
		{
			m_coordinate[i].SetDim(i);
		}
	}
	~AOIBlock()
	{

	}
	void Splite()
	{
		AOIVector<nDims> center = (m_max + m_min) / 2;
		AOIVector<nDims> vec = center - m_max;
		m_pSubBlockList[0] = new AOIBlock<nDims>(m_max, center,this);
		for (int i = 0; i < nDims; i++)
		{
			int mid = 1 << i;
			for (int j = 0; j < mid; j++)
			{
				AOIVector<nDims> temp = m_pSubBlockList[j]->m_max;
				temp[i] = center[i];
				m_pSubBlockList[j + mid] = new AOIBlock<nDims>(temp, temp + vec,this);
			}
		}
	}
};
#endif