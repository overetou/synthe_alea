#ifndef	CORE_H
#define CORE_H

#include "utils.h"

t_vector*	initialize(int argc, char **arg_str);
void		do_operations(t_vector* spectrum);
void		finish(t_vector* spectrum);

#endif
