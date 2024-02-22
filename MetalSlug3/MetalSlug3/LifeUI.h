#pragma once
#include "UIBase.h"
class LifeUI : public AUIBase
{
public:
	// constructor destructor
	LifeUI();
	~LifeUI();

	// delete Function
	LifeUI(const LifeUI& _Other) = delete;
	LifeUI(LifeUI&& _Other) noexcept = delete;
	LifeUI& operator=(const LifeUI& _Other) = delete;
	LifeUI& operator=(LifeUI&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer0 = nullptr;
	UImageRenderer* Renderer1 = nullptr;
	UImageRenderer* Renderer2 = nullptr;
	UImageRenderer* Renderer3 = nullptr;
	UImageRenderer* Renderer4 = nullptr;
};

