#include "Doctor.h"
#include "DoctorZombie.h"
ADoctor::ADoctor()
{
}

ADoctor::~ADoctor()
{
}

void ADoctor::BeginPlay()
{
	AHuman::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("Doctor.png");
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->CreateAnimation("Run", "Doctor.png", 0, 9, 0.08f, true);
	Renderer->CreateAnimation("Idle", "Doctor.png", 10, 20, 0.3f, true);
	Renderer->CreateAnimation("Death", "Doctor.png", 21, 31, 0.08f, false);

	Collider = CreateCollision(MT3CollisionOrder::Human);
	Collider->SetScale(CollisionScale);
	Collider->SetPosition(CollisionPosition);
	Collider->SetColType(ECollisionType::Rect);
}

void ADoctor::Tick(float _DeltaTime)
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

void ADoctor::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case HumanState::None:
		None(_DeltaTime);
		break;
	case HumanState::Idle:
		Idle(_DeltaTime);
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

void ADoctor::StateChange(HumanState _State)
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

void ADoctor::None(float _DeltaTime)
{
	StateChange(HumanState::Idle);
}

void ADoctor::Idle(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (DetectCollider->CollisionCheck(MT3CollisionOrder::Enemy, Result))
	{
		StateChange(HumanState::Run);
	}
}

void ADoctor::Run(float _DeltaTime)
{
	AddActorLocation(FVector::Left * RunSpeed * _DeltaTime);
}

void ADoctor::Death(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		ADoctorZombie* Zombie = GetWorld()->SpawnActor<ADoctorZombie>();
		Zombie->SetActorLocation(GetActorLocation());
		Zombie->SetCurState(EnemyZombieState::Lying);
		Destroy();
	}
}

void ADoctor::NoneStart()
{
}

void ADoctor::RunStart()
{
	Renderer->ChangeAnimation("Run", false, 0, 0.08f);
}

void ADoctor::IdleStart()
{
	Renderer->ChangeAnimation("Idle", false, 0, 0.08f);
}
void ADoctor::DeathStart()
{
	Renderer->ChangeAnimation("Death", false, 0, 0.08f);
}