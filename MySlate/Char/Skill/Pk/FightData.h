#pragma once

#include "../Utils/CommonDef.h"
#include "FightData.generated.h"

UCLASS()
class UFightData : public UObject
{
	GENERATED_BODY()

public:
	UFightData();
	virtual ~UFightData();
	virtual void BeginDestroy() override;

	UFightData* Clone();
	void Copy(UFightData* _fightData);
	void Reset();

	float GetAttackPhy() const { return mAttackPhy; }
	float GetLv() const { return mLv; }

public:
	//ԭʼ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		float		mAttackPhy;		//������

public:
	//�ɳ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		int			mLv;			//�ȼ�

public:
};
