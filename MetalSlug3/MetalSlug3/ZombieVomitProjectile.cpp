#include "ZombieVomitProjectile.h"

AZombieVomitProjectile::AZombieVomitProjectile()
{
}

AZombieVomitProjectile::~AZombieVomitProjectile()
{
}

void AZombieVomitProjectile::BeginPlay()
{
	AActor::BeginPlay();
}

void AZombieVomitProjectile::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

void AZombieVomitProjectile::GravityCheck()
{
	AddActorLocation(FVector::Down * Gravity);
}
