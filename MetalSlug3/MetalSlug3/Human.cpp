#include "Human.h"


AHuman::AHuman()
{
}

AHuman::~AHuman()
{
}

void AHuman::BeginPlay()
{
	AActor::BeginPlay();
	DetectCollider = CreateCollision(MT3CollisionOrder::Detect);
	DetectCollider->SetTransform({{0,0},{DetectRange * 2.0f, 200.0f}});
	DetectCollider->SetColType(ECollisionType::Rect);
}

void AHuman::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	GravityCheck(_DeltaTime);
	GroundUp();
}

void AHuman::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}
}

void AHuman::GroundUp()
{
	while (true)
	{
		Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::Green);
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