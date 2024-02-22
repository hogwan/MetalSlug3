#include "Man1.h"
#include "ManZombie1.h"

AMan1::AMan1()
{
}

AMan1::~AMan1()
{
}

void AMan1::BeginPlay()
{
	AHuman::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("Man1.png");
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->CreateAnimation("Idle", "Man1.png", 0, 5, 0.3f, true);
	Renderer->CreateAnimation("Shock", "Man1.png", 6, 13, 0.15f, true);
	Renderer->CreateAnimation("Death", "Man1.png", 14, 25, 0.15f, false);

	Collider = CreateCollision(MT3CollisionOrder::Human);
	Collider->SetScale(CollisionScale);
	Collider->SetPosition(CollisionPosition);
	Collider->SetColType(ECollisionType::Rect);
}

void AMan1::Tick(float _DeltaTime)
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

void AMan1::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case HumanState::None:
		None(_DeltaTime);
		break;
	case HumanState::Idle:
		Idle(_DeltaTime);
		break;
	case HumanState::Shock:
		Shock(_DeltaTime);
		break;
	case HumanState::Death:
		Death(_DeltaTime);
		break;
	default:
		break;
	}
}

void AMan1::StateChange(HumanState _State)
{
	if (_State != CurState)
	{
		switch (_State)
		{
		case HumanState::None:
			NoneStart();
			break;
		case HumanState::Idle:
			IdleStart();
			break;
		case HumanState::Shock:
			ShockStart();
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

void AMan1::None(float _DeltaTime)
{
	StateChange(HumanState::Idle);
}

void AMan1::Idle(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (DetectCollider->CollisionCheck(MT3CollisionOrder::Enemy, Result))
	{
		StateChange(HumanState::Shock);
	}
}

void AMan1::Shock(float _DeltaTime)
{
}

void AMan1::Death(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		AManZombie1* Zombie = GetWorld()->SpawnActor<AManZombie1>();
		Zombie->SetActorLocation(GetActorLocation());
		Zombie->StateChange(EnemyZombieState::Lying);
		Destroy();
	}
}

void AMan1::NoneStart()
{
}

void AMan1::IdleStart()
{
	Renderer->ChangeAnimation("Idle", false, 0, 0.08f);
}

void AMan1::ShockStart()
{
	Renderer->ChangeAnimation("Shock", false, 0, 0.08f);
}

void AMan1::DeathStart()
{
	Renderer->ChangeAnimation("Death", false, 0, 0.08f);
}
