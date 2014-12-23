#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	if ((write(1, "Here is some data\n", 18)) != 18)
	{
		write(2, "Error", strlen("Error"));
	}

	exit(0);
}
