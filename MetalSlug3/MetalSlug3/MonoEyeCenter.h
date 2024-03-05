#pragma once
#include <EngineCore/Actor.h>
#include "MonoEyes.h"
class AMonoEyeCenter : public AActor
{
public:
	// constructor destructor
	AMonoEyeCenter();
	~AMonoEyeCenter();

	// delete Function
	AMonoEyeCenter(const AMonoEyeCenter& _Other) = delete;
	AMonoEyeCenter(AMonoEyeCenter&& _Other) noexcept = delete;
	AMonoEyeCenter& operator=(const AMonoEyeCenter& _Other) = delete;
	AMonoEyeCenter& operator=(AMonoEyeCenter&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	std::vector<AMonoEyes*> MonoEyes;
};

