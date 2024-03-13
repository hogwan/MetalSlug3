#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>
#include "ScreenCollision.h"

enum MT3RenderOrder
{
	Back,
	Map,
	BossMap,
	MonoEye_Back,
	MonoEye_Mid,
	BossMapSphere,
	Van,
	UFO_BackBody,
	UFO_Body,
	Enemy,
	UFO_AncientCharactor,
	Monolith_0,
	Monolith_1,
	Monolith_2,
	Monolith_3,
	Monolith_4,
	Monolith_5,
	UFO_Lazer,
	UFO_LazerGroundEffect,
	Propeller,
	Projectile,
	LowerBody,
	UpperBody,
	ZombieArm,
	AllBody,
	MonoEye_Front,
	Item,
	Particle,
	Front,
	UI,

};
enum class MT3CollisionOrder
{
	PlayerBullet,
	EnemyProjectile,
	ZombieProjectile,
	Enemy,
	Player,
	Human,
	Screen,
	Detect,
	CameraSwitch,
	EnemyKnife,
	PlayerKnife,
	Lazer,
	Monoliths,
	Boss,
	TiedNPC,
	Item,
	Flame,
};

enum class EActorDir
{
	Left,
	Right,
};

enum class EGunType
{
	Pistol,
	Rifle,
};

enum class EGunList
{
	Pistol,
	HeavyMachineGun,
	FlameShot,
	ShotGun,
	RocketLauncher,
	IronLizard,
};

enum class UpperBodyState
{
	None,
	CameraFreeMove,
	FreeMove,
	Idle,
	Move,
	Jump,
	ForwardJump,
	Shoot,
	ForwardJumpShoot,
	Throw,
	KnifeAttack1,
	KnifeAttack2,
	AimNormalToUp,
	AimUpToNormal,
	AimUp,
	AimUpShoot,
	AimNormalToDown,
	AimDownToNormal,
	AimDownShoot,
	AimNormalToUpShoot,
	AimUpToNormalShoot,
	AimNormalToDownShoot,
	AimDownToNormalShoot,
};

enum class LowerBodyState
{
	None,
	Idle,
	Move,
	Jump,
	ForwardJump,
};

enum class AllBodyState
{
	None,
	Crouch_Intro,
	Crouch_Outro,
	Crouch_Idle,
	Crouch_Move,
	Crouch_Shoot_HeavyMachineGun,
	Crouch_Shoot,
	Crouch_Throw,
	Crouch_KnifeAttack1,
	Crouch_KnifeAttack2,
	Ceremony,
	ElephantSlug_Idle,
	ElephantSlug_Move,
	Death,
	DeathInAir,
	DeathByKnife,
	TransformToZombie_Intro,
	TransformToZombie_Falling,
	TransformToZombie_Rising,
	Zombie_Idle,
	Zombie_Move,
	Zombie_Turn,
	Zombie_AimupTurn,
	Zombie_Jump,
	Zombie_Vomit,
	Zombie_Death,
	Zombie_DeathInAir,

};

enum class ZombieArmState
{
	None,
	Idle,
	Idle_AimUp,
	Move,
	Move_AimUp,
	Jump,
	Jump_AimUp,
	AimNormalToUp,
	AimUpToNormal,
	Shoot,
	Shoot_AimUp,
};

enum class EnemyZombieState
{
	None,
	Lying,
	Idle,
	Move,
	Turn,
	Stun,
	Attack,
	Death,
	Falling,
};

enum class HumanState
{
	None,
	Idle,
	Move,
	Run,
	Shock,
	Death,
};

enum class SoldierState
{
	None,
	Idle,
	Move,
	Throw,
	KnifeAttack,
	Death,
};

enum class SoldierPattern
{
	KnifeAttack,
	Throw,
	RunAway,
};

enum class HelicopterState
{
	None,
	Move,
	Aiming,
	Shoot,
	Death,
};

enum class ZPos
{
	Back,
	Front,
	Mid,
};

class UContentsHelper
{
public:
	static UWindowImage* ColMapImage;
	static UWindowImage* CrouchColMapImage;
	static AScreenCollision* ScreenCol;
	static class Marco* Player;
	static class CameraManager* CameraManager;
	static class UEngineSoundPlayer BGMPlayer;
	static int Life;
	static int Score;
	static bool GameEnd;
private:
	UContentsHelper();
	~UContentsHelper();
};

