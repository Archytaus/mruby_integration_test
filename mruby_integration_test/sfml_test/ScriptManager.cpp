#include "ScriptManager.h"

#include <stdio.h>
#include <mruby\variable.h>
#include <mruby\compile.h>
#include <mruby\data.h>
#include "mrb_vec3.h"

mrb_value mrb_empty_method(mrb_state *mrb, mrb_value cv)
{
	return cv;
}

ScriptManager::ScriptManager(void)
{
	mrb = mrb_open();
	
	init_mrb_vec3(mrb);

	FILE* pFile;

	if (fopen_s(&pFile, "Assets/Scripts/test.rb" , "r") != 0) 
		throw new std::exception("Error opening file.");

	// Load scripts from file system
	mrb_load_file(mrb, pFile);

	fclose(pFile);
}

ScriptManager::~ScriptManager(void)
{
}

void ScriptManager::update(sf::Time elapsed)
{
	for(auto kvp : scriptComponents.components)
	{
		kvp.second->onUpdate(elapsed);
	}
}

ScriptComponent* ScriptManager::createScriptComponent(EntityId id, class WorldPositionComponent* worldPositionComponent, std::string scriptClass)
{
	return scriptComponents.components[id] = new ScriptComponent(id, worldPositionComponent, scriptClass, mrb);
}