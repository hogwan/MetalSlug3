#include "EliteHelicopterProjectile.h"
#include "ContentsHelper.h"
#include "HugeBombExplosionEffect.h"

EliteHelicopterProjectile::EliteHelicopterProjectile()
{
}

EliteHelicopterProjectile::~EliteHelicopterProjectile()
{
	AHugeBombExplosionEffect* Effect = GetWorld()->SpawnActor<AHugeBombExplosionEffect>();
	Effect->SetActorLocation(GetActorLocation());
}

void EliteHelicopterProjectile::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->SetImage("EliteHelicopter_Projectile.png");
	Renderer->CreateAnimation("Projectile", "EliteHelicopter_Projectile.png", 0, 13, 0.08f, true);
	Renderer->ChangeAnimation("Projectile", false, 0, 0.08f);

	Collider = CreateCollision(MT3CollisionOrder::EnemyProjectile);
	Collider->SetScale({ 30,50 });
	Collider->SetPosition({0,-25});
	Collider->SetColType(ECollisionType::Rect);

}

void EliteHelicopterProjectile::Tick(float _DeltaTime)
{
	AddActorLocation(FVector::Down * 300.0f * _DeltaTime);

	FallCheck();
	HitCheck();
}

void EliteHelicopterProjectile::FallCheck()
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		Destroy();
	}
}

void EliteHelicopterProjectile::HitCheck()
{
	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::Player, Result))
	{
		Destroy(0.001f);
	}
}
