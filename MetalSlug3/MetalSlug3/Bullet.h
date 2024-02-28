#pragma once
#include "MT3Object.h"
#include "ContentsHelper.h"

// Ό³Έν :
class ABullet : public AMT3Object
{
public:
	// constrcuter destructer
	ABullet();
	~ABullet();

	// delete Function
	ABullet(const ABullet& _Other) = delete;
	ABullet(ABullet&& _Other) noexcept = delete;
	ABullet& operator=(const ABullet& _Other) = delete;
	ABullet& operator=(ABullet&& _Other) noexcept = delete;

	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

	int GetDamage()
	{
		return Damage;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

	FVector Dir = FVector::Zero;
	float Speed = 1000.0f;
	bool IsDestroy = false;
	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;

	int Damage = 1;
};

