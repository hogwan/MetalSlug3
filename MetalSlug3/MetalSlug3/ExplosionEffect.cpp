#include "ExplosionEffect.h"
#include "ContentsHelper.h"

AExplosionEffect::AExplosionEffect()
{
}

AExplosionEffect::~AExplosionEffect()
{
}

void AExplosionEffect::BeginPlay()
{
	AMT3Object::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Particle);
	Renderer->SetImage("NormalExplosion.png");
	Renderer->SetTransform({ {0,0},Size });
	Renderer->CreateAnimation("Explosion", "NormalExplosion.png", 0, 27, 0.03f);
	Renderer->ChangeAnimation("Explosion",false,0,0.03f);
}

void AExplosionEffect::Tick(float _DeltaTime)
{
	AMT3Object::Tick(_DeltaTime);
	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}
