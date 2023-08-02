// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KeyColor.h"
#include "MainGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSaveInfo
{
	GENERATED_BODY()


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
		float PlayerMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
		float PlayerDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
		TMap<EKeyColor, bool> PlayerKeys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
		FVector PlayerSpawnVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
		FString LevelName;
};

/**
 * 
 */
UCLASS()
class CRIMSONFANG_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game", meta = (AllowPrivateAccess = true))
		struct FSaveInfo PlayerSaveInfo;
		
		UFUNCTION(BlueprintCallable)
		void PullSaveInfo();

		UFUNCTION(BlueprintCallable)
		void FillSaveInfo();

		UFUNCTION(BlueprintCallable)
		void SavePlayerInfo();

		UFUNCTION(BlueprintCallable)
		void LoadPlayerInfo();

	protected:

	private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game", meta = (AllowPrivateAccess = true))
	class UCFSaveGame* CurrentSaveGame;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	float PlayerMaxHealth = 100.f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	//float PlayerCurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	float PlayerDamage = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keys", meta = (AllowPrivateAccess = true))
	TMap<EKeyColor, bool> PlayerKeys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
		FVector PlayerSpawnVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
		FString LevelName = TEXT("BuriedCemetary");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
		FString SaveSlotName;

	public:

	FORCEINLINE float GetPlayerMaxHealth() {return PlayerMaxHealth;}
	FORCEINLINE float GetPlayerDamage(){return PlayerDamage;}
	FORCEINLINE TMap<EKeyColor, bool> GetPlayerKeys() { return PlayerKeys; }
	FORCEINLINE FString GetLevelName() { return LevelName; }
	FORCEINLINE UCFSaveGame* GetCurrentSaveGame() { return CurrentSaveGame; }

	UFUNCTION(BlueprintCallable)
	void SetPlayerKey(EKeyColor KeyColor, bool bNewBool);

	UFUNCTION(BlueprintCallable)
	void SetLevelName(FString NewLevelName) { LevelName = NewLevelName; }
};
