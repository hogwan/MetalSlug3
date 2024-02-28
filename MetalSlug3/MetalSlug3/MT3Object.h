#pragma once
#include <EngineCore/Actor.h>
class AMT3Object : public AActor
{
public:
	// constructor destructor
	AMT3Object();
	~AMT3Object();

	// delete Function
	AMT3Object(const AMT3Object& _Other) = delete;
	AMT3Object(AMT3Object&& _Other) noexcept = delete;
	AMT3Object& operator=(const AMT3Object& _Other) = delete;
	AMT3Object& operator=(AMT3Object&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Release();
};

