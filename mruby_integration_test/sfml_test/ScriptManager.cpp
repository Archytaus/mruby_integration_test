#include "ScriptManager.h"

#include <stdio.h>
#include <mruby\variable.h>
#include <mruby\compile.h>
#include <mruby\data.h>

#include "mrb_vec3.h"
#include "mrb_transform.h"
#include "mrb_scene.h"

#include "FolderHelper.h"

ScriptManager::ScriptManager(void)
{
	mrb = mrb_open();

	init_mrb_vec3(mrb);
	init_mrb_transform(mrb);
	init_mrb_scene(mrb);

	FILE* pFile;
	auto libs = listFilesInDirectory("Assets/Scripts/*.rb");
	for(auto scriptFile : libs)
	{
		if (fopen_s(&pFile, ("Assets/Scripts/" + scriptFile).c_str() , "r") != 0) 
			throw new std::exception("Error opening file.");

		// Load scripts from file system
		mrb_load_file(mrb, pFile);

		fclose(pFile);
	}

#if TEST	

	auto tests = listFilesInDirectory("Assets/Tests/*.rb");
	for(auto scriptFile : tests)
	{
		if (fopen_s(&pFile, ("Assets/Tests/" + scriptFile).c_str() , "r") != 0) 
			throw new std::exception("Error opening file.");

		// Load scripts from file system
		mrb_load_file(mrb, pFile);

		fclose(pFile);
	}

	auto unitTests = listFilesInDirectory("Assets/Tests/Unit/*.rb");
	for(auto scriptFile : unitTests)
	{
		if (fopen_s(&pFile, ("Assets/Tests/Unit/" + scriptFile).c_str() , "r") != 0) 
			throw new std::exception("Error opening file.");

		// Load scripts from file system
		mrb_load_file(mrb, pFile);

		fclose(pFile);
	}

	mrb_load_string(mrb, "report()");

#endif
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

ScriptComponent* ScriptManager::createScriptComponent(EntityId id, class TransformComponent* transformComponent, std::string scriptClass)
{
	return scriptComponents.components[id] = new ScriptComponent(id, transformComponent, scriptClass, mrb);
}