#include "DoctorZombie.h"
#include "Medicine.h"

ADoctorZombie::ADoctorZombie()
{
}

ADoctorZombie::~ADoctorZombie()
{
	Medicine* MC = GetWorld()->SpawnActor<Medicine>();
	MC->SetActorLocation(GetActorLocation());
}

void ADoctorZombie::BeginPlay()
{
	AZombies::BeginPlay();

	MoveSpeed = 25.f;
	Hp = 4;
	Range = 250.f;

	LaunchFrame = 16;
	LaunchEffectFrame = 16;
	LaunchEffectOffset_Up = { 0,0 };
	LaunchEffectoffset_Left = { -50,0 };
	LaunchEffectOffset_Right = { 50,0 };
	LaunchEffectScale = { 500,500 };

	ProjectileSpawnOffset_Height = { 0,-50 };
	ProjectileSpawnOffset_Left = { -50,0 };
	ProjectileSpawnOffset_Right = { 50,0 };

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("DoctorZombie.png");
	Renderer->SetTransform({ {0,0}, {600,600} });

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 50,100 });
	Collider->SetPosition({ 0,-50 });

	LaunchRenderer = CreateImageRenderer(MT3RenderOrder::Particle);
	LaunchRenderer->SetImage("DoctorZombie_LaunchEffect.png");
	LaunchRenderer->SetTransform({ LaunchEffectOffset_Up + LaunchEffectoffset_Left, {600,600} });

	Renderer->CreateAnimation("Idle_Right", "DoctorZombie.png", 0, 6, 0.2f, true);
	Renderer->CreateAnimation("Move_Right", "DoctorZombie.png", 7, 18, 0.1f, true);
	Renderer->CreateAnimation("Attack_Right", "DoctorZombie.png", 19, 46, 0.1f, false);
	Renderer->CreateAnimation("Stun_Right", "DoctorZombie.png", 47, 66, 0.1f, false);
	Renderer->CreateAnimation("Turn_Right", "DoctorZombie.png", 67, 75, 0.1f, false);
	Renderer->CreateAnimation("Death_Right", "ManZombie1.png", 77, 91, 0.05f, false);
	Renderer->CreateAnimation("DeathInFlame_Right", "DoctorZombie.png", 76, 102, 0.08f, false);


	Renderer->CreateAnimation("Idle_Left", "DoctorZombie.png", 110, 116, 0.2f, true);
	Renderer->CreateAnimation("Move_Left", "DoctorZombie.png", 117, 128, 0.1f, true);
	Renderer->CreateAnimation("Attack_Left", "DoctorZombie.png", 129, 156, 0.1f, false);
	Renderer->CreateAnimation("Stun_Left", "DoctorZombie.png", 157, 176, 0.1f, false);
	Renderer->CreateAnimation("Turn_Left", "DoctorZombie.png", 177, 185, 0.1f, false);
	Renderer->CreateAnimation("Death_Left", "ManZombie1.png", 197, 211, 0.05f, false);
	Renderer->CreateAnimation("DeathInFlame_Left", "DoctorZombie.png", 186, 212, 0.08f, false);


	Renderer->CreateAnimation("Lying", "DoctorZombie.png", 171, 181, 0.3f, false);

	LaunchRenderer->CreateAnimation("LaunchEffect_Right", "DoctorZombie_LaunchEffect.png", 0, 11, 0.08f, false);
	LaunchRenderer->CreateAnimation("LaunchEffect_Left", "DoctorZombie_LaunchEffect.png", 20, 31, 0.08f, false);
	LaunchRenderer->ActiveOff();
	LaunchRenderer->ChangeAnimation("LaunchEffect_Left", true, 0, 0.1f);
}

void ADoctorZombie::Tick(float _DeltaTime)
{
	AZombies::Tick(_DeltaTime);
	GravityCheck(_DeltaTime);
	GroundUp();
	StateUpdate(_DeltaTime);
}
