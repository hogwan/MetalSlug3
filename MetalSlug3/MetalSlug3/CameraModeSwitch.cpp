#include "CameraModeSwitch.h"
#include "ContentsHelper.h"

ACameraModeSwitch::ACameraModeSwitch()
{
}

ACameraModeSwitch::~ACameraModeSwitch()
{
}

void ACameraModeSwitch::BeginPlay()
{
	Collider = CreateCollision(MT3CollisionOrder::CameraSwitch);
	Collider->SetColType(ECollisionType::Rect);
	Collider->SetTransform({ {0,-250},{100,500} });
}

void ACameraModeSwitch::Tick(float _DeltaTime)
{
}
