#pragma once
#include "SearchEngine.h"
class CNegaMax:public CSearchEngine
{
public:
	CNegaMax(void);
	virtual ~CNegaMax(void);
//	virtual void SearchAGoodMove(int Board_Copy[8][8]);
//protected:
//	int NegaMax(int Depth);
};

