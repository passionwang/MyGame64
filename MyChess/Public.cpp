#include "stdafx.h"
#include "Public.h"
#include <iostream>


CPublicInfo::CPublicInfo(void)
{
	Turn=0;
	MaxDepth=0;
	memset(this->Board_Copy,0,8*8*4);
	for(int i=0;i<12;i++)
	{
		Local_Current[i].x=0;
		Local_Current[i].y=0;
	}
}
CPublicInfo::~CPublicInfo(void)
{

}



//���ӽڵ��ʼ��
CNodeChessInfo::CNodeChessInfo(void)
{
	this->Location_Current.x=0;//��ǰλ��
	this->Location_Current.y=0;//��ǰλ��
	this->Depth=0;
	this->nCount=0;
	this->nSide_=0;
	this->nPly=0;
	memset(DirectionToMove,0,12*4);
	memset(nSpace_Before,0,12*4);
	memset(nSpace_After,0,12*4);
	
	this->pNext=NULL;
}
CNodeChessInfo::~CNodeChessInfo(void)
{

	this->pNext=NULL;

}

//ͳ�����ķ���������Ŀո�����
int CPublicInfo::BeforeKingSpaceCount(int (*Board)[8],int Direction,int x,int y)
{
	int nCount=0;
	switch(Direction)
	{
	case 1://�������������
		{
			while((x>0&&y>0)&&Board[--x][--y]==EMPTY)
			{
				nCount++;
			}
			return nCount;
		}
	case 2://�������������
		{
			while((x>0&&y<7)&&Board[--x][++y]==EMPTY)
			{
				nCount++;
			}
			return nCount;

		}
	case -1://�������������
		{
			while((x<7&&y<7)&&Board[++x][++y]==EMPTY)
			{
				nCount++;
			}
			return nCount;
		}
	case -2://�������������
		{
			while((x<7&&y>0)&&Board[++x][--y]==EMPTY)
			{
				nCount++;
			}
			return nCount;
		}
	}
	return false;
}
//ͳ�ƹµ����Ӻ󷽵Ŀո�������Ҳ�����λ��
int CPublicInfo::AfterKingSpaceCount(int (*Board)[8],int Direction,int x,int y)
{
	int nCount=0;
	int nSide=Board[x][y];
	int Enemy=(nSide<0?BLACK_SOLDIER:WHITE_SOLDIER);
	switch(Direction)
	{
	case 1://�������������
		{
			while((x>0&&y>0)&&Board[--x][--y]==EMPTY);
			if(Board[x][y]==Enemy||Board[x][y]==Enemy*2)
			{

				while((x!=0&&y!=0)&&(Board[--x][--y]==EMPTY))
				{
					
					nCount++;
					if(x==0||y==0)
						return nCount;
				}
				return nCount;
			}
			return nCount;
		}
	case 2://�������������
		{
			while((x>0&&y<7)&&Board[--x][++y]==EMPTY);
			if(Board[x][y]==Enemy||Board[x][y]==Enemy*2)
			{
				while((x!=0&&y!=7)&&(Board[--x][++y]==EMPTY))
				{				
					nCount++;
					if(x==0||y==0)
						return nCount;
				}
				return nCount;
			}
			return nCount;
		}
	case -1://�������������
		{
			while((x<7&&y<7)&&Board[++x][++y]==EMPTY);
			if(Board[x][y]==Enemy||Board[x][y]==Enemy*2)
			{
				while((x!=7&&y!=7)&&(Board[++x][++y]==EMPTY))
				{				
					nCount++;
					if(x==0||y==0)
						return nCount;
				}
				return nCount;

			}
			return nCount;
		}
	case -2://�������������
		{
			while((x<7&&y>0)&&Board[++x][--y]==EMPTY);
			
			if(Board[x][y]==Enemy||Board[x][y]==Enemy*2)
			{
				while((x!=7&&y!=0)&&(Board[++x][--y]==EMPTY))
				{
					
					nCount++;
					if(x==0||y==0)
						return nCount;
				}
				return nCount;
			}
			return nCount;
		}

	}
	return false; 
}



list<int (*)[8]> Reset::Board_Reset;
extern int iBoard[8][8];
void Reset::Reset_Board()
{
	list<int (*)[8]>::iterator ite= Reset::Board_Reset.begin();
	memcpy_s(iBoard,8*8*4,*ite,8*8*4);
	free(*ite);
	Reset::Board_Reset.pop_front();
	//Invalidate();
}
	