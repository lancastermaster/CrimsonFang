// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "CFSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UMainGameInstance::PullSaveInfo()
{
	PlayerMaxHealth = PlayerSaveInfo.PlayerMaxHealth;
	PlayerDamage = PlayerSaveInfo.PlayerDamage;
	PlayerSpawnVector = PlayerSaveInfo.PlayerSpawnVector;
	LevelName = PlayerSaveInfo.LevelName;
		for (auto Pair : PlayerSaveInfo.PlayerKeys)
		{
			PlayerKeys.Add(Pair);
		}
}

void UMainGameInstance::FillSaveInfo()
{
	PlayerSaveInfo.PlayerMaxHealth = PlayerMaxHealth;
	PlayerSaveInfo.PlayerDamage = PlayerDamage;
	PlayerSaveInfo.LevelName = LevelName;
	for (auto Pair : PlayerKeys)
	{
		PlayerSaveInfo.PlayerKeys.Add(Pair);
	}
}

void UMainGameInstance::SavePlayerInfo()
{
	if (CurrentSaveGame == nullptr) CurrentSaveGame = Cast<UCFSaveGame>(UGameplayStatics::CreateSaveGameObject(UCFSaveGame::StaticClass()));
	
	bool bSaveExists = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);
	//if (bSaveExists)
	//{

	FillSaveInfo();
		CurrentSaveGame->SetSaveInfo(PlayerSaveInfo);
		UGameplayStatics::AsyncSaveGameToSlot(CurrentSaveGame, SaveSlotName, 0);
		//UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlotName, 0);
	//}
}

void UMainGameInstance::LoadPlayerInfo()
{
	CurrentSaveGame = Cast<UCFSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	if (!CurrentSaveGame)
	{
		UCFSaveGame* LoadedGame = Cast<UCFSaveGame>(UGameplayStatics::CreateSaveGameObject(UCFSaveGame::StaticClass()));
		CurrentSaveGame = LoadedGame;
	}

	PlayerSaveInfo = CurrentSaveGame->GetSaveInfo();
	PullSaveInfo();
}

void UMainGameInstance::SetPlayerKey(EKeyColor KeyColor, bool bNewBool)
{
	PlayerKeys.Add(KeyColor, bNewBool);
}
