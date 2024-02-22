#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"
class AEnemy : public AActor
{
public:
	// constrcuter destructer
	AEnemy();
	~AEnemy();

	// delete Function
	AEnemy(const AEnemy& _Other) = delete;
	AEnemy(AEnemy&& _Other) noexcept = delete;
	AEnemy& operator=(const AEnemy& _Other) = delete;
	AEnemy& operator=(AEnemy&& _Other) noexcept = delete;

	void Damaged(int _Damage)
	{
		Hp -= _Damage;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime)	override;

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;
	int Hp = 1;
};

