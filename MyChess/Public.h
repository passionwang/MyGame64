#pragma once
#include "PublicDefine.h"
#include <list>
using namespace std;
//坐标结构体
typedef struct LOCATION
{
	int x;
	int y;
}Location;

//用于存储一个棋的所有信息
class CNodeChessInfo
{
public:
	CNodeChessInfo(void);
	//CNodeChessInfo(const CNodeChessInfo &Copy);
	virtual ~CNodeChessInfo(void);
public:
	Location Location_Current;//当前位置
	int nSide_;//势力范围
	int DirectionToMove[12];//最大12深度，每一深度对应一次走棋方向
	int Depth;//记录递归的层数，通过层数可以得出杀子的数量
	int nCount;//第n个棋子，遍历顺序为左上到右下
	int nSpace_Before[12];
	int nSpace_After[12];
	int nPly;
	CNodeChessInfo *pNext;
};


//公共的父类，用于储存MoveGeneration，SearchEngine，Evalution所需要调用及储存的信息
class CPublicInfo
{
public:
	CPublicInfo(void);
	virtual ~CPublicInfo(void);
public:

	Location Local_Current[12];//用于保存所有我方或对方棋子的坐标
	//!!!	nSpace_Before和nSpace_After可能在后续估值用的到，所以先不移动至MoveGenerator中
	int BeforeKingSpaceCount(int (*Board)[8],int Direction,int x,int y);//统计空格1，x，y是我方坐标
	int AfterKingSpaceCount(int (*Board)[8],int Direction,int x,int y);//统计空格2，x，y是敌方坐标
	

public:
	int Turn;
	int Board_Copy[8][8];
	int MaxDepth;
};



class Reset
{

public:
	Reset()
	{

	}
	~Reset()
	{

	}
public:
	static list<int (*)[8]> Board_Reset;
	static void Reset_Board();

};
