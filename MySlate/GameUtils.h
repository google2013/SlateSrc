
#pragma once

#include "GameUtils.generated.h"

//UEmptyֻ��Ϊ������������࣬����FString
UCLASS()
class UEmptyObj : public UObject
{
	GENERATED_BODY()

public:
	UEmptyObj() {}
	virtual ~UEmptyObj() {}
};

//#define  Split_Com		TEXT(",")
#define  Split_Line		TEXT("_")
#define  Split_Pound	TEXT("#")
#define  Split_Sem		TEXT(";")

template<typename Type>
static FString GetEnumAsString(FString _name, Type _value) //�����Ӧ��enumֵ
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *_name, true);
	if (!EnumPtr) return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

	return EnumPtr->GetDisplayNameText((int32)_value).ToString();
}