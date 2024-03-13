#include "PlayLevel.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "SpawnManager.h"
#include "CameraManager.h"
#include "ContentsHelper.h"
#include <EnginePlatform/EngineSound.h>

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewPath;
	NewPath.MoveParent();
	NewPath.Move("MT3Resource");
	NewPath.Move("PlayLevel");

	GEngine->MainWindow.SetClearColor({ 0,0,0,255 });


	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	UEngineResourcesManager::GetInst().CuttingImage("Marco_UpperBody.png", 10, 44);
	UEngineResourcesManager::GetInst().CuttingImage("Marco_LowerBody.png", 10, 6);
	UEngineResourcesManager::GetInst().CuttingImage("Marco_AllBody.png", 10, 94);
	UEngineResourcesManager::GetInst().CuttingImage("Marco_ZombieArm.png", 10, 28);

	UEngineResourcesManager::GetInst().CuttingImage("Zombies_Projectile.png", 10, 10);
	UEngineResourcesManager::GetInst().CuttingImage("ManZombie3_Projectile.png", 10, 2);

	UEngineResourcesManager::GetInst().CuttingImage("ManZombie1.png", 10, 24);
	UEngineResourcesManager::GetInst().CuttingImage("ManZombie1_LaunchEffect.png", 10, 4);

	UEngineResourcesManager::GetInst().CuttingImage("DoctorZombie.png", 10, 22);
	UEngineResourcesManager::GetInst().CuttingImage("DoctorZombie_LaunchEffect.png", 10, 4);

	UEngineResourcesManager::GetInst().CuttingImage("ManZombie2.png", 10, 22);
	UEngineResourcesManager::GetInst().CuttingImage("ManZombie2_LaunchEffect.png", 10, 4);

	UEngineResourcesManager::GetInst().CuttingImage("ManZombie3.png", 10, 22);
	UEngineResourcesManager::GetInst().CuttingImage("ManZombie3_LaunchEffect.png", 10, 4);

	UEngineResourcesManager::GetInst().CuttingImage("WomanZombie.png", 10, 22);
	UEngineResourcesManager::GetInst().CuttingImage("WomanZombie_LaunchEffect.png", 10, 2);

	UEngineResourcesManager::GetInst().CuttingImage("UncleZombie.png", 10, 20);
	UEngineResourcesManager::GetInst().CuttingImage("UncleZombie_LaunchEffect.png", 10, 4);

	UEngineResourcesManager::GetInst().CuttingImage("SoldierZombie.png", 10, 18);

	UEngineResourcesManager::GetInst().CuttingImage("BulletDestroy.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("BloodEffect.png", 10, 6);
	UEngineResourcesManager::GetInst().CuttingImage("Marco_ZombieVomitProjectile.png", 10, 12);

	UEngineResourcesManager::GetInst().CuttingImage("Marco_VomitLaunchEffect.png", 10, 10);

	UEngineResourcesManager::GetInst().CuttingImage("Bomb.png", 10, 8);

	UEngineResourcesManager::GetInst().CuttingImage("Doctor.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("Man1.png", 10, 3);
	UEngineResourcesManager::GetInst().CuttingImage("Man2.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("Woman.png", 10, 3);
	UEngineResourcesManager::GetInst().CuttingImage("Uncle.png", 10, 2);
	UEngineResourcesManager::GetInst().CuttingImage("POWs.png", 10, 7);
	UEngineResourcesManager::GetInst().CuttingImage("CEOsecretary.png", 10, 3);
	UEngineResourcesManager::GetInst().CuttingImage("CEO.png", 10, 16);

	UEngineResourcesManager::GetInst().CuttingImage("Go.png", 10, 2);
	UEngineResourcesManager::GetInst().CuttingImage("In.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("P1UI.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("TimeNumber.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("MissionStart.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("NormalFont.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("YellowFont.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("Status.png", 2, 1);

	UEngineResourcesManager::GetInst().CuttingImage("Soldier.png", 10, 14);
	UEngineResourcesManager::GetInst().CuttingImage("SoldierBomb.png", 10, 2);

	UEngineResourcesManager::GetInst().CuttingImage("Van_SoldierSpawn.png", 10, 1);

	UEngineResourcesManager::GetInst().CuttingImage("Helicopter.png", 10, 12);
	UEngineResourcesManager::GetInst().CuttingImage("LeaderHelicopter.png", 10, 12);
	UEngineResourcesManager::GetInst().CuttingImage("HelicopterProjectile.png", 10, 1);

	UEngineResourcesManager::GetInst().CuttingImage("Propeller.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("EliteHelicopter_Projectile.png", 10, 2);

	UEngineResourcesManager::GetInst().CuttingImage("NormalExplosion.png", 10, 3);
	UEngineResourcesManager::GetInst().CuttingImage("HugeExplosion.png", 10, 3);
	UEngineResourcesManager::GetInst().CuttingImage("BombExplosion.png", 10, 3);
	UEngineResourcesManager::GetInst().CuttingImage("HugeBombExplosion.png", 10, 3);
	UEngineResourcesManager::GetInst().CuttingImage("VomitExplosion.png", 10, 3);

	UEngineResourcesManager::GetInst().CuttingImage("BossStartEvent.png", 4, 1);
	UEngineResourcesManager::GetInst().CuttingImage("MonoEyes_UnknownSphere.png", 10, 2);;
	UEngineResourcesManager::GetInst().CuttingImage("LaunchEffect.png", 10, 2);;
	UEngineResourcesManager::GetInst().CuttingImage("DeathBall.png", 10, 1);;
	UEngineResourcesManager::GetInst().CuttingImage("DeathBallExplosion.png", 10, 3);;
	UEngineResourcesManager::GetInst().CuttingImage("MonoEyes_Death.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("MonoEyes_Spawn.png", 10, 2);

	UEngineResourcesManager::GetInst().CuttingImage("LazerAiming.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("LazerAiming_GroundEffect.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("MonoEye_UFO_Charging.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("MonoEye_UFO_Firing.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("MonoEye_UFO_Idle.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("Rubble.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("Monoliths.png", 10, 4);

	UEngineResourcesManager::GetInst().CuttingImage("BombBox.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("ThunderCloud.png", 10, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Medicine.png", 10, 4);

	UEngineResourcesManager::GetInst().CuttingImage("FlameShot_Right.png", 10, 3);
	UEngineResourcesManager::GetInst().CuttingImage("FlameShot_Left.png", 10, 3);
	UEngineResourcesManager::GetInst().CuttingImage("FlameShot_Up.png", 10, 3);
	UEngineResourcesManager::GetInst().CuttingImage("FlameShot_Down.png", 10, 3);

	UEngineResourcesManager::GetInst().CuttingImage("RocketLauncher_Right.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("RocketLauncher_Left.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("RocketLauncher_Up.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("RocketLauncher_Down.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("RocketLauncher_LaunchEffect_Right.png", 10, 2);
	UEngineResourcesManager::GetInst().CuttingImage("RocketLauncher_LaunchEffect_Left.png", 10, 2);

	UEngineResourcesManager::GetInst().CuttingImage("ThunderCloudObj.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("ThunderCloudObjEffect.png", 10, 2);
	UEngineResourcesManager::GetInst().CuttingImage("ThunderCloudObjLaunch.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("ZombieThunder.png", 10, 1);

	UContentsHelper::CameraManager = SpawnActor<CameraManager>();
	SpawnActor<SpawnManager>();
	
	NewPath.Move("Sound");
	UEngineSound::Load(NewPath.AppendPath("BGM\\MainBGM.mp3"));
	UEngineSound::Load(NewPath.AppendPath("BGM\\EndBGM.mp3"));
	UEngineSound::Load(NewPath.AppendPath("Voice\\Mission2Start.mp3"));
	UEngineSound::Load(NewPath.AppendPath("Voice\\MissonComplete.mp3"));
	UEngineSound::Load(NewPath.AppendPath("Voice\\Okey.mp3"));
	UEngineSound::Load(NewPath.AppendPath("Voice\\RocketLauncher.mp3"));
	UEngineSound::Load(NewPath.AppendPath("Voice\\FlameShot.mp3"));
	UEngineSound::Load(NewPath.AppendPath("Voice\\HeavyMachineGun.mp3"));
	UEngineSound::Load(NewPath.AppendPath("Voice\\ThunderCloud.mp3"));
}
