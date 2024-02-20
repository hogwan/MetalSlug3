#include "Front1.h"

Front1::Front1()
{
}

Front1::~Front1()
{
}

void Front1::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Front);
	Renderer->SetImage("Front1.png");
	Renderer->SetTransform({ {0,0},{609,329} });
	
}

void Front1::Tick(float _DeltaTime)
{

}
