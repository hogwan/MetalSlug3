#include "MT3Object.h"

AMT3Object::AMT3Object()
{
}

AMT3Object::~AMT3Object()
{
}

void AMT3Object::BeginPlay()
{
	AActor::BeginPlay();
}

void AMT3Object::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	Release();
}

void AMT3Object::Release()
{
	FVector Pos = GetActorLocation();
	if (GetActorLocation().X < GetWorld()->GetCameraPos().X - 300.0f
		 || GetActorLocation().X > GetWorld()->GetCameraPos().X + 1800.0f)
	{
		Destroy();
	}
}
