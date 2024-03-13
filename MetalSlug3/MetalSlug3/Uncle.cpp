#include "Uncle.h"
#include "UncleZombie.h"
#include "ZombieThunder.h"

AUncle::AUncle()
{
}

AUncle::~AUncle()
{
}

void AUncle::BeginPlay()
{
	AHuman::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("Uncle.png");
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->CreateAnimation("Idle", "Uncle.png", 0, 7, 0.3f, true);
	Renderer->CreateAnimation("Death", "Uncle.png", 8, 18, 0.15f, false);

	Collider = CreateCollision(MT3CollisionOrder::Human);
	Collider->SetScale(CollisionScale);
	Collider->SetPosition(CollisionPosition);
	Collider->SetColType(ECollisionType::Rect);
}

void AUncle::Tick(float _DeltaTime)
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

void AUncle::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case HumanState::None:
		None(_DeltaTime);
		break;
	case HumanState::Idle:
		Idle(_DeltaTime);
		break;
	case HumanState::Death:
		Death(_DeltaTime);
		break;
	default:
		break;
	}
}

void AUncle::StateChange(HumanState _State)
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
		case HumanState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}

	CurState = _State;
}

void AUncle::None(float _DeltaTime)
{
	StateChange(HumanState::Idle);
}

void AUncle::Idle(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (DetectCollider->CollisionCheck(MT3CollisionOrder::Enemy, Result))
	{
		StateChange(HumanState::Shock);
	}
}

void AUncle::Death(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		AUncleZombie* Zombie = GetWorld()->SpawnActor<AUncleZombie>();
		Zombie->SetActorLocation(GetActorLocation());
		Zombie->StateChange(EnemyZombieState::Lying);

		ZombieThunder* Effect = GetWorld()->SpawnActor<ZombieThunder>();
		Effect->SetActorLocation(GetActorLocation());
		Destroy();
	}
}

void AUncle::NoneStart()
{
}

void AUncle::IdleStart()
{
	Renderer->ChangeAnimation("Idle", false, 0, 0.08f);
}


void AUncle::DeathStart()
{
	Renderer->ChangeAnimation("Death", false, 0, 0.08f);
}

