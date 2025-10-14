#include "Function/CentipedeColorFunctions.h"

#include "Materials/MaterialParameterCollectionInstance.h"

void ColorHelper::ApplyCentipedeColorMob(const UCentipedColorDA& ColorDA, UMaterialParameterCollectionInstance* MPCInstance)
{
	MPCInstance -> SetVectorParameterValue("R", ColorDA.Color_R);
	MPCInstance -> SetVectorParameterValue("G", ColorDA.Color_G);
	MPCInstance -> SetVectorParameterValue("B", ColorDA.Color_B);
	MPCInstance -> SetVectorParameterValue("Bar", ColorDA.Color_Bar);
}

void ColorHelper::ApplyCentipedeColorTarget(const UCentipedColorDA& ColorDA, UMaterialInstanceDynamic* BaseInstance)
{
	BaseInstance -> SetVectorParameterValue("R", ColorDA.Color_R);
	BaseInstance -> SetVectorParameterValue("G", ColorDA.Color_G);
	BaseInstance -> SetVectorParameterValue("B", ColorDA.Color_B);
}


