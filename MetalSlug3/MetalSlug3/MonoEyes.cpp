#include "MonoEyes.h"
#include "Marco.h"
#include "DeathBall.h"

AMonoEyes::AMonoEyes()
{
}

AMonoEyes::~AMonoEyes()
{
}

void AMonoEyes::BeginPlay()
{
	AEnemy::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0},{500,500} });

	LaunchRenderer = CreateImageRenderer(MT3RenderOrder::Particle);
	LaunchRenderer->SetTransform({ LaunchEffectOffset, { 500,500 } });
	LaunchRenderer->SetImage("LaunchEffect.png");
	LaunchRenderer->CreateAnimation("Launch", "LaunchEffect.png", 0, 15, 0.05f, false);
	LaunchRenderer->ActiveOff();

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 100,300 });
	Collider->SetPosition({ 0,-150 });
	Collider->SetColType(ECollisionType::Rect);

	SetActorLocation({ 14150,2050 });
	InitialPosition = { 14150,2050 };

	LaunchCoolTime = static_cast<float>(rand() % 20);
}

void AMonoEyes::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);

	RotAngle += XRotSpeed * _DeltaTime;
	VibAngle += YRotSpeed * _DeltaTime;
	// -1 ~ 1
	float CurY = sinf(RotAngle);
	float CurX = cosf(RotAngle);
	float Vibration = sinf(VibAngle);

	FVector YPos = FVector::Up * Ratio.Y * CurY;
	FVector XPos = FVector::Right * Ratio.X * CurX;
	FVector Vib = FVector::Up * amplitude * Vibration;
	
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
	else if(CurY < -0.2f)
	{
		CurZPos = ZPos::Front;
		Renderer->SetTransform({ {0,0},{500,500} });

		AttachName = "Front_";
	}

	Idle(_DeltaTime);


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


	if (Hp < 0)
	{
		DeathStart();
	}

	if (IsDeath)
	{
		Death(_DeltaTime);
	}

	if (IsSpawn)
	{
		Spawn(_DeltaTime);
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
		Destroy();
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
}

void AMonoEyes::LaunchStart()
{
	LaunchRenderer->ActiveOn();
	LaunchRenderer->ChangeAnimation("Launch", true, 0 , 0.05f);
}

void AMonoEyes::LaunchOn()
{
	IsLaunch = true;
	AccLaunch = 0.0f;
}
