
#pragma once

#include "../../Common/ISingleton.h"
#include "Tickable.h"
#include "../Skill/SkillTypes.h"
#include "EffectMgr.generated.h"

class UEffDataElem;
class UShakeElem;
struct FEffElemInfo;
struct FShakeInfo;
class UBehavData;
class AMyChar;
class AMyBullet;

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
	FEffectBind(UEffDataElem* _effData, int32 _uuId, UParticleSystemComponent* _psComp);
	int32	mUuId;		//Ψһʶ��������ͬbuff�Ƴ�
	float	mDelayTimer; //�ӳ�ʱ�� �Ʋ���
	bool	mHasDelay; //�ӳ�ʱ�� �Ʋ���
	float	mTotalTimer; //��ʱ�� �Ʋ���
	bool	mHasTotal; //��ʱ�� �Ʋ���
	UEffDataElem*	mEffData;
	UParticleSystemComponent* mPsComp; //���ɵ��������
};

UCLASS()
class UEffectMgr : public UObject, public FTickableGameObject, public USingleton<UEffectMgr>
{
	GENERATED_BODY()

public:
	UEffectMgr();
	virtual ~UEffectMgr();
	virtual void BeginDestroy() override;

	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject Interface.

public:

	UFUNCTION(BlueprintCallable, Category = "UEffectMgr")
		void			loadBehavInfo();	//TODO: ���Ż�����һ���Լ��أ��õ�ʱ�ż���
	void		CopyEffInfoToData(TArray<FEffElemInfo>& _info, TArray<UEffDataElem*>& _dstVec);
	void		CopyShkInfoToData(TArray<FShakeInfo>& _info, TArray<UShakeElem*>& _dstVec);

	UFUNCTION(BlueprintCallable, Category = "UEffectMgr")
		UBehavData*		GetBehav(int32 _key);

	UFUNCTION(BlueprintCallable, Category = "UEffectMgr")
		void			AttachBehav(AMyChar* _tarChar, EOwnType _ownType, AMyBullet* _tarBullet, int32 _behavDataId);

	UFUNCTION(BlueprintCallable, Category = "UEffectMgr")
		void			DetachEffect(int32 _targetId, const TArray<int32>& _effuuids);

	UFUNCTION(BlueprintCallable, Category = "UEffectMgr")
		UShakeElem*	TestShake(AMyChar* _actor, int32 _id);

public:
	TMap<int32, TArray<FEffectBind>>	mEffectBindMap; //��Ч����
	TMap<int32, UBehavData*>	mBehavMap;
};
