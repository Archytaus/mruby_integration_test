#include "mrb_scene.h"

void init_mrb_scene(mrb_state* mrb)
{
	auto sceneClass = mrb_define_class(mrb, "Scene", mrb->object_class);
}