#include "DoorEffect.h"

DoorEffect::DoorEffect()
{
}

DoorEffect::~DoorEffect()
{
}

void DoorEffect::BeginPlay()
{
	Renderer = CreateImageRenderer(10);
	Renderer->SetTransform({ {0,0}, {600,600} });
	Renderer->CreateAnimation("Effect", "DoorEffect.png", 0, 5, 0.05f, false);

	Renderer->ChangeAnimation("Effect");
}

void DoorEffect::Tick(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}
