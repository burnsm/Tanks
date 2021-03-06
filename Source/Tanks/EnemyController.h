// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
    AEnemyController(const class FObjectInitializer& PCIP);
    
    UPROPERTY(transient)
    UBlackboardComponent* BlackboardComp;
    
    UPROPERTY(transient)
    UBehaviorTreeComponent* BehaviorComp;
    
    virtual void Possess(class APawn *InPawn);
    
    void SetEnemy(class APawn *InPawn);
    
    UFUNCTION(BlueprintCallable, Category = Behavior)
    void SearchForEnemy();
    
protected:
    uint8 EnemyKeyID;
    uint8 EnemyLocationID;
	
	
};
