#include "ZombieVomitProjectile.h"
#include "ContentsHelper.h"

AZombieVomitProjectile::AZombieVomitProjectile()
{
}

AZombieVomitProjectile::~AZombieVomitProjectile()
{
}

void AZombieVomitProjectile::BeginPlay()
{
	AActor::BeginPlay();

	Collider = CreateCollision(MT3CollisionOrder::PlayerBullet);
	Collider->SetScale({ 50,20 });

	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->CreateAnimation("0-0_Right", "Marco_ZombieVomitProjectile.png", 0, 0, 0.05f);
	Renderer->CreateAnimation("0-1_Right", "Marco_ZombieVomitProjectile.png", 1, 1, 0.05f);
	Renderer->CreateAnimation("1-0_Right", "Marco_ZombieVomitProjectile.png", 2, 2, 0.05f);

	Renderer->SetImage("Marco_ZombieVomitProjectile.png");
	Renderer->SetTransform({ { 0,0 }, { 500,500 } });
	Renderer->ChangeAnimation("0-0");
}

void AZombieVomitProjectile::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

void AZombieVomitProjectile::DamageLogic()
{
}

void AZombieVomitProjectile::GravityCheck()
{
	AddActorLocation(FVector::Down * Gravity);
}
