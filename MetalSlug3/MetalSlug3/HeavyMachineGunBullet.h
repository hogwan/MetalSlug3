#pragma once
#include "Bullet.h"
class AHeavyMachineGunBullet
	: public ABullet
{
public:
	// constructor destructor
	AHeavyMachineGunBullet();
	~AHeavyMachineGunBullet();

	// delete Function
	AHeavyMachineGunBullet(const AHeavyMachineGunBullet& _Other) = delete;
	AHeavyMachineGunBullet(AHeavyMachineGunBullet&& _Other) noexcept = delete;
	AHeavyMachineGunBullet& operator=(const AHeavyMachineGunBullet& _Other) = delete;
	AHeavyMachineGunBullet& operator=(AHeavyMachineGunBullet&& _Other) = delete;

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
};

