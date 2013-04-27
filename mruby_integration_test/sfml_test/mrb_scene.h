#pragma once

#define _ALLOW_KEYWORD_MACROS 

#include <mruby.h>
#include <mruby\variable.h>

#include "Camera.h"

void init_mrb_scene(mrb_state* mrb);