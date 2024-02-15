#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
enum class State {
	None,
	Flying,
	CollideGround,
	CollideObject,
};

class AZombiesProjectile : public AActor
{
public:
	// constrcuter destructer
	AZombiesProjectile();
	~AZombiesProjectile();

	// delete Function
	AZombiesProjectile(const AZombiesProjectile& _Other) = delete;
	AZombiesProjectile(AZombiesProjectile&& _Other) noexcept = delete;
	AZombiesProjectile& operator=(const AZombiesProjectile& _Other) = delete;
	AZombiesProjectile& operator=(AZombiesProjectile&& _Other) noexcept = delete;

	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

	void GravityCheck(float _DeltaTime);
	std::string DirCheck(std::string _Name);

	void StateUpdate(float _DeltaTime);
	void StateChange(State _State);

	void None(float _DeltaTime);
	void Flying(float _DeltaTime);
	void CollideGround(float _DeltaTime);
	void CollideObject(float _DeltaTime);


	void NoneStart();
	void FlyingStart();
	void CollideGroundStart();
	void CollideObjectStart();

	FVector Dir = FVector::Zero;
	FVector ShootVector = { 5,-4 };
	FVector ResultVector = FVector::Zero;
	FVector Gravity = { 0.0f,500.0f };

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;

	State CurState = State::Flying;

	std::string CurAnimName = "None";

	float ShootPower = 200.0f;

};
