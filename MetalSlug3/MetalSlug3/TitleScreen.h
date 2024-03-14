#pragma once
#include <EngineCore/Actor.h>
class TitleScreen : public AActor
{
public:
	// constructor destructor
	TitleScreen();
	~TitleScreen();

	// delete Function
	TitleScreen(const TitleScreen& _Other) = delete;
	TitleScreen(TitleScreen&& _Other) noexcept = delete;
	TitleScreen& operator=(const TitleScreen& _Other) = delete;
	TitleScreen& operator=(TitleScreen&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;
	UImageRenderer* Message = nullptr;

	float AccBlink = 0.f;
	float BlinkTime = 1.0f;
	int BlinkNum = 0;
 };

