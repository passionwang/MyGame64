#pragma once
#include "SearchEngine.h"
//alpha-beta��֦˼��
//1.������ȱ���
//2.���ڼ�֦����ѭ����;������ʹ������ʣ��ķ���
//3.alpha�ӽ�������ҷ�(Max),Beta�ӽ�����ڶԷ�(Min)
//4.�Է�(Min)������ͼѰ�����ҷ�������С�������巽�����ҷ�������ͼѰ��ʹ�ҷ�������󻯵����巽��
//5.alpha��Beta���������Ϊ�ӽǣ�ÿ����������(Depth-1),��Ҫ����alpha��beta��ֵ
//6.ͨ�������ӽ���ʵ��4
//7.����ע�⣬�����һ��Ϊ�ҷ�(Max)�����ֵӦ��Ϊ������Ϊ�Է�(Min)���壬��ֵӦΪ��������



class CAlphaBeta:public CSearchEngine
{
public:
	CAlphaBeta(void);
	virtual ~CAlphaBeta(void);
	virtual void SearchAGoodMove(int (*iBoard)[8]);
protected:
	int AlphaBeta(int Depth,int Alpha,int Beta);

};

