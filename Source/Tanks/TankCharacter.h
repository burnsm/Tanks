// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "TankCharacter.generated.h"

UCLASS()
class TANKS_API ATankCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    /** Sound to play each time we fire */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
    class USoundBase* FireSound;
  
    //float RotationRate=1.0 ;
    void MoveForward(float amount);
    void MoveRight(float amount);
    void Yaw(float amount);
    void Pitch(float amount);
    void fire();
    void RaiseBarrel(float amount);
};
