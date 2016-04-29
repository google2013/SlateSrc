#include "MySlate.h"
#include "BTDecorateMyBase.h"

#include "./MyAIController.h"
#include "../MyChar.h"
#include "../Skill/CoolDown/CoolDownComp.h"
#include "../Skill/Template/SkillTemplate.h"
#include "../Skill/CoolDown/CoolDown.h"

UBTDecorateMyBase::UBTDecorateMyBase()
	: Super()
{
	mOwnerChar = nullptr;
	mOwnerAI = nullptr;
	mBTComp = nullptr;

	//����tick ����
	bNotifyTick = true;
}

UBTDecorateMyBase::~UBTDecorateMyBase()
{
	UE_LOG(AILogger, Warning, TEXT("--- UBTDecorateMyBase::~UBTDecorateMyBase"));
}


void UBTDecorateMyBase::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}

//��ʼ����Ա�������������
void UBTDecorateMyBase::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	mBTComp = &OwnerComp;
	mOwnerAI = mBTComp != nullptr ? Cast<AMyAIController>(mBTComp->GetOwner()) : nullptr;
	mOwnerChar = mOwnerAI != nullptr ? Cast<AMyChar>(mOwnerAI->GetPawn()) : nullptr;
}

void UBTDecorateMyBase::OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp)
{

}

bool UBTDecorateMyBase::CanUseSkill()
{
	if (mOwnerChar->mCharState != CharState::Attack) //���ڹ���״̬���пɷŵļ���
	{
		if (mOwnerChar->mCanUseSkillArr.Num() > 0)
		{
			return true;
		}
	}
	return false;
}

void UBTDecorateMyBase::UseSkill()
{
	if (mOwnerChar->mCanUseSkillArr.Num() > 0)
	{
		//mOwnerChar->mCDComp->UseSkill(mOwnerChar->mCanUseSkillArr[0], 0);
	}
}

bool UBTDecorateMyBase::IsAttackRange()
{
	if (mOwnerChar->mUsingSkill != nullptr)
	{

		/*
		USkillTemplate* skillTemp = mOwnerChar->mUsingSkill->mSkillTemplate;


		UBlackboardComponent* BlackboardComp = mBTComp->GetBlackboardComponent();
		if (BlackboardComp)
		{
			int32 EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
			AMyChar* enemy = Cast<AMyChar>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
			if (enemy)
			{
				const float DistSq = (enemy->GetActorLocation() - mOwnerChar->GetActorLocation()).Size();
				return skillTemp->mAttackDist > DistSq ? true : false;
			}
		}
		*/
	}

	return false;
}
