#include "ScreenCollision.h"
#include "ContentsHelper.h"

AScreenCollision::AScreenCollision()
{
}

AScreenCollision::~AScreenCollision()
{
}

void AScreenCollision::BeginPlay()
{
	Collider = CreateCollision(MT3CollisionOrder::Screen);
	Collider->SetColType(ECollisionType::Rect);
}

void AScreenCollision::Tick(float _DeltaTime)
{
	FVector Offset = { 400,300 };
	FVector Pos = GetWorld()->GetCameraPos() + Offset;
	Collider->SetTransform({ Pos,{1000,800} });
}
