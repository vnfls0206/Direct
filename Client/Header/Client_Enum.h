#ifndef Client_Enum_h__
#define Client_Enum_h__

enum eSceneState { eScene_Static = 0, eScene_Logo, eScene_Stage1, eScene_Count };
enum eDirection { eLEFT, eUP, eRIGHT, eDOWN };
enum eMonsterState { eLEFT_IDLE = 0, eUP_IDLE, eRIGHT_IDLE, eDOWN_IDLE,		//���
					 eLEFT_TRACE, eUP_TRACE, eRIGHT_TRACE, eDOWN_TRACE,		//����
					 eLEFT_ATTACK, eUP_ATTACK, eRIGHT_ATTACK, eDOWN_ATTACK,		//����
					 eMState_Count };
enum eMonsterAlignment { eGOOD, eEVIL, eMAlignmente_Count };


#endif