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

	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->CreateAnimation("Normal", "PistolBullet_Normal.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Down", "PistolBullet_Up.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Up", "PistolBullet_Up.png", 0, 0, 1.0f);

	Renderer->SetTransform({ {0,0}, {24,24} });
}
