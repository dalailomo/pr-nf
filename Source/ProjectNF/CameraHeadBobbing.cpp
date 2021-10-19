// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraHeadBobbing.h"

UCameraHeadBobbing::UCameraHeadBobbing()
{
    OscillationDuration = 1.0f;
    OscillationBlendInTime = 1.0f;
    OscillationBlendOutTime = 4.0f;

    LocOscillation.Z.Amplitude = 3.0f;
    LocOscillation.Z.Frequency = 10.0f;
}