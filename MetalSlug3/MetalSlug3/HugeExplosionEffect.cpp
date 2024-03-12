#include "HugeExplosionEffect.h"
#include "ContentsHelper.h"

AHugeExplosionEffect::AHugeExplosionEffect()
{
}

AHugeExplosionEffect::~AHugeExplosionEffect()
{
}

void AHugeExplosionEffect::BeginPlay()
{
	AMT3Object::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Particle);
	Renderer->SetImage("HugeExplosion.png");
	Renderer->SetTransform({ {0,0},Size });
	Renderer->CreateAnimation("Explosion", "HugeExplosion.png", 0, 27, 0.03f,false);
	Renderer->ChangeAnimation("Explosion", false, 0, 0.03f);
}

void AHugeExplosionEffect::Tick(float _DeltaTime)
{
	AExplosionEffect::Tick(_DeltaTime);
}
