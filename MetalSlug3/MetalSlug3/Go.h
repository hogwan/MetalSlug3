#pragma once
#include "UIBase.h"
class AGo : public AUIBase
{
public:
	// constructor destructor
	AGo();
	~AGo();

	// delete Function
	AGo(const AGo& _Other) = delete;
	AGo(AGo&& _Other) noexcept = delete;
	AGo& operator=(const AGo& _Other) = delete;
	AGo& operator=(AGo&& _Other) = delete;

	UImageRenderer* Renderer = nullptr;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float AccTime = 0.0f;
	float TurnOnTime = 3.0f;

	bool Trigger = false;
};

