#include "mrb_camera.h"

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <mruby/data.h>

#include "mrb_vec2.h"
#include "mrb_vec3.h"

struct mrb_data_type mrb_camera_type = { "Camera", mrb_camera_free };

mrb_value mrb_camera_get_position(mrb_state* mrb, mrb_value camera)
{
	return mrb_iv_get(mrb, camera, mrb_intern_cstr(mrb, "@position"));
}

mrb_value mrb_camera_get_forward(mrb_state* mrb, mrb_value self)
{
	struct mrb_camera *camera = (struct mrb_camera*)mrb_data_get_ptr(mrb, self, &mrb_camera_type);
	return mrb_vec3_wrap(mrb, mrb_class_get(mrb, "Vec3"), new mrb_vec3(camera->camera->forward()));
}

mrb_value mrb_camera_get_right(mrb_state* mrb, mrb_value self)
{
	struct mrb_camera *camera = (struct mrb_camera*)mrb_data_get_ptr(mrb, self, &mrb_camera_type);
	return mrb_vec3_wrap(mrb, mrb_class_get(mrb, "Vec3"), new mrb_vec3(camera->camera->right()));
}

mrb_value mrb_camera_move(mrb_state* mrb, mrb_value self)
{
	mrb_value new_value;
	mrb_get_args(mrb, "o", &new_value);
	mrb_vec3* arg = mrb_vec3_get_ptr(mrb, new_value);
	
	struct mrb_camera *camera = (struct mrb_camera*)mrb_data_get_ptr(mrb, self, &mrb_camera_type);
	camera->camera->offsetPosition(*arg->vector);

	return mrb_nil_value();
}

mrb_value mrb_camera_rotate(mrb_state* mrb, mrb_value self)
{
	mrb_value new_value;
	mrb_get_args(mrb, "o", &new_value);
	mrb_vec2* arg = mrb_vec2_get_ptr(mrb, new_value);

	if(!arg)
		return mrb_nil_value();

	struct mrb_camera *camera = (struct mrb_camera*)mrb_data_get_ptr(mrb, self, &mrb_camera_type);
	camera->camera->offsetOrientation(arg->vector->y, arg->vector->x);

	return mrb_nil_value();
}

void init_mrb_camera(mrb_state* mrb)	
{
	auto cameraClass = mrb_define_class(mrb, "Camera", mrb->object_class);

	mrb_define_method(mrb, cameraClass, "position", mrb_camera_get_position, ARGS_NONE());
	mrb_define_method(mrb, cameraClass, "forward", mrb_camera_get_forward, ARGS_NONE());
	mrb_define_method(mrb, cameraClass, "right", mrb_camera_get_right, ARGS_NONE());

	mrb_define_method(mrb, cameraClass, "move", mrb_camera_move, ARGS_REQ(1));
	mrb_define_method(mrb, cameraClass, "rotate", mrb_camera_rotate, ARGS_REQ(1));
}

void mrb_camera_free(mrb_state *mrb, void *p)
{
}

mrb_value mrb_camera_wrap(mrb_state *mrb, struct RClass *tc, struct mrb_camera *camera)
{
	return mrb_obj_value(Data_Wrap_Struct(mrb, tc, &mrb_camera_type, camera));
}