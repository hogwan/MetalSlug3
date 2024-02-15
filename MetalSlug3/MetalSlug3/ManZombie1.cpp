#include "Enemy.h"
#include "ManZombie1.h"
#include "Marco.h"
#include "ZombiesProjectile.h"

AManZombie1::AManZombie1()
{
}

AManZombie1::~AManZombie1()
{
}

void AManZombie1::BeginPlay()
{
	AZombies::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("ManZombie1.png");
	Renderer->SetTransform({ {0,0}, {600,600} });

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({50,100});
	Collider->SetPosition({ 0,-50 });

	LaunchRenderer = CreateImageRenderer(MT3RenderOrder::Particle);
	LaunchRenderer->SetImage("ManZombie1_LaunchEffect.png");
	LaunchRenderer->SetTransform({ LaunchEffectOffset_Up + LaunchEffectoffset_Left, {400,400} });

	Renderer->CreateAnimation("Idle_Right", "ManZombie1.png", 0, 6, 0.1f, true);
	Renderer->CreateAnimation("Move_Right", "ManZombie1.png", 7, 22, 0.1f, true);
	Renderer->CreateAnimation("Attack_Right", "ManZombie1.png", 23, 42, 0.1f, false);
	Renderer->CreateAnimation("Stun_Right", "ManZombie1.png", 43, 67, 0.1f, false);
	Renderer->CreateAnimation("Turn_Right", "ManZombie1.png", 68, 76, 0.1f, false);
	Renderer->CreateAnimation("Death_Right", "ManZombie1.png", 77, 91, 0.1f, false);
	Renderer->CreateAnimation("DeathInFlame_Right", "ManZombie1.png", 92, 118, 0.08f, false);

	Renderer->CreateAnimation("Idle_Left", "ManZombie1.png", 120, 126, 0.1f, true);
	Renderer->CreateAnimation("Move_Left", "ManZombie1.png", 127, 142, 0.1f, true);
	Renderer->CreateAnimation("Attack_Left", "ManZombie1.png", 143, 162, 0.1f, false);
	Renderer->CreateAnimation("Stun_Left", "ManZombie1.png", 163, 187, 0.1f, false);
	Renderer->CreateAnimation("Turn_Left", "ManZombie1.png", 188, 196, 0.1f, false);
	Renderer->CreateAnimation("Death_Left", "ManZombie1.png", 197, 211, 0.08f, false);
	Renderer->CreateAnimation("DeathInFlame_Left", "ManZombie1.png", 212, 238, 0.08f, false);

	Renderer->CreateAnimation("Lying", "ManZombie1.png", 175, 187, 0.08f, false);

	LaunchRenderer->CreateAnimation("LaunchEffect_Right", "ManZombie1_LaunchEffect.png", 0, 11, 0.05f, false);
	LaunchRenderer->CreateAnimation("LaunchEffect_Left", "ManZombie1_LaunchEffect.png", 20, 31, 0.05f, false);
	LaunchRenderer->ActiveOff();
	LaunchRenderer->ChangeAnimation("LaunchEffect_Left", true, 0, 0.1f);
}

void AManZombie1::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);
	GravityCheck(_DeltaTime);
	GroundUp();
	StateUpdate(_DeltaTime);
}
