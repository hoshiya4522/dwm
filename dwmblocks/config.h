//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		    /*Update Interval*/	/*Update Signal*/
	{"   ",	"net-down",	    1,	0},
    {"",	"get-volume",	0,	2},
    {"",	"sb-battery",	    1,	0},
    {"",	"date '+ %I:%M %p '",	    60,	0},
    /* {" ",	"echo [$(\"sb-nettraf\")]",	    1,	1}, */
    /* {"",	"sb-battery",	                5,	10}, */
    /* {"",	"echo [墳 $(\"get-volume\")%]",	0,	2}, */
    /* {"",	"echo [$(\"sb-clock\")]",	    60,	16}, */
};

//Sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char *delim = "   ";

// Have dwmblocks automatically recompile and run when you edit this file in
// vim with the following line in your vimrc/init.vim:

// autocmd BufWritePost ~/.local/src/dwmblocks/config.h !cd ~/.local/src/dwmblocks/; sudo make install && { killall -q dwmblocks;setsid dwmblocks & }
