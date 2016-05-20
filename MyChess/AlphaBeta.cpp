#include "stdafx.h"
#include "AlphaBeta.h"
#include "MoveGenerator.h"
//bug1：搜索问题，并不能有效记录最终走法
//bug2：走法生成器中记录走法种类貌似有bug
//bug3：关于PossibleMove[10][100],是否应该在退出某一层是将其所有数据全部reset？另：如果reset的话			BestChess永远指NULL的问题需要注意
CAlphaBeta::CAlphaBeta(void)
{



}
CAlphaBeta::~CAlphaBeta(void)
{


}
void CAlphaBeta::SearchAGoodMove(int (*iBoard)[8])
{
	int nCount=0;
	int Alpha=-200000;
	int Beta=200000;
	memcpy_s(Board_Copy,8*8*4,iBoard,8*8*4);
	//22与24不可调换位置，因为24的执行调用了22的Board_Copy
	CMoveGenerator pMG_Input(Board_Copy);
	CEvalute pEVA_Input;
	SetMoveGenerator(&pMG_Input);
	SetEvalutor(&pEVA_Input);

	
	AlphaBeta(0,Alpha,Beta);
	MakeMove(*BestChess);

	memcpy_s(Board_Copy,8*8*4,pMG->Board_MG,8*8*4);

	//1.统计当前我方势力棋子数
	//2.遍历所有棋子的Alpha-Beta剪枝算法列出所有棋子的最佳方案(估值)
	//3.挑选最优估值的棋子
	//4.行棋
}
int CAlphaBeta::AlphaBeta(int nPly,int Alpha,int Beta)
{
	int Value=0;
	int i=0;
	int nTypeRoute=0;
	if(nPly%2!=0&&nPly!=0)
		Turn = ENEMY;	//如果进入层数是2的偶数倍，则最后必定是对方走棋
	else
		Turn = MINE;	//否则为我方走棋
	if((i=IsGameOver(nPly))<=-199990||(i=IsGameOver(nPly))>=199990)
		return i;
	if(nPly==MaxSearchPly)
	{

		return	pEVA->Evalute(pMG->Board_MG,this->Turn);	//返回估值
	}

 	nTypeRoute=pMG->MakePossibleChess(Turn,nPly);	
	int TypeCount=0;
	while(TypeCount<nTypeRoute)
	{
		MakeMove(pMG->PossibleMove[nPly][TypeCount]);		
		Value=-AlphaBeta(nPly+1,-Beta,-Alpha);
		ResetMakeMove(pMG->PossibleMove[nPly][TypeCount]);
		if(Value>Alpha)
		{
			if(nPly==0)
			{
				BestChess=&(pMG->PossibleMove[nPly][TypeCount]);
			}
			Alpha=Value;
		}
		if(Alpha>=Beta)
		{
			break;
		}
		TypeCount++;
	}
	return Alpha;
}