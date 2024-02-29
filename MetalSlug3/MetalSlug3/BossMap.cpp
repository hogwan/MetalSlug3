#include "BossMap.h"
#include "ContentsHelper.h"

ABossMap::ABossMap()
{
}

ABossMap::~ABossMap()
{
}

void ABossMap::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::BossMap);
	Renderer->SetImage("BossStartEvent.png");
	Renderer->SetTransform({ {0,0},{808,602} });
	Renderer->CreateAnimation("Opening", "BossStartEvent.png", 0, 3, 1.0f, false);
	Renderer->ChangeAnimation("Opening", false, 0, 1.0f);
}

void ABossMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
