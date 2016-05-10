
#pragma once

#include "../SkillTypes.h"
#include "../../Comp/MyBaseComp.h"

#include "CoolDownComp.generated.h"

class UCoolDown;
class AMyChar;

UCLASS()
class UCoolDownComp : public UMyBaseComp
{
	GENERATED_BODY()
public:
	UCoolDownComp();
	virtual ~UCoolDownComp();

public:
	// Begin UActorComponent Interface.
	virtual void BeginPlay() override; //�����new��ʱ����������
	virtual void BeginDestroy() override; //������gc��ʱ����ã��������������ã�һ�㲻��
	virtual void DestroyComponent(bool bPromoteChildren = false); //�������ã�����
	// End UActorComponent Interface.

	void MyTick(float DeltaTime);


	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		SetOwner(AMyChar* _owner) { mOwner = _owner; }

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		USkillFunction*	CanUseSkill(int32 _skillId);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		RestartCD(int32 _skillId);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		RemoveCDById(int32 _skillId);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		AddCD(int32 _skillId, bool _isRestartCD);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCoolDownComp")
		TArray<UCoolDown*>		mCDArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCoolDownComp")
		AMyChar*				mOwner;

};