#pragma once

#include <mruby.h>
#include <mruby\variable.h>

#define _ALLOW_KEYWORD_MACROS 

#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\System\Time.hpp>

#include "Game.h"

class ScriptInput 
	: public ScriptPart
{
public:
	ScriptInput(mrb_state* mrb, class Game* game);
	Game* _game;
	bool _mouseLock;

	static ScriptInput* _instance;
	virtual void update(sf::Time elapsed);

	void setMouseLock(bool value);
	bool getMouseLock();

protected:
	static mrb_value mrb_input_lock_mouse(mrb_state* mrb, mrb_value self);
	static mrb_value mrb_input_unlock_mouse(mrb_state* mrb, mrb_value self);
	
	static mrb_value mrb_input_mouse_pos(mrb_state* mrb, mrb_value self);
	static mrb_value mrb_input_pressed(mrb_state* mrb, mrb_value self);
	static sf::Keyboard::Key convert_sym_to_key(mrb_state* mrb, mrb_sym symbol);
};
