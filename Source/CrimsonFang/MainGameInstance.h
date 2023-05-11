// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

	public:

	FORCEINLINE float GetPlayerMaxHealth() {return PlayerMaxHealth;}
};
