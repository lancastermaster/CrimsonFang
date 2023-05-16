// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Kismet/GameplayStatics.h"
#include "BaseEnemy.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	GetAllLevelEnemies();
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyManager::ReactivateAllDeadEnemies()
{
	for(auto Entry : LevelEnemies)
	{
		ABaseEnemy* Enemy = Cast<ABaseEnemy>(Entry.Value);
		if(Enemy)
		{
			if(Enemy->GetIsActive() == false)Enemy->ReactivateEnemy();
		}
	}
}

void AEnemyManager::GetAllLevelEnemies()
{
	//get an array of all enemies in the level
	//called at the start
	TArray<AActor*> EnemiesInLevel;
	
	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		ABaseEnemy::StaticClass(),
		EnemiesInLevel
		);

	LevelEnemies.Empty();

	for(AActor* Entry : EnemiesInLevel)
	{
		ABaseEnemy* Enemy = Cast<ABaseEnemy>(Entry);
		if(Enemy)
		{
			Enemy->SetManagerIndex(EnemiesInLevel.Find(Enemy));
			LevelEnemies.Add(Enemy->GetManagerIndex(), Enemy);
		}
	}
}