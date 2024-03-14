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

	MoveSpeed = 50.f;
	Hp = 6;
	Range = 100.f;

	LaunchFrame = 21;
	LaunchEffectFrame = 8;
	LaunchEffectOffset_Up = { 0,0 };
	LaunchEffectoffset_Left = { -10,0 };
	LaunchEffectOffset_Right = { 50,0 };
	LaunchEffectScale = { 500,500 };

	ProjectileSpawnOffset_Height = { 0,-50 };
	ProjectileSpawnOffset_Left = { -50,0 };
	ProjectileSpawnOffset_Right = { 50,0 };

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("ManZombie2.png");
	Renderer->SetTransform({ {0,0}, {600,600} });

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 50,100 });
	Collider->SetPosition({ 0,-50 });

	LaunchRenderer = CreateImageRenderer(MT3RenderOrder::Particle);
	LaunchRenderer->SetImage("ManZombie2_LaunchEffect.png");

	Renderer->CreateAnimation("Idle_Right", "ManZombie2.png", 0, 6, 0.1f, true);
	Renderer->CreateAnimation("Move_Right", "ManZombie2.png", 7, 18, 0.1f, true);
	Renderer->CreateAnimation("Attack_Right", "ManZombie2.png", 19, 43, 0.1f, false);
	Renderer->CreateAnimation("Stun_Right", "ManZombie2.png", 44, 69, 0.1f, false);
	Renderer->CreateAnimation("Turn_Right", "ManZombie2.png", 70, 78, 0.1f, false);
	Renderer->CreateAnimation("Death_Right", "ManZombie1.png", 77, 91, 0.05f, false);
	Renderer->CreateAnimation("DeathInFlame_Right", "ManZombie2.png", 79, 105, 0.08f, false);

	Renderer->CreateAnimation("Idle_Left", "ManZombie2.png", 110, 116, 0.1f, true);
	Renderer->CreateAnimation("Move_Left", "ManZombie2.png", 117, 128, 0.1f, true);
	Renderer->CreateAnimation("Attack_Left", "ManZombie2.png", 129, 153, 0.1f, false);
	Renderer->CreateAnimation("Stun_Left", "ManZombie2.png", 154, 179, 0.1f, false);
	Renderer->CreateAnimation("Turn_Left", "ManZombie2.png", 180, 188, 0.1f, false);
	Renderer->CreateAnimation("Death_Left", "ManZombie1.png", 197, 211, 0.05f, false);
	Renderer->CreateAnimation("DeathInFlame_Left", "ManZombie2.png", 189, 215, 0.08f, false);

	Renderer->CreateAnimation("Lying", "ManZombie2.png", 168, 179, 0.15f, false);

	LaunchRenderer->CreateAnimation("LaunchEffect_Left", "ManZombie2_LaunchEffect.png", 0, 19, 0.1f, false);
	LaunchRenderer->CreateAnimation("LaunchEffect_Right", "ManZombie2_LaunchEffect.png", 20, 39, 0.1f, false);
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
