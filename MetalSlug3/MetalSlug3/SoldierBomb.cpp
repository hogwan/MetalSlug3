#include "SoldierBomb.h"
#include "ContentsHelper.h"

ASoldierBomb::ASoldierBomb()
{
}

ASoldierBomb::~ASoldierBomb()
{
}

void ASoldierBomb::BeginPlay()
{
}

void ASoldierBomb::Tick(float _DeltaTime)
{
	AddActorLocation(MoveVector * _DeltaTime);
	GravityCheck(_DeltaTime);
	FallCheck();
}

void ASoldierBomb::GravityCheck(float _DeltaTime)
{
	MoveVector += Gravity * _DeltaTime;
}

void ASoldierBomb::FallCheck()
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{

	}
}

void ASoldierBomb::HitCheck()
{
	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::Player, Result))
	{

	}
}
