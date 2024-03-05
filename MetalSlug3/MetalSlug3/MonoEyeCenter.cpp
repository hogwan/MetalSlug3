#include "MonoEyeCenter.h"

AMonoEyeCenter::AMonoEyeCenter()
{
}

AMonoEyeCenter::~AMonoEyeCenter()
{
}

void AMonoEyeCenter::BeginPlay()
{

	AMonoEyes* Mono0 = GetWorld()->SpawnActor<AMonoEyes>();
	Mono0->SetActorLocation({ 14200,2100 });

	AMonoEyes* Mono1 = GetWorld()->SpawnActor<AMonoEyes>();
	Mono1->SetActorLocation({ 14100,2100 });

	AMonoEyes* Mono2 = GetWorld()->SpawnActor<AMonoEyes>();
	Mono2->SetActorLocation({ 14200,2100 });

	AMonoEyes* Mono3 = GetWorld()->SpawnActor<AMonoEyes>();
	Mono3->SetActorLocation({ 14300,2100 });

	AMonoEyes* Mono4 = GetWorld()->SpawnActor<AMonoEyes>();
	Mono4->SetActorLocation({ 14200,2100 });

	AMonoEyes* Mono5 = GetWorld()->SpawnActor<AMonoEyes>();
	Mono5->SetActorLocation({ 14100,2100 });


	Mono0->SetRotAngle((UEngineMath::PI / 3.0f) * 0.f);
	Mono1->SetRotAngle((UEngineMath::PI / 3.0f) * 1.f);
	Mono2->SetRotAngle((UEngineMath::PI / 3.0f) * 2.f);
	Mono3->SetRotAngle((UEngineMath::PI / 3.0f) * 3.f);
	Mono4->SetRotAngle((UEngineMath::PI / 3.0f) * 4.f);
	Mono5->SetRotAngle((UEngineMath::PI / 3.0f) * 5.f);

	Mono0->SetVibAngle((UEngineMath::PI) * 0.f);
	Mono1->SetVibAngle((UEngineMath::PI) * 1.f);
	Mono2->SetVibAngle((UEngineMath::PI) * 2.f);
	Mono3->SetVibAngle((UEngineMath::PI) * 3.f);
	Mono4->SetVibAngle((UEngineMath::PI) * 4.f);
	Mono5->SetVibAngle((UEngineMath::PI) * 5.f);

	MonoEyes.push_back(Mono0);
	MonoEyes.push_back(Mono1);
	MonoEyes.push_back(Mono2);
	MonoEyes.push_back(Mono3);
	MonoEyes.push_back(Mono4);
	MonoEyes.push_back(Mono5);

	for (AMonoEyes* mono : MonoEyes)
	{
		mono->SetRatio({ 200,25 });
	}
}

void AMonoEyeCenter::Tick(float _DeltaTime)
{
	
}
