#pragma once
#include <EngineCore/Actor.h>
class AZombieVomitProjectile : public AActor
{
public:
	// constructor destructor
	AZombieVomitProjectile();
	~AZombieVomitProjectile();

	// delete Function
	AZombieVomitProjectile(const AZombieVomitProjectile& _Other) = delete;
	AZombieVomitProjectile(AZombieVomitProjectile&& _Other) noexcept = delete;
	AZombieVomitProjectile& operator=(const AZombieVomitProjectile& _Other) = delete;
	AZombieVomitProjectile& operator=(AZombieVomitProjectile&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DamageLogic();
	void GravityCheck();

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;

	float Gravity = 3000.0f;
};

