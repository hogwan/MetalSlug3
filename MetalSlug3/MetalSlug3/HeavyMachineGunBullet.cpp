#include "HeavyMachineGunBullet.h"

AHeavyMachineGunBullet::AHeavyMachineGunBullet()
{
}

AHeavyMachineGunBullet::~AHeavyMachineGunBullet()
{
}

void AHeavyMachineGunBullet::Tick(float _DeltaTime)
{
	ABullet::Tick(_DeltaTime);

	if (Dir.Y < -0.9f)
	{
		Renderer->SetImage("HeavyMachineGunBullet_Up.png");
		Renderer->ChangeAnimation("Up");
		return;
	}
	else if (Dir.Y < -0.8f)
	{
		if (Dir.X > 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToUp2_Right.png");
			Renderer->ChangeAnimation("NormalToUp2_Right");
			return;
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToUp2_Left.png");
			Renderer->ChangeAnimation("NormalToUp2_Left");
			return;
		}
	}
	else if (Dir.Y < -0.5f)
	{
		if (Dir.X > 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToUp1_Right.png");
			Renderer->ChangeAnimation("NormalToUp1_Right");
			return;
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToUp1_Left.png");
			Renderer->ChangeAnimation("NormalToUp1_Left");
			return;
		}
	}
	else if (Dir.Y < 0.1f)
	{
		if (Dir.X > 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_Right.png");
			Renderer->ChangeAnimation("Right");
			return;
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_Left.png");
			Renderer->ChangeAnimation("Left");
			return;
		}
	}
	else if (Dir.Y < 0.6f)
	{
		if (Dir.X > 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToDown1_Right.png");
			Renderer->ChangeAnimation("NormalToDown1_Right");
			return;
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToDown1_Left.png");
			Renderer->ChangeAnimation("NormalToDown1_Left");
			return;
		}
	}
	else if (Dir.Y < 0.85f)
	{
		if (Dir.X > 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToDown2_Right.png");
			Renderer->ChangeAnimation("NormalToDown2_Right");
			return;
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToDown2_Left.png");
			Renderer->ChangeAnimation("NormalToDown2_Left");
			return;
		}
	}
	else
	{
		Renderer->SetImage("HeavyMachineGunBullet_Down.png");
		Renderer->ChangeAnimation("Down");
	}
}

void AHeavyMachineGunBullet::BeginPlay()
{
	ABullet::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->CreateAnimation("Right", "HeavyMachineGunBullet_Right.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Left", "HeavyMachineGunBullet_Left.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Up", "HeavyMachineGunBullet_Up.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Down", "HeavyMachineGunBullet_Down.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("NormalToUp1_Right", "HeavyMachineGunBullet_NormalToUp1_Right.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("NormalToUp2_Right", "HeavyMachineGunBullet_NormalToUp2_Right.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("NormalToUp1_Left", "HeavyMachineGunBullet_NormalToUp1_Left.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("NormalToUp2_Left", "HeavyMachineGunBullet_NormalToUp2_Left.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("NormalToDown1_Right", "HeavyMachineGunBullet_NormalToDown1_Right.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("NormalToDown2_Right", "HeavyMachineGunBullet_NormalToDown2_Right.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("NormalToDown1_Left", "HeavyMachineGunBullet_NormalToDown1_Left.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("NormalToDown2_Left", "HeavyMachineGunBullet_NormalToDown2_Left.png", 0, 0, 1.0f);
	Renderer->SetTransform({ {0,0}, {80,80} });
}
