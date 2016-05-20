#include "stdafx.h"
#include "SearchEngine.h"
//�������⣺
//1.MoveGenerator��SearchEngine���ν�����
//2.����Board_Copy�ĸ�ֵ����
//3.MakeMove��ResetMakeMove��Ǳ������
//4.����������������ʱ����ܷ����ϴ����ߵ���ʼ��
//

CSearchEngine::CSearchEngine(void)
{
	pMG=NULL;//MoveGeneratorָ�����ڵ���MoveGenerator
	pEVA=NULL;
	MaxSearchPly=0;//�����������
	MaxPly=0;//��ǰ��������� 
	memset(Value_Buff,0,10*12*4);//////////////////////ATTENTION!!!!
	Best_Value=0; 
	BestChess=NULL;
}


CSearchEngine::~CSearchEngine(void)
{
	
	pMG=NULL;//MoveGeneratorָ�����ڵ���MoveGenerator
	pEVA=NULL;
	BestChess=NULL;
}
//��ʼ���������
void CSearchEngine::SetSearchDepth(int nPly)
{
	MaxSearchPly=nPly;
}
//��ʼ��Evalutor
void CSearchEngine::SetEvalutor(CEvalute *pEVA_Input)
{

	pEVA=pEVA_Input;

}
//��ʼ��MoveGenerator
void CSearchEngine::SetMoveGenerator(CMoveGenerator *pMG_Input)
{
	pMG=pMG_Input;

}
//��������֮�������
void CSearchEngine::MakeMove(CNodeChessInfo &Chess)
{
	if(Chess.nSide_==BLACK_SOLDIER||Chess.nSide_==WHITE_SOLDIER)//�ж������߻��Ǳ���
	{
		if(Chess.Depth==0)//�����ǰ���Ӳ���ɱ�壬�߲���
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
		if(Chess.Depth==0)//�����ǰ���Ӳ���ɱ�壬�߲���
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
//��ԭ����������
void CSearchEngine::ResetMakeMove(CNodeChessInfo &Chess)
{
	if(Chess.nSide_==BLACK_SOLDIER||Chess.nSide_==WHITE_SOLDIER)//�ж������߻��Ǳ���
	{
		if(Chess.Depth==0)//�����ǰ���Ӳ���ɱ�壬�߲���
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
		if(Chess.Depth==0)//�����ǰ���Ӳ���ɱ�壬�߲���
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
//��δ�����ã��������λ
//�ж��Ƿ�GameOver
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
