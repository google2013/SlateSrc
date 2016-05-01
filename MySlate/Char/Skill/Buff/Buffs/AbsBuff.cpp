
#include "MySlate.h"
#include "AbsBuff.h"

#include "../../Function/Funcs/AbsPkEvent.h"
#include "../../Pk/PkMsg.h"
#include "../../../CharMgr.h"
#include "../../../MyChar.h"
#include "../../Template/BufflTemplate.h"
#include "../../Effect/UBehavData.h"
#include "../../SkillMgr.h"

UAbsBuff::UAbsBuff() : Super()
{
	mBuffId = 0;
	mSkillId = 0;
	//mOwnerId = 0;
	//mAttackerId = 0;
	mBuffTemp = nullptr;
	mTimer = 0.f;
	mInterTimer = 0.f;
	mLessTimes = 0;
	mAttacker = nullptr;
	mOwnerChar = nullptr;
	mBuffState = EBuffState::Idle;
}

UAbsBuff::~UAbsBuff()
{

}

void UAbsBuff::BeginDestroy()
{

	Super::BeginDestroy();
}

void UAbsBuff::Tick(float DeltaSeconds)
{
	//���������˺�
	if (mBuffTemp->mInterType == EIntervalType::Once)
	{
		return;
	}
	else if (mBuffTemp->mInterType == EIntervalType::Interval)
	{
		if (mInterTimer > mBuffTemp->mInterTime)
		{
			const TArray<UAbsPkEvent*>& funcs = mBuffTemp->GetAttrs();
			for (UAbsPkEvent* func : funcs)
			{
				func->RunTick(DeltaSeconds);
			}
			mInterTimer = 0.f;
		}
		else
		{
			mInterTimer += DeltaSeconds;
		}
	}
	else if (mBuffTemp->mInterType == EIntervalType::Durable)
	{
		const TArray<UAbsPkEvent*>& funcs = mBuffTemp->GetAttrs();
		for (UAbsPkEvent* func : funcs)
		{
			func->RunTick(DeltaSeconds);
		}
	}


	mTimer += DeltaSeconds;
	if (mTimer > mBuffTemp->mBuffTime)
	{
		ChangeState(EBuffState::Over);
	}
}

void UAbsBuff::BuffStart()
{
	ChangeState(EBuffState::Start);

	const TArray<UAbsPkEvent*>& funcs = mBuffTemp->GetAttrs();
	for (UAbsPkEvent* func : funcs)
	{
		func->RunStart();
	}

	//��Ч��
	float _buffTime = mBuffTemp->mInterType == EIntervalType::Once ? -1.f : mBuffTemp->mBuffTime;
	mEffectUUids = USkillMgr::GetInstance()->AttachBehavData(mOwnerChar, mBuffTemp->mBehavDataId, _buffTime);
}

void UAbsBuff::BuffOver()
{
	ChangeState(EBuffState::Over);

	const TArray<UAbsPkEvent*>& funcs = mBuffTemp->GetAttrs();
	for (UAbsPkEvent* func : funcs)
	{
		func->RunOver();
	}

	//�����Ч��
	USkillMgr::GetInstance()->DetachEffect(mOwnerChar->GetUuid(), mEffectUUids);
}

void UAbsBuff::RunBeforePk(UPkMsg* msg)
{

}

void UAbsBuff::RunEndPk(UPkMsg* msg)
{

}

AMyChar* UAbsBuff::GetOwnerChar()
{
	return mOwnerChar;
}

float UAbsBuff::GetDtVal(float _value)
{
	float f = (float)mBuffTemp->mBuffTime / GWorld->GetDeltaSeconds();
	return _value / f;
}

void UAbsBuff::SetData(UBufflTemplate* _buffTemp, AMyChar* _attacker, AMyChar* _target, int32 _skillId)
{
	mBuffTemp = _buffTemp;
	mBuffId = _buffTemp->mId;
	mSkillId = _skillId;
	mOwnerChar = _target;
	mAttacker = _attacker;

	//ӵ���߲����������������ٵ�����Ϊ����buffMgr�е������ص���ǿ�ƽ���buff�������߾ͱ���Ҫ

	if (_attacker != nullptr)
	{
		//�����ص�
		auto charDeathCallback = [&](AMyChar* _deathChar)->void {
			mAttacker = nullptr;

			const TArray<UAbsPkEvent*>& funcs = mBuffTemp->GetAttrs();
			for (UAbsPkEvent* func : funcs)
			{
				func->SetData(this, mAttacker, mOwnerChar);
			}

			UE_LOG(BuffLogger, Warning, TEXT("--- UAbsBuff::SetData, charDeathCallback, id:%d"), _deathChar->GetUuid());
		};

		_attacker->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
	}

	//���ø���func������
	const TArray<UAbsPkEvent*>& funcs = mBuffTemp->GetAttrs();
	for (UAbsPkEvent* func : funcs)
	{
		func->SetData(this, mAttacker, mOwnerChar);
	}
}
