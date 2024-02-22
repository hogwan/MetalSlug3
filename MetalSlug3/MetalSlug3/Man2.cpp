#include "Man2.h"
#include "ManZombie2.h"

AMan2::AMan2()
{
}

AMan2::~AMan2()
{
}

void AMan2::BeginPlay()
{
	AHuman::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("Man2.png");
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->CreateAnimation("Move", "Man2.png", 0, 11, 0.08f, true);
	Renderer->CreateAnimation("Run", "Man2.png", 12, 15, 0.15f, true);
	Renderer->CreateAnimation("Death", "Man2.png", 16, 32, 0.15f, false);

	Collider = CreateCollision(MT3CollisionOrder::Player);
	Collider->SetScale(CollisionScale);
	Collider->SetPosition(CollisionPosition);
	Collider->SetColType(ECollisionType::Rect);
}

void AMan2::Tick(float _DeltaTime)
{
	AHuman::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::ZombieProjectile, Result))
	{
		IsDeath = true;
	}

	if (IsDeath)
	{
		StateChange(HumanState::Death);
	}

	StateUpdate(_DeltaTime);
}

void AMan2::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case HumanState::None:
		None(_DeltaTime);
		break;
	case HumanState::Move:
		Move(_DeltaTime);
		break;
	case HumanState::Run:
		Run(_DeltaTime);
		break;
	case HumanState::Death:
		Death(_DeltaTime);
		break;
	default:
		break;
	}
}

void AMan2::StateChange(HumanState _State)
{
	if (_State != CurState)
	{
		switch (_State)
		{
		case HumanState::None:
			NoneStart();
			break;
		case HumanState::Move:
			MoveStart();
			break;
		case HumanState::Run:
			RunStart();
			break;
		case HumanState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}

	CurState = _State;
}

void AMan2::None(float _DeltaTime)
{
	StateChange(HumanState::Idle);
}

void AMan2::Move(float _DeltaTime)
{
	AddActorLocation(FVector::Left * MoveSpeed * _DeltaTime);
	std::vector<UCollision*> Result;
	if (DetectCollider->CollisionCheck(MT3CollisionOrder::Enemy, Result))
	{
		StateChange(HumanState::Run);
	}
}

void AMan2::Run(float _DeltaTime)
{
	AddActorLocation(FVector::Left * RunSpeed * _DeltaTime);
}

void AMan2::Death(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		AManZombie2* Zombie = GetWorld()->SpawnActor<AManZombie2>();
		Zombie->SetActorLocation(GetActorLocation());
		Zombie->StateChange(EnemyZombieState::Lying);
		Destroy();
	}
}

void AMan2::NoneStart()
{
}

void AMan2::MoveStart()
{
	Renderer->ChangeAnimation("Move", false, 0, 0.08f);
}

void AMan2::RunStart()
{
	RunSpeed = 35.0f;
	Renderer->ChangeAnimation("Run", false, 0, 0.08f);
}

void AMan2::DeathStart()
{
	Renderer->ChangeAnimation("Death", false, 0, 0.08f);
}