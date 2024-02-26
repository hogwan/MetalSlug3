#include "SoldierBomb.h"
#include "ContentsHelper.h"
#include "ExplosionEffect.h"

ASoldierBomb::ASoldierBomb()
{
}

ASoldierBomb::~ASoldierBomb()
{
	ExplosionEffect* Explosion = GetWorld()->SpawnActor<ExplosionEffect>();
	Explosion->SetActorLocation(GetActorLocation());
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
		Destroy();
	}
}

void ASoldierBomb::HitCheck()
{
	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::Player, Result))
	{
		Destroy();
	}
}
