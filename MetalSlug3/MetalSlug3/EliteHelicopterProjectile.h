#pragma once
#include <EngineCore/Actor.h>
class EliteHelicopterProjectile : public AActor
{
public:
	// constructor destructor
	EliteHelicopterProjectile();
	~EliteHelicopterProjectile();

	// delete Function
	EliteHelicopterProjectile(const EliteHelicopterProjectile& _Other) = delete;
	EliteHelicopterProjectile(EliteHelicopterProjectile&& _Other) noexcept = delete;
	EliteHelicopterProjectile& operator=(const EliteHelicopterProjectile& _Other) = delete;
	EliteHelicopterProjectile& operator=(EliteHelicopterProjectile&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;

	void FallCheck();
	void HitCheck();
};

