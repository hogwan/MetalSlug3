#include "BackMap.h"
#include "ContentsHelper.h"

ABackMap::ABackMap()
{
}

ABackMap::~ABackMap()
{
}

void ABackMap::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Back);
	Renderer->SetImage("DistantBackGround.png");
	Renderer->SetTransform({ {0,0}, {3987,1200} }); //{3987,812}
	Renderer->SetCameraRatio(MoveRatio);
}

void ABackMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
