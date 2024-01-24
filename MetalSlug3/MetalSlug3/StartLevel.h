#pragma once
#include <EngineCore\Level.h>
class StartLevel : public ULevel
{
public:
	// constructor destructor
	StartLevel();
	~StartLevel();

	// delete Function
	StartLevel(const StartLevel& _Other) = delete;
	StartLevel(StartLevel&& _Other) noexcept = delete;
	StartLevel& operator=(const StartLevel& _Other) = delete;
	StartLevel& operator=(StartLevel&& _Other) = delete;

protected:
	void BeginPlay() override;
};

