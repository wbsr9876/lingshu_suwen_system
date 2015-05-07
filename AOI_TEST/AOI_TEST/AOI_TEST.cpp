// AOI_TEST.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AOIList.h"

#define _ADD_POINT_ \
	

int _tmain(int argc, _TCHAR* argv[])
{
	uint64_t uKey = 1;
	AOIList<3> x(0);
	AOIList<3> y(1);
	AOIList<3> z(2);
	float v[][3] = 
	{
		{1,2,3},
		{2,3,4},
		{3,4,5},
		{4,5,6},
		{5,6,7}
	};
	AOINode<3> node[5];
	for (int i = 0; i < 5; i++)
	{
		node[i].SetPos(AOIPoint<3>(v[i]));
		x.Add(&node[i], 2.0f, 2.0f, uKey,AOI_STEP_INIT|AOI_STEP_CEHCK);
		y.Add(&node[i], 2.0f, 2.0f, uKey);
		std::vector<AOINode<3>*> vecResult;
		z.SetResult(&vecResult);
		z.Add(&node[i], 2.0f, 2.0f, uKey, AOI_STEP_OUTPUT|AOI_STEP_CEHCK);
		z.SetResult(NULL);
		printf("count:%u\n", vecResult.size());
	}
	getchar();
	return 0;
}

