#ifndef _AOI_POINT_H_
#define _AOI_POINT_H_

#include <assert.h>

template<int nDims> class AOIPoint
{
protected:
	float coordinate[nDims];
public:
	AOIPoint()
	{
		memset(coordinate, 0, sizeof(coordinate));
	}
	AOIPoint(float value[nDims])
	{
		memcpy(coordinate, value, sizeof(coordinate));
	}
	AOIPoint(const AOIPoint<nDims>& point)
	{
		memcpy(coordinate, point.coordinate, sizeof(coordinate));
	}
	~AOIPoint()
	{

	}
	AOIPoint<nDims> operator=(float value[nDims])
	{
		memcpy(coordinate, value, sizeof(coordinate));
		return *this;
	}
	AOIPoint<nDims> operator+(const AOIPoint<nDims>& point)
	{
		AOIPoint result;
		for (int i = 0; i < nDims;i++)
		{
			result.coordinate[i] = coordinate[i] + point.coordinate[i];
		}
		return result;
	}
	AOIPoint<nDims> operator-(const AOIPoint<nDims>& point)
	{
		AOIPoint result;
		for (int i = 0; i < nDims; i++)
		{
			result.coordinate[i] = coordinate[i] - point.coordinate[i];
		}
		return result;
	}
	AOIPoint<nDims> operator=(const AOIPoint<nDims>& point)
	{
		memcpy(coordinate, point.coordinate, sizeof(coordinate));
		return *this;
	}
	float operator[](int nDim) const
	{
		assert(nDim < nDims && nDim >= 0);
		return coordinate[nDim];
	}
};
#endif