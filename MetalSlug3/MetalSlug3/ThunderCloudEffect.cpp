#include "ThunderCloudEffect.h"
#include "ContentsHelper.h"

ThunderCloudEffect::ThunderCloudEffect()
{
}

ThunderCloudEffect::~ThunderCloudEffect()
{
}

void ThunderCloudEffect::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::UFO_Lazer);
	Renderer->SetTransform({ {0,0},{600,600 } });
	Renderer->CreateAnimation("Thunder", "ThunderCloudObjLaunch.png", 0, 2, 0.03f);
	Renderer->ChangeAnimation("Thunder", false, 0, 0.03f);
}

void ThunderCloudEffect::Tick(float _DeltaTime)
{
	AExplosionEffect::Tick(_DeltaTime);

	Renderer->SetTransform({ {0,0},{600,ThunderSize} });
}
