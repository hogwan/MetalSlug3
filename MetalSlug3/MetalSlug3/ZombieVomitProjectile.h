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

	UCollision* GetCollider()
	{
		return Collider;
	}

	UImageRenderer* GetRenderer()
	{
		return Renderer;
	}

	void SetDir(FVector _Dir)
	{
		Dir = _Dir;
	}

	void SetNumber(int _Number)
	{
		Number = _Number;
	}
	bool End = false;
	bool RendererEnd = false;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DamageLogic();
	FVector Dir = FVector::Zero;
	int Number = 0;
	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;

	float Gravity = 500.0f;

};

