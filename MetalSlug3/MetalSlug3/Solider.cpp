#include "Solider.h"
#include "Marco.h"
ASolider::ASolider()
{
}

ASolider::~ASolider()
{
}

void ASolider::BeginPlay()
{
	AEnemy::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("Solider.png");
	Renderer->SetTransform({ {0,0}, {500,500} });
	Renderer->CreateAnimation("Idle_Right", "Solider.png", 0, 3, 0.08f, true);
	Renderer->CreateAnimation("Move_Right", "Solider.png", 4, 15, 0.08f, true);
	Renderer->CreateAnimation("DeathByGun_Right", "Solider.png", 16, 21, 0.08f, false);
	Renderer->CreateAnimation("Throw_Right", "Solider.png", 30, 43, 0.08f, false);
	Renderer->CreateAnimation("KnifeAttack_Right", "Solider.png", 44, 55, 0.08f, false);
	Renderer->CreateAnimation("DeathByKnife_Right", "Solider.png", 56, 67, 0.08f, false);

	Renderer->CreateAnimation("Idle_Left", "Solider.png", 70, 73, 0.08f, true);
	Renderer->CreateAnimation("Move_Left", "Solider.png", 74, 85, 0.08f, true);
	Renderer->CreateAnimation("DeathByGun_Left", "Solider.png", 86, 91, 0.08f, false);
	Renderer->CreateAnimation("Throw_Left", "Solider.png", 100, 113, 0.08f, false);
	Renderer->CreateAnimation("KnifeAttack_Left", "Solider.png", 114, 125, 0.08f, false);
	Renderer->CreateAnimation("DeathByKnife_Left", "Solider.png", 126, 137, 0.08f, false);

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetTransform({ {0,-50},{50,100} });
	Collider->SetColType(ECollisionType::Rect);

	KnifeAttackCollider = CreateCollision(MT3CollisionOrder::Detect);
	KnifeAttackCollider->SetTransform({ KnifeReachCollisionPosition_Right, KnifeReachCollisionScale});
	KnifeAttackCollider->SetColType(ECollisionType::Rect);

	ChangePattern(SoliderPattern::KnifeAttack);
}

void ASolider::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);

	TargetCheck();
	GravityCheck(_DeltaTime);
	GroundUp();
	StateUpdate(_DeltaTime);
}

void ASolider::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case SoilderState::None:
		None(_DeltaTime);
		break;
	case SoilderState::Idle:
		Idle(_DeltaTime);
		break;
	case SoilderState::Move:
		Move(_DeltaTime);
		break;
	case SoilderState::KnifeAttack:
		KnifeAttack(_DeltaTime);
		break;
	case SoilderState::Throw:
		Throw(_DeltaTime);
		break;
	case SoilderState::Death:
		Death(_DeltaTime);
		break;
	default:
		break;
	}
}

void ASolider::StateChange(SoilderState _State)
{
	if (CurState != _State)
	{
		switch (_State)
		{
		case SoilderState::None:
			NoneStart();
			break;
		case SoilderState::Idle:
			IdleStart();
			break;
		case SoilderState::Move:
			MoveStart();
			break;
		case SoilderState::KnifeAttack:
			KnifeAttackStart();
			break;
		case SoilderState::Throw:
			ThrowStart();
			break;
		case SoilderState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
}

void ASolider::None(float _DeltaTime)
{
	StateChange(SoilderState::Idle);
	return;
}

void ASolider::Idle(float _DeltaTime)
{
	DirCheck();

	switch (Pattern)
	{
	case SoliderPattern::KnifeAttack:
		break;
	case SoliderPattern::Throw:
		break;
	case SoliderPattern::RunAway:
		break;
	}
}

void ASolider::Move(float _DeltaTime)
{
	DirCheck();

	switch (Pattern)
	{
	case SoliderPattern::KnifeAttack:
		break;
	case SoliderPattern::Throw:
		break;
	case SoliderPattern::RunAway:
		break;
	}
}

void ASolider::Throw(float _DeltaTime)
{
	switch (Pattern)
	{
	case SoliderPattern::KnifeAttack:
		break;
	case SoliderPattern::Throw:
		break;
	case SoliderPattern::RunAway:
		break;
	}
}

void ASolider::KnifeAttack(float _DeltaTime)
{
	switch (Pattern)
	{
	case SoliderPattern::KnifeAttack:
		break;
	case SoliderPattern::Throw:
		break;
	case SoliderPattern::RunAway:
		break;
	}
}

void ASolider::Death(float _DeltaTime)
{
}

void ASolider::NoneStart()
{
}

void ASolider::IdleStart()
{
	CurAnimName = "Idle";
	DirCheck();
}

void ASolider::MoveStart()
{
	CurAnimName = "Move";
	DirCheck();
}

void ASolider::ThrowStart()
{
	CurAnimName = "Throw";
	DirCheck();
}

void ASolider::KnifeAttackStart()
{
	CurAnimName = "KnifeAttack";
	DirCheck();
}

void ASolider::DeathStart()
{
	CurAnimName = "Death";
	DirCheck();
}

void ASolider::TargetCheck()
{
	FVector PlayerPos = UContentsHelper::Player->GetActorLocation();
	FVector Pos = GetActorLocation();

	if (PlayerPos.X > Pos.X)
	{
		TargetVector = FVector::Right;
	}
	else
	{
		TargetVector = FVector::Left;
	}
}

void ASolider::DirCheck()
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

	Renderer->ChangeAnimation(DirCheckedName, false, 0, 0.08f);
}

void ASolider::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}
}

void ASolider::GroundUp()
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

void ASolider::ChangePattern(SoliderPattern _Pattern)
{
	Pattern = _Pattern;
}
