#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"
class AFrontMap : public AActor
{
public:
	// constructor destructor
	AFrontMap();
	~AFrontMap();

	// delete Function
	AFrontMap(const AFrontMap& _Other) = delete;
	AFrontMap(AFrontMap&& _Other) noexcept = delete;
	AFrontMap& operator=(const AFrontMap& _Other) = delete;
	AFrontMap& operator=(AFrontMap&& _Other) = delete;

	UImageRenderer* Renderer = nullptr;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	
};

