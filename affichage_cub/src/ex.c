#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av)
{
	int *tab = malloc(sizeof(int) * (ac - 1));
	int tofind = atoi(av[1]);
	int amt = ac;
	int pre = ac;

	while (amt > 2) {
		tab[amt - 1] = atoi(av[amt - 1]);
		--amt;
	}
	amt = ac - 1;
	while (tab[amt] != tofind)
	{
		pre = amt;
		if (tab[amt] > tofind)
			amt -= amt == ac - 1 ? amt / 2 : (pre - amt) / 2;
		else
			amt += (pre - amt) / 2;
		printf("pre = %d, amt = %d\n", pre, amt);
	}
	printf("tab[%d] = %d, tofind was %d\n", amt, tab[amt], tofind);
	return (0);
}
