#include "ScriptInput.h"
#include "mrb_vec2.h"

ScriptInput* ScriptInput::_instance = nullptr;

sf::Keyboard::Key ScriptInput::convert_sym_to_key(mrb_state* mrb, mrb_sym symbol)
{
	if (symbol == mrb_intern(mrb, "w"))
		return sf::Keyboard::W;

	if (symbol == mrb_intern(mrb, "s"))
		return sf::Keyboard::S;

	if (symbol == mrb_intern(mrb, "a"))
		return sf::Keyboard::A;

	if (symbol == mrb_intern(mrb, "d"))
		return sf::Keyboard::D;

	return sf::Keyboard::Key::Unknown;
}

mrb_value ScriptInput::mrb_input_pressed(mrb_state* mrb, mrb_value self)
{
	mrb_sym query_pressed;
	mrb_get_args(mrb, "n", &query_pressed);

	return mrb_bool_value(sf::Keyboard::isKeyPressed(convert_sym_to_key(mrb, query_pressed)));
}

mrb_value ScriptInput::mrb_input_mouse_pos(mrb_state* mrb, mrb_value self)
{
	auto vec2Class = mrb_class_get(mrb, "Vec2");
	auto position = sf::Mouse::getPosition(*_instance->_game->window);
	return mrb_vec2_wrap(mrb, vec2Class, new mrb_vec2(glm::vec2(position.x, position.y)));
}

ScriptInput::ScriptInput(mrb_state* mrb, Game* game)
	: _game(game)
{
	_instance = this;

	auto inputClass = mrb_define_class(mrb, "Input", mrb->object_class);
	
	mrb_define_class_method(mrb, inputClass, "pressed?", (&ScriptInput::mrb_input_pressed), ARGS_REQ(1));
	mrb_define_class_method(mrb, inputClass, "mouse_pos", (&ScriptInput::mrb_input_mouse_pos), ARGS_NONE());
}