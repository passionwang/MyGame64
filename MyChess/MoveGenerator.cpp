#include "MoveGenerator.h"
#include <string.h>
//坐标0.0点为左上角，横为y，竖为x,根据数组的特征来
//此走法生成器不能恒成为我方视角，因为搜索引擎会涉及到对方的走法生成，所以应该以通用的角度设计
//nSide不光可以分析阵营，还包含了棋的价值（value）信息
//原则：对单一某个棋子而言：能杀必杀，能杀多杀最多
//由于是对单一棋子而言，不能保证所有棋子相比下挑选杀最多的走

CMoveGenerator::CMoveGenerator()
{

	this->Head=NULL;
	this->Link=NULL;
	Kill_Method=0;
	memset(DepthMax,0,12*4);

}
CMoveGenerator::CMoveGenerator(int (*InputBoard)[8])
{
	this->Head=NULL;
	this->Link=NULL;
	Kill_Method=0;
	memcpy_s(Board_MG,8*8*4,InputBoard,8*8*4);
	memset(DepthMax,0,12*4);
	
}
CMoveGenerator::~CMoveGenerator()
{
	this->Head=NULL;
	this->Link=NULL;
	Kill_Method=0;
	memset(Board_MG,0,8*8*4);
}
int CMoveGenerator::nTypeToGo=0;

int CMoveGenerator::MakePossibleChess(int nSide,int nPly)
{
	int nCount=-1;
	Kill_Method=0;
	Kill_Flag=0;
	FUNC_RESET(nPly);
	memset(DepthMax,0,12*4);
	for(int x=0;x<8;x++)
	{
		for(int y=0;y<8;y++)
		{
			
			if(Board_MG[x][y]==nSide||Board_MG[x][y]==nSide*2)//找到nSide方棋子，nCOUNT++
			{
				int Value=Board_MG[x][y];
				nCount++;
				Local_Current[nCount].x=x;
				Local_Current[nCount].y=y;				
				if((Kill_Method=MakePossibleKill(x,y,Value,nCount,0,0,nPly))>0)//如果可以杀棋，添加杀棋队列
				{
					Kill_Flag=1;
					//筛选出杀的最多的棋子
					AnalyzeKillInfo(nCount,Board_MG,Value,nPly);
					Kill_Method=0;
				}else//不能杀棋，走布局
				{
					MakePossibleMove(x,y,nCount,Value,nPly);					
				}
			}
		}
	}
	int Max=0;
	Max=DepthMax[0];
	for(int i=0;i<12;i++)
	{
		if(Max<DepthMax[i])
		{
			Max=DepthMax[i];
		}
	}
	int j=0;
	int SumToGo=nTypeToGo;
	MaxDepth=Max;
	if(Kill_Flag!=0)
	{
		for(int i=0;i<nTypeToGo;i++)
		{
			if(PossibleMove[nPly][i].Depth!=Max)
			{
				PossibleMove[nPly][i].Depth=0;
				PossibleMove[nPly][i].Location_Current.x=0;
				PossibleMove[nPly][i].Location_Current.y=0;
				PossibleMove[nPly][i].nCount=0;
				PossibleMove[nPly][i].nPly=0;
				PossibleMove[nPly][i].nSide_=0;
				PossibleMove[nPly][i].pNext=NULL;
				memset(PossibleMove[nPly][i].nSpace_After,0,12*4);
				memset(PossibleMove[nPly][i].nSpace_Before,0,12*4);
				memset(PossibleMove[nPly][i].DirectionToMove,0,12*4);
			}
			if(PossibleMove[nPly][i].Depth==Max)
			{
				PossibleMove[nPly][j].Depth=PossibleMove[nPly][i].Depth;
				PossibleMove[nPly][j].Location_Current.x=PossibleMove[nPly][i].Location_Current.x;
				PossibleMove[nPly][j].Location_Current.y=PossibleMove[nPly][i].Location_Current.y;
				PossibleMove[nPly][j].nCount=PossibleMove[nPly][i].nCount;
				PossibleMove[nPly][j].nPly=PossibleMove[nPly][i].nPly;
				PossibleMove[nPly][j].nSide_=PossibleMove[nPly][i].nSide_;
				PossibleMove[nPly][j].pNext=NULL;
				memcpy_s(PossibleMove[nPly][j].nSpace_After,12*4,PossibleMove[nPly][i].nSpace_After,12*4);
				memcpy_s(PossibleMove[nPly][j].nSpace_Before,12*4,PossibleMove[nPly][i].nSpace_Before,12*4);
				memcpy_s(PossibleMove[nPly][j].DirectionToMove,12*4,PossibleMove[nPly][i].DirectionToMove,12*4);
				if(i!=j)
				{
					PossibleMove[nPly][i].Depth=0;
					PossibleMove[nPly][i].Location_Current.x=0;
					PossibleMove[nPly][i].Location_Current.y=0;
					PossibleMove[nPly][i].nCount=0;
					PossibleMove[nPly][i].nPly=0;
					PossibleMove[nPly][i].nSide_=0;
					PossibleMove[nPly][i].pNext=NULL;
					memset(PossibleMove[nPly][i].nSpace_After,0,12*4);
					memset(PossibleMove[nPly][i].nSpace_Before,0,12*4);
					memset(PossibleMove[nPly][i].DirectionToMove,0,12*4);
				}
				j++;
				SumToGo=j;
			}
		}
	}	
	nTypeToGo=j=0;
	return SumToGo;
}
void CMoveGenerator::MakePossibleMove(int x,int y,int nCount,int Value,int nPly)
{

	if(Value==WHITE_SOLDIER||Value==BLACK_SOLDIER)
	{
		if(Value==BLACK_SOLDIER)
		{
			if((x>0&&y>0)&&(Board_MG[x-1][y-1]==EMPTY))//左上角有空，可以走,注意不能往回走，此处应该对应最终走法来确认上次方向
			{											
				//记下走的信息

				Add_Poly(nCount,Value,0,LEFT_UP,0,nPly);

			}
			if((x>0&&y<7)&&(Board_MG[x-1][y+1]==EMPTY))//右上角有空，可以走,注意不能往回走，此处应该对应最终走法来确认上次方向
			{
				//记下走的信息

				Add_Poly(nCount,Value,0,RIGHT_UP,0,nPly);				
			}
		}
		else if(Value==WHITE_SOLDIER)
		{
			if((x<7&&y>0)&&(Board_MG[x+1][y-1]==EMPTY))//左下角有空，可以走,注意不能往回走，此处应该对应最终走法来确认上次方向
			{
			//记下走的信息
	
				Add_Poly(nCount,Value,0,LEFT_DOWN,0,nPly);			
			}
			if((x<7&&y<7)&&(Board_MG[x+1][y+1]==EMPTY))//右下角有空，可以走,注意不能往回走，此处应该对应最终走法来确认上次方向
			{
				//记下走的信息

				Add_Poly(nCount,Value,0,RIGHT_DOWN,0,nPly);		
			}
		}
	}
	else if(Value==WHITE_KING||Value==BLACK_KING)//如果是王，稍后再说
	{
		int nSpace_Before=0;
		if((nSpace_Before=BeforeKingSpaceCount(Board_MG,LEFT_UP,x,y))>0)
		{
			for(int nStart=1;nStart<=nSpace_Before;nStart++)
			{
				Add_Poly(nCount,Value,0,LEFT_UP,nStart,nPly);
			}
			nSpace_Before=0;				
		}
		if((nSpace_Before=BeforeKingSpaceCount(Board_MG,RIGHT_UP,x,y))>0)
		{
			for(int nStart=1;nStart<=nSpace_Before;nStart++)
			{
				Add_Poly(nCount,Value,0,RIGHT_UP,nStart,nPly);
			}
			nSpace_Before=0;					
		}
		if((nSpace_Before=BeforeKingSpaceCount(Board_MG,LEFT_DOWN,x,y))>0)
		{
			for(int nStart=1;nStart<=nSpace_Before;nStart++)
			{
				Add_Poly(nCount,Value,0,LEFT_DOWN,nStart,nPly);
			}	
			nSpace_Before=0;			
		}
		if((nSpace_Before=BeforeKingSpaceCount(Board_MG,RIGHT_DOWN,x,y))>0)
		{
			for(int nStart=1;nStart<=nSpace_Before;nStart++)
			{
				Add_Poly(nCount,Value,0,RIGHT_DOWN,nStart,nPly);
			}
			nSpace_Before=0;			
		}
	}	
}
//走法树建立，判断所有的杀棋可能性，并存储相应的数据以便后续解析
bool CMoveGenerator::MakePossibleKill(int x,int y,int nSide,int nCount,int Depth,int Direction_From,int nPly)
{
	int Direction_To=0;
	if(nSide==WHITE_SOLDIER||nSide==BLACK_SOLDIER)//如果是兵
	{
		if((x>1&&y>1)&&(Board_MG[x-1][y-1]==-nSide||Board_MG[x-1][y-1]==-nSide*2)&&(Board_MG[x-2][y-2]==EMPTY)&&Direction_From!=RIGHT_DOWN)//如果可以左上吃子
		{	
			Kill_Method++;
			Direction_To=LEFT_UP;
			Kill_Chain_Add(nCount,nSide,++Depth,LEFT_UP,0,0,x,y,nPly);
			//吃子
			int Value=Move_Kill(LEFT_UP,nSide,x,y);
			//递归
			Kill_Method+=MakePossibleKill(x,y,nSide,nCount,Depth,Direction_To,nPly);	
			//还原
			Move_Re_Kill(LEFT_UP,nSide,x,y,Value);
			Depth--;
		}
		if((x>1&&y<6)&&(Board_MG[x-1][y+1]==-nSide||Board_MG[x-1][y+1]==-nSide*2)&&(Board_MG[x-2][y+2]==EMPTY)&&Direction_From!=LEFT_DOWN)//如果可以右上吃子
		{	
			Kill_Method++;
			Direction_To=RIGHT_UP;
			Kill_Chain_Add(nCount,nSide,++Depth,RIGHT_UP,0,0,x,y,nPly);
			//吃子
			int Value=Move_Kill(RIGHT_UP,nSide,x,y);			
			//递归
			Kill_Method+=MakePossibleKill(x,y,nSide,nCount,Depth,Direction_To,nPly);	
			//还原
			Move_Re_Kill(RIGHT_UP,nSide,x,y,Value);
			Depth--;
		}
		if((x<6&&y>1)&&(Board_MG[x+1][y-1]==-nSide||Board_MG[x+1][y-1]==-nSide*2)&&(Board_MG[x+2][y-2]==EMPTY)&&Direction_From!=RIGHT_UP)//如果可以左下吃子
		{
			Kill_Method++;
			Direction_To=LEFT_DOWN;
			Kill_Chain_Add(nCount,nSide,++Depth,LEFT_DOWN,0,0,x,y,nPly);
			//吃子
			int Value=Move_Kill(LEFT_DOWN,nSide,x,y);		
			//递归
			Kill_Method+=MakePossibleKill(x,y,nSide,nCount,Depth,Direction_To,nPly);	
			//还原
			Move_Re_Kill(LEFT_DOWN,nSide,x,y,Value);
			Depth--;
		}
		if((x<6&&y<6)&&(Board_MG[x+1][y+1]==-nSide||Board_MG[x+1][y+1]==-nSide*2)&&(Board_MG[x+2][y+2]==EMPTY)&&Direction_From!=LEFT_UP)//如果可以右下吃子
		{
			Kill_Method++;
			Direction_To=RIGHT_DOWN;
			Kill_Chain_Add(nCount,nSide,++Depth,RIGHT_DOWN,0,0,x,y,nPly);
			//吃子
			int Value=Move_Kill(RIGHT_DOWN,nSide,x,y);			
			//递归
			Kill_Method+=MakePossibleKill(x,y,nSide,nCount,Depth,Direction_To,nPly);	
			//还原
			Move_Re_Kill(RIGHT_DOWN,nSide,x,y,Value);
			Depth--;
		}
	}
	else if(nSide==WHITE_KING||nSide==BLACK_KING)//如果是王
	{
		int nSpace_Before;
		int nSpace_After;
		if((x>1&&y>1)&&((nSpace_Before=BeforeKingSpaceCount(Board_MG,LEFT_UP,x,y))>=0)&&((nSpace_After=AfterKingSpaceCount(Board_MG,LEFT_UP,x,y))>0)&&Direction_From!=RIGHT_DOWN)//如果可以左上吃子
		{	
			Kill_Method++;
			Direction_To=LEFT_UP;
			Depth++;
			//吃子
			
			for(int nStart=1;nStart<=nSpace_After;nStart++)
			{	
				Kill_Chain_Add(nCount,nSide,Depth,LEFT_UP,nSpace_Before,nStart,x,y,nPly);
				int Value=King_Kill_Poly(LEFT_UP,nSide,x,y,nSpace_Before,nStart);
				//递归
				Kill_Method+=MakePossibleKill(x,y,nSide,nCount,Depth,Direction_To,nPly);			
				//还原
				King_Kill_Re_Poly(LEFT_UP,nSide,x,y,nSpace_Before,nStart,Value);
			}
			Depth--;
		}
		if((x>1&&y<6)&&((nSpace_Before=BeforeKingSpaceCount(Board_MG,RIGHT_UP,x,y))>=0)&&((nSpace_After=AfterKingSpaceCount(Board_MG,RIGHT_UP,x,y))>0)&&Direction_From!=LEFT_DOWN)//如果可以右上吃子
		{		
			Kill_Method++;
			Direction_To=RIGHT_UP;
			Depth++;
			//吃子
			
			for(int nStart=1;nStart<=nSpace_After;nStart++)
			{	
				Kill_Chain_Add(nCount,nSide,Depth,RIGHT_UP,nSpace_Before,nStart,x,y,nPly);
				int Value=King_Kill_Poly(RIGHT_UP,nSide,x,y,nSpace_Before,nStart);		
				//递归
				Kill_Method+=MakePossibleKill(x,y,nSide,nCount,Depth,Direction_To,nPly);			
				//还原
				King_Kill_Re_Poly(RIGHT_UP,nSide,x,y,nSpace_Before,nStart,Value);
			}
			Depth--;
		}
		if((x<6&&y>1)&&((nSpace_Before=BeforeKingSpaceCount(Board_MG,LEFT_DOWN,x,y))>=0)&&((nSpace_After=AfterKingSpaceCount(Board_MG,LEFT_DOWN,x,y))>0)&&Direction_From!=RIGHT_UP)//如果可以左下吃子
		{		
			Kill_Method++;
			Direction_To=LEFT_DOWN;
			Depth++;
			//吃子
			
			for(int nStart=1;nStart<=nSpace_After;nStart++)
			{
				Kill_Chain_Add(nCount,nSide,Depth,LEFT_DOWN,nSpace_Before,nStart,x,y,nPly);
				int Value=King_Kill_Poly(LEFT_DOWN,nSide,x,y,nSpace_Before,nStart);		
				//递归
				Kill_Method+=MakePossibleKill(x,y,nSide,nCount,Depth,Direction_To,nPly);			
				//还原
				King_Kill_Re_Poly(LEFT_DOWN,nSide,x,y,nSpace_Before,nStart,Value);
			}
			Depth--;
		}
		if((x<6&&y<6)&&((nSpace_Before=BeforeKingSpaceCount(Board_MG,RIGHT_DOWN,x,y))>=0)&&((nSpace_After=AfterKingSpaceCount(Board_MG,RIGHT_DOWN,x,y))>0)&&Direction_From!=LEFT_UP)//如果可以右下吃子
		{
			Kill_Method++;
			Direction_To=RIGHT_DOWN;
			Depth++;
			//吃子
			
			for(int nStart=1;nStart<=nSpace_After;nStart++)
			{			
				Kill_Chain_Add(nCount,nSide,Depth,RIGHT_DOWN,nSpace_Before,nStart,x,y,nPly);
				int Value=King_Kill_Poly(RIGHT_DOWN,nSide,x,y,nSpace_Before,nStart);
				//递归
				Kill_Method+=MakePossibleKill(x,y,nSide,nCount,Depth,Direction_To,nPly);			
				//还原
				King_Kill_Re_Poly(RIGHT_DOWN,nSide,x,y,nSpace_Before,nStart,Value);
			}
			Depth--;
		}
	}
	return Kill_Method++;
}
//走动布局
void CMoveGenerator::Move_Poly(int Direction,int nSide,int &x,int &y)
{
	if(nSide==WHITE_SOLDIER||nSide==BLACK_SOLDIER)//如果是兵
	{
		switch (Direction)
		{
		case LEFT_UP:
			{
				Board_MG[x][y]=EMPTY;
				Board_MG[x-1][y-1]=nSide;
				x-=1;
				y-=1;
				break;
			}
		case RIGHT_UP:
			{
				Board_MG[x][y]=EMPTY;
				Board_MG[x-1][y+1]=nSide;	
				x-=1;
				y+=1;
				break;
			}
		case LEFT_DOWN:
			{
				Board_MG[x][y]=EMPTY;
				Board_MG[x+1][y-1]=nSide;
				x+=1;
				y-=1;
				break;
			}
		case RIGHT_DOWN:
			{
				Board_MG[x][y]=EMPTY;
				Board_MG[x+1][y+1]=nSide;
				x+=1;
				y+=1;
				break;
			}
		}
	}
}
//还原走动布局
void CMoveGenerator::Move_Re_Poly(int Direction,int nSide,int &x,int &y)
{
	if(nSide==WHITE_SOLDIER||nSide==BLACK_SOLDIER)//如果是兵
	{
		switch (Direction)
		{
		case LEFT_UP://左上走右下回
			{
				Board_MG[x][y]=EMPTY;
				Board_MG[x+1][y+1]=nSide;
				x+=1;
				y+=1;
				break;
			}
		case RIGHT_UP://右上走左下回
			{
				Board_MG[x][y]=EMPTY;
				Board_MG[x+1][y-1]=nSide;	
				x+=1;
				y-=1;
				break;
			}
		case LEFT_DOWN://左下走右上回
			{
				Board_MG[x][y]=EMPTY;
				Board_MG[x-1][y+1]=nSide;
				x-=1;
				y+=1;
				break;
			}
		case RIGHT_DOWN://右下走左上回
			{
				Board_MG[x][y]=EMPTY;
				Board_MG[x-1][y-1]=nSide;
				x-=1;
				y-=1;
				break;
			}
		}
	}
}
//王的走动布局
void CMoveGenerator::King_Move_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before)
{
	switch (Direction)
	{
	case LEFT_UP:
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x-nSpace_Before][y-nSpace_Before]=nSide;
			x-=nSpace_Before;
			y-=nSpace_Before;
			break;
		}
	case RIGHT_UP:
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x-nSpace_Before][y+nSpace_Before]=nSide;
			x-=nSpace_Before;
			y+=nSpace_Before;
			break;
		}
	case LEFT_DOWN:
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x+nSpace_Before][y-nSpace_Before]=nSide;
			x+=nSpace_Before;
			y-=nSpace_Before;
			break;
		}
	case RIGHT_DOWN:
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x+nSpace_Before][y+nSpace_Before]=nSide;
			x+=nSpace_Before;
			y+=nSpace_Before;
			break;
		}
	}

}
//王的走动布局还原
void CMoveGenerator::King_Move_Re_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before)
{
	switch (Direction)
	{
	case LEFT_UP:
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x+nSpace_Before][y+nSpace_Before]=nSide;
			x+=nSpace_Before;
			y+=nSpace_Before;
			break;
		}
	case RIGHT_UP:
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x+nSpace_Before][y-nSpace_Before]=nSide;
			x+=nSpace_Before;
			y-=nSpace_Before;
			break;
		}
	case LEFT_DOWN:
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x-nSpace_Before][y+nSpace_Before]=nSide;
			x-=nSpace_Before;
			y+=nSpace_Before;
			break;
		}
	case RIGHT_DOWN:
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x-nSpace_Before][y-nSpace_Before]=nSide;
			x-=nSpace_Before;
			y-=nSpace_Before;
			break;
		}
	}

}
//杀棋布局
int CMoveGenerator::Move_Kill(int Direction,int nSide,int &x,int &y)
{
	int Value;
	switch (Direction)
	{
	case LEFT_UP:
		{
			Board_MG[x][y]=0;			
			Board_MG[x-2][y-2]=nSide;
			Value=Board_MG[x-1][y-1];
			Board_MG[x-1][y-1]=0;
			x-=2;
			y-=2;
			break;		
		}
	case RIGHT_UP:
		{
			Board_MG[x][y]=0;			
			Board_MG[x-2][y+2]=nSide;	
			Value=Board_MG[x-1][y+1];
			Board_MG[x-1][y+1]=0;
			x-=2;
			y+=2;
			break;
		}
	case LEFT_DOWN:
		{
			Board_MG[x][y]=0;
			Board_MG[x+2][y-2]=nSide;
			Value=Board_MG[x+1][y-1];
			Board_MG[x+1][y-1]=0;
			x+=2;
			y-=2;
			break;
		}
	case RIGHT_DOWN:
		{
			Board_MG[x][y]=0;
			Board_MG[x+2][y+2]=nSide;
			Value=Board_MG[x+1][y+1];
			Board_MG[x+1][y+1]=0;
			x+=2;
			y+=2;
			break;
		}
	}	
	return Value;
}
//还原杀棋布局
void CMoveGenerator::Move_Re_Kill(int Direction,int nSide,int &x,int &y,int Value)
{

	switch (Direction)
	{
	case LEFT_UP://左上走右下回
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x+1][y+1]=Value;
			Board_MG[x+2][y+2]=nSide;
			x+=2;
			y+=2;
			break;
		}
	case RIGHT_UP://右上走左下回
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x+1][y-1]=Value;
			Board_MG[x+2][y-2]=nSide;
			x+=2;
			y-=2;
			break;
		}
	case LEFT_DOWN://左下走右上回
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x-1][y+1]=Value;
			Board_MG[x-2][y+2]=nSide;
			x-=2;
			y+=2;
			break;
		}
	case RIGHT_DOWN://右下走左上回
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x-1][y-1]=Value;
			Board_MG[x-2][y-2]=nSide;
			x-=2;
			y-=2;
			break;
		}
	}
	
}
//王的杀棋布局，返回杀掉的棋的价值
int CMoveGenerator::King_Kill_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int nSpace_After)
{
	switch (Direction)
	{
	case LEFT_UP:
		{
			Board_MG[x][y]=0;			
			Board_MG[x-nSpace_After-1-nSpace_Before][y-nSpace_After-1-nSpace_Before]=nSide;
			int Value=Board_MG[x-1-nSpace_Before][y-1-nSpace_Before];
			Board_MG[x-1-nSpace_Before][y-1-nSpace_Before]=0;
			x=x-nSpace_After-1-nSpace_Before;
			y=y-nSpace_After-1-nSpace_Before;
			return Value;		
		}
	case RIGHT_UP:
		{
			Board_MG[x][y]=0;			
			Board_MG[x-nSpace_After-1-nSpace_Before][y+nSpace_After+1+nSpace_Before]=nSide;	
			int Value=Board_MG[x-1-nSpace_Before][y+1+nSpace_Before];
			Board_MG[x-1-nSpace_Before][y+1+nSpace_Before]=0;
			x=x-nSpace_After-1-nSpace_Before;
			y=y+nSpace_After+1+nSpace_Before;
			return Value;	
		}
	case LEFT_DOWN:
		{
			Board_MG[x][y]=0;
			Board_MG[x+nSpace_After+1+nSpace_Before][y-nSpace_After-1-nSpace_Before]=nSide;
			int Value=Board_MG[x+1+nSpace_Before][y-1-nSpace_Before];
			Board_MG[x+1+nSpace_Before][y-1-nSpace_Before]=0;
			x=x+nSpace_After+1+nSpace_Before;
			y=y-nSpace_After-1-nSpace_Before;
			return Value;
		}
	case RIGHT_DOWN:
		{
			Board_MG[x][y]=0;
			Board_MG[x+nSpace_After+1+nSpace_Before][y+nSpace_After+1+nSpace_Before]=nSide;
			int Value=Board_MG[x+1+nSpace_Before][y+1+nSpace_Before];
			Board_MG[x+1+nSpace_Before][y+1+nSpace_Before]=0;
			x=x+nSpace_After+1+nSpace_Before;
			y=y+nSpace_After+1+nSpace_Before;
			return Value;
		}
	}
	return false;
}
//王的杀棋布局还原
void CMoveGenerator::King_Kill_Re_Poly(int Direction,int nSide,int &x,int &y,int nSpace_Before,int nSpace_After,int Value)
{
	switch (Direction)
	{
	case LEFT_UP://左上来右下回
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x+nSpace_After][y+nSpace_After]=Value;
			Board_MG[x+1+nSpace_Before+nSpace_After][y+1+nSpace_Before+nSpace_After]=nSide;
			x=x+1+nSpace_Before+nSpace_After;
			y=y+1+nSpace_Before+nSpace_After;
			break;
		}
	case RIGHT_UP://右上来左下回
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x+nSpace_After][y-nSpace_After]=Value;
			Board_MG[x+1+nSpace_Before+nSpace_After][y-1-nSpace_Before-nSpace_After]=nSide;
			x=x+1+nSpace_Before+nSpace_After;
			y=y-1-nSpace_Before-nSpace_After;
			break;
		}
	case LEFT_DOWN://左下来右上回
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x-nSpace_After][y+nSpace_After]=Value;
			Board_MG[x-1-nSpace_Before-nSpace_After][y+1+nSpace_Before+nSpace_After]=nSide;
			x=x-1-nSpace_Before-nSpace_After;
			y=y+1+nSpace_Before+nSpace_After;
			break;
		}
	case RIGHT_DOWN://右下来左上回
		{
			Board_MG[x][y]=EMPTY;
			Board_MG[x-nSpace_After][y-nSpace_After]=Value;
			Board_MG[x-1-nSpace_Before-nSpace_After][y-1-nSpace_Before-nSpace_After]=nSide;
			x=x-1-nSpace_Before-nSpace_After;
			y=y-1-nSpace_Before-nSpace_After;
			break;
		}
	}

}
//添加布局走法
void CMoveGenerator::Add_Poly(int nCount,int nSide,int Depth,int Direction_to,int nSpace_Before,int nPly)
{	
		PossibleMove[nPly][nTypeToGo].Depth=Depth;
		PossibleMove[nPly][nTypeToGo].DirectionToMove[0]=Direction_to;
		PossibleMove[nPly][nTypeToGo].Location_Current=Local_Current[nCount];
		PossibleMove[nPly][nTypeToGo].nCount=nCount;
		PossibleMove[nPly][nTypeToGo].nSide_=nSide;
		PossibleMove[nPly][nTypeToGo].nSpace_After[0]=0;
		PossibleMove[nPly][nTypeToGo].nSpace_Before[0]=nSpace_Before;
		PossibleMove[nPly][nTypeToGo].pNext=NULL;
		PossibleMove[nPly][nTypeToGo].nPly=nPly;
		nTypeToGo++;
}

//杀棋信息链表的添加
void CMoveGenerator::Kill_Chain_Add(int nCount,int nSide,int Depth,int Direction_to,int nSpace_Before,int nSpace_After,int x,int y,int nPly)
{

	CNodeChessInfo *ChessNode=new CNodeChessInfo;
	ChessNode->Location_Current.x=x;
	ChessNode->Location_Current.y=y;
	ChessNode->nSide_=nSide;//势力范围
	ChessNode->DirectionToMove[0]=Direction_to;//将要行走的方向
	ChessNode->Depth=Depth;//行走深度
	ChessNode->nCount=nCount;//第n个棋子
	ChessNode->nPly=nPly;
	//using by chess of king
	ChessNode->nSpace_Before[0]=nSpace_Before;
	ChessNode->nSpace_After[0]=nSpace_After;
	if(Head==NULL)
	{
		Head=ChessNode;
		
	}else
	{
		Link->pNext=ChessNode;
	}
	Link=ChessNode;
	Link->pNext=NULL;
}
//清空链表
void CMoveGenerator::Chain_Clear(void)
{
	CNodeChessInfo *Temp=NULL;
	while(Head!=NULL)
	{
		Temp=Head;
		Head=Head->pNext;
		delete Temp;
	}
	Head=NULL;
	Link=NULL;
}

bool CMoveGenerator::AnalyzeKillInfo(int nCount,int (*Board_MG)[8],int nSide,int nPly)
{
	CNodeChessInfo *BUFF=Head;

	int nRoute=0;//保存最大深度杀棋路径的数量
	//保存最大深度，也就是杀的最多的走法
	CNodeChessInfo *Area[100];
	int i=0;int j=0;
	int MaxSub[12];
	memset(MaxSub,0,12*4);
	for(i=0;i<100;i++)
	{
		Area[i]=NULL;
	}

	//搜寻最大深度DepthMax
	DepthMax[nCount]=BUFF->Depth;
	while(BUFF!=NULL)
	{
		if(BUFF->Depth>DepthMax[nCount])
		{
			DepthMax[nCount]=BUFF->Depth;
		}
		BUFF=BUFF->pNext;
	}
	BUFF=Head;
	i=j=0;
	//提取最大深度节点的id
	while(BUFF!=NULL)
	{
	//	Depth_Buff[j]=BUFF->Depth;
		Area[j]=BUFF;
		if(DepthMax[nCount]==BUFF->Depth)//当找到最大深度后保存节点id,将id存储到ID_BUFF[]中;
		{
			MaxSub[i++]=j;//储存杀棋最大节点在链表中的位置

		}
		BUFF=BUFF->pNext;
		j++;
	}
	nRoute=i;
//	nTypeToGo=nRoute-1;
	i=j=0;
	int k=0;

	while(i!=nRoute)
	{
		while(true)
		{		
			if(Area[MaxSub[i]-k]->Depth==DepthMax[nCount]-j)
			{
					PossibleMove[nPly][nTypeToGo].Location_Current.x=Area[MaxSub[i]-k]->Location_Current.x;
					PossibleMove[nPly][nTypeToGo].Location_Current.y=Area[MaxSub[i]-k]->Location_Current.y;			
					PossibleMove[nPly][nTypeToGo].DirectionToMove[DepthMax[nCount]-j-1]=Area[MaxSub[i]-k]->DirectionToMove[0];
					PossibleMove[nPly][nTypeToGo].nSpace_After[DepthMax[nCount]-j-1]=Area[MaxSub[i]-k]->nSpace_After[0];
					PossibleMove[nPly][nTypeToGo].nSpace_Before[DepthMax[nCount]-j-1]=Area[MaxSub[i]-k]->nSpace_Before[0];
				if(Area[MaxSub[i]-k]->Depth==DepthMax[nCount])
				{			
					PossibleMove[nPly][nTypeToGo].Depth=DepthMax[nCount];
					PossibleMove[nPly][nTypeToGo].nPly=nPly;
					PossibleMove[nPly][nTypeToGo].nSide_=Area[MaxSub[i]-k]->nSide_;
					PossibleMove[nPly][nTypeToGo].pNext=NULL;
					
				}
									
				if(DepthMax[nCount]-j-1==0)
				{
					break;
				}
				j++;
			}
			k++;
		}	
		nTypeToGo++;
		i++;	
		j=k=0;
	}
	//nTypeToGo+=i;
	for(i=0;i<100;i++)
	{
		Area[i]=NULL;
	}
	BUFF=NULL;
	Chain_Clear();
	return true;
	
}

void CMoveGenerator::FUNC_RESET(int nPly)
{
	for(int i=0;i<100;i++)
	{
		PossibleMove[nPly][i].Depth=0;
		PossibleMove[nPly][i].nCount=0;
		PossibleMove[nPly][i].nPly=0;
		PossibleMove[nPly][i].nSide_=0;
		PossibleMove[nPly][i].Location_Current.x=0;
		PossibleMove[nPly][i].Location_Current.y=0;
		PossibleMove[nPly][i].pNext=NULL;
		memset(PossibleMove[nPly][i].DirectionToMove,0,12*4);
		memset(PossibleMove[nPly][i].nSpace_Before,0,12*4);
		memset(PossibleMove[nPly][i].nSpace_After,0,12*4);
	}
}