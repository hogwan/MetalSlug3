#pragma once
#include <EngineCore/Actor.h>
class Panel : public AActor
{
public:
	// constructor destructor
	Panel();
	~Panel();

	// delete Function
	Panel(const Panel& _Other) = delete;
	Panel(Panel&& _Other) noexcept = delete;
	Panel& operator=(const Panel& _Other) = delete;
	Panel& operator=(Panel&& _Other) = delete;
	void BeginPlay() override;
private:
	UImageRenderer* ThisRenderer = nullptr;
};

