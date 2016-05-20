#pragma once
#include "SearchEngine.h"
//alpha-beta剪枝思想
//1.优先深度遍历
//2.存在剪枝，即循环中途跳出，使不遍历剩余的方案
//3.alpha视角相对于我方(Max),Beta视角相对于对方(Min)
//4.对方(Min)总是试图寻找是我方利益最小化的行棋方案，我方重视试图寻找使我方利益最大化的行棋方案
//5.alpha，Beta，可以理解为视角，每当交换行棋(Depth-1),都要交换alpha，beta的值
//6.通过交换视角来实现4
//7.尤其注意，当最后一层为我方(Max)下棋估值应该为正。当为对方(Min)下棋，估值应为负！！！



class CAlphaBeta:public CSearchEngine
{
public:
	CAlphaBeta(void);
	virtual ~CAlphaBeta(void);
	virtual void SearchAGoodMove(int (*iBoard)[8]);
protected:
	int AlphaBeta(int Depth,int Alpha,int Beta);

};

