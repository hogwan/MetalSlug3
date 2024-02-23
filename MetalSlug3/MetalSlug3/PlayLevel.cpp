#include "PlayLevel.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "SpawnManager.h"
#include "CameraManager.h"
#include "ContentsHelper.h"

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


	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	UEngineResourcesManager::GetInst().CuttingImage("Marco_UpperBody.png", 10, 44);
	UEngineResourcesManager::GetInst().CuttingImage("Marco_LowerBody.png", 10, 6);
	UEngineResourcesManager::GetInst().CuttingImage("Marco_AllBody.png", 10, 94);
	UEngineResourcesManager::GetInst().CuttingImage("Marco_ZombieArm.png", 10, 28);

	UEngineResourcesManager::GetInst().CuttingImage("Zombies_Projectile.png", 10, 10);
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

	SpawnActor<SpawnManager>();
	UContentsHelper::CameraManager = SpawnActor<CameraManager>();
}
