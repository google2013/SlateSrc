#include "MySlate.h"
#include "BTTaskMyBase.h"

#include "../MyChar.h"
#include "./MyAIController.h"
#include "../Skill/CoolDown/CoolDownComp.h"
#include "../Skill/Template/SkillTemplate.h"
#include "../Skill/CoolDown/CoolDown.h"

UBTTaskMyBase::UBTTaskMyBase()
	: Super()
{
	mOwnerChar = nullptr;
	mOwnerAI = nullptr;
	mBTComp = nullptr;

	//����ÿ֡tick
	bNotifyTick = 1;
}

UBTTaskMyBase::~UBTTaskMyBase()
{
	UE_LOG(AILogger, Warning, TEXT("--- UBTTaskMyBase::~UBTTaskMyBase"));
}

void UBTTaskMyBase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTaskMyBase::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	mBTComp = &OwnerComp;
	mOwnerAI = mBTComp != nullptr ? Cast<AMyAIController>(mBTComp->GetOwner()) : nullptr;
	mOwnerChar = mOwnerAI != nullptr ? Cast<AMyChar>(mOwnerAI->GetPawn()) : nullptr;
}

void UBTTaskMyBase::OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp)
{

}

bool UBTTaskMyBase::MoveToTarget()
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
				if (skillTemp->mAttackDist > DistSq)
				{
					return true;
				}
				else
				{
					AIOwner->MoveToActor(enemy, skillTemp->mAttackDist - 1.f); //���ڹ�����Χ�ھ�һֱ�ƶ�
				}
			}
		}
		*/

	}
	return false;
}

