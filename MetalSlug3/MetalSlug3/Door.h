#pragma once
#include <EngineCore/Actor.h>
class Door : public AActor
{
public:
	// constructor destructor
	Door();
	~Door();

	// delete Function
	Door(const Door& _Other) = delete;
	Door(Door&& _Other) noexcept = delete;
	Door& operator=(const Door& _Other) = delete;
	Door& operator=(Door&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;

	float Speed = 0.0f;
	float Accel = 500.0f;

	bool Trigger = false;
};

