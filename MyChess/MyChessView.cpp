// MyChessView.cpp : implementation of the CMyChessView class
//
#include "stdafx.h"
#include "MyChess.h"
#include "MyChessDoc.h"
#include "MyChessView.h"
#include "MoveGenerator.h"
#include "Public.h"
#include "PublicDefine.h"
#include "Evalute.h"
#include "SearchEngine.h"
#include "AlphaBeta.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CMyChessView
IMPLEMENT_DYNCREATE(CMyChessView, CView)
BEGIN_MESSAGE_MAP(CMyChessView, CView)
	//{{AFX_MSG_MAP(CMyChessView)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands

	ON_COMMAND(ID_32776, OnFileReset)
    ON_COMMAND(ID_32773, OnFileReset)

	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

int iBoard[8][8]={	{ 0,-1, 0,-1, 0,-1, 0,-1},
					{-1, 0,-1, 0,-1, 0,-1, 0},
					{ 0, -1, 0, -1, 0,-1, 0,-1},
					{ 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0},
					{ 1, 0, 1, 0, 1, 0, 1, 0},
					{ 0, 1, 0, 1, 0, 1, 0, 1},
					{ 1, 0, 1, 0, 1, 0, 1, 0}};

/////////////////////////////////////////////////////////////////////////////
// CMyChessView construction/destruction
CMyChessView::CMyChessView()
{
	// TODO: add construction code here
	int (*p)[8];
 	p = (int (*)[8])malloc(8*8*4);
	memcpy_s(p,8*8*4,iBoard,8*8*4);
	Reset::Board_Reset.push_front(p);
	
}
CMyChessView::~CMyChessView()
{
}
BOOL CMyChessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}
int UP=1;

const int iBL=50;//棋盘左侧边距
const int iBT=50;//棋盘上侧边距
const int iBS=50;//棋盘棋位单位

//int iBoard[8][8]={{ 0,-1, 0,-1, 0,-1, 0,-1},
//					{-1, 0,-1, 0,-1, 0,-1, 0},
//					{ 0,-1, 0,-1, 0,-1, 0,-1},
//					{ 0, 0, 0, 0, 0, 0, 0, 0},
//					{ 0, 0, 0, 0, 0, 0, 0, 0},
//					{ 1, 0, 1, 0, 1, 0, 1, 0},
//					{ 0, 1, 0, 1, 0, 1, 0, 1},
//					{ 1, 0, 1, 0, 1, 0, 1, 0}};




int iAIColor=-1; //引擎棋子颜色
int iGetChess=0; //对手拾取棋子
int iM_1,iN_1,iM_2,iN_2;  //拾棋与落棋座标（数组下标）
int iM,iN;
int turn=1; 

int UP_COUNT=0;

/////////////////////////////////////////////////////////////////////////////
 //CMyChessView drawing
void DrawGo(CDC* pDC)
{
	CBrush jBrush;
	jBrush.CreateSolidBrush(RGB(0,255,0));  //绿
	pDC->SelectObject(&jBrush);
	pDC->Rectangle(iBL+9*iBS,iBT+iBS-25,iBL+10*iBS,iBT+8*iBS-25);
	pDC->SelectStockObject(BLACK_BRUSH);
	jBrush.DeleteObject();
	jBrush.CreateSolidBrush(RGB(0,0,255));  //绿
	pDC->SelectObject(&jBrush);
	pDC->Rectangle(iBL+10*iBS,iBT+iBS-25,iBL+11*iBS,iBT+8*iBS-25);
	pDC->SelectStockObject(BLACK_BRUSH);
	jBrush.DeleteObject();
}
void DrawBoard(CDC* pDC)
{
	int i,j;
	CBrush jBrush;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			if((i+j)%2==0)//浅灰色棋位
				jBrush.CreateSolidBrush(RGB(120,120,120));
			else//深灰色棋位
				jBrush.CreateSolidBrush(RGB(80,80,80));
			pDC->SelectObject(&jBrush);
			pDC->Rectangle(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
			pDC->SelectStockObject(BLACK_BRUSH);
			jBrush.DeleteObject();
		}
}
void DrawChess(CDC* pDC)
{
	int i,j;
	CBrush jBrush;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			if(iBoard[i][j]==-1)//白棋
			{
				jBrush.CreateSolidBrush(RGB(220,220,220));
				pDC->SelectObject(&jBrush);
				pDC->Ellipse(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
				pDC->SelectStockObject(BLACK_BRUSH);
				jBrush.DeleteObject();
			}
			if(iBoard[i][j]==1)//黑棋
			{
				jBrush.CreateSolidBrush(RGB(0,0,0));
				pDC->SelectObject(&jBrush);
				pDC->Ellipse(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
				pDC->SelectStockObject(BLACK_BRUSH);
				jBrush.DeleteObject();
			}
			if(iBoard[i][j]==-2)//白王
			{
				jBrush.CreateSolidBrush(RGB(220,220,220));
				pDC->SelectObject(&jBrush);
				pDC->Rectangle(iBT+j*iBS+15,iBL+i*iBS+15,iBT+(j+1)*iBS-15,iBL+(i+1)*iBS-15);
				pDC->SelectStockObject(BLACK_BRUSH);
				jBrush.DeleteObject();
			}
			if(iBoard[i][j]==2)//黑王
			{
				jBrush.CreateSolidBrush(RGB(0,0,0));
				pDC->SelectObject(&jBrush);
				pDC->Rectangle(iBT+j*iBS+15,iBL+i*iBS+15,iBT+(j+1)*iBS-15,iBL+(i+1)*iBS-15);
				pDC->SelectStockObject(BLACK_BRUSH);
				jBrush.DeleteObject();
			}
			if(iBoard[i][j]==5)//终点
			{
				jBrush.CreateSolidBrush(RGB(85,220,21));
				pDC->SelectObject(&jBrush);
				pDC->Ellipse(iBT+j*iBS+12,iBL+i*iBS+12,iBT+(j+1)*iBS-10,iBL+(i+1)*iBS-12);
				pDC->SelectStockObject(BLACK_BRUSH);
				jBrush.DeleteObject();
			}
			
			if(iBoard[i][j]==-5)//过程
			{
				jBrush.CreateSolidBrush(RGB(85,220,100));
				pDC->SelectObject(&jBrush);
				pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
				pDC->SelectStockObject(BLACK_BRUSH);
				jBrush.DeleteObject();
			}
			if(1==UP)
			{
				if(iBoard[i][j]==4)//过程
				{
					jBrush.CreateSolidBrush(RGB(220,220,220));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
				if(iBoard[i][j]==-4)//过程
				{
					jBrush.CreateSolidBrush(RGB(220,220,220));
					pDC->SelectObject(&jBrush);
					pDC->Rectangle(iBT+j*iBS+15,iBL+i*iBS+15,iBT+(j+1)*iBS-15,iBL+(i+1)*iBS-15);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
				if(iBoard[i][j]==6)//过程
				{
					jBrush.CreateSolidBrush(RGB(0,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
				if(iBoard[i][j]==-6)//过程
				{
					jBrush.CreateSolidBrush(RGB(0,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Rectangle(iBT+j*iBS+15,iBL+i*iBS+15,iBT+(j+1)*iBS-15,iBL+(i+1)*iBS-15);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
			}
			else
			{
				if(iBoard[i][j]==6)//过程
				{
					jBrush.CreateSolidBrush(RGB(220,220,220));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
				if(iBoard[i][j]==-6)//过程
				{
					jBrush.CreateSolidBrush(RGB(220,220,220));
					pDC->SelectObject(&jBrush);
					pDC->Rectangle(iBT+j*iBS+15,iBL+i*iBS+15,iBT+(j+1)*iBS-15,iBL+(i+1)*iBS-15);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
				if(iBoard[i][j]==4)//过程
				{
					jBrush.CreateSolidBrush(RGB(0,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS,iBL+i*iBS,iBT+(j+1)*iBS,iBL+(i+1)*iBS);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
				if(iBoard[i][j]==-4)//过程
				{
					jBrush.CreateSolidBrush(RGB(0,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Rectangle(iBT+j*iBS+15,iBL+i*iBS+15,iBT+(j+1)*iBS-15,iBL+(i+1)*iBS-15);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
					jBrush.CreateSolidBrush(RGB(255,0,0));
					pDC->SelectObject(&jBrush);
					pDC->Ellipse(iBT+j*iBS+17,iBL+i*iBS+17,iBT+(j+1)*iBS-17,iBL+(i+1)*iBS-17);
					pDC->SelectStockObject(BLACK_BRUSH);
					jBrush.DeleteObject();
				}
			}
		
		}
}
void CMyChessView::OnDraw(CDC* pDC)
{
	CMyChessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	DrawBoard(pDC);
	DrawChess(pDC);
	DrawGo(pDC);
	/*int (*p)[8];
 	p = (int (*)[8])malloc(8*8*4);
	memcpy_s(p,8*8*4,iBoard,8*8*4);
	Reset::Board_Reset.push_front(p);*/
}
/////////////////////////////////////////////////////////////////////////////
// CMyChessView printing
BOOL CMyChessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}
void CMyChessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}
void CMyChessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}
/////////////////////////////////////////////////////////////////////////////
// CMyChessView diagnostics
#ifdef _DEBUG
void CMyChessView::AssertValid() const
{
	CView::AssertValid();
}

void CMyChessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyChessDoc* CMyChessView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyChessDoc)));
	return (CMyChessDoc*)m_pDocument;
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CMyChessView message handlers
int iInArea(int x,int y,int x1,int y1,int x2,int y2)
{
	if(x>=x1 && x<=x2 && y>=y1 && y<=y2)
		return 1;
	else
		return 0;
}

void MoveJump_L(int i,int j) //向左下间隔跳
{
	iBoard[i+2][j-2]=iBoard[i][j];
	iBoard[i][j]=0;
	iBoard[i+1][j-1]=0;
}
void MoveJump_R(int i,int j) //向右下间隔跳
{
	iBoard[i+2][j+2]=iBoard[i][j];
	iBoard[i][j]=0;
	iBoard[i+1][j+1]=0;
}
void Move1_L(int i,int j)	//向左下跳
{
	iBoard[i+1][j-1]=iBoard[i][j];
	iBoard[i][j]=0;
}
void Move1_R(int i,int j)	//向右下跳
{
	iBoard[i+1][j+1]=iBoard[i][j];
	iBoard[i][j]=0;
}


void iMove()
{
	
	CSearchEngine *Moving=new CAlphaBeta;
	
	Moving->SetSearchDepth(8);
	
	Moving->SearchAGoodMove(iBoard);
	
	memcpy_s(iBoard,8*8*4,Moving->Board_Copy,8*8*4);
	delete Moving;
	int (*p)[8];
 	p = (int (*)[8])malloc(8*8*4);
	memcpy_s(p,8*8*4,iBoard,8*8*4);
	Reset::Board_Reset.push_front(p);
	
}
void Move(int iX,int iY)
{
		static int Value;
		iM=(iY-iBT)/iBS;  //将座标转换成数组下标
		iN=(iX-iBL)/iBS;
		iM_2=iM;
		iN_2=iN;
		
		
		if(iGetChess==0&&(iBoard[iM][iN]==BLACK_SOLDIER||iBoard[iM][iN]==BLACK_KING))  //拾棋
		{	
			iM_1=iM;
			iN_1=iN;
			Value=iBoard[iM][iN];
			iBoard[iM][iN]=0;
			turn=0;
			iGetChess=1; 
		}
		else if(iM_2==iM_1&&iN_2==iN_1)  //原地
		{
			iBoard[iM][iN]=Value;
			iGetChess=0;	turn=1; 		
		} 
		else if(turn==0)//落棋
		{
			
			if(iBoard[iM][iN]==EMPTY&&Value==BLACK_SOLDIER)
			{
				if(iM_2==iM_1-2&&iN_2==iN_1-2&&iBoard[iM_1-1][iN_1-1]==-1)  //左上上
				{
					iBoard[iM_1-1][iN_1-1]=0;
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();
				}
				else if(iM_2==iM_1-2&&iN_2==iN_1+2&&iBoard[iM_1-1][iN_1+1]==-1)  //右上上
				{
					iBoard[iM_1-1][iN_1+1]=0;
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();
				}
				else if(iM_2==iM_1+2&&iN_2==iN_1-2&&iBoard[iM_1+1][iN_1-1]==-1)//左下下
				{
					iBoard[iM_1+1][iN_1-1]=0;
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();

				}
				else if(iM_2==iM_1+2&&iN_2==iN_1+2&&iBoard[iM_1+1][iN_1+1]==-1)//右下下
				{
					iBoard[iM_1+1][iN_1+1]=0;
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();

				}
				else if(iM_2==iM_1-1&&iN_2==iN_1-1&&iBoard[iM_1-1][iN_1-1]==0||iM_2==iM_1-1&&iN_2==iN_1+1&&iBoard[iM_1-1][iN_1+1]==0)  //左上或右上
				{
					iBoard[iM][iN]=iGetChess;
					iGetChess=0;	turn=1; //iMove();	
				}
				int (*p)[8];
 				p = (int (*)[8])malloc(8*8*4);
				memcpy_s(p,8*8*4,iBoard,8*8*4);
				Reset::Board_Reset.push_front(p);
			}
			else if(iBoard[iM][iN]==EMPTY&&Value==BLACK_KING)
			{
				CMoveGenerator *MG=new CMoveGenerator;
				int Flag=0;
				int nSpace_Before;
				int nSpace_After;
				int length=iM_2-iM_1>0?iM_2-iM_1:iM_1-iM_2;
				if((nSpace_After=MG->AfterKingSpaceCount(iBoard,LEFT_UP,iM_1,iN_1))>0)
				{
					Flag=1;
					nSpace_Before=MG->BeforeKingSpaceCount(iBoard,LEFT_UP,iM_1,iN_1);
					iM_1-=nSpace_Before;
					iN_1-=nSpace_Before;
					iBoard[iM_1-1][iN_1-1]=0;
					iBoard[iM_2][iN_2]=BLACK_KING;
					iGetChess=0;
				}
				else if((nSpace_After=MG->AfterKingSpaceCount(iBoard,RIGHT_UP,iM_1,iN_1))>0)
				{
					Flag=1;
					nSpace_Before=MG->BeforeKingSpaceCount(iBoard,RIGHT_UP,iM_1,iN_1);
					iM_1-=nSpace_Before;
					iN_1+=nSpace_Before;
					iBoard[iM_1-1][iN_1+1]=0;
					iBoard[iM_2][iN_2]=BLACK_KING;
					iGetChess=0;
				}
				else if((nSpace_After=MG->AfterKingSpaceCount(iBoard,LEFT_DOWN,iM_1,iN_1))>0)
				{
					Flag=1;
					nSpace_Before=MG->BeforeKingSpaceCount(iBoard,LEFT_DOWN,iM_1,iN_1);
					iM_1+=nSpace_Before;
					iN_1-=nSpace_Before;
					iBoard[iM_1+1][iN_1-1]=0;
					iBoard[iM_2][iN_2]=BLACK_KING;
					iGetChess=0;
				}
				else if((nSpace_After=MG->AfterKingSpaceCount(iBoard,RIGHT_DOWN,iM_1,iN_1))>0)
				{
					Flag=1;
					nSpace_Before=MG->BeforeKingSpaceCount(iBoard,RIGHT_DOWN,iM_1,iN_1);
					iM_1+=nSpace_Before;
					iN_1+=nSpace_Before;
					iBoard[iM_1+1][iN_1+1]=0;
					iBoard[iM_2][iN_2]=BLACK_KING;
					iGetChess=0;
				}
				if(Flag!=1)
				{
					if((nSpace_Before=MG->BeforeKingSpaceCount(iBoard,LEFT_UP,iM_2,iN_2))>=length)
					{
						iBoard[iM][iN]=BLACK_KING;
						iGetChess=0;
					}
					else if((nSpace_Before=MG->BeforeKingSpaceCount(iBoard,RIGHT_UP,iM_2,iN_2))>=length)
					{
						iBoard[iM][iN]=BLACK_KING;
						iGetChess=0;
					}
					else if((nSpace_Before=MG->BeforeKingSpaceCount(iBoard,LEFT_DOWN,iM_2,iN_2))>=length)
					{
						iBoard[iM][iN]=BLACK_KING;
						iGetChess=0;
					}
					else if((nSpace_Before=MG->BeforeKingSpaceCount(iBoard,RIGHT_DOWN,iM_2,iN_2))>=length)
					{
						iBoard[iM][iN]=BLACK_KING;
						iGetChess=0;
					}
				}
			}
			
		}	
		
		for(int i=0;i<8;i++)
		{
			if(iBoard[0][i]==1)
			{
				iBoard[0][i]=2;
			}			
		}
}//鼠标范围
void CMyChessView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonUp(nFlags, point);
	int iX,iY;


	/*int Temp[8][8];

	memcpy_s(Temp,8*8*4,iBoard,8*8*4);
	Reset::Board_Reset.push_front(Temp);*/
	/*int (*p)[8];
 	p = (int (*)[8])malloc(8*8*4);
	memcpy_s(p,8*8*4,iBoard,8*8*4);
	Reset::Board_Reset.push_front(p);*/

	iX= point.x;
	iY= point.y;
	if(iInArea(iX,iY,iBL+9*iBS,iBT+iBS-25,iBL+10*iBS,iBT+8*iBS-25)) //如果机器行棋（行棋范围）
	{
		iMove();
		UP_COUNT=1;
	}
	if(iInArea(iX,iY,iBL,iBT,iBL+iBS*8,iBT+iBS*8)) //棋盘范围
	{
		Move(iX,iY);
		UP_COUNT=1;
	}
	if(iInArea(iX,iY,iBL+10*iBS,iBT+iBS,iBL+11*iBS,iBT+8*iBS)) //棋盘范围
	{
		
	}
	Invalidate();
}
void CMyChessView::xxx()
{
	Invalidate();
}




void CMyChessView::OnFileReset()
{
	CMyChessView::Reset_Board();
}
void CMyChessView::Reset_Board()
{
	if(Reset::Board_Reset.size() <= 1) return;
	list<int (*)[8]>::iterator ite= Reset::Board_Reset.begin();
	free(*ite);
	*ite = NULL;
	Reset::Board_Reset.pop_front();
	ite= Reset::Board_Reset.begin();
	memcpy_s(iBoard,8*8*4,*ite,8*8*4);
	Invalidate();
}
