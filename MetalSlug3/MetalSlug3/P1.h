#pragma once
#include <EngineCore/Actor.h>
class P1 : public AActor
{
public:
	// constructor destructor
	P1();
	~P1();

	// delete Function
	P1(const P1& _Other) = delete;
	P1(P1&& _Other) noexcept = delete;
	P1& operator=(const P1& _Other) = delete;
	P1& operator=(P1&& _Other) = delete;

private:
	void BeginPlay() override;
	UImageRenderer* Renderer = nullptr;
};

