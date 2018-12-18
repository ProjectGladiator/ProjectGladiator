// Fill out your copyright notice in the Description page of Project Settings.

#include "ChracterCreateCamera.h"
#include "Camera/CameraComponent.h"

AChracterCreateCamera::AChracterCreateCamera()
{
	GetCameraComponent()->FieldOfView = 100.0f;
}