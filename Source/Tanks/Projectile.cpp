// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	/*PrimaryActorTick.bCanEverTick = true;

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
    //this->OnActorHit.AddDynamic(this, &AProjectile::onHit);*/
    
    // Use a sphere as a simple collision representation
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(5.0f);
    CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
    CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something blocking
    
    // Players can't walk on it
    CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
    CollisionComp->CanCharacterStepUpOn = ECB_No;
    
    // Set as root component
    RootComponent = CollisionComp;
    
    // Use a ProjectileMovementComponent to govern this projectile's movement
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;
    
    //Die after 3 seconds by default
    InitialLifeSpan = 3.0f;
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
    
    //FVector newLocation = GetActorLocation() + velocity;
    //SetActorLocation(newLocation);

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
void AProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
    
    if(OtherActor){
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Green, OtherActor->GetName());
            
            //TODO:What do we do when we hit an AI?
            if(OtherActor->GetName().Contains(TEXT("BP_Enemy"))){
                OtherActor->SetActorLocation(OtherActor->GetActorLocation() - FVector(0, 50, 0));
                
                Destroy();
            }
        }
    }
    
}



