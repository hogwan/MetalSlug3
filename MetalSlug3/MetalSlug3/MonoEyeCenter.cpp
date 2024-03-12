#include "MonoEyeCenter.h"
#include "Marco.h"

std::list<AMonoEyes*> AMonoEyeCenter::MonoEyes;
std::vector<FVector> AMonoEyeCenter::MonoEyeInitPosInfo = {
		FVector{14070,2100},
		FVector{14230,2100},
		FVector{14340,2100},
		FVector{14230,2100},
		FVector{14070,2100},
		FVector{13950,2100}
};

std::vector<FVector> AMonoEyeCenter::MonoEyeFirstTargetPosInfo = {
	FVector{13950,1920},
	FVector{14400,1920},
	FVector{14000,1920},
	FVector{14440,1920},
	FVector{14060,1920},
	FVector{14130,1920}
};

std::vector<float> AMonoEyeCenter::MonoEyeInitRotInfo = {
	(UEngineMath::PI / 3.0f) * 4.f,
	(UEngineMath::PI / 3.0f) * 5.f,
	(UEngineMath::PI / 3.0f) * 0.f,
	(UEngineMath::PI / 3.0f) * 1.f,
	(UEngineMath::PI / 3.0f) * 2.f,
	(UEngineMath::PI / 3.0f) * 3.f
};

std::vector<float> AMonoEyeCenter::MonoEyeInitVibInfo = {
	(UEngineMath::PI) * 0.f,
	(UEngineMath::PI) * 1.f,
	(UEngineMath::PI) * 2.f,
	(UEngineMath::PI) * 3.f,
	(UEngineMath::PI) * 4.f,
	(UEngineMath::PI) * 5.f
};

int AMonoEyeCenter::MonoEyeSpawnCount = 0;

AMonoEyeCenter::AMonoEyeCenter()
{
}

AMonoEyeCenter::~AMonoEyeCenter()
{
}

void AMonoEyeCenter::BeginPlay()
{
	SetActorLocation(Center);
}

void AMonoEyeCenter::Tick(float _DeltaTime)
{
	std::list<AMonoEyes*>::iterator iter = MonoEyes.begin();
	for (; iter != MonoEyes.end();)
	{
		if ((*iter)->GetIsDeath())
		{
			(*iter)->Destroy();
			iter = MonoEyes.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	if (PatternStart && !Trigger)
	{
		for (AMonoEyes* mono : MonoEyes)
		{
			mono->MoveStart = true;
		}

		ChangePattern(MonoEyesPattern::Pattern0);
		Trigger = true;
	}



	for (AMonoEyes* mono : MonoEyes)
	{
		mono->SetInitialPos(GetActorLocation());
	}

	
	if (PatternStart == true)
	{
		PatternUpdate(_DeltaTime);
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
