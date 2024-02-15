#include "PistolBullet.h"
#include "Bullet.h"

APistolBullet::APistolBullet()
{
}

APistolBullet::~APistolBullet()
{
}

void APistolBullet::Tick(float _DeltaTime)
{
	ABullet::Tick(_DeltaTime);

	if (IsDestroy && Renderer->IsCurAnimationEnd())
	{
		int a = Renderer->GetCurAnimationFrame();
		Destroy();
	}

	std::vector<UCollision*> Result;
	if (true == Collider->CollisionCheck(MT3CollisionOrder::Enemy, Result))
	{
		Speed = 0.0f;
		IsDestroy = true;
		Collider->Destroy();
		Renderer->SetImage("BulletDestroy.png");
		Renderer->ChangeAnimation("Destroy");
		Renderer->SetTransform({ {0,0}, {30,30} });
	}

	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		Speed = 0.0f;
		IsDestroy = true;
		Destroy();
	}

	if (IsDestroy) return;


	if (Dir.Y > 0.0f)
	{
		Renderer->SetImage("PistolBullet_Up.png");
		Renderer->ChangeAnimation("Up");
	}
	else if (Dir.Y < 0.0f)
	{
		Renderer->SetImage("PistolBullet_Up.png");
		Renderer->ChangeAnimation("Down");
	}
	else
	{
		Renderer->SetImage("PistolBullet_Normal.png");
		Renderer->ChangeAnimation("Normal");
	}
}

void APistolBullet::BeginPlay()
{
	ABullet::BeginPlay();

	Collider = CreateCollision(MT3CollisionOrder::PlayerBullet);
	Collider->SetScale({ 20,20 });

	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->CreateAnimation("Destroy", "BulletDestroy.png", 0, 9, 0.05f);
	Renderer->CreateAnimation("Normal", "PistolBullet_Normal.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Down", "PistolBullet_Up.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Up", "PistolBullet_Up.png", 0, 0, 1.0f);

	Renderer->SetTransform({ {0,0}, {24,24} });
}
