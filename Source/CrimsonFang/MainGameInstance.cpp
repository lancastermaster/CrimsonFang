// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

void UMainGameInstance::SetPlayerKey(EKeyColor KeyColor, bool bNewBool)
{
	PlayerKeys.Add(KeyColor, bNewBool);
}
