// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Structure to hold one-time initialization
    struct FConstructorStatics
    {
        ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
        ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> ProjectileMaterial;
        FConstructorStatics()
        : PlaneMesh(TEXT("/Game/BluePrints/ProjectileMesh.ProjectileMesh"))
        , ProjectileMaterial(TEXT("/Game/BluePrints/ProjectileMaterial.ProjectileMaterial"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;
    
    // Create dummy root scene component
    DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
    RootComponent = DummyRoot;
    
    // Create static mesh component
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
    ProjectileMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
    ProjectileMesh->SetRelativeScale3D(FVector(0.1f,0.1f,0.1f));
    ProjectileMesh->SetRelativeLocation(FVector(0.f,0.f,5.f));
    ProjectileMesh->SetMaterial(0, ConstructorStatics.ProjectileMaterial.Get());
    ProjectileMesh->AttachTo(DummyRoot);
    
    
    // Save a pointer to the orange material
    ProjectileMaterial = ConstructorStatics.ProjectileMaterial.Get();
    
    //adds onHit to detect hits
    this->OnActorHit.AddDynamic(this, &AProjectile::onHit);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
    
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    FVector newLocation = GetActorLocation() + velocity;
    SetActorLocation(newLocation);

}


/**
 Function to set the velocity of the projectile
 
 - parameter velocity: the vector to set the velocity to
 - returns: void
 */
void AProjectile::setVelocity(FVector vel){
    velocity = vel;
}


/**
 Function called to return the velocity of the projectile
 
 - parameter void:
 - returns: the velocity of the projectile
 */
FVector AProjectile::getVelocity(){
    return velocity;
}


/**
 Action triggered when the the projectile hits another object on the screen
 
 - parameter SelfActor: a pointer to the projectile
 - parameter otherActor: a pointer to the actor the projectile hit
 - parameter NormalImpulse: a vector showing the collision direction
 - parameter hit: the hit result
 - returns: void
 */
void AProjectile::onHit(AActor *SelfActor, AActor *otherActor, FVector NormalImpulse, const FHitResult &hit){
    
    if(otherActor){
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Green, otherActor->GetName());
            
            //TODO:What do we do when we hit an AI?
            if(otherActor->GetName().Contains(TEXT("BP_Enemy"))){
                otherActor->SetActorLocation(otherActor->GetActorLocation() - FVector(0, 50, 0));
            }
        }
    }
    
}



