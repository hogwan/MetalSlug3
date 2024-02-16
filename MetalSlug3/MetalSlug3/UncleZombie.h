#pragma once
#include "Zombies.h"
class AUncleZombie : public AZombies
{
public:
	// constructor destructor
	AUncleZombie();
	~AUncleZombie();

	// delete Function
	AUncleZombie(const AUncleZombie& _Other) = delete;
	AUncleZombie(AUncleZombie&& _Other) noexcept = delete;
	AUncleZombie& operator=(const AUncleZombie& _Other) = delete;
	AUncleZombie& operator=(AUncleZombie&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

