#pragma once
#include <EngineCore/Actor.h>
class ThunderCloudObj : public AActor
{
public:
	// constructor destructor
	ThunderCloudObj();
	~ThunderCloudObj();

	// delete Function
	ThunderCloudObj(const ThunderCloudObj& _Other) = delete;
	ThunderCloudObj(ThunderCloudObj&& _Other) noexcept = delete;
	ThunderCloudObj& operator=(const ThunderCloudObj& _Other) = delete;
	ThunderCloudObj& operator=(ThunderCloudObj&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;
};

