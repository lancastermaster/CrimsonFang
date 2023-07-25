// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SidescrollingCamera.generated.h"

UCLASS()
class CRIMSONFANG_API ASidescrollingCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASidescrollingCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetPlayerStartingCamera();

	UFUNCTION()
		void OnTriggerOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnConstraintBeginOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnConstraintEndOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

private:
	class USceneComponent* CameraRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		class UBoxComponent* PlayerTriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		class UBoxComponent* CameraConstraintBox;

	bool bFollowPlayer;

	class ACrimsonFangCharacter* PlayerCharacter;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
