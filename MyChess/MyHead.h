#include<stdlib.h>
//链表
typedef struct NODE
{
	int shendu;
	int tongdao;
	int kongge1;
	int kongge2;
	struct NODE *pNext;
}Node;
Node *pHead=NULL;
Node *pEnd=NULL;
//链表
typedef struct LU
{
	int hang;
	int lie;
	int wei;
	struct LU *pNext;
}Lu;
Lu *pFirst=NULL;
Lu *pLast=NULL;
void addLike(Node **pHead,Node **pEnd,int sd,int td,int kg1=0,int kg2=0);
void copy();
void iMove();
void mMoveF_y_s_s(int i,int j,int n);
void mMoveF_y_x_x(int i,int j,int n);
void mMoveF_z_s_s(int i,int j,int n) ;
void mMoveF_z_x_x(int i,int j,int n) ;
int MoNi_ShaQi(int TURN,int n,int wei);//n表示那条路
void Move(int iX,int iY)  ;
void NodeCount(int p);//value是表示当前是普通还是王
void mMove_z_x_x(int i,int j);
void mMove_z_s_s(int i,int j);
void Luo_Qi(int i,int j,int wei);
void mMove_y_s_s(int i,int j);
void mMove_y_x_x(int i,int j) ;
void iMove_z_x_x(int i,int j) ;
void iMove_z_x(int i,int j)	;
void iMove_z_s_s(int i,int j);
void iMove_z_s(int i,int j);
void iMove_y_x_x(int i,int j) ;
void iMove_y_x(int i,int j);
void FuPan();
void iMove_y_s_s(int i,int j);
int Find_Qi_Way();
void FuPan();
int YGuZhi();
void iMove_y_s(int i,int j);
int Find_Qi_Way();
void Luo_Qi(int i,int j,int wei);
void PangDuan_ShaQi(int TURN,int n,int wei);//n表示那条路
void PangDuan_ShaShangli();
void shendu(int i,int j,int value,int shu,int fangxiang,int TURN);  //n表示从哪里进来的
void XianShi_LuXian(int TURN,int wei);
int YGuZhi();
int YouShang(int x,int y);
int YouXia(int x,int y);
void YShaQi(int TURN,int FF);
int ZuoShang(int x,int y);
int ZuoXia(int x,int y);