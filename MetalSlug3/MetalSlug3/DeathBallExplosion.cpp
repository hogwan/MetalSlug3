#include "DeathBallExplosion.h"
#include "ContentsHelper.h"

ADeathBallExplosion::ADeathBallExplosion()
{
}

ADeathBallExplosion::~ADeathBallExplosion()
{
}

void ADeathBallExplosion::BeginPlay()
{
	AMT3Object::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Particle);
	Renderer->SetImage("DeathBallExplosion.png");
	Renderer->SetTransform({ {0,0},Size });
	Renderer->CreateAnimation("Explosion", "DeathBallExplosion.png", 0, 23, 0.03f);
	Renderer->ChangeAnimation("Explosion", false, 0, 0.03f);
}

void ADeathBallExplosion::Tick(float _DeltaTime)
{
	AExplosionEffect::Tick(_DeltaTime);
}
