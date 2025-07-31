#include "Items/Inv_ItemTags.h"

namespace GameItems
{

	namespace Equipment
	{
		namespace Weapons
		{
			UE_DEFINE_GAMEPLAY_TAG(Axe, "GameItems.Equipment.Weapons.Axe")
			UE_DEFINE_GAMEPLAY_TAG(Sword, "GameItems.Equipment.Weapons.Sword")
		}

		namespace Cloaks
		{
			UE_DEFINE_GAMEPLAY_TAG(RedCloak, "GameItems.Equipment.Cloaks.RedCloak")
		}

		namespace Masks
		{
			UE_DEFINE_GAMEPLAY_TAG(SteelMask, "GameItems.Equipment.Masks.SteelMask")
		}
		namespace Armor
		{
			
		}
		
	}

	namespace Consumables
	{
		namespace Potions
		{
			namespace Red
			{
				UE_DEFINE_GAMEPLAY_TAG(Small, "GameItems.Consumables.Potions.Red.Small")
				UE_DEFINE_GAMEPLAY_TAG(Large, "GameItems.Consumables.Potions.Red.Large")
			}

			namespace Blue
			{
				UE_DEFINE_GAMEPLAY_TAG(Small, "GameItems.Consumables.Potions.Blue.Small")
				UE_DEFINE_GAMEPLAY_TAG(Large, "GameItems.Consumables.Potions.Blue.Large")
			}
			
		}
		
	}

	namespace Craftables
	{
		UE_DEFINE_GAMEPLAY_TAG(FireFruit, "GameItems.Craftables.FireFruit")
		UE_DEFINE_GAMEPLAY_TAG(Daisy, "GameItems.Craftables.Daisy")
		UE_DEFINE_GAMEPLAY_TAG(ScorchPetal, "GameItems.Craftables.ScorchPetal")
	}

}