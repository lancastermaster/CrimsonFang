// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "CrimsonFangCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
    if(Player == nullptr) Player = Cast<ACrimsonFangCharacter>(TryGetPawnOwner());

    if(Player)
    {
        FVector Velocity{Player -> GetVelocity()};
        Velocity.Z = 0.f;
        Speed = Velocity.Size();

        bInAir = Player->GetMovementComponent()->IsFalling();
    }
}
