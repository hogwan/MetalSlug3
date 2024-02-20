#include "Front2.h"

AFront2::AFront2()
{
}

AFront2::~AFront2()
{
}

void AFront2::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Front);
	Renderer->SetImage("Front2.png");
	Renderer->SetTransform({ {0,0},{811,329} });
}

void AFront2::Tick(float _DeltaTime)
{
}
