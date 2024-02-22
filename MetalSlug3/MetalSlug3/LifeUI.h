#pragma once
#include "UIBase.h"
class ALifeUI
	: public AUIBase
{
public:
	// constructor destructor
	ALifeUI();
	~ALifeUI();

	// delete Function
	ALifeUI(const ALifeUI& _Other) = delete;
	ALifeUI(ALifeUI&& _Other) noexcept = delete;
	ALifeUI& operator=(const ALifeUI& _Other) = delete;
	ALifeUI& operator=(ALifeUI&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	void SwitchNumber(int _Count, UImageRenderer* _Renderer);

	UImageRenderer* Renderer0 = nullptr;
	UImageRenderer* Renderer1 = nullptr;
	UImageRenderer* Renderer2 = nullptr;
	UImageRenderer* Renderer3 = nullptr;
	UImageRenderer* Renderer4 = nullptr;
};

