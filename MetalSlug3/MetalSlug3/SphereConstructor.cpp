#include "SphereConstructor.h"
#include "UnknownSphere.h"
#include "MonoEyes.h"
#include "MonoEyeCenter.h"

ASphereConstructor::ASphereConstructor()
{
}

ASphereConstructor::~ASphereConstructor()
{
}

void ASphereConstructor::BeginPlay()
{
	SetActorLocation({ 14155,2270 });
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

	if (FirstStep == false)
	{
		FVector Gap = FirstTarget - GetActorLocation();

		if (Gap.Size2D() < 10.f)
		{
			FirstStep = true;
		}

		AddActorLocation(Gap * 2.0f * _DeltaTime);
	}

	if (FirstStep == true && SecondStep == false)
	{
		FVector Gap = SecondTarget - GetActorLocation();

		if (Gap.Size2D() < 1.f)
		{
			AMonoEyes* mono = GetWorld()->SpawnActor<AMonoEyes>();
			mono->SetActorLocation(GetActorLocation());
			mono->SetRotAngle(AMonoEyeCenter::MonoEyeInitRotInfo[AMonoEyeCenter::MonoEyeSpawnCount]);
			mono->SetVibAngle(AMonoEyeCenter::MonoEyeInitVibInfo[AMonoEyeCenter::MonoEyeSpawnCount]);
			AMonoEyeCenter::MonoEyes.push_back(mono);
			++AMonoEyeCenter::MonoEyeSpawnCount;

			Destroy();
		}

		AddActorLocation(Gap * 5.0f * _DeltaTime);
	}
}

