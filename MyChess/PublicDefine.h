#pragma once
//About Chess Info
#define EMPTY 0
#define	MINE   -1
#define ENEMY 1
#define BLACK_SOLDIER 1
#define BLACK_KING	2
#define WHITE_SOLDIER -1
#define WHITE_KING -2
#define LEFT_UP 1
#define RIGHT_UP 2
#define LEFT_DOWN -2
#define RIGHT_DOWN -1



//About Evalute Info
//ABOUT ELEMENTAL
		//������ֵ
#define SOLDIER_VAL_0								2500									//��ͨ�ڻҵļ�ֵ
#define SOLDIER_VAL_1								2000									//��ͨ�ڻҵļ�ֵ
#define SOLDIER_VAL_2								1800									//��ͨ�ڻҵļ�ֵ
#define SOLDIER_VAL_3								1400									//��ͨ�ڻҵļ�ֵ
#define SOLDIER_VAL_4								1400									//��ͨ�ڻҵļ�ֵ
#define SOLDIER_VAL_5								1600									//��ͨ�ڻҵļ�ֵ
#define SOLDIER_VAL_6								3000									//��ͨ�ڻҵļ�ֵ
		//�����ֵ
#define KING_VAL									4000									//���ļ�ֵ
///////����Լ�ֵ/////////////
#define FLEXIBLE_KING_MOVE_VAL						2000									//��������Եļ�ֵ
#define FLEXIBLE_KING_KILL_VAL						3000									//��������Եļ�ֵ(����ɱ��)
#define FLEXIBLE_SOLDIER_MOVE_VAL					1500									//��������Եļ�ֵ
#define FLEXIBLE_SOLDIER_KILL_VAL					1800									//��������Եļ�ֵ(����ɱ��)
///////��ȫ̬��ֵ/////////////
#define SAFETY_KING_VAL								2000									//���İ�ȫ̬��ֵ
#define SAFETY_SOLDIER_BOARD_VAL					1500									//���İ�ȫ̬��ֵ
#define SAFETY_SOLDIER_DEFENSE_VAL					1300	
///////����̬��ֵ/////////////
#define ATTACK_KING_VAL								3000
#define ATTACK_SOLDIER_VAL							1500
///////����̬��ֵ/////////////
#define DEFENCE_KING_VAL							800
#define DEFENCE_SOLDIER_VAL							1200
		//ǰ������ΪEMPTY����ΪENEMY��Ϊ����̬,���ǰ������Ϊ�߽���Ϊ����̬
#define ATTACK_VAL(nTypeToGo)						150*nTypeToGo						//���ڽ���״̬�����ӵļ�ֵ
		//ǰ������ΪMINE���������һ��Ϊ����̬
#define DEFENSE_VAL(nTypeToGo)						100*nTypeToGo						//���ڷ���״̬�����ӵļ�ֵ	
		//�߽����ӻ��Ϊ�ҷ����Ӷ�Ϊ��ȫ̬
#define SAFE_VAL									200									//���ڰ�ȫ״̬�����ӵļ�ֵ


		//������������Լ�ǿ
#define KING_ALONE_VAL(nTypeToGo)					200*nTypeToGo						//���������ӵļ�ֵ
//ABOUT POLY
