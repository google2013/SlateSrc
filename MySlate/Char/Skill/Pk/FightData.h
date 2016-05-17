#pragma once

#include "../../../GameUtils.h"
#include "../../Object/ObjInter.h"

#include "FightData.generated.h"

UCLASS()
class UFightData : public UObject, public IObjInterface
{
	GENERATED_BODY()

public:
	UFightData();
	virtual ~UFightData();
	virtual void BeginDestroy() override;
	virtual void Reset() override;
	virtual void Recycle() override;

	UFightData* Clone();
	void Copy(UFightData* _fightData);
	

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
