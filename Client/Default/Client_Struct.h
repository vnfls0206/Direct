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
	int Detect_Range;
	int Attack_Range;


}MON_INFO;


#endif                  