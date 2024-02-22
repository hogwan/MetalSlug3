#include "Woman.h"
#include "WomanZombie.h"

AWoman::AWoman()
{
}

AWoman::~AWoman()
{
}

void AWoman::BeginPlay()
{
	AHuman::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("Woman.png");
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->CreateAnimation("Idle", "Woman.png", 0, 8, 0.3f, true);
	Renderer->CreateAnimation("Shock", "Woman.png", 9, 14, 0.15f, true);
	Renderer->CreateAnimation("Death", "Woman.png", 15, 28, 0.15f, false);

	Collider = CreateCollision(MT3CollisionOrder::Human);
	Collider->SetScale(CollisionScale);
	Collider->SetPosition(CollisionPosition);
	Collider->SetColType(ECollisionType::Rect);
}

void AWoman::Tick(float _DeltaTime)
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

void AWoman::StateUpdate(float _DeltaTime)
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

void AWoman::StateChange(HumanState _State)
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

void AWoman::None(float _DeltaTime)
{
	StateChange(HumanState::Idle);
}

void AWoman::Idle(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (DetectCollider->CollisionCheck(MT3CollisionOrder::Enemy, Result))
	{
		StateChange(HumanState::Shock);
	}
}

void AWoman::Shock(float _DeltaTime)
{
}

void AWoman::Death(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		AWomanZombie* Zombie = GetWorld()->SpawnActor<AWomanZombie>();
		Zombie->SetActorLocation(GetActorLocation());
		Zombie->StateChange(EnemyZombieState::Lying);
		Destroy();
	}
}

void AWoman::NoneStart()
{
}

void AWoman::IdleStart()
{
	Renderer->ChangeAnimation("Idle", false, 0, 0.08f);
}

void AWoman::ShockStart()
{
	Renderer->ChangeAnimation("Shock", false, 0, 0.08f);
}

void AWoman::DeathStart()
{
	Renderer->ChangeAnimation("Death", false, 0, 0.08f);
}
