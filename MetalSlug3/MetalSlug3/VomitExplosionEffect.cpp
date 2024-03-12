#include "VomitExplosionEffect.h"
#include "ContentsHelper.h"

AVomitExplosionEffect::AVomitExplosionEffect()
{
}

AVomitExplosionEffect::~AVomitExplosionEffect()
{
}

void AVomitExplosionEffect::BeginPlay()
{
	AMT3Object::BeginPlay();

	Size = { 400,400 };
	Renderer = CreateImageRenderer(MT3RenderOrder::Particle);
	Renderer->SetImage("VomitExplosion.png");
	Renderer->SetTransform({ {0,0},Size });
	Renderer->CreateAnimation("Explosion", "VomitExplosion.png", 0, 27, 0.03f,false);
	Renderer->ChangeAnimation("Explosion", false, 0, 0.03f);
}

void AVomitExplosionEffect::Tick(float _DeltaTime)
{
	AExplosionEffect::Tick(_DeltaTime);
}
