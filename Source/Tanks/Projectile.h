// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKS_API AProjectile : public AActor
{
    GENERATED_BODY()
    
    /** Dummy root component */
    /*UPROPERTY(Category = Projectile, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* DummyRoot;
    
    //StaticMesh component for the clickable block
    UPROPERTY(Category = Projectile, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* ProjectileMesh;*/
    
    /** Sphere collision component */
    UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
    class USphereComponent* CollisionComp;
    
    /** Projectile movement component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    class UProjectileMovementComponent* ProjectileMovement;
	
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
    void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    
private:
    FVector velocity;
	
public:
    /** Returns DummyRoot subobject
    FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
    // Returns BlockMesh subobject
    FORCEINLINE class UStaticMeshComponent* GetBallMesh() const { return ProjectileMesh; } **/

    /** Returns CollisionComp subobject **/
    FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
    /** Returns ProjectileMovement subobject **/
    FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
