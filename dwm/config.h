/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "brave"

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 20;       /* horiz inner gap between windows */
static unsigned int gappiv    = 10;       /* vert inner gap between windows */
static unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 0;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char *fonts[]          = { "JetBrains Mono Nerd Font:size=10", "mohamed-salama:size=12","NotoColorEmoji:pixelsize=8:antialias=true:autohint=true",  };
static char normbgcolor[]     = "#272e33";
static char normbordercolor[] = "#000000";
static char normfgcolor[]     = "#d3c6aa";
static char selfgcolor[]      = "#d3c6aa";
static char selbordercolor[]  = "#ffffff";
static char selbgcolor[]      = "#272e33";
static char *colors[][3]      = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "50x20", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-g", "50x20", "-e", "bc", "-lq", NULL };
const char *spcmd3[] = {TERMINAL, "-n", "spnote", "-g", "50x20", "-e","/home/Aboud/.scripts/notetaking/notetaker", NULL };
const char *spcmd4[] = {TERMINAL, "-n", "splyrics", "-g", "50x20", "-e","lyrics", NULL };
static Sp scratchpads[] = {
	/* ame          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
	{"spnote",      spcmd3},
	{"splyrics",    spcmd4},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    instance      title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,       	    1 << 8,       0,           0,         0,        -1 },
	{ TERMCLASS,  NULL,       NULL,       	    0,            0,           1,         0,        -1 },
	{ NULL,       NULL,       "Event Tester",   0,            0,           0,         1,        -1 },
	{ TERMCLASS, "floatterm", NULL,       	    0,            1,           1,         0,        -1 },
	{ TERMCLASS, "bg",        NULL,       	    1 << 7,       0,           1,         0,        -1 },
	{ TERMCLASS, "spterm",    NULL,       	    SPTAG(0),     1,           1,         0,        -1 },
	{ TERMCLASS, "spcalc",    NULL,       	    SPTAG(1),     1,           1,         0,        -1 },
	{ TERMCLASS, "spnote",    NULL,       	    SPTAG(2),     1,           1,         0,        -1 },
	{ TERMCLASS, "splyrics",  NULL,       	    SPTAG(3),     1,           1,         0,        -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */
	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */
	{ "[D]",	deck },			/* Master on left, slaves in monocle-like mode on right */
	{ "[M]",	monocle },		/* All windows on top of eachother */
	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */
	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color0",		STRING,	&normbordercolor },
		{ "color8",		STRING,	&selbordercolor },
		{ "color0",		STRING,	&normbgcolor },
		{ "color4",		STRING,	&normfgcolor },
		{ "color0",		STRING,	&selfgcolor },
		{ "color4",		STRING,	&selbgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static const Key keys[] = {
	/* modifier         key                      function          argument */
	STACKKEYS(MODKEY,                            focus)
	STACKKEYS(MODKEY|ShiftMask,                  push)
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	{ MODKEY|ControlMask|ShiftMask, XK_q,        quit,             {1} }, 
	{ MODKEY,			XK_0,                    view,             {.ui = ~0 } },
	{ MODKEY|ShiftMask,	XK_0,                    tag,              {.ui = ~0 } },
	{ MODKEY,			XK_q,                    killclient,       {0} },
	{ MODKEY,			XK_Return,          	 spawn,		       {.v = termcmd } },
	{ MODKEY,			XK_w,                    spawn,            {.v = (const char*[]){ BROWSER, NULL } } },
    { MODKEY|ShiftMask,	XK_e,		             spawn,            {.v = (const char*[]){ BROWSER,"gmail.com", NULL } } },
	{ MODKEY|ShiftMask,	XK_w,                    spawn,            {.v = (const char*[]){ BROWSER,"--incognito", NULL } } },
	{ MODKEY|Mod1Mask,	XK_d,                    spawn,            {.v = (const char*[]){ BROWSER,"datacamp.com", NULL } } },
	{ MODKEY|Mod1Mask,	XK_y,                    spawn,            {.v = (const char*[]){ BROWSER,"youtube.com", NULL } } },
	{ MODKEY|Mod1Mask,	XK_c,                    spawn,            {.v = (const char*[]){ BROWSER,"coursera.org", NULL } } },
	{ MODKEY|Mod1Mask,	XK_l,                    spawn,            {.v = (const char*[]){ BROWSER,"lichess.org", NULL } } },
	{ MODKEY|Mod1Mask|ShiftMask,	XK_l,        spawn,            {.v = (const char*[]){ BROWSER,"linkedin.com", NULL } } },
	{ MODKEY|ShiftMask,	XK_s,                    spawn,            {.v = (const char*[]){ BROWSER,"https://excalidraw.com/", NULL } } },
	{ MODKEY|Mod1Mask,	XK_w,                    spawn,            {.v = (const char*[]){ BROWSER,"web.whatsapp.com/", NULL } } },
	{ MODKEY|Mod1Mask,	XK_f,                    spawn,            {.v = (const char*[]){ BROWSER,"facebook.com", NULL } } },
	{ MODKEY,			XK_r,                    spawn,            {.v = (const char*[]){ TERMINAL, "-e", "/home/Aboud/.local/bin/lfub", NULL } } },
    { MODKEY,			XK_m,		             spawn,            {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
    { MODKEY,			XK_e,		             spawn,            {.v = (const char*[]){ TERMINAL,"-e", "nvim", NULL } } },
	{ MODKEY|ShiftMask,	XK_r,                    spawn,            {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ MODKEY,		    XK_grave,                spawn,            {.v = (const char*[]){ TERMINAL, "-e", "zellij", NULL } } },
    { 0,                XF86XK_Calculator,		 spawn,            {.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
    { MODKEY,			XK_period,		         spawn,            {.v = (const char*[]){ TERMINAL, "-e", "newsboat", NULL } } },
	{ MODKEY,			XK_t,                    setlayout,        {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,	XK_t,                    setlayout,        {.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			XK_y,                    setlayout,        {.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,	XK_y,                    setlayout,        {.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			XK_u,                    setlayout,        {.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,	XK_u,                    setlayout,        {.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			XK_i,                    setlayout,        {.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,	XK_i,                    setlayout,        {.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY|ShiftMask,	XK_f,		             setlayout,        {.v = &layouts[8]} },
	{ MODKEY,			XK_o,                    incnmaster,       {.i = +1 } },
	{ MODKEY|ShiftMask,	XK_o,                    incnmaster,       {.i = -1 } },
	{ MODKEY,			XK_a,                    togglegaps,       {0} },
	{ MODKEY|ShiftMask,	XK_a,                    defaultgaps,      {0} },
	{ MODKEY,			XK_s,                    togglesticky,     {0} },
	{ MODKEY,			XK_d,                    spawn,            {.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY|ShiftMask,	XK_d,                    spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/dmenu/passmenu", NULL } } },
	{ MODKEY|ShiftMask,	XK_grave,                spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/dmenu/dmenuunicode", NULL } } },
	{ MODKEY|ShiftMask,	XK_n,                    spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/notetaking/mostRecentNote", NULL } } },
	{ MODKEY|ShiftMask,	XK_c,                    spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/notetaking/buildnote", NULL } } },
	{ MODKEY,			XK_space,                spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/lang", NULL } } },
	{ MODKEY|ShiftMask,	XK_b,                    spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/dmenu/bm.sh", NULL } } },
	{ MODKEY|ShiftMask,	XK_q,                    spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/dmenu/powermenu.sh", NULL } } },
	{ Mod1Mask|ShiftMask,	XK_y,                spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/dmenu/youtubesearch", NULL } } },
	{ Mod1Mask|ShiftMask,	XK_g,                spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/dmenu/googlesearch", NULL } } },
	{ Mod1Mask|ShiftMask,	XK_t,                spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/dmenu/dmenu-translate", NULL } } },
    { MODKEY|ShiftMask,	XK_m,                    spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/mpvscript.sh", NULL } } },
    { Mod1Mask,         XK_o,                    spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/Touchpadoff.sh", NULL } } },
    { Mod1Mask|ShiftMask,  XK_o,                 spawn,            {.v = (const char*[]){ "/home/Aboud/.scripts/Touchpadon.sh", NULL } } },
	{ MODKEY,			XK_Insert,	             spawn,            SHCMD("xdotool type $(grep -v '^#' /home/Aboud/.scripts/dmenu/bookmarks | dmenu -l 10 | cut -d' ' -f1)") },
	{ MODKEY,			XK_f,	               	 togglefullscr,    {0} },
	{ MODKEY,			XK_g,		             shiftview,        { .i = -1 } },
	{ MODKEY|ShiftMask,	XK_g,		             shifttag,         { .i = -1 } },
	{ MODKEY,			XK_h,		             setmfact,         {.f = -0.05} },
	{ MODKEY,			XK_l,		             setmfact,         {.f = +0.05} },
	{ MODKEY,			XK_semicolon,	         shiftview,        { .i = 1 } },
	{ MODKEY|ShiftMask,	XK_semicolon,	         shifttag,         { .i = 1 } },
	{ MODKEY|ShiftMask,	XK_apostrophe,	         togglesmartgaps,  {0} },
	{ MODKEY|ShiftMask,	XK_Return,	             togglescratch,	   {.ui = 0} },
	{ MODKEY,		    XK_c,	                 togglescratch,	   {.ui = 1} },
	{ MODKEY,		    XK_n,                    togglescratch,	   {.ui = 2} },
	{ MODKEY|ShiftMask,	XK_l,                    togglescratch,	   {.ui = 3} },
	{ MODKEY,			XK_z,		             incrgaps,         {.i = +3 } },
	{ MODKEY,			XK_x,		             incrgaps,         {.i = -3 } },
	{ MODKEY,			XK_b,		             togglebar,        {0} },
	{ MODKEY,			XK_Left,	             focusmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,	XK_Left,	             tagmon,           {.i = -1 } },
	{ MODKEY,			XK_Right,	             focusmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,	XK_Right,	             tagmon,           {.i = +1 } },
	{ MODKEY,			XK_Page_Up,	             shiftview,        { .i = -1 } },
	{ MODKEY|ShiftMask,	XK_Page_Up,	             shifttag,         { .i = -1 } },
	{ MODKEY,			XK_Page_Down,	         shiftview,        { .i = +1 } },
	{ MODKEY|ShiftMask,	XK_Page_Down,	         shifttag,         { .i = +1 } },
	{ Mod1Mask,	        XK_s,	                 spawn,            {.v = (const char*[]){"flameshot","gui", NULL } }} ,
    { 0,                XF86XK_AudioMute,		 spawn,            SHCMD("amixer set Master toggle") },
	{ 0,                XF86XK_AudioRaiseVolume, spawn,            SHCMD("amixer set Master 3%+") },
	{ 0,                XF86XK_AudioLowerVolume, spawn,            SHCMD("amixer set Master 3%-") },
   	{ 0,                XF86XK_AudioPlay,		 spawn,            {.v = (const char*[]){ "mpc", "toggle", NULL } } },
   	{ 0,                XF86XK_AudioPrev,		 spawn,            {.v = (const char*[]){ "mpc", "prev", NULL } } },
   	{ 0,                XF86XK_AudioNext,		 spawn,            {.v = (const char*[]){ "mpc", "next", NULL } } },
   	{ MODKEY,           XF86XK_AudioPrev,		 spawn,            {.v = (const char*[]){ "mpc", "seek","-10", NULL } } },
   	{ MODKEY,           XF86XK_AudioNext,	     spawn,            {.v = (const char*[]){ "mpc", "seek","+10", NULL } } },
	{ 0,                XF86XK_Sleep,		     spawn,            {.v = (const char*[]){ "sudo", "-A", "zzz", NULL } } },
    { 0,                XF86XK_MonBrightnessUp,	 spawn,            SHCMD("pkexec light -A 5") },
	{ 0,                XF86XK_MonBrightnessDown,spawn,	           SHCMD("pkexec light -U 5") },
	{ 0,			    XF86XK_Search,           spawn,            {.v = (const char*[]){ "dmenu_run", NULL } } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.config/suckless/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkRootWin,           0,              Button2,        togglebar,      {0} },
};

