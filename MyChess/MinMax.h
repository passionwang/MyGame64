#pragma once
#include "SearchEngine.h"
class CMinMax:public CSearchEngine
{
public:
	CMinMax(void);
	virtual ~CMinMax(void);
//	virtual void SearchAGoodMove(int Board_Copy[8][8]);
//protected:
//	int MinMax(int Depth);
};

