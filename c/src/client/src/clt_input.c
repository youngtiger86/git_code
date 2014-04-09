#include "clt_common.h"

/* Jump over the blanks and table synbol in cline from pos. */
#define DEL_BLANK(pos, cline); \
{\
	while (cline[pos] != '\0' && (cline[pos] == ' ' || cline[pos] == '\t')) \
	{\
		pos++;\
	}\
}

#if 0
/* To get a command in cline from pos. */
#define GET_ARG(arg, pos, cline); \
{\
	int i = 0; \

	while (cline[pos] != '\0' && cline[pos] != ' ' && cline[pos] != '\t') \
	{\
		arg[i] = cline[pos]; \
		i++; \
		pos++; \
	} \
}
#endif

#define GET_ARG(arg, pos, cline) \
{\
	int j = 0; \
	while (cline[pos] != '\0' && cline[pos] != ' ' && cline[pos] != '\t')\
	{\
		arg[j] = cline[pos];\
		j++;\
		pos++;\
	}\
}

/* Split the command input by the user.  */
int split(cmd_line_t * command, char cline[])
{
	int i;
	int pos = 0;

	cline[strlen(cline) - 1] = '\0';
	
	for (i = 0; i < MAX_ARG; ++i)
	{
		DEL_BLANK(pos, cline);
		if (NULL == (command->argv[i] = (char *)malloc(MAX_LENGTH)))
		{
			perror("fail to malloc");
			// free the spaces.
			return -1;
		}

		GET_ARG(command->argv[i], pos, cline);
	}

	command->argv[i] = NULL;	/* The command array ends with a NULL. */
	command->name = command->argv[0];	/* The command is just the first argument. */

	return i;
}
