#include "MySlate.h"
#include "SolusDataSingleton.h"

#include "Engine.h"
#include "Engine/StreamableManager.h"
#include "Singleton/SolusDataSingleton.h"
#include "Singleton/ItemInfoDatabase.h"

USolusDataSingleton::USolusDataSingleton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SolusCoreFilePath = "I am Mr. Yang"; //��ʼ��������������������������ͼ�г�ʼ��
	SolusEssentialVector = FVector(900, 800, 700);
	AssetLoader = new FStreamableManager();

	//����itemDataBase��ͼ
	UObject* obj = AssetLoader->SynchronousLoad(FStringAssetReference(TEXT("/Game/TopDownCPP/MeshItems/MeshDateBaseBP")));
	ItemDatabase = Cast<UItemInfoDatabase>(obj);
}

USolusDataSingleton::~USolusDataSingleton()
{
	if (AssetLoader)
		delete AssetLoader;
}

USolusDataSingleton* USolusDataSingleton::Get()
{
	USolusDataSingleton* DataInstance = Cast<USolusDataSingleton>(GEngine->GameSingleton); //����ָ�������ļ���ָ���ĵ�����
	if (!DataInstance)
		return nullptr;
	else
		return DataInstance;
}
