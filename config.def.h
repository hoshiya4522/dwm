/* See LICENSE f1le for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int showWindowNumber = 0;		 /* 1 means show number of windows in monocle and dwck layout. 0 means show the default symbol */
static const unsigned int borderpx		   = 1;        /* border pixel of windows */
static const unsigned int snap       	   = 32;       /* snap pixel */
static const int swallowfloating     	   = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih     	   = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv     	   = 10;       /* vert inner gap between windows */
static const unsigned int gappoh     	   = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov     	   = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps           	   = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar             	   = 1;        /* 0 means no bar */
static const int topbar              	   = 1;        /* 0 means bottom bar */
static const int user_bh             	   = 28;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

static const char *fonts[]      = { "agave Nerd Font:style=Regular;size=8" };
static const char dmenufont[]   =   "agave Nerd Font:style=Regular;size=8";


/* theme */
#include "themes/tokyonight.h"
/* #include "themes/nord.h" */


/* tagging */
static const char *tags[] = { " ", " ", " ", " ", " ", " ", "力 ", " ", " " };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int momentaryalttags = 1; /* 1 means alttags will show only when key is held down*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance    title                  tags mask   isfloating   isterminal  noswallow  monitor */
	{ "Gimp",       NULL,       NULL,                  0,          1,           0,           0,        -1 },
	{ "firefox",    "Toolkit",  "Picture-in-Picture",  0,          1,           0,           1,        -1 },
	{ "Firefox",    NULL,       NULL,                  1 << 8,     0,           0,          -1,        -1 },
	{ "St",         NULL,       NULL,                  0,          0,           1,           0,        -1 },
	{ "Alacritty",  NULL,       NULL,                  0,          0,           1,           0,        -1 },
	{ NULL,         NULL,       "Event Tester",        0,          0,           0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " ﬿",      tile                   },    /* first entry is default */
	{ " ",      monocle                },
	{ " ",      spiral                 },
	{ " ",      dwindle                },
	{ " ﬷",      deck                   },
	{ " ",      bstack                 },
	{ " ﯅",      bstackhoriz            },
	{ " 﩯",     grid                   },
	{ " ",      nrowgrid               },
	{ " ",      horizgrid              },
	{ " ﱖ",      gaplessgrid            },
	{ " ",      centeredmaster         },
	{ " ",      centeredfloatingmaster },
	{ " ",      NULL                   },    /* no layout function means floating behavior */
	{ NULL,      NULL                   },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALT Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,          {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]          = { "alacritty",            NULL };
static const char *alacritty[]        = { "alacritty",            NULL };
static const char *firefox[]          = { "firefox",              NULL };
static const char *screenshot[]       = { "screenshot",           NULL };
static const char *selectScreenshot[] = { "select-screenshot",    NULL };
static const char *upvol[]            = { "vol-up",               NULL };
static const char *downvol[]          = { "vol-down",             NULL };
static const char *mutevol[]          = { "vol-mute",             NULL };
static const char *sd[]               = { "shutdownAndOhersCTL",  NULL };
static const char *ec[]               = { "editConfig",           NULL };
static const char *thunar[]           = { "thunar",               NULL };

#include "movestack.c"

static Key keys[] = {
	/* modifier                     key                       function        argument */
	{ ALT,                          XK_t,                     spawn,          {.v = alacritty } },
	{ ALT,                          XK_c,                     spawn,          {.v = ec } },
	{ ALT,                          XK_f,                     spawn,          {.v = thunar } },
	{ ALT,                          XK_b,                     spawn,          {.v = firefox } },
	{ ALT,                          XK_p,                     spawn,          SHCMD("firefox --private-window") },
	{ ALT,                          XK_s,                     spawn,          {.v = screenshot } },
	{ ALT|ShiftMask,                XK_s,                     spawn,          {.v = selectScreenshot } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,          {.v = upvol } },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,          {.v = downvol } },
	{ 0,                            XF86XK_AudioMute,         spawn,          {.v = mutevol } },
	{ ALT,                          XK_equal,                 spawn,          {.v = upvol } },
	{ ALT,                          XK_minus,                 spawn,          {.v = downvol } },
	{ ALT,                          XK_0,                     spawn,          {.v = mutevol } },
	{ MODKEY,                       XK_s,                     spawn,          {.v = sd } },

	/* modifier                     key		                  function        argument */
	{ MODKEY,                       XK_r,                     spawn,          {.v = dmenucmd } },
	{ MODKEY,		                XK_Return,                spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                     togglebar,      {0} },
	{ MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                     incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                     incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                     setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                     setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,                     movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                     movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,                     setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,                     setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,                     setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_z,	                  zoom,           {0} },
	{ MODKEY|Mod1Mask,              XK_u,                     incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,                     incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,                     incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,                     incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,                     incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,                     incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,                     incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,                     incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,                     incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,                     incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,                     incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,                     incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,                     incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,                     incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,                     togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,                     defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,                   view,           {0} },
	{ MODKEY,		                XK_q,                     killclient,     {0} },
	{ MODKEY,                       XK_t,                     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_e,                     setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[13]} },
	{ MODKEY,                       XK_space,                 setlayout,      {0} },
	{ MODKEY|ControlMask,			XK_comma,                 cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,                cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,                 togglefloating, {0} },
	{ MODKEY,                       XK_Down,                  moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,                    moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,                 moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,                  moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,                  moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,                    moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,                 moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,                  moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,                    moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,                  moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,                  moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,                 moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,                    moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,                  moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,                  moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,                 moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_f,                     togglefullscreen, {0} },
	{ MODKEY|ShiftMask,             XK_f,                     togglefakefullscreen, {0} },
	{ MODKEY,                       XK_0,                     view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                     tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                 focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,                     togglealttag,   {0} },
	{ MODKEY|ShiftMask,             XK_q,                     quit,           {0} },
	
	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */

	/* click                event mask        button          function        argument */
	{ ClkLtSymbol,          0,                Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,           Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,           Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,           Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,        dragmfact,      {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button3,        dragcfact,      {0} },
	{ ClkTagBar,            0,                Button1,        view,           {0} },
	{ ClkTagBar,            0,                Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,           Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,           Button3,        toggletag,      {0} },
};

 
