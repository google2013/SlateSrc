
#pragma once

#include "../../Skill/SkillTypes.h"
#include "./BehavElem.h"
#include "EffectElem.generated.h"

UCLASS(BlueprintType)
class UEffDataElem : public UBehavElem //��ЧԪ�أ�����Ч�༭���༭������
{
	GENERATED_BODY()
public:
	UEffDataElem();
	virtual ~UEffDataElem();
	virtual void BeginDestroy() override;
	
	virtual void Tick(float DeltaTime) override;
	virtual void Start() override;
	virtual void MyDestroy(bool _needNotify = true) override;
	virtual void SetActor(IBehavInterface* _actor) override;

	void SetData(UParticleSystemComponent* _psComp);
	UEffDataElem* Clone();

	UFUNCTION(BlueprintCallable, Category = "UEffDataElem")
		void OnCompleted(UParticleSystemComponent* _psComp);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		int32		mResId;					//������Դid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EOwnType	mOwnType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EFollowType	mFollowType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		FString		mBindPoint;				//�󶨹���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mDelayTime;			//��ʱʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		FVector		mLoc;					//������Ϣ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		FVector		mScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		FRotator	mRotate;

private:
	UParticleSystemComponent*	mPsComp;
};