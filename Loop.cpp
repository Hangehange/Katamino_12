#include "stdafx.h"
#include "Loop.h"
#include "memory.h"

Loop::Loop(int inputLayer , int* inputCount)
{
	layer = inputLayer;
	count = new int[layer];
	totalCount = 1;
	for(int i = 0 ; i < layer ; ++i)
	{
		count[i] = inputCount[i];
		totalCount *= count[i];
	}

	index = new int[layer];
	memset(index , 0 , sizeof(int) * layer);
}

Loop::~Loop()
{
	delete[] count;
	delete[] index;
}

void Loop::visit(int **outputArray)
{
	int i = 0;
	memset(index , 0 , sizeof(int) * layer);
	int bytes = sizeof(int) * layer;
	while(i < totalCount)
	{
		memcpy(outputArray[i] , index , bytes); // д��һ���±�

// printf("%4d : " , i);
// for(int j = 0 ; j < layer ; ++j)
// 	printf("%2d" , outputArray[i][j]);
// printf("\n");

		next();
		++i;
	}
}


void Loop::next()
{
//	bool flag = true; // ��λ��־
	int i = 0;
	while(i < layer)
	{
// 		if(false == flag)
// 			return;

		if(index[i] == count[i] - 1)
		{//	��λ
			index[i] = 0;
			++i;
		}
		else
		{
			++index[i];
			return;
		}
	}
}