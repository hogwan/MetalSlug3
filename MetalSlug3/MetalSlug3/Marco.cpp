#include "Marco.h"
#include <EngineCore\EngineCore.h>
#include <EngineBase/EngineTime.h>
#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"
#include "Bomb.h"
#include "MarcoStatus.h"
#include "CreateMarcoAnimation.h"

#define CreateMarcoAnimation \
UpperBodyRenderer->CreateAnimation("Pistol_Idle_Right", "Marco_face-Resource.png", 0, 5, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Idle_Left", "Marco_face-Resource.png", 20, 25, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Run_Right", "Marco_face-Resource.png", 40, 51, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Run_Left", "Marco_face-Resource.png", 60, 71, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Jump_Right", "Marco_face-Resource.png", 80, 87, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Jump_Left", "Marco_face-Resource.png", 100, 107, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_ForwardJump_Right", "Marco_face-Resource.png", 120, 125, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_ForwardJump_Left", "Marco_face-Resource.png", 140, 145, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Shoot_Right", "Marco_face-Resource.png", 160, 169, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Shoot_Left", "Marco_face-Resource.png", 180, 189, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_ForwardJumpShoot_Right", "Marco_face-Resource.png", 200, 209, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_ForwardJumpShoot_Left", "Marco_face-Resource.png", 220, 229, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Throw_Right", "Marco_face-Resource.png", 240, 245, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Throw_Left", "Marco_face-Resource.png", 260, 265, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_KnifeAttack1_Right", "Marco_face-Resource.png", 280, 285, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_KnifeAttack1_Left", "Marco_face-Resource.png", 300, 305, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_KnifeAttack2_Right", "Marco_face-Resource.png", 320, 325, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_KnifeAttack2_Left", "Marco_face-Resource.png", 340, 345, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Aim_Up_NormalToUp_Right", "Marco_face-Resource.png", 360, 361, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Aim_Up_NormalToUp_Left", "Marco_face-Resource.png", 380, 381, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Aim_Up_UpToNormal_Right", "Marco_face-Resource.png", 400, 401, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Aim_Up_UpToNormal_Left", "Marco_face-Resource.png", 420, 421, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Aim_Up_Right", "Marco_face-Resource.png", 440, 445, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Aim_Up_Left", "Marco_face-Resource.png", 460, 465, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_AimUpShoot_Right", "Marco_face-Resource.png", 480, 489, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_AimUpShoot_Left", "Marco_face-Resource.png", 500, 509, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Aim_NormalToDown_Right", "Marco_face-Resource.png", 520, 522, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Aim_NormalToDown_Left", "Marco_face-Resource.png", 540, 542, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Aim_DownToNormal_Right", "Marco_face-Resource.png", 560, 562, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_Aim_DownToNormal_Left", "Marco_face-Resource.png", 580, 582, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_AimDownShoot_Right", "Marco_face-Resource.png", 600, 605, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Pistol_AimDownShoot_Left", "Marco_face-Resource.png", 620, 625, 0.08f, true);\
\
UpperBodyRenderer->CreateAnimation("Rifle_Idle_Right", "Marco_face-Resource.png", 640, 645, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Idle_Left", "Marco_face-Resource.png", 660, 665, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Run_Right", "Marco_face-Resource.png", 680, 691, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Run_Left", "Marco_face-Resource.png", 700, 711, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Jump_Right", "Marco_face-Resource.png", 720, 727, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Jump_Left", "Marco_face-Resource.png", 740, 747, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_ForwardJump_Right", "Marco_face-Resource.png", 760, 765, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_ForwardJump_Left", "Marco_face-Resource.png", 780, 785, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Shoot_HeavyMacineGun_Right", "Marco_face-Resource.png", 800, 803, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Shoot_HeavyMacineGun_Left", "Marco_face-Resource.png", 820, 823, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Shoot_Another_Right", "Marco_face-Resource.png", 840, 849, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Shoot_Another_Left", "Marco_face-Resource.png", 860, 869, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Throw_Right", "Marco_face-Resource.png", 880, 885, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Throw_Left", "Marco_face-Resource.png", 900, 905, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_KnifeAttack1_Right", "Marco_face-Resource.png", 920, 925, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_KnifeAttack1_Left", "Marco_face-Resource.png", 940, 945, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_KnifeAttack2_Right", "Marco_face-Resource.png", 960, 965, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_KnifeAttack2_Left", "Marco_face-Resource.png", 980, 985, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Aim_NormalToUp_Right", "Marco_face-Resource.png", 1000, 1001, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Aim_NormalToUp_Left", "Marco_face-Resource.png", 1020, 1021, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Aim_UpToNormal_Right", "Marco_face-Resource.png", 1040, 1041, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Aim_UpToNormal_Left", "Marco_face-Resource.png", 1060, 1061, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimUp_Right", "Marco_face-Resource.png", 1080, 1085, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimUp_Left", "Marco_face-Resource.png", 1100, 1105, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimUpShoot_HeavyMachineGun_Right", "Exception1_150by150_HeavyMacineGun_JumpUpDownShoot.png", 0, 3, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimUpShoot_HeavyMachineGun_Left", "Exception1_150by150_HeavyMacineGun_JumpUpDownShoot.png", 4, 7, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimUpShoot_Another_Right", "Marco_face-Resource.png", 1180, 1185, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimUpShoot_Another_Left", "Marco_face-Resource.png", 1200, 1205, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimUpShoot_NormalToUp_HeavyMachineGun_Right", "Marco_face-Resource.png", 1220, 1221, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimUpShoot_NormalToUp_HeavyMachineGun_Left", "Marco_face-Resource.png", 1240, 1241, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimUpShoot_UpToNormal_HeavyMachineGun_Right", "Marco_face-Resource.png", 1260, 1261, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimUpShoot_UpToNormal_HeavyMachineGun_Left", "Marco_face-Resource.png", 1280, 1281, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Aim_NormalToDown_Right", "Marco_face-Resource.png", 1300, 1302, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Aim_NormalToDown_Left", "Marco_face-Resource.png", 1320, 1322, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Aim_DownToNormal_Right", "Marco_face-Resource.png", 1340, 1342, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_Aim_DownToNormal_Left", "Marco_face-Resource.png", 1360, 1362, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimDownShoot_HeavyMachineGun_Right", "Exception1_150by150_HeavyMacineGun_JumpUpDownShoot.png", 8, 11, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimDownShoot_HeavyMachineGun_Left", "Exception1_150by150_HeavyMacineGun_JumpUpDownShoot.png", 12, 15, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimDownShoot_Another_Right", "Marco_face-Resource.png", 1440, 1446, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimDownShoot_Another_Left", "Marco_face-Resource.png", 1460, 1466, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimDownShoot_NormalToDown_HeavyMachineGun_Right", "Marco_face-Resource.png", 1480, 1481, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimDownShoot_NormalToDown_HeavyMachineGun_Left", "Marco_face-Resource.png", 1500, 1501, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimDownShoot_DownToNormal_HeavyMachineGun_Right", "Marco_face-Resource.png", 1520, 1521, 0.08f, true);\
UpperBodyRenderer->CreateAnimation("Rifle_AimDownShoot_DownToNormal_HeavyMachineGun_Left", "Marco_face-Resource.png", 1540, 1541, 0.08f, true);\
\
LowerBodyRenderer->CreateAnimation("LowerBody_Idle_Right", "Marco_face-Resource.png", 1560, 1560, 0.08f, true);\
LowerBodyRenderer->CreateAnimation("LowerBody_Idle_Left", "Marco_face-Resource.png", 1580, 1580, 0.08f, true);\
LowerBodyRenderer->CreateAnimation("LowerBody_Run_Right", "Marco_face-Resource.png", 1600, 1611, 0.08f, true);\
LowerBodyRenderer->CreateAnimation("LowerBody_Run_Left", "Marco_face-Resource.png", 1620, 1631, 0.08f, true);\
LowerBodyRenderer->CreateAnimation("Jump_Right", "Marco_face-Resource.png", 1640, 1647, 0.08f, true);\
LowerBodyRenderer->CreateAnimation("Jump_Left", "Marco_face-Resource.png", 1660, 1667, 0.08f, true);\
LowerBodyRenderer->CreateAnimation("ForwardJump_Right", "Marco_face-Resource.png", 1680, 1685, 0.08f, true);\
LowerBodyRenderer->CreateAnimation("ForwardJump_Left", "Marco_face-Resource.png", 1700, 1705, 0.08f, true);\


Marco::Marco()
{
}

Marco::~Marco()
{
}

void Marco::BeginPlay()
{
	//배경색 153,217,234

	UpperBodyRenderer = CreateImageRenderer();
	UpperBodyRenderer->SetImage("Marco_face-Resource.png");
	UpperBodyRenderer->SetTransform({ {0,-35}, {100, 100} });
	UpperBodyRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });

	LowerBodyRenderer = CreateImageRenderer();
	LowerBodyRenderer->SetImage("Marco_face-Resource.png");
	LowerBodyRenderer->SetTransform({ {0,50}, {100, 100} });
	LowerBodyRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });

	CreateMarcoAnimation;

	UpperBodyRenderer->ChangeAnimation("Pistol_Shoot_Right");
	LowerBodyRenderer->ChangeAnimation("Jump_Right");

	SetActorLocation({ 100, 100 });
}

void Marco::Tick(float _DeltaTime)
{
	if (true == EngineInput::IsPress(VK_LEFT))
	{
		UpdateStatus |= Move;
		AddActorLocation(FVector::Left * 300.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_RIGHT))
	{
		UpdateStatus |= Move;
		AddActorLocation(FVector::Right * 300.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_UP))
	{
		UpdateStatus |= AimingUp;
	}

	if (true == EngineInput::IsPress(VK_DOWN))
	{
		if (InAir)
		{
			UpdateStatus |= AimingDown;
		}
		else
		{
			UpdateStatus |= Crouch;
		}
	}

	if (true == EngineInput::IsDown('A'))
	{
		UpdateStatus |= Attack;

		ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
		FVector SpawnLocation = GetActorLocation() + FVector{ 70.0f,-10.f,0.f,0.f };
		NewBullet->SetActorLocation(SpawnLocation);
		NewBullet->SetDir(FVector::Right);
	}

	if (true == EngineInput::IsDown('S'))
	{
		if (!InAir)
		{
			InAir = true;
			//점프
		}
	}

	if (true == EngineInput::IsDown('D'))
	{
		UpdateStatus |= Throwing;
		//폭탄던지기
		ABomb* NewBomb = GetWorld()->SpawnActor<ABomb>();
		NewBomb->SetActorLocation(GetActorLocation());
		NewBomb->SetDir(FVector::Right);
	}


	////////////////////////////////////////////////////////
	//                랜더상태처리(애니메이션)            //
	////////////////////////////////////////////////////////


	UpdateStatus = 0;
}