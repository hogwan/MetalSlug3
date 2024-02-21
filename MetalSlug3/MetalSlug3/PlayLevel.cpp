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
#include "UncleZombie.h"
#include "ManZombie3.h"
#include "Front1.h"
#include "Front2.h"
#include "Go.h"
#include "ScreenCollision.h"
#include "Time.h"
#include "StatusUI.h"
#include "BackMap.h"

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

	UEngineResourcesManager::GetInst().CuttingImage("Go.png", 10, 2);
	UEngineResourcesManager::GetInst().CuttingImage("In.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("P1UI.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("TimeNumber.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("MissionStart.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("NormalFont.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("YellowFont.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("Status.png", 2, 1);

	UContentsHelper::ScreenCol = SpawnActor<AScreenCollision>();
	//UContentsHelper::ScreenCol->GetCollider()->ActiveOff();

	ABackMap* Back = SpawnActor<ABackMap>();
	Back->SetActorLocation({ 1994,550 });

	ABackGroundMap* Map = SpawnActor<ABackGroundMap>();
	Map->SetMapImage("BackGround1.png");
	Map->SetColMapImage("BackGround1_Col.png");

	AFront1* F1 = SpawnActor<AFront1>();
	F1->SetActorLocation({ 2733,930 });

	AFront2* F2 = SpawnActor<AFront2>();
	F2->SetActorLocation({ 4270,807 });

	UContentsHelper::Player = SpawnActor<Marco>();
	UContentsHelper::Player->SetActorLocation({ 100,1000 });

	AGo* Go = SpawnActor<AGo>();
	Go->SetActorLocation({ 650,230 });
	Go->Renderer->ActiveOff();

	ATime* TimeUI = SpawnActor<ATime>();
	TimeUI->SetActorLocation({400,50});

	AStatusUI* StatusUI = SpawnActor<AStatusUI>();
	StatusUI->SetActorLocation({ 270,50 });

	 
	AZombies* Zombie_0 = SpawnActor<AManZombie1>();
	Zombie_0->SetActorLocation({ 1000,1000 });

	/*AZombies* Zombie_1= SpawnActor<ADoctorZombie>();
	Zombie_1->SetActorLocation({ 500,1000 });

	AZombies* Zombie_2 = SpawnActor<AManZombie2>();
	Zombie_2->SetActorLocation({ 750,1000 });

	AZombies* Zombie_3 = SpawnActor<AWomanZombie>();
	Zombie_3->SetActorLocation({ 250,1000 });

	AZombies* Zombie_4 = SpawnActor<AUncleZombie>();
	Zombie_4->SetActorLocation({ 1250,1000 });

	AZombies* Zombie_5 = SpawnActor<AManZombie3>();
	Zombie_5->SetActorLocation({ 1500,1000 });*/

	/*17087 2676

	6429 999


	2.6578005910717063306890651734329  2.6786786786786786786786786786787

	4.0741626794258373205741626794258   0.27357286157213204450118548240015*/
}
