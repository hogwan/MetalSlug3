#pragma once
#include "MT3Object.h"
class ADeathBall : public AMT3Object
{
public:
	// constructor destructor
	ADeathBall();
	~ADeathBall();

	// delete Function
	ADeathBall(const ADeathBall& _Other) = delete;
	ADeathBall(ADeathBall&& _Other) noexcept = delete;
	ADeathBall& operator=(const ADeathBall& _Other) = delete;
	ADeathBall& operator=(ADeathBall&& _Other) = delete;

	void SetDir(FVector _DirVector)
	{
		DirVector = _DirVector;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	
	FVector DirVector = FVector::Zero;
	float Speed = 50.0f;

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;
};

