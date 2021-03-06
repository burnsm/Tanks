// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Enemy.h"
#include "EnemyController.h"
#include "Projectile.h"


// Sets default values
AEnemy::AEnemy(const class FObjectInitializer&)
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    health = 15;
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
 
 - parameter angle: the angle of the barrel to fire the bullet in
 - returns: void
 */
void AEnemy::fire(float angle){
    
    //TODO: Rotation of the barrel up and down
    
    FString TheFloatStr = FString::SanitizeFloat(angle);
    GEngine->AddOnScreenDebugMessage(100, 1.0f, FColor::Red, TheFloatStr);
    
    
    FVector start = GetActorLocation();
    FVector vel = GetActorForwardVector();
    FRotator rot = GetActorRotation();
    
    TArray<UActorComponent*> me = GetComponents();
    
    //search for the barrel to set the bullets velocity direction and start point
    for(int i = 0; i < me.Num(); i++){
        UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
        if (GEngine && thisComp) {
            
            //if the barrel is found, give the bullet the position and direction vector of the barrel
            if(thisComp->GetName() == "barrel"){
                thisComp->SetRelativeRotation(FRotator(0, 0, angle));
                vel = thisComp->GetRightVector();
                rot = thisComp->GetComponentRotation();
                start = thisComp->GetComponentLocation() + rot.RotateVector(FVector(0, 40, 35));
            }
        }
    }
    
    //only allow the computer to fire once per second
    if (canFire) {
        
        // try and fire a projectile
        if (ProjectileClass != NULL)
        {
            
            //convert velocity to a rotator
            const FRotator SpawnRotation = vel.Rotation();
            
            UWorld* const World = GetWorld();
            if (World != NULL)
            {
                // spawn the projectile at the muzzle
                World->SpawnActor<AProjectile>(ProjectileClass, start, SpawnRotation);
            }
        }
        
        GetWorld()->GetTimerManager().SetTimer(handleClock, this, &AEnemy::readyToFire, 1.0f, true);
        canFire = false;
    }
}


void AEnemy::readyToFire(){
    GetWorld()->GetTimerManager().ClearTimer(handleClock);
    canFire = true;
}


void AEnemy::checkLoss(){
    if (health == 0) {
        Destroy();
    }
}

