#include "BossMap.h"
#include "ContentsHelper.h"

bool ABossMap::LoadComplete = false;

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
	Renderer->SetTransform({ {0,0},{858,652} });
	Renderer->CreateAnimation("Opening", "BossStartEvent.png", 0, 3, 0.6f, false);
	Renderer->ChangeAnimation("Opening", false, 0, 0.6f);

	SphereRenderer = CreateImageRenderer(MT3RenderOrder::BossMapSphere);
	SphereRenderer->SetImage("CenterSphere.png");
	SphereRenderer->SetTransform({ {-8,167},{300,300} });
}

void ABossMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (Renderer->IsCurAnimationEnd())
	{
		LoadComplete = true;
	}
}
