#pragma once
#include <EngineCore/Level.h>
class EndLevel : public ULevel
{
public:
	// constructor destructor
	EndLevel();
	~EndLevel();

	// delete Function
	EndLevel(const EndLevel& _Other) = delete;
	EndLevel(EndLevel&& _Other) noexcept = delete;
	EndLevel& operator=(const EndLevel& _Other) = delete;
	EndLevel& operator=(EndLevel&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

