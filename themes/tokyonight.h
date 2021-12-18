static const char bar[]       = "#16161E";
static const char hl[]       = "#7aa2f7";
static const char sel[]       = "#c0caf5";
static const char black[]       = "#c0caf5";
static const char white[]       = "#c0caf5";


static const char *colors[][3]      = {
	/*                 fg       bg       border   */
	/* [SchemeNorm]   = { white, bar, hl }, */
	[SchemeNorm]   = { white, bar, hl },
	[SchemeSel]    = { bar, hl, white},
	[SchemeTitle]  = { white, bar, white },
};

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", bar, "-nf", white, "-sb", hl, "-sf", bar, NULL };
