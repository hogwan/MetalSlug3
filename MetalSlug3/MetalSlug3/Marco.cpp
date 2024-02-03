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
	UpperBodyRenderer->SetTransform({ {0,0}, {200, 200} });
	UpperBodyRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });
	UpperBodyRenderer->SetTransColor({ 153, 217, 234, 0 });

	LowerBodyRenderer = CreateImageRenderer(4);
	LowerBodyRenderer->SetImage("Marco_face-Resource.png");
	LowerBodyRenderer->SetTransform({ {0,16}, {200, 200} });
	LowerBodyRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });
	LowerBodyRenderer->SetTransColor({ 153, 217, 234, 0 });

	AllBodyRenderer = CreateImageRenderer(6);
	AllBodyRenderer->SetImage("Marco_face-Resource.png");
	AllBodyRenderer->SetTransform({ {0,0}, {200, 200} });
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
		ZombieLaunchEffectRenderer->ActiveOff();
		ZombieProjectileRenderer->ActiveOff();

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

void Marco::LeftKeyDownLogic(float _DeltaTime)
{
	PrevMoveDir = MoveDir;
	MoveDir += FVector::Left;
	if (InAir)
	{

	}
	else
	{
		if ((PrevRenderState & CROUCH) && !(PrevRenderState & AIMUP))
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
		else if (!(PrevRenderState & CROUCH) && (PrevRenderState & AIMUP))
		{
			LowerBodyRenderer->ChangeAnimation("LowerBody_Run_Left");
			if (IsRifle)
			{
				UpperBodyRenderer->ChangeAnimation("Rifle_AimUp_Left");
				AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Move_Left");
			}
			else
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Aim_Up_Left");
				AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Move_Left");
			}
		}
		else
		{
			LowerBodyRenderer->ChangeAnimation("LowerBody_Run_Left");
			{
				if (IsRifle)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_Run_Left");
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Move_Left");
				}
				else
				{
					UpperBodyRenderer->ChangeAnimation("Pistol_Run_Left");
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Move_Left");
				}
			}
		}
	}
}

void Marco::LeftKeyPressLogic(float _DeltaTime)
{
	if (InAir)
	{
		AddActorLocation(MoveDir * InAir_Speed * _DeltaTime);
	}
	else
	{
		if (PrevRenderState & CROUCH)
		{
			AddActorLocation(MoveDir * Crouch_Speed * _DeltaTime);
		}
		else
		{
			AddActorLocation(MoveDir * Run_Speed * _DeltaTime);
		}
	}
}

void Marco::LeftKeyUpLogic(float _DeltaTime)
{
	PrevMoveDir = MoveDir;
	MoveDir -= FVector::Left;
	if (!InAir)
	{
		if ((PrevRenderState & CROUCH) && !(PrevRenderState & AIMUP))
		{
			if (false == EngineInput::IsPress(VK_RIGHT))
			{
				if (IsRifle)
				{
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Idle_Left");
				}
				else
				{
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Idle_Left");
				}
			}
			else
			{
				if (IsRifle)
				{
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Move_Right");
				}
				else
				{
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Move_Right");
				}
			}
		}
		else if (!(PrevRenderState & CROUCH) && (PrevRenderState & AIMUP))
		{
			if (false == EngineInput::IsPress(VK_RIGHT))
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Idle_Left");
				if (IsRifle)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_AimUp_Left");
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Idle_Left");
				}
				else
				{
					UpperBodyRenderer->ChangeAnimation("Pistol_Aim_Up_Left");
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Idle_Left");
				}
			}
			else
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Run_Right");
				if (IsRifle)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_AimUp_Right");
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Idle_Left");
				}
				else
				{
					UpperBodyRenderer->ChangeAnimation("Pistol_Aim_Up_Right");
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Idle_Left");
				}
			}
		}
		else
		{
			if (false == EngineInput::IsPress(VK_RIGHT))
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Idle_Left");
				if (IsRifle)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_Idle_Left");
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Idle_Left");
				}
				else
				{
					UpperBodyRenderer->ChangeAnimation("Pistol_Idle_Left");
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Idle_Left");
				}
			}
			else
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Run_Right");
				if (IsRifle)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_Run_Right");
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Move_Right");
				}
				else
				{
					UpperBodyRenderer->ChangeAnimation("Pistol_Run_Right");
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Move_Right");
				}
			}
		}
	}

}

void Marco::RightKeyDownLogic(float _DeltaTime)
{
	PrevMoveDir = MoveDir;
	MoveDir += FVector::Right;
	if (InAir)
	{

	}
	else
	{
		if ((PrevRenderState & CROUCH) && !(PrevRenderState & AIMUP))
		{
			if (IsRifle)
			{
				AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Move_Right");
			}
			else
			{
				AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Move_Right");
			}
		}
		else if (!(PrevRenderState & CROUCH) && (PrevRenderState & AIMUP))
		{
			LowerBodyRenderer->ChangeAnimation("LowerBody_Run_Right");
			if (IsRifle)
			{
				UpperBodyRenderer->ChangeAnimation("Rifle_AimUp_Right");
				AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Move_Right");
			}
			else
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Aim_Up_Right");
				AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Move_Right");
			}
		}
		else
		{
			LowerBodyRenderer->ChangeAnimation("LowerBody_Run_Right");
			{
				if (IsRifle)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_Run_Right");
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Move_Right");
				}
				else
				{
					UpperBodyRenderer->ChangeAnimation("Pistol_Run_Right");
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Move_Right");
				}
			}
		}
	}
}

void Marco::RightKeyPressLogic(float _DeltaTime)
{
	if (InAir)
	{
		AddActorLocation(MoveDir * InAir_Speed * _DeltaTime);
	}
	else
	{
		if (PrevRenderState & CROUCH)
		{
			AddActorLocation(MoveDir * Crouch_Speed * _DeltaTime);
		}
		else
		{
			AddActorLocation(MoveDir * Run_Speed * _DeltaTime);
		}
	}
}

void Marco::RightKeyUpLogic(float _DeltaTime)
{
	PrevMoveDir = MoveDir;
	MoveDir -= FVector::Right;
	if (InAir)
	{

	}
	else
	{
		if ((PrevRenderState & CROUCH) && !(PrevRenderState & AIMUP))
		{
			if (false == EngineInput::IsPress(VK_LEFT))
			{
				if (IsRifle)
				{
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Idle_Right");
				}
				else
				{
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Idle_Right");
				}
			}
			else
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
		}
		else if (!(PrevRenderState & CROUCH) && (PrevRenderState & AIMUP))
		{
			if (false == EngineInput::IsPress(VK_LEFT))
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Idle_Right");
				if (IsRifle)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_AimUp_Right");
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Idle_Right");

				}
				else
				{
					UpperBodyRenderer->ChangeAnimation("Pistol_Aim_Up_Right");
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Idle_Right");
				}
			}
			else
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Run_Left");
				if (IsRifle)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_AimUp_Left");
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Move_Left");
				}
				else
				{
					UpperBodyRenderer->ChangeAnimation("Pistol_Aim_Up_Left");
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Move_Left");
				}
			}
		}
		else
		{
			if (false == EngineInput::IsPress(VK_LEFT))
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Idle_Right");
				if (IsRifle)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_Idle_Right");
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Idle_Right");
				}
				else
				{
					UpperBodyRenderer->ChangeAnimation("Pistol_Idle_Right");
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Idle_Right");
				}
			}
			else
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Run_Left");
				if (IsRifle)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_Run_Left");
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Move_Left");
				}
				else
				{
					UpperBodyRenderer->ChangeAnimation("Pistol_Run_Left");
					AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Move_Left");
				}
			}
		}
	}
}

void Marco::UpKeyDownLogic(float _DeltaTime)
{
	if (!(PrevRenderState & CROUCH))
	{
		if (IsRifle)
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Rifle_AimUp_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Rifle_AimUp_Right");
			}
		}
		else
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Aim_Up_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Aim_Up_Right");
			}
		}
	}
}

void Marco::UpKeyPressLogic(float _DeltaTime)
{
	ShootDir = FVector::Up;
}

void Marco::UpKeyUpLogic(float _DeltaTime)
{
	if (IsRifle)
	{
		if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
		{
			UpperBodyRenderer->ChangeAnimation("Rifle_Idle_Left");
		}
		else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
		{
			UpperBodyRenderer->ChangeAnimation("Rifle_Idle_Right");
		}
	}
	else
	{
		if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
		{
			UpperBodyRenderer->ChangeAnimation("Pistol_Idle_Left");
		}
		else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
		{
			UpperBodyRenderer->ChangeAnimation("Pistol_Idle_Right");
		}
	}
}

void Marco::DownKeyDownLogic(float _DeltaTime)
{
	if (InAir)
	{
		if (IsRifle)
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Rifle_Aim_NormalToDown_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Rifle_Aim_NormalToDown_Right");
			}
		}
		else
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Aim_NormalToDown_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Aim_NormalToDown_Right");
			}
		}
	}
	else
	{
		if (IsRifle)
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Idle_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Idle_Right");
			}
		}
		else
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Idle_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Idle_Right");
			}
		}
	}
}

void Marco::DownKeyPressLogic(float _DeltaTime)
{
	if (InAir)
	{
		ShootDir = FVector::Down;
	}
}

void Marco::DownKeyUpLogic(float _DeltaTime)
{
	if (IsRifle)
	{
		if (false == EngineInput::IsPress(VK_LEFT) && false == EngineInput::IsPress(VK_RIGHT))
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Idle_Left");
				UpperBodyRenderer->ChangeAnimation("Rifle_Idle_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Idle_Right");
				UpperBodyRenderer->ChangeAnimation("Rifle_Idle_Right");
			}
		}
		else
		{
			if (true == EngineInput::IsPress(VK_LEFT))
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Run_Left");
				UpperBodyRenderer->ChangeAnimation("Rifle_Run_Left");
			}

			if (true == EngineInput::IsPress(VK_RIGHT))
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Run_Right");
				UpperBodyRenderer->ChangeAnimation("Rifle_Run_Right");
			}
		}
	}
	else
	{
		if (false == EngineInput::IsPress(VK_LEFT) && false == EngineInput::IsPress(VK_RIGHT))
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Idle_Left");
				UpperBodyRenderer->ChangeAnimation("Pistol_Idle_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Idle_Right");
				UpperBodyRenderer->ChangeAnimation("Pistol_Idle_Right");
			}
		}
		else
		{
			if (true == EngineInput::IsPress(VK_LEFT))
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Run_Left");
				UpperBodyRenderer->ChangeAnimation("Pistol_Run_Left");
			}

			if (true == EngineInput::IsPress(VK_RIGHT))
			{
				LowerBodyRenderer->ChangeAnimation("LowerBody_Run_Right");
				UpperBodyRenderer->ChangeAnimation("Pistol_Run_Right");
			}
		}
	}
}

void Marco::Shoot()
{
	if (IsRifle)
	{
		if (IsHeavyMachineGun)
		{
			if ((RenderState & CROUCH) && !(RenderState & AIMUP))
			{
				if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
				{
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Shoot_HeavyMacineGun_Left");
				}
				else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
				{
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Shoot_HeavyMacineGun_Right");
				}
			}
			else if (!(RenderState & CROUCH) && (RenderState & AIMUP))
			{
				if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_AimUpShoot_HeavyMachineGun_Left");
				}
				else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_AimUpShoot_HeavyMachineGun_Right");
				}
			}
			else
			{
				if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_Shoot_HeavyMacineGun_Left");
				}
				else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_Shoot_HeavyMacineGun_Right");
				}
			}
		}
		else
		{
			if ((RenderState & CROUCH) && !(RenderState & AIMUP))
			{
				if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
				{
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Shoot_Another_Left");
				}
				else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
				{
					AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Shoot_Another_Right");
				}
			}
			else if (!(RenderState & CROUCH) && (RenderState & AIMUP))
			{
				if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_AimUpShoot_Another_Left");
				}
				else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_AimUpShoot_Another_Right");
				}
			}
			else
			{
				if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_Shoot_Another_Left");
				}
				else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
				{
					UpperBodyRenderer->ChangeAnimation("Rifle_Shoot_Another_Right");
				}
			}
		}
	}
	else
	{
		if ((RenderState & CROUCH) && !(RenderState & AIMUP))
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Shoot_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Shoot_Right");
			}
		}
		else if (!(RenderState & CROUCH) && (RenderState & AIMUP))
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_AimUpShoot_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_AimUpShoot_Right");
			}
		}
		else
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Shoot_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Shoot_Right");
			}
		}
	}
}

void Marco::Jump()
{
}

void Marco::Throw()
{
	if (IsRifle)
	{

		if (RenderState & CROUCH)
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Throw_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				AllBodyRenderer->ChangeAnimation("Rifle_Crouch_Throw_Right");
			}
		}
		else
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Rifle_Throw_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Rifle_Throw_Right");
			}
		}
		
	}
	else
	{
		if (RenderState & CROUCH)
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Throw_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				AllBodyRenderer->ChangeAnimation("Pistol_Crouch_Throw_Right");
			}
		}
		else
		{
			if (PrevMoveDir.X < 0.0f || MoveDir.X < 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Throw_Left");
			}
			else if (PrevMoveDir.X > 0.0f || MoveDir.X > 0.0f)
			{
				UpperBodyRenderer->ChangeAnimation("Pistol_Throw_Right");
			}
		}
	}
}
