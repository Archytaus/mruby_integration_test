#include "mrb_input.h"

sf::Keyboard::Key convert_sym_to_key(mrb_state* mrb, mrb_sym symbol)
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

mrb_value mrb_input_pressed(mrb_state* mrb, mrb_value self)
{
	mrb_sym query_pressed;
	mrb_get_args(mrb, "n", &query_pressed);

	return mrb_bool_value(sf::Keyboard::isKeyPressed(convert_sym_to_key(mrb, query_pressed)));
}

void init_mrb_input(mrb_state* mrb)
{
	auto inputClass = mrb_define_class(mrb, "Input", mrb->object_class);

	mrb_define_class_method(mrb, inputClass, "pressed?", mrb_input_pressed, ARGS_REQ(1));
}