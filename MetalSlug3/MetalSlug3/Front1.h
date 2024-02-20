#pragma once
#include "FrontMap.h"
class AFront1 : public AFrontMap
{
public:
	// constructor destructor
	AFront1();
	~AFront1();

	// delete Function
	AFront1(const AFront1& _Other) = delete;
	AFront1(AFront1&& _Other) noexcept = delete;
	AFront1& operator=(const AFront1& _Other) = delete;
	AFront1& operator=(AFront1&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

