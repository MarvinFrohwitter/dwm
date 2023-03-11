/* See LICENSE file for copyright and license details. */
/* appearance */

#include <X11/Xutil.h>
#include <string.h>
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */

static const unsigned int stairpx   = 20;       /* depth of the stairs layout */
static const int stairdirection     = 1;        /* 0: left-aligned, 1: right-aligned */
static const int stairsamesize      = 1;        /* 1 means shrink all the staired windows to the same size */

static const double activeopacity   = 1.0f;     /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity = 1.0f;   /* Window opacity when it's inactive (0 <= opacity <= 1) */
static       Bool bUseOpacity       = True;     /* Starts with opacity on any unfocused windows */
static const int user_bh            = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:pixelsize=12:antialias=true:autohint=true",
					"JoyPixels:size=12:antialias=true:autohint=true" };
/* static const char *fonts2[]          = { "NotoColorEmoji:pixelsize=15:antialias=true:autohint=true" }; */
static const char dmenufont[]       = "JetBrainsMono Nerd Font:pixelsize=12:antialias=true:autohint=true";


/* For using fonts with Xresources, uncomment the following an comment the old static font chars */

/* static char font[]            = "monospace:size=10"; */
/* static char dmenufont[]       = "monospace:size=10"; */
/* static const char *fonts[]          = { font }; */


static char normbgcolor[]           = "#11121D";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#a9b1d6";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */


static const unsigned int baralpha = 0xdd;
static const unsigned int borderalpha = OPAQUE;


static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", " ", " ", "ﭮ ", "", "", "", "爵 ", "" };

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	instance title       tags mask switchtotag isfloating isterminal noswallow monitor float x,y,w,h floatborderpx*/
	{ "thunderbird", NULL,    NULL,        1 << 2,        1,          0,     0,           0,      -1,  0,0,1000,700,      5},
	{ "discord",     NULL,    NULL,        1 << 3,        1,          0,     0,           0,      -1,  0,0,1000,700,      5},
	{ "Clementine",  NULL,    NULL,        1 << 4,        1,          0,     0,           0,      -1,  0,0,1000,700,      5},
	{ "Thunar",      NULL,    NULL,        1 << 5,        1,          1,     0,           0,      -1,  0,0,1000,700,      5},
	{ "TIPP10",      NULL,    NULL,        1 << 6,        1,          0,     0,           0,      -1,  0,0,1000,700,      5},
	{ "firefox",     NULL,    NULL,        1 << 7,        1,          0,     0,           0,      -1,  0,0,1000,700,      5},
	{ "Alacritty",   NULL,    "newsboat",  1 << 8,        1,          0,     0,           0,      -1,  0,0,1000,700,      5},
	{ "Alacritty",   NULL,    "notetaker", 0,             0,          1,     0,           0,      -1,  0,0,1000,700,      5},
	{ "Alacritty",   NULL,    "ncmpcpp",   1 << 4,        1,          1,     0,           0,      -1,  0,0,1000,700,      5},
	{ "Alacritty",   NULL,    NULL,        0,             0,          1,     0,           0,      -1,  0,0,1000,700,      5},
	{ "St",          NULL,    NULL,        0,             0,          0,     1,           0,      -1,  0,0,1000,700,      5},
	{ "gimp",        NULL,    NULL,        0,             0,          0,     0,           0,      -1,  0,0,1000,700,      5},
	{ NULL,          NULL, "Event Tester", 0,             0,          0,     0,           1,      -1,  0,0,1000,700,      5}, /* xev */
};



/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */
static Bool isfakefullscreen  = False;     /* enables fakefullscreen */


#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "helper.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|||",      col },
	{ "[S]",      stairs },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* custom symbols for nr. of clients in monocle layout */
/* when clients >= LENGTH(monocles), uses the last element */
static const char *monocles[] = { "[1]", "[2]", "[3]", "[4]", "[5]", "[6]", "[7]", "[8]", "[9]", "[9+]" };


/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include <X11/XF86keysym.h>
#include "movestack.c"

#define STATUSBAR "dwmblocks"

/* commands */
 static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-F", "-c", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, "-l", "20", NULL };
static const char *rofi[]  = { "rofi", "-show-icons", "-show", "drun", NULL };
static const char *killscript[]  = { "killscript", NULL };
static const char *st[]  = { "st", NULL };
static const char *alacritty[]  = { "alacritty", NULL };
static const char *ranger[]  = { "alacritty","-e","ranger", NULL };
static const char *lf[]  = { "alacritty", "-e", "lfueberzug", NULL };
static const char *slock[]  = { "slock", NULL };
static const char *brave[]  = { "brave", NULL };
static const char *firefox[]  = { "firefox", NULL };
static const char *surf[]  = { "tabbed", "-c", "surf", "-e", NULL };
static const char *nemo[]  = { "nemo", NULL };
static const char *thunderbird[]  = { "thunderbird", NULL };
static const char *newsboat[]  = { "alacritty", "--title=newsboat", "-e","newsboat", NULL };
static const char *discord[]  = { "discord", NULL };

static const char *clementine[]  = { "clementine", NULL };
static const char *clementinemute[]  = { "clementine", "-t", NULL };
static const char *clementineprevioustrack[]  = { "clementine", "-r", NULL };
static const char *clementinenexttrack[]  = { "clementine", "-f", NULL };
static const char *clementineup[]  = { "clementine", "--volume-up", NULL };
static const char *clementinedown[]  = { "clementine", "--volume-down", NULL };
static const char *ncmpcpp[]  = { "alacritty","--title=ncmpcpp", "-e", "ncmpcpp", NULL };

static const char *notetaker[]  = { "alacritty", "--title=notetaker", "-e", "notetaker", NULL };
static const char *notepdf[]  = { "notepdf", NULL };


/* You obviously need the X11 development packages installed, X11proto in particular */

/* static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%", NULL }; */
/* static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%", NULL }; */
/* static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL }; */
/* static const char *mutemicvol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL }; */
static const char *brightnessup[] = { "light", "-A", "10", NULL };
static const char *brightnessdown[] = { "light", "-U", "10", NULL };
static const char *layoutmenu_cmd = "layoutmenu.sh";

static const Launcher launchers[] = {
       /* command       name to display */
	{ brave,         "" },
	{ st,            "" },
	{ thunderbird,   "" },
	{ firefox,       "" },
	{ nemo,          "" }
};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color0",       STRING,  &normbordercolor },
		{ "color8",       STRING,  &selbordercolor },
		{ "color0",       STRING,  &normbgcolor },
		{ "color0",       STRING,  &selbgcolor },
		{ "color7",       STRING,  &normfgcolor },
		{ "color7",       STRING,  &selfgcolor },
		/* { "font",               STRING,  &font }, */
		/* { "dmenufont",          STRING,  &dmenufont }, */
		/* { "normbgcolor",        STRING,  &normbgcolor }, */
		/* { "normbordercolor",    STRING,  &normbordercolor }, */
		/* { "normfgcolor",        STRING,  &normfgcolor }, */
		/* { "selbgcolor",         STRING,  &selbgcolor }, */
		/* { "selbordercolor",     STRING,  &selbordercolor }, */
		/* { "selfgcolor",         STRING,  &selfgcolor }, */
		/* { "borderpx",          	INTEGER, &borderpx }, */
		/* { "snap",          		INTEGER, &snap }, */
		/* { "showbar",          	INTEGER, &showbar }, */
		/* { "topbar",          	INTEGER, &topbar }, */
		/* { "nmaster",          	INTEGER, &nmaster }, */
		/* { "resizehints",       	INTEGER, &resizehints }, */
		/* { "mfact",      	 	FLOAT,   &mfact }, */
};


static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_z, spawn, SHCMD("dmenumount") },
	{ MODKEY,                       XK_v, spawn, SHCMD("dmenuunicode") },
	{ MODKEY,                       XK_g, spawn, SHCMD("dmenuhandler") },
	{ MODKEY,                       XK_m, spawn, SHCMD("dmenumpd") },
	{ MODKEY|ShiftMask,             XK_m, spawn, SHCMD("dmenumpc") },
	{ MODKEY,                  XK_Super_L,         spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,              XK_r,         spawn,          {.v = rofi } },
	/* { 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } }, */
	/* { 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } }, */
	/* { 0,                       XF86XK_AudioMicMute,     spawn, {.v = mutemicvol } }, */
	/* { 0,                       XF86XK_AudioMute,        spawn, {.v = mutevol } }, */

	{ 0,                       XF86XK_AudioLowerVolume, spawn, SHCMD("/usr/bin/pactl set-sink-volume 0 -5% ;kill -44 $(pidof dwmblocks)") },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn,  SHCMD("/usr/bin/pactl set-sink-volume 0 +5% ;kill -44 $(pidof dwmblocks)") },

	{ 0,                       XF86XK_AudioMicMute,     spawn, SHCMD("/usr/bin/pactl set-sink-mute 0 toggle ; kill -44 $(pidof dwmblocks)") },
	{ 0,                       XF86XK_AudioMute,        spawn, SHCMD("/usr/bin/pactl set-sink-mute 0 toggle ; kill -44 $(pidof dwmblocks)") },

	{ 0,                       XF86XK_MonBrightnessUp,  spawn, {.v = brightnessup   } },
	{ 0,                       XF86XK_MonBrightnessDown,spawn, {.v = brightnessdown   } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = ranger } },
	{ MODKEY,                       XK_a,      spawn,          {.v = lf } },
	{ MODKEY,                       XK_Return, spawn,          {.v = st } },
	{ MODKEY|ControlMask,           XK_t,      spawn,          {.v = alacritty } },

	{ MODKEY,                       XK_y,      spawn,          {.v = notetaker } },
	{ MODKEY|ShiftMask,             XK_y,      spawn,          {.v = notepdf } },
	{ MODKEY,                       XK_b,      spawn,          {.v = brave } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = surf } },

	{ MODKEY,                       XK_c,      spawn,          {.v = clementine } },
	{ MODKEY,                       XK_plus,   spawn,          {.v = clementineup } },
	{ MODKEY,                       XK_minus,  spawn,          {.v = clementinedown } },
	{ MODKEY|ControlMask,           XK_plus,   spawn,          {.v = clementinenexttrack } },
	{ MODKEY|ControlMask,           XK_minus,  spawn,          {.v = clementineprevioustrack} },
	{ MODKEY|ControlMask,           XK_m,      spawn,          {.v = clementinemute } },
	{ MODKEY|ControlMask,           XK_n,      spawn,	   {.v = ncmpcpp } },

	{ MODKEY,                       XK_n,      spawn,          {.v = nemo } },
	{ MODKEY,                       XK_t,      spawn,          {.v = thunderbird }},
	{ MODKEY,                       XK_d,      spawn,	   {.v = discord } },
	{ MODKEY,                       XK_r,      spawn,          {.v = newsboat } },

	{ MODKEY,                       XK_o,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ControlMask,                       XK_Return, zoom,           {0} },

	{ ControlMask|Mod4Mask,              XK_j,      incrgaps,       {.i = +1 } },
	{ ControlMask|Mod4Mask,              XK_k,      incrgaps,       {.i = -1 } },
	{ ControlMask|ShiftMask,    XK_j,      incrigaps,      {.i = +1 } },
	{ ControlMask|ShiftMask,    XK_k,      incrigaps,      {.i = -1 } },
	{ ControlMask|Mod4Mask,              XK_h,      incrogaps,      {.i = +1 } },
	{ ControlMask|Mod4Mask,              XK_l,      incrogaps,      {.i = -1 } },
	/* { ControlMask,              XK_6,      incrihgaps,     {.i = +1 } }, */
	/* { ControlMask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } }, */
	/* { ControlMask,              XK_7,      incrivgaps,     {.i = +1 } }, */
	/* { ControlMask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } }, */
	/* { ControlMask,              XK_8,      incrohgaps,     {.i = +1 } }, */
	/* { ControlMask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } }, */
	/* { ControlMask,              XK_9,      incrovgaps,     {.i = +1 } }, */
	/* { ControlMask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } }, */

	{ ControlMask,              XK_0,      togglegaps,     {0} },
	{ ControlMask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },

	{ MODKEY|ControlMask|ShiftMask, XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,	    	XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },

	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ControlMask,           XK_f,      toggleactualfullscr,  {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,                       XK_a,      toggleopacity,  {0} },
	{ MODKEY|ShiftMask,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY|ControlMask,           XK_space,  focusmaster,    {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },


	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY,                       XK_w, scratchpad_show, {0} },
	{ MODKEY|ShiftMask,             XK_w, scratchpad_hide, {0} },
	{ MODKEY|ControlMask,           XK_w,scratchpad_remove,{0} },

	{ MODKEY,                       XK_s,  spawn,           {.v = slock } },
	{ MODKEY|ShiftMask,             XK_e,  reloadafterquit, {.v = killscript } },
	{ MODKEY,                       XK_e,  reloadafterquitwithsig, {.v = killscript } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	/* { ClkLtSymbol,          0,              Button1,        setlayout,      {0} }, */
	/* { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} }, */
	/* { ClkWinTitle,          0,              Button2,        zoom,           {0} }, */
	/* { ClkStatusText,        0,              Button2,        spawn,          {.v = st } }, */

	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
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


