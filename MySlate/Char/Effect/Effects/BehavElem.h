
#pragma once

#include "../../Skill/SkillTypes.h"
#include "../../Object/ObjInter.h"
#include "BehavElem.generated.h"

class UBehavElem;
class IBehavInterface;

DECLARE_DELEGATE_OneParam(FBehavElemDlg, UBehavElem*);

UENUM()
enum class EElemState : uint8 //��Ч״̬
{
	Idle = 0,
	Start,
	Delay,
	Ticking,
	Over,
};

UCLASS(BlueprintType)
class UBehavElem : public UObject, public IObjInterface //��Ԫ�أ�����Ч�༭���༭������
{
	GENERATED_BODY()
public:
	UBehavElem();
	virtual ~UBehavElem();
	virtual void BeginDestroy() override;
	virtual void Reset() override;

public:
	virtual void Tick(float DeltaTime);
	virtual void Start();
	virtual void SetActor(IBehavInterface* _actor);
	virtual void MyDestroy(bool _needNotify = true);

	void AddOverDlg(FBehavElemDlg _dlg);
	EElemState	GetElemState() const { return mState; }

public:
	int32		mGroupId;		//��Ч��id��ÿһ��behav������һ��mGroupId���Ա�����ɾ��

protected:
	IBehavInterface*	mTarget;				//����
	float		mDelayer;
	float		mDelayTime;
	EElemState	mState;
	FBehavElemDlg	mOverDlg;
};
