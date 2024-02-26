#include "ExplosionEffect.h"
#include "ContentsHelper.h"

ExplosionEffect::ExplosionEffect()
{
}

ExplosionEffect::~ExplosionEffect()
{
}

void ExplosionEffect::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Particle);
	Renderer->SetImage("NormalExplosion.png");
	Renderer->CreateAnimation("Explosion", "NormalExplosion.png", 0, 27, 0.03f);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->ChangeAnimation("Explosion",false,0,0.03f);
}

void ExplosionEffect::Tick(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}
