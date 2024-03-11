#include "Item.h"
#include "ContentsHelper.h"

AItem::AItem()
{
}

AItem::~AItem()
{
}

void AItem::BeginPlay()
{
	AMT3Object::BeginPlay();
	Renderer = CreateImageRenderer(MT3RenderOrder::Item);
	Renderer->SetTransform({ { 0,0 }, { 500, 500 } });

	Collider = CreateCollision(MT3CollisionOrder::Item);
	Collider->SetScale({ 50,50 });
	Collider->SetPosition({ 0,-25 });
	Collider->SetColType(ECollisionType::Rect);
}

void AItem::Tick(float _DeltaTime)
{
	AMT3Object::Tick(_DeltaTime);
	GravityCheck(_DeltaTime);

	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::Player, Result))
	{
		Action();
	}
}

void AItem::Action()
{
}

void AItem::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}
}
