#pragma once
#include "PublicDefine.h"
#include <list>
using namespace std;
//����ṹ��
typedef struct LOCATION
{
	int x;
	int y;
}Location;

//���ڴ洢һ�����������Ϣ
class CNodeChessInfo
{
public:
	CNodeChessInfo(void);
	//CNodeChessInfo(const CNodeChessInfo &Copy);
	virtual ~CNodeChessInfo(void);
public:
	Location Location_Current;//��ǰλ��
	int nSide_;//������Χ
	int DirectionToMove[12];//���12��ȣ�ÿһ��ȶ�Ӧһ�����巽��
	int Depth;//��¼�ݹ�Ĳ�����ͨ���������Եó�ɱ�ӵ�����
	int nCount;//��n�����ӣ�����˳��Ϊ���ϵ�����
	int nSpace_Before[12];
	int nSpace_After[12];
	int nPly;
	CNodeChessInfo *pNext;
};


//�����ĸ��࣬���ڴ���MoveGeneration��SearchEngine��Evalution����Ҫ���ü��������Ϣ
class CPublicInfo
{
public:
	CPublicInfo(void);
	virtual ~CPublicInfo(void);
public:

	Location Local_Current[12];//���ڱ��������ҷ���Է����ӵ�����
	//!!!	nSpace_Before��nSpace_After�����ں�����ֵ�õĵ��������Ȳ��ƶ���MoveGenerator��
	int BeforeKingSpaceCount(int (*Board)[8],int Direction,int x,int y);//ͳ�ƿո�1��x��y���ҷ�����
	int AfterKingSpaceCount(int (*Board)[8],int Direction,int x,int y);//ͳ�ƿո�2��x��y�ǵз�����
	

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
