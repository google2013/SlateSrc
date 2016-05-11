
#pragma once

#include "../../Skill/SkillTypes.h"
#include "./BehavElem.h"
#include "ShakeElem.generated.h"

UCLASS(BlueprintType)
class UShakeElem : public UBehavElem //��Ԫ�أ�����Ч�༭���༭������
{
	GENERATED_BODY()
public:
	UShakeElem();
	virtual ~UShakeElem();
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, Category = "UShakeElem")
		virtual void Tick(float DeltaTime) override;

	virtual void Start() override;

	UShakeElem* Clone();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		int32		mA;						//���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mW;						//���ٶ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mTime;					//����ʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		bool		mIsX;					//X����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EOwnType	mOwnType;				//������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mDelayTime;				//��ʱʱ��

private:
		FVector		mLoc;
		FVector		mDtLoc;
		float		mRunTimer;
};