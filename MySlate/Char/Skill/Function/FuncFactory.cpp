// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "FuncFactory.h"
#include "../Utils/CommonDef.h"
#include "Funcs/AbsPkEvent.h"
#include "Funcs/AttackPhy.h"
#include "Funcs/Suckup.h"
#include "Funcs/AddBuff.h"
#include "../Filter/AbsFilter.h"
#include "../Filter/LockFilter.h"
#include "../Filter/CircleFilter.h"

UFuncFactory::UFuncFactory() : Super()
{

}

UFuncFactory::~UFuncFactory()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UFuncFactory::~UFuncFactory"));
}

void UFuncFactory::BeginDestroy()
{
	//���ݶ��ظ�gc
	for (auto iter = mFunctionMap.CreateConstIterator(); iter; ++iter)
	{
		iter->Value->RemoveFromRoot();
		iter->Value->ConditionalBeginDestroy();
	}
	mFunctionMap.Empty();

	for (auto iter = mFilterMap.CreateConstIterator(); iter; ++iter)
	{
		iter->Value->RemoveFromRoot();
		iter->Value->ConditionalBeginDestroy();
	}
	mFilterMap.Empty();

	UE_LOG(SkillLogger, Warning, TEXT("--- UFuncFactory::BeginDestroy"));
	Super::BeginDestroy();
}

//����ע��ģ��
void UFuncFactory::InitFuncAndFilters()
{
	//------------ ѡ�� Start ------------
	registerFilter(ULockFilter::CreateFilter(Filter_Lock));
	registerFilter(UCircleFilter::CreateFilter(Filter_Circle));
	
	//------------ ѡ�� End ------------

	//------------ ���� Start ------------
	registerFunction(UAttackPhy::CreateFunction(Func_AttackPhy));
	registerFunction(UAddBuff::CreateFunction(Func_AddBuff));
	//------------ ���� End ------------

	//------------ ���� Start ------------
	registerFunction(USuckup::CreateFunction(Func_Suckhp));
	//------------ ���� End ------------
}

void UFuncFactory::registerFunction(UAbsPkEvent* _object)
{
	FString key = _object->GetKey();
	UAbsPkEvent** func = mFunctionMap.Find(key);
	if (func != nullptr)
	{
		return;
	}
	_object->AddToRoot();
	mFunctionMap.Add(key, _object);
}

void UFuncFactory::registerFilter(UAbsFilter* _object)
{
	FString key = _object->GetKey();
	UAbsFilter** filter = mFilterMap.Find(key);
	if (filter != nullptr)
	{
		return;
	}
	_object->AddToRoot();
	mFilterMap.Add(key, _object);
}

UAbsFilter* UFuncFactory::createFilter(const FString& _str)
{
	FString paramStr = _str.ToLower();
	TArray<FString> params;
	paramStr.ParseIntoArray(params, Split_Line, true);
	if (params.Num() > 0)
	{
		const FString clsName = params[0];
		UAbsFilter** filter = mFilterMap.Find(clsName);
		if (filter == nullptr)
		{
			UE_LOG(SkillLogger, Error, TEXT("--- Error: UFuncFactory::createFilter, return null"));
			return nullptr;
		}

		*filter = (*filter)->Clone();
		if (*filter == nullptr)
		{
			UE_LOG(SkillLogger, Error, TEXT("--- Error: UFuncFactory::createFilter, clone null"));
			return nullptr;
		}

		params.RemoveAt(0); //�Ƴ�������
		(*filter)->Parser(params);
		return *filter;
	}
	return nullptr;
}

UAbsPkEvent* UFuncFactory::createFunction(const FString& _str)
{
	FString paramStr = _str.ToLower();
	TArray<FString> params;
	paramStr.ParseIntoArray(params, Split_Line, true);
	if (params.Num() > 0)
	{
		const FString clsName = params[0];
		UAbsPkEvent** func = mFunctionMap.Find(clsName);
		if (func == nullptr)
		{
			UE_LOG(SkillLogger, Error, TEXT("--- Error: UFuncFactory::createFunction, return null"));
			return nullptr;
		}

		*func = (*func)->Clone();
		if (*func == nullptr)
		{
			UE_LOG(SkillLogger, Error, TEXT("--- Error: UFuncFactory::createFunction, clone null"));
			return nullptr;
		}

		params.RemoveAt(0); //�Ƴ�������
		(*func)->Parser(params);
		return *func;
	}
	return nullptr;
}
