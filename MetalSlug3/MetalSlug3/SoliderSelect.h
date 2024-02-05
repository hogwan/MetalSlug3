#pragma once
#include <EngineCore/Actor.h>
class SoliderSelect : public AActor
{
public:
	// constructor destructor
	SoliderSelect();
	~SoliderSelect();

	// delete Function
	SoliderSelect(const SoliderSelect& _Other) = delete;
	SoliderSelect(SoliderSelect&& _Other) noexcept = delete;
	SoliderSelect& operator=(const SoliderSelect& _Other) = delete;
	SoliderSelect& operator=(SoliderSelect&& _Other) = delete;
	void BeginPlay() override;
private:
	UImageRenderer* ThisRenderer = nullptr;
};

