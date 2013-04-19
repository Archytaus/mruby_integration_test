#include "mrb_vec3.h"

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

#include <glm/glm.hpp>

struct mrb_data_type mrb_vec3_type = { "Vec3", mrb_vec3_free };

void mrb_vec3_free(mrb_state *mrb, void *p)
{
}

mrb_value mrb_vec3_wrap(mrb_state *mrb, struct RClass *tc, struct mrb_vec3 *tm)
{
	return mrb_obj_value(Data_Wrap_Struct(mrb, tc, &mrb_vec3_type, tm));
}

mrb_value mrb_vec3_get_x(mrb_state* mrb, mrb_value self)
{
	struct mrb_vec3 *vec = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);

	return mrb_float_value(vec->vector->x);
}

mrb_value mrb_vec3_set_x(mrb_state* mrb, mrb_value self)
{
	mrb_value new_value;
	mrb_get_args(mrb, "f", &new_value);

	struct mrb_vec3 *vec = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);
	vec->vector->x = mrb_float(new_value);

	return new_value;
}

mrb_value mrb_vec3_get_y(mrb_state* mrb, mrb_value self)
{
	struct mrb_vec3 *vec = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);

	return mrb_float_value(vec->vector->y);
}

mrb_value mrb_vec3_set_y(mrb_state* mrb, mrb_value self)
{
	mrb_value new_value;
	mrb_get_args(mrb, "f", &new_value);

	struct mrb_vec3 *vec = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);
	vec->vector->y = mrb_float(new_value);

	return new_value;
}

mrb_value mrb_vec3_get_z(mrb_state* mrb, mrb_value self)
{
	struct mrb_vec3 *vec = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);

	return mrb_float_value(vec->vector->z);
}

mrb_value mrb_vec3_set_z(mrb_state* mrb, mrb_value self)
{
	mrb_value new_value;
	mrb_get_args(mrb, "f", &new_value);
	struct mrb_vec3 *vec = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);
	vec->vector->z = mrb_float(new_value);

	return new_value;
}

void init_mrb_vec3(mrb_state* mrb)
{
	auto vector3Class = mrb_define_class(mrb, "Vec3", mrb->object_class);
	mrb_define_method(mrb, vector3Class, "x", mrb_vec3_get_x, ARGS_NONE());
	mrb_define_method(mrb, vector3Class, "x=", mrb_vec3_set_x, ARGS_REQ(1));

	mrb_define_method(mrb, vector3Class, "y", mrb_vec3_get_y, ARGS_NONE());
	mrb_define_method(mrb, vector3Class, "y=", mrb_vec3_set_y, ARGS_REQ(1));

	mrb_define_method(mrb, vector3Class, "z", mrb_vec3_get_z, ARGS_NONE());
	mrb_define_method(mrb, vector3Class, "z=", mrb_vec3_set_z, ARGS_REQ(1));
}