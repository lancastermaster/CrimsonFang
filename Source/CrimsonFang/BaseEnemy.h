// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IDamageableInterface.h"
#include "BaseEnemy.generated.h"

USTRUCT(BlueprintType)
struct FEnemyInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
    float SpeedMultiplier;
};

UCLASS()
class CRIMSONFANG_API ABaseEnemy : public ACharacter, public IIDamageableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnDeath();

	UFUNCTION(BlueprintCallable)
	void FinishDeath();

	void PlayHitMontage(FName Section, float PlayRate = 1.0f);

	UFUNCTION(BlueprintCallable)
	void PlayAttackMontage(FName Section, float PlayRate = 1.0f);

	void DestroyEnemy();

	UFUNCTION(BlueprintCallable)
	void DeactivateEnemy();

	UFUNCTION(BlueprintCallable)
	void ResetHitReact();

	UFUNCTION(BlueprintCallable)
	void ResetCanAttack();

	void SetBlackboardValues();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	FEnemyInfo EnemyStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	bool bCanAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	bool bCanHitReact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	bool bDying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	float DeathTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	float StunChance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Manager", meta = (AllowPrivateAccess = true))
	int ManagerIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Navigation", meta = (AllowPrivateAccess = true))
	FVector StartLocation;

	FTimerHandle DeathTimer;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = true))
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	class AEnemyController* EnemyBrain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	class UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	UAnimMontage* HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	TArray<FName> AttackMontageSections;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	class UParticleSystem* BloodParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> HealthPickupClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ReactivateEnemy();

	FORCEINLINE bool GetIsActive() {return bIsActive;}
	FORCEINLINE int GetManagerIndex() {return ManagerIndex;}
	FORCEINLINE void SetManagerIndex(float NewIndex) {ManagerIndex = NewIndex;}
	FORCEINLINE UBehaviorTree* GetBehaviorTree() {return BehaviorTree;}
};
