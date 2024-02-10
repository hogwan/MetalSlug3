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
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransform({ MarcoUpperBodyPosition, MarcoSize });
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetImage("Marco_LowerBody.png");
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetTransform({ {0,0}, MarcoSize });
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetImage("Marco_AllBody.png");
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetTransform({ {0,0}, MarcoSize });
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetImage("Marco_UpperBody.png");
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetTransform({ {150,0}, MarcoSize });
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->SetImage("Marco_UpperBody.png");
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->SetTransform({ {150,-75}, MarcoSize });
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->SetTransColor({ 0,0,0,255 });

	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->SetImage("Marco_UpperBody.png");
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->SetTransform({ {150,-225}, MarcoSize });
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->SetTransColor({ 0,0,0,255 });

	CreateMarcoAnimation;

	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation("Pistol_UpperBody_Idle_Right");
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation("LowerBody_Idle_Right");

	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->ActiveOff();

	SetActorLocation({ 50, 450 });
	UpperStateChange(UpperBodyState::Idle);
	LowerStateChange(LowerBodyState::Idle);
	AllStateChange(AllBodyState::None);
}


void Marco::Tick(float _DeltaTime)
{
	GetWorld()->SetCameraPos({ GetActorLocation().X - 400.0f, 0.0f });
	InAirCheck();
	UpperStateUpdate(_DeltaTime);
	LowerStateUpdate(_DeltaTime);
	AllBodyStateUpdate(_DeltaTime);
}

void Marco::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		FallSpeed += Gravity * _DeltaTime;
		AddActorLocation(FVector::Down * _DeltaTime * FallSpeed);
	}
	else
	{
		FallSpeed = 0.0f;
	}
}

void Marco::InAirCheck()
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		InAir = false;
	}
	else InAir = true;
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
		int PrevFrame = Renderer[static_cast<int>(_BodyRendererType)]->CurAnimation->CurFrame;
		Renderer[static_cast<int>(_BodyRendererType)]->ChangeAnimation(ChangeName);
		Renderer[static_cast<int>(_BodyRendererType)]->CurAnimation->CurFrame = PrevFrame; // 이거 꼭 만들어달라해야함
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
		EndTime = &Pistol_Shoot_EndTime;
		break;
	case EGunList::HeavyMachineGun:
		AccTime = &HeavyMachineGun_Shoot_AccTime;
		CoolTime = &HeavyMachineGun_Shoot_CoolTime;
		EndTime = &HeavyMachineGun_Shoot_EndTime;
		break;
	case EGunList::FlameShot:
		AccTime = &FlameShot_Shoot_AccTime;
		CoolTime = &FlameShot_Shoot_CoolTime;
		EndTime = &FlameShot_Shoot_EndTime;
		break;
	case EGunList::ShotGun:
		AccTime = &ShotGun_Shoot_AccTime;
		CoolTime = &ShotGun_Shoot_CoolTime;
		EndTime = &ShotGun_Shoot_EndTime;
		break;
	case EGunList::RocketLauncher:
		AccTime = &RocketLauncher_Shoot_AccTime;
		CoolTime = &RocketLauncher_Shoot_CoolTime;
		EndTime = &RocketLauncher_Shoot_EndTime;
		break;
	case EGunList::IronLizard:
		AccTime = &IronLizard_Shoot_AccTime;
		CoolTime = &IronLizard_Shoot_CoolTime;
		EndTime = &IronLizard_Shoot_EndTime;
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
	int PrevFrame = Renderer[static_cast<int>(_BodyRenderer)]->CurAnimation->CurFrame;
	Renderer[static_cast<int>(_BodyRenderer)]->ChangeAnimation(ChangeName);
	Renderer[static_cast<int>(_BodyRenderer)]->CurAnimation->CurFrame = PrevFrame;
}


void Marco::CameraFreeMove(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		GetWorld()->AddCameraPos(FVector::Left * _DeltaTime * 500.0f);
		// AddActorLocation(FVector::Left * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		GetWorld()->AddCameraPos(FVector::Right * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		GetWorld()->AddCameraPos(FVector::Up * _DeltaTime * 500.0f);
		// AddActorLocation(FVector::Up * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		GetWorld()->AddCameraPos(FVector::Down * _DeltaTime * 500.0f);
		// AddActorLocation(FVector::Down * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsDown('2'))
	{
		UpperStateChange(UpperBodyState::Idle);
		LowerStateChange(LowerBodyState::Idle);
		AllStateChange(AllBodyState::None);
	}
}
void Marco::FreeMove(float _DeltaTime)
{
	FVector MovePos;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		MovePos += FVector::Up * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		MovePos += FVector::Down * _DeltaTime * FreeMoveSpeed;
	}

	AddActorLocation(MovePos);
	GetWorld()->SetCameraPos({ GetActorLocation().X - 400.0f, GetActorLocation().Y - 300.0f });

	if (UEngineInput::IsDown('1'))
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

void Marco::UpperNone(float _DeltaTime)
{
	UpperStateChange(UpperBodyState::Idle);
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

		if (
			true == UEngineInput::IsDown('S') ||
			true == UEngineInput::IsDown('s')
			)
		{
			UpperStateChange(UpperBodyState::Jump);
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
			UpperStateChange(UpperBodyState::Shoot);
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


}

void Marco::UpperMove(float _DeltaTime)
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
			UpperStateChange(UpperBodyState::Shoot);
			return;
		}

		if (
			true == UEngineInput::IsDown('S') ||
			true == UEngineInput::IsDown('s')
			)
		{
			UpperStateChange(UpperBodyState::ForwardJump);
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
			std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
			TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
			UpperStateChange(UpperBodyState::ForwardJumpShoot);
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
		return;
	}
}

void Marco::UpperShoot(float _DeltaTime)
{
	GunTypeShootCheck();
	
	if (true == UEngineInput::IsPress(VK_UP))
	{
		if (Gun == EGunList::HeavyMachineGun)
		{
			*AccTime = 0.0f;
			UpperStateChange(UpperBodyState::AimNormalToUpShoot);
			return;
		}
	}

	if (InAir)
	{
		if (true == UEngineInput::IsPress(VK_DOWN))
		{
			if (Gun == EGunList::HeavyMachineGun)
			{
				*AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimNormalToDownShoot);
				return;
			}
		}
	}

	*AccTime += _DeltaTime;
	if (*AccTime > *CoolTime)
	{
		if (InAir)
		{
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
		else
		{
			std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
			DirCheck(BodyRenderer::UpperBody, GunCheckedName);
			if (true == UEngineInput::IsPress(VK_DOWN))
			{
				*AccTime = 0.0f;
				Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
				Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
				return;
			}
			
			if (
				true == UEngineInput::IsDown('S') ||
				true == UEngineInput::IsDown('s')
				)
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
		if (*AccTime > *EndTime)
		{
			*AccTime = 0.0f;
			UpperStateChange(UpperBodyState::Idle);
			return;
		}
		if (true == UEngineInput::IsPress(VK_UP))
		{
			*AccTime = 0.0f;
			UpperStateChange(UpperBodyState::AimNormalToUp);
			return;
		}
	}

	
}

void Marco::UpperForwardJumpShoot(float _DeltaTime)
{
	GunTypeShootCheck();
	if (InAir)
	{
		if (true == UEngineInput::IsPress(VK_UP))
		{
			if (Gun == EGunList::HeavyMachineGun)
			{
				*AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimNormalToUpShoot);
				return;
			}
		}

		if (true == UEngineInput::IsPress(VK_DOWN))
		{
			if (Gun == EGunList::HeavyMachineGun)
			{
				*AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimNormalToDownShoot);
				return;
			}
		}

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
				std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
				HeavyMachineGunCheckName(AddedGunTypeName);
				TriggerDirCheck(BodyRenderer::UpperBody, AddedGunTypeName);
				UpperStateChange(UpperBodyState::ForwardJumpShoot);
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
		*AccTime = 0.0f;
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperThrow(float _DeltaTime)
{
	GunTypeShootCheck();
	*AccTime += _DeltaTime;
	if (*AccTime > *CoolTime)
	{
		if (InAir)
		{
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
				HeavyMachineGunCheckName(AddedGunTypeName);
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
		else
		{
			std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
			DirCheck(BodyRenderer::UpperBody, GunCheckedName);
			if (true == UEngineInput::IsPress(VK_DOWN))
			{
				*AccTime = 0.0f;
				Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOff();
				Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOn();
				return;
			}

			if (
				true == UEngineInput::IsDown('S') ||
				true == UEngineInput::IsDown('s')
				)
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
			if (*AccTime > *EndTime)
			{
				*AccTime = 0.0f;
				UpperStateChange(UpperBodyState::Idle);
				return;
			}
		}

		if (true == UEngineInput::IsPress(VK_UP))
		{
			*AccTime = 0.0f;
			UpperStateChange(UpperBodyState::AimNormalToUp);
			return;
		}


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
	if (
		true == UEngineInput::IsDown('a') ||
		true == UEngineInput::IsDown('A')
		)
	{
		UpperStateChange(UpperBodyState::AimUpShoot);
		return;
	}
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
	if (
		true == UEngineInput::IsDown('a') ||
		true == UEngineInput::IsDown('A')
		)
	{
		UpperStateChange(UpperBodyState::Shoot);
		return;
	}
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
	if (true == UEngineInput::IsFree(VK_UP))
	{
		if (Gun == EGunList::HeavyMachineGun)
		{
			*AccTime = 0.0f;
			UpperStateChange(UpperBodyState::AimUpToNormalShoot);
			return;
		}
	}

	*AccTime += _DeltaTime;
	if (*AccTime > *CoolTime)
	{
		if (InAir)
		{
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
		else
		{
			std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
			DirCheck(BodyRenderer::UpperBody, GunCheckedName);
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

			if (*AccTime > *EndTime)
			{
				*AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimUp);
				return;
			}
		}
		if (true == UEngineInput::IsFree(VK_UP))
		{
			*AccTime = 0.0f;
			UpperStateChange(UpperBodyState::AimUp);
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

	if (InAir)
	{
		if (true == UEngineInput::IsFree(VK_DOWN))
		{
			if (Gun == EGunList::HeavyMachineGun)
			{
				*AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimDownToNormalShoot);
				return;
			}
		}
	}

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
				*AccTime = 0.0f;
				UpperStateChange(UpperBodyState::AimDownToNormal);
				return;
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

void Marco::UpperAimNormalToUpShoot(float _DeltaTime)
{
	AimNormalToUpShoot_AccTime += _DeltaTime;
	if (AimNormalToUpShoot_AccTime > AimNormalToUpShoot_Delay)
	{
		AimNormalToUpShoot_AccTime = 0.0f;
		UpperStateChange(UpperBodyState::AimUpShoot);
		return;
	}
}

void Marco::UpperAimUpToNormalShoot(float _DeltaTime)
{
	AimNormalToUpShoot_AccTime += _DeltaTime;
	if (AimNormalToUpShoot_AccTime > AimNormalToUpShoot_Delay)
	{
		AimNormalToUpShoot_AccTime = 0.0f;
		UpperStateChange(UpperBodyState::Idle);
		return;
	}
}

void Marco::UpperAimNormalToDownShoot(float _DeltaTime)
{
	AimNormalToDownShoot_AccTime += _DeltaTime;
	if (AimNormalToDownShoot_AccTime > AimNormalToDownShoot_Delay)
	{
		AimNormalToDownShoot_AccTime = 0.0f;
		UpperStateChange(UpperBodyState::AimDownShoot);
		return;
	}
}

void Marco::UpperAimDownToNormalShoot(float _DeltaTime)
{
	AimNormalToDownShoot_AccTime += _DeltaTime;
	if (AimNormalToDownShoot_AccTime > AimNormalToDownShoot_Delay)
	{
		AimNormalToDownShoot_AccTime = 0.0f;
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
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true);
}

void Marco::UpperForwardJumpShootStart()
{
	//SpawnActor<Bullet>
	CurUpperBodyName = "UpperBody_ForwardJumpShoot";
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true);
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
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true);
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
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName, true);
}

void Marco::UpperAimNormalToUpShootStart()
{
	CurUpperBodyName = "UpperBody_AimNormalToUpShoot";
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName);
}

void Marco::UpperAimUpToNormalShootStart()
{
	CurUpperBodyName = "UpperBody_AimUpToNormalShoot";
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName);
}

void Marco::UpperAimNormalToDownShootStart()
{
	CurUpperBodyName = "UpperBody_AimNormalToDownShoot";
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName);
}

void Marco::UpperAimDownToNormalShootStart()
{
	CurUpperBodyName = "UpperBody_AimDownToNormalShoot";
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName);
}

void Marco::UpperStart()
{
	std::string AddedGunTypeName = AddGunTypeName(CurUpperBodyName);
	std::string AddedDirectionName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionName,true);
}

void Marco::LowerNone(float _DeltaTime)
{

	LowerStateChange(LowerBodyState::Idle);
}

void Marco::LowerIdle(float _DeltaTime)
{
	DirCheck(BodyRenderer::LowerBody, CurLowerBodyName);
	GravityCheck(_DeltaTime);
	if (InAir)
	{
		LowerStateChange(LowerBodyState::Jump);
		return;
	}

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

	if (
		true == UEngineInput::IsDown('S') || 
		true == UEngineInput::IsDown('s')
		)
	{
		LowerStateChange(LowerBodyState::Jump);
		return;
	}

	if (true == UEngineInput::IsPress(VK_DOWN))
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

	if (true == UEngineInput::IsPress(VK_DOWN))
	{
		Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOff();
		return;
	}

	FVector MovePos = FVector::Zero;
	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * Run_Speed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * Run_Speed;
	}

	if (
		true == UEngineInput::IsDown('S') ||
		true == UEngineInput::IsDown('s')
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
	}
}

void Marco::LowerJump(float _DeltaTime)
{
	GravityCheck(_DeltaTime);
	if (InAir)
	{
		FVector MovePos = FVector::Zero;
		if (UEngineInput::IsPress(VK_LEFT))
		{
			MovePos += FVector::Left * _DeltaTime * InAir_Speed;
		}

		if (UEngineInput::IsPress(VK_RIGHT))
		{
			MovePos += FVector::Right * _DeltaTime * InAir_Speed;
		}

		if (UEngineInput::IsDown('A') ||
			UEngineInput::IsDown('a'))
		{
			std::string ChangeName = AddDirectionName(CurLowerBodyName);
			int PrevFrame = Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CurAnimation->CurFrame;
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(ChangeName);
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CurAnimation->CurFrame = PrevFrame;
		}

		if (UEngineInput::IsDown('D') ||
			UEngineInput::IsDown('d'))
		{
			std::string ChangeName = AddDirectionName(CurLowerBodyName);
			int PrevFrame = Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CurAnimation->CurFrame;
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(ChangeName);
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CurAnimation->CurFrame = PrevFrame;
		}

		AddActorLocation(MovePos);
	}
	else
	{
		DirCheck(BodyRenderer::LowerBody, CurLowerBodyName);
		Reset_UpperBodySyncro();
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
		if (UEngineInput::IsPress(VK_LEFT))
		{
			MovePos += FVector::Left * _DeltaTime * InAir_Speed;
		}

		if (UEngineInput::IsPress(VK_RIGHT))
		{
			MovePos += FVector::Right * _DeltaTime * InAir_Speed;
		}

		if (UEngineInput::IsDown('A') ||
			UEngineInput::IsDown('a'))
		{
			std::string ChangeName = AddDirectionName(CurLowerBodyName);
			int PrevFrame = Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CurAnimation->CurFrame;
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(ChangeName);
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CurAnimation->CurFrame = PrevFrame;
		}

		if (UEngineInput::IsDown('D') ||
			UEngineInput::IsDown('d'))
		{
			std::string ChangeName = AddDirectionName(CurLowerBodyName);
			int PrevFrame = Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CurAnimation->CurFrame;
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(ChangeName);
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CurAnimation->CurFrame = PrevFrame;
		}
		AddActorLocation(MovePos);
	}
	else
	{
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
	Moving_UpperBodySyncro();
	CurLowerBodyName = "LowerBody_Move";
	LowerStart();
}

void Marco::LowerJumpStart()
{
	//addforce
	AddActorLocation({ 0.0f, -3.0f });
	FallSpeed = -500.0f;
	Jumping_UpperBodySyncro();
	CurLowerBodyName = "LowerBody_Jump";
	LowerStart();
}

void Marco::LowerForwardJumpStart()
{
	//addforce
	AddActorLocation({ 0.0f, -3.0f });
	FallSpeed = -500.0f;
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
	CrouchIntro_AccTime += _DeltaTime;
	if (CrouchIntro_AccTime > CrouchIntro_Delay)
	{
		CrouchIntro_AccTime = 0.0f;
		AllStateChange(AllBodyState::Crouch_Idle);
		return;
	}
}

void Marco::AllCrouch_Outro(float _DeltaTime)
{
	CrouchIntro_AccTime += _DeltaTime;
	if (CrouchIntro_AccTime > CrouchIntro_Delay)
	{
		CrouchIntro_AccTime = 0.0f;
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
		AllStateChange(AllBodyState::Crouch_Shoot);
		return;
	}

	if (
		true == UEngineInput::IsDown('S') ||
		true == UEngineInput::IsDown('s')
		)
	{
		Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
		Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOn();
		Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOn();
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
		AllStateChange(AllBodyState::Crouch_Shoot);
		return;
	}

	if (
		true == UEngineInput::IsDown('S') ||
		true == UEngineInput::IsDown('s')
		)
	{
		Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
		Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOn();
		Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOn();
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

void Marco::AllCrouch_Shoot(float _DeltaTime)
{
	GunTypeShootCheck();
	*AccTime += _DeltaTime;
	if (*AccTime > *CoolTime)
	{
		if (true == UEngineInput::IsFree(VK_DOWN))
		{
			*AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Outro);
			return;
		}

		if (
			true == UEngineInput::IsPress(VK_RIGHT) ||
			true == UEngineInput::IsPress(VK_LEFT)
			)
		{
			*AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Move);
			return;
		}

		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			*AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Shoot);
			return;
		}

		if (
			true == UEngineInput::IsDown('S') ||
			true == UEngineInput::IsDown('s')
			)
		{
			*AccTime = 0.0f;
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOn();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOn();
			return;
		}

		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			*AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Throw);
			return;
		}
	}

	if (*AccTime > *EndTime)
	{
		*AccTime = 0.0f;
		AllStateChange(AllBodyState::Crouch_Idle);
		return;
	}
}

void Marco::AllCrouch_HeavyMachineGun_Shoot(float _DeltaTime)
{
	GunTypeShootCheck();
	*AccTime += _DeltaTime;
	if (*AccTime > *CoolTime)
	{
		if (true == UEngineInput::IsFree(VK_DOWN))
		{
			*AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Outro);
			return;
		}

		if (
			true == UEngineInput::IsPress(VK_RIGHT) ||
			true == UEngineInput::IsPress(VK_LEFT)
			)
		{
			*AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Move);
			return;
		}

		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			*AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Shoot);
			return;
		}

		if (
			true == UEngineInput::IsDown('S') ||
			true == UEngineInput::IsDown('s')
			)
		{
			*AccTime = 0.0f;
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOn();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOn();
			return;
		}

		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			*AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Throw);
			return;
		}
	}

	if (*AccTime > *EndTime)
	{
		*AccTime = 0.0f;
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
			Throw_AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Outro);
			return;
		}

		if (
			true == UEngineInput::IsPress(VK_RIGHT) ||
			true == UEngineInput::IsPress(VK_LEFT)
			)
		{
			Throw_AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Move);
			return;
		}

		if (
			true == UEngineInput::IsDown('A') ||
			true == UEngineInput::IsDown('a')
			)
		{
			Throw_AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Shoot);
			return;
		}

		if (
			true == UEngineInput::IsDown('S') ||
			true == UEngineInput::IsDown('s')
			)
		{
			Throw_AccTime = 0.0f;
			Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
			Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ActiveOn();
			Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ActiveOn();
			return;
		}

		if (
			true == UEngineInput::IsDown('D') ||
			true == UEngineInput::IsDown('d')
			)
		{
			Throw_AccTime = 0.0f;
			AllStateChange(AllBodyState::Crouch_Throw);
			return;
		}
	}

	if (Throw_AccTime > Throw_EndTime)
	{
		Throw_AccTime = 0.0f;
		AllStateChange(AllBodyState::Crouch_Idle);
		return;
	}
}

void Marco::AllCrouch_KnifeAttack1(float _DeltaTime)
{
	//콜라이더
}

void Marco::AllCrouch_KnifeAttack2(float _DeltaTime)
{
	//콜라이더
}

void Marco::AllCeremony(float _DeltaTime)
{
}

void Marco::AllDeath(float _DeltaTime)
{
	Destroy(5.0f);
}

void Marco::AllDeathInAir(float _DeltaTime)
{
	Destroy(5.0f);
}

void Marco::AllDeathByKnife(float _DeltaTime)
{
	Destroy(5.0f);
}

void Marco::AllElephantSlug_Idle(float _DeltaTime)
{
	if (
		true == UEngineInput::IsPress(VK_RIGHT) ||
		true == UEngineInput::IsPress(VK_LEFT)
		)
	{
		AllStateChange(AllBodyState::ElephantSlug_Move);
	}
}

void Marco::AllElephantSlug_Move(float _DeltaTime)
{
	if (
		false == UEngineInput::IsPress(VK_RIGHT) &&
		false == UEngineInput::IsPress(VK_LEFT)
		)
	{
		AllStateChange(AllBodyState::ElephantSlug_Idle);
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
	CurAllBodyName = "AllBody_Crouch_Intro";
	AllStart();
}

void Marco::AllCrouch_OutroStart()
{
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
	CurAllBodyName = "AllBody_Crouch_Shoot";
	std::string AddedGunTypeName = AddGunTypeName(CurAllBodyName);
	HeavyMachineGunCheckName(AddedGunTypeName);
	std::string DirectedName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(DirectedName, true);
}

void Marco::AllCrouch_HeavyMachineGun_ShootStart()
{
	CurAllBodyName = "AllBody_Crouch_Shoot";
	AllStart();
}

void Marco::AllCrouch_ThrowStart()
{
	CurAllBodyName = "AllBody_Crouch_Throw";
	AllStart();
}

void Marco::AllCrouch_KnifeAttack1Start()
{
	//콜라이더
}

void Marco::AllCrouch_KnifeAttack2Start()
{
	//콜라이더
}

void Marco::AllCeremonyStart()
{
	CurAllBodyName = "AllBody_Ceremony";
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(AddGunTypeName(CurAllBodyName));
}

void Marco::AllDeathStart()
{
	//AddForce
	CurAllBodyName = "AllBody_Death";
	std::string DirectedName = AddDirectionName(CurAllBodyName);
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(DirectedName);
	DirCheck(BodyRenderer::AllBody, CurAllBodyName);
}

void Marco::AllDeathInAirStart()
{
	//AddForce
	CurAllBodyName = "AllBody_DeathInAir";
	std::string DirectedName = AddDirectionName(CurAllBodyName);
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(DirectedName);
	DirCheck(BodyRenderer::AllBody, CurAllBodyName);
}

void Marco::AllDeathByKnifeStart()
{
	CurAllBodyName = "AllBody_DeathByKnife";
	std::string DirectedName = AddDirectionName(CurAllBodyName);
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(DirectedName);
	DirCheck(BodyRenderer::AllBody, CurAllBodyName);
}

void Marco::AllElephantSlug_IdleStart()
{
	CurAllBodyName = "AllBody_ElephantSlug_Idle";
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(CurAllBodyName);
}

void Marco::AllElephantSlug_MoveStart()
{
	CurAllBodyName = "AllBody_ElephantSlug_Move";
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(CurAllBodyName);
}

void Marco::AllStart()
{
	std::string AddedGunTypeName = AddGunTypeName(CurAllBodyName);
	std::string DirectedName = AddDirectionName(AddedGunTypeName);
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation(DirectedName, true);
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

void Marco::Moving_UpperBodySyncro()
{
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransform({ MarcoUpperBodyPosition + Moving_UpperBodyOffset, MarcoSize });
}
void Marco::Jumping_UpperBodySyncro()
{
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransform({ MarcoUpperBodyPosition + Juming_UpperBodyOffset, MarcoSize });
}
void Marco::ForwardJumping_UpperBodySyncro()
{
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransform({ MarcoUpperBodyPosition + ForwardJumping_UpperBodyOffset, MarcoSize });
}
void Marco::Reset_UpperBodySyncro()
{
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransform({ MarcoUpperBodyPosition, MarcoSize });
}