// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hazard.generated.h"

UCLASS()
class CRIMSONFANG_API AHazard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHazard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActivateHazard();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DeactivateHazard();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bCanBeActivated;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
