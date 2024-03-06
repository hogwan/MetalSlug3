#include "Laser.h"
#include "ContentsHelper.h"
#include "Marco.h"

ALaser::ALaser()
{
}

ALaser::~ALaser()
{
}

void ALaser::BeginPlay()
{
	FVector PlayerPos = UContentsHelper::Player->GetActorLocation();
	SetActorLocation({ PlayerPos.X, 2400.f });

	Lazer = CreateImageRenderer(MT3RenderOrder::UFO_Lazer);
	Lazer->SetTransform({ {0,0},{500,500} });
	Lazer->CreateAnimation("Lazer", "LazerAiming.png", 0, 2, 0.02f, true);
	Lazer->ChangeAnimation("Lazer", false, 0, 0.02f);

	GroundEffect = CreateImageRenderer(MT3RenderOrder::UFO_LazerGroundEffect);
	GroundEffect->SetTransform({ {0,0},{500,500} });
	GroundEffect->CreateAnimation("GroundEffect", "LazerAiming_GroundEffect.png", 0, 5, 0.02f, true);
	GroundEffect->ChangeAnimation("GroundEffect", false, 0, 0.02f);

	Collider = CreateCollision(MT3CollisionOrder::Lazer);
	Collider->SetScale({ 1,1 });
	Collider->SetColType(ECollisionType::Rect);
}

void ALaser::Tick(float _DeltaTime)
{
	FVector PlayerPos = UContentsHelper::Player->GetActorLocation();

	if (abs(PlayerPos.X - GetActorLocation().X) > 1.0f)
	{
		if (GetActorLocation().X < PlayerPos.X)
		{
			AddActorLocation(FVector::Right * Speed * _DeltaTime);
		}
		else
		{
			AddActorLocation(FVector::Left * Speed * _DeltaTime);
		}
	}

	GroundUp();
}

void ALaser::GroundUp()
{
	while (true)
	{
		Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 15, Color8Bit::MagentaA);
		std::vector<UCollision*> Result;

		if (Color == Color8Bit(255, 0, 255, 0) || Collider->CollisionCheck(MT3CollisionOrder::Monoliths, Result))
		{
			AddActorLocation(FVector::Up);
		}
		else
		{
			break;
		}
	}
}
