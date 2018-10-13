#include "../includes/utils.h"
#define TEST_ARRAY_LENGTH 1
//every test function returns true or false. Char type is used as return because it is the smallest type in term of memory usage.

void	do_tests(test_array* (char*)(*))
{
	int 	i = 0;
	char	visual[TEST_ARRAY_LENGTH];

	while (i != TEST_ARRAY_LENGTH)
	{
		if (test_array[i])
			visual[i] = '.';
		else
		{
			printf("Test %n failed\n", i);
			visual[i] = 'X';
		}
		i++;
	}
	printf("%s\n", visual);
}

char	test_vector_extraction
{
	
}


//main creates an array of test functions and test them one by one.
int	main(void)
{
	test_array	(char*)(*)[TEST_ARRAY_LENGTH];
	
	test_array[0] = test_vector_extraction();

	do_tests(test_array);
	return (0);
}
