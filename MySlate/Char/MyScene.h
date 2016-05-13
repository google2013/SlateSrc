
#pragma once

#include "./BehavInter.h"
#include "../Common/ISingleton.h"

#include "MyScene.generated.h"

/*
����actor����������Ч��������񶯵�
*/

UCLASS()
class AMyScene : public AActor, public IBehavInterface, public USingleton<AMyScene>
{
	GENERATED_BODY()

public:	
	AMyScene();
	virtual ~AMyScene();

	// Begin Actor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;
	// End Actor interface

public:
	ACameraActor*		mCameraActor;
};
