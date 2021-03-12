#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac < 4)
		return 0;
	int r = atoi(av[1]), g = atoi(av[2]), b = atoi(av[3]);
	int color = 0;
	
	color += r << 0;
	color += g << 8;
	color += b << 16;
	printf("color = %x\n", (unsigned int)color);
	return 1;
}
