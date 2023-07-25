// Fill out your copyright notice in the Description page of Project Settings.


#include "SidescrollingCamera.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "CrimsonFangCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASidescrollingCamera::ASidescrollingCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));
	RootComponent = CameraRoot;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 900.f;
	CameraBoom->SocketOffset.Z = 75.f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 1.f;
	CameraBoom->CameraLagMaxDistance = 200.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);


	PlayerTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Player Trigger Box"));
	PlayerTriggerBox->SetupAttachment(CameraRoot);

	CameraConstraintBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Camera Constraint Box"));
	CameraConstraintBox->SetupAttachment(CameraRoot);
}

// Called when the game starts or when spawned
void ASidescrollingCamera::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter = Cast<ACrimsonFangCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	PlayerTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASidescrollingCamera::OnTriggerOverlap);
	CameraConstraintBox->OnComponentBeginOverlap.AddDynamic(this, &ASidescrollingCamera::OnConstraintBeginOverlap);
	CameraConstraintBox->OnComponentEndOverlap.AddDynamic(this, &ASidescrollingCamera::OnConstraintEndOverlap);

	FTimerHandle InitialCameraHandle;
	GetWorldTimerManager().SetTimer(InitialCameraHandle, this, &ASidescrollingCamera::SetPlayerStartingCamera, .1f, false);
}

// Called every frame
void ASidescrollingCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bFollowPlayer)
	{
		FVector StartPosition = Camera->GetSocketLocation("Camera");
		FVector PlayerPosition = PlayerCharacter->GetActorLocation();

		//FMath::FInterpConstantTo(StartPosition.Y, PlayerPosition.Y, DeltaTime, 30.f);
		//FMath::FInterpConstantTo(StartPosition.Z, PlayerPosition.Z, DeltaTime, 30.f);

		/*Camera->SetWorldLocation(
			FMath::VInterpConstantTo(StartPosition, FVector(StartPosition.X, PlayerPosition.Y, PlayerPosition.Z + 200.f), DeltaTime, 1000.f));*/

		//Camera->SetWorldLocation(FVector(StartPosition.X, PlayerPosition.Y, PlayerPosition.Z + 100.f));
	}

}

void ASidescrollingCamera::SetPlayerStartingCamera()
{
	TArray<UPrimitiveComponent*> OverlappingComponents;

	PlayerCharacter->GetOverlappingComponents(OverlappingComponents);

	for (UPrimitiveComponent* Comp : OverlappingComponents)
	{
		if (Comp == PlayerTriggerBox)
		{
			//Player->SetCurrentCamera(Camera);

			auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			PlayerController->SetViewTargetWithBlend(this);
		}

		if (Comp == CameraConstraintBox)
		{
			CameraBoom->AttachTo(PlayerCharacter->GetRootComponent(), NAME_None, EAttachLocation::KeepRelativeOffset);
		}
	}
}

void ASidescrollingCamera::OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweep, const FHitResult& SweepResult)
{
	if (OtherActor == PlayerCharacter)
	{
		//Player->SetCurrentCamera(Camera);

		auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->SetViewTargetWithBlend(this, .5f);
	}
}

void ASidescrollingCamera::OnConstraintBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweep, const FHitResult& SweepResult)
{
	if(OtherActor == PlayerCharacter) bFollowPlayer = true;

	FVector StartPosition = Camera->GetSocketLocation("Camera");
	FVector PlayerPosition = PlayerCharacter->GetActorLocation();

	//Camera->SetWorldLocation(FVector(StartPosition.X, PlayerPosition.Y, PlayerPosition.Z));

	CameraBoom->AttachTo(PlayerCharacter->GetRootComponent(), NAME_None, EAttachLocation::KeepRelativeOffset);
}

void ASidescrollingCamera::OnConstraintEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == PlayerCharacter) bFollowPlayer = false;

	CameraBoom->DetachFromParent();
}

