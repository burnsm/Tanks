// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Enemy.h"
#include "EnemyController.h"
#include "Projectile.h"


// Sets default values
AEnemy::AEnemy(const class FObjectInitializer&)
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    AIControllerClass = AEnemyController::StaticClass();
    
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
}


/**
 Function triggered when the space bar is pressed to fire a projectile
 
 - parameter void:
 - returns: void
 */
void AEnemy::fire(float angle){
    
    //TODO: Rotation of the barrel up and down
    
    FString TheFloatStr = FString::SanitizeFloat(angle);
    GEngine->AddOnScreenDebugMessage(100, 1.0f, FColor::Red, TheFloatStr);
    
    
    FVector start = GetActorLocation();
    FVector vel = GetActorForwardVector();
    
    TArray<UActorComponent*> me = GetComponents();
    
    for(int i = 0; i < me.Num(); i++){
        UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
        if (GEngine && thisComp) {
            GEngine->AddOnScreenDebugMessage(i, 1.0f, FColor::Blue, thisComp->GetName());
            
            if(thisComp->GetName() == "barrel"){
                thisComp->SetRelativeRotation(FRotator(0, 0, angle));
                vel = thisComp->GetRightVector();
                start = thisComp->GetComponentLocation();
            }
        }else{
            GEngine->AddOnScreenDebugMessage(i, 1.0f, FColor::Blue, TEXT("No name"));
        }
    }
    
    if (canFire) {
        //TODO: edit starting position of bullet and initial velocity and physics and stuff
        AProjectile *bullet = GetWorld()->SpawnActor<AProjectile>(start, FRotator(0,0,0));
        vel = vel*100;
        bullet->setVelocity(vel);
        
        GetWorld()->GetTimerManager().SetTimer(handleClock, this, &AEnemy::readyToFire, 1.0f, true);
        canFire = false;
    }
}


void AEnemy::readyToFire(){
    GetWorld()->GetTimerManager().ClearTimer(handleClock);
    canFire = true;
}


