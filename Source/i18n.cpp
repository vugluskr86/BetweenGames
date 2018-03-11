#include "i18n.h"

std::map<eBalancePropery, std::string> I18n::PROPERTIES = {
	{ IP_ATTACKPWMULTMAX,"Attack multiplier for weapon" },
	{ IP_ELEMDAMAGE_PYRE,"Pyre damage" },
	{ IP_ELEMDAMAGE_FIRE,"Fire damage" },
	{ IP_ELEMDAMAGE_COLD,"Cold damage" },
	{ IP_ELEMDAMAGE_LIGHTNING,"Lightning damage" },
	{ IP_ELEMDAMAGE_ACID,"Acid damage" },
	{ IP_ELEMDAMAGE_LIGHT,"Light damage" },
	{ IP_ELEMDAMAGE_DARKNESS,"Darkness damage" },
	{ IP_ATTACKPWR,"Attack power" },
	{ IP_HP,"HP" },
	{ IP_CRIT,"Critical chance" },
	{ IP_RANGE,"Attack range" },
	{ IP_ABSORB,"Absorb damage" },
	{ IP_BLEEDCHANCE,"Bleed chance" },
	{ IP_STUNCHANCE,"Stun chance" },
	{ IP_ATTACKPERTURN,"Attack per turn" },
	{ IP_DODGE,"Dodge chance" },
	{ IP_DAZECHANCE,"Daze chance" },
	{ IP_BLOCKVAL,"Block value" },
	{ IP_PHYSRES,"Physical resist" },
	{ IP_FIRERES,"Fire resist" },
	{ IP_COLDRES,"Cold resist" },
	{ IP_LIGHTRES,"Lightning resist" },
	{ IP_ACIDRES,"Acid resist" },
	{ IP_BLOCKCHANCE,"Block chance" },
	{ IP_COOLDOWN,"Cool down" },
	{ IP_COOLDOWN_MIN,"Minimal cool down" }
};

std::map<eItemType, std::string> I18n::ITEM_TYPES = {
	{ WT_WEAPON_1H,"One-handed weapon" },
	{ WT_WEAPON_2H,"Two-handed weapon" },
	{ WT_WEAPON_RIFLE,"Rifle" },
	{ WT_SHIELD,"Shield" }
};
std::map<eSlotType, std::string> I18n::SLOT_TYPES = {
	{ ST_LEFT_HAND,"Left hand" },
	{ ST_RIGHT_HAND,"Right hand" }
};
std::map<eDamageType, std::string> I18n::DAMAGE_TYPES = {
	{ DT_PYRE,"Pyre damage" },
	{ DT_FIRE,"Fire damage" },
	{ DT_COLD,"Cold damage" },
	{ DT_LIGHTNING,"Lightning damage" },
	{ DT_ACID,"Acid damage" },
	{ DT_LIGHT,"Light damage" },
	{ DT_DARKNESS,"Darkness damage" }
};
std::map<Direction, std::string> I18n::DIRECTIONS = {
	/*{ North,"North" },
	{ South,"South" },
	{ East,"East" },
	{ West,"West" }*/
};
std::map<eTileObjects, std::string> I18n::TILE_OBJECT_TYPES = {
	{ TO_DOOR,"Door" },
	{ TO_MONSTER,"Monster" },
	{ TO_PLAYER,"Player" },
	{ TO_TREASURE,"Treasure" },
	{ TO_PORTAL,"Portal" },
	{ TO_STAIRS,"Stairs" }
};
std::map<eAbilityType, std::string> I18n::ABILITY_TYPES = {
	{ AT_TWO_HANDED_SKILL,"Two-handed skill" },
	{ AT_ONE_HANDED_SKILL,"One-handed skill" },
	{ AT_SHIELD_SKILL,"Shield skill" },
	{ AT_CRUSHING_BLOW,"Crushing blow" }
};
std::map<eAbilityClassType, std::string> I18n::ABILITY_CLASS_TYPES = {
	{ ACT_TWO_HAND,"Two-handed class" },
	{ ACT_ONE_HAND,"One-handed class" },
	{ ACT_SHIELD,"Shield class" },
	{ ACT_RIFLE,"Rifle class" }
};