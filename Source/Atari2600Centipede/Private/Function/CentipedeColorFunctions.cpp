#include "Function/CentipedeColorFunctions.h"

#include "Log/CentipedeLoggerCategories.h"
#include "Materials/MaterialParameterCollectionInstance.h"

void ColorHelper::ApplyCentipedeColorMob(const TSoftObjectPtr<UCentipedColorDA> ColorDA, UMaterialParameterCollectionInstance* MPCInstance)
{
	if (!MPCInstance)
	{
		UE_LOG(LogCentipede, Error, TEXT("MPCInstance is nullptr!"));
		return;
	}

	if (!ColorDA.IsValid())
	{
		UE_LOG(LogCentipede, Warning, TEXT("ColorDA is not loaded, loading synchronously..."));
		ColorDA.LoadSynchronous();
	}

	if (!ColorDA.IsValid())
	{
		UE_LOG(LogCentipede, Error, TEXT("Failed to load ColorDA!"));
		return;
	}
	
	MPCInstance -> SetVectorParameterValue("R", ColorDA.Get()->Color_R);
	MPCInstance -> SetVectorParameterValue("G", ColorDA.Get()->Color_G);
	MPCInstance -> SetVectorParameterValue("B", ColorDA.Get()->Color_B);
	MPCInstance -> SetVectorParameterValue("Bar", ColorDA.Get()->Color_Bar);
}

void ColorHelper::ApplyCentipedeColorTarget(const TSoftObjectPtr<UCentipedColorDA> ColorDA, UMaterialInstanceDynamic* BaseInstance)
{
	if (!BaseInstance)
	{
		UE_LOG(LogCentipede, Error, TEXT("BaseInstance is nullptr!"));
		return;
	}

	if (!ColorDA.IsValid())
	{
		UE_LOG(LogCentipede, Warning, TEXT("ColorDA is not loaded, loading synchronously..."));
		ColorDA.LoadSynchronous();
	}

	if (!ColorDA.IsValid())
	{
		UE_LOG(LogCentipede, Error, TEXT("Failed to load ColorDA!"));
		return;
	}
	
	BaseInstance -> SetVectorParameterValue("R", ColorDA.Get()->Color_R);
	BaseInstance -> SetVectorParameterValue("G", ColorDA.Get()->Color_G);
	BaseInstance -> SetVectorParameterValue("B", ColorDA.Get()->Color_B);
}


