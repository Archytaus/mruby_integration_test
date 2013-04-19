#pragma once
#define _ALLOW_KEYWORD_MACROS 
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

#include "TransformComponent.h"

struct mrb_transform
{
	class TransformComponent* transform;	
public:
	mrb_transform()
		:transform(nullptr)
	{
	}

	mrb_transform(class TransformComponent* transform)
		:transform(transform)
	{
	}
};

void init_mrb_transform(mrb_state* mrb);
void mrb_transform_free(mrb_state *mrb, void *p);
mrb_value mrb_transform_wrap(mrb_state *mrb, struct RClass *tc, struct mrb_transform *tm);