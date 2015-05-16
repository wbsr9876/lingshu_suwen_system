// AOI_TEST.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AOIList.h"
#include "AOIBlock.h"
#include <stdlib.h>
#include <windows.h>

#define MAX_COOR 100.0f
#define MAX_COUNT 100000
#define MAX_RANGE 10.f

float GetRand()
{
	return MAX_COOR * rand() / RAND_MAX;
}
int _tmain(int argc, _TCHAR* argv[])
{
//ex
	std::vector<AOINode<3>*> vecResult;
	std::vector<AOINode<3>*> vecNodes;
	AOIVector<3> a({ 0, 0, 0 });
	AOIVector<3> b({ MAX_COOR, MAX_COOR, MAX_COOR });
	AOIBlock<3> test(a, b, NULL);

	test.Splite();
	float v[3] = { 0, 0, 0 };
	for (int i = 0; i < MAX_COUNT; i++)
	{
		v[0] = GetRand();
		v[1] = GetRand();
		v[2] = GetRand();
		AOINode<3>* pNode = new AOINode<3>(AOIVector<3>(v));
		AOINode<3> * pTemp = test.Add(pNode, MAX_RANGE, MAX_RANGE, &vecResult);
		if (pTemp)
		{
			vecNodes.push_back(pNode);
		}
		else
		{
			delete pNode;
		}
		printf("broadcast count:%u\n", vecResult.size());
		vecResult.clear();
	}
	
	test.GetSubBlock(0)->Splite();
	test.GetSubBlock(5)->Splite();
	test.GetSubBlock(7)->Splite();
	while (true)
	{
		for (std::vector<AOINode<3>*>::iterator iter = vecNodes.begin(); iter != vecNodes.end(); ++iter)
		{
			test.Del(*iter, MAX_RANGE, MAX_RANGE, &vecResult);
			printf("move 1 count:%u\n", vecResult.size());
			vecResult.clear();
			
			(*iter)->m_pos[0] = GetRand();
			(*iter)->m_pos[1] = GetRand();
			(*iter)->m_pos[2] = GetRand();
			(*iter)->Clear();
			//printf("%.2f %.2f %.2f\n", (*iter)->m_pos[0], (*iter)->m_pos[1], (*iter)->m_pos[2]);
			test.Add((*iter), MAX_RANGE, MAX_RANGE, &vecResult);
			printf("move 2 count:%u\n", vecResult.size());
			vecResult.clear();
			
		}
		Sleep(1);
	}


	getchar();
	return 0;
}

