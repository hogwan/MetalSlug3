#include "Marco.h"
#include <EngineCore\EngineCore.h>
#include <EngineBase/EngineTime.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineSound.h>
#include "Bullet.h"
#include "PistolBullet.h"
#include "HeavyMachineGunBullet.h"
#include "Bomb.h"
#include "CreateMarcoAnimation.h"
#include "ContentsHelper.h"
#include "ZombieVomitProjectile.h"
#include "CameraManager.h"
#include "Enemy.h"
#include "VomitLauncher.h"
#include "POWs.h"
#include "FlameShotBullet.h"
#include "RocketLauncherBullet.h"
#include "ZombieThunder.h"


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

	Collision = CreateCollision(MT3CollisionOrder::Player);
	Collision->SetScale(DefaultCollisionScale);
	Collision->SetPosition(DefaultCollisionPosition);
	Collision->SetColType(ECollisionType::Rect);

	KnifeReach = CreateCollision(MT3CollisionOrder::PlayerKnife);
	KnifeReach->SetScale(KnifeReachCollisionScale);
	KnifeReach->SetPosition(KnifeReachCollisionPosition_Right);
	KnifeReach->SetColType(ECollisionType::Rect);

	GroundCheckCol = CreateCollision(MT3CollisionOrder::Player);
	GroundCheckCol->SetScale({1,1});
	GroundCheckCol->SetPosition({ 0,5 });
	GroundCheckCol->SetColType(ECollisionType::Rect);

	RightCheckCol = CreateCollision(MT3CollisionOrder::Player);
	RightCheckCol->SetScale({ 1,1 });
	RightCheckCol->SetPosition({ 25,-30 });
	RightCheckCol->SetColType(ECollisionType::Rect);

	LeftCheckCol = CreateCollision(MT3CollisionOrder::Player);
	LeftCheckCol->SetScale({ 1,1 });
	LeftCheckCol->SetPosition({ -25,-30 });
	LeftCheckCol->SetColType(ECollisionType::Rect);

	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetImage("Marco_UpperBody.png");
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransform({ MarcoDefaultUpperBodyOffset, MarcoSize });
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetImage("Marco_LowerBody.png");
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetTransform({ {0,0}, MarcoSize });
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetImage("Marco_AllBody.png");
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetTransform({ {0,0}, MarcoSize });
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetImage("Marco_ZombieArm.png");
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetTransform({ {10,-60} ,MarcoSize });
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetTransColor({ 0,0,0,255 });

	CreateMarcoAnimation;

	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation("Pistol_UpperBody_Idle_Right");
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation("LowerBody_Idle_Right");

	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();

	UpperStateChange(UpperBodyState::Idle);
	LowerStateChange(LowerBodyState::Idle);
	AllStateChange(AllBodyState::None);
	ZombieArmStateChange(ZombieArmState::None);

	GetWorld()->SetCameraPos({ 0,497 });
}


void Marco::Tick(float _DeltaTime)
{
	CameraUpdate(_DeltaTime);
	if (OutOfControl(_DeltaTime))
	{
		return;
	}

	ArmsCheck();

	InAirCheck(_DeltaTime);
	GravityCheck(_DeltaTime);
	GroundUp();
	DeathCheck();

	if (Manipulate)
	{
		ManipulateUpdate(_DeltaTime);
	}

	AllBodyStateUpdate(_DeltaTime);
	if (!IsZombie)
	{
		UpperStateUpdate(_DeltaTime);
		LowerStateUpdate(_DeltaTime);
	}
	else
	{
		ZombieArmStateUpdate(_DeltaTime);
	}

}

void Marco::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	Color8Bit CrouchColor = UContentsHelper::CrouchColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() + 3, Color8Bit::MagentaA);
	GroundCheckCol->SetPosition({ 0,0 });
	CalGravityVector(_DeltaTime);
	std::vector<UCollision*> Result;
	if (Color == Color8Bit(255, 0, 255, 0) && !IsCrouching)
	{
		JumpVector = FVector::Zero;
	}
	else if (CrouchColor == Color8Bit(255, 255, 0, 0) && IsCrouching)
	{
		JumpVector = FVector::Zero;
	}
	else if (GroundCheckCol->CollisionCheck(MT3CollisionOrder::Monoliths, Result))
	{
		JumpVector = FVector::Zero;
	}
	else if (IsCrouching)
	{
		JumpVector = FVector::Down * 10000.f * _DeltaTime;
	}
	else
	{
		JumpVector += GravityVector * _DeltaTime;
	}
	AddActorLocation(JumpVector * _DeltaTime);
}

void Marco::InAirCheck(float _DeltaTime)
{
	Color8Bit CrouchColor = UContentsHelper::CrouchColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY()+3, Color8Bit::MagentaA);
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY()+3, Color8Bit::MagentaA);
	GroundCheckCol->SetPosition({ 0,3 });
	std::vector<UCollision*> Result;
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		AccInAir = 0.0f;
		InAir = false;
	}
	else if (CrouchColor == Color8Bit(255, 255, 0, 0))
	{
		AccInAir = 0.0f;
		InAir = false;
	}
	else if (GroundCheckCol->CollisionCheck(MT3CollisionOrder::Monoliths, Result))
	{
		AccInAir = 0.0f;
		InAir = false;
	}
	else
	{
		AccInAir += _DeltaTime;
		if (AccInAir > InAirTime)
		{
			AccInAir = 0.0f;
			InAir = true;
		}
	}
}

void Marco::DeathCheck()
{
	if(true == UEngineInput::IsDown('Q'))
	{
		IsZombie = true;
		Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
		Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOff();
		Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
		Collision->SetScale(DefaultCollisionScale);
		Collision->SetPosition(DefaultCollisionPosition);
		AllStateChange(AllBodyState::TransformToZombie_Intro);
		return;
	}

	if (NoHitOn) NoHit = true;

	std::vector<UCollision*> Result;
	if (IsZombie)
	{
		if (NoHit) return;
		//if(좀비 DNA 피격 시) || (TrueDamaged)
		if (
			true == Collision->CollisionCheck(MT3CollisionOrder::ZombieProjectile, Result)
			)
		{
			Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
			if (InAir)
			{
				AllStateChange(AllBodyState::Zombie_DeathInAir);
				return;
			}
			else
			{
				AllStateChange(AllBodyState::Zombie_Death);
				return;
			}
		}
	}
	else
	{
		//if(좀비 DNA 피격 시)
		if (
			true == Collision->CollisionCheck(MT3CollisionOrder::ZombieProjectile, Result)
			)
		{
			IsZombie = true;
			Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
			Collision->SetScale(DefaultCollisionScale);
			Collision->SetPosition(DefaultCollisionPosition);
			AllStateChange(AllBodyState::TransformToZombie_Intro);
			return;
		}
		//else if(좀비 DNA없는 것에 피격시) || TrueDamaged
		else if (
			true == Collision->CollisionCheck(MT3CollisionOrder::EnemyProjectile, Result)
			)
		{
			if (NoHit) return;
			Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
			if (InAir)
			{
				AllStateChange(AllBodyState::DeathInAir);
				return;
			}
			else
			{
				AllStateChange(AllBodyState::Death);
				return;
			}
		}
		else if (
			true == Collision->CollisionCheck(MT3CollisionOrder::EnemyKnife, Result)
			)
		{
			if (NoHit) return;
			Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
			AllStateChange(AllBodyState::DeathByKnife);
			return;
		}

	}
}

void Marco::ManipulateUpdate(float _DeltaTime)
{
	if (!InAir)
	{
		if (true == UEngineInput::IsDown('S') ||
			true == UEngineInput::IsDown('s'))
		{
			if (IsZombie)
			{
				AllStateChange(AllBodyState::Zombie_Jump);
			}
			else
			{
				//AddForce()
				AddActorLocation(FVector::Up * 20);
				JumpVector = JumpPower;
			}
		}
	}

	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 20;
		break;
	case EActorDir::Right:
		CheckPos.X += 20;
		break;
	default:
		break;
	}
	CheckPos.Y -= 20;
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);

	if (Color == Color8Bit(255, 0, 255, 0))
	{
		return;
	}

	if (CheckPos.X < GetWorld()->GetCameraPos().X ||
		CheckPos.X > GetWorld()->GetCameraPos().X + GEngine->MainWindow.GetWindowScale().X)
	{
		return;
	}

	{
		std::vector<UCollision*> Result;
		if ((RightCheckCol->CollisionCheck(MT3CollisionOrder::Enemy, Result) && true == UEngineInput::IsPress(VK_RIGHT))
			|| (RightCheckCol->CollisionCheck(MT3CollisionOrder::Monoliths, Result) && true == UEngineInput::IsPress(VK_RIGHT)))
		{
			return;
		}
	}

	{
		std::vector<UCollision*> Result;
		if ((LeftCheckCol->CollisionCheck(MT3CollisionOrder::Enemy, Result) && true == UEngineInput::IsPress(VK_LEFT))
			|| (LeftCheckCol->CollisionCheck(MT3CollisionOrder::Monoliths, Result) && true == UEngineInput::IsPress(VK_LEFT)))
		{
			return;
		}
	}


	if (!CrouchShooting)
	{
		if (true == UEngineInput::IsPress(VK_LEFT) &&
			false == UEngineInput::IsPress(VK_RIGHT))
		{
			AddActorLocation({ FVector::Left.X * Move_Speed * _DeltaTime, 0.0f });
		}
		else if (false == UEngineInput::IsPress(VK_LEFT)&&
				 true == UEngineInput::IsPress(VK_RIGHT))
		{
			AddActorLocation({ FVector::Right.X * Move_Speed * _DeltaTime, 0.0f });
		}
	}


}

std::string Marco::DirCheck(BodyRenderer _BodyRendererType, std::string _Name)
{
	if (
		true == UEngineInput::IsPress(VK_RIGHT) &&
		true == UEngineInput::IsPress(VK_LEFT)
		)
	{
		return AddDirectionName(_Name);
	}

	EActorDir Dir = DirState;
	if (Dir == EActorDir::Left)
	{
		Juming_UpperBodyOffset = Juming_UpperBodyOffset_Left;
		ForwardJumping_UpperBodyOffset = ForwardJumping_UpperBodyOffset_Left;
	}
	else if (Dir == EActorDir::Right)
	{
		Juming_UpperBodyOffset = Juming_UpperBodyOffset_Right;
		ForwardJumping_UpperBodyOffset = ForwardJumping_UpperBodyOffset_Right;
	}

	if (!InAir)
	{
		if (UEngineInput::IsPress(VK_LEFT))
		{
			Dir = EActorDir::Left;
		}
		if (UEngineInput::IsPress(VK_RIGHT))
		{
			Dir = EActorDir::Right;
		}

	}

	if (Dir != DirState)
	{
		DirState = Dir;
		std::string ChangeName = AddDirectionName(_Name);
		int PrevFrame = Renderer[static_cast<int>(_BodyRendererType)]->GetCurAnimationFrame();
		float PrevTime = Renderer[static_cast<int>(_BodyRendererType)]->GetCurAnimationTime();
		Renderer[static_cast<int>(_BodyRendererType)]->ChangeAnimation(ChangeName, false, PrevFrame, PrevTime);
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

void Marco::HeavyMachineGunCheckName(std::string& CurAnimName)
{
	if (Gun == EGunList::HeavyMachineGun)
	{
		CurAnimName.replace(0, 6, "HeavyMachineGun_");
	}
	else return;
}

void Marco::GunTypeShootCheck()
{
	switch (Gun)
	{
	case EGunList::Pistol:
		AccTime = &Pistol_Shoot_AccTime;
		CoolTime = &Pistol_Shoot_CoolTime;
		break;
	case EGunList::HeavyMachineGun:
		AccTime = &HeavyMachineGun_Shoot_AccTime;
		CoolTime = &HeavyMachineGun_Shoot_CoolTime;
		break;
	case EGunList::FlameShot:
		AccTime = &FlameShot_Shoot_AccTime;
		CoolTime = &FlameShot_Shoot_CoolTime;
		break;
	case EGunList::RocketLauncher:
		AccTime = &RocketLauncher_Shoot_AccTime;
		CoolTime = &RocketLauncher_Shoot_CoolTime;
		break;
	default:
		break;
	}
}

void Marco::TriggerDirCheck(BodyRenderer _BodyRenderer, std::string _Name)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		DirState = EActorDir::Left;
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		DirState = EActorDir::Right;
	}

	std::string ChangeName = AddDirectionName(_Name);
	int PrevFrame = Renderer[static_cast<int>(_BodyRenderer)]->GetCurAnimationFrame();
	float PrevTime = Renderer[static_cast<int>(_BodyRenderer)]->GetCurAnimationTime();
	Renderer[static_cast<int>(_BodyRenderer)]->ChangeAnimation(ChangeName, false, PrevFrame, PrevTime);
}

void Marco::UpperStateUpdate(float _DeltaTime)
{
	switch (UpperState)
	{
	case UpperBodyState::None:
		UpperNone(_DeltaTime);
		break;
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
	case UpperBodyState::AimNormalToUpShoot:
		UpperAimNormalToUpShoot(_DeltaTime);
		break;
	case UpperBodyState::AimUpToNormalShoot:
		UpperAimUpToNormalShoot(_DeltaTime);
		break;
	case UpperBodyState::AimNormalToDownShoot:
		UpperAimNormalToDownShoot(_DeltaTime);
		break;
	case UpperBodyState::AimDownToNormalShoot:
		UpperAimDownToNormalShoot(_DeltaTime);
		break;
	default:
		break;
	}
}
void Marco::LowerStateUpdate(float _DeltaTime)
{
	switch (LowerState)
	{
	case LowerBodyState::None:
		LowerNone(_DeltaTime);
		break;
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
	case AllBodyState::None:
		AllNone(_DeltaTime);
		break;
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
void Marco::ZombieArmStateUpdate(float _DeltaTime)
{
	switch (ZArmState)
	{
	case ZombieArmState::None:
		ZombieArm_None(_DeltaTime);
		break;
	case ZombieArmState::Idle:
		ZombieArm_Idle(_DeltaTime);
		break;
	case ZombieArmState::Idle_AimUp:
		ZombieArm_Idle_AimUp(_DeltaTime);
		break;
	case ZombieArmState::Move:
		ZombieArm_Move(_DeltaTime);
		break;
	case ZombieArmState::Move_AimUp:
		ZombieArm_Move_AimUp(_DeltaTime);
		break;
	case ZombieArmState::Jump:
		ZombieArm_Jump(_DeltaTime);
		break;
	case ZombieArmState::Jump_AimUp:
		ZombieArm_Jump_AimUp(_DeltaTime);
		break;
	case ZombieArmState::Shoot:
		ZombieArm_Shoot(_DeltaTime);
		break;
	case ZombieArmState::Shoot_AimUp:
		ZombieArm_Shoot_AimUp(_DeltaTime);
		break;
	case ZombieArmState::AimNormalToUp:
		ZombieArm_AimNormalToUp(_DeltaTime);
		break;
	case ZombieArmState::AimUpToNormal:
		ZombieArm_AimUpToNormal(_DeltaTime);
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
		case UpperBodyState::None:
			UpperNoneStart();
			break;
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
		case UpperBodyState::AimNormalToUpShoot:
			UpperAimNormalToUpShootStart();
			break;
		case UpperBodyState::AimUpToNormalShoot:
			UpperAimUpToNormalShootStart();
			break;
		case UpperBodyState::AimNormalToDownShoot:
			UpperAimNormalToDownShootStart();
			break;
		case UpperBodyState::AimDownToNormalShoot:
			UpperAimDownToNormalShootStart();
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
		case LowerBodyState::None:
			LowerNoneStart();
			break;
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
		switch (_AllState)
		{
		case AllBodyState::None:
			AllNoneStart();
			break;
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
		case AllBodyState::Ceremony:
			AllCeremonyStart();
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
			Zombie_AllDeathInAirStart();
			break;
		default:
			break;
		}
	}

	switch (_AllState)
	{
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
	}
	AllState = _AllState;
}

void Marco::ZombieArmStateChange(ZombieArmState _State)
{
	if (ZArmState != _State)
	{
		switch (_State)
		{
		case ZombieArmState::None:
			ZombieArm_NoneStart();
			break;
		case ZombieArmState::Idle:
			ZombieArm_IdleStart();
			break;
		case ZombieArmState::Idle_AimUp:
			ZombieArm_Idle_AimUpStart();
			break;
		case ZombieArmState::Move:
			ZombieArm_MoveStart();
			break;
		case ZombieArmState::Move_AimUp:
			ZombieArm_Move_AimUpStart();
			break;
		case ZombieArmState::Jump:
			ZombieArm_JumpStart();
			break;
		case ZombieArmState::Jump_AimUp:
			ZombieArm_Jump_AimUpStart();
			break;
		case ZombieArmState::Shoot:
			ZombieArm_ShootStart();
			break;
		case ZombieArmState::Shoot_AimUp:
			ZombieArm_Shoot_AimUpStart();
			break;
		case ZombieArmState::AimNormalToUp:
			ZombieArm_AimNormalToUpStart();
			break;
		case ZombieArmState::AimUpToNormal:
			ZombieArm_AimUpToNormalStart();
			break;
		default:
			break;
		}
	}

	switch (_State)
	{
	case ZombieArmState::Shoot:
		ZombieArm_ShootStart();
		break;
	case ZombieArmState::Shoot_AimUp:
		ZombieArm_Shoot_AimUpStart();
		break;
	default:
		break;
	}

	ZArmState = _State;
}

void Marco::UpperNone(float _DeltaTime)
{
	UpperStateChange(UpperBodyState::Idle);
	return;
}

void Marco::UpperIdle(float _DeltaTime)
{
	if (InAir)
	{
		UpperStateChange(UpperBodyState::Jump);
		return;
	}
	else
	{
		std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
		DirCheck(BodyRenderer::UpperBody, GunCheckedName);
		if (
			true == UEngineInput::IsPress(VK_LEFT) &&
			true == UEngineInput::IsPress(VK_RIGHT)
			)
		{
			return;
		}

		if (
			true == UEngineInput::IsPress(VK_LEFT) ||
			true == UEngineInput::IsPress(VK_RIGHT)
			)
		{
			UpperStateChange(UpperBodyState::Move);
			return;
		}

		if (true == UEngineInput::IsPress(VK_DOWN))
		{
			Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
			return;
		}

		if (true == UEngineInput::IsPress(VK_UP))
		{
			UpperStateChange(UpperBodyState::AimNormalToUp);
			return;
		}

		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			std::vector<UCollision*> Result;
			if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
				|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
			{
				int random = rand() % 2;
				if (random == 0)
				{
					UpperStateChange(UpperBodyState::KnifeAttack1);
					return;
				}
				else
				{
					UpperStateChange(UpperBodyState::KnifeAttack2);
					return;
				}
			}
			else
			{
				UpperStateChange(UpperBodyState::Shoot);
				return;
			}
		}

		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			UpperStateChange(UpperBodyState::Throw);
			return;
		}
	}


}

void Marco::UpperMove(float _DeltaTime)
{

	if (InAir)
	{
		UpperStateChange(UpperBodyState::ForwardJump);
		return;
	}
	else
	{
		std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
		DirCheck(BodyRenderer::UpperBody, GunCheckedName);
		if (
			true == UEngineInput::IsPress(VK_LEFT) &&
			true == UEngineInput::IsPress(VK_RIGHT)
			)
		{
			UpperStateChange(UpperBodyState::Idle);
			return;
		}

		if (
			false == UEngineInput::IsPress(VK_LEFT) &&
			false == UEngineInput::IsPress(VK_RIGHT)
			)
		{
			UpperStateChange(UpperBodyState::Idle);
			return;
		}

		if (true == UEngineInput::IsPress(VK_UP))
		{
			UpperStateChange(UpperBodyState::AimNormalToUp);
			return;
		}

		if (true == UEngineInput::IsPress(VK_DOWN))
		{
			Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
			return;
		}

		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			std::vector<UCollision*> Result;
			if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
				|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
			{
				int random = rand() % 2;
				if (random == 0)
				{
					UpperStateChange(UpperBodyState::KnifeAttack1);
					return;
				}
				else
				{
					UpperStateChange(UpperBodyState::KnifeAttack2);
					return;
				}
			}
			else
			{
				UpperStateChange(UpperBodyState::Shoot);
				return;
			}
		}

		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			UpperStateChange(UpperBodyState::Throw);
			return;
		}
	}

}

void Marco::UpperJump(float _DeltaTime)
{

	if (InAir)
	{
		if (true == UEngineInput::IsPress(VK_UP))
		{
			UpperStateChange(UpperBodyState::AimNormalToUp);
			return;
		}

		if (true == UEngineInput::IsPress(VK_DOWN))
		{
			UpperStateChange(UpperBodyState::AimNormalToDown);
			return;
		}

		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			std::vector<UCollision*> Result;
			if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
				|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
			{
				int random = rand() % 2;
				if (random == 0)
				{
					UpperStateChange(UpperBodyState::KnifeAttack1);
					return;
				}
				else
				{
					UpperStateChange(UpperBodyState::KnifeAttack2);
					return;
				}
			}
			else
			{
				std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
				TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
				UpperStateChange(UpperBodyState::Shoot);
				return;
			}
		}


		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
			TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
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
		if (true == UEngineInput::IsPress(VK_UP))
		{
			UpperStateChange(UpperBodyState::AimNormalToUp);
			return;
		}

		if (true == UEngineInput::IsPress(VK_DOWN))
		{
			UpperStateChange(UpperBodyState::AimNormalToDown);
			return;
		}

		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			std::vector<UCollision*> Result;
			if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
				|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
			{
				int random = rand() % 2;
				if (random == 0)
				{
					UpperStateChange(UpperBodyState::KnifeAttack1);
					return;
				}
				else
				{
					UpperStateChange(UpperBodyState::KnifeAttack2);
					return;
				}
			}
			else
			{
				std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
				TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
				UpperStateChange(UpperBodyState::ForwardJumpShoot);
				return;
			}
		}

		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
			TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
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
	GunTypeShootCheck();

	
	if (Gun == EGunList::HeavyMachineGun)
	{	
		if (true == UEngineInput::IsPress(VK_UP))
		{
			HeavyMachineGun_PrevFrame = -1;
			UpperStateChange(UpperBodyState::AimNormalToUpShoot);
			return;
		}

		if (InAir)
		{
			if (true == UEngineInput::IsPress(VK_DOWN))
			{
				HeavyMachineGun_PrevFrame = -1;
				UpperStateChange(UpperBodyState::AimNormalToDownShoot);
				return;
			}
		}
		std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
		HeavyMachineGunCheckName(GunCheckedName);
		DirCheck(BodyRenderer::UpperBody, GunCheckedName);
		if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
		{
			HeavyMachineGun_PrevFrame = -1;
			UpperStateChange(UpperBodyState::Idle);
			return;
		}

		int CurFrame = Renderer[static_cast<int>(BodyRenderer::UpperBody)]->GetCurAnimationFrame();

		if (CurFrame >= 3)
		{
			if (
				true == UEngineInput::IsPress('A') ||
				true == UEngineInput::IsPress('a')
				)
			{
				std::vector<UCollision*> Result;
				if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
					|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
				{
					int random = rand() % 2;
					if (random == 0)
					{
						UpperStateChange(UpperBodyState::KnifeAttack1);
						return;
					}
					else
					{
						UpperStateChange(UpperBodyState::KnifeAttack2);
						return;
					}
				}
				else
				{
					UpperStateChange(UpperBodyState::Shoot);
					return;
				}
			}
		}
		if (CurFrame != HeavyMachineGun_PrevFrame)
		{
			FVector BulletSpawnLocation = MarcoUpperBodyOffset + Standing_RifleBulletSpawnOffset;
			
			FVector BulletDir = FVector::Zero;
			if (DirState == EActorDir::Right)
			{
				BulletSpawnLocation += BulletSpawnOffset_Right;
				int RandomInt = rand();
				FVector RandomVector = HeavyMachineGun_RightArr[RandomInt % 5];
				BulletDir = RandomVector;
			}
			else if (DirState == EActorDir::Left)
			{
				BulletSpawnLocation += BulletSpawnOffset_Left;
				int RandomInt = rand();
				FVector RandomVector = HeavyMachineGun_LeftArr[RandomInt % 5];
				BulletDir = RandomVector;
			}
			BulletDir.Normalize2D();

			ABullet* Bullet = GetWorld()->SpawnActor<AHeavyMachineGunBullet>(MT3RenderOrder::Projectile);
			--ArmsCount;
			FVector BulletLocation = GetActorLocation() + BulletSpawnLocation;
			Bullet->SetActorLocation(BulletLocation);
			Bullet->SetDir(BulletDir);

			HeavyMachineGun_PrevFrame = CurFrame;
		}
	}
	else
	{

		*AccTime += _DeltaTime;
		if (InAir)
		{
			if (*AccTime > *CoolTime)
			{
				if (true == UEngineInput::IsPress(VK_UP))
				{
					*AccTime = 0.0f;
					UpperStateChange(UpperBodyState::AimNormalToUp);
					return;
				}

				if (true == UEngineInput::IsPress(VK_DOWN))
				{
					*AccTime = 0.0f;
					UpperStateChange(UpperBodyState::AimNormalToDown);
					return;
				}

				if (
					true == UEngineInput::IsDown('A') ||
					true == UEngineInput::IsDown('a')
					)
				{
					*AccTime = 0.0f;
					std::vector<UCollision*> Result;
					if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
						|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
					{
						int random = rand() % 2;
						if (random == 0)
						{
							UpperStateChange(UpperBodyState::KnifeAttack1);
							return;
						}
						else
						{
							UpperStateChange(UpperBodyState::KnifeAttack2);
							return;
						}
					}
					else
					{
						std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
						TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
						UpperStateChange(UpperBodyState::Shoot);
						return;
					}
				}

				if (
					true == UEngineInput::IsDown('D') ||
					true == UEngineInput::IsDown('d')
					)
				{
					*AccTime = 0.0f;
					std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
					TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
					UpperStateChange(UpperBodyState::Throw);
					return;
				}
			}
		}
		else
		{
			std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
			DirCheck(BodyRenderer::UpperBody, GunCheckedName);
			if (*AccTime > *CoolTime)
			{
				if (true == UEngineInput::IsPress(VK_DOWN))
				{
					*AccTime = 0.0f;
					Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
					Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
					return;
				}
				if (true == UEngineInput::IsPress(VK_UP))
				{
					*AccTime = 0.0f;
					UpperStateChange(UpperBodyState::AimNormalToUp);
					return;
				}
				if (
					true == UEngineInput::IsDown('A') ||
					true == UEngineInput::IsDown('a')
					)
				{
					*AccTime = 0.0f;
					std::vector<UCollision*> Result;
					if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
						|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
					{
						int random = rand() % 2;
						if (random == 0)
						{
							UpperStateChange(UpperBodyState::KnifeAttack1);
							return;
						}
						else
						{
							UpperStateChange(UpperBodyState::KnifeAttack2);
							return;
						}
					}
					else
					{
						UpperStateChange(UpperBodyState::Shoot);
						return;
					}
				}

				if (
					true == UEngineInput::IsDown('D') ||
					true == UEngineInput::IsDown('d')
					)
				{
					*AccTime = 0.0f;
					UpperStateChange(UpperBodyState::Throw);
					return;
				}
			}
		}

		if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
		{
			*AccTime = 0.0f;
			UpperStateChange(UpperBodyState::Idle);
			return;
		}
	}

}

void Marco::UpperForwardJumpShoot(float _DeltaTime)
{
	GunTypeShootCheck();

	if (InAir)
	{
		if (Gun == EGunList::HeavyMachineGun)
		{
			if (true == UEngineInput::IsPress(VK_UP))
			{
				HeavyMachineGun_PrevFrame = -1;
				UpperStateChange(UpperBodyState::AimNormalToUpShoot);
				return;
			}

			if (true == UEngineInput::IsPress(VK_DOWN))
			{
				HeavyMachineGun_PrevFrame = -1;
				UpperStateChange(UpperBodyState::AimNormalToDownShoot);
				return;
			}

			if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
			{
				HeavyMachineGun_PrevFrame = -1;
				UpperStateChange(UpperBodyState::ForwardJump);
				return;
			}

			int CurFrame = Renderer[static_cast<int>(BodyRenderer::UpperBody)]->GetCurAnimationFrame();
			if (CurFrame >= 3)
			{
				std::vector<UCollision*> Result;
				if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
					|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
				{
					int random = rand() % 2;
					if (random == 0)
					{
						UpperStateChange(UpperBodyState::KnifeAttack1);
						return;
					}
					else
					{
						UpperStateChange(UpperBodyState::KnifeAttack2);
						return;
					}
				}
				else
				{
					std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
					TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
					UpperStateChange(UpperBodyState::ForwardJumpShoot);
					return;
				}
			}
			if (CurFrame != HeavyMachineGun_PrevFrame)
			{
				FVector BulletSpawnLocation = MarcoUpperBodyOffset + Standing_BulletSpawnOffset;

				FVector BulletDir = FVector::Zero;
				if (DirState == EActorDir::Right)
				{
					BulletSpawnLocation += BulletSpawnOffset_Right;
					int RandomInt = rand();
					FVector RandomVector = HeavyMachineGun_RightArr[RandomInt % 5];
					BulletDir = RandomVector;
				}
				else if (DirState == EActorDir::Left)
				{
					BulletSpawnLocation += BulletSpawnOffset_Left;
					int RandomInt = rand();
					FVector RandomVector = HeavyMachineGun_LeftArr[RandomInt % 5];
					BulletDir = RandomVector;
				}
				BulletDir.Normalize2D();

				ABullet* Bullet = GetWorld()->SpawnActor<AHeavyMachineGunBullet>(MT3RenderOrder::Projectile);
				--ArmsCount;
				FVector BulletLocation = GetActorLocation() + BulletSpawnLocation;
				Bullet->SetActorLocation(BulletLocation);
				Bullet->SetDir(BulletDir);

				HeavyMachineGun_PrevFrame = CurFrame;
			}
		}
		else
		{
			*AccTime += _DeltaTime;
			if (AccTime > CoolTime)
			{
				if (true == UEngineInput::IsPress(VK_DOWN))
				{
					*AccTime = 0.0f;
					UpperStateChange(UpperBodyState::AimNormalToDown);
					return;
				}
				if (true == UEngineInput::IsPress(VK_UP))
				{
					*AccTime = 0.0f;
					UpperStateChange(UpperBodyState::AimNormalToUp);
					return;
				}
				if (
					true == UEngineInput::IsDown('A') ||
					true == UEngineInput::IsDown('a')
					)
				{
					*AccTime = 0.0f;
					std::vector<UCollision*> Result;
					if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
						|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
					{
						int random = rand() % 2;
						if (random == 0)
						{
							UpperStateChange(UpperBodyState::KnifeAttack1);
							return;
						}
						else
						{
							UpperStateChange(UpperBodyState::KnifeAttack2);
							return;
						}
					}
					else
					{
						std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
						TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
						UpperStateChange(UpperBodyState::ForwardJumpShoot);
						return;
					}
				}

				if (
					true == UEngineInput::IsDown('D') ||
					true == UEngineInput::IsDown('d')
					)
				{
					*AccTime = 0.0f;
					std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
					TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
					UpperStateChange(UpperBodyState::Throw);
					return;
				}
			}
		}


	}
	else
	{
		*AccTime = 0.0f;
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperThrow(float _DeltaTime)
{
	GunTypeShootCheck();

	*AccTime += _DeltaTime;
	if (InAir)
	{
		if (*AccTime > *CoolTime)
		{
			if (true == UEngineInput::IsPress(VK_UP))
			{
				*AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimNormalToUp);
				return;
			}

			if (true == UEngineInput::IsPress(VK_DOWN))
			{
				*AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimNormalToDown);
				return;
			}
			if (
				true == UEngineInput::IsDown('A') ||
				true == UEngineInput::IsDown('a')
				)
			{
				*AccTime = 0.0f;
				std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
				TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
				UpperStateChange(UpperBodyState::Shoot);
				return;
			}

			if (
				true == UEngineInput::IsDown('D') ||
				true == UEngineInput::IsDown('d')
				)
			{
				*AccTime = 0.0f;
				std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
				TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
				UpperStateChange(UpperBodyState::Throw);
				return;
			}
		}
	}
	else
	{
		std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
		DirCheck(BodyRenderer::UpperBody, GunCheckedName);
		if (*AccTime > *CoolTime)
		{
			if (true == UEngineInput::IsPress(VK_DOWN))
			{
				*AccTime = 0.0f;
				Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
				Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
				return;
			}
			if (true == UEngineInput::IsPress(VK_UP))
			{
				*AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimNormalToUp);
				return;
			}

			if (
				true == UEngineInput::IsDown('A') ||
				true == UEngineInput::IsDown('a')
				)
			{
				*AccTime = 0.0f;
				UpperStateChange(UpperBodyState::Shoot);
				return;
			}

			if (
				true == UEngineInput::IsDown('D') ||
				true == UEngineInput::IsDown('d')
				)
			{
				*AccTime = 0.0f;
				UpperStateChange(UpperBodyState::Throw);
				return;
			}
		}
	}

	if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
	{
		*AccTime = 0.0f;
		UpperStateChange(UpperBodyState::Idle);
		return;
	}

}

void Marco::UpperKnifeAttack1(float _DeltaTime)
{
	
	if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
	{
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperKnifeAttack2(float _DeltaTime)
{
	if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
	{
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperAimNormalToUp(float _DeltaTime)
{
	if (
		true == UEngineInput::IsDown('a') ||
		true == UEngineInput::IsDown('A')
		)
	{
		UpperStateChange(UpperBodyState::AimUpShoot);
		return;
	}
	if(Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
	{
		UpperStateChange(UpperBodyState::AimUp);
		return;
	}
}

void Marco::UpperAimUpToNormal(float _DeltaTime)
{
	if (
		true == UEngineInput::IsDown('a') ||
		true == UEngineInput::IsDown('A')
		)
	{
		UpperStateChange(UpperBodyState::Shoot);
		return;
	}
	if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
	{
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperAimUp(float _DeltaTime)
{
	if (InAir)
	{
		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
			TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
			UpperStateChange(UpperBodyState::AimUpShoot);
			return;
		}

		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
			TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
			UpperStateChange(UpperBodyState::Throw);
			return;
		}
	}
	else
	{
		std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
		DirCheck(BodyRenderer::UpperBody, GunCheckedName);

		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			UpperStateChange(UpperBodyState::AimUpShoot);
			return;
		}

		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			UpperStateChange(UpperBodyState::Throw);
			return;
		}
	}

	if (true == UEngineInput::IsFree(VK_UP))
	{
		UpperStateChange(UpperBodyState::AimUpToNormal);
		return;
	}

}

void Marco::UpperAimUpShoot(float _DeltaTime)
{
	GunTypeShootCheck();
	if (Gun == EGunList::HeavyMachineGun)
	{
		if (true == UEngineInput::IsFree(VK_UP))
		{
			HeavyMachineGun_PrevFrame = -1;
			UpperStateChange(UpperBodyState::AimUpToNormalShoot);
			return;
		}

		if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
		{
			HeavyMachineGun_PrevFrame = -1;
			UpperStateChange(UpperBodyState::Idle);
			return;
		}

		int CurFrame = Renderer[static_cast<int>(BodyRenderer::UpperBody)]->GetCurAnimationFrame();
		if (CurFrame >= 3)
		{
			if (true == UEngineInput::IsPress('A') ||
				true == UEngineInput::IsPress('a'))
			{
				UpperStateChange(UpperBodyState::AimUpShoot);
			}
		}
		if (CurFrame != HeavyMachineGun_PrevFrame)
		{
			FVector BulletSpawnLocation = FVector::Zero;
			FVector BulletDir = FVector::Zero;
			if (DirState == EActorDir::Right)
			{
				BulletSpawnLocation = MarcoUpperBodyOffset + AimUp_RifleBulletSpawnOffset_Right;
				int RandomInt = rand();
				FVector RandomVector = HeavyMachineGun_UpArr[RandomInt % 5];
				BulletDir = RandomVector;
			}
			else if (DirState == EActorDir::Left)
			{
				BulletSpawnLocation = MarcoUpperBodyOffset + AimUp_RifleBulletSpawnOffset_Left;
				int RandomInt = rand();
				FVector RandomVector = HeavyMachineGun_UpArr[RandomInt % 5];
				BulletDir = RandomVector;
			}
			BulletDir.Normalize2D();

			ABullet* Bullet = GetWorld()->SpawnActor<AHeavyMachineGunBullet>(MT3RenderOrder::Projectile);
			--ArmsCount;
			FVector BulletLocation = GetActorLocation() + BulletSpawnLocation;
			Bullet->SetActorLocation(BulletLocation);
			Bullet->SetDir(BulletDir);

			HeavyMachineGun_PrevFrame = CurFrame;
		}
	}
	else
	{
		*AccTime += _DeltaTime;
		if (InAir)
		{
			if (*AccTime > *CoolTime)
			{
				if (true == UEngineInput::IsFree(VK_UP))
				{
					HeavyMachineGun_PrevFrame = -1;
					UpperStateChange(UpperBodyState::AimUpToNormal);
					return;
				}
				if (
					true == UEngineInput::IsDown('A') ||
					true == UEngineInput::IsDown('a')
					)
				{
					*AccTime = 0.0f;
					std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
					TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
					UpperStateChange(UpperBodyState::AimUpShoot);
					return;
				}

				if (
					true == UEngineInput::IsDown('D') ||
					true == UEngineInput::IsDown('d')
					)
				{
					*AccTime = 0.0f;
					std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
					TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
					UpperStateChange(UpperBodyState::Throw);
					return;
				}
			}
		}
		else
		{
			std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
			DirCheck(BodyRenderer::UpperBody, GunCheckedName);
			if (*AccTime > *CoolTime)
			{
				if (true == UEngineInput::IsFree(VK_UP))
				{
					HeavyMachineGun_PrevFrame = -1;
					UpperStateChange(UpperBodyState::AimUpToNormal);
					return;
				}
				if (InAir)
				{
					*AccTime = 0.0f;
					UpperStateChange(UpperBodyState::Jump);
					return;
				}
				if (
					true == UEngineInput::IsDown('A') ||
					true == UEngineInput::IsDown('a')
					)
				{
					*AccTime = 0.0f;
					UpperStateChange(UpperBodyState::AimUpShoot);
					return;
				}

				if (
					true == UEngineInput::IsDown('D') ||
					true == UEngineInput::IsDown('d')
					)
				{
					*AccTime = 0.0f;
					UpperStateChange(UpperBodyState::Throw);
					return;
				}
			}
		}

		if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
		{
			*AccTime = 0.0f;
			UpperStateChange(UpperBodyState::AimUp);
			return;
		}

	}

}

void Marco::UpperAimNormalToDown(float _DeltaTime)
{
	if (InAir)
	{
		if (true == UEngineInput::IsFree(VK_DOWN))
		{
			UpperStateChange(UpperBodyState::AimDownToNormal);
		}

		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
			TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
			UpperStateChange(UpperBodyState::AimDownShoot);
			return;
		}

		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
			TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
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
	if (InAir)
	{
		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
			TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
			UpperStateChange(UpperBodyState::Shoot);
			return;
		}

		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
			TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
			UpperStateChange(UpperBodyState::Throw);
			return;
		}
		if (true == UEngineInput::IsPress(VK_DOWN))
		{
			UpperStateChange(UpperBodyState::AimNormalToDown);
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
	GunTypeShootCheck();

	if (Gun == EGunList::HeavyMachineGun)
	{
		if (true == UEngineInput::IsFree(VK_DOWN))
		{
			HeavyMachineGun_PrevFrame = -1;
			UpperStateChange(UpperBodyState::AimDownToNormalShoot);
			return;
		}

		if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
		{
			HeavyMachineGun_PrevFrame = -1;
			UpperStateChange(UpperBodyState::Idle);
			return;
		}

		int CurFrame = Renderer[static_cast<int>(BodyRenderer::UpperBody)]->GetCurAnimationFrame();
		if (CurFrame >= 3)
		{
			if (true == UEngineInput::IsPress('A') ||
				true == UEngineInput::IsPress('a'))
			{
				UpperStateChange(UpperBodyState::AimDownShoot);
				return;
			}
		}
		if (CurFrame != HeavyMachineGun_PrevFrame)
		{
			FVector BulletSpawnLocation = FVector::Zero;
			FVector BulletDir = FVector::Zero;
			if (DirState == EActorDir::Right)
			{
				BulletSpawnLocation = MarcoUpperBodyOffset + AimDown_RifleBulletSpawnOffset_Right;
				int RandomInt = rand();
				FVector RandomVector = HeavyMachineGun_DownArr[RandomInt % 5];
				BulletDir = RandomVector;
			}
			else if (DirState == EActorDir::Left)
			{
				BulletSpawnLocation = MarcoUpperBodyOffset + AimDown_RifleBulletSpawnOffset_Left;
				int RandomInt = rand();
				FVector RandomVector = HeavyMachineGun_DownArr[RandomInt % 5];
				BulletDir = RandomVector;
			}
			BulletDir.Normalize2D();

			ABullet* Bullet = GetWorld()->SpawnActor<AHeavyMachineGunBullet>(MT3RenderOrder::Projectile);
			--ArmsCount;
			FVector BulletLocation = GetActorLocation() + BulletSpawnLocation;
			Bullet->SetActorLocation(BulletLocation);
			Bullet->SetDir(BulletDir);

			HeavyMachineGun_PrevFrame = CurFrame;
		}
	}
	else
	{
		if (InAir)
		{
			*AccTime += _DeltaTime;
			if (*AccTime > *CoolTime)
			{

				if (
					true == UEngineInput::IsDown('A') ||
					true == UEngineInput::IsDown('a')
					)
				{
					*AccTime = 0.0f;
					std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
					TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
					UpperStateChange(UpperBodyState::AimDownShoot);
					return;
				}

				if (
					true == UEngineInput::IsDown('D') ||
					true == UEngineInput::IsDown('d')
					)
				{
					*AccTime = 0.0f;
					std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
					TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
					UpperStateChange(UpperBodyState::Throw);
					return;
				}

				if (true == UEngineInput::IsFree(VK_DOWN))
				{
					UpperStateChange(UpperBodyState::Idle);
					return;
				}
			}

			if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
			{
				UpperStateChange(UpperBodyState::Idle);
				return;
			}
		}
		else
		{
			*AccTime = 0.0f;
			UpperStateChange(UpperBodyState::Idle);
			return;
		}
	}

}

void Marco::UpperAimNormalToUpShoot(float _DeltaTime)
{
	int CurFrame = Renderer[static_cast<int>(BodyRenderer::UpperBody)]->GetCurAnimationFrame();
	if (CurFrame != HeavyMachineGun_PrevFrame)
	{
		FVector DirectionVector = FVector::Zero;
		if (CurFrame == 0)
		{
			DirectionVector = { 25.0f,-18.0f };
		}
		else if (CurFrame == 1)
		{
			DirectionVector = { 18.0f,-25.0f };
		}
		DirectionVector.Normalize2D();
		FVector BulletSpawnLocation = FVector::Zero;
		if (DirState == EActorDir::Right)
		{
			FVector SpawnAngleVector = { BulletSpawnOffset_Right.Size2D() * DirectionVector.X,  BulletSpawnOffset_Right.Size2D() * DirectionVector.Y };
			BulletSpawnLocation = Standing_RifleBulletSpawnOffset + SpawnAngleVector;
		}
		else if (DirState == EActorDir::Left)
		{
			DirectionVector.X = -DirectionVector.X;
			FVector SpawnAngleVector = { BulletSpawnOffset_Left.Size2D() * DirectionVector.X, BulletSpawnOffset_Left.Size2D() * DirectionVector.Y };
			BulletSpawnLocation = Standing_RifleBulletSpawnOffset + SpawnAngleVector;
		}


		FVector BulletDir = DirectionVector;
		ABullet* Bullet = GetWorld()->SpawnActor<AHeavyMachineGunBullet>(MT3RenderOrder::Projectile);
		--ArmsCount;
		FVector BulletLocation = GetActorLocation() + BulletSpawnLocation;
		Bullet->SetActorLocation(BulletLocation);
		Bullet->SetDir(BulletDir);

		HeavyMachineGun_PrevFrame = CurFrame;
	}

	if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
	{
		UpperStateChange(UpperBodyState::AimUpShoot);
		return;
	}
}

void Marco::UpperAimUpToNormalShoot(float _DeltaTime)
{
	int CurFrame = Renderer[static_cast<int>(BodyRenderer::UpperBody)]->GetCurAnimationFrame();
	if (CurFrame != HeavyMachineGun_PrevFrame)
	{
		FVector DirectionVector = FVector::Zero;
		if (CurFrame == 0)
		{
			DirectionVector = { 18.0f, -25.0f };
		}
		else if (CurFrame == 1)
		{
			DirectionVector = { 25.0f,-18.0f };
		}
		DirectionVector.Normalize2D();
		FVector BulletSpawnLocation = FVector::Zero;
		if (DirState == EActorDir::Right)
		{
			FVector SpawnAngleVector = { BulletSpawnOffset_Right.Size2D() * DirectionVector.X, BulletSpawnOffset_Right.Size2D() * DirectionVector.Y };
			BulletSpawnLocation = Standing_RifleBulletSpawnOffset + SpawnAngleVector;
		}
		else if (DirState == EActorDir::Left)
		{
			DirectionVector.X = -DirectionVector.X;
			FVector SpawnAngleVector = { BulletSpawnOffset_Left.Size2D() * DirectionVector.X, BulletSpawnOffset_Left.Size2D() * DirectionVector.Y };
			BulletSpawnLocation = Standing_RifleBulletSpawnOffset + SpawnAngleVector;
		}

		FVector BulletDir = DirectionVector;
		ABullet* Bullet = GetWorld()->SpawnActor<AHeavyMachineGunBullet>(MT3RenderOrder::Projectile);
		--ArmsCount;
		FVector BulletLocation = GetActorLocation() + BulletSpawnLocation;
		Bullet->SetActorLocation(BulletLocation);
		Bullet->SetDir(BulletDir);

		HeavyMachineGun_PrevFrame = CurFrame;
	}

	if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
	{
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperAimNormalToDownShoot(float _DeltaTime)
{
	int CurFrame = Renderer[static_cast<int>(BodyRenderer::UpperBody)]->GetCurAnimationFrame();
	if (CurFrame != HeavyMachineGun_PrevFrame)
	{
		FVector DirectionVector = FVector::Zero;
		if (CurFrame == 0)
		{
			DirectionVector = { 25.0f,18.0f };
			int a = 0;
		}
		else if (CurFrame == 1)
		{
			DirectionVector = { 18.0f, 25.0f };
			int a = 0;
		}

		DirectionVector.Normalize2D();
		FVector BulletSpawnLocation = FVector::Zero;
		if (DirState == EActorDir::Right)
		{
			FVector SpawnAngleVector = { BulletSpawnOffset_Right.Size2D() * DirectionVector.X, BulletSpawnOffset_Right.Size2D() * DirectionVector.Y };
			BulletSpawnLocation = Standing_RifleBulletSpawnOffset + SpawnAngleVector;
		}
		else if (DirState == EActorDir::Left)
		{
			DirectionVector.X = -DirectionVector.X;
			FVector SpawnAngleVector = { BulletSpawnOffset_Left.Size2D() * DirectionVector.X, BulletSpawnOffset_Left.Size2D() * DirectionVector.Y };
			BulletSpawnLocation = Standing_RifleBulletSpawnOffset + SpawnAngleVector;
		}

		FVector BulletDir = DirectionVector;
		ABullet* Bullet = GetWorld()->SpawnActor<AHeavyMachineGunBullet>(MT3RenderOrder::Projectile);
		--ArmsCount;
		FVector BulletLocation = GetActorLocation() + BulletSpawnLocation;
		Bullet->SetActorLocation(BulletLocation);
		Bullet->SetDir(BulletDir);

		HeavyMachineGun_PrevFrame = CurFrame;
	}

	if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
	{
		UpperStateChange(UpperBodyState::AimDownShoot);
		return;
	}
}

void Marco::UpperAimDownToNormalShoot(float _DeltaTime)
{
	int CurFrame = Renderer[static_cast<int>(BodyRenderer::UpperBody)]->GetCurAnimationFrame();
	if (CurFrame != HeavyMachineGun_PrevFrame)
	{
		FVector DirectionVector = FVector::Zero;
		if (CurFrame == 0)
		{
			DirectionVector = { 18.0f, 25.0f };
		}
		else if (CurFrame == 1)
		{
			DirectionVector = { 25.0f,18.0f };
		}

		DirectionVector.Normalize2D();
		FVector BulletSpawnLocation = FVector::Zero;
		if (DirState == EActorDir::Right)
		{
			FVector SpawnAngleVector = { BulletSpawnOffset_Right.Size2D() * DirectionVector.X, BulletSpawnOffset_Right.Size2D() * DirectionVector.Y };
			BulletSpawnLocation = Standing_RifleBulletSpawnOffset + SpawnAngleVector;
		}
		else if (DirState == EActorDir::Left)
		{
			DirectionVector.X = -DirectionVector.X;
			FVector SpawnAngleVector = { BulletSpawnOffset_Left.Size2D() * DirectionVector.X, BulletSpawnOffset_Left.Size2D() * DirectionVector.Y };
			BulletSpawnLocation = Standing_RifleBulletSpawnOffset + SpawnAngleVector;
		}

		FVector BulletDir = DirectionVector;
		ABullet* Bullet = GetWorld()->SpawnActor<AHeavyMachineGunBullet>(MT3RenderOrder::Projectile);
		--ArmsCount;
		FVector BulletLocation = GetActorLocation() + BulletSpawnLocation;
		Bullet->SetActorLocation(BulletLocation);
		Bullet->SetDir(BulletDir);

		HeavyMachineGun_PrevFrame = CurFrame;
	}
	if (Renderer[static_cast<int>(BodyRenderer::UpperBody)]->IsCurAnimationEnd())
	{
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}


void Marco::UpperNoneStart()
{
	CurUpperBodyName = "None";
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
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true,0,0.07f);

	if (Gun != EGunList::HeavyMachineGun)
	{
		FVector BulletSpawnLocation = MarcoUpperBodyOffset + Standing_BulletSpawnOffset;
		FVector BulletDir = FVector::Zero;
		if (DirState == EActorDir::Right)
		{
			BulletSpawnLocation += BulletSpawnOffset_Right;
			BulletDir = FVector::Right;
		}
		else if (DirState == EActorDir::Left)
		{
			BulletSpawnLocation += BulletSpawnOffset_Left;
			BulletDir = FVector::Left;
		}
		BulletSpawn(BulletSpawnLocation, BulletDir);
	}
	else
	{
		std::vector<UCollision*> Result;
		if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
			|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
		{
			return;
		}
		else
		{
			UEngineSound::SoundPlay("HeavyMachineGun_Launch.mp3");
			return;
		}
	}
}

void Marco::UpperForwardJumpShootStart()
{
	//SpawnActor<Bullet>
	CurUpperBodyName = "UpperBody_ForwardJumpShoot";
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true,0,0.1f);

	if (Gun != EGunList::HeavyMachineGun)
	{
		FVector BulletSpawnLocation = MarcoUpperBodyOffset + Standing_BulletSpawnOffset;
		FVector BulletDir = FVector::Zero;
		if (DirState == EActorDir::Right)
		{
			BulletSpawnLocation += BulletSpawnOffset_Right;
			BulletDir = FVector::Right;
		}
		else if (DirState == EActorDir::Left)
		{
			BulletSpawnLocation += BulletSpawnOffset_Left;
			BulletDir = FVector::Left;
		}

		BulletSpawn(BulletSpawnLocation, BulletDir);
	}
	else
	{
		std::vector<UCollision*> Result;
		if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
			|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
		{
			return;
		}
		else
		{
			UEngineSound::SoundPlay("HeavyMachineGun_Launch.mp3");
			return;
		}
	}
}

void Marco::UpperThrowStart()
{
	//SpawnActor<Bomb>
	CurUpperBodyName = "UpperBody_Throw";
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true, 0 , 0.08f);

	if (BombsCount > 0 && RemainBomb > 0)
	{
		ABomb* Bomb = GetWorld()->SpawnActor<ABomb>();
		--BombsCount;
		FVector ThrowVector = { 3,-3 };
		ThrowVector.Normalize2D();
		float ThrowForce = 400.0f;
		ThrowVector *= ThrowForce;
		FVector SpawnLocation = GetActorLocation();

		if (DirState == EActorDir::Left)
		{
			SpawnLocation += {-30.0f, -100.0f};
			ThrowVector.X = -ThrowVector.X;
		}
		else if (DirState == EActorDir::Right)
		{
			SpawnLocation += {30.0f, -100.0f};
		}

		Bomb->SetActorLocation(SpawnLocation);
		Bomb->SetMoveVector(ThrowVector);
	}
}

void Marco::UpperKnifeAttack1Start()
{
	UContentsHelper::Score += 100;
	UEngineSound::SoundPlay("KnifeAttack1.mp3");

	std::vector<UCollision*> Result;
	if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result))
	{
		for (UCollision* EnemyCol : Result)
		{
			AEnemy* Enemy = dynamic_cast<AEnemy*>(EnemyCol->GetOwner());
			Enemy->Damaged(KnifeDamage);
		}
	}

	if (KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
	{
		APOWs* Pow = dynamic_cast<APOWs*>(Result[0]->GetOwner());
		Pow->StateChange(POWsState::Liberate);
	}

	CurUpperBodyName = "UpperBody_KnifeAttack1";
	UpperStart();
}

void Marco::UpperKnifeAttack2Start()
{
	UContentsHelper::Score += 100;
	UEngineSound::SoundPlay("KnifeAttack2.mp3");

	std::vector<UCollision*> Result;
	if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result))
	{
		for (UCollision* EnemyCol : Result)
		{
			AEnemy* Enemy = dynamic_cast<AEnemy*>(EnemyCol->GetOwner());
			Enemy->Damaged(KnifeDamage);
		}
	}

	if (KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
	{
		APOWs* Pow = dynamic_cast<APOWs*>(Result[0]->GetOwner());
		Pow->StateChange(POWsState::Liberate);
	}
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
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true,0,0.1f);

	if (Gun != EGunList::HeavyMachineGun)
	{
		FVector BulletSpawnLocation = FVector::Zero;
		FVector BulletDir = FVector::Zero;
		if (DirState == EActorDir::Right)
		{
			BulletSpawnLocation = MarcoUpperBodyOffset + AimUp_BulletSpawnOffset_Right;
		}
		else if (DirState == EActorDir::Left)
		{
			BulletSpawnLocation = MarcoUpperBodyOffset + AimUp_BulletSpawnOffset_Left;
		}

		BulletDir = FVector::Up;

		BulletSpawn(BulletSpawnLocation, BulletDir);
	}
	else
	{
		UEngineSound::SoundPlay("HeavyMachineGun_Launch.mp3");
		return;
	}
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
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true,0,0.1f);

	if (Gun != EGunList::HeavyMachineGun)
	{
		FVector BulletSpawnLocation = FVector::Zero;
		FVector BulletDir = FVector::Zero;
		if (DirState == EActorDir::Right)
		{
			BulletSpawnLocation = MarcoUpperBodyOffset + AimDown_BulletSpawnOffset_Right;
		}
		else if (DirState == EActorDir::Left)
		{
			BulletSpawnLocation = MarcoUpperBodyOffset + AimDown_BulletSpawnOffset_Left;
		}

		BulletDir = FVector::Down;

		BulletSpawn(BulletSpawnLocation, BulletDir);
	}
	else
	{
		UEngineSound::SoundPlay("HeavyMachineGun_Launch.mp3");
		return;
	}
}

void Marco::UpperAimNormalToUpShootStart()
{
	CurUpperBodyName = "UpperBody_AimNormalToUpShoot";
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true,0,0.08f);
}

void Marco::UpperAimUpToNormalShootStart()
{
	CurUpperBodyName = "UpperBody_AimUpToNormalShoot";
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true, 0, 0.08f);
}

void Marco::UpperAimNormalToDownShootStart()
{
	CurUpperBodyName = "UpperBody_AimNormalToDownShoot";
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true, 0, 0.08f);
}

void Marco::UpperAimDownToNormalShootStart()
{
	CurUpperBodyName = "UpperBody_AimDownToNormalShoot";
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true, 0, 0.08f);
}

void Marco::UpperStart()
{
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName);
}

void Marco::LowerNone(float _DeltaTime)
{

	LowerStateChange(LowerBodyState::Idle);
}

void Marco::LowerIdle(float _DeltaTime)
{
	DirCheck(BodyRenderer::LowerBody, CurLowerBodyName);
	if (
		true == UEngineInput::IsPress(VK_LEFT) &&
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		return;
	}

	if (
		true == UEngineInput::IsPress(VK_LEFT) ||
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		LowerStateChange(LowerBodyState::Move);
		return;
	}

	if (InAir)
	{
		LowerStateChange(LowerBodyState::Jump);
		return;
	}



	if (InAir)
	{
		LowerStateChange(LowerBodyState::Jump);
		return;
	}
	if (!InAir)
	{
		if (true == UEngineInput::IsPress(VK_DOWN))
		{
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOff();
			return;
		}

	}

}

void Marco::LowerMove(float _DeltaTime)
{
	DirCheck(BodyRenderer::LowerBody, CurLowerBodyName);


	if (
		true == UEngineInput::IsPress(VK_LEFT) &&
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		Reset_UpperBodySyncro();
		LowerStateChange(LowerBodyState::Idle);
		return;
	}

	if (
		false == UEngineInput::IsPress(VK_LEFT) && 
		false == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		Reset_UpperBodySyncro();
		LowerStateChange(LowerBodyState::Idle);
		return;
	}

	if (!InAir)
	{
		if (true == UEngineInput::IsPress(VK_DOWN))
		{
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOff();
			return;
		}
	}

	if (InAir)
	{
		LowerStateChange(LowerBodyState::ForwardJump);
		return;
	}
}

void Marco::LowerJump(float _DeltaTime)
{
	if (InAir)
	{
		if (UEngineInput::IsDown('A') ||
			UEngineInput::IsDown('a'))
		{
			std::string ChangeName = AddDirectionName(CurLowerBodyName);
			int PrevFrame = Renderer[static_cast<int>(BodyRenderer::LowerBody)]->GetCurAnimationFrame();
			float PrevTime = Renderer[static_cast<int>(BodyRenderer::LowerBody)]->GetCurAnimationTime();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(ChangeName, false, PrevFrame, PrevTime);
		}

		if (UEngineInput::IsDown('D') ||
			UEngineInput::IsDown('d'))
		{
			std::string ChangeName = AddDirectionName(CurLowerBodyName);
			int PrevFrame = Renderer[static_cast<int>(BodyRenderer::LowerBody)]->GetCurAnimationFrame();
			float PrevTime = Renderer[static_cast<int>(BodyRenderer::LowerBody)]->GetCurAnimationTime();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(ChangeName, false, PrevFrame, PrevTime);
		}
	}
	else
	{
		Move_Speed = Run_Speed;
		DirCheck(BodyRenderer::LowerBody, CurLowerBodyName);
		Reset_UpperBodySyncro();
		LowerStateChange(LowerBodyState::Idle);
		return;
	}
}

void Marco::LowerForwardJump(float _DeltaTime)
{
	if (InAir)
	{
		if (UEngineInput::IsDown('A') ||
			UEngineInput::IsDown('a'))
		{
			std::string ChangeName = AddDirectionName(CurLowerBodyName);
			int PrevFrame = Renderer[static_cast<int>(BodyRenderer::LowerBody)]->GetCurAnimationFrame();
			float PrevTime = Renderer[static_cast<int>(BodyRenderer::LowerBody)]->GetCurAnimationTime();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(ChangeName, false, PrevFrame, PrevTime);
		}

		if (UEngineInput::IsDown('D') ||
			UEngineInput::IsDown('d'))
		{
			std::string ChangeName = AddDirectionName(CurLowerBodyName);
			int PrevFrame = Renderer[static_cast<int>(BodyRenderer::LowerBody)]->GetCurAnimationFrame();
			float PrevTime = Renderer[static_cast<int>(BodyRenderer::LowerBody)]->GetCurAnimationTime();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(ChangeName, false, PrevFrame, PrevTime);
		}
	}
	else
	{
		Move_Speed = Run_Speed;
		DirCheck(BodyRenderer::LowerBody, CurLowerBodyName);
		Reset_UpperBodySyncro();
		LowerStateChange(LowerBodyState::Idle);
		return;
	}
}

void Marco::LowerNoneStart()
{
	CurLowerBodyName = "None";
}

void Marco::LowerIdleStart()
{
	CurLowerBodyName = "LowerBody_Idle";
	LowerStart();
}

void Marco::LowerMoveStart()
{
	KnifeReach->SetScale(KnifeReachCollisionScale);
	if (DirState == EActorDir::Left)
	{
		KnifeReach->SetPosition(KnifeReachCollisionPosition_Left);
	}
	else
	{
		KnifeReach->SetPosition(KnifeReachCollisionPosition_Right);
	}

	CurLowerBodyName = "LowerBody_Move";
	LowerStart();
}

void Marco::LowerJumpStart()
{
	Move_Speed = Jump_Speed;
	Jumping_UpperBodySyncro();
	CurLowerBodyName = "LowerBody_Jump";
	LowerStart();
}

void Marco::LowerForwardJumpStart()
{
	Move_Speed = ForwardJump_Speed;
	ForwardJumping_UpperBodySyncro();
	CurLowerBodyName = "LowerBody_ForwardJump";
	LowerStart();
}

void Marco::LowerStart()
{
	std::string AddedDirectionName = AddDirectionName(CurLowerBodyName);
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(AddedDirectionName);
}

void Marco::AllSpawn(float _DeltaTime)
{
}

void Marco::AllNone(float _DeltaTime)
{
	if (!InAir && (true == UEngineInput::IsPress(VK_DOWN)))
	{
		AllStateChange(AllBodyState::Crouch_Intro);
		UpperStateChange(UpperBodyState::None);
		LowerStateChange(LowerBodyState::None);
		return;
	}
}
void Marco::AllCrouch_Intro(float _DeltaTime)
{
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		AllStateChange(AllBodyState::Crouch_Idle);
		return;
	}
}

void Marco::AllCrouch_Outro(float _DeltaTime)
{
	Reset_UpperBodySyncro();
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
		Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOn();
		Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOn();
		AllStateChange(AllBodyState::None);
		return;
	}
}

void Marco::AllCrouch_Idle(float _DeltaTime)
{
	std::string GunCheckedName = AddGunTypeName(CurAllBodyName);
	DirCheck(BodyRenderer::AllBody, GunCheckedName);
	if (true == UEngineInput::IsFree(VK_DOWN))
	{
		AllStateChange(AllBodyState::Crouch_Outro);
		return;
	}

	if (
		true == UEngineInput::IsPress(VK_RIGHT) &&
		true == UEngineInput::IsPress(VK_LEFT)
		)
	{
		return;
	}

	if (
		true == UEngineInput::IsPress(VK_RIGHT) ||
		true == UEngineInput::IsPress(VK_LEFT)
		)
	{
		AllStateChange(AllBodyState::Crouch_Move);
		return;
	}

	if (
		true == UEngineInput::IsDown('A') ||
		true == UEngineInput::IsDown('a')
		)
	{
		std::vector<UCollision*> Result;
		if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
			|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
		{
			int random = rand() % 2;
			if (random == 0)
			{
				AllStateChange(AllBodyState::Crouch_KnifeAttack1);
				return;
			}
			else
			{
				AllStateChange(AllBodyState::Crouch_KnifeAttack2);
				return;
			}
		}
		else
		{
			if (Gun == EGunList::HeavyMachineGun)
			{
				AllStateChange(AllBodyState::Crouch_Shoot_HeavyMachineGun);
				return;
			}
			else
			{
				AllStateChange(AllBodyState::Crouch_Shoot);
				return;
			}
		}
		
	}

	if (InAir)
	{
		AllStateChange(AllBodyState::Crouch_Outro);
		return;
	}

	if (
		true == UEngineInput::IsDown('D') ||
		true == UEngineInput::IsDown('d')
		)
	{
		AllStateChange(AllBodyState::Crouch_Throw);
		return;
	}
}

void Marco::AllCrouch_Move(float _DeltaTime)
{
	std::string GunCheckedName = AddGunTypeName(CurAllBodyName);
	DirCheck(BodyRenderer::AllBody, GunCheckedName);
	if (true == UEngineInput::IsFree(VK_DOWN))
	{
		AllStateChange(AllBodyState::Crouch_Outro);
		return;
	}

	if (InAir)
	{
		AllStateChange(AllBodyState::Crouch_Outro);
		return;
	}

	if (
		false == UEngineInput::IsPress(VK_RIGHT) &&
		false == UEngineInput::IsPress(VK_LEFT)
		)
	{
		AllStateChange(AllBodyState::Crouch_Idle);
		return;
	}

	if (
		true == UEngineInput::IsDown('A') ||
		true == UEngineInput::IsDown('a')
		)
	{
		std::vector<UCollision*> Result;
		if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
			|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
		{
			int random = rand() % 2;
			if (random == 0)
			{
				AllStateChange(AllBodyState::Crouch_KnifeAttack1);
				return;
			}
			else
			{
				AllStateChange(AllBodyState::Crouch_KnifeAttack2);
				return;
			}
		}
		else
		{
			if (Gun == EGunList::HeavyMachineGun)
			{
				AllStateChange(AllBodyState::Crouch_Shoot_HeavyMachineGun);
				return;
			}
			else
			{
				AllStateChange(AllBodyState::Crouch_Shoot);
				return;
			}
		}
	}

	if (
		true == UEngineInput::IsDown('D') ||
		true == UEngineInput::IsDown('d')
		)
	{
		AllStateChange(AllBodyState::Crouch_Throw);
		return;
	}
}

void Marco::AllCrouch_Shoot(float _DeltaTime)
{
	GunTypeShootCheck();
	*AccTime += _DeltaTime;
	if (*AccTime > *CoolTime)
	{
		if (true == UEngineInput::IsFree(VK_DOWN))
		{
			CrouchShooting = false;
			*AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Outro);
			return;
		}

		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			*AccTime = 0.0f;
			std::vector<UCollision*> Result;
			if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
				|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
			{
				int random = rand() % 2;
				if (random == 0)
				{
					AllStateChange(AllBodyState::Crouch_KnifeAttack1);
					return;
				}
				else
				{
					AllStateChange(AllBodyState::Crouch_KnifeAttack2);
					return;
				}
			}
			else
			{
				if (Gun == EGunList::HeavyMachineGun)
				{
					AllStateChange(AllBodyState::Crouch_Shoot_HeavyMachineGun);
					return;
				}
				else
				{
					AllStateChange(AllBodyState::Crouch_Shoot);
					return;
				}
			}
			return;
		}

		if (InAir)
		{
			CrouchShooting = false;
			*AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Outro);
			return;
		}

		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			CrouchShooting = false;
			*AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Throw);
			return;
		}
	}

	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		CrouchShooting = false;
		*AccTime = 0.0f;
		AllStateChange(AllBodyState::Crouch_Idle);
		return;
	}
}

void Marco::AllCrouch_HeavyMachineGun_Shoot(float _DeltaTime)
{
	GunTypeShootCheck();
	if (true == UEngineInput::IsFree(VK_DOWN))
	{
		CrouchShooting = false;
		HeavyMachineGun_PrevFrame = -1;
		AllStateChange(AllBodyState::Crouch_Outro);
		return;
	}

	if (InAir)
	{
		CrouchShooting = false;
		HeavyMachineGun_PrevFrame = -1;
		AllStateChange(AllBodyState::Crouch_Outro);
		return;
	}

	int CurFrame = Renderer[static_cast<int>(BodyRenderer::AllBody)]->GetCurAnimationFrame();
	if (CurFrame >= 3)
	{

		if (true == UEngineInput::IsPress('A') ||
			true == UEngineInput::IsPress('a'))
		{
			HeavyMachineGun_PrevFrame = -1;
			std::vector<UCollision*> Result;
			if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result)
				|| KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
			{
				int random = rand() % 2;
				if (random == 0)
				{
					AllStateChange(AllBodyState::Crouch_KnifeAttack1);
					return;
				}
				else
				{
					AllStateChange(AllBodyState::Crouch_KnifeAttack2);
					return;
				}
			}
			else
			{
				AllStateChange(AllBodyState::Crouch_Shoot_HeavyMachineGun);
				return;
			}
		}
	}
	if (CurFrame != HeavyMachineGun_PrevFrame)
	{
		FVector BulletSpawnLocation = Crouching_BulletSpawnOffset;
		FVector BulletDir = FVector::Zero;
		if (DirState == EActorDir::Right)
		{
			BulletSpawnLocation += BulletSpawnOffset_Right;
			int RandomInt = rand();
			FVector RandomVector = HeavyMachineGun_RightArr[RandomInt % 5];
			BulletDir = RandomVector;
		}
		else if (DirState == EActorDir::Left)
		{
			BulletSpawnLocation += BulletSpawnOffset_Left;
			int RandomInt = rand();
			FVector RandomVector = HeavyMachineGun_LeftArr[RandomInt % 5];
			BulletDir = RandomVector;
		}
		BulletDir.Normalize2D();

		ABullet* Bullet = GetWorld()->SpawnActor<AHeavyMachineGunBullet>(MT3RenderOrder::Projectile);
		--ArmsCount;
		FVector BulletLocation = GetActorLocation() + BulletSpawnLocation;
		Bullet->SetActorLocation(BulletLocation);
		Bullet->SetDir(BulletDir);

		HeavyMachineGun_PrevFrame = CurFrame;
	}

	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		HeavyMachineGun_PrevFrame = -1;
		CrouchShooting = false;
		AllStateChange(AllBodyState::Crouch_Idle);
		return;
	}

}

void Marco::AllCrouch_Throw(float _DeltaTime)
{
	Throw_AccTime += _DeltaTime;
	if (Throw_AccTime > Throw_CoolTime)
	{
		if (true == UEngineInput::IsFree(VK_DOWN))
		{
			CrouchShooting = false;
			Throw_AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Outro);
			return;
		}

		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			CrouchShooting = false;
			Throw_AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Shoot);
			return;
		}

		if (InAir)
		{
			CrouchShooting = false;
			Throw_AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Outro);
			return;
		}

		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			CrouchShooting = false;
			Throw_AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Throw);
			return;
		}
	}

	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		CrouchShooting = false;
		Throw_AccTime = 0.0f;
		AllStateChange(AllBodyState::Crouch_Idle);
		return;
	}
}

void Marco::AllCrouch_KnifeAttack1(float _DeltaTime)
{
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		CrouchShooting = false;
		AllStateChange(AllBodyState::Crouch_Idle);
		return;
	}
}

void Marco::AllCrouch_KnifeAttack2(float _DeltaTime)
{
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		CrouchShooting = false;
		AllStateChange(AllBodyState::Crouch_Idle);
		return;
	}
}

void Marco::AllCeremony(float _DeltaTime)
{
}

void Marco::AllDeath(float _DeltaTime)
{
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		--UContentsHelper::Life;
		Destroy();
	}
}

void Marco::AllDeathInAir(float _DeltaTime)
{
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		--UContentsHelper::Life;
		Destroy();
	}
}

void Marco::AllDeathByKnife(float _DeltaTime)
{
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		--UContentsHelper::Life;
		Destroy();
	}
}

void Marco::AllSpawnStart()
{
	CurAllBodyName = "AllBody_Spawn";
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(CurAllBodyName);
}

void Marco::AllNoneStart()
{
	CurAllBodyName = "None";
}

void Marco::AllCrouch_IntroStart()
{
	Move_Speed = Crouch_Speed;
	IsCrouching = true;
	Collision->SetScale(CrouchCollisionScale);
	Collision->SetPosition(CrouchCollisionPosition);
	KnifeReach->SetScale(CrouchKnifeReachCollisionScale);
	if (DirState == EActorDir::Left)
	{
		KnifeReach->SetPosition(CrouchKnifeReachCollisionPosition_Left);
	}
	else
	{
		KnifeReach->SetPosition(CrouchKnifeReachCollisionPosition_Right);
	}
	CurAllBodyName = "AllBody_Crouch_Intro";
	AllStart();
}

void Marco::AllCrouch_OutroStart()
{
	Move_Speed = Run_Speed;
	IsCrouching = false;
	Collision->SetScale(DefaultCollisionScale);
	Collision->SetPosition(DefaultCollisionPosition);
	KnifeReach->SetScale(KnifeReachCollisionScale);
	if (DirState == EActorDir::Left)
	{
		KnifeReach->SetPosition(KnifeReachCollisionPosition_Left);
	}
	else
	{
		KnifeReach->SetPosition(KnifeReachCollisionPosition_Right);
	}
	CurAllBodyName = "AllBody_Crouch_Outro";
	AllStart();
}

void Marco::AllCrouch_IdleStart()
{
	CurAllBodyName = "AllBody_Crouch_Idle";
	AllStart();
	std::string GunCheckedName = AddGunTypeName(CurAllBodyName);
	DirCheck(BodyRenderer::AllBody, GunCheckedName);
}

void Marco::AllCrouch_MoveStart()
{
	CurAllBodyName = "AllBody_Crouch_Move";
	AllStart();
	std::string GunCheckedName = AddGunTypeName(CurAllBodyName);
	DirCheck(BodyRenderer::AllBody, GunCheckedName);
}

void Marco::AllCrouch_ShootStart()
{
	CrouchShooting = true;
	CurAllBodyName = "AllBody_Crouch_Shoot";
	AllStart();

	FVector BulletSpawnLocation = Crouching_BulletSpawnOffset;
	FVector BulletDir = FVector::Zero;
	if (DirState == EActorDir::Right)
	{
		BulletSpawnLocation += BulletSpawnOffset_Right;
		BulletDir = FVector::Right;
	}
	else if (DirState == EActorDir::Left)
	{
		BulletSpawnLocation += BulletSpawnOffset_Left;
		BulletDir = FVector::Left;
	}

	BulletSpawn(BulletSpawnLocation, BulletDir);
}

void Marco::AllCrouch_HeavyMachineGun_ShootStart()
{
	CrouchShooting = true;
	CurAllBodyName = "AllBody_Crouch_Shoot";
	std::string AddedGunTypeName = AddGunTypeName(CurAllBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string DirectedName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(DirectedName, true, 0, 0.1f);
	UEngineSound::SoundPlay("HeavyMachineGun_Launch.mp3");
}

void Marco::AllCrouch_ThrowStart()
{
	CrouchShooting = true;
	CurAllBodyName = "AllBody_Crouch_Throw";
	AllStart();

	if (BombsCount > 0 && RemainBomb > 0)
	{
		ABomb* Bomb = GetWorld()->SpawnActor<ABomb>();
		--BombsCount;
		FVector ThrowVector = { 3,-3 };
		ThrowVector.Normalize2D();
		float ThrowForce = 400.0f;
		ThrowVector *= ThrowForce;
		FVector SpawnLocation = GetActorLocation();

		if (DirState == EActorDir::Left)
		{
			SpawnLocation += {-30.0f, -50.0f};
			ThrowVector.X = -ThrowVector.X;
		}
		else if (DirState == EActorDir::Right)
		{
			SpawnLocation += {30.0f, -50.0f};
		}

		Bomb->SetActorLocation(SpawnLocation);
		Bomb->SetMoveVector(ThrowVector);
	}
}

void Marco::AllCrouch_KnifeAttack1Start()
{
	UContentsHelper::Score += 100;
	UEngineSound::SoundPlay("KnifeAttack1.mp3");
	std::vector<UCollision*> Result;
	if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result))
	{
		for (UCollision* EnemyCol : Result)
		{
			AEnemy* Enemy = dynamic_cast<AEnemy*>(EnemyCol->GetOwner());
			Enemy->Damaged(KnifeDamage);
		}
	}

	if (KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
	{
		APOWs* Pow = dynamic_cast<APOWs*>(Result[0]->GetOwner());
		Pow->StateChange(POWsState::Liberate);
	}
	CrouchShooting = true;
	CurAllBodyName = "AllBody_Crouch_KnifeAttack1";
	AllStart();
}

void Marco::AllCrouch_KnifeAttack2Start()
{
	UContentsHelper::Score += 100;
	UEngineSound::SoundPlay("KnifeAttack2.mp3");
	std::vector<UCollision*> Result;
	if (KnifeReach->CollisionCheck(MT3CollisionOrder::Enemy, Result))
	{
		for (UCollision* EnemyCol : Result)
		{
			AEnemy* Enemy = dynamic_cast<AEnemy*>(EnemyCol->GetOwner());
			Enemy->Damaged(KnifeDamage);
		}
	}
	if (KnifeReach->CollisionCheck(MT3CollisionOrder::TiedNPC, Result))
	{
		APOWs* Pow = dynamic_cast<APOWs*>(Result[0]->GetOwner());
		Pow->StateChange(POWsState::Liberate);
	}
	CrouchShooting = true;
	CurAllBodyName = "AllBody_Crouch_KnifeAttack2";
	AllStart();
}

void Marco::AllCeremonyStart()
{
	CurAllBodyName = "AllBody_Ceremony";
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(AddGunTypeName(CurAllBodyName));
}

void Marco::AllDeathStart()
{
	UEngineSound::SoundPlay("Marco_Death.mp3");
	//AddForce
	ManipulateOff();
	NoHit = true;
	CurAllBodyName = "AllBody_Death";
	std::string DirectedName = AddDirectionName(CurAllBodyName);
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(DirectedName);
	DirCheck(BodyRenderer::AllBody, CurAllBodyName);
}

void Marco::AllDeathInAirStart()
{
	UEngineSound::SoundPlay("Marco_Death.mp3");
	//AddForce
	ManipulateOff();
	NoHit = true;
	CurAllBodyName = "AllBody_DeathInAir";
	std::string DirectedName = AddDirectionName(CurAllBodyName);
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(DirectedName);
	DirCheck(BodyRenderer::AllBody, CurAllBodyName);
}

void Marco::AllDeathByKnifeStart()
{
	UEngineSound::SoundPlay("Marco_Death");
	ManipulateOff();
	NoHit = true;
	CurAllBodyName = "AllBody_DeathByKnife";
	std::string DirectedName = AddDirectionName(CurAllBodyName);
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(DirectedName);
	DirCheck(BodyRenderer::AllBody, CurAllBodyName);
}

void Marco::AllStart()
{
	std::string AddedGunTypeName = AddGunTypeName(CurAllBodyName);
	std::string DirectedName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(DirectedName, true);
}

void Marco::Zombie_AllTransformToZombie_Intro(float _DeltaTime)
{
	NoHit = true;
	if (!InAir)
	{
		AllStateChange(AllBodyState::TransformToZombie_Falling);
		return;
	}
}

void Marco::Zombie_AllTransformToZombie_Falling(float _DeltaTime)
{
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		AllStateChange(AllBodyState::TransformToZombie_Rising);
		return;
	}
}

void Marco::Zombie_AllTransformToZombie_Rising(float _DeltaTime)
{
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		ManipulateOn();
		Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOn();
		GunType = EGunType::Pistol;
		Gun = EGunList::Pistol;
		AllStateChange(AllBodyState::Zombie_Idle);
		NoHit = false;
		return;
	}
}

void Marco::Zombie_AllIdle(float _DeltaTime)
{
	if (
		true == UEngineInput::IsPress(VK_RIGHT) &&
		true == UEngineInput::IsPress(VK_LEFT)
		)
	{
		return;
	}
	if (
		true == UEngineInput::IsPress(VK_RIGHT) &&
		(EActorDir::Left == DirState && true == UEngineInput::IsPress(VK_UP))
		)
	{
		AllStateChange(AllBodyState::Zombie_AimupTurn);
		return;
	}

	if (
		true == UEngineInput::IsPress(VK_LEFT) &&
		(EActorDir::Right == DirState && true == UEngineInput::IsPress(VK_UP))
		)
	{
		AllStateChange(AllBodyState::Zombie_AimupTurn);
		return;
	}

	if (
		true == UEngineInput::IsPress(VK_RIGHT) &&
		(EActorDir::Left == DirState)
		)
	{
		AllStateChange(AllBodyState::Zombie_Turn);
		return;
	}

	if (
		true == UEngineInput::IsPress(VK_LEFT) &&
		(EActorDir::Right == DirState)
		)
	{
		AllStateChange(AllBodyState::Zombie_Turn);
		return;
	}

	DirCheck(BodyRenderer::AllBody, CurAllBodyName);



	if (
		true == UEngineInput::IsDown('D') ||
		true == UEngineInput::IsDown('D')
		)
	{
		AllStateChange(AllBodyState::Zombie_Vomit);
		return;
	}

	if (
		true == UEngineInput::IsPress(VK_RIGHT) ||
		true == UEngineInput::IsPress(VK_LEFT)
		)
	{
		AllStateChange(AllBodyState::Zombie_Move);
		return;
	}

}

void Marco::Zombie_AllMove(float _DeltaTime)
{
	DirCheck(BodyRenderer::AllBody, CurAllBodyName);
	if (
		true == UEngineInput::IsPress(VK_RIGHT) &&
		true == UEngineInput::IsPress(VK_LEFT)
		)
	{
		AllStateChange(AllBodyState::Zombie_Idle);
		return;
	}

	if (
		true == UEngineInput::IsFree(VK_RIGHT) &&
		true == UEngineInput::IsFree(VK_LEFT)
		)
	{
		AllStateChange(AllBodyState::Zombie_Idle);
		return;
	}

	if (
		true == UEngineInput::IsDown('D') ||
		true == UEngineInput::IsDown('D')
		)
	{
		AllStateChange(AllBodyState::Zombie_Vomit);
		return;
	}
}

void Marco::Zombie_AllTurn(float _DeltaTime)
{
	ManipulateOff();
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		ManipulateOn();
		Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOn();
		DirCheck(BodyRenderer::AllBody, CurAllBodyName);
		AllStateChange(AllBodyState::Zombie_Idle);
		return;
	}
}

void Marco::Zombie_AllAimupTurn(float _DeltaTime)
{
	ManipulateOff();
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		ManipulateOn();
		Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOn();
		DirCheck(BodyRenderer::AllBody, CurAllBodyName);
		AllStateChange(AllBodyState::Zombie_Idle);
		return;
	}
}

void Marco::Zombie_AllJump(float _DeltaTime)
{
	int CurFrame = Renderer[static_cast<int>(BodyRenderer::AllBody)]->GetCurAnimationFrame();
	
	if (CurFrame == 7 && Jump_PrevFrame != CurFrame)
	{
		AddActorLocation(FVector::Up * 20);
		JumpVector = ZombieJumpPower;

		Jump_PrevFrame = CurFrame;
		ManipulateOn();
	}
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		Jump_PrevFrame = -1;
		AllStateChange(AllBodyState::Zombie_Idle);
		return;
	}
}

void Marco::Zombie_AllVomit(float _DeltaTime)
{
	ManipulateOff();
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
	int CurFrame = Renderer[static_cast<int>(BodyRenderer::AllBody)]->GetCurAnimationFrame();
	int LaunchFrame = 21;

	if (Vomit_PrevFrame != CurFrame && CurFrame == LaunchFrame)
	{
		AVomitLauncher* VomitLauncher = GetWorld()->SpawnActor<AVomitLauncher>();
		FVector Offset = { 0,-100 };
		if (DirState == EActorDir::Right)
		{
			Offset.X = 30;
		}
		else if(DirState == EActorDir::Left)
		{
			Offset.X = -100;
		}


		VomitLauncher->SetActorLocation(GetActorLocation() + Offset);
		Vomit_PrevFrame = CurFrame;
	}
	
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		Vomit_PrevFrame = -1;
		ManipulateOn();
		Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOn();
		AllStateChange(AllBodyState::Zombie_Idle);
	}
}

void Marco::Zombie_AllDeath(float _DeltaTime)
{
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		--UContentsHelper::Life;
		Destroy();
	}
}

void Marco::Zombie_AllDeathInAir(float _DeltaTime)
{
	if (Renderer[static_cast<int>(BodyRenderer::AllBody)]->IsCurAnimationEnd())
	{
		--UContentsHelper::Life;
		Destroy();
	}
}

void Marco::Zombie_AllTransformToZombie_IntroStart()
{
	ManipulateOff();
	CurAllBodyName = "Zombie_AllBody_TransformToZombie_Intro";
	ZombieStart();
}

void Marco::Zombie_AllTransformToZombie_FallingStart()
{
	CurAllBodyName = "Zombie_AllBody_TransformToZombie_Falling";
	ZombieStart();
}

void Marco::Zombie_AllTransformToZombie_RisingStart()
{
	CurAllBodyName = "Zombie_AllBody_TransformToZombie_Rising";
	ZombieThunder* Effect = GetWorld()->SpawnActor<ZombieThunder>();
	Effect->SetActorLocation(GetActorLocation());
	ZombieStart();
}

void Marco::Zombie_AllIdleStart()
{
	ManipulateOn();
	Move_Speed = Zombie_Speed;
	CurAllBodyName = "Zombie_AllBody_Idle";
	ZombieStart();
}

void Marco::Zombie_AllMoveStart()
{
	CurAllBodyName = "Zombie_AllBody_Move";
	ZombieStart();
}

void Marco::Zombie_AllTurnStart()
{
	CurAllBodyName = "Zombie_AllBody_Turn";
	ZombieStart();
}

void Marco::Zombie_AllAimupTurnStart()
{
	CurAllBodyName = "Zombie_AllBody_AimUpTurn";
	ZombieStart();
}

void Marco::Zombie_AllJumpStart()
{
	CurAllBodyName = "Zombie_AllBody_Jump";
	ManipulateOff();
	ZombieStart();
}

void Marco::Zombie_AllVomitStart()
{
	CurAllBodyName = "Zombie_AllBody_Vomit";
	BombsCount--;
	ZombieStart();
}

void Marco::Zombie_AllDeathStart()
{
	UEngineSound::SoundPlay("Zombie_Marco_Death.mp3");
	ManipulateOff();
	CurAllBodyName = "Zombie_AllBody_Death";
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
	ZombieStart();
}

void Marco::Zombie_AllDeathInAirStart()
{
	UEngineSound::SoundPlay("Zombie_Marco_Death.mp3");
	ManipulateOff();
	CurAllBodyName = "Zombie_AllBody_DeathInAir";
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
	ZombieStart();
}

void Marco::ZombieStart()
{
	std::string DirectedName = AddDirectionName(CurAllBodyName);
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(DirectedName);
}

void Marco::ZombieArm_None(float _DeltaTime)
{
	ZombieArmStateChange(ZombieArmState::Idle);
	return;
}

void Marco::ZombieArm_Idle(float _DeltaTime)
{
	if (InAir)
	{
		ZombieArmStateChange(ZombieArmState::Jump);
		return;
	}
	DirCheck(BodyRenderer::ZombieArm, CurZArmName);
	if (
		true == UEngineInput::IsPress(VK_LEFT) &&
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		return;
	}
	if (
		true == UEngineInput::IsPress(VK_LEFT) ||
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		ZombieArmStateChange(ZombieArmState::Move);
		return;
	}

	if (true == UEngineInput::IsPress(VK_UP))
	{
		ZombieArmStateChange(ZombieArmState::AimNormalToUp);
		return;
	}

	if (true == UEngineInput::IsDown('A') ||
		true == UEngineInput::IsDown('a'))
	{
		ZombieArmStateChange(ZombieArmState::Shoot);
		return;
	}
}

void Marco::ZombieArm_Idle_AimUp(float _DeltaTime)
{
	if (InAir)
	{
		ZombieArmStateChange(ZombieArmState::Jump_AimUp);
		return;
	}

	DirCheck(BodyRenderer::ZombieArm, CurZArmName);
	if (
		true == UEngineInput::IsPress(VK_LEFT) &&
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		return;
	}
	if (true == UEngineInput::IsFree(VK_UP))
	{
		ZombieArmStateChange(ZombieArmState::AimUpToNormal);
		return;
	}
	if (
		true == UEngineInput::IsPress(VK_LEFT) ||
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		ZombieArmStateChange(ZombieArmState::Move_AimUp);
		return;
	}


	if (true == UEngineInput::IsDown('A') ||
		true == UEngineInput::IsDown('a'))
	{
		ZombieArmStateChange(ZombieArmState::Shoot_AimUp);
		return;
	}
}

void Marco::ZombieArm_Move(float _DeltaTime)
{
	if (InAir)
	{
		ZombieArmStateChange(ZombieArmState::Jump);
		return;
	}

	DirCheck(BodyRenderer::ZombieArm, CurZArmName);
	if (
		true == UEngineInput::IsPress(VK_LEFT) &&
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		ZombieArmStateChange(ZombieArmState::Idle);
		return;
	}
	if (
		true == UEngineInput::IsFree(VK_LEFT) &&
		true == UEngineInput::IsFree(VK_RIGHT)
		)
	{
		ZombieArmStateChange(ZombieArmState::Idle);
		return;
	}
	if (true == UEngineInput::IsPress(VK_UP))
	{
		ZombieArmStateChange(ZombieArmState::AimNormalToUp);
		return;
	}
	if (true == UEngineInput::IsDown('A') ||
		true == UEngineInput::IsDown('a'))
	{
		ZombieArmStateChange(ZombieArmState::Shoot);
		return;
	}
}

void Marco::ZombieArm_Move_AimUp(float _DeltaTime)
{
	if (InAir)
	{
		ZombieArmStateChange(ZombieArmState::Jump_AimUp);
		return;
	}

	DirCheck(BodyRenderer::ZombieArm, CurZArmName);
	if (
		true == UEngineInput::IsPress(VK_LEFT) &&
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		ZombieArmStateChange(ZombieArmState::Idle_AimUp);
		return;
	}
	if (
		true == UEngineInput::IsFree(VK_LEFT) &&
		true == UEngineInput::IsFree(VK_RIGHT)
		)
	{
		ZombieArmStateChange(ZombieArmState::Idle_AimUp);
		return;
	}
	if (true == UEngineInput::IsFree(VK_UP))
	{
		ZombieArmStateChange(ZombieArmState::AimUpToNormal);
		return;
	}
	if (true == UEngineInput::IsDown('A') ||
		true == UEngineInput::IsDown('a'))
	{
		ZombieArmStateChange(ZombieArmState::Shoot_AimUp);
		return;
	}
}

void Marco::ZombieArm_Jump(float _DeltaTime)
{
	if (!InAir)
	{
		ZombieArmStateChange(ZombieArmState::Idle);
		return;
	}

	if (true == UEngineInput::IsPress(VK_UP))
	{
		ZombieArmStateChange(ZombieArmState::AimNormalToUp);
		return;
	}

	if (true == UEngineInput::IsDown('A') ||
		true == UEngineInput::IsDown('a'))
	{
		ZombieArmStateChange(ZombieArmState::Shoot);
		return;
	}
}

void Marco::ZombieArm_Jump_AimUp(float _DeltaTime)
{
	if (!InAir)
	{
		ZombieArmStateChange(ZombieArmState::Idle_AimUp);
		return;
	}

	if (true == UEngineInput::IsFree(VK_UP))
	{
		
		(ZombieArmState::AimUpToNormal);
		return;
	}

	if (true == UEngineInput::IsDown('A') ||
		true == UEngineInput::IsDown('a'))
	{
		ZombieArmStateChange(ZombieArmState::Shoot_AimUp);
		return;
	}
}

void Marco::ZombieArm_Shoot(float _DeltaTime)
{
	GunTypeShootCheck();
	*AccTime += _DeltaTime;
	if (!InAir)
	{
		DirCheck(BodyRenderer::ZombieArm, CurZArmName);
	}

	if (*AccTime > *CoolTime)
	{
		if(true == UEngineInput::IsPress(VK_UP))
		{
			*AccTime = 0.0f;
			ZombieArmStateChange(ZombieArmState::AimNormalToUp);
			return;
		}
		if(true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a'))
		{
			*AccTime = 0.0f;
			ZombieArmStateChange(ZombieArmState::Shoot);
			return;
		}
		if (InAir)
		{
			*AccTime = 0.0f;
			ZombieArmStateChange(ZombieArmState::Jump);
			return;
		}

	}
	if (Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->IsCurAnimationEnd())
	{
		*AccTime = 0.0f;
		ZombieArmStateChange(ZombieArmState::Idle);
		return;
	}
}

void Marco::ZombieArm_Shoot_AimUp(float _DeltaTime)
{
	GunTypeShootCheck();
	*AccTime += _DeltaTime;
	if (!InAir)
	{
		DirCheck(BodyRenderer::ZombieArm, CurZArmName);
	}
	if (*AccTime > *CoolTime)
	{
		if (true == UEngineInput::IsFree(VK_UP))
		{
			*AccTime = 0.0f;
			ZombieArmStateChange(ZombieArmState::AimUpToNormal);
			return;
		}
		if (true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a'))
		{
			*AccTime = 0.0f;
			ZombieArmStateChange(ZombieArmState::Shoot_AimUp);
			return;
		}
		if (true == UEngineInput::IsPress('S') ||
			true == UEngineInput::IsPress('s'))
		{
			*AccTime = 0.0f;
			ZombieArmStateChange(ZombieArmState::Jump_AimUp);
			return;
		}

	}
	if (Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->IsCurAnimationEnd())
	{
		*AccTime = 0.0f;
		ZombieArmStateChange(ZombieArmState::Idle_AimUp);
		return;
	}
}

void Marco::ZombieArm_AimNormalToUp(float _DeltaTime)
{
	if(Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->IsCurAnimationEnd())
	{
		ZombieArmStateChange(ZombieArmState::Idle_AimUp);
		return;
	}
}

void Marco::ZombieArm_AimUpToNormal(float _DeltaTime)
{
	if (Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->IsCurAnimationEnd())
	{
		ZombieArmStateChange(ZombieArmState::Idle);
		return;
	}
}

void Marco::ZombieArm_NoneStart()
{
	CurZArmName = "ZombieArm_None";
}

void Marco::ZombieArm_IdleStart()
{
	CurZArmName = "ZombieArm_Idle";
	ZombieArmStart();
}

void Marco::ZombieArm_Idle_AimUpStart()
{
	CurZArmName = "ZombieArm_Idle_AimUp";
	ZombieArmStart();
}

void Marco::ZombieArm_MoveStart()
{
	CurZArmName = "ZombieArm_Move";
	ZombieArmStart();
}

void Marco::ZombieArm_Move_AimUpStart()
{
	CurZArmName = "ZombieArm_Move_AimUp";
	ZombieArmStart();
}

void Marco::ZombieArm_JumpStart()
{
	CurZArmName = "ZombieArm_Jump";
	ZombieArmStart();
}

void Marco::ZombieArm_Jump_AimUpStart()
{
	CurZArmName = "ZombieArm_Jump_AimUp";
	ZombieArmStart();
}

void Marco::ZombieArm_ShootStart()
{
	if (!Manipulate) return;

	CurZArmName = "ZombieArm_Shoot";
	std::string DirectedName = AddDirectionName(CurZArmName);
	ZombieArm_Syncro();
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ChangeAnimation(DirectedName, true);

	FVector BulletSpawnLocation = MarcoUpperBodyOffset + Standing_BulletSpawnOffset;
	FVector BulletDir = FVector::Zero;
	if (DirState == EActorDir::Right)
	{
		BulletSpawnLocation += BulletSpawnOffset_Right;
		BulletDir = FVector::Right;
	}
	else if (DirState == EActorDir::Left)
	{
		BulletSpawnLocation += BulletSpawnOffset_Left;
		BulletDir = FVector::Left;
	}

	ABullet* Bullet = GetWorld()->SpawnActor<APistolBullet>(MT3RenderOrder::Projectile);
	FVector BulletLocation = GetActorLocation() + BulletSpawnLocation;
	Bullet->SetActorLocation(BulletLocation);
	Bullet->SetDir(BulletDir);
}

void Marco::ZombieArm_Shoot_AimUpStart()
{
	if (!Manipulate) return;

	CurZArmName = "ZombieArm_Shoot_AimUp";
	std::string DirectedName = AddDirectionName(CurZArmName);
	ZombieArm_Syncro();
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ChangeAnimation(DirectedName, true);

	FVector BulletSpawnLocation = FVector::Zero;
	FVector BulletDir = FVector::Zero;
	if (DirState == EActorDir::Right)
	{
		BulletSpawnLocation = MarcoUpperBodyOffset + AimUp_BulletSpawnOffset_Right;
	}
	else if (DirState == EActorDir::Left)
	{
		BulletSpawnLocation = MarcoUpperBodyOffset + AimUp_BulletSpawnOffset_Left;
	}

	BulletDir = FVector::Up;

	ABullet* Bullet = GetWorld()->SpawnActor<APistolBullet>(MT3RenderOrder::Projectile);
	FVector BulletLocation = GetActorLocation() + BulletSpawnLocation;
	Bullet->SetActorLocation(BulletLocation);
	Bullet->SetDir(BulletDir);
}

void Marco::ZombieArm_AimNormalToUpStart()
{
	CurZArmName = "ZombieArm_AimNormalToUp";
	std::string DirectedName = AddDirectionName(CurZArmName);
	ZombieArm_Syncro();
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ChangeAnimation(DirectedName, false);
}

void Marco::ZombieArm_AimUpToNormalStart()
{
	CurZArmName = "ZombieArm_AimUpToNormal";
	std::string DirectedName = AddDirectionName(CurZArmName);
	ZombieArm_Syncro();
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ChangeAnimation(DirectedName, false);
}

void Marco::ZombieArmStart()
{
	std::string DirectedName = AddDirectionName(CurZArmName);
	ZombieArm_Syncro();
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ChangeAnimation(DirectedName);
}

void Marco::Jumping_UpperBodySyncro()
{
	MarcoUpperBodyOffset = MarcoDefaultUpperBodyOffset + Juming_UpperBodyOffset;
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransform({ MarcoUpperBodyOffset, MarcoSize });
}
void Marco::ForwardJumping_UpperBodySyncro()
{
	MarcoUpperBodyOffset = MarcoDefaultUpperBodyOffset + ForwardJumping_UpperBodyOffset;
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransform({ MarcoUpperBodyOffset, MarcoSize });
}
void Marco::Reset_UpperBodySyncro()
{
	MarcoUpperBodyOffset = MarcoDefaultUpperBodyOffset;
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransform({ MarcoUpperBodyOffset, MarcoSize });
}

void Marco::ZombieArm_Syncro()
{
	if (DirState == EActorDir::Left)
	{
		Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetTransform({ ZombieArm_Offset_Left, MarcoSize });
	}
	else if (DirState == EActorDir::Right)
	{
		Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetTransform({ ZombieArm_Offset_Right, MarcoSize });
	}
}

void Marco::CalGravityVector(float _DeltaTime)
{
	GravityVector += Gravity * _DeltaTime;
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	Color8Bit CrouchColor = UContentsHelper::CrouchColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	GroundCheckCol->SetPosition({ 0,0 });
	std::vector<UCollision*> Result;
	if (Color == Color8Bit(255, 0, 255, 0) && !IsCrouching)
	{
		GravityVector = FVector::Zero;
	}
	else if (CrouchColor == Color8Bit(255, 255, 0, 0) && IsCrouching)
	{
		GravityVector = FVector::Zero;
	}
	else if (GroundCheckCol->CollisionCheck(MT3CollisionOrder::Monoliths, Result))
	{
		GravityVector = FVector::Zero;
	}
}

void Marco::GroundUp()
{
	while (true)
	{
		Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY()-3, Color8Bit::MagentaA);
		Color8Bit CrouchColor = UContentsHelper::CrouchColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 3, Color8Bit::MagentaA);
		GroundCheckCol->SetPosition({ 0,-3 });
		std::vector<UCollision*> Result;
		if (Color == Color8Bit(255, 0, 255, 0) && !IsCrouching )
		{
			AddActorLocation(FVector::Up);
		}
		else if (CrouchColor == Color8Bit(255, 255, 0, 0) && IsCrouching)
		{
			AddActorLocation(FVector::Up);
		}
		else if (GroundCheckCol->CollisionCheck(MT3CollisionOrder::Monoliths, Result))
		{
			AddActorLocation(FVector::Up);
		}
		else
		{
			break;
		}
	}
}

void Marco::BulletSpawn(FVector _SpawnLocation, FVector _BulletDir)
{
	ABullet* Bullet = nullptr;
	switch (Gun)
	{
	case EGunList::Pistol:
		Bullet = GetWorld()->SpawnActor<APistolBullet>(MT3RenderOrder::Projectile);
		UEngineSound::SoundPlay("Pistol_Launch.mp3");
		break;
	case EGunList::FlameShot:
		Bullet = GetWorld()->SpawnActor<AFlameShotBullet>(MT3RenderOrder::Projectile);
		UEngineSound::SoundPlay("FlameShot_Launch.mp3");
		break;
	case EGunList::RocketLauncher:
		Bullet = GetWorld()->SpawnActor<RocketLauncherBullet>();
		UEngineSound::SoundPlay("RocketLauncher_Launch.mp3");
		break;
	default:
		break;
	}

	FVector BulletLocation = GetActorLocation() + _SpawnLocation;
	Bullet->SetActorLocation(BulletLocation);
	Bullet->SetDir(_BulletDir);

	--ArmsCount;
}

void Marco::ZombieToHuman()
{
	IsZombie = false;
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOn();
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOn();
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
	UpperStateChange(UpperBodyState::None);
	LowerStateChange(LowerBodyState::None);
	AllStateChange(AllBodyState::None);
	Move_Speed = Run_Speed;
}

void Marco::CameraUpdate(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (Collision->CollisionCheck(MT3CollisionOrder::CameraSwitch, Result))
	{
		AActor* Switch = Result[0]->GetOwner();
		Switch->Destroy();

		++UContentsHelper::CameraManager->CameraMode;
	}
}

void Marco::AutoMove(float _DeltaTime)
{
	float TargetX = 13900.f;

	if (IsZombie)
	{
		if (GetActorLocation().X > TargetX)
		{
			DirState = EActorDir::Left;
			AddActorLocation(FVector::Left * Zombie_Speed * _DeltaTime);
			Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
			Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOn();

			std::string AllAnimName = "Zombie_AllBody_Move_Left";
			std::string ZArmAnimName = "ZombieArm_Move_Left";
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(AllAnimName);
			Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ChangeAnimation(ZArmAnimName);
		}
		else
		{
			DirState = EActorDir::Right;
			Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
			Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOn();

			std::string AllAnimName = "Zombie_AllBody_Idle_Right";
			std::string ZArmAnimName = "ZombieArm_Idle_Right";
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(AllAnimName);
			Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ChangeAnimation(ZArmAnimName);
		}

		return;
	}

	std::string GunName = "None";
	switch (GunType)
	{
	case EGunType::Pistol:
		GunName = "Pistol_";
		break;
	case EGunType::Rifle:
		GunName = "Rifle_";
		break;
	}

	if (GetActorLocation().X > TargetX)
	{
		DirState = EActorDir::Left;
		AddActorLocation(FVector::Left * Run_Speed * _DeltaTime);
		Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOn();
		Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOn();
		Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
		Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
		
		std::string UpperAnimName = GunName + "UpperBody_Move_Left";
		std::string LowerAnimName = "LowerBody_Move_Left";
		Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(UpperAnimName);
		Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(LowerAnimName);
	}
	else
	{
		DirState = EActorDir::Right;
		Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOn();
		Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOn();
		Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
		Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();

		std::string UpperAnimName = GunName + "UpperBody_Idle_Right";
		std::string LowerAnimName = "LowerBody_Idle_Right";
		Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(UpperAnimName);
		Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(LowerAnimName);
	}
}

bool Marco::OutOfControl(float _DeltaTime)
{
	if (UContentsHelper::GameEnd)
	{
		InAirCheck(_DeltaTime);
		GravityCheck(_DeltaTime);
		GroundUp();

		std::string GunName = "None";

		switch (GunType)
		{
		case EGunType::Pistol:
			GunName = "Pistol_";
			break;
		case EGunType::Rifle:
			GunName = "Rifle_";
			break;
		}

		Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
		Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOff();
		Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
		Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();

		std::string UpperAnimName = GunName + "AllBody_Ceremony";

		Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(UpperAnimName, false, 0, 0.08f);
		return true;
	}

	if (IsAutoMove)
	{
		AutoMove(_DeltaTime);
		return true;
	}

	return false;
}

void Marco::ArmsCheck()
{
	if (ArmsCount < 0)
	{
		ArmsCount = 0;
	}

	if (ArmsCount == 0)
	{
		Gun = EGunList::Pistol;
		GunType = EGunType::Pistol;
	}
}
