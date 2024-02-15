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

	if (Dir.Y > 0.999f)
	{

	}
	else if (Dir.Y > 0.98f)
	{

	}
	else if (Dir.Y > 0.97f)
	{

	}
	else if (Dir.Y > 0.8f)
	{

	}
	else if (Dir.Y > 0.55f)
	{

	}
	else if (Dir.Y > 0.233f)
	{

	}
	else if (Dir.Y > 0.135f)
	{

	}
	else if (Dir.Y > -0.0001f)
	{

	}
	else if(Dir.Y > -0.14f)
	{

	}
	else if (Dir.Y > -0.25f)
	{

	}
	else if (Dir.Y > -0.6f)
	{

	}
	else if (Dir.Y > -0.98f)
	{

	}
	else if (Dir.Y > -0.9999f)
	{

	}
	else
	{

	}

	
}

void AHeavyMachineGunBullet::BeginPlay()
{
	ABullet::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->CreateAnimation("Right0", "HeavyMachineGunBullet_Right_0.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Right1", "HeavyMachineGunBullet_Right_1.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Right2", "HeavyMachineGunBullet_Right_2.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Right3", "HeavyMachineGunBullet_Right_3.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Right4", "HeavyMachineGunBullet_Right_4.png", 0, 0, 1.0f);

	Renderer->CreateAnimation("Left0", "HeavyMachineGunBullet_Left_0.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Left1", "HeavyMachineGunBullet_Left_1.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Left2", "HeavyMachineGunBullet_Left_2.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Left3", "HeavyMachineGunBullet_Left_3.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Left4", "HeavyMachineGunBullet_Left_4.png", 0, 0, 1.0f);

	Renderer->CreateAnimation("Up0", "HeavyMachineGunBullet_Up_0.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Up1", "HeavyMachineGunBullet_Up_1.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Up2", "HeavyMachineGunBullet_Up_2.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Up3", "HeavyMachineGunBullet_Up_3.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Up4", "HeavyMachineGunBullet_Up_4.png", 0, 0, 1.0f);

	Renderer->CreateAnimation("Down0", "HeavyMachineGunBullet_Down_0.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Down1", "HeavyMachineGunBullet_Down_1.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Down2", "HeavyMachineGunBullet_Down_2.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Down3", "HeavyMachineGunBullet_Down_3.png", 0, 0, 1.0f);
	Renderer->CreateAnimation("Down4", "HeavyMachineGunBullet_Down_4.png", 0, 0, 1.0f);

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
