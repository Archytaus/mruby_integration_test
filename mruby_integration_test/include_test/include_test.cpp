// include_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	mrb_state *mrb = mrb_open();
	char code[] = "p 'hello world!'";
	printf("Executing Ruby code from C!\n");

	mrb_load_string(mrb, code);

	getchar();

	return 0;
}