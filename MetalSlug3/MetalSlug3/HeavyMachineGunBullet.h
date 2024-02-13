#pragma once
class HeavyMachineGunBullet
{
public:
	// constructor destructor
	HeavyMachineGunBullet();
	~HeavyMachineGunBullet();

	// delete Function
	HeavyMachineGunBullet(const HeavyMachineGunBullet& _Other) = delete;
	HeavyMachineGunBullet(HeavyMachineGunBullet&& _Other) noexcept = delete;
	HeavyMachineGunBullet& operator=(const HeavyMachineGunBullet& _Other) = delete;
	HeavyMachineGunBullet& operator=(HeavyMachineGunBullet&& _Other) = delete;
};

