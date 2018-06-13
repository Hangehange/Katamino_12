#include "stdafx.h"

typedef unsigned char UINT8;

class Loop
{
public:
	int layer; // ѭ���Ĳ���
	UINT8* count; // ����Ҫѭ���Ĵ���
	Loop(int inputLayer , UINT8* inputCount);
	~Loop();

	void visit(UINT8 **outputArray);

private:
	int totalCount; // ѭ���γɵ��������
	UINT8* index; // ���㵱ǰѭ�����Ĵ�������ΧΪ0 ~ count[i] - 1
	
	void next();
};