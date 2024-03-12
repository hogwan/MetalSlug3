#include "RocketLauncher_LaunchEffect.h"
#include "ContentsHelper.h"
#include "Marco.h"

RocketLauncher_LaunchEffect::RocketLauncher_LaunchEffect()
{
}

RocketLauncher_LaunchEffect::~RocketLauncher_LaunchEffect()
{
}

void RocketLauncher_LaunchEffect::BeginPlay()
{
	AActor::BeginPlay();
	
	Renderer = CreateImageRenderer(MT3RenderOrder::Particle);
	Renderer->SetTransform({ {0,0},Size });

	if (UContentsHelper::Player->DirState == EActorDir::Right)
	{
		Renderer->CreateAnimation("Effect", "RocketLauncher_LaunchEffect_Right.png", 0, 15, 0.03f,false);
		Renderer->ChangeAnimation("Effect", false, 0, 0.03f);
		Dir = FVector::Right;
	}
	else
	{
		Renderer->CreateAnimation("Effect", "RocketLauncher_LaunchEffect_Left.png", 0, 15, 0.03f,false);
		Renderer->ChangeAnimation("Effect", false, 0, 0.03f);
		Dir = FVector::Left;
	}
}

void RocketLauncher_LaunchEffect::Tick(float _DeltaTime)
{
	AExplosionEffect::Tick(_DeltaTime);

	AddActorLocation(Dir * 100.0f * _DeltaTime);
}
