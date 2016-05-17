
#include "MySlate.h"
#include "MyChar.h"

#include "./Skill/CoolDown/CoolDownComp.h"
#include "./Skill/CoolDown/CoolDown.h"
#include "./Skill/SkillFunction.h"
#include "./Comp/MyCharDataComp.h"
#include "./AI/MyAIController.h"
#include "./CharMgr.h"
#include "./CharData.h"
#include "./Skill/Buff/BuffMgr.h"
#include "./Effect/Effects/BehavElem.h"

AMyChar::AMyChar() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	//--------- 
	gCharMgr = nullptr;
	mCDComp = nullptr;
	mDataComp = nullptr;
	mUsingSkill = nullptr;
	mCharState = CharState::IdleRun;
	mUuid = 0;
	mCharData = nullptr;
	mTurnToLoc = FVector::ZeroVector;
	mAnimation = nullptr;
}

AMyChar::~AMyChar()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::~AMyChar"));
}

void AMyChar::BeginPlay()
{
	Super::BeginPlay();
	gCharMgr = gGetCharMgr();

	//����Ĭ��AI�����࣬������һ��
	AIControllerClass = AMyAIController::StaticClass();
	SpawnDefaultController();

	//ע��cd���
	mCDComp = NewObject<UCoolDownComp>(this, TEXT("CDComponent"));
	mCDComp->RegisterComponent();
	mCDComp->SetOwner(this);

	//ע��data���
	mDataComp = NewObject<UMyCharDataComp>(this, TEXT("CharDataComponent"));
	mDataComp->RegisterComponent();

	//��buff������
	mDeathMultiNotify.Add(FDeathOneNotify::CreateUObject(gGetBuffMgr(), &UBuffMgr::CharDeathNotify));
	//GetMesh()->SetSkeletalMesh(nullptr);

	//����ʵ��
	mAnimation = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	if (mAnimation != nullptr)
	{
		UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::BeginPlay, UMyAnimInstance load success"));
	}
}

void AMyChar::Tick( float DeltaTime )
{
	AActor::Tick( DeltaTime );
	IBehavInterface::BehavTick(DeltaTime);

	if (mCDComp != nullptr)
	{
		mCDComp->MyTick(DeltaTime);
	}

	if (mUsingSkill != nullptr)
	{
		mUsingSkill->Tick(DeltaTime);
	}
}	

void AMyChar::Destroyed()
{

	if (mCDComp != nullptr)
	{
		mCDComp->DestroyComponent();
		mCDComp = nullptr;
	}

	if (mDataComp != nullptr)
	{
		mDataComp->DestroyComponent();
		mDataComp = nullptr;
	}

	UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::Destroyed"));
	Super::Destroyed();
}

void AMyChar::OnCDFinish(UCoolDown* _cd)
{
	UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::OnCDFinish, skillId:%d"), _cd->GetSkillId());
	mCanUseSkillArr.AddUnique(_cd);
}

void AMyChar::AddDeathNotify(const FDeathOneNotify& _notify)
{
	mDeathMultiNotify.Add(_notify);
}

void AMyChar::SetCharData(int32 _id)
{
	mDataComp->SetCharData(_id);
}

bool AMyChar::IsAlive() const
{
	return mDataComp->mHealth > 0.f ? true : false;
}

bool AMyChar::UseSkill(int32 _skillId, int32 _targetId /* = 0 */, FVector _targetLoc /* = FVector::ZeroVector */)
{
	bool canUse = false;
	if (mUsingSkill == nullptr)
	{	
		//�����ݴ������Ǳ��룬��Ϊʹ�ü�����Ŀ��϶��Ǵ��ڵ�
		//AMyChar* target = _targetId > 0 ? gGetCharMgr()->GetChar(_targetId) : nullptr;
		//if (target == nullptr)
		//{
		//	return canUse;
		//}

		AMyChar* target = gGetCharMgr()->GetChar(_targetId);

		USkillFunction* skillFunc = mCDComp->CanUseSkill(_skillId);
		if (skillFunc != nullptr)
		{
			skillFunc->UseSkill(target, _targetLoc);
			mUsingSkill = skillFunc;
			canUse = true;
		}
	}		
	else
	{
		UE_LOG(SkillLogger, Error, TEXT("--AMyChar::Turing- AMyChar::UseSkill, mUsingSkill != nullptr, skillId:%d"), mUsingSkill->mSkillId);
	}

	return canUse;
}

void AMyChar::ChangeState(CharState _state)
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMyChar::ChangeState, state = %s"), *GetEnumAsString("CharState", _state));
	mCharState = _state;
	if (mAnimation != nullptr)
	{
		mAnimation->mStateDlg.ExecuteIfBound(_state);
	}
	//for test
	//USkillFunction* sdf = GetUsingSkill();
	//bool b = sdf != nullptr ? sdf->CanAttack() : false;
	//if (b)
	//{
	//	UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::UseSkill, mUsingSkill != nullptr, skillId:%d"), mUsingSkill->mSkillId);
	//}
}

void AMyChar::FaceToTargetLoc(const FVector& _targetLoc, bool _smooth /* = false */)
{
	if (!_smooth)
	{
		SetActorRotation(
			UKismetMathLibrary::FindLookAtRotation(
				GetActorLocation()
				, _targetLoc)
			);
	}
	else //ƽ����ת
	{
		mTurnToLoc = _targetLoc;
		mTurnToRot = FRotator::ZeroRotator;

		auto rotaInterp = [&]() -> void{
			mTurnToRot = UKismetMathLibrary::RInterpTo(
				GetActorRotation()
				, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mTurnToLoc)
				, GetWorld()->GetDeltaSeconds()
				, 10.f);

			if (GetActorRotation().Equals(mTurnToRot, 1.f))
			{
				this->GetWorldTimerManager().ClearTimer(mTimer); //����ʱ��
				UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::FaceToTargetLoc, stop rotate"));
			}
			else
			{
				SetActorRotation(mTurnToRot);
			}
		};

		GetWorldTimerManager().SetTimer(mTimer, FTimerDelegate::CreateLambda(rotaInterp), GetWorld()->GetDeltaSeconds(), true); //���ö�ʱ��
	}
}

void AMyChar::Death()
{
	mDeathMultiNotify.Broadcast(this);//֪ͨ���а��˵Ĵ���
	IBehavInterface::RemoveBehavElemAll();

	//ʩ�ż����б��������ͷŴ������ӵ���pkMsg
	if (mUsingSkill != nullptr)
	{
		mUsingSkill->ReleaseData();
		mUsingSkill = nullptr;
	}

	//TODO: �ӹ��������Ƴ�������Ӧ�������գ����������٣���ʱ������
	gCharMgr->RemoveChar(mUuid);

	OnDeath(); //֪ͨһ����ͼ

	ChangeState(CharState::Death);//�ȶ���״̬��֪ͨ����
}

void AMyChar::Reset()
{

}