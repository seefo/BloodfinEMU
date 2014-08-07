--Automatically generated by SWGEmu Spawn Tool v0.12 loot editor.

at_helmet = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "",
	directObjectTemplate = "object/tangible/wearables/helmet/helmet_atat.iff",
	craftingValues = {
	         {"armor_rating",1,1,0},
	         {"armor_effectiveness",35,30,10},
             {"kineticeffectiveness",80,80,10},
	         {"energyeffectiveness",80,80,10},
	         {"heateffectiveness",80,80,10},
	         {"coldeffectiveness",80,80,10},
	         {"stuneffectiveness",35,35,10},		 
	         {"acideffectiveness",80,80,10},
	         {"electriceffectiveness",80,80,10},		 
		{"blasteffectiveness",80,80,10},		 
	         {"armor_integrity",60000,70000,0},
	         {"armor_health_encumbrance",25,15,0},
	         {"armor_action_encumbrance",22,13,0},
	         {"armor_mind_encumbrance",30,18,0},
	},
	customizationStringNames = {},
	customizationValues = {},
	skillMods = {
		{"blind_defense",25},
		{"resistance_poison",25},
		{"pistol_accuracy",45},		
		{"knockdown_defense",25},
		{"heavy_flame_thrower_accuracy",45},
		{"heavy_rifle_acid_accuracy",45},		
		{"melee_defense",25},
		{"ranged_defense",25},
		{"stun_defense",25},
		{"slope_move",25},		
		{"resistance_fire",25}
	}
}

addLootItemTemplate("at_helmet", at_helmet)