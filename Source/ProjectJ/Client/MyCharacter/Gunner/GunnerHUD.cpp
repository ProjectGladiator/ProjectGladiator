// Fill out your copyright notice in the Description page of Project Settings.

#include "GunnerHUD.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "Engine/Texture2D.h" // 2D 텍스처 헤더 파일
#include "Engine/Canvas.h" // 뷰포트 
#include "Client/MyCharacter/Gunner/Gunner.h"
#include "Kismet/GameplayStatics.h" //각종 유틸 헤더

//서버 헤더

AGunnerHUD::AGunnerHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D>T_CrossHairUpDown(TEXT("Texture2D'/Game/Assets/Paragon/Chracter/ParagonLtBelica/Characters/Heroes/Belica/Textures/CrossHair/UpDown.UpDown'"));

	if (T_CrossHairUpDown.Succeeded())
	{
		CrossHairUpDown = T_CrossHairUpDown.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>T_CrossHairLeftRight(TEXT("Texture2D'/Game/Assets/Paragon/Chracter/ParagonLtBelica/Characters/Heroes/Belica/Textures/CrossHair/LeftRight.LeftRight'"));

	if (T_CrossHairLeftRight.Succeeded())
	{
		CrossHairLeftRight = T_CrossHairLeftRight.Object;
	}
}

void AGunnerHUD::DrawHUD()
{
	Super::DrawHUD();

	auto Gunner = Cast<AGunner>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Gunner)
	{
		if (Gunner->GetRightClickFlag())
		{
			float CrossHairSpread = Gunner->GetCrossHairSpread();

			float ScreenX;
			float ScreenY;

			float CanvasSizeX = (float)Canvas->SizeX;
			float CanvasSizeY = (float)Canvas->SizeY;

			ScreenX = (CanvasSizeX / 2.0f) + -1.0f;
			ScreenY = ((CanvasSizeY / 2.0f) + -16.0f) - CrossHairSpread;

			DrawTexture(CrossHairUpDown, ScreenX, ScreenY, 2.0f, 12.0f, 0, 0, 1.0f, 1.0f);

			ScreenX = (CanvasSizeX / 2.0f) + -1.0f;
			ScreenY = ((CanvasSizeY / 2.0f) + 4.0f) + CrossHairSpread;

			DrawTexture(CrossHairUpDown, ScreenX, ScreenY, 2.0f, 12.0f, 0, 0, 1.0f, 1.0f);

			ScreenX = ((CanvasSizeX / 2.0f) + -16.0f) - CrossHairSpread;
			ScreenY = (CanvasSizeY / 2.0f) + -1.0f;

			DrawTexture(CrossHairUpDown, ScreenX, ScreenY, 12.0f, 2.0f, 0, 0, 1.0f, 1.0f);

			ScreenX = ((CanvasSizeX / 2.0f) + 4.0f) + CrossHairSpread;
			ScreenY = (CanvasSizeY / 2.0f) + -1.0f;

			DrawTexture(CrossHairUpDown, ScreenX, ScreenY, 12.0f, 2.0f, 0, 0, 1.0f, 1.0f);
		}
	}
}
