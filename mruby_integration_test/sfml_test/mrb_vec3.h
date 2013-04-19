#pragma once
#define _ALLOW_KEYWORD_MACROS 
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

#include <glm/glm.hpp>

struct mrb_vec3
{
	glm::vec3* vector;	
public:
	mrb_vec3()
		:vector(nullptr)
	{
	}

	mrb_vec3(glm::vec3* vec)
		:vector(vec)
	{
	}
};

void mrb_vec3_free(mrb_state *mrb, void *p);
mrb_value mrb_vec3_wrap(mrb_state *mrb, struct RClass *tc, struct mrb_vec3 *tm);

mrb_value mrb_vec3_get_x(mrb_state* mrb, mrb_value self);
mrb_value mrb_vec3_set_x(mrb_state* mrb, mrb_value self);

mrb_value mrb_vec3_get_y(mrb_state* mrb, mrb_value self);
mrb_value mrb_vec3_set_y(mrb_state* mrb, mrb_value self);

mrb_value mrb_vec3_get_z(mrb_state* mrb, mrb_value self);
mrb_value mrb_vec3_set_z(mrb_state* mrb, mrb_value self);