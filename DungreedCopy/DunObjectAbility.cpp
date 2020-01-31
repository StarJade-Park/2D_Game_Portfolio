#include <..\psklib\GamePos.h>

#include "DunObjectAbility.h"

GamePos DunObjectAbility::Gravity = { 0.0f, 400.f };
GamePos DunObjectAbility::DashLimit = { 200.f, 200.f };

float DunObjectAbility::JumpLimit = 400.f;
float DunObjectAbility::MinJumpHeight = 250.f;