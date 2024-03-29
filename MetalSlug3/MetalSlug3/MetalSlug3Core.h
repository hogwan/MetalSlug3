#pragma once
#include <EngineCore/EngineCore.h>
class MetalSlug3Core : public UEngineCore
{
public:
	// constructor destructor
	MetalSlug3Core();
	~MetalSlug3Core();

	// delete Function
	MetalSlug3Core(const MetalSlug3Core& _Other) = delete;
	MetalSlug3Core(MetalSlug3Core&& _Other) noexcept = delete;
	MetalSlug3Core& operator=(const MetalSlug3Core& _Other) = delete;
	MetalSlug3Core& operator=(MetalSlug3Core&& _Other) = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

