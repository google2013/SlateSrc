
#pragma once

#include "Tickable.h"
#include "../../Common/ISingleton.h"
#include "./Effect/UBehavData.h"

#include "SkillMgr.generated.h"

class UBehavData;
class AMyChar;

USTRUCT()
struct FEffectBind
{
	GENERATED_USTRUCT_BODY()
public:
	FEffectBind() {}
	bool operator ==(const FEffectBind& _cp) //����==��������TArray remove����Ҫ�õ�
	{
		return mUuId == _cp.mUuId;
	}
	FEffectBind(UEffDataElem* _effData, int32 _lefTtime, int32 _uuId, UParticleSystemComponent* _psComp);
	int32	mUuId;		//Ψһʶ��������ͬbuff�Ƴ�
	float	mDelayTimer; //�ӳ�ʱ�� �Ʋ���
	float	mLeftTimer;	//ʣ��ʱ�� �Ʋ���
	UEffDataElem*	mEffData;
	UParticleSystemComponent* mPsComp; //���ɵ��������
};

UCLASS()
class USkillMgr : public UObject, public FTickableGameObject, public USingleton<USkillMgr>
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	USkillMgr();
	virtual ~USkillMgr();
	virtual void BeginDestroy() override;

	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject Interface.

public:
	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		UBehavData*	GetBehaviorData(int32 _id);

	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		TArray<int32>	AttachBehavData(AMyChar* _target, int32 _behavDataId, float _time = -1.f);

	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		bool			AttachBehavDataOnce(AMyChar* _target, UBehavData* _behavData);

	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		void			CreateEffBind(AMyChar* _target, UEffDataElem* _ele, float _time, TArray<FEffectBind>& _bindArr, TArray<int32>& _dstUuids, bool _isDurable = true);

	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		void			DetachEffect(int32 _targetId, const TArray<int32>& _effuuids);

	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		void			CharDeathNotify(AMyChar* _char);

	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		UBehavData*		CreateBehavData(int32 _id);

private:
	UBehavData* LoadBehaviorData(int32 _id);

private:
	TMap<int32, TArray<FEffectBind>>	mEffectBindMap; //��Ч����

	TMap<int32, UBehavData*>		mBehaviorDataMap;//��ż�������
};
