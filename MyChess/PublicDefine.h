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
		//单兵价值
#define SOLDIER_VAL_0								2500									//普通炮灰的价值
#define SOLDIER_VAL_1								2000									//普通炮灰的价值
#define SOLDIER_VAL_2								1800									//普通炮灰的价值
#define SOLDIER_VAL_3								1400									//普通炮灰的价值
#define SOLDIER_VAL_4								1400									//普通炮灰的价值
#define SOLDIER_VAL_5								1600									//普通炮灰的价值
#define SOLDIER_VAL_6								3000									//普通炮灰的价值
		//王棋价值
#define KING_VAL									4000									//王的价值
///////灵活性价值/////////////
#define FLEXIBLE_KING_MOVE_VAL						2000									//王的灵活性的价值
#define FLEXIBLE_KING_KILL_VAL						3000									//王的灵活性的价值(可以杀人)
#define FLEXIBLE_SOLDIER_MOVE_VAL					1500									//兵的灵活性的价值
#define FLEXIBLE_SOLDIER_KILL_VAL					1800									//兵的灵活性的价值(可以杀人)
///////安全态价值/////////////
#define SAFETY_KING_VAL								2000									//王的安全态价值
#define SAFETY_SOLDIER_BOARD_VAL					1500									//兵的安全态价值
#define SAFETY_SOLDIER_DEFENSE_VAL					1300	
///////攻击态价值/////////////
#define ATTACK_KING_VAL								3000
#define ATTACK_SOLDIER_VAL							1500
///////防御态价值/////////////
#define DEFENCE_KING_VAL							800
#define DEFENCE_SOLDIER_VAL							1200
		//前进方向为EMPTY或者为ENEMY都为进攻态,如果前进方向为边界则不为进攻态
#define ATTACK_VAL(nTypeToGo)						150*nTypeToGo						//处于进攻状态的棋子的价值
		//前进方向为MINE或者在最后一行为防御态
#define DEFENSE_VAL(nTypeToGo)						100*nTypeToGo						//处于防御状态的棋子的价值	
		//边界棋子或后方为我方棋子都为安全态
#define SAFE_VAL									200									//处于安全状态的棋子的价值


		//孤立的王灵活性极强
#define KING_ALONE_VAL(nTypeToGo)					200*nTypeToGo						//孤立的棋子的价值
//ABOUT POLY
