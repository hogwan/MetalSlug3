#pragma once
#include "MT3Object.h"
#include <EnginePlatform/EngineSound.h>
class AEliteHelicopterProjectile : public AMT3Object
{
public:
	// constructor destructor
	AEliteHelicopterProjectile();
	~AEliteHelicopterProjectile();

	// delete Function
	AEliteHelicopterProjectile(const AEliteHelicopterProjectile& _Other) = delete;
	AEliteHelicopterProjectile(AEliteHelicopterProjectile&& _Other) noexcept = delete;
	AEliteHelicopterProjectile& operator=(const AEliteHelicopterProjectile& _Other) = delete;
	AEliteHelicopterProjectile& operator=(AEliteHelicopterProjectile&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;

	float Speed = 0.0f;
	float Accel = 300.0f;

	void FallCheck();
	void HitCheck();

	UEngineSoundPlayer Sound;
};

