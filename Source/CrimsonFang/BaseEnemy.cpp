// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Animation/AnimMontage.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyController.h"

// Sets default values
ABaseEnemy::ABaseEnemy() :

	bCanAttack(true),
	bCanHitReact(true),
	bDying(false),
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
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	if(Health - DamageAmount <= 0.f)
	{
		Health = 0.f;
		OnDeath_Implementation();
	}
	else
	{
		Health -= DamageAmount;
	}

	if(bDying)return DamageAmount;

	const float Stunned = FMath::RandRange(0.f,1.f);
	if(Stunned >= StunChance)
	{
		//stun enemy
		PlayHitMontage(FName("React"));
		//SetStunned(true);
	}

    return 0.0f;
}

void ABaseEnemy::FinishDeath()
{
	GetMesh()->bPauseAnims = true;

	GetWorldTimerManager().SetTimer(
		DeathTimer,
		this, 
		&ABaseEnemy::DestroyEnemy, 
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

void ABaseEnemy::ResetHitReact()
{
	bCanHitReact = true;
}

void ABaseEnemy::ResetCanAttack()
{
	bCanAttack = true;
}

void ABaseEnemy::OnDeath_Implementation()
{
	
}
