// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "TankCharacter.h"
#include "Projectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"


// Sets default values
ATankCharacter::ATankCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    currentDirection = FVector(0, -1, 0).Rotation();
    
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
    InputComponent->BindAxis("RotateForward", this, &ATankCharacter::RotateForward);
    InputComponent->BindAxis("RotateStrafe", this, &ATankCharacter::RotateRight);
    //InputComponent->BindAxis("Yaw", this, &ATankCharacter::Yaw);
    //InputComponent->BindAxis("Pitch", this, &ATankCharacter::RaiseBarrel);
    InputComponent->BindAxis("MoveForward", this, &ATankCharacter::MoveForward);
    InputComponent->BindAction("Fire", IE_Pressed, this, &ATankCharacter::fire);
}


/**
 Function triggered when W or S is pressed to rotate the character forward or backward
 
 - parameter amount: the amount to rotate the tank
 - returns: void
 */
void ATankCharacter::RotateForward(float amount)
{
    if(Controller && amount)
    {
        FVector fwd = GetActorRightVector();
        
        TArray<UActorComponent*> me = GetComponents();
        
        //loop through all components of the tank
        for(int i = 0; i < me.Num(); i++){
            UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
            if (thisComp) {
                
                //if the turrent is found, set the direction the tank is facing to that direction
                if(thisComp->GetName() == "turret"){
                    fwd = thisComp->GetForwardVector();
                    fwd = fwd * (-1);
                    
                    if (amount < 0){
                        currentDirection = (thisComp->GetComponentRotation().Vector() * -1).Rotation();
                    }else if (amount > 0){
                        currentDirection = thisComp->GetComponentRotation();
                    }
                    
                    //if the rotation of the bottom is happening, rotate all of the pieces
                }else if (thisComp->GetName() == "body" || thisComp->GetName() == "sideL" ||thisComp->GetName() == "sideR" ||thisComp->GetName() == "treadL" ||thisComp->GetName() == "treadR") {
                    
                    int direction;
                    FRotator newRot = thisComp->GetComponentRotation();
                    
                    
                    //find the direction of the shortest rotation to get the bottom facing the correct angle
                    if ((currentDirection.Yaw - newRot.Yaw) > 0 && (currentDirection.Yaw - newRot.Yaw) < 360 - (currentDirection.Yaw - newRot.Yaw)){
                        direction = 5;
                    }else if ((currentDirection.Yaw - newRot.Yaw) > 0 && (currentDirection.Yaw - newRot.Yaw) > 360 - (currentDirection.Yaw - newRot.Yaw)) {
                        direction = -5;
                    }else if ((currentDirection.Yaw - newRot.Yaw) < 0 && FMath::Abs(currentDirection.Yaw - newRot.Yaw) < 360 - FMath::Abs(currentDirection.Yaw - newRot.Yaw)) {
                        direction = -5;
                    }else if ((currentDirection.Yaw - newRot.Yaw) < 0 && FMath::Abs(currentDirection.Yaw - newRot.Yaw) > 360 - FMath::Abs(currentDirection.Yaw - newRot.Yaw)) {
                        direction = 5;
                    }
                    
                    
                    //if the bottom of the tank is not already facing that direction, rotate it by the ABS(amount) in the calculated direction
                    if (!currentDirection.Equals(newRot, 5)){
                        thisComp->AddLocalRotation(FRotator(0, FMath::Abs(amount)*direction, 0));
                    }
                }
                
            }
        }
    }
}


/**
 Function triggered when A or D is pressed to rotate the character right or left
 
 - parameter amount: the amount to rotate the tank
 - returns: void
 */
void ATankCharacter::RotateRight(float amount)
{
    if(Controller && amount)
    {
        FVector fwd = GetActorRightVector();
        
        TArray<UActorComponent*> me = GetComponents();
        
        //loop through all components of the tank
        for(int i = 0; i < me.Num(); i++){
            UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
            if (thisComp) {
                
                //if the turrent is found, set the direction the tank is facing to that direction
                if(thisComp->GetName() == "turret"){
                    fwd = thisComp->GetForwardVector();
                    fwd = fwd * (-1);
                    
                    if (amount < 0){
                        currentDirection = (thisComp->GetComponentRotation().Vector() * -1).Rotation() + FRotator(0, 90, 0);
                    }else if (amount > 0){
                        currentDirection = thisComp->GetComponentRotation() + FRotator(0, 90, 0);
                    }
                    
                    //if the rotation of the bottom is happening, rotate all of the pieces
                }else if (thisComp->GetName() == "body" || thisComp->GetName() == "sideL" ||thisComp->GetName() == "sideR" ||thisComp->GetName() == "treadL" ||thisComp->GetName() == "treadR") {
                    
                    int direction;
                    FRotator newRot = thisComp->GetComponentRotation();
                    
                    
                    //find the direction of the shortest rotation to get the bottom facing the correct angle
                    if ((currentDirection.Yaw - newRot.Yaw) > 0 && (currentDirection.Yaw - newRot.Yaw) < 360 - (currentDirection.Yaw - newRot.Yaw)){
                        direction = 5;
                    }else if ((currentDirection.Yaw - newRot.Yaw) > 0 && (currentDirection.Yaw - newRot.Yaw) > 360 - (currentDirection.Yaw - newRot.Yaw)) {
                        direction = -5;
                    }else if ((currentDirection.Yaw - newRot.Yaw) < 0 && FMath::Abs(currentDirection.Yaw - newRot.Yaw) < 360 - FMath::Abs(currentDirection.Yaw - newRot.Yaw)) {
                        direction = -5;
                    }else if ((currentDirection.Yaw - newRot.Yaw) < 0 && FMath::Abs(currentDirection.Yaw - newRot.Yaw) > 360 - FMath::Abs(currentDirection.Yaw - newRot.Yaw)) {
                        direction = 5;
                    }
                    
                    
                    //if the bottom of the tank is not already facing that direction, rotate it by the ABS(amount) in the calculated direction
                    if (!currentDirection.Equals(newRot, 5)){
                        thisComp->AddLocalRotation(FRotator(0, FMath::Abs(amount)*direction, 0));
                    }
                }
                
            }
        }
    }
}


/**
 Function triggered when mouse is moved in the X direction
 
 - parameter amount: the amount the mouse is moved
 - returns: void
 */
void ATankCharacter::Yaw(float amount)
{
    AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}


/**
 Function triggered when Space or Left Shift is pressed to move the character forward or backward
 
 - parameter amount: the amount to rotate the tank
 - returns: void
 */
void ATankCharacter::MoveForward(float amount)
{
    if(Controller && amount)
    {
        FVector fwd = GetActorRightVector();
        
        TArray<UActorComponent*> me = GetComponents();
        
        //find the direction of the turrent to move the tank in
        for(int i = 0; i < me.Num(); i++){
            UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
            if (thisComp) {
                
                //if the turrent is found, get its direction to move the tank side to side from that direction
                if(thisComp->GetName() == "body"){
                    fwd = thisComp->GetRightVector();
                }
            }
        }
        AddMovementInput (fwd, amount);
    }
}


/**
 Function triggered when the space bar is pressed to fire a projectile
 
 - parameter void:
 - returns: void
 */
void ATankCharacter::fire(){
    
    FVector start = GetActorLocation();
    FVector vel = GetActorForwardVector();
    FRotator rot = GetActorRotation();
    
    TArray<UActorComponent*> me = GetComponents();
    
    //find the barrel to get the direction vector of the velocity of the bullet
    for(int i = 0; i < me.Num(); i++){
        UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
        if (GEngine && thisComp) {
            //GEngine->AddOnScreenDebugMessage(i, 1.0f, FColor::Blue, thisComp->GetName());
            
            //if the barrel is found, set starting position and velocity
            if(thisComp->GetName() == "barrel"){
                vel = thisComp->GetRightVector();
                start = thisComp->GetComponentLocation();
                rot = thisComp->GetComponentRotation();
            }
        }else{
            //GEngine->AddOnScreenDebugMessage(i, 1.0f, FColor::Blue, TEXT("No name"));
        }
    }
    
    //play the fire sound
    if(FireSound !=NULL)
    {
        //UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
    }
    
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
}


/**
 TODO: Transform BluePrints to code
 Raising and Lowering the  Barrel - to be connected with up/down arrow keys
 
 parameter amount: the amount to raise or lower the barrel
 returns: void
 */
void ATankCharacter::RaiseBarrel(float amount)
{
    
    //(AddControllerPitchInput(-200.f * amount * GetWorld()->GetDeltaSeconds())));
    TArray<UActorComponent*> me = GetComponents();
    
    //find the barrel component
    for(int i = 0; i < me.Num(); i++){
        UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
        if (GEngine && thisComp) {
            
            //if the barrel is found, add the rotation to it
            if(thisComp->GetName() == "barrel"){
                thisComp->AddLocalRotation(FRotator(0, 0, amount));
                //GEngine->AddOnScreenDebugMessage(40, 1.0f, FColor::Blue, TEXT("Pitch"));
            }
        }
    }
}


