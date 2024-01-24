#pragma once
#include <EngineCore/EngineCore.h>
class MetalSlug3Core : public EngineCore
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
	void Start() override;
	void Update() override;
	void End() override;

private:
};

