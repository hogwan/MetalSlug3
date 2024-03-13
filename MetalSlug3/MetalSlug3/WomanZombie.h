#pragma once
#include "Zombies.h"
class AWomanZombie : public AZombies
{
public:
	// constructor destructor
	AWomanZombie();
	~AWomanZombie();

	// delete Function
	AWomanZombie(const AWomanZombie& _Other) = delete;
	AWomanZombie(AWomanZombie&& _Other) noexcept = delete;
	AWomanZombie& operator=(const AWomanZombie& _Other) = delete;
	AWomanZombie& operator=(AWomanZombie&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DeathStart() override;
};

