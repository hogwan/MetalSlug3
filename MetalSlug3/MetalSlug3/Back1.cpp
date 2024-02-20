#include "Back1.h"

ABack1::ABack1()
{
}

ABack1::~ABack1()
{
}

void ABack1::BeginPlay()
{
	ABackMap::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Back);
	Renderer->SetImage("DistantBackGround1.png");
	Renderer->SetTransform({ {0,0},{4526,1659} });
}

void ABack1::Tick(float _DeltaTime)
{
	ABackMap::Tick(_DeltaTime);
}
