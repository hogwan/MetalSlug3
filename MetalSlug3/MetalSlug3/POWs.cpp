#include "POWs.h"
#include "ContentsHelper.h"
#include "BombBox.h"
#include "HeavyMachineGun.h"
#include "RocketLauncher.h"
#include "FlameShot.h"

APOWs::APOWs()
{
}

APOWs::~APOWs()
{
	
}

void APOWs::BeginPlay()
{
	AMT3Object::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ { 0,0 }, { 500,500 } });
	Renderer->CreateAnimation("Tied", "POWs.png", 0, 4, 0.08f, true);
	Renderer->CreateAnimation("Liberate", "POWs.png", 5, 8, 0.08f, false);
	Renderer->CreateAnimation("Compensation", "POWs.png", 9, 33, 0.08f, false);
	Renderer->CreateAnimation("RunAway", "POWs.png", 34, 41, 0.08f, true);
	Renderer->CreateAnimation("Patrol_Left", "POWs.png", 42, 53, 0.08f, true);
	Renderer->CreateAnimation("Patrol_Right", "POWs.png", 54, 65, 0.08f, true);
	Renderer->ChangeAnimation("Tied");

	Collider = CreateCollision(MT3CollisionOrder::TiedNPC);
	Collider->SetTransform({ {0,-25},{50,50} });
	Collider->SetColType(ECollisionType::Rect);
}

void APOWs::Tick(float _DeltaTime)
{
	AMT3Object::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);

	GravityCheck(_DeltaTime);
	GroundUp();
}

void APOWs::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case POWsState::Tied:
		Tied(_DeltaTime);
		break;
	case POWsState::Liberate:
		Liberate(_DeltaTime);
		break;
	case POWsState::Patrol:
		Patrol(_DeltaTime);
		break;
	case POWsState::Compensation:
		Compensation(_DeltaTime);
		break;
	case POWsState::Runaway:
		RunAway(_DeltaTime);
		break;
	default:
		break;
	}
}

void APOWs::StateChange(POWsState _State)
{
	if (CurState != _State)
	{
		switch (_State)
		{
		case POWsState::Tied:
			TiedStart();
			break;
		case POWsState::Liberate:
			LiberateStart();
			break;
		case POWsState::Patrol:
			PatrolStart();
			break;
		case POWsState::Compensation:
			CompensationStart();
			break;
		case POWsState::Runaway:
			RunAwayStart();
			break;
		default:
			break;
		}
	}

	CurState = _State;
}

void APOWs::Tied(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::PlayerBullet, Result))
	{
		StateChange(POWsState::Liberate);
		return;
	}
}

void APOWs::Liberate(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(POWsState::Patrol);
		return;
	}
}

void APOWs::Patrol(float _DeltaTime)
{
	if (abs(GetActorLocation().X - InitialPos.X) > MoveRange)
	{
		int a = 0;
		if (MoveVector.X  > 0.f)
		{
			MoveVector = FVector::Left;

		}
		else if (MoveVector.X < 0.f)
		{
			MoveVector = FVector::Right;
		}

		if (MoveVector.X < 0.f)
		{
			Renderer->ChangeAnimation("Patrol_Left", false, 0, 0.08f);
		}
		else if (MoveVector.X > 0.f)
		{
			Renderer->ChangeAnimation("Patrol_Right", false, 0, 0.08f);
		}
	}
	AddActorLocation(MoveVector * MoveSpeed * _DeltaTime);

	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::Player, Result))
	{
		StateChange(POWsState::Compensation);
		return;
	}
}

void APOWs::Compensation(float _DeltaTime)
{
	int CurFrame = Renderer->GetCurAnimationFrame();
	if (CurFrame != PrevFrame && CurFrame == CompensationFrame)
	{
		switch (Reward)
		{
		case ItemReward::BombBox:
		{
			BombBox* BB = GetWorld()->SpawnActor<BombBox>();
			BB->SetActorLocation({ GetActorLocation().X - 30, GetActorLocation().Y });
			break;
		}
		case ItemReward::FlameShot:
		{
			FlameShot* FS = GetWorld()->SpawnActor<FlameShot>();
			FS->SetActorLocation({ GetActorLocation().X - 30, GetActorLocation().Y });
			break;
		}
		case ItemReward::RocketLauncher:
		{
			RocketLauncher* RL = GetWorld()->SpawnActor<RocketLauncher>();
			RL->SetActorLocation({ GetActorLocation().X - 30, GetActorLocation().Y });
			break;
		}
		case ItemReward::HeavyMachineGun:
		{
			HeavyMachineGun* HM = GetWorld()->SpawnActor<HeavyMachineGun>();
			HM->SetActorLocation({ GetActorLocation().X - 30, GetActorLocation().Y });
			break;
		}
		default:
			break;
		}

		PrevFrame = CurFrame;
	}

	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(POWsState::Runaway);
		return;
	}
}

void APOWs::RunAway(float _DeltaTime)
{
	AddActorLocation(FVector::Left * 150.f * _DeltaTime);
}

void APOWs::TiedStart()
{
	Renderer->ChangeAnimation("Tied", false, 0, 0.08f);
}

void APOWs::LiberateStart()
{
	Collider->SetOrder(static_cast<int>(MT3CollisionOrder::Detect));
	Renderer->ChangeAnimation("Liberate", false, 0, 0.08f);
}

void APOWs::PatrolStart()
{
	if (MoveVector.X < 0.f)
	{
		Renderer->ChangeAnimation("Patrol_Left", false, 0, 0.08f);
	}
	else if(MoveVector.X > 0.f)
	{
		Renderer->ChangeAnimation("Patrol_Right", false, 0, 0.08f);
	}
}

void APOWs::CompensationStart()
{
	Renderer->ChangeAnimation("Compensation", false, 0, 0.08f);
}

void APOWs::RunAwayStart()
{
	Renderer->ChangeAnimation("RunAway", false, 0, 0.08f);
}

void APOWs::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}
}

void APOWs::GroundUp()
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
