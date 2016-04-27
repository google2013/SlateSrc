// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "BuffMgr.h"

#include "Char/MyChar.h"
#include "Buffs/AbsBuff.h"
#include "Buffs/AppendBuff.h"
#include "Buffs/CommonBuff.h"
#include "../Utils/SkillDataMgr.h"
#include "../Template/BufflTemplate.h"


UBuffMgr::UBuffMgr() : Super()
{

}

UBuffMgr::~UBuffMgr()
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::~UBuffMgr"));
}

void UBuffMgr::BeginDestroy()
{
	for (auto iter = mBuffs.CreateIterator(); iter; ++iter)
	{
		for (auto tempBuff : iter->Value)
		{
			tempBuff->RemoveFromRoot();
			tempBuff->ConditionalBeginDestroy();
		}
		iter->Value.Empty();
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
			if (buff->IsRemoeve())
			{
				buff->BuffOver();
				buffs.RemoveAt(i);
			}
			else
			{
				buff->Tick(DeltaTime);//����buffer
			}
		}

		if (buffs.Num() == 0)
		{
			Iter.RemoveCurrent();
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

void UBuffMgr::AddBuff(int32 _attackId,int32 _targetId, int32 _skillId, int32 _buffId)
{
	UBufflTemplate* buffTemp = USkillDataMgr::GetInstance()->GetBuffTemplate(_buffId);
	if (buffTemp != nullptr)
	{
		UAbsBuff* beAdd = nullptr;
		if (buffTemp->mCanAdd) //����buff
		{
			beAdd = NewObject<UAppendBuff>(UAppendBuff::StaticClass());
		}
		else
		{
			beAdd = NewObject<UCommonBuff>(UCommonBuff::StaticClass());
		}
		beAdd->SetBuffTemp(buffTemp);

		TArray<UAbsBuff*>* buffs = mBuffs.Find(_targetId);
		if (buffs != nullptr)
		{
			UAbsBuff** buff = buffs->FindByPredicate([&](const UAbsBuff* _buff)->bool { return _buff->GetBuffId() == _buffId; });
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
					UAbsBuff* tmpBuff = *buff;
					tmpBuff->BuffOver();
					buffs->Remove(tmpBuff);//�ǳ���Ҫ��ɾ���Ǳ����*buff��ֵ��һ����ʱ���󣬲�Ȼ��ַ��鲻ͨ�����±���
					tmpBuff->RemoveFromRoot();
					tmpBuff->ConditionalBeginDestroy();

					beAdd->AddToRoot();
					beAdd->BuffStart();
					buffs->Add(beAdd);
				}
			}
			else
			{
				beAdd->AddToRoot();
				beAdd->BuffStart();
				buffs->Add(beAdd);
			}
		}
		else
		{
			beAdd->AddToRoot();
			beAdd->BuffStart();

			TArray<UAbsBuff*> tmpBuffs;
			tmpBuffs.Add(beAdd);
			mBuffs.Add(_targetId, tmpBuffs);
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
		for (UAbsBuff* buff : *buffs)
		{
			if (buff->GetBuffId() == _buffId)
				return buff;

		}
	}
	return nullptr;
}

//�Ƴ�ĳ����ɫ���ϵ�����buff
void UBuffMgr::RemoveBuff(int32 _charId, bool _exeBuffOver /* = false */)
{
	TArray<UAbsBuff*>* buffs = mBuffs.Find(_charId);
	if (buffs != nullptr)
	{
		for (UAbsBuff* buff : *buffs)
		{
			if (_exeBuffOver)
			{
				buff->BuffOver();
			}
			buff->RemoveFromRoot();
			buff->ConditionalBeginDestroy();
		}

		mBuffs.Remove(_charId);
	}
}

//�Ƴ�ĳ����ɫ���ϵ�ĳ������buff
void UBuffMgr::RemoveBuffSpec(int32 _charId, int32 _buffId, bool _exeBuffOver /* = false */)
{
	TArray<UAbsBuff*>* buffs = mBuffs.Find(_charId);
	if (buffs != nullptr)
	{
		for (UAbsBuff* buff : *buffs)
		{
			if (buff->GetBuffId() == _buffId)
			{
				if (_exeBuffOver)
				{
					buff->BuffOver();
				}
				buff->RemoveFromRoot();
				buff->ConditionalBeginDestroy();
				buffs->Remove(buff);
				break;
			}
		}

		if (buffs->Num() == 0) //��ɫ����buff�ƹ���
		{
			mBuffs.Remove(_charId);
		}
	}
}

void UBuffMgr::CharDeathNotify(AMyChar* _char)
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::CharDeathNotify, char death, uuid:%d"), _char->GetUuid());

	RemoveBuff(_char->GetUuid());
}
