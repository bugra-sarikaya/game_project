// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#include "input_settings.h"
Uinput_settings::Uinput_settings() {
    UInputSettings* input_settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
    if (input_settings) {
        TArray<FInputActionKeyMapping> TArray_actions;
        TArray<FInputAxisKeyMapping> TArray_axes;
        TArray_actions = input_settings->GetActionMappings();
        TArray_axes = input_settings->GetAxisMappings();
        for (int action_index = 0; action_index < TArray_actions.Num(); action_index++) {
            input_settings->RemoveActionMapping(FInputActionKeyMapping(TArray_actions[action_index].ActionName, TArray_actions[action_index].Key, TArray_actions[action_index].bShift, TArray_actions[action_index].bCtrl, TArray_actions[action_index].bAlt, TArray_actions[action_index].bCmd));
        }
        input_settings->SaveKeyMappings();
        for (int axis_index = 0; axis_index < TArray_axes.Num(); axis_index++) {
            input_settings->RemoveAxisMapping(FInputAxisKeyMapping(TArray_axes[axis_index].AxisName, TArray_axes[axis_index].Key, TArray_axes[axis_index].Scale));
        }
        input_settings->AddActionMapping(FInputActionKeyMapping("fire", FKey(TEXT("LeftMouseButton"))));
        input_settings->AddActionMapping(FInputActionKeyMapping("jump", FKey(TEXT("Spacebar"))));
        input_settings->AddActionMapping(FInputActionKeyMapping("quit", FKey(TEXT("Escape"))));
        input_settings->AddAxisMapping(FInputAxisKeyMapping("move_forward", FKey(TEXT("W")), 1.f));
        input_settings->AddAxisMapping(FInputAxisKeyMapping("move_backward", FKey(TEXT("S")), 1.f));
        input_settings->AddAxisMapping(FInputAxisKeyMapping("move_right", FKey(TEXT("D")), 1.f));
        input_settings->AddAxisMapping(FInputAxisKeyMapping("move_left", FKey(TEXT("A")), 1.f));
        input_settings->AddAxisMapping(FInputAxisKeyMapping("look_right", FKey(TEXT("MouseX")), 1.f));
        input_settings->AddAxisMapping(FInputAxisKeyMapping("look_up", FKey(TEXT("MouseY")), -1.f));
        input_settings->SaveKeyMappings();
    }
}
