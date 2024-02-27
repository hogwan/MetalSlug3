#pragma once
#include "Zombies.h"
class AManZombie3
	: public AZombies
{
public:
	// constructor destructor
	AManZombie3();
	~AManZombie3();

	// delete Function
	AManZombie3(const AManZombie3& _Other) = delete;
	AManZombie3(AManZombie3&& _Other) noexcept = delete;
	AManZombie3& operator=(const AManZombie3& _Other) = delete;
	AManZombie3& operator=(AManZombie3&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Attack(float _DeltaTime, int _LaunchFrame, int _LaunchEffectFrame) override;
};

