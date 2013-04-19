#include "mrb_transform.h"

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

struct mrb_data_type mrb_transform_type = { "TransformComponent", mrb_transform_free };

mrb_value mrb_transform_get_position(mrb_state* mrb, mrb_value transform)
{
	return mrb_iv_get(mrb, transform, mrb_intern_cstr(mrb, "@position"));
}

mrb_value mrb_transform_get_rotation(mrb_state* mrb, mrb_value transform)
{
	auto rotation = mrb_intern_cstr(mrb, "@rotation");
	return mrb_iv_get(mrb, transform, rotation);
}

mrb_value mrb_transform_get_scale(mrb_state* mrb, mrb_value transform)
{
	return mrb_iv_get(mrb, transform, mrb_intern_cstr(mrb, "@scale"));
}

void init_mrb_transform(mrb_state* mrb)	
{
	auto transformClass = mrb_define_class(mrb, "TransformComponent", mrb->object_class);

	mrb_define_method(mrb, transformClass, "position", mrb_transform_get_position, ARGS_NONE());
	mrb_define_method(mrb, transformClass, "rotation", mrb_transform_get_rotation, ARGS_NONE());
	mrb_define_method(mrb, transformClass, "scale", mrb_transform_get_scale, ARGS_NONE());
}

void mrb_transform_free(mrb_state *mrb, void *p)
{
}

mrb_value mrb_transform_wrap(mrb_state *mrb, struct RClass *tc, struct mrb_transform *tm)
{
	return mrb_obj_value(Data_Wrap_Struct(mrb, tc, &mrb_transform_type, tm));
}