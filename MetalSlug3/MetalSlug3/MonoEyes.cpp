#include "MonoEyes.h"
#include "Marco.h"
#include "DeathBall.h"
#include "MonoEyeCenter.h"
#include <EnginePlatform/EngineSound.h>

AMonoEyes::AMonoEyes()
{
	UEngineSound::SoundPlay("MonoEyes_Spawn.mp3");
}

AMonoEyes::~AMonoEyes()
{
	UEngineSound::SoundPlay("MonoEyes_Destroy.mp3");
}

void AMonoEyes::BeginPlay()
{
	AEnemy::BeginPlay();

	Hp = 40;

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->SetImage("MonoEyes_Death.png");
	Renderer->CreateAnimation("Spawn", "MonoEyes_Spawn.png", 0, 13, 0.03f, false);
	Renderer->CreateAnimation("Death", "MonoEyes_Death.png", 0, 7, 0.08, false);

	LaunchRenderer = CreateImageRenderer(MT3RenderOrder::Particle);
	LaunchRenderer->SetTransform({ LaunchEffectOffset, { 500,500 } });
	LaunchRenderer->SetImage("LaunchEffect.png");
	LaunchRenderer->CreateAnimation("Launch", "LaunchEffect.png", 0, 15, 0.05f, false);
	LaunchRenderer->ActiveOff();

	Collider = CreateCollision(MT3CollisionOrder::Boss);
	Collider->SetScale({ 100,300 });
	Collider->SetColType(ECollisionType::Rect);

	LaunchCoolTime = static_cast<float>(rand() % 20);

	Renderer->ChangeAnimation("Spawn", false, 0, 0.03f);
}

void AMonoEyes::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);

	if (!IsSpawn)
	{
		if (Renderer->IsCurAnimationEnd())
		{
			IsSpawn = true;
			Renderer->AnimationReset();
		}

		return;
	}

	float CurY = sinf(RotAngle);
	float CurX = cosf(RotAngle);
	float Vibration = sinf(VibAngle);

	if (CurY > 0.4f)
	{
		CurZPos = ZPos::Back;
		Renderer->SetTransform({ {0,0},{450,450} });

		AttachName = "Back_";
	}
	else if (CurY <= 0.4f && CurY >= -0.2f)
	{
		CurZPos = ZPos::Mid;
		Renderer->SetTransform({ {0,0},{480,480} });

		AttachName = "Mid_";
	}
	else if (CurY < -0.2f)
	{
		CurZPos = ZPos::Front;
		Renderer->SetTransform({ {0,0},{500,500} });

		AttachName = "Front_";
	}

	Idle(_DeltaTime);

	if (!MoveStart) return;

	RotAngle += XRotSpeed * _DeltaTime;
	VibAngle += YRotSpeed * _DeltaTime;
	// -1 ~ 1

	FVector YPos = FVector::Up * Ratio.Y * CurY;
	FVector XPos = FVector::Right * Ratio.X * CurX;
	FVector Vib = FVector::Up * amplitude * Vibration;
	
	InitialPosition;

	TargetPosition = InitialPosition + YPos + XPos + Vib;

	FVector MoveVector = TargetPosition - GetActorLocation();
	if (MoveVector.Size2D() > 5.0f)
	{
		MoveVector.Normalize2D();
		AddActorLocation(MoveVector * Speed * _DeltaTime);
	}
	else
	{
		SetActorLocation(TargetPosition);
	}


	if (AccLaunch > LaunchCoolTime)
	{
		LaunchOn();
		LaunchStart();
	}

	if (IsLaunch)
	{
		Launch(_DeltaTime);
	}
	else
	{
		AccLaunch += _DeltaTime;
	}


	if (Hp < 0 && !IsDeathStart)
	{
		DeathStart();
	}

	if (IsDeathStart)
	{
		Death(_DeltaTime);
	}
}
void AMonoEyes::Spawn(float _DeltaTime)
{
}

void AMonoEyes::Death(float _DeltaTime)
{
	Collider->ActiveOff();
	if(Renderer->IsCurAnimationEnd())
	{
		IsMonoDeath = true;
	}
}

void AMonoEyes::Idle(float _DeltaTime)
{
	FVector PlayerPos = UContentsHelper::Player->GetActorLocation();
	float XGap = GetActorLocation().X - PlayerPos.X;

	if (XGap > 0.0f)
	{
		LaunchEffectOffset = { -50,-180 };
		LaunchRenderer->SetTransform({ LaunchEffectOffset, { 500,500 } });
	}
	else
	{
		LaunchEffectOffset = { 50,-180 };
		LaunchRenderer->SetTransform({ LaunchEffectOffset, { 500,500 } });
	}

	if (CurZPos == ZPos::Front)
	{
		Renderer->SetOrder(MT3RenderOrder::MonoEye_Front);
	}
	else if (CurZPos == ZPos::Mid)
	{
		Renderer->SetOrder(MT3RenderOrder::MonoEye_Mid);
	}
	else
	{
		Renderer->SetOrder(MT3RenderOrder::MonoEye_Back);
	}


	if (CurZPos == ZPos::Back || CurZPos == ZPos::Mid)
	{
		if (XGap > 300.0f)
		{
			CurImageName = "Left_9.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 250.0f)
		{
			CurImageName = "Left_8.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 200.0f)
		{
			CurImageName = "Left_7.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 150.0f)
		{
			CurImageName = "Left_6.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 100.0f)
		{
			CurImageName = "Left_5.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 80.0f)
		{
			CurImageName = "Left_4.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 60.0f)
		{
			CurImageName = "Left_3.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 40.0f)
		{
			CurImageName = "Left_2.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 20.0f)
		{
			CurImageName = "Left_1.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 0.0f)
		{
			CurImageName = "Left_0.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -20.0f)
		{
			CurImageName = "Right_0.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -40.0f)
		{
			CurImageName = "Right_1.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -60.0f)
		{
			CurImageName = "Right_2.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -80.0f)
		{
			CurImageName = "Right_3.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -100.0f)
		{
			CurImageName = "Right_4.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -150.0f)
		{
			CurImageName = "Right_5.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -200.0f)
		{
			CurImageName = "Right_6.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -250.0f)
		{
			CurImageName = "Right_7.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -300.0f)
		{
			CurImageName = "Right_8.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else
		{
			CurImageName = "Right_9.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
	}
	else
	{
		if (XGap > 150.0f)
		{
			CurImageName = "Left_10.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 100.0f)
		{
			CurImageName = "Left_11.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 80.0f)
		{
			CurImageName = "Left_12.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 60.0f)
		{
			CurImageName = "Left_13.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 40.0f)
		{
			CurImageName = "Left_14.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 20.0f)
		{
			CurImageName = "Left_15.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 0.0f)
		{
			CurImageName = "Left_16.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -20.0f)
		{
			CurImageName = "Right_16.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -40.0f)
		{
			CurImageName = "Right_15.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -60.0f)
		{
			CurImageName = "Right_14.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -80.0f)
		{
			CurImageName = "Right_13.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -100.0f)
		{
			CurImageName = "Right_12.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -150.0f)
		{
			CurImageName = "Right_11.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else
		{
			CurImageName = "Right_10.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
	}
}

void AMonoEyes::Launch(float _DeltaTime)
{
	if (LaunchRenderer->IsCurAnimationEnd())
	{
		UEngineSound::SoundPlay("MonoEyes_DeathBallLaunch.mp3");

		LaunchRenderer->ActiveOff();
		IsLaunch = false;
		LaunchCoolTime = static_cast<float>(rand() % 20);
		
		FVector PlayerPos = UContentsHelper::Player->GetActorLocation();
		FVector SpawnLocation = GetActorLocation() + LaunchEffectOffset;

		ADeathBall* DeathBall = GetWorld()->SpawnActor<ADeathBall>();
		DeathBall->SetActorLocation(SpawnLocation);

		FVector DirVector = PlayerPos - GetActorLocation();
		DirVector.Normalize2D();

		DeathBall->SetDir(DirVector);
	}
}

void AMonoEyes::SpawnStart()
{
}

void AMonoEyes::DeathStart()
{
	IsDeathStart = true;
	Renderer->ChangeAnimation("Death", false, 0, 0.08f);
}

void AMonoEyes::LaunchStart()
{
	UEngineSound::SoundPlay("MonoEyes_DeathBallCharging.mp3");

	LaunchRenderer->ActiveOn();
	LaunchRenderer->ChangeAnimation("Launch", true, 0 , 0.05f);
}

void AMonoEyes::LaunchOn()
{
	IsLaunch = true;
	AccLaunch = 0.0f;
}
