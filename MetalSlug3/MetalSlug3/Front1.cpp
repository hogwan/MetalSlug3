#include "Front1.h"

AFront1::AFront1()
{
}

AFront1::~AFront1()
{
}

void AFront1::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Front);
	Renderer->SetImage("Front1.png");
	Renderer->SetTransform({ {0,0},{609,329} });
	
}

void AFront1::Tick(float _DeltaTime)
{

}
