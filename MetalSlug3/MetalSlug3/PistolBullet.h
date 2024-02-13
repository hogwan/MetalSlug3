#pragma once
#include "Bullet.h"
class APistolBullet : public ABullet
{
public:
	// constructor destructor
	APistolBullet();
	~APistolBullet();

	// delete Function
	APistolBullet(const APistolBullet& _Other) = delete;
	APistolBullet(APistolBullet&& _Other) noexcept = delete;
	APistolBullet& operator=(const APistolBullet& _Other) = delete;
	APistolBullet& operator=(APistolBullet&& _Other) = delete;


protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
};

