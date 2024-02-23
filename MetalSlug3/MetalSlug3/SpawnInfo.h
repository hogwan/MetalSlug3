#pragma once

#define SpawnAllActor ADoctor* Doctor_0 = SpawnActor<ADoctor>();\
Doctor_0->SetActorLocation({ 300,1000 });\
Doctor_0->StateChange(HumanState::Run);\
\
ADoctor* Doctor_1 = SpawnActor<ADoctor>();\
Doctor_1->SetActorLocation({ 340,1000 });\
Doctor_1->StateChange(HumanState::Run);\
\
ADoctor* Doctor_2 = SpawnActor<ADoctor>();\
Doctor_2->SetActorLocation({ 380,1000 });\
Doctor_2->StateChange(HumanState::Run);\
\
ADoctor* Doctor_3 = SpawnActor<ADoctor>();\
Doctor_3->SetActorLocation({ 400,1000 });\
Doctor_3->StateChange(HumanState::Run);\
\
ADoctor* Doctor_4 = SpawnActor<ADoctor>();\
Doctor_4->SetActorLocation({ 450,1000 });\
Doctor_4->StateChange(HumanState::Run);\
\
ADoctor* Doctor_5 = SpawnActor<ADoctor>();\
Doctor_4->SetActorLocation({ 1200,1000 });\
Doctor_4->StateChange(HumanState::Run);\
\
AManZombie2* AManZombie2_0 = SpawnActor<AManZombie2>();\
AManZombie2_0->SetActorLocation({1240,1000});\
Doctor_4->StateChange(HumanState::Move);\
\