#include "ScriptManager.h"

#include <stdio.h>

mrb_value mrb_empty_method(mrb_state *mrb, mrb_value cv)
{
	return cv;
}

ScriptManager::ScriptManager(void)
{
	mrb = mrb_open();

	FILE* pFile;
	
	if (fopen_s(&pFile, "Assets/Scripts/test.rb" , "r") != 0) 
		throw new std::exception("Error opening file.");

	// Load scripts from file system
	mrb_load_file(mrb, pFile);
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

ScriptComponent* ScriptManager::createScriptComponent(EntityId id, std::string scriptClass)
{
	return new ScriptComponent(id, scriptClass, mrb);
}