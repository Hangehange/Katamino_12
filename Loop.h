#include "stdafx.h"

class Loop
{
public:
	int layer; // ѭ���Ĳ���
	int* count; // ����Ҫѭ���Ĵ���
	Loop(int inputLayer , int* inputCount);
	~Loop();

	void visit(int **outputArray);

private:
	int totalCount; // ѭ���γɵ��������
	int* index; // ���㵱ǰѭ�����Ĵ�������ΧΪ0 ~ count[i] - 1
	
	void next();
};