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
/////////////单元价值计数////////////
	int FlexibleCount();//灵活性
	int ValueCount();//价值计数
	int SafetyCount();//安全态计数
	int AttackCount();//攻击态计数
	int DefenseCount();//防御态计数
/////////////局势价值计数////////////
	int TriangleCount();
	int DefenseLineCount();
};

