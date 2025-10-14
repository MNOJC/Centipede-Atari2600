
#pragma once

#include "CoreMinimal.h"
#include "DataAsset/CentipedColorDA.h"

namespace ColorHelper
{
	void ApplyCentipedeColorMob(const TSoftObjectPtr<UCentipedColorDA> ColorDA, UMaterialParameterCollectionInstance* MPCInstance);
	void ApplyCentipedeColorTarget(const TSoftObjectPtr<UCentipedColorDA> ColorDA, UMaterialInstanceDynamic* BaseInstance);
}