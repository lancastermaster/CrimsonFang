// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseEnemy.h"

AEnemyController::AEnemyController()
{
    BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
    check(BlackboardComp);

    BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
    check(BehaviorTreeComp);
}

void AEnemyController::OnPossess(APawn *InPawn)
{
     Super::OnPossess(InPawn);

    if(InPawn == nullptr)return;

    ABaseEnemy* Enemy = Cast<ABaseEnemy>(InPawn);
    if(Enemy)
    {
        if(Enemy->GetBehaviorTree())
        {
            BlackboardComp->InitializeBlackboard(*(Enemy->GetBehaviorTree()->BlackboardAsset));
        }
    }
}
