#pragma once

#include <mruby.h>
#include <mruby\variable.h>

#define _ALLOW_KEYWORD_MACROS 

#include <SFML\Window\Keyboard.hpp>

void init_mrb_input(mrb_state* mrb);