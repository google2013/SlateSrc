#include "MySlate.h"
#include "SolusDataSingleton.h"

#include "Engine.h"

USolusDataSingleton::USolusDataSingleton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SolusCoreFilePath = "I am Mr. Yang"; //��ʼ��������������������������ͼ�г�ʼ��
	SolusEssentialVector = FVector(900, 800, 700);
}

USolusDataSingleton* USolusDataSingleton::Get()
{
	USolusDataSingleton* DataInstance = Cast<USolusDataSingleton>(GEngine->GameSingleton); //����ָ�������ļ���ָ���ĵ�����
	if (!DataInstance)
		return nullptr;
	else
		return DataInstance;
}
