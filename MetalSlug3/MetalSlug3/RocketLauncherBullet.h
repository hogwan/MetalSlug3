#pragma once
#include "Bullet.h"
class RocketLauncherBullet : public ABullet
{
public:
	// constructor destructor
	RocketLauncherBullet();
	~RocketLauncherBullet();

	// delete Function
	RocketLauncherBullet(const RocketLauncherBullet& _Other) = delete;
	RocketLauncherBullet(RocketLauncherBullet&& _Other) noexcept = delete;
	RocketLauncherBullet& operator=(const RocketLauncherBullet& _Other) = delete;
	RocketLauncherBullet& operator=(RocketLauncherBullet&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	bool Trigger = false;

};

