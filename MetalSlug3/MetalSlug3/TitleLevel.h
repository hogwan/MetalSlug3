#pragma once
#include <EngineCore/Level.h>
class TitleLevel : public ULevel
{
public:
	// constructor destructor
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	float AccWait = 0.0f;
	float WaitTime = 1.0f;
	bool Trigger = false;
};

