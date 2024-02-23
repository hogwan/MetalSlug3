#include "SpawnManager.h"
#include "Marco.h"
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
#include "ScoreUI.h"
#include "SlugEnergyBar.h"
#include "LifeUI.h"
#include "Doctor.h"
#include "Man1.h"
#include "Man2.h"
#include "Woman.h"
#include "Uncle.h"
#include "CameraModeSwitch.h"

SpawnManager::SpawnManager()
{
}

SpawnManager::~SpawnManager()
{
}

void SpawnManager::BeginPlay()
{
	UContentsHelper::ScreenCol = GetWorld()->SpawnActor<AScreenCollision>();
	UContentsHelper::ScreenCol->GetCollider()->ActiveOff();

	ABackMap* Back = GetWorld()->SpawnActor<ABackMap>();
	Back->SetActorLocation({ 1994,550 });

	ABackGroundMap* Map = GetWorld()->SpawnActor<ABackGroundMap>();
	Map->SetMapImage("BackGround1.png");
	Map->SetColMapImage("BackGround1_Col.png");

	AFront1* F1 = GetWorld()->SpawnActor<AFront1>();
	F1->SetActorLocation({ 2733,930 });

	AFront2* F2 = GetWorld()->SpawnActor<AFront2>();
	F2->SetActorLocation({ 4270,807 });

	UContentsHelper::Player = GetWorld()->SpawnActor<Marco>();
	UContentsHelper::Player->SetActorLocation({ 100,1000 });

	AGo* Go = GetWorld()->SpawnActor<AGo>();
	Go->SetActorLocation({ 650,230 });
	Go->Renderer->ActiveOff();

	ATime* TimeUI = GetWorld()->SpawnActor<ATime>();
	TimeUI->SetActorLocation({ 400,70 });

	AStatusUI* StatusUI = GetWorld()->SpawnActor<AStatusUI>();
	StatusUI->SetActorLocation({ 280,70 });

	AScoreUI* ScoreUI = GetWorld()->SpawnActor<AScoreUI>();
	ScoreUI->SetActorLocation({ 190,47 });
	UContentsHelper::Score = 1234567;

	ASlugEnergyBar* SlugEnergyBar = GetWorld()->SpawnActor<ASlugEnergyBar>();
	SlugEnergyBar->SetActorLocation({ 120,67 });

	ALifeUI* LifeUI = GetWorld()->SpawnActor<ALifeUI>();
	LifeUI->SetActorLocation({ 70,87 });

	ACameraModeSwitch* CameraSwitch_0 = GetWorld()->SpawnActor<ACameraModeSwitch>();
	CameraSwitch_0->SetActorLocation({ 3500,870 });

	ACameraModeSwitch* CameraSwitch_1 = GetWorld()->SpawnActor<ACameraModeSwitch>();
	CameraSwitch_1->SetActorLocation({ 4680,650 });

	ACameraModeSwitch* CameraSwitch_2 = GetWorld()->SpawnActor<ACameraModeSwitch>();
	CameraSwitch_2->SetActorLocation({ 6900,1450 });

	ACameraModeSwitch* CameraSwitch_3 = GetWorld()->SpawnActor<ACameraModeSwitch>();
	CameraSwitch_3->SetActorLocation({ 7300,1450 });

	ACameraModeSwitch* CameraSwitch_4 = GetWorld()->SpawnActor<ACameraModeSwitch>();
	CameraSwitch_4->SetActorLocation({ 8160,1810 });

	ACameraModeSwitch* CameraSwitch_5 = GetWorld()->SpawnActor<ACameraModeSwitch>();
	CameraSwitch_5->SetActorLocation({ 8535,2200 });

	ACameraModeSwitch* CameraSwitch_6 = GetWorld()->SpawnActor<ACameraModeSwitch>();
	CameraSwitch_6->SetActorLocation({ 10730,2200 });

	ACameraModeSwitch* CameraSwitch_7 = GetWorld()->SpawnActor<ACameraModeSwitch>();
	CameraSwitch_7->SetActorLocation({ 13200,2370 });

	ADoctor* Doctor_0 = GetWorld()->SpawnActor<ADoctor>();
	Doctor_0->SetActorLocation({ 300,1000 }); 
	Doctor_0->StateChange(HumanState::Run); 
	
	ADoctor* Doctor_1 = GetWorld()->SpawnActor<ADoctor>();
	Doctor_1->SetActorLocation({ 340,1000 }); 
	Doctor_1->StateChange(HumanState::Run); 
	
	ADoctor* Doctor_2 = GetWorld()->SpawnActor<ADoctor>();
	Doctor_2->SetActorLocation({ 380,1000 }); 
	Doctor_2->StateChange(HumanState::Run); 
	
	ADoctor* Doctor_3 = GetWorld()->SpawnActor<ADoctor>();
	Doctor_3->SetActorLocation({ 400,1000 }); 
	Doctor_3->StateChange(HumanState::Run); 
	
	ADoctor* Doctor_4 = GetWorld()->SpawnActor<ADoctor>();
	Doctor_4->SetActorLocation({ 450,1000 }); 
	Doctor_4->StateChange(HumanState::Run); 
	
}

void SpawnManager::Tick(float _DeltaTime)
{
	float CameraPos = GetWorld()->GetCameraPos().X;
	float TargetPos = CameraPos + 800.0f;

	if (SpawnNumber == 0 && TargetPos > 1100.0f)
	{
		ADoctor* Doctor_5 = GetWorld()->SpawnActor<ADoctor>();
		Doctor_5->SetActorLocation({ 1200,1000 }); 
		Doctor_5->StateChange(HumanState::Run);

		AManZombie2* ManZombie2_0 = GetWorld()->SpawnActor<AManZombie2>();
		ManZombie2_0->SetActorLocation({ 1240,1000 }); 
		ManZombie2_0->StateChange(EnemyZombieState::Move); 
	
		AManZombie1* ManZombie1_0 = GetWorld()->SpawnActor<AManZombie1>();
		ManZombie1_0->SetActorLocation({ 1320,1000 }); 
		ManZombie1_0->StateChange(EnemyZombieState::Move); 

		ADoctorZombie* DoctorZombie_0 = GetWorld()->SpawnActor<ADoctorZombie>();
		DoctorZombie_0->SetActorLocation({ 1370,1000 });
		DoctorZombie_0->StateChange(EnemyZombieState::Move);
		++SpawnNumber;
	}
	
	if (SpawnNumber == 1 && TargetPos > 1500)
	{
		AWomanZombie* WomanZombie_0 = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie_0->SetActorLocation({ 1600,1030 });
		WomanZombie_0->StateChange(EnemyZombieState::Idle);
		++SpawnNumber;
	}
	
}
