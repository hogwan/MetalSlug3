#include "WomanZombie.h"

AWomanZombie::AWomanZombie()
{
}

AWomanZombie::~AWomanZombie()
{
}

void AWomanZombie::BeginPlay()
{
	AZombies::BeginPlay();

	LaunchFrame = 13;
	LaunchEffectFrame = 11;
	LaunchEffectOffset_Up = { 0,0 };
	LaunchEffectoffset_Left = { -25,0 };
	LaunchEffectOffset_Right = { 70,0 };
	LaunchEffectScale = { 500,500 };

	ProjectileSpawnOffset_Height = { 0,-50 };
	ProjectileSpawnOffset_Left = { -50,0 };
	ProjectileSpawnOffset_Right = { 50,0 };

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("WomanZombie.png");
	Renderer->SetTransform({ {0,0}, {600,600} });

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 50,100 });
	Collider->SetPosition({ 0,-50 });

	LaunchRenderer = CreateImageRenderer(MT3RenderOrder::Particle);
	LaunchRenderer->SetImage("WomanZombie_LaunchEffect.png");
	LaunchRenderer->SetTransform({ LaunchEffectOffset_Up + LaunchEffectoffset_Left, {600,600} });

	Renderer->CreateAnimation("Idle_Right", "WomanZombie.png", 0, 11, 0.2f, true);
	Renderer->CreateAnimation("Move_Right", "WomanZombie.png", 12, 23, 0.1f, true);
	Renderer->CreateAnimation("Attack_Right", "WomanZombie.png", 24, 44, 0.1f, false);
	Renderer->CreateAnimation("Stun_Right", "WomanZombie.png", 45, 69, 0.1f, false);
	Renderer->CreateAnimation("Turn_Right", "WomanZombie.png", 70, 78, 0.1f, false);
	Renderer->CreateAnimation("Death_Right", "ManZombie1.png", 77, 91, 0.05f, false);
	Renderer->CreateAnimation("DeathInFlame_Right", "WomanZombie.png", 79, 105, 0.08f, false);


	Renderer->CreateAnimation("Idle_Left", "WomanZombie.png", 110, 121, 0.2f, true);
	Renderer->CreateAnimation("Move_Left", "WomanZombie.png", 122, 133, 0.1f, true);
	Renderer->CreateAnimation("Attack_Left", "WomanZombie.png", 134, 154, 0.1f, false);
	Renderer->CreateAnimation("Stun_Left", "WomanZombie.png", 155, 179, 0.1f, false);
	Renderer->CreateAnimation("Turn_Left", "WomanZombie.png", 180, 188, 0.1f, false);
	Renderer->CreateAnimation("Death_Left", "ManZombie1.png", 197, 211, 0.05f, false);
	Renderer->CreateAnimation("DeathInFlame_Left", "WomanZombie.png", 189, 215, 0.08f, false);


	Renderer->CreateAnimation("Lying", "WomanZombie.png", 171, 181, 0.15f, false);

	LaunchRenderer->CreateAnimation("LaunchEffect_Right", "WomanZombie_LaunchEffect.png", 0, 9, 0.1f, false);
	LaunchRenderer->CreateAnimation("LaunchEffect_Left", "WomanZombie_LaunchEffect.png", 10, 19, 0.1f, false);
	LaunchRenderer->ActiveOff();
	LaunchRenderer->ChangeAnimation("LaunchEffect_Left", true, 0, 0.1f);
}

void AWomanZombie::Tick(float _DeltaTime)
{
	AZombies::Tick(_DeltaTime);
	GravityCheck(_DeltaTime);
	GroundUp();
	StateUpdate(_DeltaTime);
}
