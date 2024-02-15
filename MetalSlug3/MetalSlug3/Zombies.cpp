#include "Zombies.h"
#include "Enemy.h"
#include "Marco.h"
#include "ZombiesProjectile.h"

AZombies::AZombies()
{
}

AZombies::~AZombies()
{
}
void AZombies::BeginPlay()
{
	AEnemy::BeginPlay();
}
void AZombies::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);
}
void AZombies::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case EnemyZombieState::None:
		None(_DeltaTime);
		break;
	case EnemyZombieState::Lying:
		Lying(_DeltaTime);
		break;
	case EnemyZombieState::Idle:
		Idle(_DeltaTime);
		break;
	case EnemyZombieState::Move:
		Move(_DeltaTime);
		break;
	case EnemyZombieState::Turn:
		Turn(_DeltaTime);
		break;
	case EnemyZombieState::Stun:
		Stun(_DeltaTime);
		break;
	case EnemyZombieState::Attack:
		Attack(_DeltaTime);
		break;
	default:
		break;
	}
}

void AZombies::StateChange(EnemyZombieState _State)
{
	if (CurState != _State)
	{
		switch (_State)
		{
		case EnemyZombieState::None:
			NoneStart();
			break;
		case EnemyZombieState::Lying:
			LyingStart();
			break;
		case EnemyZombieState::Idle:
			IdleStart();
			break;
		case EnemyZombieState::Move:
			MoveStart();
			break;
		case EnemyZombieState::Turn:
			TurnStart();
			break;
		case EnemyZombieState::Stun:
			StunStart();
			break;
		case EnemyZombieState::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}
	CurState = _State;
}

void AZombies::None(float _DeltaTime)
{
	StateChange(EnemyZombieState::Idle);
	return;
}

void AZombies::Lying(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(EnemyZombieState::Idle);
	}
}

void AZombies::Idle(float _DeltaTime)
{
	AccTime += _DeltaTime;
	if (AccTime > CoolTime)
	{
		if (false == WatchPlayer())
		{
			AccTime = 0.0f;
			StateChange(EnemyZombieState::Turn);
			return;
		}

		if (PlayerInRange())
		{
			AccTime = 0.0f;
			StateChange(EnemyZombieState::Attack);
			return;
		}
		else
		{
			AccTime = 0.0f;
			StateChange(EnemyZombieState::Move);
			return;
		}

		if (MaxStunGauge < CurStunGauge)
		{
			AccTime = 0.0f;
			StateChange(EnemyZombieState::Stun);
			return;
		}
	}
}

void AZombies::Move(float _DeltaTime)
{
	if (false == WatchPlayer())
	{
		AccTime = 0.0f;
		StateChange(EnemyZombieState::Turn);
		return;
	}

	if (PlayerInRange())
	{
		AccTime = 0.0f;
		StateChange(EnemyZombieState::Attack);
		return;
	}

	if (MaxStunGauge < CurStunGauge)
	{
		AccTime = 0.0f;
		CurStunGauge = 0.0f;
		StateChange(EnemyZombieState::Stun);
		return;
	}

	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 30;
		break;
	case EActorDir::Right:
		CheckPos.X += 30;
		break;
	default:
		break;
	}
	CheckPos.Y -= 30;
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);

	if (Color == Color8Bit(255, 0, 255, 0))
	{
		return;
	}

	if (DirState == EActorDir::Left)
	{
		AddActorLocation(FVector::Left * MoveSpeed * _DeltaTime);
	}
	else if (DirState == EActorDir::Right)
	{
		AddActorLocation(FVector::Right * MoveSpeed * _DeltaTime);
	}

}

void AZombies::Turn(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		if (DirState == EActorDir::Left)
		{
			DirState = EActorDir::Right;
		}
		else if (DirState == EActorDir::Right)
		{
			DirState = EActorDir::Left;
		}

		StateChange(EnemyZombieState::Idle);
		return;
	}
}

void AZombies::Stun(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		CurStunGauge = 0.0f;
		StateChange(EnemyZombieState::Idle);
		return;
	}
}

void AZombies::Attack(float _DeltaTime, float _LaunchFrame)
{
	int CurFrame = Renderer->GetCurAnimationFrame();
	if (CurFrame == PrevFrame) return;
	if (CurFrame == _LaunchFrame)
	{
		LaunchRenderer->ActiveOn();
		AZombiesProjectile* Projectile = GetWorld()->SpawnActor<AZombiesProjectile>();
		FVector SpawnLocation = FVector::Zero;
		if (DirState == EActorDir::Right)
		{
			SpawnLocation = GetActorLocation() + ProjectileSpawnOffset_Height + ProjectileSpawnOffset_Right;
			Projectile->SetDir(FVector::Right);
			LaunchRenderer->ChangeAnimation("LaunchEffect_Right", true, 0, 0.1f);
			LaunchRenderer->SetTransform({ LaunchEffectOffset_Up + LaunchEffectOffset_Right, {400,400} });
		}
		else if (DirState == EActorDir::Left)
		{
			SpawnLocation = GetActorLocation() + ProjectileSpawnOffset_Height + ProjectileSpawnOffset_Left;
			Projectile->SetDir(FVector::Left);
			LaunchRenderer->ChangeAnimation("LaunchEffect_Left", true, 0, 0.1f);
			LaunchRenderer->SetTransform({ LaunchEffectOffset_Up + LaunchEffectoffset_Left, {400,400} });
		}
		Projectile->SetActorLocation(SpawnLocation);

		PrevFrame = CurFrame;
	}
	if (Renderer->IsCurAnimationEnd())
	{
		PrevFrame = -1;
		StateChange(EnemyZombieState::Idle);
		return;
	}

	if (LaunchRenderer->IsCurAnimationEnd())
	{
		LaunchRenderer->ActiveOff();
	}
}

void AZombies::NoneStart()
{
	CurAnimName = "None";
}

void AZombies::LyingStart()
{
	CurAnimName = "Lying";
	Renderer->ChangeAnimation(CurAnimName);
}

void AZombies::IdleStart()
{
	CurAnimName = "Idle";
	DirCheck(CurAnimName);
	Renderer->ChangeAnimation(CurAnimName);

}

void AZombies::MoveStart()
{
	CurAnimName = "Move";
	DirCheck(CurAnimName);
	Renderer->ChangeAnimation(CurAnimName);
}

void AZombies::TurnStart()
{
	CurAnimName = "Turn";
	DirCheck(CurAnimName);
	Renderer->ChangeAnimation(CurAnimName);
}

void AZombies::StunStart()
{
	CurAnimName = "Stun";
	DirCheck(CurAnimName);
	Renderer->ChangeAnimation(CurAnimName);
}

void AZombies::AttackStart()
{
	CurAnimName = "Attack";
	DirCheck(CurAnimName);
	Renderer->ChangeAnimation(CurAnimName);
}

void AZombies::DirCheck(std::string& _Name)
{
	std::string Dir;

	switch (DirState)
	{
	case EActorDir::Left:
		Dir = "_Left";
		break;
	case EActorDir::Right:
		Dir = "_Right";
		break;
	default:
		break;
	}

	_Name += Dir;
}

bool AZombies::PlayerInRange()
{
	FVector PlayerPos = UContentsHelper::Player->GetActorLocation();
	FVector ThisPos = GetActorLocation();

	float _Range = abs(PlayerPos.X - ThisPos.X);

	if (_Range >= Range)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool AZombies::WatchPlayer()
{
	FVector PlayerPos = UContentsHelper::Player->GetActorLocation();
	FVector ThisPos = GetActorLocation();

	float gap = PlayerPos.X - ThisPos.X;

	if (gap > 0)
	{
		if (DirState == EActorDir::Right)
		{
			return true;
		}
		else if (DirState == EActorDir::Left)
		{
			return false;
		}
	}
	else
	{
		if (DirState == EActorDir::Right)
		{
			return false;
		}
		else if (DirState == EActorDir::Left)
		{
			return true;
		}
	}

	return false;
}

void AZombies::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}
}

void AZombies::GroundUp()
{
	while (true)
	{
		Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
		if (Color == Color8Bit(255, 0, 255, 0))
		{
			AddActorLocation(FVector::Up);
		}
		else
		{
			break;
		}
	}
}