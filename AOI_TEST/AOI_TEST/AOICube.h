#ifndef _AOI_CUBE_H_
#define _AOI_CUBE_H_

#include "AOIVector.h"

template<int nDims> class AOICube
{
public:
	AOIVector<nDims> m_min;
	AOIVector<nDims> m_max;
	AOIVector<nDims> m_mid;

	AOICube(const AOIVector<nDims>& min, const AOIVector<nDims>& max)
		: m_min(min)
		, m_max(max)
		, m_mid((m_max + m_min) / 2)
	{

	}
	AOICube(const AOIVector<nDims>& point,float fBroadcastMin, float fBroadcastMax)
		: m_min(point - fBroadcastMin)
		, m_max(point + fBroadcastMax)
		, m_mid((m_max + m_min) / 2)
	{

	}
	~AOICube()
	{

	}

	bool Cross(const AOICube<nDims>& cube)
	{
		for (int i = 0; i < nDims;i++)
		{
			if (Less(cube.m_max[i],m_min[i]) || More(cube.m_min[i],m_max[i]))
			{
				return false;
			}
		}
		return true;
	}
	bool Inside(const AOIVector<nDims>& point)
	{
		for (int i = 0; i < nDims; i++)
		{
			if (Less(point[i], m_min[i]) || !Less(point[i],m_max[i]))
			{
				return false;
			}
		}
		return true;
	}
};
#endif