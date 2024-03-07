#include "ZombieVomitProjectile.h"
#include "ContentsHelper.h"

AZombieVomitProjectile::AZombieVomitProjectile()
{
}

AZombieVomitProjectile::~AZombieVomitProjectile()
{
}

void AZombieVomitProjectile::BeginPlay()
{
	AActor::BeginPlay();

	Collider = CreateCollision(MT3CollisionOrder::PlayerBullet);
	Collider->SetScale({ 50,20 });

	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->CreateAnimation("0-0_Right", "Marco_ZombieVomitProjectile.png", 0, 0, 0.05f);
	Renderer->CreateAnimation("0-1_Right", "Marco_ZombieVomitProjectile.png", 1, 1, 0.05f);
	Renderer->CreateAnimation("1-0_Right", "Marco_ZombieVomitProjectile.png", 2, 2, 0.05f);
	Renderer->CreateAnimation("1-1_Right", "Marco_ZombieVomitProjectile.png", 3, 3, 0.05f);
	Renderer->CreateAnimation("2-0_Right", "Marco_ZombieVomitProjectile.png", 4, 4, 0.05f);
	Renderer->CreateAnimation("2-1_Right", "Marco_ZombieVomitProjectile.png", 5, 5, 0.05f);
	Renderer->CreateAnimation("3-0_Right", "Marco_ZombieVomitProjectile.png", 6, 6, 0.05f);
	Renderer->CreateAnimation("3-1_Right", "Marco_ZombieVomitProjectile.png", 7, 7, 0.05f);
	Renderer->CreateAnimation("4-0_Right", "Marco_ZombieVomitProjectile.png", 8, 8, 0.05f);
	Renderer->CreateAnimation("4-1_Right", "Marco_ZombieVomitProjectile.png", 9, 9, 0.05f);
	Renderer->CreateAnimation("5-0_Right", "Marco_ZombieVomitProjectile.png", 10, 10, 0.05f);
	Renderer->CreateAnimation("5-1_Right", "Marco_ZombieVomitProjectile.png", 11, 11, 0.05f);
	Renderer->CreateAnimation("6-0_Right", "Marco_ZombieVomitProjectile.png", 12, 12, 0.05f);
	Renderer->CreateAnimation("6-1_Right", "Marco_ZombieVomitProjectile.png", 13, 13, 0.05f);
	Renderer->CreateAnimation("7-0_Right", "Marco_ZombieVomitProjectile.png", 14, 14, 0.05f);
	Renderer->CreateAnimation("7-1_Right", "Marco_ZombieVomitProjectile.png", 15, 15, 0.05f);
	Renderer->CreateAnimation("8-0_Right", "Marco_ZombieVomitProjectile.png", 16, 16, 0.05f);
	Renderer->CreateAnimation("8-1_Right", "Marco_ZombieVomitProjectile.png", 17, 17, 0.05f);
	Renderer->CreateAnimation("9-0_Right", "Marco_ZombieVomitProjectile.png", 18, 18, 0.05f);
	Renderer->CreateAnimation("9-1_Right", "Marco_ZombieVomitProjectile.png", 19, 19, 0.05f);
	Renderer->CreateAnimation("10-0_Right", "Marco_ZombieVomitProjectile.png", 20, 20, 0.05f);
	Renderer->CreateAnimation("10-1_Right", "Marco_ZombieVomitProjectile.png", 21, 21, 0.05f);
	Renderer->CreateAnimation("11-0_Right", "Marco_ZombieVomitProjectile.png", 22, 22, 0.05f);
	Renderer->CreateAnimation("11-1_Right", "Marco_ZombieVomitProjectile.png", 23, 23, 0.05f);
	Renderer->CreateAnimation("12-0_Right", "Marco_ZombieVomitProjectile.png", 24, 24, 0.05f);
	Renderer->CreateAnimation("12-1_Right", "Marco_ZombieVomitProjectile.png", 25, 25, 0.05f);
	Renderer->CreateAnimation("13-0_Right", "Marco_ZombieVomitProjectile.png", 26, 26, 0.05f);
	Renderer->CreateAnimation("13-1_Right", "Marco_ZombieVomitProjectile.png", 27, 27, 0.05f);
	Renderer->CreateAnimation("14-0_Right", "Marco_ZombieVomitProjectile.png", 28, 28, 0.05f);
	Renderer->CreateAnimation("14-1_Right", "Marco_ZombieVomitProjectile.png", 29, 29, 0.05f);
	Renderer->CreateAnimation("15-0_Right", "Marco_ZombieVomitProjectile.png", 30, 30, 0.05f);
	Renderer->CreateAnimation("15-1_Right", "Marco_ZombieVomitProjectile.png", 31, 31, 0.05f);
	Renderer->CreateAnimation("16-0_Right", "Marco_ZombieVomitProjectile.png", 32, 32, 0.05f);
	Renderer->CreateAnimation("16-1_Right", "Marco_ZombieVomitProjectile.png", 33, 33, 0.05f);
	Renderer->CreateAnimation("17-0_Right", "Marco_ZombieVomitProjectile.png", 34, 34, 0.05f);
	Renderer->CreateAnimation("17-1_Right", "Marco_ZombieVomitProjectile.png", 35, 35, 0.05f);
	Renderer->CreateAnimation("End_Right", "Marco_ZombieVomitProjectile.png", 36, 51, 0.05f);

	Renderer->CreateAnimation("0-0_Left", "Marco_ZombieVomitProjectile.png", 60, 60, 0.05f);
	Renderer->CreateAnimation("0-1_Left", "Marco_ZombieVomitProjectile.png", 61, 61, 0.05f);
	Renderer->CreateAnimation("1-0_Left", "Marco_ZombieVomitProjectile.png", 62, 62, 0.05f);
	Renderer->CreateAnimation("1-1_Left", "Marco_ZombieVomitProjectile.png", 63, 63, 0.05f);
	Renderer->CreateAnimation("2-0_Left", "Marco_ZombieVomitProjectile.png", 64, 64, 0.05f);
	Renderer->CreateAnimation("2-1_Left", "Marco_ZombieVomitProjectile.png", 65, 65, 0.05f);
	Renderer->CreateAnimation("3-0_Left", "Marco_ZombieVomitProjectile.png", 66, 66, 0.05f);
	Renderer->CreateAnimation("3-1_Left", "Marco_ZombieVomitProjectile.png", 67, 67, 0.05f);
	Renderer->CreateAnimation("4-0_Left", "Marco_ZombieVomitProjectile.png", 68, 68, 0.05f);
	Renderer->CreateAnimation("4-1_Left", "Marco_ZombieVomitProjectile.png", 69, 69, 0.05f);
	Renderer->CreateAnimation("5-0_Left", "Marco_ZombieVomitProjectile.png", 70, 70, 0.05f);
	Renderer->CreateAnimation("5-1_Left", "Marco_ZombieVomitProjectile.png", 71, 71, 0.05f);
	Renderer->CreateAnimation("6-0_Left", "Marco_ZombieVomitProjectile.png", 72, 72, 0.05f);
	Renderer->CreateAnimation("6-1_Left", "Marco_ZombieVomitProjectile.png", 73, 73, 0.05f);
	Renderer->CreateAnimation("7-0_Left", "Marco_ZombieVomitProjectile.png", 74, 74, 0.05f);
	Renderer->CreateAnimation("7-1_Left", "Marco_ZombieVomitProjectile.png", 75, 75, 0.05f);
	Renderer->CreateAnimation("8-0_Left", "Marco_ZombieVomitProjectile.png", 76, 76, 0.05f);
	Renderer->CreateAnimation("8-1_Left", "Marco_ZombieVomitProjectile.png", 77, 77, 0.05f);
	Renderer->CreateAnimation("9-0_Left", "Marco_ZombieVomitProjectile.png", 78, 78, 0.05f);
	Renderer->CreateAnimation("9-1_Left", "Marco_ZombieVomitProjectile.png", 79, 79, 0.05f);
	Renderer->CreateAnimation("10-0_Left", "Marco_ZombieVomitProjectile.png", 80, 80, 0.05f);
	Renderer->CreateAnimation("10-1_Left", "Marco_ZombieVomitProjectile.png", 81, 81, 0.05f);
	Renderer->CreateAnimation("11-0_Left", "Marco_ZombieVomitProjectile.png", 82, 82, 0.05f);
	Renderer->CreateAnimation("11-1_Left", "Marco_ZombieVomitProjectile.png", 83, 83, 0.05f);
	Renderer->CreateAnimation("12-0_Left", "Marco_ZombieVomitProjectile.png", 84, 84, 0.05f);
	Renderer->CreateAnimation("12-1_Left", "Marco_ZombieVomitProjectile.png", 85, 85, 0.05f);
	Renderer->CreateAnimation("13-0_Left", "Marco_ZombieVomitProjectile.png", 86, 86, 0.05f);
	Renderer->CreateAnimation("13-1_Left", "Marco_ZombieVomitProjectile.png", 87, 87, 0.05f);
	Renderer->CreateAnimation("14-0_Left", "Marco_ZombieVomitProjectile.png", 88, 88, 0.05f);
	Renderer->CreateAnimation("14-1_Left", "Marco_ZombieVomitProjectile.png", 89, 89, 0.05f);
	Renderer->CreateAnimation("15-0_Left", "Marco_ZombieVomitProjectile.png", 90, 90, 0.05f);
	Renderer->CreateAnimation("15-1_Left", "Marco_ZombieVomitProjectile.png", 91, 91, 0.05f);
	Renderer->CreateAnimation("16-0_Left", "Marco_ZombieVomitProjectile.png", 92, 92, 0.05f);
	Renderer->CreateAnimation("16-1_Left", "Marco_ZombieVomitProjectile.png", 93, 93, 0.05f);
	Renderer->CreateAnimation("17-0_Left", "Marco_ZombieVomitProjectile.png", 94, 94, 0.05f);
	Renderer->CreateAnimation("17-1_Left", "Marco_ZombieVomitProjectile.png", 95, 95, 0.05f);
	Renderer->CreateAnimation("End_Left", "Marco_ZombieVomitProjectile.png", 96, 111, 0.05f);



	Renderer->SetImage("Marco_ZombieVomitProjectile.png");
	Renderer->SetTransform({ { 0,0 }, { 600,600 } });
	Renderer->ChangeAnimation("0-0_Right");
}

void AZombieVomitProjectile::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (RendererEnd)
	{
		if (Dir.X > 0)
		{
			Renderer->ChangeAnimation("End_Right");
		}
		else
		{
			Renderer->ChangeAnimation("End_Left");
		}
		RendererEnd = false;
	}

	if (Dir.Y < -0.97f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2) 
			{
				Renderer->ChangeAnimation("17-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("17-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("17-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("17-0_Left");
			}
		}
	}
	else if (Dir.Y < -0.91f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("16-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("16-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("16-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("16-0_Left");
			}
		}
	}
	else if (Dir.Y < -0.77f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("15-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("15-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("15-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("15-0_Left");
			}
		}
	}
	else if (Dir.Y < -0.73f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("14-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("14-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("14-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("14-0_Left");
			}
		}
	}
	else if (Dir.Y < -0.66f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("13-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("13-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("13-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("13-0_Left");
			}
		}
	}
	else if (Dir.Y < -0.63f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("12-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("12-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("12-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("12-0_Left");
			}
		}
	}
	else if (Dir.Y < -0.56f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("11-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("11-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("11-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("11-0_Left");
			}
		}
	}
	else if (Dir.Y < -0.42f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("10-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("10-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("10-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("10-0_Left");
			}
		}
	}
	else if (Dir.Y < -0.37f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("9-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("9-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("9-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("9-0_Left");
			}
		}
	}
	else if (Dir.Y < -0.34f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("8-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("8-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("8-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("8-0_Left");
			}
		}
	}
	else if (Dir.Y < -0.19f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("7-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("7-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("7-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("7-0_Left");
			}
		}
	}
	else if (Dir.Y < 0.001f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("6-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("6-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("6-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("6-0_Left");
			}
		}
	}
	else if (Dir.Y < 0.17f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("5-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("5-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("5-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("5-0_Left");
			}
		}
	}
	else if (Dir.Y < 0.24f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("4-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("4-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("4-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("4-0_Left");
			}
		}
	}
	else if (Dir.Y < 0.33f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("3-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("3-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("3-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("3-0_Left");
			}
		}
	}
	else if (Dir.Y < 0.39f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("2-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("2-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("2-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("2-0_Left");
			}
		}
	}
	else if (Dir.Y < 0.51f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("1-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("1-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("1-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("1-0_Left");
			}
		}
	}
	else if (Dir.Y < 1.0f)
	{
		if (Dir.X > 0)
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("0-1_Right");
			}
			else
			{
				Renderer->ChangeAnimation("0-0_Right");
			}
		}
		else
		{
			if (Number % 2)
			{
				Renderer->ChangeAnimation("0-1_Left");
			}
			else
			{
				Renderer->ChangeAnimation("0-0_Left");
			}
		}
	}
}

void AZombieVomitProjectile::DamageLogic()
{
}