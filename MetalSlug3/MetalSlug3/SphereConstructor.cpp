#include "SphereConstructor.h"
#include "UnknownSphere.h"

ASphereConstructor::ASphereConstructor()
{
}

ASphereConstructor::~ASphereConstructor()
{
}

void ASphereConstructor::BeginPlay()
{

}

void ASphereConstructor::Tick(float _DeltaTime)
{
	AccSpawnTime += _DeltaTime;
	if (AccSpawnTime > SpawnCoolTime)
	{
		AccSpawnTime = 0.0f;
		AUnknownSphere* Sphere = GetWorld()->SpawnActor<AUnknownSphere>();
		Sphere->SetActorLocation(GetActorLocation());
	}

	if (ClockDir)
	{

	}
	else
	{
		
	}
}
