#pragma once
#include <EngineCore/Actor.h>
class CameraManager : public AActor
{
public:
	// constructor destructor
	CameraManager();
	~CameraManager();

	// delete Function
	CameraManager(const CameraManager& _Other) = delete;
	CameraManager(CameraManager&& _Other) noexcept = delete;
	CameraManager& operator=(const CameraManager& _Other) = delete;
	CameraManager& operator=(CameraManager&& _Other) = delete;

	int CameraMode = 0;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	float CameraSpeed = 0.0f;
	float Cameraacceleration = 300.0f;
	float MaxCameraSpeed = 300.0f;
	void CameraUpdate(float _DeltaTime);

};

