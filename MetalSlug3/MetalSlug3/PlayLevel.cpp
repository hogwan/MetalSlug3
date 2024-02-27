#include "PlayLevel.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "SpawnManager.h"
#include "CameraManager.h"
#include "ContentsHelper.h"
#include "Soldier.h"
#include "Helicopter.h"
#include "ManZombie3.h"

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

	UEngineResourcesManager::GetInst().CuttingImage("BulletDestroy.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("BloodEffect.png", 10, 6);
	UEngineResourcesManager::GetInst().CuttingImage("Marco_ZombieVomitProjectile.png", 10, 12);

	UEngineResourcesManager::GetInst().CuttingImage("Marco_VomitLaunchEffect.png", 10, 8);

	UEngineResourcesManager::GetInst().CuttingImage("Bomb.png", 10, 8);

	UEngineResourcesManager::GetInst().CuttingImage("Doctor.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("Man1.png", 10, 3);
	UEngineResourcesManager::GetInst().CuttingImage("Man2.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("Woman.png", 10, 3);
	UEngineResourcesManager::GetInst().CuttingImage("Uncle.png", 10, 2);

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

	UEngineResourcesManager::GetInst().CuttingImage("Helicopter.png", 10, 12);
	UEngineResourcesManager::GetInst().CuttingImage("LeaderHelicopter.png", 10, 12);
	UEngineResourcesManager::GetInst().CuttingImage("HelicopterProjectile.png", 10, 1);

	UEngineResourcesManager::GetInst().CuttingImage("NormalExplosion.png", 10, 3);
	SpawnActor<SpawnManager>();
	
	AHelicopter* aaa = SpawnActor<AHelicopter>();
	aaa->SetActorLocation({ 1100,800 });
	UContentsHelper::CameraManager = SpawnActor<CameraManager>();
}
