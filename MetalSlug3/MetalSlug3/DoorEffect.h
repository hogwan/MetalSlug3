#pragma once
#include <EngineCore/Actor.h>
class DoorEffect : public AActor
{
public:
	// constructor destructor
	DoorEffect();
	~DoorEffect();

	// delete Function
	DoorEffect(const DoorEffect& _Other) = delete;
	DoorEffect(DoorEffect&& _Other) noexcept = delete;
	DoorEffect& operator=(const DoorEffect& _Other) = delete;
	DoorEffect& operator=(DoorEffect&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;
};

