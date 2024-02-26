#include "Helicopter.h"
#include "Marco.h"

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
	Renderer->CreateAnimation("Speed4_Right", "Helicopter.png", 0, 5, 0.08f, true);
	Renderer->CreateAnimation("Speed3_Right", "Helicopter.png", 6, 11, 0.08f, true);
	Renderer->CreateAnimation("Speed2_Right", "Helicopter.png", 12, 17, 0.08f, true);
	Renderer->CreateAnimation("Speed1_Right", "Helicopter.png", 18, 23, 0.08f, true);
	Renderer->CreateAnimation("Speed0_Right", "Helicopter.png", 24, 29, 0.08f, true);
	Renderer->CreateAnimation("Aiming2_Right", "Helicopter.png", 30, 35, 0.08f, true);
	Renderer->CreateAnimation("Aiming1_Right", "Helicopter.png", 36, 41, 0.08f, true);
	Renderer->CreateAnimation("Aiming0_Right", "Helicopter.png", 42, 47, 0.08f, true);

	Renderer->CreateAnimation("Speed4_Left", "Helicopter.png", 50, 55, 0.08f, true);
	Renderer->CreateAnimation("Speed3_Left", "Helicopter.png", 56, 61, 0.08f, true);
	Renderer->CreateAnimation("Speed2_Left", "Helicopter.png", 62, 67, 0.08f, true);
	Renderer->CreateAnimation("Speed1_Left", "Helicopter.png", 68, 73, 0.08f, true);
	Renderer->CreateAnimation("Speed0_Left", "Helicopter.png", 74, 79, 0.08f, true);
	Renderer->CreateAnimation("Aiming2_Left", "Helicopter.png", 80, 85, 0.08f, true);
	Renderer->CreateAnimation("Aiming1_Left", "Helicopter.png", 86, 91, 0.08f, true);
	Renderer->CreateAnimation("Aiming0_Left", "Helicopter.png", 92, 97, 0.08f, true);

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 100,100 });
	Collider->SetPosition({ 0,-100 });
	Collider->SetColType(ECollisionType::Rect);
}

void AHelicopter::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);
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
		switch (CurState)
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
	MoveVector.X = UContentsHelper::Player->GetActorLocation().X - GetActorLocation().X;
	AddActorLocation(MoveVector * _DeltaTime);

	if (MoveVector.X > 500.0f)
	{
		CurAnimName = "Speed4";
	}
	else if (MoveVector.X > 400.0f)
	{
		CurAnimName = "Speed3";
	}
	else if (MoveVector.X > 300.0f)
	{
		CurAnimName = "Speed2";
	}
	else if (MoveVector.X > 200.0f)
	{
		CurAnimName = "Speed1";
	}
	else
	{
		CurAnimName = "Speed0";
	}
	DirCheck();
}

void AHelicopter::Aiming(float _DeltaTime)
{
}

void AHelicopter::NoneStart()
{
}

void AHelicopter::MoveStart()
{
}

void AHelicopter::AimingStart()
{
}

void AHelicopter::DirCheck()
{
	std::string DirCheckedName = CurAnimName;
	if (MoveVector.X < 0.0f)
	{
		DirCheckedName += "_Left";
	}
	else
	{
		DirCheckedName += "_Right";
	}

	int CurFrame = Renderer->GetCurAnimationFrame();
	Renderer->ChangeAnimation(DirCheckedName, false, CurFrame, 0.08f);
}
