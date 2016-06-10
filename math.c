#include <math.h>
#include <errno.h>
#include "math.h"

extern int errno;
double errorCheck(double value, char *mess);

double Log(double x)
{
	return errorCheck(log(x), "Log");
}

void warning(const char *mess, const char *type);
double errorCheck(double value, char *mess)
{
	if (errno != 0)
	{
		switch(errno) {
			case EDOM:	warning(mess, "Invalid argument"); break;
			case ERANGE:	warning(mess, "Out of range");	break;
			default:	warning(mess, "Unknown");	break;		
		}
		errno = 0;
	}
	return value;
}
