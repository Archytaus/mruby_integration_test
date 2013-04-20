#include "mrb_scene.h"

mrb_value mrb_scene_get_camera(mrb_state* mrb, mrb_value scene)
{
	return mrb_iv_get(mrb, scene, mrb_intern_cstr(mrb, "@camera"));
}

void init_mrb_scene(mrb_state* mrb)
{
	auto sceneClass = mrb_define_class(mrb, "Scene", mrb->object_class);
	mrb_define_class_method(mrb, sceneClass, "camera", mrb_scene_get_camera, ARGS_NONE());
}