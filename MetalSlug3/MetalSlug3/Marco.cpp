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
	Renderer.push_back(CreateImageRenderer(MT3RenderOrder::Player));          // UpperBody
	Renderer.push_back(CreateImageRenderer(MT3RenderOrder::Player));          // LowerBody
	Renderer.push_back(CreateImageRenderer(MT3RenderOrder::Player));          // AllBody
	Renderer.push_back(CreateImageRenderer(MT3RenderOrder::Player));          //ZombieArm
	Renderer.push_back(CreateImageRenderer(MT3RenderOrder::Projectile));      //ZombieLaunchEffect
	Renderer.push_back(CreateImageRenderer(MT3RenderOrder::Projectile));      //ZombieProjectile

	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetImage("Marco_face-Resource.png");
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransform({ {0,0}, {200, 200} });
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetImageCuttingTransform({ {0,0}, {100, 100} });
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->SetTransColor({ 153, 217, 234, 0 });

	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetImage("Marco_face-Resource.png");
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetTransform({ {0,16}, {200, 200} });
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetImageCuttingTransform({ {0,0}, {100, 100} });
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->SetTransColor({ 153, 217, 234, 0 });

	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetImage("Marco_face-Resource.png");
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetTransform({ {0,0}, {200, 200} });
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetImageCuttingTransform({ {0,0}, {100, 100} });
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->SetTransColor({ 153, 217, 234, 0 });

	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetImage("Marco_face-Resource.png");
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetTransform({ {150,150}, {100, 100} });
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetImageCuttingTransform({ {0,0}, {100, 100} });
	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->SetTransColor({ 153, 217, 234, 0 });

	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->SetImage("Marco_face-Resource.png");
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->SetTransform({ {150,0}, {100, 100} });
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->SetImageCuttingTransform({ {0,0}, {100, 100} });
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->SetTransColor({ 153, 217, 234, 0 });

	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->SetImage("Marco_face-Resource.png");
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->SetTransform({ {150,150}, {100, 100} });
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->SetImageCuttingTransform({ {0,0}, {100, 100} });
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->SetTransColor({ 153, 217, 234, 0 });

	CreateMarcoAnimation;

	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation("Pistol_UpperBody_Idle_Right");
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation("LowerBody_Idle_Right");

	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation("Zombie_AllBody_Vomit_Right");
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->ChangeAnimation("Zombie_AllBody_Vomit_LaunchEffect_Right");
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->ChangeAnimation("Zombie_AllBody_Vomit_ProjectileEffect_Right");

	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->ActiveOff();

	SetActorLocation({ 400, 300 });
	StateChange(EPlayState::Idle);
}


void Marco::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);
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

void Marco::StateChange(EPlayState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EPlayState::Idle:
			IdleStart();
			break;
		case EPlayState::Move:
			MoveStart();
			break;
		case EPlayState::Jump:
			JumpStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Marco::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EPlayState::CameraFreeMove:
		CameraFreeMove(_DeltaTime);
		break;
	case EPlayState::FreeMove:
		FreeMove(_DeltaTime);
		break;
	case EPlayState::Idle:
		Idle(_DeltaTime);
		break;
	case EPlayState::Move:
		Move(_DeltaTime);
		break;
	case EPlayState::Jump:
		Jump(_DeltaTime);
		break;
	
	default:
		break;
	}
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
		StateChange(EPlayState::Idle);
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
		StateChange(EPlayState::Idle);
	}
}

void Marco::Idle(float _DeltaTime)
{
	if (true == EngineInput::IsDown('1'))
	{
		StateChange(EPlayState::FreeMove);
		return;
	}
	GravityCheck(_DeltaTime);
}


void Marco::Move(float _DeltaTime)
{
}

void Marco::Jump(float _DeltaTime)
{
}

void Marco::IdleStart()
{
	CurUpperBodyName = "UpperBody_Idle";
	CurLowerBodyName = "LowerBody_Idle";
	std::string UpperTempName = CurUpperBodyName;
	std::string LowerTempName = CurLowerBodyName;
	std::string AddedGunTypeUpperName = AddGunTypeName(UpperTempName);
	std::string AddedDirectionUpperName = AddDirectionName(AddedGunTypeUpperName);
	std::string AddedDirectionLowerName = AddDirectionName(LowerTempName);
	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation(AddedDirectionUpperName);
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation(AddedDirectionLowerName);
	std::string GunCheckedName = GunCheck(BodyRenderer::UpperBody, CurUpperBodyName);
	std::string DirectionCheckedUpperName = DirCheck(BodyRenderer::UpperBody, GunCheckedName);
	std::string DirectionCheckedLowerName = DirCheck(BodyRenderer::LowerBody , CurLowerBodyName);
}

void Marco::MoveStart()
{
}

void Marco::JumpStart()
{
}
