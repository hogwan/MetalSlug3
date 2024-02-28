#include "BombExplosionEffect.h"
#include "ContentsHelper.h"
ABombExplosionEffect::ABombExplosionEffect()
{
}

ABombExplosionEffect::~ABombExplosionEffect()
{
}

void ABombExplosionEffect::BeginPlay()
{
	AMT3Object::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Particle);
	Renderer->SetImage("BombExplosion.png");
	Renderer->SetTransform({ {0,0},Size });
	Renderer->CreateAnimation("Explosion", "BombExplosion.png", 0, 25, 0.03f);
	Renderer->ChangeAnimation("Explosion", false, 0, 0.03f);
}

void ABombExplosionEffect::Tick(float _DeltaTime)
{
	AExplosionEffect::Tick(_DeltaTime);
}
