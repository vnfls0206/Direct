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
	int Detect_Range;		//Ž������
	int Attack_Range;		//���ݹ���
	//���ݷ�, ü��, ���� ��, ���ݵ�����, ��-��Ÿ��
	UINT uiAttackDamage;
	UINT uiHP;
	float uiAttackDelay;
	int iAttackType;	//0�� �ٰŸ�, 1�� ���Ÿ� ����Ÿ��
	const TCHAR* pName;

}MON_INFO;


#endif                  