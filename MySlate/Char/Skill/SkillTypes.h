
#pragma once

#include "SkillTypes.generated.h"

UENUM()
enum class EAnimType : uint8 //���ܶ���
{
	None = 0,
	Skill_1,
	Skill_2,
	Skill_3,
	Skill_4,
	Skill_5,
	Skill_6,
	Skill_7,
	Injure_1,
	Injure_2,
	Victory_1,
	Victory_2,
	Victory_3,
	Count,
};

UENUM()
enum class EOwnType : uint8 //��Ч������
{
	None = 0,
	Self,
	Target,
	Bullet,
	Scene,
	Count,
};

UENUM()
enum class EFollowType : uint8 //��Ч����
{
	None = 0,
	Follow,
	UnFollow,
	Count,
};

UENUM()
enum class EIntervalType : uint8 //buff��������
{
	Once = 0,	//һ����
	Interval,	//�����
	Durable,	//������
};

UENUM()
enum class EBuffState : uint8 //buff״̬
{
	Idle = 0,
	Start,
	Break,
	Over,
};

UENUM()
enum class ESkillType : uint8 //��������
{
	Normal = 0,
	Initiative, //����
	Passive_A,
	Passive_B,
	Passive_C,
	Passive_Permanent,
	Count,
};

UENUM()
enum class ESkillAtkType : uint8 //���ܹ�������
{
	None = 0,
	Physics,	//�����˺�
	Magic,		//ħ���˺�
	Cure,		//����
	Power,		//����
	Buff,		//buffer
	Suckup,		//��Ѫ
	Rebound,	//����
	Count,
};

UENUM()
enum class EFormulaPkType : uint8 //���㹫ʽ����
{
	None = 0,
	Dodge,		//����
	Crit,		//����
	Damage,		//�˺�
	Cure,		//����
	Rebound,	//����
	Count,
};

//------------------- 
UENUM()
enum class EFilterType : uint8 //ѡ������
{
	Locked = 0,	//����һ��
	Circle,		//Բ��
	Rect,		//����
	Count,
};

UENUM()
enum class ESelectType : uint8 //ѡ�˱��
{
	Enemy = 0,	//��
	Self,		//��
	Count,
};

UENUM()
enum class ELockedType : uint8 //��������
{
	Loc = 0,	//�ص�
	Char,		//��
	Count,
};