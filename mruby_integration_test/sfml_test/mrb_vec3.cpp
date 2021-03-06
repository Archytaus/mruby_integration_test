#include "mrb_vec3.h"

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

#include <glm/glm.hpp>
#include <glm\core\func_geometric.hpp>

struct mrb_data_type mrb_vec3_type = { "Vec3", mrb_vec3_free };

void mrb_vec3_free(mrb_state *mrb, void *ptr)
{
	mrb_free(mrb, ptr);
}

mrb_value mrb_vec3_wrap(mrb_state *mrb, struct RClass *tc, struct mrb_vec3 *tm)
{
	return mrb_obj_value(Data_Wrap_Struct(mrb, tc, &mrb_vec3_type, tm));
}

mrb_vec3* mrb_vec3_get_ptr(mrb_state* mrb, mrb_value value)
{
	return (mrb_vec3*)mrb_data_get_ptr(mrb, value, &mrb_vec3_type);
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

mrb_value mrb_vec3_plus(mrb_state* mrb, mrb_value self)
{
	mrb_value new_value;
	int args = mrb_get_args(mrb, "o", &new_value);
	mrb_vec3* arg =(struct mrb_vec3*)mrb_data_get_ptr(mrb, new_value, &mrb_vec3_type);
	mrb_vec3* selfValue = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);

	if (!arg) return mrb_nil_value();

	return mrb_vec3_wrap(mrb, mrb_class_get(mrb, "Vec3"), new mrb_vec3(
		glm::vec3(selfValue->vector->x + arg->vector->x, 
		selfValue->vector->y + arg->vector->y,
		selfValue->vector->z + arg->vector->z)));
}

mrb_value mrb_vec3_equals(mrb_state* mrb, mrb_value self)
{
	mrb_value new_value;
	int args = mrb_get_args(mrb, "o", &new_value);
	mrb_vec3* arg =(struct mrb_vec3*)mrb_data_get_ptr(mrb, new_value, &mrb_vec3_type);
	mrb_vec3* selfValue = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);

	if (!arg) return mrb_nil_value();

	return mrb_bool_value(
		selfValue->vector->x == arg->vector->x &&
		selfValue->vector->y == arg->vector->y &&
		selfValue->vector->z == arg->vector->z);
}

mrb_value mrb_vec3_subtract(mrb_state* mrb, mrb_value self)
{
	mrb_value new_value;
	int args = mrb_get_args(mrb, "o", &new_value);
	mrb_vec3* arg =(struct mrb_vec3*)mrb_data_get_ptr(mrb, new_value, &mrb_vec3_type);
	mrb_vec3* selfValue = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);

	if (!arg) return mrb_nil_value();

	return mrb_vec3_wrap(mrb, mrb_class_get(mrb, "Vec3"), new mrb_vec3(
		glm::vec3(
		selfValue->vector->x - arg->vector->x, 
		selfValue->vector->y - arg->vector->y,
		selfValue->vector->z - arg->vector->z)));
}

mrb_value mrb_vec3_usubtract(mrb_state* mrb, mrb_value self)
{
	mrb_vec3* selfValue = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);

	if (!selfValue) return mrb_nil_value();

	return mrb_vec3_wrap(mrb, mrb_class_get(mrb, "Vec3"), new mrb_vec3(
		glm::vec3(
			0 - selfValue->vector->x, 
			0 - selfValue->vector->y,
			0 - selfValue->vector->z)));
}

mrb_value mrb_vec3_times(mrb_state* mrb, mrb_value self)
{
	mrb_vec3* selfValue = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);

	mrb_value new_value;
	mrb_get_args(mrb, "o", &new_value);
	mrb_vec3* arg =(struct mrb_vec3*)mrb_data_get_ptr(mrb, new_value, &mrb_vec3_type);

	if (arg)
	{
		return mrb_vec3_wrap(mrb, mrb_class_get(mrb, "Vec3"), new mrb_vec3(
			glm::vec3(selfValue->vector->x * arg->vector->x, 
			selfValue->vector->y * arg->vector->y,
			selfValue->vector->z * arg->vector->z)));
	}

	mrb_float modifier;
	mrb_get_args(mrb, "f", &modifier);
	if(modifier)
	{
		return mrb_vec3_wrap(mrb, mrb_class_get(mrb, "Vec3"), new mrb_vec3(
			glm::vec3(selfValue->vector->x * modifier, 
			selfValue->vector->y * modifier,
			selfValue->vector->z * modifier)));
	}

	return mrb_nil_value();
}

mrb_value mrb_vec3_divide(mrb_state* mrb, mrb_value self)
{
	mrb_vec3* selfValue = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);

	mrb_value new_value;
	mrb_get_args(mrb, "o", &new_value);
	mrb_vec3* arg =(struct mrb_vec3*)mrb_data_get_ptr(mrb, new_value, &mrb_vec3_type);

	if (arg)
	{
		return mrb_vec3_wrap(mrb, mrb_class_get(mrb, "Vec3"), new mrb_vec3(
			glm::vec3(selfValue->vector->x / arg->vector->x, 
			selfValue->vector->y / arg->vector->y,
			selfValue->vector->z / arg->vector->z)));
	}

	mrb_float modifier;
	mrb_get_args(mrb, "f", &modifier);
	if(modifier)
	{
		return mrb_vec3_wrap(mrb, mrb_class_get(mrb, "Vec3"), new mrb_vec3(
			glm::vec3(selfValue->vector->x / modifier, 
			selfValue->vector->y / modifier,
			selfValue->vector->z / modifier)));
	}

	return mrb_nil_value();
}

mrb_value mrb_vec3_initialize(mrb_state *mrb, mrb_value self)
{
	mrb_float x, y, z;
	int n;
	struct mrb_vec3 *tm;

	tm = (struct mrb_vec3*)DATA_PTR(self);
	if (tm) {
		mrb_vec3_free(mrb, tm);
	}
	DATA_TYPE(self) = &mrb_vec3_type;
	DATA_PTR(self) = NULL;

	n = mrb_get_args(mrb, "|f|ff", &x, &y, &z); // 1 or 3 float arguments
	tm = (struct mrb_vec3 *)mrb_malloc(mrb, sizeof(struct mrb_vec3));

	if (n == 0)
	{
		tm->value = glm::vec3();
	}
	if (n == 1)
	{
		tm->value = glm::vec3(x);
	}
	else if (n == 3)
	{
		tm->value = glm::vec3(x, y, z);
	}

	tm->vector = &tm->value;
	DATA_PTR(self) = tm;
	return self;
}

mrb_value mrb_vec3_normalize(mrb_state* mrb, mrb_value self)
{
	mrb_vec3* selfValue = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);
	mrb_vec3* result = new mrb_vec3(glm::normalize(*selfValue->vector));

	return mrb_vec3_wrap(mrb, mrb_class_get(mrb, "Vec3"), result);
}

mrb_value mrb_vec3_length(mrb_state* mrb, mrb_value self)
{
	mrb_vec3* selfValue = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);

	return mrb_float_value(glm::length(*selfValue->vector));
}

mrb_value mrb_vec3_distance(mrb_state* mrb, mrb_value self)
{
	mrb_value new_value;
	int args = mrb_get_args(mrb, "o", &new_value);
	mrb_vec3* arg =(struct mrb_vec3*)mrb_data_get_ptr(mrb, new_value, &mrb_vec3_type);
	mrb_vec3* selfValue = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);

	if (!arg) return mrb_nil_value();

	return mrb_float_value(glm::distance(*selfValue->vector, *arg->vector));
}

mrb_value mrb_vec3_dot(mrb_state* mrb, mrb_value self)
{
	mrb_value new_value;
	int args = mrb_get_args(mrb, "o", &new_value);
	mrb_vec3* arg =(struct mrb_vec3*)mrb_data_get_ptr(mrb, new_value, &mrb_vec3_type);
	mrb_vec3* selfValue = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);

	if (!arg) return mrb_nil_value();

	return mrb_float_value(glm::dot(*selfValue->vector, *arg->vector));
}

mrb_value mrb_vec3_inspect(mrb_state* mrb, mrb_value self)
{
	char buf[256];
	int len;
	
	mrb_vec3* selfValue = (struct mrb_vec3*)mrb_data_get_ptr(mrb, self, &mrb_vec3_type);
	if (!selfValue) return mrb_nil_value();
	
	len = snprintf(buf, sizeof(buf), "[%.4f,%.4f,%.4f]",
		selfValue->vector->x, selfValue->vector->y, selfValue->vector->z);
	return mrb_str_new(mrb, buf, len);
}

void init_mrb_vec3(mrb_state* mrb)
{
	auto vector3Class = mrb_define_class(mrb, "Vec3", mrb->object_class);
	MRB_SET_INSTANCE_TT(vector3Class, MRB_TT_DATA);

	mrb_define_method(mrb, vector3Class, "x", mrb_vec3_get_x, ARGS_NONE());
	mrb_define_method(mrb, vector3Class, "x=", mrb_vec3_set_x, ARGS_REQ(1));

	mrb_define_method(mrb, vector3Class, "y", mrb_vec3_get_y, ARGS_NONE());
	mrb_define_method(mrb, vector3Class, "y=", mrb_vec3_set_y, ARGS_REQ(1));

	mrb_define_method(mrb, vector3Class, "z", mrb_vec3_get_z, ARGS_NONE());
	mrb_define_method(mrb, vector3Class, "z=", mrb_vec3_set_z, ARGS_REQ(1));

	mrb_define_method(mrb, vector3Class, "+", mrb_vec3_plus, ARGS_REQ(1));
	mrb_define_method(mrb, vector3Class, "-", mrb_vec3_subtract, ARGS_REQ(1));
	mrb_define_method(mrb, vector3Class, "-@", mrb_vec3_usubtract, ARGS_NONE());
	mrb_define_method(mrb, vector3Class, "*", mrb_vec3_times, ARGS_REQ(1));
	mrb_define_method(mrb, vector3Class, "/", mrb_vec3_divide, ARGS_REQ(1));

	mrb_define_method(mrb, vector3Class, "normalize", mrb_vec3_normalize, ARGS_NONE());
	mrb_define_method(mrb, vector3Class, "length", mrb_vec3_length, ARGS_NONE());

	mrb_define_method(mrb, vector3Class, "dot", mrb_vec3_dot, ARGS_REQ(1));
	mrb_define_method(mrb, vector3Class, "distance_to", mrb_vec3_distance, ARGS_REQ(1));

	mrb_define_method(mrb, vector3Class, "==", mrb_vec3_equals, ARGS_REQ(1));

	mrb_define_method(mrb, vector3Class, "initialize", mrb_vec3_initialize, ARGS_ANY());

	mrb_define_method(mrb, vector3Class, "to_s", mrb_vec3_inspect, ARGS_NONE());
	mrb_define_method(mrb, vector3Class, "inspect", mrb_vec3_inspect, ARGS_NONE());
}