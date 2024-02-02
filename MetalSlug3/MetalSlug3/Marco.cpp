#include "Marco.h"
#include <EngineCore\EngineCore.h>
#include <EngineBase/EngineTime.h>
#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"
#include "Bomb.h"
#include "MarcoStatus.h"
#include "CreateMarcoAnimation.h"


Marco::Marco()
{
}

Marco::~Marco()
{
}

void Marco::BeginPlay()
{
	//¹è°æ»ö 153,217,234

	UpperBodyRenderer = CreateImageRenderer(5);
	UpperBodyRenderer->SetImage("Marco_face-Resource.png");
	UpperBodyRenderer->SetTransform({ {0,0}, {100, 100} });
	UpperBodyRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });
	UpperBodyRenderer->SetTransColor({ 153, 217, 234, 0 });

	LowerBodyRenderer = CreateImageRenderer(4);
	LowerBodyRenderer->SetImage("Marco_face-Resource.png");
	LowerBodyRenderer->SetTransform({ {0,8}, {100, 100} });
	LowerBodyRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });
	LowerBodyRenderer->SetTransColor({ 153, 217, 234, 0 });

	AllBodyRenderer = CreateImageRenderer(6);
	AllBodyRenderer->SetImage("Marco_face-Resource.png");
	AllBodyRenderer->SetTransform({ {0,0}, {100, 100} });
	AllBodyRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });
	AllBodyRenderer->SetTransColor({ 153, 217, 234, 0 });

	ZombieLaunchEffectRenderer = CreateImageRenderer(2);
	ZombieLaunchEffectRenderer->SetImage("Marco_face-Resource.png");
	ZombieLaunchEffectRenderer->SetTransform({ {150,0}, {100, 100} });
	ZombieLaunchEffectRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });
	ZombieLaunchEffectRenderer->SetTransColor({ 153, 217, 234, 0 });

	ZombieProjectileRenderer = CreateImageRenderer(3);
	ZombieProjectileRenderer->SetImage("Marco_face-Resource.png");
	ZombieProjectileRenderer->SetTransform({ {150,150}, {100, 100} });
	ZombieProjectileRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });
	ZombieProjectileRenderer->SetTransColor({ 153, 217, 234, 0 });

	CreateMarcoAnimation;

	UpperBodyRenderer->ChangeAnimation("Pistol_Idle_Right");
	LowerBodyRenderer->ChangeAnimation("LowerBody_Idle_Right");

	AllBodyRenderer->ChangeAnimation("Zombie_AllBody_Vomit_Right");
	ZombieLaunchEffectRenderer->ChangeAnimation("Zombie_AllBody_Vomit_LaunchEffect_Right");
	ZombieProjectileRenderer->ChangeAnimation("Zombie_AllBody_Vomit_ProjectileEffect_Right");

	AllBodyRenderer->ActiveOff();
	ZombieLaunchEffectRenderer->ActiveOff();
	ZombieProjectileRenderer->ActiveOff();

	SetActorLocation({ 400, 300 });
}

void Marco::Tick(float _DeltaTime)
{
	if (true == EngineInput::IsDown(VK_LEFT))
	{
		LeftKeyDownLogic(_DeltaTime);
	}
	if (true == EngineInput::IsPress(VK_LEFT))
	{	
		LeftKeyPressLogic(_DeltaTime);
		RenderState |= MOVE;
		Dir = FVector::Left;
	}
	if (true == EngineInput::IsUp(VK_LEFT))
	{
		LeftKeyUpLogic(_DeltaTime);
		RenderState &= ~MOVE;
	}


	if (true == EngineInput::IsDown(VK_RIGHT))
	{
		RightKeyDownLogic(_DeltaTime);
	}
	if (true == EngineInput::IsPress(VK_RIGHT))
	{
		RightKeyPressLogic(_DeltaTime);
		RenderState |= MOVE;
		Dir = FVector::Right;
	}
	if (true == EngineInput::IsUp(VK_RIGHT))
	{
		RightKeyUpLogic(_DeltaTime);
		RenderState &= ~MOVE;
	}

	if (true == EngineInput::IsDown(VK_UP))
	{
		UpKeyDownLogic(_DeltaTime);
	}
	if (true == EngineInput::IsPress(VK_UP))
	{
		UpKeyPressLogic(_DeltaTime);
		RenderState |= AIMUP;
	}
	if (true == EngineInput::IsUp(VK_UP))
	{
		UpKeyUpLogic(_DeltaTime);
		RenderState &= ~AIMUP;
	}

	if (true == EngineInput::IsDown(VK_DOWN))
	{
		DownKeyDownLogic(_DeltaTime);
	}
	if (true == EngineInput::IsPress(VK_DOWN))
	{
		DownKeyPressLogic(_DeltaTime);
		if (InAir)
		{
			RenderState |= AIMDOWN;
		}
		else
		{
			RenderState |= CROUCH;
		}
	}
	if (true == EngineInput::IsUp(VK_DOWN))
	{
		DownKeyUpLogic(_DeltaTime);
		RenderState &= ~AIMDOWN;
		RenderState &= ~CROUCH;
	}


	if (true == EngineInput::IsDown('A'))
	{
		Shoot();
	}

	if (true == EngineInput::IsDown('S'))
	{
		Jump();
	}

	if (true == EngineInput::IsDown('D'))
	{
		Throw();
	}

	if (RenderState & CROUCH || IsZombie)
	{
		AllBodyRenderer->ActiveOn();
		ZombieLaunchEffectRenderer->ActiveOn();
		ZombieProjectileRenderer->ActiveOn();

		UpperBodyRenderer->ActiveOff();
		LowerBodyRenderer->ActiveOff();
	}
	else
	{
		AllBodyRenderer->ActiveOff();
		ZombieLaunchEffectRenderer->ActiveOff();
		ZombieProjectileRenderer->ActiveOff();

		UpperBodyRenderer->ActiveOn();
		LowerBodyRenderer->ActiveOn();
	}

	PrevRenderState = RenderState;
	RenderState = 0;
}

void Marco::Shoot()
{
}

void Marco::Jump()
{
}

void Marco::Throw()
{
}

void Marco::LeftKeyDownLogic(float _DeltaTime)
{
	if (!InAir)
	{
		if (PrevRenderState & CROUCH)
		{
			if (IsRifle)
			{
				AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Move_Left");
			}
			else
			{
				AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Move_Left");
			}
		}
		else
		{
			if (IsRifle)
			{
				UpperBodyRenderer->ChangeAnimation("Rifle_Run_Left");
			}
			else
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Run_Left");
			}
		}
	}
}

void Marco::LeftKeyPressLogic(float _DeltaTime)
{
	if (InAir)
	{
		AddActorLocation(Dir * InAir_Speed * _DeltaTime);
	}
	else
	{
		if (PrevRenderState & CROUCH)
		{
			AddActorLocation(Dir * Crouch_Speed * _DeltaTime);
		}
		else
		{
			AddActorLocation(Dir * Speed * _DeltaTime);
		}
	}
}

void Marco::LeftKeyUpLogic(float _DeltaTime)
{
	if (IsRifle)
	{
		if (PrevRenderState & CROUCH)
		{
			if (Dir == FVector::Left)
			{
				AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Idle_Left");
			}
			else if(Dir == FVector::Right)
			{
				AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Idle_Right");
			}
		}
		else
		{
			if (Dir == FVector::Left)
			{
				UpperBodyRenderer->ChangeAnimation("Rifle_Idle_Left");
			}
			else if (Dir == FVector::Right)
			{
				UpperBodyRenderer->ChangeAnimation("Rifle_Idle_Right");
			}
		}
	}
	else
	{
		if (PrevRenderState & CROUCH)
		{
			if (Dir == FVector::Left)
			{
				AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Idle_Left");
			}
			else if (Dir == FVector::Right)
			{
				AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Idle_Right");
			}
		}
		else
		{
			if (Dir == FVector::Left)
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Idle_Left");
			}
			else if (Dir == FVector::Right)
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Idle_Right");
			}
		}
	}
}

void Marco::RightKeyDownLogic(float _DeltaTime)
{
}

void Marco::RightKeyPressLogic(float _DeltaTime)
{
}

void Marco::RightKeyUpLogic(float _DeltaTime)
{
}

void Marco::UpKeyDownLogic(float _DeltaTime)
{
}

void Marco::UpKeyPressLogic(float _DeltaTime)
{
}

void Marco::UpKeyUpLogic(float _DeltaTime)
{
}

void Marco::DownKeyDownLogic(float _DeltaTime)
{
	if (InAir)
	{

	}
	else
	{
		
	}
}

void Marco::DownKeyPressLogic(float _DeltaTime)
{
}

void Marco::DownKeyUpLogic(float _DeltaTime)
{
}
