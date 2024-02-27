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
#include "ContentsHelper.h"
#include "CameraManager.h"
#include "Soldier.h"
#include "Helicopter.h"
#include "LeaderHelicopter.h"
#include "Van.h"

SpawnManager::SpawnManager()
{
}

SpawnManager::~SpawnManager()
{
}

void SpawnManager::BeginPlay()
{
	UContentsHelper::ScreenCol = GetWorld()->SpawnActor<AScreenCollision>();
	//UContentsHelper::ScreenCol->GetCollider()->ActiveOff();

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
	if (ALeaderHelicopter::HeliList.size())
	{
		std::list<AHelicopter*>::iterator iter = ALeaderHelicopter::HeliList.begin();
		for (; iter != ALeaderHelicopter::HeliList.end();)
		{
			if ((*iter == nullptr))
			{
				std::list<AHelicopter*>::iterator Previter = iter++;
				ALeaderHelicopter::HeliList.erase(Previter);
				continue;
			}

			if ((*iter)->IsDeath)
			{
				(*iter)->Destroy();
				std::list<AHelicopter*>::iterator Previter = iter++;
				ALeaderHelicopter::HeliList.erase(Previter);
			}
			else
			{
				++iter;
			}
		}
	}

	float CameraPos = GetWorld()->GetCameraPos().X;
	float TargetPos = CameraPos + 800.0f;

	if (SpawnNumber == 0 && TargetPos > 1100.0f)
	{
		ADoctor* Doctor = GetWorld()->SpawnActor<ADoctor>();
		Doctor->SetActorLocation({ 1200,1000 }); 
		Doctor->StateChange(HumanState::Run);

		AManZombie2* ManZombie2 = GetWorld()->SpawnActor<AManZombie2>();
		ManZombie2->SetActorLocation({ 1240,1000 }); 
		ManZombie2->StateChange(EnemyZombieState::Move); 
	
		AManZombie1* ManZombie1 = GetWorld()->SpawnActor<AManZombie1>();
		ManZombie1->SetActorLocation({ 1320,1000 }); 
		ManZombie1->StateChange(EnemyZombieState::Move); 

		ADoctorZombie* DoctorZombie = GetWorld()->SpawnActor<ADoctorZombie>();
		DoctorZombie->SetActorLocation({ 1370,1000 });
		DoctorZombie->StateChange(EnemyZombieState::Move);
		++SpawnNumber;
	}
	
	if (SpawnNumber == 1 && TargetPos > 1500)
	{
		AWomanZombie* WomanZombie = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie->SetActorLocation({ 1600,1030 });
		WomanZombie->StateChange(EnemyZombieState::Idle);
		++SpawnNumber;
	}

	if (SpawnNumber == 2 && TargetPos > 1600)
	{
		AManZombie2* ManZombie2_0 = GetWorld()->SpawnActor<AManZombie2>();
		ManZombie2_0->SetActorLocation({ 1670,1030 });
		ManZombie2_0->StateChange(EnemyZombieState::Idle);

		AUncle* Uncle = GetWorld()->SpawnActor<AUncle>();
		Uncle->SetActorLocation({ 1770, 1030 });
		Uncle->StateChange(HumanState::Idle);

		AManZombie2* ManZombie2_1 = GetWorld()->SpawnActor<AManZombie2>();
		ManZombie2_1->SetActorLocation({ 1930,1030 });
		ManZombie2_1->StateChange(EnemyZombieState::Idle);

		++SpawnNumber;
	}
	
	if (SpawnNumber == 3 && TargetPos > 1920)
	{
		AManZombie1* ManZombie1 = GetWorld()->SpawnActor<AManZombie1>();
		ManZombie1->SetActorLocation({ 1050,1000 });
		ManZombie1->DirState = EActorDir::Right;
		ManZombie1->StateChange(EnemyZombieState::Move);
		++UContentsHelper::CameraManager->CameraMode;


		++SpawnNumber;
	}

	if (SpawnNumber == 4 && UContentsHelper::CameraManager->CameraMode == 1)
	{
		std::vector<UCollision*> Result;
		UContentsHelper::CameraManager->CameraMode;
		if (
			!UContentsHelper::ScreenCol->GetCollider()->CollisionCheck(MT3CollisionOrder::Enemy, Result)
			)
		{
			++UContentsHelper::CameraManager->CameraMode;
		}
	}

	if (SpawnNumber == 4 && TargetPos > 2150)
	{
		AWomanZombie* WomanZombie_0 = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie_0->SetActorLocation({ 2300,1020 });
		WomanZombie_0->StateChange(EnemyZombieState::Move);

		AWomanZombie* WomanZombie_1 = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie_1->SetActorLocation({ 2500,1020 });
		WomanZombie_1->StateChange(EnemyZombieState::Move);

		AUncleZombie* UncleZombie = GetWorld()->SpawnActor<AUncleZombie>();
		UncleZombie->SetActorLocation({ 2700,1020 });
		UncleZombie->StateChange(EnemyZombieState::Move);

		AMan1* Man = GetWorld()->SpawnActor<AMan1>();
		Man->SetActorLocation({ 2530,1020 });
		Man->StateChange(HumanState::Idle);

		AWoman* Woman = GetWorld()->SpawnActor<AWoman>();
		Woman->SetActorLocation({ 2580,1020 });
		Woman->StateChange(HumanState::Idle);

		++SpawnNumber;
	}

	if (SpawnNumber == 5 && TargetPos > 3080)
	{
		ADoctor* Doctor = GetWorld()->SpawnActor<ADoctor>();
		Doctor->SetActorLocation({ 3200,950 });
		Doctor->StateChange(HumanState::Run);

		AMan2* Man2_0 = GetWorld()->SpawnActor<AMan2>();
		Man2_0->SetActorLocation({ 3200,950 });
		Man2_0->StateChange(HumanState::Move);

		AMan1* Man1 = GetWorld()->SpawnActor<AMan1>();
		Man1->SetActorLocation({ 3250,950 });
		Man1->StateChange(HumanState::Idle);

		AUncle* Uncle = GetWorld()->SpawnActor<AUncle>();
		Uncle->SetActorLocation({ 3300,950 });
		Uncle->StateChange(HumanState::Idle);

		AMan2* Man2_1 = GetWorld()->SpawnActor<AMan2>();
		Man2_1->SetActorLocation({ 3350,950 });
		Man2_1->StateChange(HumanState::Move);

		AManZombie1* ManZombie1 = GetWorld()->SpawnActor<AManZombie1>();
		ManZombie1->SetActorLocation({ 3450,900 });
		ManZombie1->StateChange(EnemyZombieState::Move);

		ADoctorZombie* DoctorZombie_0 = GetWorld()->SpawnActor<ADoctorZombie>();
		DoctorZombie_0->SetActorLocation({ 3650,850 });
		DoctorZombie_0->StateChange(EnemyZombieState::Move);

		ADoctorZombie* DoctorZombie_1 = GetWorld()->SpawnActor<ADoctorZombie>();
		DoctorZombie_1->SetActorLocation({ 3850,800 });
		DoctorZombie_1->StateChange(EnemyZombieState::Move);

		++SpawnNumber;
	}

	if (SpawnNumber == 6 && UContentsHelper::CameraManager->CameraMode==3)
	{
		ADoctor* Doctor = GetWorld()->SpawnActor<ADoctor>();
		Doctor->SetActorLocation({ 4000,750 });
		Doctor->StateChange(HumanState::Run);

		AUncleZombie* UncleZombie_0 = GetWorld()->SpawnActor<AUncleZombie>();
		UncleZombie_0->SetActorLocation({ 4000,750 });
		UncleZombie_0->StateChange(EnemyZombieState::Move);

		AWomanZombie* WomanZombie = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie->SetActorLocation({ 4200,700 });
		WomanZombie->StateChange(EnemyZombieState::Move);

		AUncleZombie* UncleZombie_1 = GetWorld()->SpawnActor<AUncleZombie>();
		UncleZombie_1->SetActorLocation({ 3070,970 });
		UncleZombie_1->DirState = EActorDir::Right;
		UncleZombie_1->StateChange(EnemyZombieState::Move);

		AManZombie1* ManZombie1 = GetWorld()->SpawnActor<AManZombie1>();
		ManZombie1->SetActorLocation({ 2700,970 });
		ManZombie1->DirState = EActorDir::Right;
		ManZombie1->StateChange(EnemyZombieState::Move);

		++SpawnNumber;
	}

	if (SpawnNumber == 7 && TargetPos > 4060)
	{
		AManZombie1* ManZombie1_0 = GetWorld()->SpawnActor<AManZombie1>();
		ManZombie1_0->SetActorLocation({ 1400,720 });
		ManZombie1_0->StateChange(EnemyZombieState::Move);

		AWomanZombie* WomanZombie_0 = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie_0->SetActorLocation({ 4100,720 });
		WomanZombie_0->StateChange(EnemyZombieState::Move);

		AWoman* Woman = GetWorld()->SpawnActor<AWoman>();
		Woman->SetActorLocation({ 4190,710 });
		Woman->StateChange(HumanState::Idle);

		AManZombie1* ManZombie1_1 = GetWorld()->SpawnActor<AManZombie1>();
		ManZombie1_1->SetActorLocation({ 4400,600 });
		ManZombie1_1->StateChange(EnemyZombieState::Move);

		AManZombie2* ManZombie2_0 = GetWorld()->SpawnActor<AManZombie2>();
		ManZombie2_0->SetActorLocation({ 4475,600 });
		ManZombie2_0->StateChange(EnemyZombieState::Move);

		AWomanZombie* WomanZombie_1 = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie_1->SetActorLocation({ 4550,600 });
		WomanZombie_1->StateChange(EnemyZombieState::Move);

		++SpawnNumber;
	}

	if (SpawnNumber == 8 && TargetPos > 4670)
	{
		AWoman* Woman = GetWorld()->SpawnActor<AWoman>();
		Woman->SetActorLocation({ 4750,930 });
		Woman->StateChange(HumanState::Idle);

		AUncle* Uncle = GetWorld()->SpawnActor<AUncle>();
		Uncle->SetActorLocation({ 4790,930 });
		Uncle->StateChange(HumanState::Idle);

		AMan2* Man2 = GetWorld()->SpawnActor<AMan2>();
		Man2->SetActorLocation({ 5300,930 });
		Man2->StateChange(HumanState::Move);

		AWomanZombie* WomanZombie_0 = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie_0->SetActorLocation({ 4830,930 });
		WomanZombie_0->StateChange(EnemyZombieState::Lying);

		AWomanZombie* WomanZombie_1 = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie_1->SetActorLocation({ 4920,930 });
		WomanZombie_1->StateChange(EnemyZombieState::Lying);

		AWomanZombie* WomanZombie_2 = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie_2->SetActorLocation({ 5020,930 });
		WomanZombie_2->StateChange(EnemyZombieState::Lying);

		AWomanZombie* WomanZombie_3 = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie_3->SetActorLocation({ 5400,930 });
		WomanZombie_3->StateChange(EnemyZombieState::Lying);

		++SpawnNumber;
	}

	if (SpawnNumber == 9 && TargetPos > 5950)
	{
		ASoldier* Soldier_0 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_0->SetPattern(SoldierPattern::Throw);
		Soldier_0->StateChange(SoldierState::Move);
		Soldier_0->SetActorLocation({ 6050,1050 });

		ASoldier* Soldier_1 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_1->SetPattern(SoldierPattern::Throw);
		Soldier_1->StateChange(SoldierState::Move);
		Soldier_1->SetActorLocation({ 6120,1050 });

		ASoldier* Soldier_2 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_2->SetPattern(SoldierPattern::Throw);
		Soldier_2->StateChange(SoldierState::Move);
		Soldier_2->SetActorLocation({ 6190,1050 });

		++SpawnNumber;
	}

	if (SpawnNumber == 10 && TargetPos > 6100)
	{
		ASoldier* Soldier_0 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_0->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_0->StateChange(SoldierState::Move);
		Soldier_0->SetActorLocation({ 6150,1050 });

		ASoldier* Soldier_1 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_1->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_1->StateChange(SoldierState::Move);
		Soldier_1->SetActorLocation({ 6250,1050 });

		ASoldier* Soldier_2 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_2->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_2->StateChange(SoldierState::Move);
		Soldier_2->SetActorLocation({ 6350,1050 });

		ASoldier* Soldier_3 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_3->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_3->StateChange(SoldierState::Move);
		Soldier_3->SetActorLocation({ 6550,1050 });

		ASoldier* Soldier_4 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_4->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_4->StateChange(SoldierState::Move);
		Soldier_4->SetActorLocation({ 6650,1050 });

		ASoldier* Soldier_5 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_5->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_5->StateChange(SoldierState::Move);
		Soldier_5->SetActorLocation({ 6750,1050 });

		ASoldier* Soldier_6 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_6->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_6->StateChange(SoldierState::Move);
		Soldier_6->SetActorLocation({ 6950,1050 });

		ASoldier* Soldier_7 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_7->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_7->StateChange(SoldierState::Move);
		Soldier_7->SetActorLocation({ 7050,1050 });

		ASoldier* Soldier_8 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_8->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_8->StateChange(SoldierState::Move);
		Soldier_8->SetActorLocation({ 7150,1050 });

		ASoldier* Soldier_9 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_9->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_9->StateChange(SoldierState::Move);
		Soldier_9->SetActorLocation({ 7350,1050 });

		ASoldier* Soldier_10 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_10->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_10->StateChange(SoldierState::Move);
		Soldier_10->SetActorLocation({ 7450,1050 });

		ASoldier* Soldier_11 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_11->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_11->StateChange(SoldierState::Move);
		Soldier_11->SetActorLocation({ 7550,1050 });

		ASoldier* Soldier_12 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_12->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_12->StateChange(SoldierState::Move);
		Soldier_12->SetActorLocation({ 7750,1050 });

		ASoldier* Soldier_13 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_13->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_13->StateChange(SoldierState::Move);
		Soldier_13->SetActorLocation({ 7850,1050 });

		ASoldier* Soldier_14 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_14->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_14->StateChange(SoldierState::Move);
		Soldier_14->SetActorLocation({ 7950,1050 });

		ASoldier* Soldier_15 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_15->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_15->StateChange(SoldierState::Move);
		Soldier_15->SetActorLocation({ 8150,1050 });

		ASoldier* Soldier_16 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_16->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_16->StateChange(SoldierState::Move);
		Soldier_16->SetActorLocation({ 8225,1050 });

		ASoldier* Soldier_17 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_17->SetPattern(SoldierPattern::KnifeAttack);
		Soldier_17->StateChange(SoldierState::Move);
		Soldier_17->SetActorLocation({ 8350,1050 });

		++SpawnNumber;
	}

	if (SpawnNumber == 11 && TargetPos > 7200)
	{
		ALeaderHelicopter* LeaderHelicopter = GetWorld()->SpawnActor<ALeaderHelicopter>();
		LeaderHelicopter->SetActorLocation({ 7300,1135 });

		AHelicopter* Helicopter_0 = GetWorld()->SpawnActor<AHelicopter>();
		Helicopter_0->SetActorLocation({ 7500,1135 });
		Helicopter_0->IsDependent = true;

		AHelicopter* Helicopter_1 = GetWorld()->SpawnActor<AHelicopter>();
		Helicopter_1->SetActorLocation({ 7700,1135 });
		Helicopter_1->IsDependent = true;

		AHelicopter* Helicopter_2 = GetWorld()->SpawnActor<AHelicopter>();
		Helicopter_2->SetActorLocation({ 7900,1135 });
		Helicopter_2->IsDependent = true;

		AHelicopter* Helicopter_3 = GetWorld()->SpawnActor<AHelicopter>();
		Helicopter_3->SetActorLocation({ 8100,1135 });
		Helicopter_3->IsDependent = true;

		ALeaderHelicopter::HeliList.push_back(Helicopter_0);
		ALeaderHelicopter::HeliList.push_back(Helicopter_1);
		ALeaderHelicopter::HeliList.push_back(Helicopter_2);
		ALeaderHelicopter::HeliList.push_back(Helicopter_3);

		AUncleZombie* UncleZombie_0 = GetWorld()->SpawnActor<AUncleZombie>();
		UncleZombie_0->SetActorLocation({ 6250,1050 });
		UncleZombie_0->StateChange(EnemyZombieState::Move);

		ADoctorZombie* DoctorZombie_0 = GetWorld()->SpawnActor<ADoctorZombie>();
		DoctorZombie_0->SetActorLocation({ 6150,1050 });
		DoctorZombie_0->StateChange(EnemyZombieState::Move);

		AUncleZombie* UncleZombie_1 = GetWorld()->SpawnActor<AUncleZombie>();
		UncleZombie_1->SetActorLocation({ 6050,1000 });
		UncleZombie_1->StateChange(EnemyZombieState::Move);

		ADoctorZombie* DoctorZombie_1 = GetWorld()->SpawnActor<ADoctorZombie>();
		DoctorZombie_1->SetActorLocation({ 5950,1000 });
		DoctorZombie_1->StateChange(EnemyZombieState::Move);

		++SpawnNumber;
	}

	if (SpawnNumber == 12)
	{
		std::vector<UCollision*> Result;
		if (
			!UContentsHelper::ScreenCol->GetCollider()->CollisionCheck(MT3CollisionOrder::Enemy, Result)
			)
		{
			++SpawnNumber;
		}
	}

	if (SpawnNumber == 13)
	{
		AHelicopter* Helicopter_0 = GetWorld()->SpawnActor<AHelicopter>();
		Helicopter_0->SetActorLocation({ 7380,1450 });
		Helicopter_0->Offset = { 0,-300 };
		Helicopter_0->StateChange(HelicopterState::Move);

		AHelicopter* Helicopter_1 = GetWorld()->SpawnActor<AHelicopter>();
		Helicopter_1->SetActorLocation({ 6500,830 });
		Helicopter_1->Offset = { 0,-200 };
		Helicopter_1->StateChange(HelicopterState::Move);

		ASoldier* Soldier_0 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_0->SetActorLocation({ 6600,1300 });
		Soldier_0->StateChange(SoldierState::Move);
		Soldier_0->SetPattern(SoldierPattern::Throw);

		ASoldier* Soldier_1 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_1->SetActorLocation({ 7300,1420 });
		Soldier_1->StateChange(SoldierState::Move);
		Soldier_1->SetPattern(SoldierPattern::Throw);

		ASoldier* Soldier_2 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_2->SetActorLocation({ 6400,1000 });
		Soldier_2->StateChange(SoldierState::Move);
		Soldier_2->SetPattern(SoldierPattern::Throw);

		ASoldier* Soldier_3 = GetWorld()->SpawnActor<ASoldier>();
		Soldier_3->SetActorLocation({ 7500,1520 });
		Soldier_3->StateChange(SoldierState::Move);
		Soldier_3->SetPattern(SoldierPattern::Throw);

		AUncleZombie* UncleZombie_0 = GetWorld()->SpawnActor<AUncleZombie>();
		UncleZombie_0->SetActorLocation({ 6700,1300 });
		UncleZombie_0->StateChange(EnemyZombieState::Move);

		ADoctorZombie* DoctorZombie_0 = GetWorld()->SpawnActor<ADoctorZombie>();
		DoctorZombie_0->SetActorLocation({ 7400,1400 });
		DoctorZombie_0->StateChange(EnemyZombieState::Move);

		++SpawnNumber;
	}
		

	if (SpawnNumber == 14)
	{
		std::vector<UCollision*> Result;
		if (
			!UContentsHelper::ScreenCol->GetCollider()->CollisionCheck(MT3CollisionOrder::Enemy, Result)
			)
		{
			++SpawnNumber;
		}
	}

	if (SpawnNumber == 15)
	{
		AWomanZombie* WomanZombie_0 = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie_0->SetActorLocation({ 7580,1780 });
		WomanZombie_0->StateChange(EnemyZombieState::Lying);

		AWomanZombie* WomanZombie_1 = GetWorld()->SpawnActor<AWomanZombie>();
		WomanZombie_1->SetActorLocation({ 7660,1780 });
		WomanZombie_1->StateChange(EnemyZombieState::Lying);

		AManZombie1* ManZombie1_0 = GetWorld()->SpawnActor<AManZombie1>();
		ManZombie1_0->SetActorLocation({ 7860,1780 });
		ManZombie1_0->StateChange(EnemyZombieState::Lying);

		ADoctorZombie* ADoctorZombie_0 = GetWorld()->SpawnActor<ADoctorZombie>();
		ADoctorZombie_0->SetActorLocation({ 7975,1780 });
		ADoctorZombie_0->StateChange(EnemyZombieState::Lying);
		
		++SpawnNumber;
	}

	if (SpawnNumber == 16)
	{
		std::vector<UCollision*> Result;
		if (
			!UContentsHelper::ScreenCol->GetCollider()->CollisionCheck(MT3CollisionOrder::Enemy, Result)
			)
		{
			++UContentsHelper::CameraManager->CameraMode;
			++SpawnNumber;
		}
	}

	if (SpawnNumber == 17 && TargetPos > 8950.0f)
	{
		AVan* Van_0 = GetWorld()->SpawnActor<AVan>();
		Van_0->SetActorLocation({ 9050,2200 });

		AVan* Van_1 = GetWorld()->SpawnActor<AVan>();
		Van_1->SetActorLocation({ 9280,2200 });

		AVan* Van_2 = GetWorld()->SpawnActor<AVan>();
		Van_2->SetActorLocation({ 9510,2200 });

		AVan* Van_3 = GetWorld()->SpawnActor<AVan>();
		Van_3->SetActorLocation({ 9640,2200 });

		++SpawnNumber;
	}
}
