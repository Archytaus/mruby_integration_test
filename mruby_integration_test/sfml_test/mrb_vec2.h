#pragma once
#define _ALLOW_KEYWORD_MACROS 
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

#include <glm/glm.hpp>

struct mrb_vec2
{
	glm::vec2* vector;	
	glm::vec2 value;

public:
	mrb_vec2()
		:vector(nullptr), value(0.0f)
	{
	}

	mrb_vec2(glm::vec2* vec)
		:vector(vec)
	{
	}

	mrb_vec2(glm::vec2 vec)
		:value(vec), vector(&value)
	{
	}
};

void mrb_vec2_free(mrb_state *mrb, void *p);

void init_mrb_vec2(mrb_state* mrb);
mrb_value mrb_vec2_wrap(mrb_state *mrb, struct RClass *tc, struct mrb_vec2 *tm);
mrb_vec2* mrb_vec2_get_ptr(mrb_state* mrb, mrb_value value);

mrb_value mrb_vec2_get_x(mrb_state* mrb, mrb_value self);
mrb_value mrb_vec2_set_x(mrb_state* mrb, mrb_value self);

mrb_value mrb_vec2_get_y(mrb_state* mrb, mrb_value self);
mrb_value mrb_vec2_set_y(mrb_state* mrb, mrb_value self);