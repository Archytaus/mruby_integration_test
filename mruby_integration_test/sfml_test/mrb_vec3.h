#pragma once
#define _ALLOW_KEYWORD_MACROS 
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

#include <glm/glm.hpp>

struct mrb_vec3
{
	glm::vec3* vector;	
	glm::vec3 value;

public:
	mrb_vec3()
		:vector(nullptr), value(0.0f)
	{
	}

	mrb_vec3(glm::vec3* vec)
		:vector(vec)
	{
	}

	mrb_vec3(glm::vec3 vec)
		:value(vec), vector(&value)
	{
	}
};

void mrb_vec3_free(mrb_state *mrb, void *p);

void init_mrb_vec3(mrb_state* mrb);
mrb_value mrb_vec3_wrap(mrb_state *mrb, struct RClass *tc, struct mrb_vec3 *tm);
mrb_vec3* mrb_vec3_get_ptr(mrb_state* mrb, mrb_value value);

mrb_value mrb_vec3_get_x(mrb_state* mrb, mrb_value self);
mrb_value mrb_vec3_set_x(mrb_state* mrb, mrb_value self);

mrb_value mrb_vec3_get_y(mrb_state* mrb, mrb_value self);
mrb_value mrb_vec3_set_y(mrb_state* mrb, mrb_value self);

mrb_value mrb_vec3_get_z(mrb_state* mrb, mrb_value self);
mrb_value mrb_vec3_set_z(mrb_state* mrb, mrb_value self);