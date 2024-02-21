#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"
class ABackMap : public AActor
{
public:
	// constructor destructor
	ABackMap();
	~ABackMap();

	// delete Function
	ABackMap(const ABackMap& _Other) = delete;
	ABackMap(ABackMap&& _Other) noexcept = delete;
	ABackMap& operator=(const ABackMap& _Other) = delete;
	ABackMap& operator=(ABackMap&& _Other) = delete;

	UImageRenderer* Renderer = nullptr;
	float MoveRatio = 0.27357286f;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

