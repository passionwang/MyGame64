#include "stdafx.h"
#include "SearchEngine.h"
//存在问题：
//1.MoveGenerator与SearchEngine的衔接问题
//2.关于Board_Copy的赋值紊乱
//3.MakeMove与ResetMakeMove有潜在问题
//4.关于如何在深层搜索时，规避返回上次行走的起始点
//

CSearchEngine::CSearchEngine(void)
{
	pMG=NULL;//MoveGenerator指针用于调用MoveGenerator
	pEVA=NULL;
	MaxSearchPly=0;//最大的搜索深度
	MaxPly=0;//当前的搜索深度 
	memset(Value_Buff,0,10*12*4);//////////////////////ATTENTION!!!!
	Best_Value=0; 
	BestChess=NULL;
}


CSearchEngine::~CSearchEngine(void)
{
	
	pMG=NULL;//MoveGenerator指针用于调用MoveGenerator
	pEVA=NULL;
	BestChess=NULL;
}
//初始化搜索深度
void CSearchEngine::SetSearchDepth(int nPly)
{
	MaxSearchPly=nPly;
}
//初始化Evalutor
void CSearchEngine::SetEvalutor(CEvalute *pEVA_Input)
{

	pEVA=pEVA_Input;

}
//初始化MoveGenerator
void CSearchEngine::SetMoveGenerator(CMoveGenerator *pMG_Input)
{
	pMG=pMG_Input;

}
//产生行棋之后的棋盘
void CSearchEngine::MakeMove(CNodeChessInfo &Chess)
{
	if(Chess.nSide_==BLACK_SOLDIER||Chess.nSide_==WHITE_SOLDIER)//判断是王走还是兵走
	{
		if(Chess.Depth==0)//如果当前棋子不能杀棋，走布局
		{
			pMG->Move_Poly(Chess.DirectionToMove[0],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y);
			
		}else
		{
			for(int i=0;i<Chess.Depth;i++)
			{
				Value_Buff[Chess.nPly][i]=pMG->Move_Kill(Chess.DirectionToMove[i],Chess.nSide_,(Chess.Location_Current.x),(Chess.Location_Current.y));
			}
		}
		
	}
	else if(Chess.nSide_==BLACK_KING||Chess.nSide_==WHITE_KING)
	{
		if(Chess.Depth==0)//如果当前棋子不能杀棋，走布局
		{
			pMG->King_Move_Poly(Chess.DirectionToMove[0],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y,Chess.nSpace_Before[0]);
			
		}else
		{
			for(int i=0;i<Chess.Depth;i++)
			{
				Value_Buff[Chess.nPly][i]=pMG->King_Kill_Poly(Chess.DirectionToMove[i],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y,Chess.nSpace_Before[i],Chess.nSpace_After[i]);
			}
		}
	}
	for(int i=0;i<8;i++)
	{
		if(pMG->Board_MG[7][i]==-1)
		{
			pMG->Board_MG[7][i]=-2;
		}	
		else if(pMG->Board_MG[0][i]==1)
		{
			pMG->Board_MG[0][i]=2;

		}
	}
	memcpy_s(this->Board_Copy,8*8*4,pMG->Board_MG,8*8*4);
}
//还原行棋后的棋盘
void CSearchEngine::ResetMakeMove(CNodeChessInfo &Chess)
{
	if(Chess.nSide_==BLACK_SOLDIER||Chess.nSide_==WHITE_SOLDIER)//判断是王走还是兵走
	{
		if(Chess.Depth==0)//如果当前棋子不能杀棋，走布局
		{
			pMG->Move_Re_Poly(Chess.DirectionToMove[0],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y);
			
		}else
		{
			int i=Chess.Depth-1;
			for(i;i>=0;i--)
			{
				pMG->Move_Re_Kill(Chess.DirectionToMove[i],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y,Value_Buff[Chess.nPly][i]);
				
			}
		}
		
	}
	else if(Chess.nSide_==BLACK_KING||Chess.nSide_==WHITE_KING)
	{
		if(Chess.Depth==0)//如果当前棋子不能杀棋，走布局
		{
			pMG->King_Move_Re_Poly(Chess.DirectionToMove[0],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y,Chess.nSpace_Before[0]);
			
		}else
		{
			int i=Chess.Depth-1;
			for(i;i>=0;i--)
			{
				pMG->King_Kill_Re_Poly(Chess.DirectionToMove[i],Chess.nSide_,Chess.Location_Current.x,Chess.Location_Current.y,Chess.nSpace_Before[i],Chess.nSpace_After[i],Value_Buff[Chess.nPly][i]);
			}
		}
	}
	memcpy_s(this->Board_Copy,8*8*4,pMG->Board_MG,8*8*4);
}
//尚未被调用，或许存在位
//判断是否GameOver
int CSearchEngine::IsGameOver(int Depth)
{
	int i;	int j;
	bool Black_Live=false;	
	bool White_Live=false;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(Board_Copy[i][j]==BLACK_SOLDIER||Board_Copy[i][j]==BLACK_KING)
			{
				Black_Live=true;
			}
			else if(Board_Copy[i][j]==WHITE_SOLDIER||Board_Copy[i][j]==WHITE_KING)
			{
				White_Live=true;
			}
			else if(Black_Live==true&&White_Live==true)
				goto GO_TO_FLAG;

		}
	}
	GO_TO_FLAG :;
	i=(MaxPly-Depth+1)%2;
	if(Black_Live==false)
	{
		if(i)
			return 199990+Depth;
		else
			return -199990-Depth;
	}
	else if(White_Live==false)
	{
		if(i)
			return -199990-Depth;
		else
			return 199990+Depth;
	}
}
