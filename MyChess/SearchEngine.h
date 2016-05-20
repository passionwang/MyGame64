#pragma once
#include "Public.h"
#include "MoveGenerator.h"
#include "Evalute.h"
class CSearchEngine:public CPublicInfo
{
public:
	CSearchEngine(void);
	virtual ~CSearchEngine(void);
	///////////////��������ӿ�/////////////////////////////////
	virtual void SearchAGoodMove(int (*iBoard)[8])=0;//��������ǰ��õ����巽��
	///////////////��������ӿ�/////////////////////////////////
	void SetSearchDepth(int nPly);//��ʼ���������
	void SetEvalutor(CEvalute *pEVA_Input);//��ʼ��Evalutor
	void SetMoveGenerator(CMoveGenerator *pMG_Input);//��ʼ��MoveGenerator
	//��������֮�������,nTypeRoute��n���߷���ֻ���������ǰһ�־���
	void MakeMove(CNodeChessInfo &Chess);
	//��ԭ����������,nTypeRoute��n���߷���ֻ����ԭ��ǰһ�־���
	void ResetMakeMove(CNodeChessInfo &Chess);
	////////ATTENTION!!!��δ����//////////
	int IsGameOver(int Depth);//�ж��Ƿ�GameOver	
protected:
	//;//���������������ӣ����б�����������巽��
	CMoveGenerator *pMG;//MoveGeneratorָ�����ڵ���MoveGenerator
	CEvalute *pEVA;
	int MaxSearchPly;//�����������
	int MaxPly;//���������� 
	int Value_Buff[10][100];//10��//����ɱ�������ӵļ�ֵ�����ڻ�ԭ������
	int Best_Value; //���ڴ洢���չ�ֵ
	CNodeChessInfo *BestChess;

};

