#include "ManZombie3Projectile.h"

AManZombie3Projectile::AManZombie3Projectile()
{
}

AManZombie3Projectile::~AManZombie3Projectile()
{
}

void AManZombie3Projectile::BeginPlay()
{
	Collider = CreateCollision(MT3CollisionOrder::ZombieProjectile);
	Collider->SetScale({ 30,30 });
	Collider->SetPosition({ 0,-30 });
	Collider->SetColType(ECollisionType::Rect);

	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->SetImage("ManZombie3_Projectile.png");
	Renderer->SetTransform({ { 0,0 }, { 500,500 } });

	Renderer->CreateAnimation("Flying_Right", "ManZombie3_Projectile.png", 0, 7, 0.08f, false);
	Renderer->CreateAnimation("CollideGround_Right", "Zombies_Projectile.png", 14, 32, 0.08f, false);
	Renderer->CreateAnimation("CollideObject_Right", "Zombies_Projectile.png", 33, 48, 0.08f, false);

	Renderer->CreateAnimation("Flying_Left", "ManZombie3_Projectile.png", 10, 17, 0.08f, false);
	Renderer->CreateAnimation("CollideGround_Left", "Zombies_Projectile.png", 64, 82, 0.08f, false);
	Renderer->CreateAnimation("CollideObject_Left", "Zombies_Projectile.png", 83, 98, 0.08f, false);

	ShootVector.Normalize2D();
	ResultVector = ShootVector * ShootPower;

	StateChange(State::None);
}

void AManZombie3Projectile::Tick(float _DeltaTime)
{
	AZombiesProjectile::Tick(_DeltaTime);
}
