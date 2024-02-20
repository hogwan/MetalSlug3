#pragma once
#include "FrontMap.h"
class Front1 : public FrontMap
{
public:
	// constructor destructor
	Front1();
	~Front1();

	// delete Function
	Front1(const Front1& _Other) = delete;
	Front1(Front1&& _Other) noexcept = delete;
	Front1& operator=(const Front1& _Other) = delete;
	Front1& operator=(Front1&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

