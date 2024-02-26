#include "Helicopter.h"
#include "Marco.h"
#include "HelicopterBullet.h"

AHelicopter::AHelicopter()
{
}

AHelicopter::~AHelicopter()
{
}


void AHelicopter::BeginPlay()
{
	AEnemy::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0}, {500,500} });
	Renderer->SetImage("Helicopter.png");
	Renderer->CreateAnimation("Speed1_Right", "Helicopter.png", 0, 5, 0.08f, true);
	Renderer->CreateAnimation("Speed2_Right", "Helicopter.png", 6, 11, 0.08f, true);
	Renderer->CreateAnimation("Speed3_Right", "Helicopter.png", 12, 17, 0.08f, true);
	Renderer->CreateAnimation("Speed4_Right", "Helicopter.png", 18, 23, 0.08f, true);
	Renderer->CreateAnimation("Speed5_Right", "Helicopter.png", 24, 29, 0.08f, true);
	Renderer->CreateAnimation("Speed0_Right", "Helicopter.png", 30, 35, 0.08f, true);
	Renderer->CreateAnimation("Aiming1_Right", "Helicopter.png", 36, 41, 0.08f, true);
	Renderer->CreateAnimation("Aiming0_Right", "Helicopter.png", 42, 47, 0.08f, true);

	Renderer->CreateAnimation("Speed1_Left", "Helicopter.png", 60, 65, 0.08f, true);
	Renderer->CreateAnimation("Speed2_Left", "Helicopter.png", 66, 71, 0.08f, true);
	Renderer->CreateAnimation("Speed3_Left", "Helicopter.png", 72, 77, 0.08f, true);
	Renderer->CreateAnimation("Speed4_Left", "Helicopter.png", 78, 83, 0.08f, true);
	Renderer->CreateAnimation("Speed5_Left", "Helicopter.png", 84, 89, 0.08f, true);
	Renderer->CreateAnimation("Speed0_Left", "Helicopter.png", 90, 95, 0.08f, true);
	Renderer->CreateAnimation("Aiming1_Left", "Helicopter.png", 96, 101, 0.08f, true);
	Renderer->CreateAnimation("Aiming0_Left", "Helicopter.png", 102, 107, 0.08f, true);

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 100,100 });
	Collider->SetPosition({ 0,-100 });
	Collider->SetColType(ECollisionType::Rect);

	StateChange(HelicopterState::Move);
	Renderer->ChangeAnimation("Speed4_Right");
}

void AHelicopter::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void AHelicopter::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case HelicopterState::None:
		None(_DeltaTime);
		break;
	case HelicopterState::Move:
		Move(_DeltaTime);
		break;;
	case HelicopterState::Aiming:
		Aiming(_DeltaTime);
		break;
	}
}

void AHelicopter::StateChange(HelicopterState _State)
{
	if (CurState != _State)
	{
		switch (_State)
		{
		case HelicopterState::None:
			NoneStart();
			break;
		case HelicopterState::Move:
			MoveStart();
			break;;
		case HelicopterState::Aiming:
			AimingStart();
			break;
		}
	}
	CurState = _State;
}

void AHelicopter::None(float _DeltaTime)
{
	StateChange(HelicopterState::Move);
	return;
}

void AHelicopter::Move(float _DeltaTime)
{

	FVector Offset = { 0,-300 };
	TargetVector = (UContentsHelper::Player->GetActorLocation() + Offset) - GetActorLocation();
	MoveVector = TargetVector;
	AddActorLocation(MoveVector * _DeltaTime);

	if (MoveVector.Size2D() > 300.0f)
	{
		CurAnimName = "Speed5";
	}
	else if (MoveVector.Size2D() > 250.0f)
	{
		CurAnimName = "Speed4";
	}
	else if (MoveVector.Size2D() > 200.0f)
	{
		CurAnimName = "Speed3";
	}
	else if (MoveVector.Size2D() > 150.0f)
	{
		CurAnimName = "Speed2";
	}
	else if (MoveVector.Size2D() > 100.0f)
	{
		CurAnimName = "Speed1";
	}
	else
	{
		CurAnimName = "Speed0";
	}
	DirCheck();

	FVector AimVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
	AimVector.Normalize2D();

	if (abs(AimVector.X) < 0.58f)
	{
		AccMove = 0.0f;
		StateChange(HelicopterState::Aiming);
		return;
	}
	/*0.7764580943901145744254063635837(69,56)

	0.57993129338951082900686700669849(42,59)

	0.16598207031014622822993720684492 (16,102)*/
}

void AHelicopter::Aiming(float _DeltaTime)
{
	AccAiming += _DeltaTime;
	FVector AimVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
	AimVector.Normalize2D();

	if (abs(AimVector.X) < 0.17f)
	{
		CurAnimName = "Aiming0";
	}
	else if (abs(AimVector.X) < 0.58f)
	{
		CurAnimName = "Aiming1";
	}
	else
	{
		AccMove += _DeltaTime;
		if (AccMove > MoveCoolDown)
		{
			AccMove = 0.0f;
			StateChange(HelicopterState::Move);
			return;
		}
	}

	DirCheck();

	if (AccAiming > ShootCoolDown && Bullet > 0)
	{
		AHelicopterBullet* BulletPtr = GetWorld()->SpawnActor<AHelicopterBullet>();
		BulletPtr->SetDir(AimVector);
		BulletPtr->SetActorLocation(GetActorLocation());
		--Bullet;

		AccAiming = 0.0f;
		if (Bullet <= 0)
		{
			Bullet = 3;
		}
	}
}

void AHelicopter::NoneStart()
{
}

void AHelicopter::MoveStart()
{
	TargetVector = (UContentsHelper::Player->GetActorLocation() + Offset) - GetActorLocation();
	MoveVector.X = TargetVector.X / 2.0f;
	if (abs(MoveVector.X) > 300.0f)
	{
		CurAnimName = "Speed5";
	}
	else if (abs(MoveVector.X) > 250.0f)
	{
		CurAnimName = "Speed4";
	}
	else if (abs(MoveVector.X) > 200.0f)
	{
		CurAnimName = "Speed3";
	}
	else if (abs(MoveVector.X) > 150.0f)
	{
		CurAnimName = "Speed2";
	}
	else if (abs(MoveVector.X) > 100.0f)
	{
		CurAnimName = "Speed1";
	}
	else
	{
		CurAnimName = "Speed0";
	}
	DirCheck();
}

void AHelicopter::AimingStart()
{
}

void AHelicopter::DirCheck()
{
	FVector AimVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
	AimVector.Normalize2D();
	std::string DirCheckedName = CurAnimName;
	if (AimVector.X < 0.0f)
	{
		DirCheckedName += "_Left";
	}
	else
	{
		DirCheckedName += "_Right";
	}

	if (nullptr == Renderer->GetCurAnimation())
	{
		Renderer->ChangeAnimation(DirCheckedName, false, 0, 0.08f);
	}
	else
	{
		int CurFrame = Renderer->GetCurAnimationFrame();
		Renderer->ChangeAnimation(DirCheckedName, false, CurFrame, 0.08f);
	}
}
