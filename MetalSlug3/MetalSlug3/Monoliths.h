#pragma once
#include "Enemy.h"

class AMonoliths : public  AEnemy
{
public:
	// constructor destructor
	AMonoliths();
	~AMonoliths();

	// delete Function
	AMonoliths(const AMonoliths& _Other) = delete;
	AMonoliths(AMonoliths&& _Other) noexcept = delete;
	AMonoliths& operator=(const AMonoliths& _Other) = delete;
	AMonoliths& operator=(AMonoliths&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Gravity(float _DeltaTime);

	float Speed = 0.0f;
	float Accel = 500.0f;

	FVector InitScale = { 150.f,330.f };

	bool IsLand = false;
};

