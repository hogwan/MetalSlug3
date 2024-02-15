#include "ManZombie2.h"

AManZombie2::AManZombie2()
{
}

AManZombie2::~AManZombie2()
{
}

void AManZombie2::BeginPlay()
{
	AZombies::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("ManZombie2.png");
	Renderer->SetTransform({ {0,0}, {600,600} });

	LaunchRenderer = CreateImageRenderer(MT3RenderOrder::Particle);
	LaunchRenderer->SetImage("ManZombie2_LaunchEffect.png");
	LaunchRenderer->SetTransform({ LaunchEffectOffset_Up + LaunchEffectoffset_Left, {400,400} });

	Renderer->CreateAnimation("Idle_Right", "ManZombie2.png", 0, 6, 0.1f, true);
	Renderer->CreateAnimation("Move_Right", "ManZombie2.png", 7, 22, 0.1f, true);
	Renderer->CreateAnimation("Attack_Right", "ManZombie2.png", 23, 42, 0.1f, false);
	Renderer->CreateAnimation("Stun_Right", "ManZombie2.png", 43, 67, 0.1f, false);
	Renderer->CreateAnimation("Turn_Right", "ManZombie2.png", 68, 76, 0.1f, false);
	Renderer->CreateAnimation("Death_Right", "ManZombie2.png", 77, 91, 0.1f, false);
	Renderer->CreateAnimation("DeathInFlame_Right", "ManZombie2.png", 92, 118, 0.08f, false);

	Renderer->CreateAnimation("Idle_Left", "ManZombie2.png", 120, 126, 0.1f, true);
	Renderer->CreateAnimation("Move_Left", "ManZombie2.png", 127, 142, 0.1f, true);
	Renderer->CreateAnimation("Attack_Left", "ManZombie2.png", 143, 162, 0.1f, false);
	Renderer->CreateAnimation("Stun_Left", "ManZombie2.png", 163, 187, 0.1f, false);
	Renderer->CreateAnimation("Turn_Left", "ManZombie2.png", 188, 196, 0.1f, false);
	Renderer->CreateAnimation("Death_Left", "ManZombie2.png", 197, 211, 0.08f, false);
	Renderer->CreateAnimation("DeathInFlame_Left", "ManZombie2.png", 212, 238, 0.08f, false);

	Renderer->CreateAnimation("Lying", "ManZombie1.png", 175, 187, 0.08f, false);

	LaunchRenderer->CreateAnimation("LaunchEffect_Right", "ManZombie1_LaunchEffect.png", 0, 19, 0.05f, false);
	LaunchRenderer->CreateAnimation("LaunchEffect_Left", "ManZombie1_LaunchEffect.png", 20, 31, 0.05f, false);
	LaunchRenderer->ActiveOff();
	LaunchRenderer->ChangeAnimation("LaunchEffect_Left", true, 0, 0.1f);
}

void AManZombie2::Tick(float _DeltaTime)
{
	AZombies::Tick(_DeltaTime);
	GravityCheck(_DeltaTime);
	GroundUp();
	StateUpdate(_DeltaTime);
}
