#include "../includes/utils.h"
#define TEST_ARRAY_LENGTH 2
//every test function returns true or false. Char type is used as return because it is the smallest type in term of memory usage.

char	is_digit_test(void)
{
	return (is_digit('0') && is_digit('9') && !is_digit('x') && !is_digit('/') && !is_digit(':'));
}

char	str_to_int_test(void)
{
	return (1552 == str_to_int("1552") && 0 == str_to_int("0") && -966235 == str_to_int("-966235") && 0 == str_to_int("potiron"));
}

void	do_tests(char	(**test_array)(void))
{
	int 	i = 0;
	char	visual[TEST_ARRAY_LENGTH];

	while (i != TEST_ARRAY_LENGTH)
	{
		if ((*test_array[i])())
			visual[i] = '.';
		else
		{
			printf("Test %n failed\n", i);
			visual[i] = 'X';
		}
		i++;
	}
	visual[TEST_ARRAY_LENGTH] = 0;
	printf("%s\n", visual);
}

//main creates an array of test functions with an array of function pointers and test them one by one.
//To add one test just increment TEST_ARRAY_LENGTH by one on the second line and add the function to its corresponding index on the array in the main.
//You can also do freestyle testing by calling whatever function you want, however you want.
int	main(void)
{
	char	(*test_array[TEST_ARRAY_LENGTH])(void);
	
	test_array[0] = is_digit_test;
	test_array[1] = str_to_int_test;

	do_tests(test_array);
	return (0);
}
