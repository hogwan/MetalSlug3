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
	
	void GoDown();
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Gravity(float _DeltaTime);
	void UpLayCheck();

	float Speed = 0.0f;
	float Accel = 500.0f;

	FVector InitScale = { 100.f,330.f };

	bool IsLand = false;
	bool UpLay = false;
	bool DownLay = false;

	float UpLayerSpeed = 0.0f;
	float AccDamage = 0.0f;
	float DamageTime = 0.03f;

	std::string CurAnim = "None";

	bool Trigger = false;

	UCollision* UpLayCollision = nullptr;

};

