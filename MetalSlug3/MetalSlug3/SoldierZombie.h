#pragma once
#include "Zombies.h"
class SoldierZombie : public AZombies
{
public:
	// constructor destructor
	SoldierZombie();
	~SoldierZombie();

	// delete Function
	SoldierZombie(const SoldierZombie& _Other) = delete;
	SoldierZombie(SoldierZombie&& _Other) noexcept = delete;
	SoldierZombie& operator=(const SoldierZombie& _Other) = delete;
	SoldierZombie& operator=(SoldierZombie&& _Other) = delete;
	
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Attack(float _DeltaTime, int _LaunchFrame, int _LaunchEffectFrame) override;
};

