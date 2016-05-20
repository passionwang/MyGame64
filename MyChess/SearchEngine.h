#pragma once
#include "Public.h"
#include "MoveGenerator.h"
#include "Evalute.h"
class CSearchEngine:public CPublicInfo
{
public:
	CSearchEngine(void);
	virtual ~CSearchEngine(void);
	///////////////搜索引擎接口/////////////////////////////////
	virtual void SearchAGoodMove(int (*iBoard)[8])=0;//搜索出当前最好的行棋方法
	///////////////搜索引擎接口/////////////////////////////////
	void SetSearchDepth(int nPly);//初始化搜索深度
	void SetEvalutor(CEvalute *pEVA_Input);//初始化Evalutor
	void SetMoveGenerator(CMoveGenerator *pMG_Input);//初始化MoveGenerator
	//产生行棋之后的棋盘,nTypeRoute第n种走法，只负责产生当前一种局面
	void MakeMove(CNodeChessInfo &Chess);
	//还原行棋后的棋盘,nTypeRoute第n种走法，只负责还原当前一种局面
	void ResetMakeMove(CNodeChessInfo &Chess);
	////////ATTENTION!!!尚未调用//////////
	int IsGameOver(int Depth);//判断是否GameOver	
protected:
	//;//储存最佳行棋的棋子，其中保存了最佳行棋方法
	CMoveGenerator *pMG;//MoveGenerator指针用于调用MoveGenerator
	CEvalute *pEVA;
	int MaxSearchPly;//最大的搜索深度
	int MaxPly;//最大搜索深度 
	int Value_Buff[10][100];//10层//储存杀死的棋子的价值，用于还原棋盘用
	int Best_Value; //用于存储最终估值
	CNodeChessInfo *BestChess;

};

