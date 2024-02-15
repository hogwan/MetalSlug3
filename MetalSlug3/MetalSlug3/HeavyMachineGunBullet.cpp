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
		Renderer->SetImage("HeavyMachineGunBullet_Down_2.png");
		Renderer->ChangeAnimation("Down2");
	}
	else if (Dir.Y > 0.98f)
	{
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_Down_1.png");
			Renderer->ChangeAnimation("Down1");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_Down_3.png");
			Renderer->ChangeAnimation("Down3");
		}
	}
	else if (Dir.Y > 0.97f)
	{
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_Down_0.png");
			Renderer->ChangeAnimation("Down0");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_Down_4.png");
			Renderer->ChangeAnimation("Down4");
		}
	}
	else if (Dir.Y > 0.8f)
	{
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToDown2_left.png");
			Renderer->ChangeAnimation("NormalToDown2_Left");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToDown2_Right.png");
			Renderer->ChangeAnimation("NormalToDown2_Right");
		}
	}
	else if (Dir.Y > 0.55f)
	{
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToDown1_left.png");
			Renderer->ChangeAnimation("NormalToDown1_Left");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToDown1_Right.png");
			Renderer->ChangeAnimation("NormalToDown1_Right");
		}
	}
	else if (Dir.Y > 0.233f)
	{
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_Left_4.png");
			Renderer->ChangeAnimation("Left4");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_Right_4.png");
			Renderer->ChangeAnimation("Right4");
		}
	}
	else if (Dir.Y > 0.135f)
	{
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_Left_3.png");
			Renderer->ChangeAnimation("Left3");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_Right_3.png");
			Renderer->ChangeAnimation("Right3");
		}
	}
	else if (Dir.Y > -0.0001f)
	{
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_Left_2.png");
			Renderer->ChangeAnimation("Left2");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_Right_2.png");
			Renderer->ChangeAnimation("Right2");
		}
	}
	else if(Dir.Y > -0.14f)
	{
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_Left_1.png");
			Renderer->ChangeAnimation("Left1");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_Right_1.png");
			Renderer->ChangeAnimation("Right1");
		}
	}
	else if (Dir.Y > -0.25f)
	{
		
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_Left_0.png");
			Renderer->ChangeAnimation("Left0");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_Right_0.png");
			Renderer->ChangeAnimation("Right0");
		}
	}
	else if (Dir.Y > -0.6f)
	{
		
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToUp1_Left.png");
			Renderer->ChangeAnimation("NormalToUp1_Left");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToUp1_Right.png");
			Renderer->ChangeAnimation("NormalToUp1_Right");
		}
		
	}
	else if (Dir.Y > -0.85f)
	{
		
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToUp2_Left.png");
			Renderer->ChangeAnimation("NormalToUp2_Left");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_NormalToUp2_Right.png");
			Renderer->ChangeAnimation("NormalToUp2_Right");
		}
	}
	else if (Dir.Y > -0.98f)
	{
		
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_Up_0.png");
			Renderer->ChangeAnimation("Up0");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_Up_4.png");
			Renderer->ChangeAnimation("Up4");
		}
	}
	else if (Dir.Y > -0.9999f)
	{
		
		if (Dir.X < 0.0f)
		{
			Renderer->SetImage("HeavyMachineGunBullet_Up_1.png");
			Renderer->ChangeAnimation("Up1");
		}
		else
		{
			Renderer->SetImage("HeavyMachineGunBullet_Up_3.png");
			Renderer->ChangeAnimation("Up3");
		}
	}
	else
	{
		
		Renderer->SetImage("HeavyMachineGunBullet_Up_2.png");
		Renderer->ChangeAnimation("Up2");
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
