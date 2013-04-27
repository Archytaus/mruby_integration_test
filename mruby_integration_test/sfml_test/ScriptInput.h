#pragma once

#include <mruby.h>
#include <mruby\variable.h>

#define _ALLOW_KEYWORD_MACROS 

#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>

#include "Game.h"

class ScriptInput 
{
public:
	ScriptInput(mrb_state* mrb, class Game* game);
	Game* _game;
	
	static ScriptInput* _instance;

protected:
	static mrb_value mrb_input_mouse_pos(mrb_state* mrb, mrb_value self);
	static mrb_value mrb_input_pressed(mrb_state* mrb, mrb_value self);
	static sf::Keyboard::Key convert_sym_to_key(mrb_state* mrb, mrb_sym symbol);
};
