#include "Soldier.h"
#include "Marco.h"
#include "SoldierBomb.h"
#include <EnginePlatform/EngineSound.h>
#include <EngineBase/EngineRandom.h>
ASoldier::ASoldier()
{
}

ASoldier::~ASoldier()
{
}

void ASoldier::BeginPlay()
{
	AEnemy::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("Soldier.png");
	Renderer->SetTransform({ {0,0}, {500,500} });
	Renderer->CreateAnimation("Idle_Right", "Soldier.png", 0, 3, 0.2f, false);
	Renderer->CreateAnimation("Move_Right", "Soldier.png", 4, 15, 0.08f, true);
	Renderer->CreateAnimation("DeathByGun_Right", "Soldier.png", 16, 21, 0.12f, false);
	Renderer->CreateAnimation("Throw_Right", "Soldier.png", 30, 43, 0.08f, false);
	Renderer->CreateAnimation("KnifeAttack_Right", "Soldier.png", 44, 55, 0.08f, false);
	Renderer->CreateAnimation("DeathByKnife_Right", "Soldier.png", 56, 67, 0.08f, false);

	Renderer->CreateAnimation("Idle_Left", "Soldier.png", 70, 73, 0.2f, false);
	Renderer->CreateAnimation("Move_Left", "Soldier.png", 74, 85, 0.08f, true);
	Renderer->CreateAnimation("DeathByGun_Left", "Soldier.png", 86, 91, 0.12f, false);
	Renderer->CreateAnimation("Throw_Left", "Soldier.png", 100, 113, 0.08f, false);
	Renderer->CreateAnimation("KnifeAttack_Left", "Soldier.png", 114, 125, 0.08f, false);
	Renderer->CreateAnimation("DeathByKnife_Left", "Soldier.png", 126, 137, 0.08f, false);

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetTransform({ {0,-50},{50,100} });
	Collider->SetColType(ECollisionType::Rect);

	KnifeRangecollider = CreateCollision(MT3CollisionOrder::Detect);
	KnifeRangecollider->SetTransform({ KnifeReachCollisionPosition_Right, KnifeReachCollisionScale });
	KnifeRangecollider->SetColType(ECollisionType::Rect);

	KnifeAttackCollider = CreateCollision(MT3CollisionOrder::EnemyKnife);
	KnifeAttackCollider->SetTransform({ KnifeReachCollisionPosition_Right, KnifeReachCollisionScale});
	KnifeAttackCollider->SetColType(ECollisionType::Rect);

	ChangePattern(SoldierPattern::KnifeAttack);
}

void ASoldier::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);

	GravityCheck(_DeltaTime);
	GroundUp();
	StateUpdate(_DeltaTime);
	
	if (Hp <= 0)
	{
		StateChange(SoldierState::Death);
	}
}

void ASoldier::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case SoldierState::None:
		None(_DeltaTime);
		break;
	case SoldierState::Idle:
		Idle(_DeltaTime);
		break;
	case SoldierState::Move:
		Move(_DeltaTime);
		break;
	case SoldierState::KnifeAttack:
		KnifeAttack(_DeltaTime);
		break;
	case SoldierState::Throw:
		Throw(_DeltaTime);
		break;
	case SoldierState::Death:
		Death(_DeltaTime);
		break;
	default:
		break;
	}
}

void ASoldier::StateChange(SoldierState _State)
{
	if (CurState != _State)
	{
		switch (_State)
		{
		case SoldierState::None:
			NoneStart();
			break;
		case SoldierState::Idle:
			IdleStart();
			break;
		case SoldierState::Move:
			MoveStart();
			break;
		case SoldierState::KnifeAttack:
			KnifeAttackStart();
			break;
		case SoldierState::Throw:
			ThrowStart();
			break;
		case SoldierState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}

	CurState = _State;
}

void ASoldier::None(float _DeltaTime)
{
	StateChange(SoldierState::Idle);
	return;
}

void ASoldier::Idle(float _DeltaTime)
{
	DirCheck();

	if (Renderer->IsCurAnimationEnd())
	{
		switch (Pattern)
		{
		case SoldierPattern::KnifeAttack:
			StateChange(SoldierState::Move);
			break;
		case SoldierPattern::Throw:
			StateChange(SoldierState::Move);
			break;
		case SoldierPattern::RunAway:
			StateChange(SoldierState::Move);
			break;
		}
	}

}

void ASoldier::Move(float _DeltaTime)
{
	DirCheck();

	switch (Pattern)
	{
	case SoldierPattern::KnifeAttack:
	{
		TargetVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
		std::vector<UCollision*> Result;
		if (true == KnifeRangecollider->CollisionCheck(MT3CollisionOrder::Player, Result))
		{
			StateChange(SoldierState::KnifeAttack);
			return;
		}

		if (TargetVector.X > 0.0f)
		{
			MoveVector = FVector::Right;
		}
		else
		{
			MoveVector = FVector::Left;
		}

		AddActorLocation(MoveVector * MoveSpeed * _DeltaTime);

	}
		break;
	case SoldierPattern::Throw:
	{
		TargetVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
		if (abs(TargetVector.X) > ThrowRange && abs(TargetVector.X) < ThrowRange + 50.0f)
		{
			if (TargetVector.X > 0.f)
			{
				MoveVector = FVector::Right;
			}
			else
			{
				MoveVector = FVector::Left;
			}


			StateChange(SoldierState::Throw);
			return;
		}

		if (TargetVector.X > 0.0f && abs(TargetVector.X) < ThrowRange)
		{
			MoveVector = FVector::Left;
		}
		else if (TargetVector.X > 0.0f && abs(TargetVector.X) > ThrowRange + 50.0f)
		{
			MoveVector = FVector::Right;
		}
		else if(TargetVector.X < 0.0f && abs(TargetVector.X) < ThrowRange)
		{
			MoveVector = FVector::Right;
		}
		else if (TargetVector.X < 0.0f && abs(TargetVector.X) > ThrowRange + 50.0f)
		{
			MoveVector = FVector::Left;
		}

		AddActorLocation(MoveVector * MoveSpeed * _DeltaTime);
	}
		break;
	case SoldierPattern::RunAway:
	{
		TargetVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
		if (abs(TargetVector.X) > RunAwayRange)
		{
			RandomPattern();
			StateChange(SoldierState::Idle);
			return;
		}
		if (TargetVector.X > 0.0f)
		{
			MoveVector = FVector::Left;
		}
		else
		{
			MoveVector = FVector::Right;
		}

		AddActorLocation(MoveVector * MoveSpeed * _DeltaTime);
	}
		break;
	}
}

void ASoldier::Throw(float _DeltaTime)
{
	int CurFrame = Renderer->GetCurAnimationFrame();
	if (CurFrame != PrevFrame && CurFrame == 10)
	{
		ASoldierBomb* Bomb = GetWorld()->SpawnActor<ASoldierBomb>();
		FVector ThrowVector = { 3,-5 };
		ThrowVector.Normalize2D();
		float ThrowForce = 400.0f;
		ThrowVector *= ThrowForce;
		FVector SpawnLocation = GetActorLocation();

		if (MoveVector.X >  0.0f)
		{
			SpawnLocation += {30.0f, -100.0f};
		}
		else
		{
			SpawnLocation += {-30.0f, -100.0f};
			ThrowVector.X = -ThrowVector.X;
		}

		Bomb->SetActorLocation(SpawnLocation);
		Bomb->SetMoveVector(ThrowVector);

		PrevFrame = CurFrame;

	}

	if (Renderer->IsCurAnimationEnd())
	{
		RandomPattern();
		PrevFrame = -1;
		StateChange(SoldierState::Idle);
		return;
	}
}

void ASoldier::KnifeAttack(float _DeltaTime)
{
	if (Renderer->GetCurAnimationFrame() >= 6)
	{
		KnifeAttackCollider->ActiveOn();
	}

	if (Renderer->IsCurAnimationEnd())
	{
		std::vector<UCollision*> Result;
		KnifeAttackCollider->ActiveOff();
		RandomPattern();
		StateChange(SoldierState::Idle);
		return;
	}
}

void ASoldier::Death(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
		return;
	}
}

void ASoldier::NoneStart()
{
}

void ASoldier::IdleStart()
{
	KnifeAttackCollider->ActiveOff();
	CurAnimName = "Idle";
	DirCheck();
}

void ASoldier::MoveStart()
{
	CurAnimName = "Move";
	DirCheck();
}

void ASoldier::ThrowStart()
{
	CurAnimName = "Throw";
	FVector TargetVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
	if (TargetVector.X > 0.0f)
	{
		MoveVector = FVector::Right;
	}
	else
	{
		MoveVector = FVector::Left;
	}

	DirCheck();
}

void ASoldier::KnifeAttackStart()
{
	CurAnimName = "KnifeAttack";
	FVector TargetVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
	if (TargetVector.X > 0.0f)
	{
		MoveVector = FVector::Right;
	}
	else
	{
		MoveVector = FVector::Left;
	}
	DirCheck();
}

void ASoldier::DeathStart()
{
	int Random = UEngineRandom::MainRandom.RandomInt(0, 2);
	switch (Random)
	{
	case 0:
		UEngineSound::SoundPlay("SoldierDeath_0.mp3");
		break;
	case 1:
		UEngineSound::SoundPlay("SoldierDeath_1.mp3");
		break;
	case 2:
		UEngineSound::SoundPlay("SoldierDeath_2.mp3");
		break;
	}

	std::vector<UCollision*> Result;
	if (true == Collider->CollisionCheck(MT3CollisionOrder::PlayerKnife, Result))
	{
		CurAnimName = "DeathByKnife";
	}
	else
	{
		CurAnimName = "DeathByGun";
	}
	FVector TargetVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
	if (TargetVector.X > 0.0f)
	{
		MoveVector = FVector::Right;
	}
	else
	{
		MoveVector = FVector::Left;
	}
	DirCheck();
	Collider->ActiveOff();
}

void ASoldier::DirCheck()
{
	std::string DirCheckedName = CurAnimName;
	if (MoveVector.X < 0.0f)
	{
		DirCheckedName += "_Left";
		KnifeRangecollider->SetTransform({ KnifeReachCollisionPosition_Left, KnifeReachCollisionScale });
		KnifeRangecollider->SetColType(ECollisionType::Rect);

		KnifeAttackCollider->SetTransform({ KnifeReachCollisionPosition_Left, KnifeReachCollisionScale });
		KnifeAttackCollider->SetColType(ECollisionType::Rect);
	}
	else
	{
		DirCheckedName += "_Right";
		KnifeRangecollider->SetTransform({ KnifeReachCollisionPosition_Right, KnifeReachCollisionScale });
		KnifeRangecollider->SetColType(ECollisionType::Rect);

		KnifeAttackCollider->SetTransform({ KnifeReachCollisionPosition_Right, KnifeReachCollisionScale });
		KnifeAttackCollider->SetColType(ECollisionType::Rect);
	}


	Renderer->ChangeAnimation(DirCheckedName, false, 0, 0.08f);
}

void ASoldier::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}
}

void ASoldier::GroundUp()
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

void ASoldier::RandomPattern()
{
	int Random = UEngineRandom::MainRandom.RandomInt(0, 2);
	Pattern = SoldierPattern(Random);
}

void ASoldier::ChangePattern(SoldierPattern _Pattern)
{
	Pattern = _Pattern;
}
