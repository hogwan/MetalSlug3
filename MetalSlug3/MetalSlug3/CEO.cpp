#include "CEO.h"
#include "ContentsHelper.h"
#include "CEOsecretary.h"
#include <EnginePlatform/EngineSound.h>

ACEO::ACEO()
{
}

ACEO::~ACEO()
{
}

void ACEO::BeginPlay()
{
	AMT3Object::BeginPlay();

	CompensationFrame = 40;

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ { 0,0 }, { 500,500 } });
	Renderer->CreateAnimation("Tied", "CEO.png", 0, 5, 0.08f, true);
	Renderer->CreateAnimation("Liberate", "CEO.png", 6, 29, 0.08f, false);
	Renderer->CreateAnimation("Patrol", "CEO.png", 30, 61, 0.08f, true);
	Renderer->CreateAnimation("Compensation", "CEO.png", 62, 118, 0.08f, false);
	Renderer->CreateAnimation("RunAway", "CEO.png", 119, 157, 0.08f, false);

	Renderer->ChangeAnimation("Tied");

	Collider = CreateCollision(MT3CollisionOrder::TiedNPC);
	Collider->SetTransform({ {0,-25},{50,50} });
	Collider->SetColType(ECollisionType::Rect);
}

void ACEO::Tick(float _DeltaTime)
{
	APOWs::Tick(_DeltaTime);
}

void ACEO::Tied(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::PlayerBullet, Result))
	{
		StateChange(POWsState::Liberate);
		return;
	}
}

void ACEO::Liberate(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(POWsState::Patrol);
		return;
	}
}

void ACEO::Patrol(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::Player, Result))
	{
		StateChange(POWsState::Compensation);
		return;
	}
}

void ACEO::Compensation(float _DeltaTime)
{
	int CurFrame = Renderer->GetCurAnimationFrame();
	if (CurFrame != PrevFrame && CurFrame == CompensationFrame)
	{
		CEOsecretary* CEOsec = GetWorld()->SpawnActor<CEOsecretary>();
		CEOsec->SetActorLocation({ GetActorLocation().X + 50.f, GetActorLocation().Y });

		PrevFrame = CurFrame;
	}

	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(POWsState::Runaway);
		return;
	}
}

void ACEO::RunAway(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
		return;
	}
}

void ACEO::TiedStart()
{
	Renderer->ChangeAnimation("Tied", false, 0, 0.08f);
}

void ACEO::LiberateStart()
{
	Collider->SetOrder(static_cast<int>(MT3CollisionOrder::Detect));
	Renderer->ChangeAnimation("Liberate", false, 0, 0.08f);
}

void ACEO::PatrolStart()
{
	Renderer->ChangeAnimation("Patrol", false, 0, 0.08f);
}

void ACEO::CompensationStart()
{
	UEngineSound::SoundPlay("President.mp3");
	Renderer->ChangeAnimation("Compensation", false, 0, 0.08f);
}

void ACEO::RunAwayStart()
{
	Renderer->ChangeAnimation("RunAway", false, 0, 0.08f);
}
