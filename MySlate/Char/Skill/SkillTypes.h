// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SkillTypes.generated.h"

UENUM()
enum class ESkillType : uint8 //��������
{
	Normal = 0,
	Initiative, //����
	Passive_A,
	Passive_B,
	Passive_C,
	Passive_Permanent,
	Count
};

UENUM()
enum class ESkillAttackType : uint8 //���ܹ�������
{
	ATTACK_PHY = 1,	//�����˺�
	ATTACK_MAG,		//ħ���˺�
	ATTACK_CURE,	//����
	ATTACK_POWER,	//����
	ATTACK_BUFF,	//buffer
	ATTACK_SUCKHP,	//��Ѫ
	ATTACK_REBOUND	//����
};

//------------------- 
UENUM()
enum class EFilterType : uint8 //ѡ������
{
	Locked = 0,	//����һ��
	Circle,		//Բ��
	Rect,		//����
};

UENUM()
enum class ESelectType : uint8 //ѡ�˱��
{
	Enemy = 0,	//�ܻ���
	Self,		//������
};