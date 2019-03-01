// Fill out your copyright notice in the Description page of Project Settings.

#include "GunnerCameraShake.h"

UGunnerCameraShake::UGunnerCameraShake()
{
	OscillationDuration = 0.1f; //카메라 흔드는 시간
	OscillationBlendInTime = 0.05f; //카메라 흔들기 시작 시간
	OscillationBlendOutTime = 0.05f; //카메라 흔들기 끝 시간

	//위아래
	RotOscillation.Pitch.Amplitude = 15.0f; //진동의 강도
	RotOscillation.Pitch.Frequency = 1.0f; //진동의 빈도
	RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;//어디서 부터 시작하는지
}
