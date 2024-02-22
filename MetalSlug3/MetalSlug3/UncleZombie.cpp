#include "UncleZombie.h"

AUncleZombie::AUncleZombie()
{
}

AUncleZombie::~AUncleZombie()
{
}

void AUncleZombie::BeginPlay()
{
	AZombies::BeginPlay();

	LaunchFrame = 9;
	LaunchEffectFrame = 1;
	LaunchEffectOffset_Up = { 0,0 };
	LaunchEffectoffset_Left = { -20,0 };
	LaunchEffectOffset_Right = { 65,0 };
	LaunchEffectScale = { 500,500 };

	ProjectileSpawnOffset_Height = { 0,-50 };
	ProjectileSpawnOffset_Left = { -50,0 };
	ProjectileSpawnOffset_Right = { 50,0 };

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("UncleZombie.png");
	Renderer->SetTransform({ {0,0}, {600,600} });

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 50,100 });
	Collider->SetPosition({ 0,-50 });

	LaunchRenderer = CreateImageRenderer(MT3RenderOrder::Particle);
	LaunchRenderer->SetImage("UncleZombie_LaunchEffect.png");
	LaunchRenderer->SetTransform({ LaunchEffectOffset_Up + LaunchEffectoffset_Left, {600,600} });

	Renderer->CreateAnimation("Idle_Right", "UncleZombie.png", 0, 10, 0.2f, true);
	Renderer->CreateAnimation("Move_Right", "UncleZombie.png", 11, 24, 0.1f, true);
	Renderer->CreateAnimation("Attack_Right", "UncleZombie.png", 25, 36, 0.1f, false);
	Renderer->CreateAnimation("Stun_Right", "UncleZombie.png", 37, 61, 0.1f, false);
	Renderer->CreateAnimation("Turn_Right", "UncleZombie.png", 62, 70, 0.1f, false);
	Renderer->CreateAnimation("Death_Right", "ManZombie1.png", 77, 91, 0.05f, false);
	Renderer->CreateAnimation("DeathInFlame_Right", "UncleZombie.png", 71, 97, 0.08f, false);


	Renderer->CreateAnimation("Idle_Left", "UncleZombie.png", 100, 110, 0.2f, true);
	Renderer->CreateAnimation("Move_Left", "UncleZombie.png", 111, 124, 0.1f, true);
	Renderer->CreateAnimation("Attack_Left", "UncleZombie.png", 125, 136, 0.1f, false);
	Renderer->CreateAnimation("Stun_Left", "UncleZombie.png", 137, 161, 0.1f, false);
	Renderer->CreateAnimation("Turn_Left", "UncleZombie.png", 162, 170, 0.1f, false);
	Renderer->CreateAnimation("Death_Left", "ManZombie1.png", 197, 211, 0.05f, false);
	Renderer->CreateAnimation("DeathInFlame_Left", "UncleZombie.png", 171, 197, 0.08f, false);


	Renderer->CreateAnimation("Lying", "UncleZombie.png", 149, 161, 0.08f, false);

	LaunchRenderer->CreateAnimation("LaunchEffect_Right", "UncleZombie_LaunchEffect.png", 0, 12, 0.1f, false);
	LaunchRenderer->CreateAnimation("LaunchEffect_Left", "UncleZombie_LaunchEffect.png", 13, 25, 0.1f, false);
	LaunchRenderer->ActiveOff();
	LaunchRenderer->ChangeAnimation("LaunchEffect_Left", true, 0, 0.1f);
}

void AUncleZombie::Tick(float _DeltaTime)
{
	AZombies::Tick(_DeltaTime);
	GravityCheck(_DeltaTime);
	GroundUp();
	StateUpdate(_DeltaTime);
}
