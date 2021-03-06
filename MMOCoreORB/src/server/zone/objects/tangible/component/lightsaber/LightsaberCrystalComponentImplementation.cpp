/*
 * LightsaberCrystalComponentImplementation.cpp
 *
 *      Author: Katherine
 */

#include "engine/engine.h"


#include "server/zone/objects/tangible/component/Component.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/tangible/component/lightsaber/LightsaberCrystalComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/tangible/LightsaberCrystalObjectTemplate.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/callbacks/LightsaberCrystalTuneSuiCallback.h"

void LightsaberCrystalComponentImplementation::initializeTransientMembers() {
	ComponentImplementation::initializeTransientMembers();

	setLoggingName("LightsaberCrystalComponent");

}

void LightsaberCrystalComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	lcoTemplate = dynamic_cast<LightsaberCrystalObjectTemplate*>(templateData);

	postTuneName = lcoTemplate->getPostTunedName();
}

void LightsaberCrystalComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {

	PlayerObject* player = object->getPlayerObject();

	if (player->getJediState() > 1 || player->isPrivileged()){	
	
		if (getColor() == 31){
			if (owner == ""){
				StringBuffer str;
				str << "\\#FF6600" << "UNTUNED" ;
				alm->insertAttribute("crystal_owner", str);
			} else {
				alm->insertAttribute("crystal_owner", owner);
			}
		}		
	
	}
	
	if (player->getJediState() > 1 || player->isPrivileged())	{	

		if (getColor() != 31){
			if (owner == ""){
				StringBuffer str;
				StringBuffer str2;
				str << "\\#FF6600" << "UNTUNED" ;
				str2 << "@jedi_spam:saber_color_" << getColor();
				alm->insertAttribute("crystal_owner", str);
				alm->insertAttribute("color", str2);
			} else {
				StringBuffer str3;
				str3 << "@jedi_spam:saber_color_" << getColor();
				alm->insertAttribute("crystal_owner", owner);
				alm->insertAttribute("color", str3);
			}
		}	

	}

	if (player->getJediState() > 1 || player->isPrivileged()){

		if (getColor() == 31){
			if (owner != ""){
				alm->insertAttribute("mindamage", minimumDamage);
				alm->insertAttribute("maxdamage", maximumDamage);
				alm->insertAttribute("wpn_attack_speed", attackSpeed);
				alm->insertAttribute("wpn_wound_chance", woundChance);
				alm->insertAttribute("wpn_attack_cost_health", sacHealth);
				alm->insertAttribute("wpn_attack_cost_action", sacAction);
				alm->insertAttribute("wpn_attack_cost_mind", sacMind);
				alm->insertAttribute("forcecost", forceCost);
			} else {
				StringBuffer str;
				str << "@jedi_spam:crystal_quality_" << getQuality();
				alm->insertAttribute("quality", str);
			}
		}
	}
	
	TangibleObjectImplementation::fillAttributeList(alm, object);	

}

void LightsaberCrystalComponentImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if ((inventory != NULL) && (owner == "") && player->hasSkill("force_title_jedi_rank_01")){
		String text = "@jedi_spam:tune_crystal";
		menuResponse->addRadialMenuItem(128, 3, text);
	}

	ComponentImplementation::fillObjectMenuResponse(menuResponse, player);	
	
}

int LightsaberCrystalComponentImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if (selectedID == 128) {

		ManagedReference<SuiMessageBox*> suiMessageBox = new SuiMessageBox(player, SuiWindowType::TUNE_CRYSTAL);

		suiMessageBox->setPromptTitle("@jedi_spam:confirm_tune_title");
		suiMessageBox->setPromptText("@jedi_spam:confirm_tune_prompt");
		suiMessageBox->setCancelButton(true, "Cancel");
		suiMessageBox->setUsingObject(_this.get());
		suiMessageBox->setCallback(new LightsaberCrystalTuneSuiCallback(player->getZoneServer()));


		player->getPlayerObject()->addSuiBox(suiMessageBox);
		player->sendMessage(suiMessageBox->generateMessage());

	}

	return 0;
}

void LightsaberCrystalComponentImplementation::tuneCrystal(CreatureObject* player) {

	if ((owner == "") && player->hasSkill("force_title_jedi_rank_01")){
			
			String name = player->getDisplayedName();
			setOwner(name);

			// Color code is lime green.
			String tuneName = "\\#00FF00" + postTuneName + " (tuned)";
			setCustomObjectName(tuneName, true);
			player->sendSystemMessage("@jedi_spam:crystal_tune_success");
		} else {
			player->sendSystemMessage("This crystal has already been successfully tuned.");
		
		}
		
}

void LightsaberCrystalComponentImplementation::updateCrystal(int value){

	byte type = 0x02;

	setCustomizationVariable(type, value, true);

}

void LightsaberCrystalComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {

	int colorMax = values->getMaxValue("color");
	int color = values->getCurrentValue("color"); 
	
	if (colorMax != 31) {
		int finalColor = MIN(color, 30);
		setColor(finalColor);
		updateCrystal(finalColor);
	} 	
	else {
		setColor(31);
		updateCrystal(31);
	}


	if (color == 31){
		setQuality(values->getCurrentValue("quality"));
		setAttackSpeed(Math::getPrecision(values->getCurrentValue("attackspeed"), 2));
		setMinimumDamage(MIN(values->getCurrentValue("mindamage"), 50));
		setMaximumDamage(MIN(values->getCurrentValue("maxdamage"), 50));
		setWoundChance(values->getCurrentValue("woundchance"));

		// Following are incoming positive values in script (Due to loot modifier.)
		// Switch to negative number.
		setSacHealth(MIN(values->getCurrentValue("attackhealthcost"), 9) * -1);
		setSacAction(MIN(values->getCurrentValue("attackactioncost"), 9) * -1);
		setSacMind(MIN(values->getCurrentValue("attackmindcost"), 9) * -1);
		setForceCost(MIN(values->getCurrentValue("forcecost"), 9) * -1);
	}
	
	ComponentImplementation::updateCraftingValues(values, firstUpdate);	

}
