cmake_minimum_required(VERSION 3.7)

project(Synthe)

set (SRCS
	src/main.c
	src/utils/vector/vector.c
	src/utils/file_management/parsing.c
	src/utils/exit/exit.c
	src/utils/type_management/conversion/conversion.c
	src/utils/type_management/type_questions/type_questions.c
)

include_directories(includes)

add_executable(synthe ${SRCS})
