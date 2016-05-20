#include "stdafx.h"
#include "AlphaBeta.h"
#include "MoveGenerator.h"
//bug1���������⣬��������Ч��¼�����߷�
//bug2���߷��������м�¼�߷�����ò����bug
//bug3������PossibleMove[10][100],�Ƿ�Ӧ�����˳�ĳһ���ǽ�����������ȫ��reset�������reset�Ļ�			BestChess��ԶָNULL��������Ҫע��
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
	//22��24���ɵ���λ�ã���Ϊ24��ִ�е�����22��Board_Copy
	CMoveGenerator pMG_Input(Board_Copy);
	CEvalute pEVA_Input;
	SetMoveGenerator(&pMG_Input);
	SetEvalutor(&pEVA_Input);

	
	AlphaBeta(0,Alpha,Beta);
	MakeMove(*BestChess);

	memcpy_s(Board_Copy,8*8*4,pMG->Board_MG,8*8*4);

	//1.ͳ�Ƶ�ǰ�ҷ�����������
	//2.�����������ӵ�Alpha-Beta��֦�㷨�г��������ӵ���ѷ���(��ֵ)
	//3.��ѡ���Ź�ֵ������
	//4.����
}
int CAlphaBeta::AlphaBeta(int nPly,int Alpha,int Beta)
{
	int Value=0;
	int i=0;
	int nTypeRoute=0;
	if(nPly%2!=0&&nPly!=0)
		Turn = ENEMY;	//������������2��ż�����������ض��ǶԷ�����
	else
		Turn = MINE;	//����Ϊ�ҷ�����
	if((i=IsGameOver(nPly))<=-199990||(i=IsGameOver(nPly))>=199990)
		return i;
	if(nPly==MaxSearchPly)
	{

		return	pEVA->Evalute(pMG->Board_MG,this->Turn);	//���ع�ֵ
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