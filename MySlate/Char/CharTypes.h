
#pragma once

#include "CharTypes.generated.h"

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

UENUM(BlueprintType)
enum class CharState : uint8 //����״̬
{
	IdleRun = 0,
	Attack,
	Injured,
	Death,
	Count,
};