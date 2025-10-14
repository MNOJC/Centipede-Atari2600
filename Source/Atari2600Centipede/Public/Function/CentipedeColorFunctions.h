
#pragma once

#include "CoreMinimal.h"
#include "DataAsset/CentipedColorDA.h"

namespace ColorHelper
{
	void ApplyCentipedeColorMob(const UCentipedColorDA& ColorDA, UMaterialParameterCollectionInstance* MPCInstance);
	void ApplyCentipedeColorTarget(const UCentipedColorDA& ColorDA, UMaterialInstanceDynamic* BaseInstance);
}