// Fill out your copyright notice in the Description page of Project Settings.


#include "camera_shake_walking.h"

Ucamera_shake_walking::Ucamera_shake_walking() {
	 
	OscillationDuration = 0.5f;
	OscillationBlendInTime = 0.5f;
	OscillationBlendOutTime = 0.5f;
	RotOscillation.Pitch.Amplitude = 0.6f;
	RotOscillation.Pitch.Frequency = 0.1f;
	RotOscillation.Roll.Amplitude = 0.6f;
	RotOscillation.Roll.Frequency = 0.1f;

}