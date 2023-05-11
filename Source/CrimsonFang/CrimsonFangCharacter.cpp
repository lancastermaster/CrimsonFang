// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrimsonFangCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

ACrimsonFangCharacter::ACrimsonFangCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

/*void ACrimsonFangCharacter::PostInitializeComponents()
{
}*/

void ACrimsonFangCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentGameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	Health = CurrentGameInstance->GetPlayerMaxHealth();
}

void ACrimsonFangCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACrimsonFangCharacter::Attack);
	//PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &ACrimsonFangCharacter::Dodge);
	//PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACrimsonFangCharacter::Interact);
	//PlayerInputComponent->BindAction("Spell", IE_Pressed, this, &ACrimsonFangCharacter::Spell);

	PlayerInputComponent->BindAxis("MoveRight", this, &ACrimsonFangCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACrimsonFangCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ACrimsonFangCharacter::TouchStopped);
}


//////////////////////////////////////////////////////////////////////////
// Input



void ACrimsonFangCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ACrimsonFangCharacter::Attack()
{
	PlayAttackMontage("Slash");
}

void ACrimsonFangCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ACrimsonFangCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}


float ACrimsonFangCharacter::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    if(Health - DamageAmount <= 0.f)
	{
		Health = 0.f;
		//OnDeath();
	}
	else
	{
		Health -= DamageAmount;
	}

	if(bDying)return DamageAmount;

	const float Stunned = FMath::RandRange(0.f,1.f);
	if(Stunned >= StunChance)
	{
		//stun enemy
		PlayHitMontage(FName("React"));
		//SetStunned(true);
	}

    return 0.0f;
}

void ACrimsonFangCharacter::OnDeath()
{
}

void ACrimsonFangCharacter::FinishDeath()
{
}

void ACrimsonFangCharacter::PlayHitMontage(FName Section, float PlayRate)
{
	if(bCanHitReact)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if(AnimInstance)
		{
			if(HitMontage)
			{
				AnimInstance->Montage_Play(HitMontage, PlayRate);
				AnimInstance->Montage_JumpToSection(Section, HitMontage);
			}
		}

		//Reset via AnimNotify in Montage
		bCanHitReact = false;
		bCanAttack = false;
		
	}
}

void ACrimsonFangCharacter::PlayAttackMontage(FName Section, float PlayRate)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if(AnimInstance && AttackMontage)
		{
			if(AttackMontage)
			{
				AnimInstance->Montage_Play(AttackMontage, PlayRate);
				AnimInstance->Montage_JumpToSection(Section, AttackMontage);
			}
		}

		//Reset via AnimNotify in Montage
		bCanAttack = false;
}

void ACrimsonFangCharacter::ResetHitReact()
{
	bCanHitReact = true;
}

void ACrimsonFangCharacter::ResetCanAttack()
{
	bCanHitReact = true;
}
