#pragma once
#include "FrontMap.h"
class AFront2 : public AFrontMap
{
public:
	// constructor destructor
	AFront2();
	~AFront2();

	// delete Function
	AFront2(const AFront2& _Other) = delete;
	AFront2(AFront2&& _Other) noexcept = delete;
	AFront2& operator=(const AFront2& _Other) = delete;
	AFront2& operator=(AFront2&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

