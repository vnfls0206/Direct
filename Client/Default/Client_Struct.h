#ifndef Client_Struct_h__
#define Client_Struct_h__



typedef struct tagState_Information
{
	float m_Motion_Time;
	int Min_Texture_Num;
	int Max_Texture_Num;

}STATE_INFO;

typedef struct tagMonster_Infomation
{
	STATE_INFO m_State_Info[12];
	int Detect_Range;		//탐색범위
	int Attack_Range;		//공격범위
	//공격력, 체력, 몬스터 명, 공격딜레이, 근-원타입
	UINT uiAttackDamage;
	UINT uiHP;
	float uiAttackDelay;
	float uiCurrentAttackDelay;
	int iAttackType;	//1은 근거리, -1은 원거리 공격타입
	const TCHAR* pName;

}MON_INFO;

typedef struct tagPlayer_Infomation
{
	STATE_INFO m_State_Info[12];
	int Attack_Range;		//공격범위
	//공격력, 체력, 마나, 공격딜레이, 이름
	UINT uiAttackDamage;
	UINT uiHP;
	float fMana;
	float uiAttackDelay;
	const TCHAR* pName;
	
}PLAYER_INFO;


#endif                  