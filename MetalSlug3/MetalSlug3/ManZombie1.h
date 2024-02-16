#pragma once
#include "Zombies.h"
class AManZombie1 : public AZombies
{
public:
	// constrcuter destructer
	AManZombie1();
	~AManZombie1();

	// delete Function
	AManZombie1(const AManZombie1& _Other) = delete;
	AManZombie1(AManZombie1&& _Other) noexcept = delete;
	AManZombie1& operator=(const AManZombie1& _Other) = delete;
	AManZombie1& operator=(AManZombie1&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime)	override;
};
