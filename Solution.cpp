#include "stdafx.h"
#include "Solution.h"

Solution::Solution(int inputCols)
{
	cols = inputCols;
	rows = 5;
	nodeCount = 0;
	pSolution = NULL;
	pLastSolution = NULL;
}


Solution::~Solution()
{
	strSolutionNode *p = pSolution;
	strSolutionNode *q = p;
	while(NULL != p)
	{
		p = p->next;
		delete[] q->tileIndex;
		delete[] q->typeIndex;
		delete[] q->posIndex;
		delete[] q->graphic;
		delete q;
		q = p;
	}
	pSolution = NULL;
	nodeCount = 0;
}

bool Solution::isContain(char* inputGraphic)
{ // �жϵ�ǰ���е�ƴ���У��Ƿ��Ѱ���inputGraphic���ֽ�
  // ����������ת��ˮƽ����ֱ���Խ��߷�ת
	strSolutionNode* p = pSolution;
	int i = 0 , j = 0;
	
	while(p != NULL)
	{
		char* pCurrent = p->graphic;
		char* pNew = inputGraphic;
		bool returnFlag = true;

		// ������ת180����ʵ����һά����ĵ���
		pNew = pNew + cols * rows - 1;
		for(i = 0 ; i < cols * rows / 2 ; ++i)
		{
			if(*pCurrent != *pNew)
			{
				returnFlag = false;
				break; // ������ת180����ͬ�����������һ���任
			}
			++pCurrent;
			--pNew;
		}
		if(returnFlag == true)
			return true;

		// ˮƽ��ת
		pCurrent = p->graphic;
		pNew = inputGraphic;
		returnFlag = true;

		for(i = 0 ; i < rows ; ++i)
		{
			pCurrent = p->graphic + (i * cols);
			pNew = inputGraphic + (i * cols + cols - 1);
			for(j = 0 ; j < cols / 2 ; ++j)
			{
				if(*pCurrent != *pNew)
				{
					returnFlag = false;
					break; // ˮƽ��ת����ͬ�����������һ���任
				}
				++pCurrent;
				--pNew;
			}
		}
		if(returnFlag == true)
			return true;

		// ��ֱ��ת
		pCurrent = p->graphic;
		pNew = inputGraphic;
		returnFlag = true;

		for(i = 0 ; i < rows ; ++i)
		{
			pCurrent = p->graphic + (i * cols);
			pNew = inputGraphic + ((rows - 1 - i) * cols);
			for(j = 0 ; j < cols ; ++j)
			{
				if(*pCurrent != *pNew)
				{
					returnFlag = false;
					break; // ��ֱ��ת����ͬ�����������һ���任
				}
				++pCurrent;
				++pNew;
			}
		}
		if(returnFlag == true)
			return true;

		// �Խ��߷�ת (�����β���)

		p = p->next;
	}

	return false;
}

void Solution::addSolution(UINT8* inputIndex , UINT8* inputTypes , UINT8* inputPositions , char* inputGraphic)
{
	strSolutionNode* newNode = new strSolutionNode;

	newNode->tileIndex = new UINT8[cols];
	memcpy(newNode->tileIndex , inputIndex , sizeof(UINT8) * cols);

	newNode->typeIndex = new UINT8[cols];
	memcpy(newNode->typeIndex , inputTypes , sizeof(UINT8) * cols);

	newNode->posIndex = new UINT8[cols];
	memcpy(newNode->posIndex , inputPositions , sizeof(UINT8) * cols);

	newNode->next = NULL;
	newNode->graphic = inputGraphic;

	if(pSolution == NULL)
		pSolution = newNode;
	else
		pLastSolution->next = newNode;

	pLastSolution = newNode;
	++nodeCount;
}