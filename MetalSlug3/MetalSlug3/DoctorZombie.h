#pragma once
#include "Zombies.h"
class ADoctorZombie :public AZombies
{
public:
	// constructor destructor
	ADoctorZombie();
	~ADoctorZombie();

	// delete Function
	ADoctorZombie(const ADoctorZombie& _Other) = delete;
	ADoctorZombie(ADoctorZombie&& _Other) noexcept = delete;
	ADoctorZombie& operator=(const ADoctorZombie& _Other) = delete;
	ADoctorZombie& operator=(ADoctorZombie&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

