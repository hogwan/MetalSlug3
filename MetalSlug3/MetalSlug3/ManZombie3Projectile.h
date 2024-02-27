#pragma once
#include "ZombiesProjectile.h"
class AManZombie3Projectile : public AZombiesProjectile
{
public:
	// constructor destructor
	AManZombie3Projectile();
	~AManZombie3Projectile();

	// delete Function
	AManZombie3Projectile(const AManZombie3Projectile& _Other) = delete;
	AManZombie3Projectile(AManZombie3Projectile&& _Other) noexcept = delete;
	AManZombie3Projectile& operator=(const AManZombie3Projectile& _Other) = delete;
	AManZombie3Projectile& operator=(AManZombie3Projectile&& _Other) = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

};

