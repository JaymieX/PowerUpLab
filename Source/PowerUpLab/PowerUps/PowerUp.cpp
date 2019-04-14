// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUp.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::SphereOverlapCallBack);
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rot(Pitch, Yaw, Roll);
	AddActorLocalRotation(rot.Quaternion());
}

void APowerUp::SphereOverlapCallBack
(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
ACharacter* Character = Cast<ACharacter>(OtherActor);

	UE_LOG(LogTemp, Warning, TEXT("Collided"));

	if (Character)
	{
		Destroy();
	}
}

