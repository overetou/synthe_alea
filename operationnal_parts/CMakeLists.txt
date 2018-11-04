cmake_minimum_required(VERSION 3.7)

project(Synthe)

set (SRCS
	src/utils/vector/vector.c
	src/utils/file_management/parsing.c
	src/utils/exit/exit.c
	src/utils/type_management/conversion/conversion.c
	src/utils/type_management/type_questions/type_questions.c
	src/core/initialize.c
	src/core/do_operations.c
	src/core/finish.c
)

include_directories(includes)

add_executable(synthe_exe src/main.c ${SRCS})
add_executable(test_exe tests/test_main.c ${SRCS})
