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
	
	auto vector3Class = mrb_define_class(mrb, "Vec3", mrb->object_class);
	mrb_define_method(mrb, vector3Class, "x", mrb_vec3_get_x, ARGS_NONE());
	mrb_define_method(mrb, vector3Class, "x=", mrb_vec3_set_x, ARGS_REQ(1));

	mrb_define_method(mrb, vector3Class, "y", mrb_vec3_get_y, ARGS_NONE());
	mrb_define_method(mrb, vector3Class, "y=", mrb_vec3_set_y, ARGS_REQ(1));

	mrb_define_method(mrb, vector3Class, "z", mrb_vec3_get_z, ARGS_NONE());
	mrb_define_method(mrb, vector3Class, "z=", mrb_vec3_set_z, ARGS_REQ(1));

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