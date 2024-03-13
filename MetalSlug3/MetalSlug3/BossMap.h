#pragma once
#include <EngineCore/Actor.h>
class ABossMap : public AActor
{
public:
	// constructor destructor
	ABossMap();
	~ABossMap();

	// delete Function
	ABossMap(const ABossMap& _Other) = delete;
	ABossMap(ABossMap&& _Other) noexcept = delete;
	ABossMap& operator=(const ABossMap& _Other) = delete;
	ABossMap& operator=(ABossMap&& _Other) = delete;

	static bool LoadComplete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;
	UImageRenderer* SphereRenderer = nullptr;

	int PrevFrame = -1;

};

