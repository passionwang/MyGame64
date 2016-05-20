#include "stdafx.h"
#include "NegaMax.h"


CNegaMax::CNegaMax(void)
{
}


CNegaMax::~CNegaMax(void)
{
}

//
//void CNegaMax::SearchAGoodMove(int Board_Input[8][8])
//{
//	//设置深度
//	MaxDepth=MaxSearchDepth;
//	//复制棋盘副本
//	memcpy_s(Board_Copy,8*8*4,Board_Input,8*8*4);
//	//搜索开始
//	NegaMax(MaxDepth);
//	//产生走后的棋盘
//	BoardAfterMove(FinalnCount,BestTypeToute);
//	//棋盘复制
//	memcpy_s(Board_Input,8*8*4,Board_Copy,8*8*4);
//}
//负极大值搜索核心
//int CNegaMax::NegaMax(int Depth)
//{
//
//
//}