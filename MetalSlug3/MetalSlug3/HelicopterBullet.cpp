#include "HelicopterBullet.h"
#include "Marco.h"
#include "ContentsHelper.h"

AHelicopterBullet::AHelicopterBullet()
{
}

AHelicopterBullet::~AHelicopterBullet()
{
}


void AHelicopterBullet::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->SetImage("HelicopterProjectile.png");
	Renderer->CreateAnimation("Bullet", "HelicopterProjectile.png", 0, 1, 0.03f, true);
	Renderer->ChangeAnimation("Bullet");

	Collider = CreateCollision(MT3CollisionOrder::EnemyProjectile);
	Collider->SetScale({ 10,10 });
	Collider->SetColType(ECollisionType::Rect);


	ColRenderer = CreateImageRenderer(MT3RenderOrder::Particle);
	ColRenderer->SetImage("BulletDestroy.png");
	ColRenderer->CreateAnimation("Destroy", "BulletDestroy.png", 0, 9, 0.05f);
	ColRenderer->SetTransform({ {0,0}, {30,30} });
	ColRenderer->ActiveOff();
}

void AHelicopterBullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);
	if (IsDestroy && ColRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}

	std::vector<UCollision*> Result;
	if (true == Collider->CollisionCheck(MT3CollisionOrder::Player, Result))
	{
		Speed = 0.0f;
		IsDestroy = true;
		Collider->ActiveOff();
		Renderer->ActiveOff();
		ColRenderer->ActiveOn();
		ColRenderer->ChangeAnimation("Destroy");
	}
}