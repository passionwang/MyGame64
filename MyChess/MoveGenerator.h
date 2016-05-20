#pragma once
#include "PublicDefine.h"
#include "Public.h"
class CMoveGenerator:public CPublicInfo
{
public:
	CMoveGenerator();
	CMoveGenerator(int (*Input_Board)[8]);
	virtual ~CMoveGenerator();

public:
	int MakePossibleChess(int nSide,int nPly);
	//�߶�����
	void Move_Poly(int Direction,int nSide,int &x,int &y);
	//��ԭ�߶�����
	void Move_Re_Poly(int Direction,int nSide,int &x,int &y);
	//ɱ�岼��,����ɱ������ļ�ֵ
	int Move_Kill(int Direction,int nSide,int &x,int &y);
	//��ԭɱ�岼��
	void Move_Re_Kill(int Direction,int nSide,int &x,int &y,int Value);
	//�����߶�����
	void King_Move_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before);
	//�����߶����ֻ�ԭ
	void King_Move_Re_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before);
	//����ɱ�岼�֣�����ɱ������ļ�ֵ
	int King_Kill_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int nSpace_After);
	//����ɱ�岼�ֻ�ԭ
	void King_Kill_Re_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int nSpace_After,int Value);
	
	//���̸�������ֹ��Ⱦԭ����������
	int Board_MG[8][8];
	//�����������ӵĿ�������Ϣ
	CNodeChessInfo PossibleMove[10][100];
	static int nTypeToGo;

	
private:
	int Kill_Method;
	int Kill_Flag;
	int DepthMax[12];
protected:
	//PossibleMove���㺯��
	void FUNC_RESET(int nPly);
	bool MakePossibleKill(int x,int y,int nSide,int nCount,int Depth,int Direction_Form,int nPly);
	void MakePossibleMove(int x,int y,int nCount,int Value,int nPly);
	//��Ӳ�����Ϣ
	void Add_Poly(int nCount,int nSide,int Depth,int Direction_to,int nSpace_Before,int nPly);
	//��������ɱ����е�����,�����Ժ�ɸѡ
	void Kill_Chain_Add(int nCount,int nSide,int Depth,int Direction_to,int nSpace_Before,int nSpace_After,int x,int y,int nPly);
	//�������
	void Chain_Clear(void);
	
	//����ɱ�������е���Ϣ����ȡ��ɱ�������߷�
	bool AnalyzeKillInfo(int nCount,int (*Board_MG)[8],int nSide,int nPly);
	CNodeChessInfo *Head;
	CNodeChessInfo *Link;
	
};



