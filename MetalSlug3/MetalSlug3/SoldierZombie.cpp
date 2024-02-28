#include "SoldierZombie.h"

SoldierZombie::SoldierZombie()
{
}

SoldierZombie::~SoldierZombie()
{
}

void SoldierZombie::BeginPlay()
{
	AZombies::BeginPlay();
}

void SoldierZombie::Tick(float _DeltaTime)
{
	AZombies::Tick(_DeltaTime);
}

void SoldierZombie::Attack(float _DeltaTime, int _LaunchFrame, int _LaunchEffectFrame)
{
}
