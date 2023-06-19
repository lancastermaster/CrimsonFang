// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KeyColor.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CRIMSONFANG_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	public:
	protected:
	private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	float PlayerMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	float PlayerDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keys", meta = (AllowPrivateAccess = true))
	TMap<EKeyColor, bool> PlayerKeys;

	public:

	FORCEINLINE float GetPlayerMaxHealth() {return PlayerMaxHealth;}
	FORCEINLINE float GetPlayerDamage(){return PlayerDamage;}
	FORCEINLINE TMap<EKeyColor, bool> GetPlayerKeys() { return PlayerKeys; }

	UFUNCTION(BlueprintCallable)
	void SetPlayerKey(EKeyColor KeyColor, bool bNewBool);
};
