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

	int SpawnNumber = 0;
};

