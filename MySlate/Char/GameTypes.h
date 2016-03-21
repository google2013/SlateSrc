// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameTypes.generated.h"

UENUM()
enum class EGroup : uint8 //������
{
	None = 0,
	Group1,
	Group2,
	Group3,
	Group4,
	Count,
};

UENUM()
enum class ETeam : uint8 //�ǵ�����
{
	None = 0,
	Teammate,
	Enemy,
};
