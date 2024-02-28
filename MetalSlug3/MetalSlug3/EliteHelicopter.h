#pragma once
#include "Enemy.h"
class AEliteHelicopter : public AEnemy
{
public:
	// constructor destructor
	AEliteHelicopter();
	~AEliteHelicopter();

	// delete Function
	AEliteHelicopter(const AEliteHelicopter& _Other) = delete;
	AEliteHelicopter(AEliteHelicopter&& _Other) noexcept = delete;
	AEliteHelicopter& operator=(const AEliteHelicopter& _Other) = delete;
	AEliteHelicopter& operator=(AEliteHelicopter&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Propeller = nullptr;


	float Speed = 0.0f;
	float TargetY = 700.0f;
};

