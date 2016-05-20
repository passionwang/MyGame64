#include "stdafx.h"
#include "Evalute.h"


CEvalute::CEvalute(void)
{
	pPI=new CPublicInfo;
	pMG=new CMoveGenerator;
	memset(Board_Eva,0,8*8*4);
}


CEvalute::~CEvalute(void)
{
}
int CEvalute::Evalute(int (*Board)[8],int Turn)
{
	int Total_Value=0;
	int Element_Value=0;
	int Poly_Value=0;
	pPI->Turn=Turn;
	memcpy_s(Board_Eva,8*8*4,Board,8*8*4);
	Element_Value=ValueCount()+SafetyCount()+AttackCount()+DefenseCount();
	Poly_Value=0;
	Total_Value=Element_Value+Poly_Value;
	return Total_Value;
}

////灵活性
//int CEvalute::FlexibleCount()
//{
//	//有成王的可能性非常重要
//	int FlexibleWhiteSoldierCount=0;
//	int FlexibleWhiteKingCount=0;
//	int FlexibleBlackSoldierCount=0;
//	int FlexibleBlackKingCount=0;
//	int nCount=0;
//	int nTypeRoute_White=pMG->MakePossibleChess(MINE,0);
//	int nTypeRoute_Black=pMG->MakePossibleChess(ENEMY,0);
//	//可能性：能杀人---王或兵，例如同时有兵和王都能杀同样多的子
//	//		  不能杀人---王或兵
//	for(nCount;nCount<nTypeRoute_White;nCount++)
//	{
//		if(pMG->PossibleMove[0][nCount].Depth!=0)//说明能杀人 
//		{
//			if(pMG->PossibleMove[0][nCount].nSide_==WHITE_KING||pMG->PossibleMove[0][nCount].nSide_==BLACK_KING)
//			{
//				FlexibleWhiteKingCount++;
//			}
//			else if(pMG->PossibleMove[0][nCount].nSide_==WHITE_SOLDIER||pMG->PossibleMove[0][nCount].nSide_==BLACK_SOLDIER)
//			{
//				FlexibleWhiteSoldierCount++;
//			}
//		}else
//		{
//			if(pMG->PossibleMove[0][nCount].nSide_==WHITE_KING||pMG->PossibleMove[0][nCount].nSide_==BLACK_KING)
//			{
//				FlexibleWhiteKingCount++;
//			}
//			else if(pMG->PossibleMove[0][nCount].nSide_==WHITE_SOLDIER||pMG->PossibleMove[0][nCount].nSide_==WHITE_SOLDIER)
//			{
//				FlexibleWhiteSoldierCount++;
//			}
//		}
//	}
//	return FlexibleValue;
//}
//价值计数
int CEvalute::ValueCount()
{
	int TotalWhiteValue=0;
	int TotalBlackValue=0;
	int NumBlackSoldierLine[8];
	int NumBlackKingLine[8];
	int NumWhiteSoldierLine[8];
	int NumWhiteKingLine[8];
	int Value=0;
	memset(NumBlackSoldierLine,0,8*4);
	memset(NumBlackKingLine,0,8*4);
	memset(NumWhiteSoldierLine,0,8*4);
	memset(NumWhiteKingLine,0,8*4);
	//棋盘计数
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(Board_Eva[i][j]==WHITE_SOLDIER)
				++NumWhiteSoldierLine[i];
			else if(Board_Eva[i][j]==WHITE_KING)
				++NumWhiteKingLine[i];
			if(Board_Eva[i][j]==BLACK_SOLDIER)
				++NumBlackSoldierLine[i];
			else if(Board_Eva[i][j]==BLACK_KING)
				++NumBlackKingLine[i];
		}

	}
	//价值估算
	for(int i=0;i<8;i++)
	{
		switch(i)
		{
		case 0:
			TotalWhiteValue+=NumWhiteSoldierLine[0]*SOLDIER_VAL_0+NumWhiteKingLine[0]*KING_VAL;
			TotalBlackValue+=NumBlackKingLine[0]*KING_VAL;
			break;
		case 1:
			TotalWhiteValue+=NumWhiteSoldierLine[1]*SOLDIER_VAL_1+NumWhiteKingLine[1]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[1]+SOLDIER_VAL_6+NumBlackKingLine[1]*KING_VAL;
			break;
		case 2:
			TotalWhiteValue+=NumWhiteSoldierLine[2]*SOLDIER_VAL_2+NumWhiteKingLine[2]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[2]+SOLDIER_VAL_5+NumBlackKingLine[2]*KING_VAL;
			break;
		case 3:
			TotalWhiteValue+=NumWhiteSoldierLine[3]*SOLDIER_VAL_3+NumWhiteKingLine[3]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[3]+SOLDIER_VAL_4+NumBlackKingLine[3]*KING_VAL;
			break;
		case 4:
			TotalWhiteValue+=NumWhiteSoldierLine[4]*SOLDIER_VAL_4+NumWhiteKingLine[4]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[4]+SOLDIER_VAL_3+NumBlackKingLine[4]*KING_VAL;
			break;
		case 5:
			TotalWhiteValue+=NumWhiteSoldierLine[5]*SOLDIER_VAL_5+NumWhiteKingLine[5]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[5]+SOLDIER_VAL_2+NumBlackKingLine[5]*KING_VAL;
			break;
		case 6:
			TotalWhiteValue+=NumWhiteSoldierLine[6]*SOLDIER_VAL_6+NumWhiteKingLine[6]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[6]+SOLDIER_VAL_1+NumBlackKingLine[6]*KING_VAL;
			break;
		case 7:
			TotalWhiteValue+=NumWhiteKingLine[7]*KING_VAL;
			TotalBlackValue+=NumBlackSoldierLine[7]+SOLDIER_VAL_0+NumBlackKingLine[7]*KING_VAL;
			break;
		}

	}
	if(pPI->Turn==ENEMY)
		return Value=TotalBlackValue-TotalWhiteValue;
	else if(pPI->Turn==MINE)
		return Value=TotalWhiteValue-TotalBlackValue;
}
//安全态计数
int CEvalute::SafetyCount()
{
	int TotalBlackValue=0;
	int TotalWhiteValue=0;

	int NumDefenseBlack=0;
	int NumBoardBlack=0;
	int NumDefenseWhite=0;
	int NumBoardWhite=0;

	int NumBlackKing=0;
	int NumWhiteKing=0;
	/////边界安全态//////
	for(int j=0;j<8;j++)
	{
		if(Board_Eva[0][j]==WHITE_SOLDIER)
			++NumBoardWhite;
		if(Board_Eva[0][j]==WHITE_KING)
			++NumWhiteKing;
		if(Board_Eva[7][j]==WHITE_KING)
			++NumWhiteKing;

		if(Board_Eva[7][j]==BLACK_SOLDIER)
			++NumBoardBlack;
		if(Board_Eva[7][j]==BLACK_KING)
			++NumBlackKing;
		if(Board_Eva[0][j]==BLACK_KING)
			++NumBlackKing;
	}
	for(int i=0;i<8;i++)
	{
		if(Board_Eva[i][0]==WHITE_SOLDIER)
			++NumBoardWhite;
		else if(Board_Eva[i][0]==WHITE_KING)
			++NumWhiteKing;
		if(Board_Eva[i][7]==WHITE_SOLDIER)
			++NumBoardWhite;
		else if(Board_Eva[i][7]==WHITE_KING)
			++NumWhiteKing;
	}
	/////被防御安全态//////
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(((0<i<7)&&(0<j<7)))
			{
				if(Board_Eva[i][j]==WHITE_SOLDIER)
				{
					if(Board_Eva[i-1][j-1]==WHITE_SOLDIER||Board_Eva[i-1][j-1]==WHITE_KING)
						++NumDefenseWhite;
					if(Board_Eva[i-1][j+1]==WHITE_SOLDIER||Board_Eva[i-1][j+1]==WHITE_KING)
						++NumDefenseWhite;
					if(Board_Eva[i+1][j-1]==WHITE_SOLDIER||Board_Eva[i+1][j-1]==WHITE_KING)
						++NumDefenseWhite;
					if(Board_Eva[i+1][j+1]==WHITE_SOLDIER||Board_Eva[i+1][j+1]==WHITE_KING)
						++NumDefenseWhite;
				}
				//if(Board_Eva[i][j]==WHITE_KING)
				//{
				//	if(Board_Eva[i-1][j-1]==WHITE_SOLDIER||Board_Eva[i-1][j-1]==WHITE_KING)
				//		++NumWhiteKing;
				//	if(Board_Eva[i-1][j+1]==WHITE_SOLDIER||Board_Eva[i-1][j+1]==WHITE_KING)
				//		++NumWhiteKing;
				//	if(Board_Eva[i+1][j-1]==WHITE_SOLDIER||Board_Eva[i+1][j-1]==WHITE_KING)
				//		++NumWhiteKing;
				//	if(Board_Eva[i+1][j+1]==WHITE_SOLDIER||Board_Eva[i+1][j+1]==WHITE_KING)
				//		++NumWhiteKing;
				//}
				if(Board_Eva[i][j]==BLACK_SOLDIER)
				{
					if(Board_Eva[i-1][j-1]==BLACK_SOLDIER||Board_Eva[i-1][j-1]==BLACK_KING)
						++NumDefenseBlack;
					if(Board_Eva[i-1][j+1]==BLACK_SOLDIER||Board_Eva[i-1][j+1]==BLACK_KING)
						++NumDefenseBlack;
					if(Board_Eva[i+1][j-1]==BLACK_SOLDIER||Board_Eva[i+1][j-1]==BLACK_KING)
						++NumDefenseBlack;
					if(Board_Eva[i+1][j+1]==BLACK_SOLDIER||Board_Eva[i+1][j+1]==BLACK_KING)
						++NumDefenseBlack;
				}
				//if(Board_Eva[i][j]==BLACK_KING)
				//{
				//	if(Board_Eva[i-1][j-1]==BLACK_SOLDIER||Board_Eva[i-1][j-1]==BLACK_KING)
				//		++NumBlackKing;
				//	if(Board_Eva[i-1][j+1]==BLACK_SOLDIER||Board_Eva[i-1][j+1]==BLACK_KING)
				//		++NumBlackKing;
				//	if(Board_Eva[i+1][j-1]==BLACK_SOLDIER||Board_Eva[i+1][j-1]==BLACK_KING)
				//		++NumBlackKing;
				//	if(Board_Eva[i+1][j+1]==BLACK_SOLDIER||Board_Eva[i+1][j+1]==BLACK_KING)
				//		++NumBlackKing;
				//}
			
			}

		}

	}
	TotalWhiteValue=NumWhiteKing*SAFETY_KING_VAL+NumBoardWhite*SAFETY_SOLDIER_BOARD_VAL+NumDefenseWhite*SAFETY_SOLDIER_DEFENSE_VAL;		
	TotalBlackValue=NumBlackKing*SAFETY_KING_VAL+NumBoardBlack*SAFETY_SOLDIER_BOARD_VAL+NumDefenseBlack*SAFETY_SOLDIER_DEFENSE_VAL;	
	if(pPI->Turn==ENEMY)
		return TotalBlackValue-TotalWhiteValue;
	else if(pPI->Turn==MINE)
		return TotalWhiteValue-TotalBlackValue;
}
//攻击态计数
int CEvalute::AttackCount()
{
	//攻击态的标准：1.某方棋子的前进方向为EMPTY
	//				2.某方棋子的前进方向为为ENEMY(此情况不适用于ENEMY在边界,且我方后方必须有防御)
	//				3.后方棋子为ENEMY
	int NumBlack=0;
	int NumWhite=0;
	int NumBlackKing=0;
	int NumWhiteKing=0;
	int TotalWhiteValue=0;
	int TotalBlackValue=0;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(Board_Eva[i][j]==WHITE_SOLDIER)
			{
				//////黑棋视角//////
				if(Board_Eva[i+1][j-1]==EMPTY)
					++NumWhite;
				if(((i<6)&&(1<j)&&(j<6))
					&&((Board_Eva[i+1][j-1]==BLACK_SOLDIER||Board_Eva[i+1][j-1]==BLACK_KING))
					&&((Board_Eva[i-1][j+1]==WHITE_SOLDIER||Board_Eva[i-1][j+1]==WHITE_SOLDIER)))
				{
					++NumWhite;
				}
				if(Board_Eva[i+1][j+1]==EMPTY)
					++NumWhite;
				if((i<6)&&((j>1)&&(j<6))
					&&((Board_Eva[i+1][j+1]==BLACK_SOLDIER||Board_Eva[i+1][j+1]==BLACK_KING))
					&&((Board_Eva[i-1][j-1]==WHITE_SOLDIER||Board_Eva[i-1][j-1]==WHITE_SOLDIER)))
				{
					++NumWhite;
				}
			}
			if(Board_Eva[i][j]==WHITE_KING)
			{
				Location Local_Current;
				Local_Current.x=i;
				Local_Current.y=j;
				while((Local_Current.x!=7&&Local_Current.y!=7)&&(Board_Eva[++Local_Current.x][++Local_Current.y]!=WHITE_SOLDIER||Board_Eva[++Local_Current.x][++Local_Current.y]!=WHITE_KING))
				{
					++NumWhiteKing;break;
				}
				Local_Current.x=i;
				Local_Current.y=j;
				while(Local_Current.x!=7&&Local_Current.y!=0&&(Board_Eva[++Local_Current.x][--Local_Current.y]!=WHITE_SOLDIER||Board_Eva[++Local_Current.x][--Local_Current.y]!=WHITE_KING))
				{
					++NumWhiteKing;break;
				}
				Local_Current.x=i;
				Local_Current.y=j;
				while((Local_Current.x!=0&&Local_Current.y!=7)&&(Board_Eva[--Local_Current.x][++Local_Current.y]!=WHITE_SOLDIER||Board_Eva[--Local_Current.x][++Local_Current.y]!=WHITE_KING))
				{
					++NumWhiteKing;break;						
				}
				Local_Current.x=i;
				Local_Current.y=j;
				while((Local_Current.x!=0&&Local_Current.y!=0)&&(Board_Eva[--Local_Current.x][--Local_Current.y]!=WHITE_SOLDIER||Board_Eva[--Local_Current.x][--Local_Current.y]!=WHITE_KING))
				{
					++NumWhiteKing;break;				
				}

			}			
			//////黑棋视角//////
			if(Board_Eva[i][j]==BLACK_SOLDIER)
			{
				//////黑棋视角//////
				if(Board_Eva[i-1][j-1]==EMPTY)
					++NumWhite;
				if(((i>1)&&(1<j)&&(j<6))
					&&((Board_Eva[i-1][j-1]==WHITE_SOLDIER||Board_Eva[i-1][j-1]==WHITE_KING))
					&&((Board_Eva[i+1][j+1]==BLACK_SOLDIER||Board_Eva[i+1][j+1]==BLACK_KING)))
				{
					++NumBlack;
				}
				if(Board_Eva[i-1][j+1]==EMPTY)
					++NumWhite;
				if((i>1)&&((j>1)&&(j<6))
					&&((Board_Eva[i-1][j+1]==WHITE_SOLDIER||Board_Eva[i-1][j+1]==WHITE_KING))
					&&((Board_Eva[i+1][j-1]==BLACK_SOLDIER||Board_Eva[i+1][j-1]==BLACK_KING)))
				{
					++NumBlack;
				}
			}
			if(Board_Eva[i][j]==BLACK_KING)
			{
				Location Local_Current;
				Local_Current.x=i;
				Local_Current.y=j;
				while((Local_Current.x!=7&&Local_Current.y!=7)&&(Board_Eva[++Local_Current.x][++Local_Current.y]!=BLACK_SOLDIER||Board_Eva[++Local_Current.x][++Local_Current.y]!=BLACK_KING))
				{
					++NumBlackKing;break;
				}
				Local_Current.x=i;
				Local_Current.y=j;
				while(Local_Current.x!=7&&Local_Current.y!=0&&(Board_Eva[++Local_Current.x][--Local_Current.y]!=BLACK_SOLDIER||Board_Eva[++Local_Current.x][--Local_Current.y]!=BLACK_KING))
				{
					++NumBlackKing;break;
				}
				Local_Current.x=i;
				Local_Current.y=j;
				while((Local_Current.x!=0&&Local_Current.y!=7)&&(Board_Eva[--Local_Current.x][++Local_Current.y]!=BLACK_SOLDIER||Board_Eva[--Local_Current.x][++Local_Current.y]!=BLACK_KING))
				{
					++NumBlackKing;break;						
				}
				Local_Current.x=i;
				Local_Current.y=j;
				while((Local_Current.x!=0&&Local_Current.y!=0)&&(Board_Eva[--Local_Current.x][--Local_Current.y]!=BLACK_SOLDIER||Board_Eva[--Local_Current.x][--Local_Current.y]!=BLACK_KING))
				{
					++NumBlackKing;break;				
				}

			}
			
		}
	}
	TotalWhiteValue=NumWhiteKing*ATTACK_KING_VAL+NumWhite*ATTACK_SOLDIER_VAL;
	TotalBlackValue=NumBlackKing*ATTACK_KING_VAL+NumBlack*ATTACK_SOLDIER_VAL;
	if(pPI->Turn==ENEMY)
		return TotalBlackValue-TotalWhiteValue;
	else if(pPI->Turn==MINE)
		return TotalWhiteValue-TotalBlackValue;
}
//防御态计数
int CEvalute::DefenseCount()
{
	//防御态基准： 当我方棋子前进方向为我方棋子时，此棋子为防御态，当然注意棋子范围
	int NumBlack=0;
	int NumWhite=0;
	int NumBlackKing=0;
	int NumWhiteKing=0;
	int TotalBlackValue=0;
	int TotalWhiteValue=0;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if((i<7)&&(j>0)&&(j<7)&&(Board_Eva[i][j]==WHITE_SOLDIER||Board_Eva[i][j]==WHITE_KING))
			{
				if(Board_Eva[i+1][j-1]==WHITE_SOLDIER||Board_Eva[i+1][j-1]==WHITE_KING)
					NumWhite++;
				if(Board_Eva[i+1][j+1]==WHITE_SOLDIER||Board_Eva[i+1][j+1]==WHITE_KING)
					NumWhite++;
			}

			if((i>0)&&(j>0)&&(j<7)&&Board_Eva[i][j]==BLACK_SOLDIER||Board_Eva[i][j]==BLACK_KING)
			{
				if(Board_Eva[i-1][j-1]==BLACK_SOLDIER||Board_Eva[i-1][j-1]==BLACK_KING)
					NumBlack++;
				if(Board_Eva[i-1][j+1]==BLACK_SOLDIER||Board_Eva[i-1][j+1]==BLACK_KING)
					NumBlack++;
			}

		}

	}
	TotalBlackValue=NumBlackKing*DEFENCE_KING_VAL+NumBlack*DEFENCE_SOLDIER_VAL;
	TotalWhiteValue=NumWhiteKing*DEFENCE_KING_VAL+NumWhite*DEFENCE_SOLDIER_VAL;
	if(pPI->Turn==ENEMY)
		return TotalBlackValue-TotalWhiteValue;
	else if(pPI->Turn==MINE)
		return TotalWhiteValue-TotalBlackValue;
}
//int TriangleCount()
//{
//
//
//}
//int DefenseLineCount()
//{
//
//
//}
