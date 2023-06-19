#pragma once

UENUM(BlueprintType)
	enum class EKeyColor : uint8 {
		EKC_Red = 0 UMETA(DisplayName = "Red"),
		EKC_Yellow = 1 UMETA(DisplayName = "Yellow"),
		EKC_Green = 2 UMETA(DisplayName = "Green"),
		EKC_Blue = 3 UMETA(DisplayName = "Blue"),
		EKC_Purple = 4 UMETA(DisplayName = "Purple"),
		EKC_White = 7 UMETA(DisplayName = "White")
	};