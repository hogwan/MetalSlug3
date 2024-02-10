#pragma once
#include <EngineCore\Level.h>
class TestLevel : public ULevel
{
public:
	// constructor destructor
	TestLevel();
	~TestLevel();

	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) = delete;

protected:
	void BeginPlay() override;
};

