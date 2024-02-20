#pragma once
#include "FrontMap.h"
class Front2 : public FrontMap
{
public:
	// constructor destructor
	Front2();
	~Front2();

	// delete Function
	Front2(const Front2& _Other) = delete;
	Front2(Front2&& _Other) noexcept = delete;
	Front2& operator=(const Front2& _Other) = delete;
	Front2& operator=(Front2&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

