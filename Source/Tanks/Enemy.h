// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class TANKS_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy(const class FObjectInitializer&);
    
    UPROPERTY(EditAnywhere, Category = Behavior)
    class UBehaviorTree* EnemyBehavior;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UFUNCTION(BlueprintCallable, Category = "UserMade")
    void fire();
    
    FTimerHandle handleClock;
    void readyToFire();
    bool canFire = true;
	
};
