// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "KeyColor.h"
#include "MainGameInstance.h"
#include "CFSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CRIMSONFANG_API UCFSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	struct FSaveInfo SaveInfo;

public:

	FSaveInfo GetSaveInfo() { return SaveInfo; }

	void SetSaveInfo(FSaveInfo NewSaveInfo) { SaveInfo = NewSaveInfo; }

};
