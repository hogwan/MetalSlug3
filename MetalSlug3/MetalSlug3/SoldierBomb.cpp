#include "SoldierBomb.h"
#include "ContentsHelper.h"
#include "ExplosionEffect.h"

ASoldierBomb::ASoldierBomb()
{
}

ASoldierBomb::~ASoldierBomb()
{
	AExplosionEffect* Explosion = GetWorld()->SpawnActor<AExplosionEffect>();
	Explosion->SetActorLocation(GetActorLocation());
}

void ASoldierBomb::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->SetTransform({ {0,0}, {500,500} });
	Renderer->SetImage("SoldierBomb.png");
	Renderer->CreateAnimation("Flying", "SoldierBomb.png", 0, 19, 0.05f,true);
	Renderer->ChangeAnimation("Flying", false, 0, 0.05f);

	Collider = CreateCollision(MT3CollisionOrder::EnemyProjectile);
	Collider->SetScale({ 10,10 });
	Collider->SetColType(ECollisionType::Rect);
}

void ASoldierBomb::Tick(float _DeltaTime)
{
	AddActorLocation(MoveVector * _DeltaTime);
	GravityCheck(_DeltaTime);
	FallCheck();
	HitCheck();
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
		Destroy(0.001f);
	}
}
