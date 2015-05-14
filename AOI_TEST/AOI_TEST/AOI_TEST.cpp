// AOI_TEST.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AOIList.h"
#include "AOIBlock.h"

int _tmain(int argc, _TCHAR* argv[])
{
	uint64_t uKey = 1;
	std::vector<AOINode<3>*> vecResult;
	std::vector<AOINode<3>*> vecNodes;
	AOIVector<3> a({ 0, 0, 0 });
	AOIVector<3> b({ 8, 8, 8 });
	AOIBlock<3> test(a, b, NULL);
	float v[][3] = 
	{
		{0,0,0},
		{1,1,1},
		{3,4,5},
		{4,5,6},
		{5,6,7},
		{5, 6, 7},
		{ 5, 6, 7 },
		{ 5, 6, 7 }
	};
	AOINode<3> node[8];

	test.Splite();

	for (int i = 0; i < 8; i++)
	{
		AOINode<3>* pNode = test.Add(AOIVector<3>(v[i]), 2.0f, 2.0f, &vecResult);
		if (pNode)
		{
			vecNodes.push_back(pNode);
		}
		printf("broadcast count:%u\n", vecResult.size());
		vecResult.clear();
	}
	
	test.Splite();
	test.GetSubBlock(0)->Splite();
	test.GetSubBlock(5)->Splite();
	test.GetSubBlock(7)->Splite();
	for (std::vector<AOINode<3>*>::iterator iter = vecNodes.begin(); iter != vecNodes.end();++iter)
	{
		test.Del(*iter, 2.0f, 2.0f, &vecResult);
		printf("count:%u\n", vecResult.size());
		vecResult.clear();
		delete (*iter);
	}

	getchar();
	return 0;
}

