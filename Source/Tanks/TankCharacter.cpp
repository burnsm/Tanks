// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankCharacter.h"
#include "Projectile.h"


// Sets default values
ATankCharacter::ATankCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
}

// Called when the game starts or when spawned
void ATankCharacter::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ATankCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
}

// Called to bind functionality to input
void ATankCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    //Super::SetupPlayerInputComponent(InputComponent);
    check(InputComponent);
    InputComponent->BindAxis("Forward", this, &ATankCharacter::MoveForward);
    InputComponent->BindAxis("Strafe", this, &ATankCharacter::MoveRight);
    InputComponent->BindAxis("Yaw", this, &ATankCharacter::Yaw);
    InputComponent->BindAxis("Pitch", this, &ATankCharacter::RaiseBarrel);
    InputComponent->BindAxis("Raise", this, &ATankCharacter::Pitch);
    InputComponent->BindAction("Fire", IE_Pressed, this, &ATankCharacter::fire);
}

void ATankCharacter::MoveForward(float amount)
{
    if(Controller && amount)
    {
        FVector fwd = GetActorForwardVector();
        
        TArray<UActorComponent*> me = GetComponents();
        
        for(int i = 0; i < me.Num(); i++){
            UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
            if (thisComp) {
                if(thisComp->GetName() == "turret"){
                    fwd = thisComp->GetRightVector();
                }

            }
        }
        
        AddMovementInput (fwd, amount);
    }
}


void ATankCharacter::MoveRight(float amount)
{
    if(Controller && amount)
    {
        FVector fwd = GetActorRightVector();
        
        TArray<UActorComponent*> me = GetComponents();
        
        for(int i = 0; i < me.Num(); i++){
            UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
            if (thisComp) {
                if(thisComp->GetName() == "turret"){
                    fwd = thisComp->GetForwardVector();
                    fwd = fwd * (-1);
                }
                
            }
        }
        
        AddMovementInput (fwd, amount);
    }
}


void ATankCharacter::Yaw(float amount)
{
    AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}


void ATankCharacter::Pitch(float amount)
{
    AddControllerPitchInput(-200.f * amount * GetWorld()->GetDeltaSeconds());
    //RaiseBarrel(-200.f * amount * GetWorld()->GetDeltaSeconds());
}


/**
 Function triggered when the space bar is pressed to fire a projectile
 
 - parameter void:
 - returns: void
 */
void ATankCharacter::fire(){
    
    FVector start = GetActorLocation();
    FVector vel = GetActorForwardVector();
    
    TArray<UActorComponent*> me = GetComponents();
    
    for(int i = 0; i < me.Num(); i++){
        UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
        if (GEngine && thisComp) {
            GEngine->AddOnScreenDebugMessage(i, 1.0f, FColor::Blue, thisComp->GetName());
            
            if(thisComp->GetName() == "barrel"){
                vel = thisComp->GetRightVector();
                start = thisComp->GetComponentLocation();
            }
        }else{
            GEngine->AddOnScreenDebugMessage(i, 1.0f, FColor::Blue, TEXT("No name"));
        }
    }
    
    if(FireSound !=NULL)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
    }
    
    //TODO: edit starting position of bullet and initial velocity and physics and stuff
    AProjectile *bullet = GetWorld()->SpawnActor<AProjectile>(start, FRotator(0,0,0));
    vel = vel*100;
    bullet->setVelocity(vel);
}

/**
 TODO: Transform BluePrints to code
 Raising and Lowering the  Barrel - to be connected with up/down arrow keys
 parameter void:
 returns: void
*/
void ATankCharacter::RaiseBarrel(float amount)
{

    //(AddControllerPitchInput(-200.f * amount * GetWorld()->GetDeltaSeconds())));
    TArray<UActorComponent*> me = GetComponents();
    
    for(int i = 0; i < me.Num(); i++){
        UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
        if (GEngine && thisComp) {
            if(thisComp->GetName() == "barrel"){
                thisComp->AddLocalRotation(FRotator(0, 0, amount));
                GEngine->AddOnScreenDebugMessage(40, 1.0f, FColor::Blue, TEXT("Pitch"));
            }
        }
    }
}


