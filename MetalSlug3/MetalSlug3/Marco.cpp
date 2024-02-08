#include "Marco.h"
#include <EngineCore\EngineCore.h>
#include <EngineBase/EngineTime.h>
#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"
#include "Bomb.h"
#include "CreateMarcoAnimation.h"
#include "ContentsHelper.h"


Marco::Marco()
{
}

Marco::~Marco()
{
}

void Marco::BeginPlay()
{
	Renderer.push_back(CreateImageRenderer(MT3RenderOrder::UpperBody));          // UpperBody
	Renderer.push_back(CreateImageRenderer(MT3RenderOrder::LowerBody));          // LowerBody
	Renderer.push_back(CreateImageRenderer(MT3RenderOrder::AllBody));          // AllBody
	Renderer.push_back(CreateImageRenderer(MT3RenderOrder::ZombieArm));          //ZombieArm
	Renderer.push_back(CreateImageRenderer(MT3RenderOrder::Projectile));      //ZombieLaunchEffect
	Renderer.push_back(CreateImageRenderer(MT3RenderOrder::Projectile));      //ZombieProjectile

	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetImage("Marco_UpperBody.png");
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransform({ {0,-24}, {200, 200} });
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetImageCuttingTransform({ {0,0}, {200, 200} });
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetImage("Marco_LowerBody.png");
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetTransform({ {0,0}, {200, 200} });
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetImageCuttingTransform({ {0,0}, {200, 200} });
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetImage("Marco_UpperBody.png");
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetTransform({ {0,0}, {200, 200} });
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetImageCuttingTransform({ {0,0}, {200, 200} });
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetImage("Marco_UpperBody.png");
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetTransform({ {150,150}, {100, 100} });
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetImageCuttingTransform({ {0,0}, {200, 200} });
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->SetImage("Marco_UpperBody.png");
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->SetTransform({ {150,0}, {100, 100} });
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->SetImageCuttingTransform({ {0,0}, {200, 200} });
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->SetImage("Marco_UpperBody.png");
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->SetTransform({ {150,150}, {100, 100} });
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->SetImageCuttingTransform({ {0,0}, {200, 200} });
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->SetTransColor({ 0,0,0,255 });

	CreateMarcoAnimation;

	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation("Pistol_UpperBody_Idle_Right");
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation("LowerBody_Idle_Right");

	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->ActiveOff();

	SetActorLocation({ 400, 300 });
	UpperStateChange(UpperBodyState::Idle);
	LowerStateChange(LowerBodyState::Idle);
	AllStateChange(AllBodyState::None);
}


void Marco::Tick(float _DeltaTime)
{
	UpperStateUpdate(_DeltaTime);
	LowerStateUpdate(_DeltaTime);
	AllBodyStateUpdate(_DeltaTime);
}

void Marco::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Gravity);
	}
}

std::string Marco::DirCheck(BodyRenderer _BodyRendererType, std::string _Name)
{
	EActorDir Dir = DirState;
	if (EngineInput::IsPress(VK_LEFT))
	{
		Dir = EActorDir::Left;
	}
	if (EngineInput::IsPress(VK_RIGHT))
	{
		Dir = EActorDir::Right;
	}

	if (Dir != DirState)
	{
		DirState = Dir;
		std::string ChangeName = AddDirectionName(_Name);
		Renderer[static_cast<int>(_BodyRendererType)]->ChangeAnimation(ChangeName);
	}
	return AddDirectionName(_Name);
}

std::string Marco::GunCheck(BodyRenderer BodyRendererType, std::string _Name)
{
	return AddGunTypeName(_Name);
}

std::string Marco::AddDirectionName(std::string _Name)
{
	std::string DirName = "";

	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
		break;
	default:
		break;
	}

	_Name += DirName;
	return _Name;
}

std::string Marco::AddGunTypeName(std::string _Name)
{
	std::string AddGunType = "";

	switch (GunType)
	{
	case EGunType::Pistol:
		AddGunType = "Pistol_";
		break;
	case EGunType::Rifle:
		AddGunType = "Rifle_";
		break;
	default:
		break;
	}

	_Name = AddGunType + _Name;
	return _Name;
}


void Marco::CameraFreeMove(float _DeltaTime)
{
	if (EngineInput::IsPress(VK_LEFT))
	{
		GetWorld()->AddCameraPos(FVector::Left * _DeltaTime * 500.0f);
		// AddActorLocation(FVector::Left * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsPress(VK_RIGHT))
	{
		GetWorld()->AddCameraPos(FVector::Right * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsPress(VK_UP))
	{
		GetWorld()->AddCameraPos(FVector::Up * _DeltaTime * 500.0f);
		// AddActorLocation(FVector::Up * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsPress(VK_DOWN))
	{
		GetWorld()->AddCameraPos(FVector::Down * _DeltaTime * 500.0f);
		// AddActorLocation(FVector::Down * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsDown('2'))
	{
		UpperStateChange(UpperBodyState::Idle);
		LowerStateChange(LowerBodyState::Idle);
		AllStateChange(AllBodyState::None);
	}
}
void Marco::FreeMove(float _DeltaTime)
{
	FVector MovePos;

	if (EngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * FreeMoveSpeed;
	}

	if (EngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * FreeMoveSpeed;
	}

	if (EngineInput::IsPress(VK_UP))
	{
		MovePos += FVector::Up * _DeltaTime * FreeMoveSpeed;
	}

	if (EngineInput::IsPress(VK_DOWN))
	{
		MovePos += FVector::Down * _DeltaTime * FreeMoveSpeed;
	}

	AddActorLocation(MovePos);
	GetWorld()->SddCameraPos({ GetActorLocation().X - 400.0f, GetActorLocation().Y - 300.0f });

	if (EngineInput::IsDown('1'))
	{
		UpperStateChange(UpperBodyState::Idle);
		LowerStateChange(LowerBodyState::Idle);
		AllStateChange(AllBodyState::None);
	}
}
void Marco::UpperStateUpdate(float _DeltaTime)
{
	switch (UpperState)
	{
	case UpperBodyState::Idle:
		UpperIdle(_DeltaTime);
		break;
	case UpperBodyState::Move:
		UpperMove(_DeltaTime);
		break;
	case UpperBodyState::Jump:
		UpperJump(_DeltaTime);
		break;
	case UpperBodyState::ForwardJump:
		UpperForwardJump(_DeltaTime);
		break;
	case UpperBodyState::Shoot:
		UpperShoot(_DeltaTime);
		break;
	case UpperBodyState::ForwardJumpShoot:
		UpperForwardJumpShoot(_DeltaTime);
		break;
	case UpperBodyState::Throw:
		UpperThrow(_DeltaTime);
		break;
	case UpperBodyState::KnifeAttack1:
		UpperKnifeAttack1(_DeltaTime);
		break;
	case UpperBodyState::KnifeAttack2:
		UpperKnifeAttack2(_DeltaTime);
		break;
	case UpperBodyState::AimNormalToUp:
		UpperAimNormalToUp(_DeltaTime);
		break;
	case UpperBodyState::AimUpToNormal:
		UpperAimUpToNormal(_DeltaTime);
		break;
	case UpperBodyState::AimUp:
		UpperAimUp(_DeltaTime);
		break;
	case UpperBodyState::AimUpShoot:
		UpperAimUpShoot(_DeltaTime);
		break;
	case UpperBodyState::AimNormalToDown:
		UpperAimNormalToDown(_DeltaTime);
		break;
	case UpperBodyState::AimDownToNormal:
		UpperAimDownToNormal(_DeltaTime);
		break;
	case UpperBodyState::AimDownShoot:
		UpperAimDownShoot(_DeltaTime);
		break;
	default:
		break;
	}
}
void Marco::LowerStateUpdate(float _DeltaTime)
{
	switch (LowerState)
	{
	case LowerBodyState::Idle:
		LowerIdle(_DeltaTime);
		break;
	case LowerBodyState::Move:
		LowerMove(_DeltaTime);
		break;
	case LowerBodyState::Jump:
		LowerJump(_DeltaTime);
		break;
	case LowerBodyState::ForwardJump:
		LowerForwardJump(_DeltaTime);
		break;
	default:
		break;
	}
}
void Marco::AllBodyStateUpdate(float _DeltaTime)
{
	switch (AllState)
	{
	case AllBodyState::Crouch_Intro:
		AllCrouch_Intro(_DeltaTime);
		break;
	case AllBodyState::Crouch_Outro:
		AllCrouch_Outro(_DeltaTime);
		break;
	case AllBodyState::Crouch_Idle:
		AllCrouch_Idle(_DeltaTime);
		break;
	case AllBodyState::Crouch_Move:
		AllCrouch_Move(_DeltaTime);
		break;
	case AllBodyState::Crouch_Shoot_HeavyMachineGun:
		AllCrouch_HeavyMachineGun_Shoot(_DeltaTime);
		break;
	case AllBodyState::Crouch_Shoot:
		AllCrouch_Shoot(_DeltaTime);
		break;
	case AllBodyState::Crouch_Throw:
		AllCrouch_Throw(_DeltaTime);
		break;
	case AllBodyState::Crouch_KnifeAttack1:
		AllCrouch_KnifeAttack1(_DeltaTime);
		break;
	case AllBodyState::Crouch_KnifeAttack2:
		AllCrouch_KnifeAttack2(_DeltaTime);
		break;
	case AllBodyState::Ceremony:
		AllCeremony(_DeltaTime);
		break;
	case AllBodyState::ElephantSlug_Idle:
		AllElephantSlug_Idle(_DeltaTime);
		break;
	case AllBodyState::ElephantSlug_Move:
		AllElephantSlug_Move(_DeltaTime);
		break;
	case AllBodyState::Death:
		AllDeath(_DeltaTime);
		break;
	case AllBodyState::DeathInAir:
		AllDeathInAir(_DeltaTime);
		break;
	case AllBodyState::DeathByKnife:
		AllDeathByKnife(_DeltaTime);
		break;
	case AllBodyState::TransformToZombie_Intro:
		Zombie_AllTransformToZombie_Intro(_DeltaTime);
		break;
	case AllBodyState::TransformToZombie_Falling:
		Zombie_AllTransformToZombie_Falling(_DeltaTime);
		break;
	case AllBodyState::TransformToZombie_Rising:
		Zombie_AllTransformToZombie_Rising(_DeltaTime);
		break;
	case AllBodyState::Zombie_Idle:
		Zombie_AllIdle(_DeltaTime);
		break;
	case AllBodyState::Zombie_Move:
		Zombie_AllMove(_DeltaTime);
		break;
	case AllBodyState::Zombie_Turn:
		Zombie_AllTurn(_DeltaTime);
		break;
	case AllBodyState::Zombie_AimupTurn:
		Zombie_AllAimupTurn(_DeltaTime);
		break;
	case AllBodyState::Zombie_Jump:
		Zombie_AllJump(_DeltaTime);
		break;
	case AllBodyState::Zombie_Vomit:
		Zombie_AllVomit(_DeltaTime);
		break;
	case AllBodyState::Zombie_Death:
		Zombie_AllDeath(_DeltaTime);
		break;
	case AllBodyState::Zombie_DeathInAir:
		Zombie_AllIdle(_DeltaTime);
		break;
	default:
		break;
	}
}
void Marco::UpperStateChange(UpperBodyState _UpperState)
{
	if (UpperState != _UpperState)
	{
		switch (_UpperState)
		{
		case UpperBodyState::Idle:
			UpperIdleStart();
			break;
		case UpperBodyState::Move:
			UpperMoveStart();
			break;
		case UpperBodyState::Jump:
			UpperJumpStart();
			break;
		case UpperBodyState::ForwardJump:
			UpperForwardJumpStart();
			break;
		case UpperBodyState::AimNormalToUp:
			UpperAimNormalToUpStart();
			break;
		case UpperBodyState::AimUpToNormal:
			UpperAimUpToNormalStart();
			break;
		case UpperBodyState::AimUp:
			UpperAimUpStart();
			break;
		case UpperBodyState::AimNormalToDown:
			UpperAimNormalToDownStart();
			break;
		case UpperBodyState::AimDownToNormal:
			UpperAimDownToNormalStart();
			break;
		default:
			break;
		}
	}

	switch (_UpperState)
	{
	case UpperBodyState::Shoot:
		UpperShootStart();
		break;
	case UpperBodyState::ForwardJumpShoot:
		UpperForwardJumpShootStart();
		break;
	case UpperBodyState::Throw:
		UpperThrowStart();
		break;
	case UpperBodyState::KnifeAttack1:
		UpperKnifeAttack1Start();
		break;
	case UpperBodyState::KnifeAttack2:
		UpperKnifeAttack2Start();
		break;
	case UpperBodyState::AimUpShoot:
		UpperAimUpShootStart();
		break;
	case UpperBodyState::AimDownShoot:
		UpperAimDownShootStart();
		break;
	default:
		break;
	}

	UpperState = _UpperState;
}
void Marco::LowerStateChange(LowerBodyState _LowerState)
{
	if (LowerState != _LowerState)
	{
		switch (_LowerState)
		{
		case LowerBodyState::Idle:
			LowerIdleStart();
			break;
		case LowerBodyState::Move:
			LowerMoveStart();
			break;
		case LowerBodyState::Jump:
			LowerJumpStart();
			break;
		case LowerBodyState::ForwardJump:
			LowerForwardJumpStart();
			break;
		default:
			break;
		}
	}

	LowerState = _LowerState;
}
void Marco::AllStateChange(AllBodyState _AllState)
{
	if (AllState != _AllState)
	{
		switch (AllState)
		{
		case AllBodyState::Crouch_Intro:
			AllCrouch_IntroStart();
			break;
		case AllBodyState::Crouch_Outro:
			AllCrouch_OutroStart();
			break;
		case AllBodyState::Crouch_Idle:
			AllCrouch_IdleStart();
			break;
		case AllBodyState::Crouch_Move:
			AllCrouch_MoveStart();
			break;
		case AllBodyState::Crouch_Shoot_HeavyMachineGun:
			AllCrouch_HeavyMachineGun_ShootStart();
			break;
		case AllBodyState::Crouch_Shoot:
			AllCrouch_ShootStart();
			break;
		case AllBodyState::Crouch_Throw:
			AllCrouch_ThrowStart();
			break;
		case AllBodyState::Crouch_KnifeAttack1:
			AllCrouch_KnifeAttack1Start();
			break;
		case AllBodyState::Crouch_KnifeAttack2:
			AllCrouch_KnifeAttack2Start();
			break;
		case AllBodyState::Ceremony:
			AllCeremonyStart();
			break;
		case AllBodyState::ElephantSlug_Idle:
			AllElephantSlug_IdleStart();
			break;
		case AllBodyState::ElephantSlug_Move:
			AllElephantSlug_MoveStart();
			break;
		case AllBodyState::Death:
			AllDeathStart();
			break;
		case AllBodyState::DeathInAir:
			AllDeathInAirStart();
			break;
		case AllBodyState::DeathByKnife:
			AllDeathByKnifeStart();
			break;
		case AllBodyState::TransformToZombie_Intro:
			Zombie_AllTransformToZombie_IntroStart();
			break;
		case AllBodyState::TransformToZombie_Falling:
			Zombie_AllTransformToZombie_FallingStart();
			break;
		case AllBodyState::TransformToZombie_Rising:
			Zombie_AllTransformToZombie_RisingStart();
			break;
		case AllBodyState::Zombie_Idle:
			Zombie_AllIdleStart();
			break;
		case AllBodyState::Zombie_Move:
			Zombie_AllMoveStart();
			break;
		case AllBodyState::Zombie_Turn:
			Zombie_AllTurnStart();
			break;
		case AllBodyState::Zombie_AimupTurn:
			Zombie_AllAimupTurnStart();
			break;
		case AllBodyState::Zombie_Jump:
			Zombie_AllJumpStart();
			break;
		case AllBodyState::Zombie_Vomit:
			Zombie_AllVomitStart();
			break;
		case AllBodyState::Zombie_Death:
			Zombie_AllDeathStart();
			break;
		case AllBodyState::Zombie_DeathInAir:
			Zombie_AllIdleStart();
			break;
		default:
			break;
		}
	}
	AllState = _AllState;
}

void Marco::UpperIdle(float _DeltaTime)
{
	std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
	DirCheck(BodyRenderer::UpperBody, GunCheckedName);
	if (InAir)
	{
		if (true == EngineInput::IsPress(VK_DOWN))
		{
			UpperStateChange(UpperBodyState::AimNormalToDown);
			return;
		}
	}
	else
	{
		if (
			true == EngineInput::IsPress(VK_LEFT) &&
			true == EngineInput::IsPress(VK_RIGHT)
			)
		{
			return;
		}

		if (
			true == EngineInput::IsPress(VK_LEFT) ||
			true == EngineInput::IsPress(VK_RIGHT)
			)
		{
			UpperStateChange(UpperBodyState::Move);
			return;
		}

		if (true == EngineInput::IsPress(VK_DOWN))
		{
			Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
			AllStateChange(AllBodyState::Crouch_Intro);
			return;
		}

		if (
			true == EngineInput::IsDown('S') ||
			true == EngineInput::IsDown('s')
			)
		{
			UpperStateChange(UpperBodyState::Jump);
			return;
		}
	}

	if (true == EngineInput::IsPress(VK_UP))
	{
		UpperStateChange(UpperBodyState::AimNormalToUp);
		return;
	}


	if (
		true == EngineInput::IsDown('A') ||
		true == EngineInput::IsDown('a')
		)
	{
		UpperStateChange(UpperBodyState::Shoot);
		return;
	}


	if (
		true == EngineInput::IsDown('D') ||
		true == EngineInput::IsDown('d')
		)
	{
		UpperStateChange(UpperBodyState::Throw);
		return;
	}

}

void Marco::UpperMove(float _DeltaTime)
{
	std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
	DirCheck(BodyRenderer::UpperBody, GunCheckedName);

	if (
		true == EngineInput::IsPress(VK_LEFT) &&
		true == EngineInput::IsPress(VK_RIGHT)
		)
	{
		UpperStateChange(UpperBodyState::Idle);
		return;
	}

	if (
		false == EngineInput::IsPress(VK_LEFT) &&
		false == EngineInput::IsPress(VK_RIGHT)
		)
	{
		UpperStateChange(UpperBodyState::Idle);
		return;
	}

	if (true == EngineInput::IsPress(VK_UP))
	{
		UpperStateChange(UpperBodyState::AimNormalToUp);
		return;
	}

	if (true == EngineInput::IsPress(VK_DOWN))
	{
		Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
		Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
		AllStateChange(AllBodyState::Crouch_Intro);
		return;
	}

	if (
		true == EngineInput::IsDown('A') ||
		true == EngineInput::IsDown('a')
		)
	{
		UpperStateChange(UpperBodyState::Shoot);
		return;
	}

	if (
		true == EngineInput::IsDown('S') ||
		true == EngineInput::IsDown('s')
		)
	{
		UpperStateChange(UpperBodyState::ForwardJump);
		return;
	}

	if (
		true == EngineInput::IsDown('D') ||
		true == EngineInput::IsDown('d')
		)
	{
		UpperStateChange(UpperBodyState::Throw);
		return;
	}
}

void Marco::UpperJump(float _DeltaTime)
{

	if (InAir)
	{
		if (true == EngineInput::IsPress(VK_UP))
		{
			UpperStateChange(UpperBodyState::AimNormalToUp);
			return;
		}

		if (true == EngineInput::IsPress(VK_DOWN))
		{
			UpperStateChange(UpperBodyState::AimNormalToDown);
			return;
		}

		if (
			true == EngineInput::IsDown('A') ||
			true == EngineInput::IsDown('a')
			)
		{
			UpperStateChange(UpperBodyState::Shoot);
			return;
		}

		if (
			true == EngineInput::IsDown('D') ||
			true == EngineInput::IsDown('d')
			)
		{
			UpperStateChange(UpperBodyState::Throw);
			return;
		}
	}
	else
	{
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperForwardJump(float _DeltaTime)
{
	if (InAir)
	{
		if (true == EngineInput::IsPress(VK_UP))
		{
			UpperStateChange(UpperBodyState::AimNormalToUp);
			return;
		}

		if (true == EngineInput::IsPress(VK_DOWN))
		{
			UpperStateChange(UpperBodyState::AimNormalToDown);
			return;
		}

		if (
			true == EngineInput::IsDown('A') ||
			true == EngineInput::IsDown('a')
			)
		{
			UpperStateChange(UpperBodyState::ForwardJumpShoot);
			return;
		}

		if (
			true == EngineInput::IsDown('D') ||
			true == EngineInput::IsDown('d')
			)
		{
			UpperStateChange(UpperBodyState::Throw);
			return;
		}
	}
	else
	{
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperShoot(float _DeltaTime)
{
	Pistol_Shoot_AccTime += _DeltaTime;
	if (Pistol_Shoot_AccTime > Pistol_Shoot_CoolTime)
	{
		if (
			true == EngineInput::IsPress(VK_LEFT) &&
			DirState == EActorDir::Right
			)
		{
			Pistol_Shoot_AccTime = 0.0;
			UpperStateChange(UpperBodyState::Move);
			return;
		}

		if (
			true == EngineInput::IsPress(VK_RIGHT) &&
			DirState == EActorDir::Left
			)
		{
			Pistol_Shoot_AccTime = 0.0;
			UpperStateChange(UpperBodyState::Move);
			return;
		}

		if (true == EngineInput::IsPress(VK_UP))
		{
			Pistol_Shoot_AccTime = 0.0f;
			UpperStateChange(UpperBodyState::AimNormalToUp);
			return;
		}

		if (
			true == EngineInput::IsDown('A') ||
			true == EngineInput::IsDown('a')
			)
		{
			Pistol_Shoot_AccTime = 0.0f;
			UpperStateChange(UpperBodyState::Shoot);
			return;
		}

		if (
			true == EngineInput::IsDown('D') ||
			true == EngineInput::IsDown('d')
			)
		{
			Pistol_Shoot_AccTime = 0.0f;
			UpperStateChange(UpperBodyState::Throw);
			return;
		}

		if (InAir)
		{
			if (true == EngineInput::IsPress(VK_DOWN))
			{
				Pistol_Shoot_AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimNormalToDown);
				return;
			}
		}
		else
		{
			if (true == EngineInput::IsPress(VK_DOWN))
			{
				Pistol_Shoot_AccTime = 0.0f;
				Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
				Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
				AllStateChange(AllBodyState::Crouch_Intro);
				return;
			}
			
			if (
				true == EngineInput::IsDown('S') ||
				true == EngineInput::IsDown('s')
				)
			{
				Pistol_Shoot_AccTime = 0.0f;
				UpperStateChange(UpperBodyState::Jump);
				return;
			}
		}
	}

	if (Pistol_Shoot_AccTime > Pistol_Shoot_EndTime)
	{
		Pistol_Shoot_AccTime = 0.0f;
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperForwardJumpShoot(float _DeltaTime)
{
	if (InAir)
	{
		Pistol_Shoot_AccTime += _DeltaTime;
		if (Pistol_Shoot_AccTime > Pistol_Shoot_CoolTime)
		{
			if (true == EngineInput::IsPress(VK_UP))
			{
				Pistol_Shoot_AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimNormalToUp);
				return;
			}

			if (true == EngineInput::IsPress(VK_DOWN))
			{
				Pistol_Shoot_AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimNormalToDown);
				return;
			}

			if (
				true == EngineInput::IsDown('A') ||
				true == EngineInput::IsDown('a')
				)
			{
				Pistol_Shoot_AccTime = 0.0f;
				UpperStateChange(UpperBodyState::ForwardJumpShoot);
				return;
			}

			if (
				true == EngineInput::IsDown('D') ||
				true == EngineInput::IsDown('d')
				)
			{
				Pistol_Shoot_AccTime = 0.0f;
				UpperStateChange(UpperBodyState::Throw);
				return;
			}
		}

		if (Pistol_Shoot_AccTime > Pistol_Shoot_EndTime)
		{
			Pistol_Shoot_AccTime = 0.0f;
			UpperStateChange(UpperBodyState::Idle);
			return;
		}
	}
	else
	{
		Pistol_Shoot_AccTime = 0.0f;
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperThrow(float _DeltaTime)
{
	Throw_AccTime += _DeltaTime;
	if (Throw_AccTime > Throw_CoolTime)
	{
		if (true == EngineInput::IsPress(VK_UP))
		{
			Throw_AccTime = 0.0f;
			UpperStateChange(UpperBodyState::AimNormalToUp);
			return;
		}

		if (
			true == EngineInput::IsPress(VK_LEFT) &&
			DirState == EActorDir::Right
			)
		{
			Throw_AccTime = 0.0;
			UpperStateChange(UpperBodyState::Move);
			return;
		}

		if (
			true == EngineInput::IsPress(VK_RIGHT) &&
			DirState == EActorDir::Left
			)
		{
			Throw_AccTime = 0.0;
			UpperStateChange(UpperBodyState::Move);
			return;
		}

		if (
			true == EngineInput::IsDown('A') ||
			true == EngineInput::IsDown('a')
			)
		{
			Throw_AccTime = 0.0f;
			UpperStateChange(UpperBodyState::Shoot);
			return;
		}

		if (
			true == EngineInput::IsDown('D') ||
			true == EngineInput::IsDown('d')
			)
		{
			if (RemainBomb < 2)
			{
				Throw_AccTime = 0.0f;
				UpperStateChange(UpperBodyState::Throw);
				return;
			}
		}

		if (InAir)
		{
			if (true == EngineInput::IsPress(VK_DOWN))
			{
				Throw_AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimNormalToDown);
				return;
			}

		}
		else
		{
			if (true == EngineInput::IsPress(VK_DOWN))
			{
				Throw_AccTime = 0.0f;
				Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
				Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
				AllStateChange(AllBodyState::Crouch_Intro);
				return;
			}

			if (
				true == EngineInput::IsPress(VK_LEFT) ||
				true == EngineInput::IsPress(VK_RIGHT)
				)
			{
				Throw_AccTime = 0.0f;
				UpperStateChange(UpperBodyState::Move);
				return;
			}
			if (
				true == EngineInput::IsDown('S') ||
				true == EngineInput::IsDown('s')
				)
			{
				Throw_AccTime = 0.0f;
				UpperStateChange(UpperBodyState::Jump);
				return;
			}
		}
	}

	if (Throw_AccTime > Throw_EndTime)
	{
		Throw_AccTime = 0.0f;
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperKnifeAttack1(float _DeltaTime)
{
	//콜라이더 배우면 구현
}

void Marco::UpperKnifeAttack2(float _DeltaTime)
{
	//콜라이더 배우면 구현
}

void Marco::UpperAimNormalToUp(float _DeltaTime)
{
	AimNormalToUp_AccTime += _DeltaTime;
	if (AimNormalToUp_AccTime > AimNormalToUp_Delay)
	{
		AimNormalToUp_AccTime = 0.0f;
		UpperStateChange(UpperBodyState::AimUp);
		return;
	}
}

void Marco::UpperAimUpToNormal(float _DeltaTime)
{
	AimNormalToUp_AccTime += _DeltaTime;
	if (AimNormalToUp_AccTime > AimNormalToUp_Delay)
	{
		AimNormalToUp_AccTime = 0.0f;
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperAimUp(float _DeltaTime)
{
	std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
	DirCheck(BodyRenderer::UpperBody, GunCheckedName);

	if (true == EngineInput::IsFree(VK_UP))
	{
		UpperStateChange(UpperBodyState::AimUpToNormal);
		return;
	}

	if (
		true == EngineInput::IsDown('A') ||
		true == EngineInput::IsDown('a')
		)
	{
		UpperStateChange(UpperBodyState::AimUpShoot);
		return;
	}

	if (
		true == EngineInput::IsDown('D') ||
		true == EngineInput::IsDown('d')
		)
	{
		UpperStateChange(UpperBodyState::Throw);
		return;
	}


}

void Marco::UpperAimUpShoot(float _DeltaTime)
{
	Pistol_Shoot_AccTime += _DeltaTime;
	if (Pistol_Shoot_AccTime > Pistol_Shoot_CoolTime)
	{

		if (true == EngineInput::IsFree(VK_UP))
		{
			UpperStateChange(UpperBodyState::AimUp);
		}

		if (
			true == EngineInput::IsDown('A') ||
			true == EngineInput::IsDown('a')
			)
		{
			Pistol_Shoot_AccTime = 0.0f;
			UpperStateChange(UpperBodyState::AimUpShoot);
			return;
		}

		if (
			true == EngineInput::IsDown('D') ||
			true == EngineInput::IsDown('d')
			)
		{
			Pistol_Shoot_AccTime = 0.0f;
			UpperStateChange(UpperBodyState::Throw);
			return;
		}
	}

	if (Pistol_Shoot_AccTime > Pistol_Shoot_EndTime)
	{
		Pistol_Shoot_AccTime = 0.0f;
		UpperStateChange(UpperBodyState::AimUp);
		return;
	}
}

void Marco::UpperAimNormalToDown(float _DeltaTime)
{
	if (InAir)
	{
		if (true == EngineInput::IsFree(VK_DOWN))
		{
			UpperStateChange(UpperBodyState::AimDownToNormal);
		}

		if (
			true == EngineInput::IsDown('A') ||
			true == EngineInput::IsDown('a')
			)
		{
			Pistol_Shoot_AccTime = 0.0f;
			UpperStateChange(UpperBodyState::AimDownShoot);
			return;
		}

		if (
			true == EngineInput::IsDown('D') ||
			true == EngineInput::IsDown('d')
			)
		{
			Pistol_Shoot_AccTime = 0.0f;
			UpperStateChange(UpperBodyState::Throw);
			return;
		}
		
	}
	else
	{
		UpperStateChange(UpperBodyState::Idle);
	}
}

void Marco::UpperAimDownToNormal(float _DeltaTime)
{
	AimDownToNormal_AccTime += _DeltaTime;
	
	if (InAir)
	{
		if (AimDownToNormal_AccTime > AimDownToNormal_Delay)
		{
			UpperStateChange(UpperBodyState::Idle);
			return;
		}

	}
	else
	{
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperAimDownShoot(float _DeltaTime)
{
	if (InAir)
	{
		Pistol_Shoot_AccTime += _DeltaTime;
		if (Pistol_Shoot_AccTime > Pistol_Shoot_CoolTime)
		{

			if (
				true == EngineInput::IsDown('A') ||
				true == EngineInput::IsDown('a')
				)
			{
				Pistol_Shoot_AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimDownShoot);
				return;
			}

			if (
				true == EngineInput::IsDown('D') ||
				true == EngineInput::IsDown('d')
				)
			{
				Pistol_Shoot_AccTime = 0.0f;
				UpperStateChange(UpperBodyState::Throw);
				return;
			}

			if (true == EngineInput::IsFree(VK_DOWN))
			{
				UpperStateChange(UpperBodyState::AimDownToNormal);
			}
		}

	}
	else
	{
		UpperStateChange(UpperBodyState::Idle);
	}
}



void Marco::UpperIdleStart()
{
	CurUpperBodyName = "UpperBody_Idle";
	UpperStart();
}

void Marco::UpperMoveStart()
{
	CurUpperBodyName = "UpperBody_Move";
	UpperStart();
}

void Marco::UpperJumpStart()
{
	CurUpperBodyName = "UpperBody_Jump";
	UpperStart();
}

void Marco::UpperForwardJumpStart()
{
	CurUpperBodyName = "UpperBody_ForwardJump";
	UpperStart();
}

void Marco::UpperShootStart()
{
	//SpawnActor<Bullet>
	CurUpperBodyName = "UpperBody_Shoot";
	UpperStart();
}

void Marco::UpperForwardJumpShootStart()
{
	//SpawnActor<Bullet>
	CurUpperBodyName = "UpperBody_ForwardJumpShoot";
	UpperStart();
}

void Marco::UpperThrowStart()
{
	//SpawnActor<Bomb>
	CurUpperBodyName = "UpperBody_Throw";
	UpperStart();
}

void Marco::UpperKnifeAttack1Start()
{
	CurUpperBodyName = "UpperBody_KnifeAttack1";
	UpperStart();
}

void Marco::UpperKnifeAttack2Start()
{
	CurUpperBodyName = "UpperBody_KnifeAttack2";
	UpperStart();
}

void Marco::UpperAimNormalToUpStart()
{
	CurUpperBodyName = "UpperBody_AimNormalToUp";
	UpperStart();
}

void Marco::UpperAimUpToNormalStart()
{
	CurUpperBodyName = "UpperBody_AimUpToNormal";
	UpperStart();
}

void Marco::UpperAimUpStart()
{
	CurUpperBodyName = "UpperBody_AimUp";
	UpperStart();
}

void Marco::UpperAimUpShootStart()
{
	//SpawnActor<Bullet>
	CurUpperBodyName = "UpperBody_AimUpShoot";
	UpperStart();
}

void Marco::UpperAimNormalToDownStart()
{
	CurUpperBodyName = "UpperBody_AimNormalToDown";
	UpperStart();
}

void Marco::UpperAimDownToNormalStart()
{
	CurUpperBodyName = "UpperBody_AimDownToNormal";
	UpperStart();
}

void Marco::UpperAimDownShootStart()
{
	//SpawnActor<Bullet>
	CurUpperBodyName = "UpperBody_AimDownShoot";
	UpperStart();
}

void Marco::UpperStart()
{
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName,true);
	std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
	DirCheck(BodyRenderer::UpperBody, GunCheckedName);
}

void Marco::LowerIdle(float _DeltaTime)
{
	DirCheck(BodyRenderer::LowerBody, CurLowerBodyName);
	GravityCheck(_DeltaTime);
	if (
		true == EngineInput::IsPress(VK_LEFT) &&
		true == EngineInput::IsPress(VK_RIGHT)
		)
	{
		return;
	}

	if (
		true == EngineInput::IsPress(VK_LEFT) ||
		true == EngineInput::IsPress(VK_RIGHT)
		)
	{
		LowerStateChange(LowerBodyState::Move);
		return;
	}

	if (
		true == EngineInput::IsDown('S') || 
		true == EngineInput::IsDown('s')
		)
	{
		LowerStateChange(LowerBodyState::Jump);
		return;
	}

	if (true == EngineInput::IsPress(VK_DOWN))
	{
		Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOff();
		return;
	}

}

void Marco::LowerMove(float _DeltaTime)
{
	DirCheck(BodyRenderer::LowerBody, CurLowerBodyName);
	GravityCheck(_DeltaTime);

	if (
		true == EngineInput::IsPress(VK_LEFT) &&
		true == EngineInput::IsPress(VK_RIGHT)
		)
	{
		LowerStateChange(LowerBodyState::Idle);
		return;
	}

	if (
		false == EngineInput::IsPress(VK_LEFT) && 
		false == EngineInput::IsPress(VK_RIGHT)
		)
	{
		LowerStateChange(LowerBodyState::Idle);
		return;
	}

	FVector MovePos = FVector::Zero;
	if (EngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * Run_Speed;
	}

	if (EngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * Run_Speed;
	}

	if (
		true == EngineInput::IsDown('S') ||
		true == EngineInput::IsDown('s')
		)
	{
		LowerStateChange(LowerBodyState::ForwardJump);
		return;
	}

	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 30;
		break;
	case EActorDir::Right:
		CheckPos.X += 30;
		break;
	default:
		break;
	}
	CheckPos.Y -= 30;
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(MovePos);
		GetWorld()->AddCameraPos(MovePos);
	}
}

void Marco::LowerJump(float _DeltaTime)
{
	GravityCheck(_DeltaTime);
	if (InAir)
	{
		FVector MovePos = FVector::Zero;
		if (EngineInput::IsPress(VK_LEFT))
		{
			MovePos += FVector::Left * _DeltaTime * InAir_Speed;
		}

		if (EngineInput::IsPress(VK_RIGHT))
		{
			MovePos += FVector::Right * _DeltaTime * InAir_Speed;
		}
		AddActorLocation(MovePos);
	}
	else
	{
		LowerStateChange(LowerBodyState::Idle);
		return;
	}
}

void Marco::LowerForwardJump(float _DeltaTime)
{
	GravityCheck(_DeltaTime);
	if (InAir)
	{
		FVector MovePos = FVector::Zero;
		if (EngineInput::IsPress(VK_LEFT))
		{
			MovePos += FVector::Left * _DeltaTime * InAir_Speed;
		}

		if (EngineInput::IsPress(VK_RIGHT))
		{
			MovePos += FVector::Right * _DeltaTime * InAir_Speed;
		}
		AddActorLocation(MovePos);
	}
	else
	{
		LowerStateChange(LowerBodyState::Idle);
		return;
	}
}

void Marco::LowerIdleStart()
{
	CurLowerBodyName = "LowerBody_Idle";
	LowerStart();
}

void Marco::LowerMoveStart()
{
	CurLowerBodyName = "LowerBody_Move";
	LowerStart();
}

void Marco::LowerJumpStart()
{
	//addforce
	CurLowerBodyName = "LowerBody_Jump";
	LowerStart();
}

void Marco::LowerForwardJumpStart()
{
	//addforce
	CurLowerBodyName = "LowerBody_ForwardJump";
	LowerStart();
}

void Marco::LowerStart()
{
	std::string AddedDirectionName = AddDirectionName(CurLowerBodyName);
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(AddedDirectionName, true);
	DirCheck(BodyRenderer::LowerBody, CurLowerBodyName);
}

void Marco::AllSpawn(float _DeltaTime)
{
}

void Marco::AllCrouch_Intro(float _DeltaTime)
{
	CrouchIntro_AccTime += _DeltaTime;
	if (CrouchIntro_AccTime > CrouchIntro_Delay)
	{
		AllStateChange(AllBodyState::Crouch_Idle);
	}
}

void Marco::AllCrouch_Outro(float _DeltaTime)
{
}

void Marco::AllCrouch_Idle(float _DeltaTime)
{
}

void Marco::AllCrouch_Move(float _DeltaTime)
{
}

void Marco::AllCrouch_Shoot(float _DeltaTime)
{
}

void Marco::AllCrouch_HeavyMachineGun_Shoot(float _DeltaTime)
{
}

void Marco::AllCrouch_Throw(float _DeltaTime)
{
}

void Marco::AllCrouch_KnifeAttack1(float _DeltaTime)
{
}

void Marco::AllCrouch_KnifeAttack2(float _DeltaTime)
{
}

void Marco::AllCeremony(float _DeltaTime)
{
}

void Marco::AllDeath(float _DeltaTime)
{
}

void Marco::AllDeathInAir(float _DeltaTime)
{
}

void Marco::AllDeathByKnife(float _DeltaTime)
{
}

void Marco::AllElephantSlug_Idle(float _DeltaTime)
{
}

void Marco::AllElephantSlug_Move(float _DeltaTime)
{
}

void Marco::AllSpawnStart()
{
	CurAllBodyName = "AllBody_Spawn";
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(CurAllBodyName);
}

void Marco::AllCrouch_IntroStart()
{
	CurAllBodyName = "AllBody_Crouch_Intro";
	AllStart();
}

void Marco::AllCrouch_OutroStart()
{
}

void Marco::AllCrouch_IdleStart()
{
}

void Marco::AllCrouch_MoveStart()
{
}

void Marco::AllCrouch_ShootStart()
{
}

void Marco::AllCrouch_HeavyMachineGun_ShootStart()
{
}

void Marco::AllCrouch_ThrowStart()
{
}

void Marco::AllCrouch_KnifeAttack1Start()
{
}

void Marco::AllCrouch_KnifeAttack2Start()
{
}

void Marco::AllCeremonyStart()
{
}

void Marco::AllDeathStart()
{
}

void Marco::AllDeathInAirStart()
{
}

void Marco::AllDeathByKnifeStart()
{
}

void Marco::AllElephantSlug_IdleStart()
{
}

void Marco::AllElephantSlug_MoveStart()
{
}

void Marco::AllStart()
{
	std::string AddedGunTypeName = AddGunTypeName(CurAllBodyName);
	std::string DirectedName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(DirectedName);
	std::string GunCheckedName = AddGunTypeName(CurAllBodyName);
	DirCheck(BodyRenderer::AllBody, GunCheckedName);
}

void Marco::Zombie_AllTransformToZombie_Intro(float _DeltaTime)
{
}

void Marco::Zombie_AllTransformToZombie_Falling(float _DeltaTime)
{
}

void Marco::Zombie_AllTransformToZombie_Rising(float _DeltaTime)
{
}

void Marco::Zombie_AllIdle(float _DeltaTime)
{
}

void Marco::Zombie_AllMove(float _DeltaTime)
{
}

void Marco::Zombie_AllTurn(float _DeltaTime)
{
}

void Marco::Zombie_AllAimupTurn(float _DeltaTime)
{
}

void Marco::Zombie_AllJump(float _DeltaTime)
{
}

void Marco::Zombie_AllVomit(float _DeltaTime)
{
}

void Marco::Zombie_AllDeath(float _DeltaTime)
{
}

void Marco::Zombie_AllDeathInAir(float _DeltaTime)
{
}

void Marco::Zombie_AllTransformToZombie_IntroStart()
{
}

void Marco::Zombie_AllTransformToZombie_FallingStart()
{
}

void Marco::Zombie_AllTransformToZombie_RisingStart()
{
}

void Marco::Zombie_AllIdleStart()
{
}

void Marco::Zombie_AllMoveStart()
{
}

void Marco::Zombie_AllTurnStart()
{
}

void Marco::Zombie_AllAimupTurnStart()
{
}

void Marco::Zombie_AllJumpStart()
{
}

void Marco::Zombie_AllVomitStart()
{
}

void Marco::Zombie_AllDeathStart()
{
}

void Marco::Zombie_AllDeathInAirStart()
{
}

void Marco::ZombieStart()
{
}
