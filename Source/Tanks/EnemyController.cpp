// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "EnemyController.h"
#include "Enemy.h"
#include "TankCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

AEnemyController::AEnemyController(const class FObjectInitializer& PCIP)
: Super(PCIP)
{
    BlackboardComp = PCIP.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
    
    BehaviorComp = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
}


/**
 Function called to possess an AI controller
 
 - parameter InPawn: the pawn that is being possessed
 - returns: void
 */
void AEnemyController::Possess(class APawn* InPawn)
{
    Super::Possess(InPawn);
    AEnemy* Enemy = Cast<AEnemy>(InPawn);
    if (Enemy && Enemy->EnemyBehavior)
    {
        UBlackboardData* BlackboardData = Enemy->EnemyBehavior->BlackboardAsset;
        BlackboardComp->InitializeBlackboard(*BlackboardData);
        EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
        EnemyLocationID = BlackboardComp->GetKeyID("Destination");
        
        BehaviorComp->StartTree(*Enemy->EnemyBehavior);
    }
}


/**
 Function called to search for an enemy
 
 - parameter void:
 - returns: void
 */
void AEnemyController::SearchForEnemy()
{
    APawn* MyEnemy = GetPawn();
    if (MyEnemy == NULL)
        return;
    
    const FVector MyLoc = MyEnemy->GetActorLocation();
    float BestDistSq = MAX_FLT;
    ATankCharacter* BestPawn = NULL;
    
    for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
    {
        ATankCharacter* TestPawn = Cast<ATankCharacter>(*It);
        if (TestPawn)
        {
            const float DistSq = FVector::Dist(TestPawn->GetActorLocation(), MyLoc);
            bool canSee = LineOfSightTo(TestPawn);
            
            //choose the closest option to the AI that can be seen
            if (DistSq < BestDistSq && canSee)
            {
                BestDistSq = DistSq;
                BestPawn = TestPawn;
            }
        }
    }
    
    if (BestPawn)
    {
        GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Green, BestPawn->GetName());
        SetEnemy(BestPawn);
        
    }
}


/**
 Function called to set the AI controller's enemy
 
 - parameter InPawn: the pawn that is being set as the enemy
 - returns: void
 */
void AEnemyController::SetEnemy(class APawn* InPawn)
{
    BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
    BlackboardComp->SetValue<UBlackboardKeyType_Vector>(EnemyLocationID, InPawn->GetActorLocation());
}


