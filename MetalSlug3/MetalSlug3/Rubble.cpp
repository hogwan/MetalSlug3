#include "Rubble.h"
#include "ContentsHelper.h"

Rubble::Rubble()
{
}

Rubble::~Rubble()
{
}

void Rubble::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Particle);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->CreateAnimation("Idle", "Rubble.png", 0, 7, 0.03f, true);
	Renderer->ChangeAnimation("Idle", false, 0, 0.03f);
}

void Rubble::Tick(float _DeltaTime)
{
	Gravity.Y += GravityAccel * _DeltaTime;
	ResultVector = CurVector + Gravity;

	AddActorLocation(ResultVector * _DeltaTime);
}
