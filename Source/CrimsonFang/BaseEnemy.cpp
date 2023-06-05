// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyController.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "CrimsonFangCharacter.h"

// Sets default values
ABaseEnemy::ABaseEnemy() :

	bCanAttack(true),
	bCanHitReact(true),
	bDying(false),
	bIsActive(true),
	DeathTime(4.f),
	StunChance(.5f)

{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	Health = EnemyStats.MaxHealth;
	EnemyBrain = Cast<AEnemyController>(GetController());
	StartLocation = GetActorLocation();
	
	if(BehaviorTree != nullptr) EnemyBrain->RunBehaviorTree(BehaviorTree);
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetBlackboardValues();
}

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	if(bDying)return DamageAmount;

	if(BloodParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this->GetWorld(),
			BloodParticles,
			GetMesh()->GetSocketLocation(TEXT("Spine2")),
			FRotator(0.f),
			FVector(1.f),
			true
		);
	}
	/*
		spawn blood particles attached to the enemies torso (setup socket)
	*/

	if(Health - DamageAmount <= 0.f)
	{
		Health = 0.f;
		bDying = true;
		OnDeath_Implementation();
	}
	else
	{
		Health -= DamageAmount;
		const float Stunned = FMath::RandRange(0.f,1.f);
		if(Stunned >= StunChance)
		{
			//stun enemy
			if(HitMontage)PlayHitMontage(FName("React"));
			//SetStunned(true);
		}
	}


    return 0.0f;
}

void ABaseEnemy::FinishDeath()
{
	GetMesh()->bPauseAnims = true;

	//Deactivate the enemy's brain/behavior tree.

	GetWorldTimerManager().SetTimer(
		DeathTimer,
		this, 
		&ABaseEnemy::DeactivateEnemy, 
		DeathTime);
}

void ABaseEnemy::PlayHitMontage(FName Section, float PlayRate)
{
	if(bCanHitReact)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if(AnimInstance)
		{
			AnimInstance->Montage_Play(HitMontage, PlayRate);
			AnimInstance->Montage_JumpToSection(Section, HitMontage);
		}

		//Reset via AnimNotify in Montage
		bCanHitReact = false;
		bCanAttack = false;
	}
}

void ABaseEnemy::PlayAttackMontage(FName Section, float PlayRate)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if(AnimInstance && AttackMontage)
		{
			AnimInstance->Montage_Play(AttackMontage, PlayRate);
			AnimInstance->Montage_JumpToSection(Section, AttackMontage);
		}

		//Reset via AnimNotify in Montage
		bCanAttack = false;
		/*
			if(EnemyController)
			{
				EnemyController->GetBlackboardComponent()->SetValueAsBool(FName ("CanAttack"), false);
			}
		*/
}

void ABaseEnemy::DestroyEnemy()
{
	Destroy();
}

void ABaseEnemy::DeactivateEnemy()
{
	SetActorHiddenInGame(true);
	SetActorLocation(StartLocation);
	bIsActive = false;
}

void ABaseEnemy::ReactivateEnemy()
{
	Health = EnemyStats.MaxHealth;
	bDying = false;
	GetMesh()->bPauseAnims = false;
	SetActorHiddenInGame(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	bIsActive = true;
}

void ABaseEnemy::ResetHitReact()
{
	bCanHitReact = true;
	bCanAttack = true;
}

void ABaseEnemy::ResetCanAttack()
{
	bCanAttack = true;
}


void ABaseEnemy::OnDeath_Implementation()
{
	this->GetMovementComponent()->StopMovementImmediately();
	//EnemyBrain.BrainComponent->StopLogic();

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if(AnimInstance)
	{
		AnimInstance->Montage_Play(DeathMontage, 1.f);
		AnimInstance->Montage_JumpToSection(TEXT("Death"), HitMontage);
	}

	AActor* HealthPickup = GetWorld()->SpawnActor<AActor>(HealthPickupClass);
	HealthPickup -> SetActorLocation(
		this->GetActorLocation(),
		false,
		NULL,
		ETeleportType::None
	);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseEnemy::SetBlackboardValues()
{
	ACrimsonFangCharacter* Player = Cast<ACrimsonFangCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	bool bSeesPlayer = EnemyBrain->LineOfSightTo(Player, FVector(0.f), false);

	EnemyBrain->GetBlackboardComponent()->SetValueAsBool(FName("IsDead"), bDying);
	EnemyBrain->GetBlackboardComponent()->SetValueAsBool(FName("SeesPlayer"), bSeesPlayer);
	EnemyBrain->GetBlackboardComponent()->SetValueAsBool(FName("PlayerDead"), Player->GetPlayerDead());

	if(bSeesPlayer)
	{
		EnemyBrain->GetBlackboardComponent()->SetValueAsObject(FName("Player"), Player);
	}
	else
	{
		EnemyBrain->GetBlackboardComponent()->ClearValue(FName("Player"));
	}
}