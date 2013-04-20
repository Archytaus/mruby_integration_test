#pragma once

#define _ALLOW_KEYWORD_MACROS 

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

#include "Camera.h"

struct mrb_camera
{
	class Camera* camera;	
public:
	mrb_camera()
		:camera(nullptr)
	{
	}

	mrb_camera(class Camera* camera)
		:camera(camera)
	{
	}
};

void init_mrb_camera(mrb_state* mrb);
void mrb_camera_free(mrb_state *mrb, void *p);
mrb_value mrb_camera_wrap(mrb_state *mrb, struct RClass *tc, struct mrb_transform *tm);