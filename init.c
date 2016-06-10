#include "expr.h"
#include "expr.tab.h"
#include <math.h>
#include "math.h"

static struct {
	char *constName;
	double constValue;
} consts[] = {
	"PI",		3.14,
	"E",		2.71,
	"GAMMA",	0.57,
	"DEG",		57.29,
	"PHI",		1.61,
	NULL,		0
};

static struct {
	char *predefName;
	double (*predefFuncPtr) ();
} predefs[] = {
	"sin",		sin,
	"cos",		cos,
	"tg",		tan,
	"log",		Log,
	"abs",		fabs,
	NULL,		0
};

void init(void)
{
	int i;
	Psymbol sp;

	fprintf(stdout, "Loading constants");
	for (i = 0 ; consts[i].constName != NULL; i++)
		sp = installSymbol(consts[i].constName, VAR, consts[i].constValue);
	fprintf(stdout, " (done)\n");
	fprintf(stdout, "Loading functions");
	for (i = 0 ; predefs[i].predefName != NULL ; i++) {
		sp = installSymbol(predefs[i].predefName, PREDEF, 0.0);
		sp->U.func = predefs[i].predefFuncPtr;
	}
	fprintf(stdout, " (done)\n");
}
