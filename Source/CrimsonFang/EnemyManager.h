// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class CRIMSONFANG_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetAllLevelEnemies();

	UFUNCTION(BlueprintCallable)
	void ReactivateAllDeadEnemies();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TMap<int, class ABaseEnemy*> LevelEnemies;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
