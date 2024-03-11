#pragma once
#include "Bullet.h"
class AFlameShotBullet : public ABullet
{
public:
	// constructor destructor
	AFlameShotBullet();
	~AFlameShotBullet();

	// delete Function
	AFlameShotBullet(const AFlameShotBullet& _Other) = delete;
	AFlameShotBullet(AFlameShotBullet&& _Other) noexcept = delete;
	AFlameShotBullet& operator=(const AFlameShotBullet& _Other) = delete;
	AFlameShotBullet& operator=(AFlameShotBullet&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	float AccDamageTick = 0.0f;
	float DamageTick = 0.05f;
};

