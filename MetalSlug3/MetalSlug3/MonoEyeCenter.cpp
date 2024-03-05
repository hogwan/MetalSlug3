#include "MonoEyeCenter.h"
#include "Marco.h"

AMonoEyeCenter::AMonoEyeCenter()
{
}

AMonoEyeCenter::~AMonoEyeCenter()
{
}

void AMonoEyeCenter::BeginPlay()
{
	SetActorLocation(Center);

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

	ChangePattern(MonoEyesPattern::Pattern0);
}

void AMonoEyeCenter::Tick(float _DeltaTime)
{
	PatternUpdate(_DeltaTime);

	for (AMonoEyes* mono : MonoEyes)
	{
		mono->SetInitialPos(GetActorLocation());
	}
}

void AMonoEyeCenter::PatternUpdate(float _DeltaTime)
{
	switch (CurPattern)
	{
	case MonoEyesPattern::Pattern0:
		Pattern0(_DeltaTime);
		break;
	case MonoEyesPattern::Pattern1:
		Pattern1(_DeltaTime);
		break;
	case MonoEyesPattern::Pattern2:
		Pattern2(_DeltaTime);
		break;
	}
}

void AMonoEyeCenter::ChangePattern(MonoEyesPattern _Pattern)
{
	if (CurPattern != _Pattern)
	{
		switch (_Pattern)
		{
		case MonoEyesPattern::Pattern0:
			Pattern0Start();
			break;
		case MonoEyesPattern::Pattern1:
			Pattern1Start();
			break;
		case MonoEyesPattern::Pattern2:
			Pattern2Start();
			break;
		}
	}

	CurPattern = _Pattern;
}

void AMonoEyeCenter::Pattern0(float _DeltaTime)
{
	AccPattern += _DeltaTime;
	if (AccPattern > PatternCoolTime)
	{
		AccPattern = 0.0f;
		++turn;
		if (turn % 2 == 0)
		{
			ChangePattern(MonoEyesPattern::Pattern2);
		}
		else
		{
			ChangePattern(MonoEyesPattern::Pattern1);
		}
	}
}

void AMonoEyeCenter::Pattern1(float _DeltaTime)
{
	AccPattern += _DeltaTime;
	if (AccPattern > PatternCoolTime)
	{
		AccPattern = 0.0f;
		ChangePattern(MonoEyesPattern::Pattern0);
	}
}

void AMonoEyeCenter::Pattern2(float _DeltaTime)
{
	float XPlayerPos = UContentsHelper::Player->GetActorLocation().X;
	float Gap = Center.X - XPlayerPos;
	XTargetPosition = Center.X + Gap;

	AddActorLocation(FVector::Right * (XTargetPosition - GetActorLocation().X) * _DeltaTime);

	AccPattern += _DeltaTime;
	if (AccPattern > PatternCoolTime)
	{
		AccPattern = 0.0f;
		ChangePattern(MonoEyesPattern::Pattern0);
	}
}

void AMonoEyeCenter::Pattern0Start()
{
	SetActorLocation(Center);
	for (AMonoEyes* mono : MonoEyes)
	{
		mono->SetRatio({ 200,25 });
		mono->SetRotSpeed(UEngineMath::PI / 2.5f, UEngineMath::PI);
	}
}

void AMonoEyeCenter::Pattern1Start()
{
	SetActorLocation(Center);
	for (AMonoEyes* mono : MonoEyes)
	{
		mono->SetRatio({ 350,50 });
		mono->SetRotSpeed(UEngineMath::PI / 2.5f, UEngineMath::PI);
	}
}

void AMonoEyeCenter::Pattern2Start()
{
	for (AMonoEyes* mono : MonoEyes)
	{
		mono->SetRatio({ 100,25 });
		mono->SetRotSpeed(UEngineMath::PI / 2.5f, UEngineMath::PI);
	}
}
