// Fill out your copyright notice in the Description page of Project Settings.

#include "BruteAnimInstance.h"
#include "Brute.h"
#include "UObject/ConstructorHelpers.h" 

//#define Anim_Default_Attack "AnimMontage'/Game/Blueprints/Monster/StageOne/Spider/Animations/SpiderDefaultAttackMontage.SpiderDefaultAttackMontage'"
//#define Anim_Twice_Attack "AnimSequence'/Game/Assets/Monster/MixamoBrute/Anim/AttackTwice.AttackTwice'"
//#define Anim_Jump_Attack "AnimSequence'/Game/Assets/Monster/MixamoBrute/Anim/RootFallowJumpAttack.RootFallowJumpAttack'"
//#define Anim_Kick_Attack "AnimSequence'/Game/Assets/Monster/MixamoBrute/Anim/KickBrute.KickBrute'"

UBruteAnimInstance::UBruteAnimInstance()
{
	/*static ConstructorHelpers::FObjectFinder<UAnimMontage>BruteDefaultAttack_Montage(TEXT(Anim_Default_Attack));
	if (BruteDefaultAttack_Montage.Succeeded())
	{
		AttackMontages.Add(BruteDefaultAttack_Montage.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>BruteJumpAttack_Montage(TEXT(Anim_Jump_Attack));
	if (BruteJumpAttack_Montage.Succeeded())
	{
		AttackMontages.Add(BruteJumpAttack_Montage.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>BruteKickAttack_Montage(TEXT(Anim_Kick_Attack));
	if (BruteJumpAttack_Montage.Succeeded())
	{
		AttackMontages.Add(BruteKickAttack_Montage.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>BruteTwiceAttack_Montage(TEXT(Anim_Twice_Attack));
	if (BruteTwiceAttack_Montage.Succeeded())
	{
		AttackMontages.Add(BruteTwiceAttack_Montage.Object);
	}*/
}

void UBruteAnimInstance::NativeUpdateAnimation(float DeltaSecnds)
{
	Super::NativeUpdateAnimation(DeltaSecnds);

	auto Brute = Cast<ABrute>(TryGetPawnOwner());

	if (Brute && Brute->IsValidLowLevelFast())
	{
		CurrentState = Brute->GetCurrnetState();
		CurrentAttackState = Brute->GetCurrentAttackState();
	}
}

