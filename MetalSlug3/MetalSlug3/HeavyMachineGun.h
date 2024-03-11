#pragma once
#include "Item.h"
class HeavyMachineGun : public AItem
{
public:
	// constructor destructor
	HeavyMachineGun();
	~HeavyMachineGun();

	// delete Function
	HeavyMachineGun(const HeavyMachineGun& _Other) = delete;
	HeavyMachineGun(HeavyMachineGun&& _Other) noexcept = delete;
	HeavyMachineGun& operator=(const HeavyMachineGun& _Other) = delete;
	HeavyMachineGun& operator=(HeavyMachineGun&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Action() override;
};

