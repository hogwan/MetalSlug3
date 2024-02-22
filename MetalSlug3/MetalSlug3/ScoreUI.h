#pragma once
#include "UIBase.h"
class AScoreUI : public AUIBase
{
public:
	// constructor destructor
	AScoreUI();
	~AScoreUI();

	// delete Function
	AScoreUI(const AScoreUI& _Other) = delete;
	AScoreUI(AScoreUI&& _Other) noexcept = delete;
	AScoreUI& operator=(const AScoreUI& _Other) = delete;
	AScoreUI& operator=(AScoreUI&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int Score = 0;
	UImageRenderer* Units = nullptr;
	UImageRenderer* Tens = nullptr;
	UImageRenderer* Hundreds = nullptr;
	UImageRenderer* Thousands = nullptr;
	UImageRenderer* TenThousands = nullptr;
	UImageRenderer* HundredThousands = nullptr;
	UImageRenderer* Millions = nullptr;

	void DecideNumber(int _Count);
	void SwitchNumber(int _Count, UImageRenderer* _Renderer);

	std::string Num;
};

