//
// Created by Arpit Jain on 11/3/18.
//

#ifndef INC_537MAKE_OPTION_PARSER_H
#define INC_537MAKE_OPTION_PARSER_H

#endif //INC_537MAKE_OPTION_PARSER_H

#ifndef INC_537MAKE_STRUCT_INPUT_H
#define INC_537MAKE_STRUCT_INPUT_H
#include "../entities/struct_input.h"
#endif

struct_input parse_and_get_unprocessed_input(int argc, char **argv);

struct_input get_default_input_arg();