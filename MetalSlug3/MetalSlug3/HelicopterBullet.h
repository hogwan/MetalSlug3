#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class AHelicopterBullet : public AActor
{
public:
	// constrcuter destructer
	AHelicopterBullet();
	~AHelicopterBullet();

	// delete Function
	AHelicopterBullet(const AHelicopterBullet& _Other) = delete;
	AHelicopterBullet(AHelicopterBullet&& _Other) noexcept = delete;
	AHelicopterBullet& operator=(const AHelicopterBullet& _Other) = delete;
	AHelicopterBullet& operator=(AHelicopterBullet&& _Other) noexcept = delete;

	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

	void SetSpeed(float _Speed)
	{
		Speed = _Speed;
	}
protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

	FVector Dir = FVector::Zero;
	float Speed = 300.0f;
	bool IsDestroy = false;
	UImageRenderer* ColRenderer = nullptr;
	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;
};
