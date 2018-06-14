#include "stdafx.h"
#include "Solution.h"
#include "string.h"

void fprintBoard(FILE* pf , char* board , int row , int col);

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


void Solution::printToFile(char* path)
{
	char pathname[128];
	int len = strlen(path);
	memset(pathname , 0 , 128 * sizeof(char));
	memcpy(pathname , path , len * sizeof(char));
	char filename[6] = {'0' , 'x' , '.' , 't' , 'x' , 't'};
	char lut[13] = {'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , '0' , '1' , '2'};
	filename[0] = cols > 9 ? '1' : '0';
	filename[1] = lut[cols];
	memcpy(pathname + len , filename , 6 * sizeof(char));

	char lut_m[12] = {'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'H' , 'I' , 'J' , 'K' , 'L'};

	FILE* pf = NULL;
	pf = fopen(pathname , "wt");

	int i = 0;
	strSolutionNode* pStr = pSolution;
	fprintf(pf , "there are %d solutions for N = %d\n\n" , nodeCount , cols);

	while(pStr != NULL)
	{
		fprintf(pf , "solution(%d): using Tiles..." , ++i);
		for(int j = 0 ; j < cols ; ++j)
			fprintf(pf , "%3c" , lut_m[pStr->tileIndex[j]]);
		fprintBoard(pf , pStr->graphic , rows , cols);
		pStr = pStr->next;
	}

	if(NULL != pf)
		fclose(pf);

	return;
}

void fprintBoard(FILE* pf , char* board , int row , int col)
{
	fprintf(pf , "\n");
	for(int i = 0 ; i < row ; ++i)
	{
		for(int j = 0 ; j < col ; ++j)
		{
			char c = board[i * col + j];
			if(c == ' ')
				fprintf(pf , " .");
			else
				fprintf(pf , "%2c" , c);
		}
		fprintf(pf , "\n");
	}
	fprintf(pf , "\n");
}