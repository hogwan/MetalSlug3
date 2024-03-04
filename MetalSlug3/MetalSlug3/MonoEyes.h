#pragma once
#include "Enemy.h"
class MonoEyes : public AEnemy
{
public:
	// constructor destructor
	MonoEyes();
	~MonoEyes();

	// delete Function
	MonoEyes(const MonoEyes& _Other) = delete;
	MonoEyes(MonoEyes&& _Other) noexcept = delete;
	MonoEyes& operator=(const MonoEyes& _Other) = delete;
	MonoEyes& operator=(MonoEyes&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate();
	void StateChange();

	void None(float _DeltaTime);
	void Spawn(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Attack(float _DeltaTime);

	void NoneStart();
	void SpawnStart();
	void IdleStart();
	void AttackStart();

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;
};

