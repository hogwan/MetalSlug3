#pragma once
#include "Zombies.h"
class ASoldierZombie : public AZombies
{
public:
	// constructor destructor
	ASoldierZombie();
	~ASoldierZombie();

	// delete Function
	ASoldierZombie(const ASoldierZombie& _Other) = delete;
	ASoldierZombie(ASoldierZombie&& _Other) noexcept = delete;
	ASoldierZombie& operator=(const ASoldierZombie& _Other) = delete;
	ASoldierZombie& operator=(ASoldierZombie&& _Other) = delete;
	
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Attack(float _DeltaTime, int _LaunchFrame, int _LaunchEffectFrame) override;
	void AttackStart() override;

	FVector JumpVector = { 5,-6};
	FVector ResultVector = { 0,0 };
	float JumpForce = 0.0f;
	float AttackGravity = 0.0f;

	int PrevFrame = -1;

	void FallCheck();
	void HitCheck();

	bool GravityOn = true;
	bool IsDeath = false;

	UCollision* AttackCollider = nullptr;
};

