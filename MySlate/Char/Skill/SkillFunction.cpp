
#include "MySlate.h"
#include "SkillFunction.h"

#include "./Template/SkillTemplate.h"
#include "./Pk/PkMsg.h"
#include "../MyBullet.h"
#include "../CharMgr.h"
#include "../MyChar.h"
#include "../Comp/MyCharDataComp.h"
#include "./CoolDown/CoolDown.h"
#include "./Function/Funcs/AbsPkEvent.h"
#include "./Pk/FightData.h"
#include "../Effect/EffectMgr.h"
#include "../Object/ObjMgr.h"

USkillFunction::USkillFunction() : Super(), IObjInterface()
{
	IObjInterface::SetObj(this);
}

USkillFunction::~USkillFunction()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::~USkillFunction"));
}

void USkillFunction::BeginDestroy()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::BeginDestroy:%d"), mSkillId);
	Super::BeginDestroy();
}

void USkillFunction::Reset()
{
	mSkillId = 0;
	mSkillTemplate = nullptr;
	mType = ESkillType::Normal;
	mPkMsg = nullptr;
	mBullet = nullptr;
	mAttacker = nullptr;
	mTargetLoc = FVector::ZeroVector;
	mCanAttack = false;
	mMoving = false;
	mIsOver = false;
	mTarget = nullptr;
	mTargetId = 0;
}

void USkillFunction::Recycle()
{
	if (mPkMsg != nullptr)
	{
		mPkMsg->Recycle();
		mPkMsg = nullptr;
	}

	IObjInterface::Recycle();
}

void USkillFunction::Tick(float DeltaSeconds)
{
	if (!mCanAttack)
	{
		mCanAttack = CanAttack();
	}

	if (mCanAttack)
	{
		if (mAttacker->GetState() != CharState::Attack)
		{
			mAttacker->ChangeState(CharState::Attack);

			//�������
			FVector targetLoc = mTarget != nullptr ? mTarget->GetActorLocation() : mTargetLoc;
			mAttacker->FaceToTargetLoc(targetLoc);
		}
	}
}

void USkillFunction::SetSkillTemplate(USkillTemplate* _skillTemp)
{
	mSkillTemplate = _skillTemp;
	mSkillId = _skillTemp->mId;
	mType = _skillTemp->mSkillType;
}

void USkillFunction::UseSkill(AMyChar* _target, const FVector& _targetLoc)
{
	if (_target != nullptr)
	{
		mTarget = _target;
		mTargetId = _target->GetUuid();
		mTargetLoc = _target->GetActorLocation();

		//�����ص�
		auto charDeathCallback = [&](AMyChar* _deathChar)->void {
			mTarget = nullptr;
			UE_LOG(BuffLogger, Warning, TEXT("--- USkillFunction::UseSkill, charDeathCallback, id:%d"), _deathChar->GetUuid());
		};


		_target->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
	}
	else
	{
		mTargetLoc = _targetLoc;
	}

}

bool USkillFunction::CanAttack()
{
	float DistSq = 0.f;
	AMyChar* target = mTarget;
	if (target != nullptr) //����Ŀ�꣬δ��
	{
		DistSq = (target->GetActorLocation() - mAttacker->GetActorLocation()).SizeSquared();
	}
	else if (mTargetId > 0) //����Ŀ�꣬����
	{
		if (mMoving) //�ƶ�����Ҫȡ���ƶ�
		{
			mAttacker->GetController()->StopMovement();
		}
		CancelSkill();
		return false;
	}
	else //�����ص�
	{
		DistSq = (mTargetLoc - mAttacker->GetActorLocation()).SizeSquared();
	}
	float atkDist = mSkillTemplate->mAttackDist;
	bool ret = FMath::Pow(atkDist, 2) > DistSq ? true : false;

	if (ret)
	{
		if (mMoving) //�ƶ�����Ҫȡ���ƶ�
		{
			mAttacker->GetController()->StopMovement();
			UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CanAttack, stop moving, atkDist > DistSq, %f > %f"), atkDist, FMath::Sqrt(DistSq));
		}
		else
		{
			UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CanAttack, dont need move, atkDist > DistSq, %f > %f"), atkDist, FMath::Sqrt(DistSq));
		}
		mMoving = false;
	}
	else
	{
		if (!mMoving)
		{
			if (target != nullptr) 
			{
				UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CanAttack, move to target"));
				UNavigationSystem::SimpleMoveToActor(mAttacker->GetController(), target);
			}
			else
			{
				UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CanAttack, move to location"));
				UNavigationSystem::SimpleMoveToLocation(mAttacker->GetController(), mTargetLoc);
			}
			mMoving = true;
		}
	}
	return ret;
}

void USkillFunction::CancelSkill()
{
	//��������Ŀ�걼��ʱ��Ŀ��������ȡ������
	mTargetId = 0;
	mTarget = nullptr;
	mTargetLoc = FVector::ZeroVector;
	mAttacker->ChangeState(CharState::IdleRun);
	mAttacker->SetUsingSkillNull();
	mCanAttack = false;
	mMoving = false;
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CancelSkill"));
}

void USkillFunction::SkillBegin()
{
	if (mPkMsg != nullptr || mAttacker == nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletCreate, mPkMsg != nullptr before"));
		return;
	}

	//TODO: ��������, �����ܱ���
	//mAttacker->TempNotifyA();
	mIsOver = false;

	mOwnerCD->Restart();

	UPkMsg* pkMsg = gGetObjMgr()->GetObj<UPkMsg>(gGetObjMgr()->mPkMsgCls);
	mPkMsg = pkMsg;
	pkMsg->SetData(mSkillTemplate, mAttacker, mTarget, mTargetLoc);

	UFightData* attackerData = mAttacker->GetDataComp()->GetFigthData()->Clone();//�������ߵ�ս�����ݿ����� �½���ս�����ݶ�����
	pkMsg->SetAttackerData(attackerData);
	pkMsg->SetAttackerTeam(mAttacker->GetTeamType());
	//step1 - ���м���ǰ��func, ����˲���ƶ�
	const TArray<UAbsPkEvent*>& functions2 = mSkillTemplate->GetBeforeSkill();
	for (UAbsPkEvent* func : functions2)
	{
		func->RunBeforeSkill(pkMsg);
	}

	//step2 - �����ͷ���pkǰ���¼���һ�����ڷż���ǰҪbuff�����и��������Լ���buff��func
	const TArray<UAbsPkEvent*>& functions = mSkillTemplate->GetBeforePk();
	for (UAbsPkEvent* func : functions)
	{
		func->RunBeforePk(pkMsg);
	}

	//---------- �����ӵ�
	//TODO: �����ӵ�,����pk��Ϣ, �󶨵������ĳ��socket��λ��
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	mBullet = GWorld->SpawnActor<AMyBullet>(mAttacker->BulletClass, SpawnInfo);
	mBullet->SetPkMsg(pkMsg);
	mBullet->SetSkillTemplate(mSkillTemplate);
	mBullet->SetTargetAndLoc(pkMsg->GetTarget(), pkMsg->GetTargetLoc());
	mBullet->SetSpeed(mSkillTemplate->mBltElem->mBulletSpeed);
	mBullet->SetFly(false);
	mBullet->SetActorHiddenInGame(true); //�����ӵ��ǲſ�ʼ��ʾ

	if (mSkillTemplate->mBltElem->mAttachPoint.Len() > 0) //�а󶨲�λ
	{
		//TODO: ��������, ���þ�����Ϣtransform
		mBullet->AttachRootComponentTo(mAttacker->GetMesh(), FName(*mSkillTemplate->mBltElem->mAttachPoint));
		mBullet->SetActorRelativeLocation(mSkillTemplate->mBltElem->mLoc);
		mBullet->SetActorRelativeRotation(mSkillTemplate->mBltElem->mRotate);
		mBullet->SetActorRelativeScale3D(mSkillTemplate->mBltElem->mScale);
	}
	else
	{
		mBullet->SetActorLocation(mAttacker->GetActorLocation() + mSkillTemplate->mBltElem->mLoc);
		mBullet->SetActorRotation(mAttacker->GetActorRotation() + mSkillTemplate->mBltElem->mRotate);
		mBullet->SetActorScale3D(mSkillTemplate->mBltElem->mScale);
	}

	//---------- ����, ��Ч�����߼�
	gGetEffectMgr()->AttachBehav(mAttacker, EOwnType::Self, mBullet, mSkillTemplate->mBehavId);

	//---------- ����, Mesh�����߼�
	gGetEffectMgr()->AttachMesh(mBullet, mSkillTemplate);
}

void USkillFunction::BulletCreate()
{
	if (mBullet == nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletCreate, mBullet == nullptr before"));
		return;
	}
	mBullet->SetActorHiddenInGame(false);
}

void USkillFunction::BulletShoot()
{
	if (mBullet != nullptr && mPkMsg != nullptr)
	{
		//step3 - ���и��������Լ�������������func����ÿ������Ŀ�����
		const TArray<UAbsPkEvent*>& functions = mSkillTemplate->GetBeforeEvns();
		for (UAbsPkEvent* func : functions)
		{
			func->RunBeforeEvns(mPkMsg);
		}

		//TODO: ���������󶨵㣬��Ŀ����У�����ײ�����ײ�¼�
		mBullet->DetachRootComponentFromParent();
		mBullet->SetFly(true);

		UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::BulletShoot, mBullet = nullptr"));
		mBullet = nullptr;//�����ȥ���ӵ���pkMsg�ÿգ����ӵ�ȥ�ͷ�pkMsg
		mPkMsg = nullptr;
	}
	else
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletShoot, mBullet or mPkMsg is nullptr"));
	}
}

void USkillFunction::SkillEnd()
{
	//�л�״̬��ʹ���еļ����ÿ�
	//step6 - ���м��ܺ����¼�, ����˲���ƶ��ƻ�ԭ��
	const TArray<UAbsPkEvent*>& functions2 = mSkillTemplate->GetEndSkill();
	for (UAbsPkEvent* func : functions2)
	{	//issue mPkMsg is nullptr befor
		func->RunEndSkill(mPkMsg);
	}

	mIsOver = true;
	CancelSkill();
	ReleaseData();
}

void USkillFunction::ReleaseData()
{
	if (!mIsOver)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::ReleaseData, mIsOver == false"));

		CancelSkill();

		//�����ͷ��ڴ�
		if (mBullet != nullptr) //�����ӵ���û�����ȥ�����ܾͱ���ϣ���Ҫ�����ӵ�,pkMsg��������������
		{
			mBullet->DestroyBullet();
			mBullet = nullptr;
			mPkMsg = nullptr;
		}
		else //��û�д����ӵ����ͱ�����������pkMsg
		{
			if (mPkMsg != nullptr)
			{
				//mPkMsg->RemoveFromRoot();
				//mPkMsg->ConditionalBeginDestroy();
				mPkMsg->Recycle();
				mPkMsg = nullptr;
			}
		}
	}
}

