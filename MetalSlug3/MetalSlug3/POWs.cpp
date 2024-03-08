#include "POWs.h"
#include "ContentsHelper.h"

POWs::POWs()
{
}

POWs::~POWs()
{
}

void POWs::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ { 0,0 }, { 500,500 } });
	Renderer->CreateAnimation("Tied", "POWs.png", 0, 4, 0.08f, true);
	Renderer->CreateAnimation("Liberate", "POWs.png", 5, 8, 0.08f, false);
	Renderer->CreateAnimation("Compensation", "POWs.png", 9, 41, 0.08f, false);
	Renderer->CreateAnimation("RunAway", "POWs.png", 42, 49, 0.08f, true);
	Renderer->CreateAnimation("Patrol_Left", "POWs.png", 50, 61, 0.08f, true);
	Renderer->CreateAnimation("Patrol_Right", "POWs.png", 62, 73, 0.08f, true);

	Collider = CreateCollision(MT3CollisionOrder::Detect);
	Collider->SetTransform({ {0,-25},{50,50} });
	Collider->SetColType(ECollisionType::Rect);
}

void POWs::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);
}

void POWs::StateUpdate(float _DeltaTime)
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

void POWs::StateChange(POWsState _State)
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
}

void POWs::Tied(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::PlayerBullet, Result)
		|| Collider->CollisionCheck(MT3CollisionOrder::PlayerKnife, Result))
	{
		StateChange(POWsState::Liberate);
		return;
	}
}

void POWs::Liberate(float _DeltaTime)
{
}

void POWs::Patrol(float _DeltaTime)
{
}

void POWs::Compensation(float _DeltaTime)
{
}

void POWs::RunAway(float _DeltaTime)
{
}

void POWs::TiedStart()
{
}

void POWs::LiberateStart()
{
}

void POWs::PatrolStart()
{
}

void POWs::CompensationStart()
{
}

void POWs::RunAwayStart()
{
}
