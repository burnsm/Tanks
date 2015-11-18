// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "MyTank.h"


// Sets default values
AMyTank::AMyTank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyTank::BeginPlay()
{
	Super::BeginPlay();
	
   Super::SetupPlayerInputComponent(InputComponent);

   //Super::SetupPlayerInputComponent(InputComponent);
   check(InputComponent);
   InputComponent->BindAxis("keyW",this,&AMyTank::walkForward);
   InputComponent->BindAxis("keyS",this,&AMyTank::walkBack);
   InputComponent->BindAxis("keyA",this,&AMyTank::walkLeft);
   InputComponent->BindAxis("keyD",this,&AMyTank::walkRight);
   InputComponent->BindAxis("mouseX",this,&AMyTank::Yaw);       //look left-right
   InputComponent->BindAxis("mouseY",this,&AMyTank::Pitch);     //look up-down

}

// Called every frame
void AMyTank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMyTank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AMyTank::walkForward(float amount)
{
   if(Controller && amount){
      FVector fwd=GetActorForwardVector();
      AddMovementInput(fwd, amount);
   }
}

void AMyTank::walkBack(float amount)
{
   AMyTank::walkForward(-.7*amount);
}

void AMyTank::walkLeft(float amount)
{
   AMyTank::walkRight(-1.0*amount);
}

void AMyTank::walkRight(float amount)
{
   if(Controller && amount){
      FVector fwd=GetActorRightVector();
      AddMovementInput(fwd, amount);
   }
}

void AMyTank::Yaw(float amount)
{
   AddControllerYawInput( 200.f * .6*amount * (GetWorld())->GetDeltaSeconds() );
}

void AMyTank::Pitch(float amount)
{
   AddControllerPitchInput( 200.f * amount * (GetWorld())->GetDeltaSeconds() );
}

