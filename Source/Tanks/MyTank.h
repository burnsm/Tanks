// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyTank.generated.h"

UCLASS()
class TANKS_API AMyTank : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyTank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void walkForward(float amount);
	void walkBack(float amount);
	void walkLeft(float amount);
	void walkRight(float amount);
	
	void Yaw(float amount); 		//rotate to look left-right
	void Pitch(float amount);		//rotate to look up-down	
};
