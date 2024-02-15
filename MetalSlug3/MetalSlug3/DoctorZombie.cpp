#include "DoctorZombie.h"

ADoctorZombie::ADoctorZombie()
{
}

ADoctorZombie::~ADoctorZombie()
{
}

void ADoctorZombie::BeginPlay()
{
	AZombies::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("DoctorZombie.png");
	Renderer->SetTransform({ {0,0}, {600,600} });

	LaunchRenderer = CreateImageRenderer(MT3RenderOrder::Particle);
	LaunchRenderer->SetImage("DoctorZombie_LaunchEffect.png");
	LaunchRenderer->SetTransform({ LaunchEffectOffset_Up + LaunchEffectoffset_Left, {400,400} });

	Renderer->CreateAnimation("Idle_Right", "DoctorZombie.png", 0, 6, 0.1f, true);
	Renderer->CreateAnimation("Move_Right", "DoctorZombie.png", 7, 18, 0.1f, true);
	Renderer->CreateAnimation("Attack_Right", "DoctorZombie.png", 19, 46, 0.1f, false);
	Renderer->CreateAnimation("Stun_Right", "DoctorZombie.png", 47, 66, 0.1f, false);
	Renderer->CreateAnimation("Turn_Right", "DoctorZombie.png", 67, 75, 0.1f, false);
	Renderer->CreateAnimation("Death_Right", "ManZombie1.png", 77, 91, 0.1f, false);
	Renderer->CreateAnimation("DeathInFlame_Right", "DoctorZombie.png", 76, 102, 0.08f, false);


	Renderer->CreateAnimation("Idle_Left", "DoctorZombie.png", 110, 116, 0.1f, true);
	Renderer->CreateAnimation("Move_Left", "DoctorZombie.png", 117, 128, 0.1f, true);
	Renderer->CreateAnimation("Attack_Left", "DoctorZombie.png", 129, 156, 0.1f, false);
	Renderer->CreateAnimation("Stun_Left", "DoctorZombie.png", 157, 176, 0.1f, false);
	Renderer->CreateAnimation("Turn_Left", "DoctorZombie.png", 177, 185, 0.1f, false);
	Renderer->CreateAnimation("Death_Left", "ManZombie1.png", 197, 211, 0.08f, false);
	Renderer->CreateAnimation("DeathInFlame_Left", "DoctorZombie.png", 186, 212, 0.08f, false);


	Renderer->CreateAnimation("Lying", "DoctorZombie.png", 175, 187, 0.08f, false);

	LaunchRenderer->CreateAnimation("LaunchEffect_Right", "DoctorZombie_LaunchEffect.png", 0, 19, 0.05f, false);
	LaunchRenderer->CreateAnimation("LaunchEffect_Left", "DoctorZombie_LaunchEffect.png", 20, 31, 0.05f, false);
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
