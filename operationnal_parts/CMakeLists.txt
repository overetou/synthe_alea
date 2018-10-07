project(Synthe)

set (SRCS
	src/main.c
)

include_directories(includes)

add_executable(synthe ${SRCS})
