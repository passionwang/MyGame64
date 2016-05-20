#pragma once
#include "Public.h"
#include "MoveGenerator.h"
class CEvalute
{
public:
	CEvalute(void);
	~CEvalute(void);
public:
	int Evalute(int (*Board)[8],int Turn);
	int Board_Eva[8][8];
	CPublicInfo * pPI;
	CMoveGenerator *pMG;
public:
/////////////��Ԫ��ֵ����////////////
	int FlexibleCount();//�����
	int ValueCount();//��ֵ����
	int SafetyCount();//��ȫ̬����
	int AttackCount();//����̬����
	int DefenseCount();//����̬����
/////////////���Ƽ�ֵ����////////////
	int TriangleCount();
	int DefenseLineCount();
};

