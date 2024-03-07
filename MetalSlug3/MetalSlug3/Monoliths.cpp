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
	Renderer->CreateAnimation("FastSmaller", "Monoliths.png", 0, 32, 0.01f, false);
	Renderer->ChangeAnimation("Idle", false, 0, 0.08f);

	Collider = CreateCollision(MT3CollisionOrder::Monoliths);
	Collider->SetTransform({ {0.f,-InitScale.Y/2.0f},InitScale });
	Collider->SetColType(ECollisionType::Rect);

	UpLayCollision = CreateCollision(MT3CollisionOrder::Detect);
	UpLayCollision->SetScale({ 100,30 });
	UpLayCollision->SetColType(ECollisionType::Rect);
}

void AMonoliths::Tick(float _DeltaTime)
{
	Collider->SetTransform({ {0.f,-InitScale.Y / 2.0f},InitScale });
	UpLayCollision->SetPosition({ 0.f,-InitScale.Y - 16.0f });

	UpLayCheck();

	if (IsLand && !UpLay)
	{
		
		InitScale.Y -= 24.f * _DeltaTime;
		
	}
	else if (UpLay)
	{
		InitScale.Y -= UpLayerSpeed * _DeltaTime;
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

void AMonoliths::UpLayCheck()
{
	std::vector<UCollision*> Result;
	if (UpLayCollision->CollisionCheck(MT3CollisionOrder::Monoliths, Result))
	{
		AMonoliths* UpLayer = dynamic_cast<AMonoliths*>(Result[0]->GetOwner());
		UpLayerSpeed = UpLayer->Speed;

		int CurFrame = Renderer->GetCurAnimationFrame();
		Renderer->ChangeAnimation("FastSmaller", true, CurFrame, 0.01f);
		CurAnim = "FastSmaller";

		UpLay = true;
	}
}

void AMonoliths::GoDown()
{
	InitScale.Y -= 15;
	int CurFrame = Renderer->GetCurAnimationFrame();
	if (CurFrame + 5 <= 32)
	{
		if (CurAnim == "Smaller")
		{
			Renderer->ChangeAnimation("Smaller", true, CurFrame+1, 0.04f);
		}
		else if (CurAnim == "FastSmaller")
		{
			Renderer->ChangeAnimation("FastSmaller", true, CurFrame+1, 0.01f);
		}
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
		Renderer->ChangeAnimation("Smaller", true, 0, 0.4f);
		CurAnim = "Smaller";
		IsLand = true;
	}
}
