#include "Monoliths.h"

AMonoliths::AMonoliths()
{
}

AMonoliths::~AMonoliths()
{
}

void AMonoliths::BeginPlay()
{
	SetActorLocation({ 14150,1850 });
	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0},{700,700} });
	Renderer->CreateAnimation("Idle", "Monoliths.png", 0, 0, 0.4f, true);
	Renderer->CreateAnimation("Smaller", "Monoliths.png", 0, 32, 0.4f, false);
	Renderer->CreateAnimation("FastSmaller", "Monoliths.png", 0, 32, 0.1f, false);
	Renderer->ChangeAnimation("Idle", false, 0, 0.08f);

	Collider = CreateCollision(MT3CollisionOrder::Monoliths);
	Collider->SetTransform({ {0.f,-InitScale.Y/2.0f},InitScale });
	Collider->SetColType(ECollisionType::Rect);

	LayCheck = CreateCollision(MT3CollisionOrder::Detect);
	LayCheck->SetScale({ 30,30 });
	LayCheck->SetColType(ECollisionType::Rect);
}

void AMonoliths::Tick(float _DeltaTime)
{
	Collider->SetTransform({ {0.f,-InitScale.Y / 2.0f},InitScale });
	LayCheck->SetPosition({ 0.f,-InitScale.Y - 50.0f });

	if (IsLand)
	{
		Renderer->ChangeAnimation("Smaller", false, 0, 0.4f);
		InitScale.Y -= 24.f * _DeltaTime;
		
	}
	else if (Lay)
	{
		int CurFrame = Renderer->GetCurAnimationFrame();
		Renderer->ChangeAnimation("FastSmaller", false, CurFrame, 0.1f);
		InitScale.Y -= 96.f * _DeltaTime;
	}
	else
	{
		Gravity(_DeltaTime);
	}

	if (InitScale.Y < 0.f)
	{
		Destroy();
	}
}

void AMonoliths::Gravity(float _DeltaTime)
{
	Speed += Accel * _DeltaTime;
	AddActorLocation(FVector::Down * Speed * _DeltaTime);

	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		Speed = 0.0f;
		IsLand = true;
	}

	std::vector<UCollision*> Result;
	if (LayCheck->CollisionCheck(MT3CollisionOrder::Monoliths, Result))
	{
		Lay = true;
	}
}
