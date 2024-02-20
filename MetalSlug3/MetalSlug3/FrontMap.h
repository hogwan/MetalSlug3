#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"
class FrontMap : public AActor
{
public:
	// constructor destructor
	FrontMap();
	~FrontMap();

	// delete Function
	FrontMap(const FrontMap& _Other) = delete;
	FrontMap(FrontMap&& _Other) noexcept = delete;
	FrontMap& operator=(const FrontMap& _Other) = delete;
	FrontMap& operator=(FrontMap&& _Other) = delete;

	UImageRenderer* Renderer = nullptr;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	
};

