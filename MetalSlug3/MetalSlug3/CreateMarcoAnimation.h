#pragma once

#define CreateMarcoAnimation \
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_Idle_Right", "Marco_UpperBody.png", 0, 5, 0.12f, true);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_Move_Right", "Marco_UpperBody.png", 6, 17, 0.05f, true);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_Jump_Right", "Marco_UpperBody.png", 18, 25, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_ForwardJump_Right", "Marco_UpperBody.png", 26, 31, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_Shoot_Right", "Marco_UpperBody.png", 32, 41, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_ForwardJumpShoot_Right", "Marco_UpperBody.png", 42, 51, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_Throw_Right", "Marco_UpperBody.png", 52, 57, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_KnifeAttack1_Right", "Marco_UpperBody.png", 58, 63, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_KnifeAttack2_Right", "Marco_UpperBody.png", 64, 69, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimNormalToUp_Right", "Marco_UpperBody.png", 70, 71, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimUpToNormal_Right", "Marco_UpperBody.png", 72, 73, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimUp_Right", "Marco_UpperBody.png", 74, 79, 0.12f, true);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimUpShoot_Right", "Marco_UpperBody.png", 80, 89, 0.05f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimNormalToDown_Right", "Marco_UpperBody.png", 90, 92, 0.05f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimDownToNormal_Right", "Marco_UpperBody.png", 93, 95, 0.05f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimDownShoot_Right", "Marco_UpperBody.png", 96, 101, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_Idle_Right", "Marco_UpperBody.png", 102, 107, 0.12f, true);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_Move_Right", "Marco_UpperBody.png", 108, 119, 0.05f, true);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_Jump_Right", "Marco_UpperBody.png", 120, 127, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_ForwardJump_Right", "Marco_UpperBody.png", 128, 133, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_Shoot_Right", "Marco_UpperBody.png", 134, 137, 0.1f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_ForwardJumpShoot_Right", "Marco_UpperBody.png", 134, 137, 0.1f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_Shoot_Right", "Marco_UpperBody.png", 138, 147, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_ForwardJumpShoot_Right", "Marco_UpperBody.png", 138, 147, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_Throw_Right", "Marco_UpperBody.png", 148, 153, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_KnifeAttack1_Right", "Marco_UpperBody.png", 154, 159, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_KnifeAttack2_Right", "Marco_UpperBody.png", 160, 165, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimNormalToUp_Right", "Marco_UpperBody.png", 166, 167, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimUpToNormal_Right", "Marco_UpperBody.png", 168, 169, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimUp_Right", "Marco_UpperBody.png", 170, 175, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_AimUpShoot_Right", "Marco_UpperBody.png", 176, 179, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimUpShoot_Right", "Marco_UpperBody.png", 180, 185, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_AimNormalToUpShoot_Right", "Marco_UpperBody.png", 186, 187, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_AimUpToNormalShoot_Right", "Marco_UpperBody.png", 188, 189, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimNormalToDown_Right", "Marco_UpperBody.png", 190, 192, 0.05f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimDownToNormal_Right", "Marco_UpperBody.png", 193, 195, 0.05f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_AimDownShoot_Right", "Marco_UpperBody.png", 196, 199, 0.1f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimDownShoot_Right", "Marco_UpperBody.png", 200, 206, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_AimNormalToDownShoot_Right", "Marco_UpperBody.png", 207, 208, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_AimDownToNormalShoot_Right", "Marco_UpperBody.png", 209, 210, 0.12f, false);\
\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_Idle_Left", "Marco_UpperBody.png", 220, 225, 0.12f, true);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_Move_Left", "Marco_UpperBody.png", 226, 237, 0.05f, true);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_Jump_Left", "Marco_UpperBody.png", 238, 245, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_ForwardJump_Left", "Marco_UpperBody.png", 246, 251, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_Shoot_Left", "Marco_UpperBody.png", 252, 261, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_ForwardJumpShoot_Left", "Marco_UpperBody.png", 262, 271, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_Throw_Left", "Marco_UpperBody.png", 272, 277, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_KnifeAttack1_Left", "Marco_UpperBody.png", 278, 283, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_KnifeAttack2_Left", "Marco_UpperBody.png", 284, 289, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimNormalToUp_Left", "Marco_UpperBody.png", 290, 291, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimUpToNormal_Left", "Marco_UpperBody.png", 292, 293, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimUp_Left", "Marco_UpperBody.png", 294, 299, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimUpShoot_Left", "Marco_UpperBody.png", 300, 309, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimNormalToDown_Left", "Marco_UpperBody.png", 310, 312, 0.05f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimDownToNormal_Left", "Marco_UpperBody.png", 313, 315, 0.05f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Pistol_UpperBody_AimDownShoot_Left", "Marco_UpperBody.png", 316, 321, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_Idle_Left", "Marco_UpperBody.png", 322, 327, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_Move_Left", "Marco_UpperBody.png", 328, 339, 0.05f, true);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_Jump_Left", "Marco_UpperBody.png", 340, 347, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_ForwardJump_Left", "Marco_UpperBody.png", 348, 353, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_Shoot_Left", "Marco_UpperBody.png", 354, 357, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_ForwardJumpShoot_Left", "Marco_UpperBody.png", 354, 357, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_Shoot_Left", "Marco_UpperBody.png", 358, 367, 0.1f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_ForwardJumpShoot_Left", "Marco_UpperBody.png", 358, 367, 0.1f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_Throw_Left", "Marco_UpperBody.png", 368, 373, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_KnifeAttack1_Left", "Marco_UpperBody.png", 374, 379, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_KnifeAttack2_Left", "Marco_UpperBody.png", 380, 385, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimNormalToUp_Left", "Marco_UpperBody.png", 386, 387, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimUpToNormal_Left", "Marco_UpperBody.png", 388, 389, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimUp_Left", "Marco_UpperBody.png", 390, 395, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_AimUpShoot_Left", "Marco_UpperBody.png", 396, 399, 0.1f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimUpShoot_Left", "Marco_UpperBody.png", 400, 405, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_AimNormalToUpShoot_Left", "Marco_UpperBody.png", 406, 407, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_AimUpToNormalShoot_Left", "Marco_UpperBody.png", 408, 409, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimNormalToDown_Left", "Marco_UpperBody.png", 410, 412, 0.05f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimDownToNormal_Left", "Marco_UpperBody.png", 413, 415, 0.05f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_AimDownShoot_Left", "Marco_UpperBody.png", 416, 419, 0.1f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("Rifle_UpperBody_AimDownShoot_Left", "Marco_UpperBody.png", 420, 426, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_AimNormalToDownShoot_Left", "Marco_UpperBody.png", 427, 428, 0.12f, false);\
Renderer[static_cast<int>(BodyRenderer::UpperBody)]->CreateAnimation("HeavyMachineGun_UpperBody_AimDownToNormalShoot_Left", "Marco_UpperBody.png", 429, 430, 0.12f, false);\
\
Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CreateAnimation("LowerBody_Idle_Right", "Marco_LowerBody.png", 0, 0, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CreateAnimation("LowerBody_Move_Right", "Marco_LowerBody.png", 1, 12, 0.05f, true);\
Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CreateAnimation("LowerBody_Jump_Right", "Marco_LowerBody.png", 13, 20, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CreateAnimation("LowerBody_ForwardJump_Right", "Marco_LowerBody.png", 21, 26, 0.12f, false);\
\
Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CreateAnimation("LowerBody_Idle_Left", "Marco_LowerBody.png", 30, 30, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CreateAnimation("LowerBody_Move_Left", "Marco_LowerBody.png", 31, 42, 0.05f, true);\
Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CreateAnimation("LowerBody_Jump_Left", "Marco_LowerBody.png", 43, 50, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::LowerBody)]->CreateAnimation("LowerBody_ForwardJump_Left", "Marco_LowerBody.png", 51, 56, 0.12f, false);\
\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_Intro_Right", "Marco_AllBody.png", 0, 2, 0.02f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_Outro_Right", "Marco_AllBody.png", 3, 5, 0.02f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_Idle_Right", "Marco_AllBody.png", 6, 11, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_Move_Right", "Marco_AllBody.png", 12, 18, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_Shoot_Right", "Marco_AllBody.png", 19, 28, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_Throw_Right", "Marco_AllBody.png", 29, 34, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_KnifeAttack1_Right", "Marco_AllBody.png", 35, 41, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_KnifeAttack2_Right", "Marco_AllBody.png", 42, 47, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Ceremony", "Marco_AllBody.png", 48, 53, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_Intro_Right", "Marco_AllBody.png", 54, 56, 0.02f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_Outro_Right", "Marco_AllBody.png", 57, 59, 0.02f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_Idle_Right", "Marco_AllBody.png", 60, 65, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_Move_Right", "Marco_AllBody.png", 66, 72, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("HeavyMachineGun_AllBody_Crouch_Shoot_Right", "Marco_AllBody.png", 73, 76, 0.1f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_Shoot_Right", "Marco_AllBody.png", 77, 86, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_Throw_Right", "Marco_AllBody.png", 87, 92, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_KnifeAttack1_Right", "Marco_AllBody.png", 93, 99, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_KnifeAttack2_Right", "Marco_AllBody.png", 100, 105, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Ceremony", "Marco_AllBody.png", 106, 111, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("AllBody_ElephantSlug_Idle", "Marco_AllBody.png", 112, 117, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("AllBody_ElephantSlug_Move", "Marco_AllBody.png", 118, 125, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("AllBody_Death_Right", "Marco_AllBody.png", 126, 144, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("AllBody_DeathInAir_Right", "Marco_AllBody.png", 145, 154, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("AllBody_DeathByKnife_Right", "Marco_AllBody.png", 155, 173, 0.08f, false);\
\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_TransformToZombie_Intro_Right", "Marco_AllBody.png", 174, 176, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_TransformToZombie_Falling_Right", "Marco_AllBody.png", 177, 186, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_TransformToZombie_Rising_Right", "Marco_AllBody.png", 187, 234, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_Idle_Right", "Marco_AllBody.png", 235, 246, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_Move_Right", "Marco_AllBody.png", 247, 270, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_Turn_Right", "Marco_AllBody.png", 271, 286, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_AimUpTurn_Right", "Marco_AllBody.png", 287, 302, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_Jump_Right", "Marco_AllBody.png", 303, 318, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_Vomit_Right", "Marco_AllBody.png", 319, 365, 0.06f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_Death_Right", "Marco_AllBody.png", 366, 445, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_DeathInAir_Right", "Marco_AllBody.png", 446, 460, 0.08f, false);\
\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_Intro_Left", "Marco_AllBody.png", 470, 472, 0.02f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_Outro_Left", "Marco_AllBody.png", 473, 475, 0.02f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_Idle_Left", "Marco_AllBody.png", 476, 481, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_Move_Left", "Marco_AllBody.png", 482, 488, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_Shoot_Left", "Marco_AllBody.png", 489, 498, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_Throw_Left", "Marco_AllBody.png", 499, 504, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_KnifeAttack1_Left", "Marco_AllBody.png", 505, 511, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Pistol_AllBody_Crouch_KnifeAttack2_Left", "Marco_AllBody.png", 512, 517, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_Intro_Left", "Marco_AllBody.png", 524, 526, 0.02f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_Outro_Left", "Marco_AllBody.png", 527, 529, 0.02f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_Idle_Left", "Marco_AllBody.png", 530, 535, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_Move_Left", "Marco_AllBody.png", 536, 542, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("HeavyMachineGun_AllBody_Crouch_Shoot_Left", "Marco_AllBody.png", 543, 546, 0.1f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_Shoot_Left", "Marco_AllBody.png", 547, 556, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_Throw_Left", "Marco_AllBody.png", 557, 562, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_KnifeAttack1_Left", "Marco_AllBody.png", 563, 569, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Rifle_AllBody_Crouch_KnifeAttack2_Left", "Marco_AllBody.png", 570, 575, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("AllBody_Death_Left", "Marco_AllBody.png", 596, 614, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("AllBody_DeathInAir_Left", "Marco_AllBody.png", 615, 624, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("AllBody_DeathByKnife_Left", "Marco_AllBody.png", 625, 643, 0.08f, false);\
\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_TransformToZombie_Intro_Left", "Marco_AllBody.png", 644, 646, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_TransformToZombie_Falling_Left", "Marco_AllBody.png", 647, 656, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_TransformToZombie_Rising_Left", "Marco_AllBody.png", 657, 704, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_Idle_Left", "Marco_AllBody.png", 705, 716, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_Move_Left", "Marco_AllBody.png", 717, 740, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_Turn_Left", "Marco_AllBody.png", 741, 756, 0.03f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_AimUpTurn_Left", "Marco_AllBody.png", 757, 772, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_Jump_Left", "Marco_AllBody.png", 773, 788, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_Vomit_Left", "Marco_AllBody.png", 789, 835, 0.06f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_Death_Left", "Marco_AllBody.png", 836, 915, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::AllBody)]->CreateAnimation("Zombie_AllBody_DeathInAir_Left", "Marco_AllBody.png", 916, 930, 0.08f, false);\
\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Idle_Right", "Marco_ZombieArm.png", 0, 11, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Move_Right", "Marco_ZombieArm.png", 12, 35, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Jump_Right", "Marco_ZombieArm.png", 36, 51, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Shoot_Right", "Marco_ZombieArm.png", 52, 61, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_AimUpToNormal_Right", "Marco_ZombieArm.png", 62, 63, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_AimNormalToUp_Right", "Marco_ZombieArm.png", 64, 65, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Idle_AimUp_Right", "Marco_ZombieArm.png", 70, 81, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Move_AimUp_Right", "Marco_ZombieArm.png", 82, 105, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Jump_AimUp_Right", "Marco_ZombieArm.png", 106, 121, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Shoot_AimUp_Right", "Marco_ZombieArm.png", 122, 131, 0.08f, false);\
\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Idle_Left", "Marco_ZombieArm.png", 140, 151, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Move_Left", "Marco_ZombieArm.png", 152, 175, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Jump_Left", "Marco_ZombieArm.png", 176, 191, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Shoot_Left", "Marco_ZombieArm.png", 192, 201, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_AimUpToNormal_Left", "Marco_ZombieArm.png", 202, 203, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_AimNormalToUp_Left", "Marco_ZombieArm.png", 204, 205, 0.08f, false);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Idle_AimUp_Left", "Marco_ZombieArm.png", 210, 221, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Move_AimUp_Left", "Marco_ZombieArm.png", 222, 245, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Jump_AimUp_Left", "Marco_ZombieArm.png", 246, 261, 0.08f, true);\
Renderer[static_cast<int>(BodyRenderer::ZombieArm)]->CreateAnimation("ZombieArm_Shoot_AimUp_Left", "Marco_ZombieArm.png", 262, 271, 0.08f, false);







