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
	//走动布局
	void Move_Poly(int Direction,int nSide,int &x,int &y);
	//还原走动布局
	void Move_Re_Poly(int Direction,int nSide,int &x,int &y);
	//杀棋布局,返回杀掉的棋的价值
	int Move_Kill(int Direction,int nSide,int &x,int &y);
	//还原杀棋布局
	void Move_Re_Kill(int Direction,int nSide,int &x,int &y,int Value);
	//王的走动布局
	void King_Move_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before);
	//王的走动布局还原
	void King_Move_Re_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before);
	//王的杀棋布局，返回杀掉的棋的价值
	int King_Kill_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int nSpace_After);
	//王的杀棋布局还原
	void King_Kill_Re_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int nSpace_After,int Value);
	
	//棋盘副本，防止污染原有棋盘数据
	int Board_MG[8][8];
	//保存所有棋子的可行性信息
	CNodeChessInfo PossibleMove[10][100];
	static int nTypeToGo;

	
private:
	int Kill_Method;
	int Kill_Flag;
	int DepthMax[12];
protected:
	//PossibleMove置零函数
	void FUNC_RESET(int nPly);
	bool MakePossibleKill(int x,int y,int nSide,int nCount,int Depth,int Direction_Form,int nPly);
	void MakePossibleMove(int x,int y,int nCount,int Value,int nPly);
	//添加布局信息
	void Add_Poly(int nCount,int nSide,int Depth,int Direction_to,int nSpace_Before,int nPly);
	//保存所有杀棋队列的链表,便于以后筛选
	void Kill_Chain_Add(int nCount,int nSide,int Depth,int Direction_to,int nSpace_Before,int nSpace_After,int x,int y,int nPly);
	//清空链表
	void Chain_Clear(void);
	
	//解析杀棋链表中的信息，提取出杀得最多的走法
	bool AnalyzeKillInfo(int nCount,int (*Board_MG)[8],int nSide,int nPly);
	CNodeChessInfo *Head;
	CNodeChessInfo *Link;
	
};



