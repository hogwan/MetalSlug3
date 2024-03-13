#include "ZombieThunder.h"
#include "ContentsHelper.h"
#include <EnginePlatform/EngineSound.h>

ZombieThunder::ZombieThunder()
{
}

ZombieThunder::~ZombieThunder()
{
}

void ZombieThunder::BeginPlay()
{
	AMT3Object::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Particle);
	Renderer->SetTransform({ {0,0},{1500,1500} });
	Renderer->CreateAnimation("Explosion", "ZombieThunder.png", 0, 9, 0.03f, false);
	Renderer->ChangeAnimation("Explosion", false, 0, 0.03f);

	UEngineSound::SoundPlay("Thunder.mp3");
}

void ZombieThunder::Tick(float _DeltaTime)
{
	AExplosionEffect::Tick(_DeltaTime);
}
