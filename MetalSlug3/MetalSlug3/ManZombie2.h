#pragma once
#include "Zombies.h"
class AManZombie2 : public AZombies
{
public:
	// constructor destructor
	AManZombie2();
	~AManZombie2();

	// delete Function
	AManZombie2(const AManZombie2& _Other) = delete;
	AManZombie2(AManZombie2&& _Other) noexcept = delete;
	AManZombie2& operator=(const AManZombie2& _Other) = delete;
	AManZombie2& operator=(AManZombie2&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

