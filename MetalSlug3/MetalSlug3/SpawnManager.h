#pragma once
#include <EngineCore/Actor.h>
class SpawnManager : public AActor
{
public:
	// constructor destructor
	SpawnManager();
	~SpawnManager();

	// delete Function
	SpawnManager(const SpawnManager& _Other) = delete;
	SpawnManager(SpawnManager&& _Other) noexcept = delete;
	SpawnManager& operator=(const SpawnManager& _Other) = delete;
	SpawnManager& operator=(SpawnManager&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void TestSpawn();
	int SpawnNumber = 0;

	float AccTime = 0.0f;
	float MonoEyeSpawnTime = 1.0f;
	float WaitTime = 2.0f;
	int MonoSpawnNum = 0;

	class AMonoEyeCenter* MC = nullptr;
	bool Trigger = false;

};

