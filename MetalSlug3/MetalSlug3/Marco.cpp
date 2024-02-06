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
	//¹è°æ»ö 153,217,234
	/*UpperBody,
		LowerBody,
		AllBody,
		ZombieArm,
		ZombieLaunchEffect,
		ZombieProjectile,*/
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

	Renderer[static_cast<int>(BodyRenderer::UpperBody)]->ChangeAnimation("Pistol_Idle_Right");
	Renderer[static_cast<int>(BodyRenderer::LowerBody)]->ChangeAnimation("LowerBody_Idle_Right");

	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ChangeAnimation("Zombie_AllBody_Vomit_Right");
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->ChangeAnimation("Zombie_AllBody_Vomit_LaunchEffect_Right");
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->ChangeAnimation("Zombie_AllBody_Vomit_ProjectileEffect_Right");

	Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::AllBody)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::ZombieLaunchEffect)]->ActiveOff();
	Renderer[static_cast<int>(BodyRenderer::ZombieProjectile)]->ActiveOff();

	SetActorLocation({ 400, 300 });
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

void Marco::DirCheck(BodyRenderer BodyRendererType)
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
		AddDirectionName(CurAnimationName);
		Renderer[static_cast<int>(BodyRendererType)]->ChangeAnimation(CurAnimationName);
	}
}

void Marco::AddDirectionName(std::string& CurAnimName)
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

	CurAnimName += DirName;
}

void Marco::AddRifleName(std::string& CurAnimName)
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

	CurAnimName = AddGunType + CurAnimName;
}

void Marco::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case PlayState::Idle:
		Idle(_DeltaTime);
		break;
	case PlayState::Move:
		Move(_DeltaTime);
		break;
	case PlayState::Jump:
		Jump(_DeltaTime);
		break;
	default:
		break;
	}
}

void Marco::Idle(float _DeltaTime)
{
}

void Marco::Move(float _DeltaTime)
{
}

void Marco::Jump(float _DeltaTime)
{
}
