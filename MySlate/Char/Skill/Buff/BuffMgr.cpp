
#include "MySlate.h"
#include "BuffMgr.h"

#include "../../MyChar.h"
#include "./Buffs/AbsBuff.h"
#include "./Buffs/AppendBuff.h"
#include "./Buffs/CommonBuff.h"
#include "../SkillMgr.h"
#include "../Template/BufflTemplate.h"
#include "../SkillTypes.h"
#include "../../Object/ObjMgr.h"

UBuffMgr::UBuffMgr() : Super()
{

}

UBuffMgr::~UBuffMgr()
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::~UBuffMgr"));
}

void UBuffMgr::BeginDestroy()
{
	for (auto Iter = mBuffs.CreateIterator(); Iter; ++Iter)
	{
		for (UAbsBuff* tempBuff : Iter->Value)
		{
			tempBuff->RemoveFromRoot();
			tempBuff->ConditionalBeginDestroy();
		}
		Iter->Value.Empty();
	}
	mBuffs.Empty();

	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::BeginDestroy"));
	Super::BeginDestroy();
}

void UBuffMgr::Tick(float DeltaTime)
{
	UAbsBuff* buff = nullptr;
	for (auto Iter = mBuffs.CreateIterator(); Iter; ++Iter)
	{
		TArray<UAbsBuff*>&	buffs = Iter->Value;
		for (int32 i = 0;i < buffs.Num(); i++)
		{
			buff = buffs[i];
			if (buff->GetState() == EBuffState::Start)
			{
				buff->Tick(DeltaTime);//����buffer
			}
			else if (buff->GetState() == EBuffState::Over
				|| buff->GetState() == EBuffState::Break) //Break��ʱ����
			{
				ForceOver(buffs, buff);
				if (buffs.Num() == 0)
				{
					Iter.RemoveCurrent();
				}
			}
		}
	}
}

bool UBuffMgr::IsTickable() const
{
	return true;
}

TStatId UBuffMgr::GetStatId() const
{
	return TStatId();
}

void UBuffMgr::RunBeforePkBuffs(int32 _charId, UPkMsg* msg)
{

}

void UBuffMgr::RunEndPkBuffs(int32 _charId, UPkMsg* msg)
{

}

void UBuffMgr::AddBuff(AMyChar* _attacker, AMyChar* _target, int32 _skillId, int32 _buffId)
{
	UBufflTemplate* buffTemp = USkillMgr::GetInstance()->GetBuffTemplate(_buffId);
	if (buffTemp != nullptr && _target != nullptr)
	{
		int32 targetId = _target->GetUuid();
		UAbsBuff* beAdd = nullptr;
		if (buffTemp->mCanAdd) //����buff
		{
			beAdd = GetObjMgr()->GetObj<UAppendBuff>(GetObjMgr()->mAppBuffCls);
		}
		else
		{
			beAdd = GetObjMgr()->GetObj<UCommonBuff>(GetObjMgr()->mComBuffCls);
		}
		beAdd->SetData(buffTemp, _attacker, _target, _skillId);

		TArray<UAbsBuff*>* buffs = mBuffs.Find(targetId);
		if (buffs != nullptr)
		{
			UAbsBuff** buff = buffs->FindByPredicate([&](const UAbsBuff* _buff)->bool {
				return _buff->GetBuffId() == _buffId; 
			});

			if (buff != nullptr)//ԭ���Ѵ������buffId
			{
				UAppendBuff* appBuff = Cast<UAppendBuff>(*buff);
				if (appBuff != nullptr)//���ڵ�buff��׺�ӵģ���׺�����ݶ�����ȥ���ͷ��´�����
				{
					appBuff->AppendBuff(beAdd);
					beAdd->ConditionalBeginDestroy(); 
				}
				else //����׺�ӣ�ȥ��ӭ��
				{
					(*buff)->ChangeState(EBuffState::Over);

					beAdd->BuffStart();
					buffs->Add(beAdd);
				}
			}
			else
			{
				beAdd->BuffStart();
				buffs->Add(beAdd);
			}
		}
		else
		{
			beAdd->BuffStart();

			TArray<UAbsBuff*> tmpBuffs;
			tmpBuffs.Add(beAdd);
			mBuffs.Add(targetId, tmpBuffs);
		}
	}
	else
	{
		UE_LOG(BuffLogger, Error, TEXT("--- UBuffMgr::AddBuff, buff template == nullptr, id:%d"), _buffId);
	}
}

UAbsBuff* UBuffMgr::FindBuff(int32 _charId, int32 _buffId)
{
	TArray<UAbsBuff*>* buffs = mBuffs.Find(_charId);
	if (buffs != nullptr)
	{
		UAbsBuff** buff = buffs->FindByPredicate([&](const UAbsBuff* _buff)->bool {
			return _buff->GetBuffId() == _buffId; 
		});

		return buff != nullptr ? *buff : nullptr;
	}
	return nullptr;
}

void UBuffMgr::ForceOver(TArray<UAbsBuff*>& _buffArr, UAbsBuff* _buff)
{
	_buff->BuffOver();
	_buff->Recycle();
	_buffArr.Remove(_buff);
}

//�Ƴ�ĳ����ɫ���ϵ�����buff
void UBuffMgr::RemoveBuff(int32 _charId)
{
	TArray<UAbsBuff*>* buffs = mBuffs.Find(_charId);
	if (buffs != nullptr)
	{
		for (UAbsBuff* buff : *buffs)
		{
			ForceOver(*buffs, buff);
		}
		mBuffs.Remove(_charId);
	}
}

//�Ƴ�ĳ����ɫ���ϵ�ĳ������buff
void UBuffMgr::RemoveBuffSpec(int32 _charId, int32 _buffId)
{
	TArray<UAbsBuff*>* buffs = mBuffs.Find(_charId);
	if (buffs != nullptr)
	{
		UAbsBuff** buff = buffs->FindByPredicate([&](const UAbsBuff* _buff)->bool {
			return _buff->GetBuffId() == _buffId; 
		});

		if (buff != nullptr)
		{
			ForceOver(*buffs, *buff);
			if (buffs->Num() == 0)
			{
				mBuffs.Remove(_charId);
			}
			UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::RemoveBuffSpec, buffId:%d"), (*buff)->GetBuffId());
		}
	}
}

void UBuffMgr::CharDeathNotify(AMyChar* _char)
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::CharDeathNotify, char death, uuid:%d"), _char->GetUuid());

	RemoveBuff(_char->GetUuid());
}
