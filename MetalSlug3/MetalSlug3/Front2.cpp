#include "Front2.h"

Front2::Front2()
{
}

Front2::~Front2()
{
}

void Front2::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Front);
	Renderer->SetImage("Front2.png");
	Renderer->SetTransform({ {0,0},{811,329} });
}

void Front2::Tick(float _DeltaTime)
{
}
