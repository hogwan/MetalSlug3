#include "HugeBombExplosionEffect.h"
#include "ContentsHelper.h"

AHugeBombExplosionEffect::AHugeBombExplosionEffect()
{
}

AHugeBombExplosionEffect::~AHugeBombExplosionEffect()
{
}

void AHugeBombExplosionEffect::BeginPlay()
{
	AMT3Object::BeginPlay();

	Size = { 700,700 };

	Renderer = CreateImageRenderer(MT3RenderOrder::Particle);
	Renderer->SetImage("HugeBombExplosion.png");
	Renderer->SetTransform({ {0,0},Size });
	Renderer->CreateAnimation("Explosion", "HugeBombExplosion.png", 0, 29, 0.03f,false);
	Renderer->ChangeAnimation("Explosion", false, 0, 0.03f);
}

void AHugeBombExplosionEffect::Tick(float _DeltaTime)
{
	AExplosionEffect::Tick(_DeltaTime);
}
