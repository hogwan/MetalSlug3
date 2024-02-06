#pragma once
#include <EngineCore/Actor.h>
class ABackGroundMap : public AActor
{
public:
	// constructor destructor
	ABackGroundMap();
	~ABackGroundMap();

	// delete Function
	ABackGroundMap(const ABackGroundMap& _Other) = delete;
	ABackGroundMap(ABackGroundMap&& _Other) noexcept = delete;
	ABackGroundMap& operator=(const ABackGroundMap& _Other) = delete;
	ABackGroundMap& operator=(ABackGroundMap&& _Other) = delete;

	void SetMapImage(std::string_view _MapImageName);
	void SetColMapImage(std::string_view _MapImageName);

	UImageRenderer* GetRenderer()
	{
		return Renderer;
	}

	UImageRenderer* GetColRenderer()
	{
		return ColRenderer;
	}

	void SwitchDebug();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	UImageRenderer* ColRenderer = nullptr;
};

