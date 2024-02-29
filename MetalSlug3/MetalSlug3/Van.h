#pragma once
#include "Enemy.h"
class AVan : public AEnemy
{
public:
	// constrcuter destructer
	AVan();
	~AVan();

	// delete Function
	AVan(const AVan& _Other) = delete;
	AVan(AVan&& _Other) noexcept = delete;
	AVan& operator=(const AVan& _Other) = delete;
	AVan& operator=(AVan&& _Other) noexcept = delete;

	void Damaged(int _Damage)
	{
		Hp -= _Damage;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime)	override;

	UImageRenderer* SoldierSpawnRenderer = nullptr;

	bool Spawning = false;

	float AccSpawnTime = 0.0f;
	float SpawnCoolTime = 3.0f;

	int MaxHp = 8;

	int PrevFrame = -1;
};

