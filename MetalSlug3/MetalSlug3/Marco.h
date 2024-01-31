#pragma once
#include <EngineCore\Actor.h>
class Marco : public AActor
{
public:
	// constructor destructor
	Marco();
	~Marco();

	// delete Function
	Marco(const Marco& _Other) = delete;
	Marco(Marco&& _Other) noexcept = delete;
	Marco& operator=(const Marco& _Other) = delete;
	Marco& operator=(Marco&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* UpperBodyRenderer;
	UImageRenderer* LowerBodyRenderer;
	UImageRenderer* AllBodyRenderer;
	UImageRenderer* ZombieArmRenderer;

	int UpdateStatus;
	int RenderStatus;

	int Dir;
	bool InAir;
	bool EquipRifle;
};

