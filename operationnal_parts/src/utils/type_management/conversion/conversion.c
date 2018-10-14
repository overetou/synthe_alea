int	str_to_int(const char* str)
{
	int	n;
	int	res;
	int	i;

	i = 0;
	res = 0;
	n = 1;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\r' || str[i] == '\v'
	|| str[i] == '\n' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	res = res * n;
	return (res);
}
