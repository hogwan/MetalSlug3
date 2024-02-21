#pragma once
#include <EngineCore/Actor.h>
class AUIBase : public AActor
{
public:
	// constructor destructor
	AUIBase();
	~AUIBase();

	// delete Function
	AUIBase(const AUIBase& _Other) = delete;
	AUIBase(AUIBase&& _Other) noexcept = delete;
	AUIBase& operator=(const AUIBase& _Other) = delete;
	AUIBase& operator=(AUIBase&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

