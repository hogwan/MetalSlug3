#include "PlayLevel.h"
#include "Marco.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "BackGroundMap.h"
#include "ManZombie1.h"
#include "ManZombie2.h"
#include "DoctorZombie.h"
#include "WomanZombie.h"

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
		// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
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

	UEngineResourcesManager::GetInst().CuttingImage("WomanZombie.png", 10, 22);
	UEngineResourcesManager::GetInst().CuttingImage("WomanZombie_LaunchEffect.png", 10, 2);

	UEngineResourcesManager::GetInst().CuttingImage("BulletDestroy.png", 10, 1);
	ABackGroundMap* Map = SpawnActor<ABackGroundMap>();
	Map->SetMapImage("BackGround1.png");
	Map->SetColMapImage("BackGround1_Col.png");

	UContentsHelper::Player = SpawnActor<Marco>();
	 
	/*AZombies* Zombie_0 = SpawnActor<AManZombie1>();
	Zombie_0->SetActorLocation({ 1000,1000 });

	AZombies* Zombie_1= SpawnActor<ADoctorZombie>();
	Zombie_1->SetActorLocation({ 500,1000 });

	AZombies* Zombie_2 = SpawnActor<AManZombie2>();
	Zombie_2->SetActorLocation({ 750,1000 });*/

	AZombies* Zombie_3 = SpawnActor<AWomanZombie>();
	Zombie_3->SetActorLocation({ 250,1000 });
}
