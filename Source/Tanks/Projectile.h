// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKS_API AProjectile : public AActor
{
    GENERATED_BODY()
    
    /** Dummy root component */
    UPROPERTY(Category = Projectile, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* DummyRoot;
    
    /** StaticMesh component for the clickable block */
    UPROPERTY(Category = Projectile, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* ProjectileMesh;
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
    
    /** Pointer to orange material used on active blocks */
    UPROPERTY()
    class UMaterialInstance* ProjectileMaterial;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    void setVelocity(FVector vel);
    FVector getVelocity();
    
    UFUNCTION()
    void onHit(AActor *SelfActor, AActor *otherActor, FVector NormalImpulse, const FHitResult &hit);
    
    
private:
    FVector velocity;
	
public:
    /** Returns DummyRoot subobject **/
    FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
    /** Returns BlockMesh subobject **/
    FORCEINLINE class UStaticMeshComponent* GetBallMesh() const { return ProjectileMesh; }

};
