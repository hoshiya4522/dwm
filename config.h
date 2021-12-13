/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const int user_bh            = 28;     
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[] = {"agave Nerd Font:style=Regular;size=8"};
static const char dmenufont[]       = "agave Nerd Font:style=Regular;size=8";


/* #include "themes/nord.h" */
/* #include "themes/tokyonight-storm.h" */
#include "themes/tokyonight.h"

/* tagging */
static const char *tags[] = { " ", " ", " ", " ", " ", " ", "力 ", " ", " " };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int momentaryalttags = 1; /* 1 means alttags will show only when key is held down*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance    title                  tags mask   isfloating  isterminal  noswallow  monitor */
	/* { "Gimp",       NULL,       NULL,                  0,          1,          0,           0,        -1 }, */
	{ "Gimp",       NULL,       NULL,                  0,          0,          0,           0,        -1 },
	{ "Firefox",    NULL,       NULL,                  1 << 8,     0,          0,          -1,        -1 },
	{ "st",         NULL,       NULL,                  0,          0,          1,           0,        -1 },
	{ "Alacritty",  NULL,       NULL,                  0,          0,          1,           0,        -1 },
	{ "eww-example", NULL,  NULL,  0,          1,          0,           1,        -1 }, /* xev */
	{ "firefox",    "Toolkit",  "Picture-in-Picture",  0,          1,          0,           1,        -1 }, /* xev */
	{ NULL,         NULL,       "Event Tester",        0,          0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#include "./centeredmaster.c"
#include "./deck.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " []=",      tile },    /* first entry is default */
	{ " ><>",      NULL },    /* no layout function means floating behavior */
	{ " [M]",      monocle },
	{ " [D]",      deck },
	{ " |M|",      centeredmaster },
	{ " >M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALT Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
/* static const char *st[]  = { "st", NULL }; */
static const char *alacritty[]  = { "alacritty", NULL };
static const char *firefox[]  = { "firefox", NULL };
static const char *screenshot[]  = { "screenshot", NULL };
static const char *selectScreenshot[]  = { "select-screenshot", NULL };
static const char *upvol[]   = { "vol-up",     NULL };
static const char *downvol[]   = { "vol-down",     NULL };
static const char *mutevol[] = { "vol-mute",  NULL };
static const char *sd[] = { "shutdownAndOthersCTL",  NULL };
static const char *ec[] = { "editConfig",  NULL };
static const char *thunar[] = { "thunar",  NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ ALT,                          XK_t,      spawn,          {.v = alacritty } },
	{ ALT,                          XK_c,      spawn,          {.v = ec } },
	{ ALT,                          XK_f,      spawn,          {.v = thunar } },
	{ ALT,                          XK_b,      spawn,          {.v = firefox } },
	{ ALT,                          XK_s,      spawn,          {.v = screenshot } },
	{ ALT|ShiftMask,                XK_s,      spawn,          {.v = selectScreenshot } },

	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,    {.v = upvol } },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,    {.v = downvol } },
	{ 0,                            XF86XK_AudioMute,         spawn,    {.v = mutevol } },

	{ ALT,                          XK_equal,  spawn,          {.v = upvol } },
	{ ALT,                          XK_minus,  spawn,          {.v = downvol } },
	{ ALT,                          XK_0,      spawn,          {.v = mutevol } },
	{ MODKEY,                       XK_s,      spawn,          {.v = sd } },

	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = alacritty } },
	/* { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = alacritty } }, */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
 	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
 	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
 	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_z, zoom,           {0} },
 	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
 	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_q,      killclient,     {0} },
	/* { MODKEY|ShiftMask,             XK_c,      killclient,     {0} }, */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
 	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	{ MODKEY|ALT,                   XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY|ALT,                   XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ALT,                   XK_0,	   setgaps,        {.i = 10 } },
	{ MODKEY|ALT,					XK_BackSpace,  setgaps,    {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	/* { ClkStatusText,        0,              Button2,        spawn,          {.v = alacritty } }, */
 	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
 	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
 	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

