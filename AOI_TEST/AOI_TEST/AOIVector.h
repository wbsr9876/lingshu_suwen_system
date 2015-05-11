#ifndef _AOI_POINT_H_
#define _AOI_POINT_H_

#include <assert.h>

template<int nDims> class AOIVector
{
protected:
	float coordinate[nDims];
public:
	AOIVector()
	{
		memset(coordinate, 0, sizeof(coordinate));
	}
	AOIVector(float value[nDims])
	{
		memcpy(coordinate, value, sizeof(coordinate));
	}
	AOIVector(float x)
	{
		coordinate[0] = x;
	}
	AOIVector(float x, float y)
	{
		coordinate[0] = x;
		coordinate[1] = y;
	}
	AOIVector(float x, float y, float z)
	{
		coordinate[0] = x;
		coordinate[1] = y;
		coordinate[2] = z;
	}
	AOIVector(const AOIVector<nDims>& point)
	{
		memcpy(coordinate, point.coordinate, sizeof(coordinate));
	}
	~AOIVector()
	{

	}
	AOIVector<nDims> operator=(float value[nDims])
	{
		memcpy(coordinate, value, sizeof(coordinate));
		return *this;
	}
	AOIVector<nDims> operator+(const AOIVector<nDims>& point) const
	{
		AOIVector result;
		for (int i = 0; i < nDims;i++)
		{
			result.coordinate[i] = coordinate[i] + point.coordinate[i];
		}
		return result;
	}
	AOIVector<nDims> operator-(const AOIVector<nDims>& point) const
	{
		AOIVector result;
		for (int i = 0; i < nDims; i++)
		{
			result.coordinate[i] = coordinate[i] - point.coordinate[i];
		}
		return result;
	}
	AOIVector<nDims> operator*(float rate) const
	{
		AOIVector result;
		for (int i = 0; i < nDims; i++)
		{
			result.coordinate[i] = coordinate[i] * rate;
		}
		return result;
	}
	AOIVector<nDims> operator/(float rate) const 
	{
		AOIVector result;
		for (int i = 0; i < nDims; i++)
		{
			result.coordinate[i] = coordinate[i] / rate;
		}
		return result;
	}
	const AOIVector<nDims>& operator=(const AOIVector<nDims>& point)
	{
		memcpy(coordinate, point.coordinate, sizeof(coordinate));
		return *this;
	}
	float& operator[](int nDim)
	{
		assert(nDim < nDims && nDim >= 0);
		return coordinate[nDim];
	}
	const float& operator[](int nDim) const
	{
		assert(nDim < nDims && nDim >= 0);
		return coordinate[nDim];
	}
	float SquaredMagnitude() const
	{
		float fRet = 0.0f;
		for (int i = 0; i < nDims; i++)
		{
			fRet += coordinate[i] * coordinate[i];
		}
		return fRet;
	}
	float Magnitude() const
	{
		return sqrt(SquaredMagnitude());
	}
};
#endif