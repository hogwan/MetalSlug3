#pragma once
#include "ExplosionEffect.h"
class ADeathBallExplosion : public AExplosionEffect
{
public:
	// constructor destructor
	ADeathBallExplosion();
	~ADeathBallExplosion();

	// delete Function
	ADeathBallExplosion(const ADeathBallExplosion& _Other) = delete;
	ADeathBallExplosion(ADeathBallExplosion&& _Other) noexcept = delete;
	ADeathBallExplosion& operator=(const ADeathBallExplosion& _Other) = delete;
	ADeathBallExplosion& operator=(ADeathBallExplosion&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

};

