#include "Enemy.h"
#include "ManZombie1.h"

AManZombie1::AManZombie1()
{
}

AManZombie1::~AManZombie1()
{
}

void AManZombie1::BeginPlay()
{
	AEnemy::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("ManZombie1.png");
	Renderer->SetTransform({ {0,0}, {200,200} });


}

void AManZombie1::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);
	GravityCheck(_DeltaTime);
	GroundUp();
	StateUpdate(_DeltaTime);
}

void AManZombie1::StateUpdate(float _DeltaTime)
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
	Default:
		break;
	}
}

void AManZombie1::StateChange(EnemyZombieState _State)
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
		Default:
			break;
		}
	}
}

void AManZombie1::None(float _DeltaTime)
{
	StateChange(EnemyZombieState::Idle);
	return;
}

void AManZombie1::Lying(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(EnemyZombieState::Idle);
	}
}

void AManZombie1::Idle(float _DeltaTime)
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

void AManZombie1::Move(float _DeltaTime)
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

void AManZombie1::Turn(float _DeltaTime)
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

void AManZombie1::Stun(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		CurStunGauge = 0.0f;
		StateChange(EnemyZombieState::Idle);
		return;
	}
}

void AManZombie1::Attack(float _DeltaTime)
{
	//if (Renderer->GetCurAnimationFrame() == 5)
	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(EnemyZombieState::Idle);
		return;
	}
}

void AManZombie1::NoneStart()
{
	CurAnimName = "None";
}

void AManZombie1::LyingStart()
{
	CurAnimName = "Lying";
	Renderer->ChangeAnimation(CurAnimName);
}

void AManZombie1::IdleStart()
{
	CurAnimName = "Idle";
	DirCheck(CurAnimName);
	Renderer->ChangeAnimation(CurAnimName);

}

void AManZombie1::MoveStart()
{
	CurAnimName = "Move";
	DirCheck(CurAnimName);
	Renderer->ChangeAnimation(CurAnimName);
}

void AManZombie1::TurnStart()
{
	CurAnimName = "Turn";
	DirCheck(CurAnimName);
	Renderer->ChangeAnimation(CurAnimName);
}

void AManZombie1::StunStart()
{
	CurAnimName = "Stun";
	DirCheck(CurAnimName);
	Renderer->ChangeAnimation(CurAnimName);
}

void AManZombie1::AttackStart()
{
	CurAnimName = "Attack";
	DirCheck(CurAnimName);
	Renderer->ChangeAnimation(CurAnimName);
}

void AManZombie1::DirCheck(std::string& _Name)
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
	Default:
		break;
	}

	_Name += Dir;
}

bool AManZombie1::PlayerInRange()
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

bool AManZombie1::WatchPlayer()
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
		else if(DirState == EActorDir::Left)
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
}

void AManZombie1::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}
}

void AManZombie1::GroundUp()
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
