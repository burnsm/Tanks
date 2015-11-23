// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankCharacter.h"
#import "Projectile.h"


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
    InputComponent->BindAxis("Pitch", this, &ATankCharacter::Pitch);
    InputComponent->BindAction("Fire", IE_Pressed, this, &ATankCharacter::fire);
}

void ATankCharacter::MoveForward(float amount)
{
    if(Controller && amount)
    {
        FVector fwd = GetActorForwardVector();
        AddMovementInput (fwd, amount);
    }
}


void ATankCharacter::MoveRight(float amount)
{
    if(Controller && amount)
    {
        FVector fwd = GetActorRightVector();
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
}


/**
 Function triggered when the space bar is pressed to fire a projectile
 
 - parameter void:
 - returns: void
*/
void ATankCharacter::fire(){
    
    AProjectile *bullet = GetWorld()->SpawnActor<AProjectile>(this->GetActorLocation(), FRotator(0,0,0));
    bullet->setVelocity(GetActorForwardVector());
}
