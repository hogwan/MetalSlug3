#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum MT3RenderOrder
{
	Map,
	Projectile,
	Enemy,
	LowerBody,
	UpperBody,
	ZombieArm,
	AllBody,
	Particle,
	Front,

};
enum class MT3CollisionOrder
{
	PlayerBullet,
	EnemyProjectile,
	ZombieProjectile,
	Enemy,
	Player,
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

class UContentsHelper
{
public:
	static UWindowImage* ColMapImage;
	static class Marco* Player;
private:
	UContentsHelper();
	~UContentsHelper();
};

