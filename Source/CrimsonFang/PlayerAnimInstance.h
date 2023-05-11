// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CRIMSONFANG_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	public:
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	protected:
	
	private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement",meta = (AllowPrivateAccess = true))
	bool bInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class ACrimsonFangCharacter* Player;
};
