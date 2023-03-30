/* See LICENSE file for copyright and license details. */
/* appearance */
#define TERMINAL "st"
#define TERMINALCLASS "St"
#define BROWSER "brave"
#define FIRE "librewolf"

#include <X11/Xutil.h>
#include <string.h>
static const unsigned int borderpx  = 2;        /* border pixel of windows */
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

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */

static const unsigned int stairpx   = 20;       /* depth of the stairs layout */
static const int stairdirection     = 1;        /* 0: left-aligned, 1: right-aligned */
static const int stairsamesize      = 1;        /* 1 means shrink all the staired windows to the same size */

static const double activeopacity   = 1.0f;     /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity = 1.0f;   /* Window opacity when it's inactive (0 <= opacity <= 1) */
static       Bool bUseOpacity       = True;     /* Starts with opacity on any unfocused windows */
static const double defaultopacity  = 1.0;

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
static char red[]           = "#FF00FF";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#a9b1d6";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeTray] = { normfgcolor, normbgcolor, normbordercolor },
       // [SchemeTray] = { red, red, red },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  red  },
       // [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */


static const unsigned int baralpha = 0xdd;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int trayalpha = 0xff;


static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeTray] = { OPAQUE, baralpha, borderalpha },
	// [SchemeTray] = { trayalpha, trayalpha, trayalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", " ", " ", "ﭮ ", "", "", "", "爵 ", "" };

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */


#include "scratchtagwins.c"

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	instance          title       tags mask  switchtotag isfloating confocus isterminal noswallow opacity monitor float x,y,w,h floatborderpx scratch key*/
	{ "thunderbird", NULL,             NULL,           1<<2, 1,          0,         1,       0,         0,        1.0,     -1,     0,0,1000,700, borderpx,      0   },
	{ "discord",     NULL,             NULL,           1<<3, 1,          0,         1,       0,         0,        1.0,     -1,     0,0,1000,700, borderpx,      0   },
	{ "Clementine",  NULL,             NULL,           1<<4, 1,          0,         1,       0,         0,        1.0,     -1,     0,0,1000,700, borderpx,      0   },
	{ "Audacity",    NULL,             NULL,           1<<4, 1,          0,         1,       0,         0,        1.0,     -1,     0,0,1000,700, borderpx,      0   },
	{ "Thunar",      NULL,             NULL,           1<<5, 1,          1,         1,       0,         0, defaultopacity, -1,     0,0,1000,700, borderpx,      0   },
	{ "TIPP10",      NULL,             NULL,           1<<6, 1,          0,         1,       0,         0,        1.0,     -1,     0,0,1000,700, borderpx,      0   },
	{ FIRE,          NULL,             NULL,           1<<7, 1,          0,         1,       0,         0,        1.0,     -1,     0,0,1000,700, borderpx,      0   },
	{ TERMINALCLASS, NULL,             "newsboat",     1<<8, 1,          0,         1,       0,         0,        1.0,     -1,     0,0,1000,700, borderpx,      0   },
	{ TERMINALCLASS, NULL,             "ncmpcpp",      1<<4, 1,          1,         1,       0,         0,        1.0,     -1,     0,0,1000,700, borderpx,      0   },
	{ TERMINALCLASS, NULL,             "notetaker",    0,    0,          1,         1,       0,         0,        1.0,     -1,     0,0,1000,700, borderpx,      0   },
	{ TERMINALCLASS, NULL,             "lf",           0,    0,          1,         1,       0,         0,        1.0,     -1,     0,0,1000,700, borderpx,      'l' },
	{ TERMINALCLASS, NULL,             "ranger",       0,    0,          1,         1,       0,         0,        1.0,     -1,     0,0,1000,700, 10,            0   },
	{ "Alacritty",   NULL,             NULL,           0,    0,          1,         1,       0,         0,        1.0,     -1,     0,0,1000,700, borderpx,      0   },
	{ TERMINALCLASS, "float",          NULL,           0,    0,          1,         1,       1,         0,        1.1,     -1,     0,0,1000,700, borderpx,      0   },
	{ TERMINALCLASS, TERMINAL,         TERMINAL,       0,    0,          0,         1,       1,         0,        1.1,     -1,     0,0,1000,700, borderpx,      0   },
	{ "gimp",        NULL,             NULL,           0,    0,          0,         1,       0,         0,        1.0,     -1,     0,0,1000,700, borderpx,      0   },
	{ NULL,          NULL,             "Event Tester", 0,    0,          0,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      0   }, /* xev */
	{ "panel",       NULL,             NULL,           0,    0,          0,         0,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      0   },
	{ NULL,          NULL,             "htop",         0,    0,          1,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      'h' },
	{ NULL,          NULL,             "bc",           0,    0,          1,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      'b' },
	{ NULL,          "scratchpad",     NULL,           0,    0,          1,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      's' },
	{ NULL,          "scratchtagwin1", NULL,           0,    0,          1,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      '1' },
	{ NULL,          "scratchtagwin2", NULL,           0,    0,          1,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      '2' },
	{ NULL,          "scratchtagwin3", NULL,           0,    0,          1,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      '3' },
	{ NULL,          "scratchtagwin4", NULL,           0,    0,          1,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      '4' },
	{ NULL,          "scratchtagwin5", NULL,           0,    0,          1,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      '5' },
	{ NULL,          "scratchtagwin6", NULL,           0,    0,          1,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      '6' },
	{ NULL,          "scratchtagwin7", NULL,           0,    0,          1,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      '7' },
	{ NULL,          "scratchtagwin8", NULL,           0,    0,          1,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      '8' },
	{ NULL,          "scratchtagwin9", NULL,           0,    0,          1,         1,       0,         1,        1.0,     -1,     0,0,1000,700, borderpx,      '9' },
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
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-F", "-c", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, "-l", "20", NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-F", "-c", "-fn", dmenufont, "-l", "20", NULL };
static const char *rofi[]  = { "rofi", "-show-icons", "-show", "drun", NULL };
static const char *killscript[]  = { "killscript", NULL };
static const char *term[]  = { TERMINAL, NULL };
static const char *termfloat[]  = { TERMINAL, "-n", "float", NULL };
static const char *ranger[]  = { TERMINAL, "-t", "ranger" ,"-e","ranger", NULL };
static const char *lf[]  = { TERMINAL, "-t", "lf", "-e", "lfueberzug", NULL };
static const char *slock[]  = { "slock", NULL };
static const char *brave[]  = { BROWSER, NULL };
static const char *firefox[]  = { FIRE, NULL };
static const char *surf[]  = { "tabbed", "-c", "surf", "-e", NULL };
static const char *nemo[]  = { "nemo", NULL };
static const char *thunderbird[]  = { "thunderbird", NULL };
static const char *newsboat[]  = { TERMINAL, "-t", "newsboat", "-e","newsboat", NULL };
static const char *discord[]  = { "discord", NULL };

static const char *clementine[]  = { "clementine", NULL };
// static const char *clementinemute[]  = { "clementine", "-t", NULL };
static const char *musicmute[]  = { "musicmute", NULL };
static const char *clementineprevioustrack[]  = { "clementine", "-r", NULL };
static const char *clementinenexttrack[]  = { "clementine", "-f", NULL };
static const char *clementineup[]  = { "clementine", "--volume-up", NULL };
static const char *clementinedown[]  = { "clementine", "--volume-down", NULL };
static const char *ncmpcpp[]  = { TERMINAL, "-t", "ncmpcpp", "-e", "ncmpcpp", NULL };

static const char *notetaker[]  = { TERMINAL, "-t", "notetaker", "-e", "notetaker", NULL };
static const char *notepdf[]  = { "notepdf", NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchpad_htop[] = {"h", TERMINAL, "-t", "htop", "-e", "htop", NULL};
static const char *scratchpad_bc[] = {"b", TERMINAL, "-t", "bc", "-e", "bc", "-q", NULL};
static const char *scratchpad[] = {"s", TERMINAL, "-n", "scratchpad", NULL};
static const char *scratchtagwin1[] = { "1", TERMINAL, "-n", "scratchtagwin1",  NULL };
static const char *scratchtagwin2[] = { "2", TERMINAL, "-n", "scratchtagwin2",  NULL };
static const char *scratchtagwin3[] = { "3", TERMINAL, "-n", "scratchtagwin3",  NULL };
static const char *scratchtagwin4[] = { "4", TERMINAL, "-n", "scratchtagwin4",  NULL };
static const char *scratchtagwin5[] = { "5", TERMINAL, "-n", "scratchtagwin5",  NULL };
static const char *scratchtagwin6[] = { "6", TERMINAL, "-n", "scratchtagwin6",  NULL };
static const char *scratchtagwin7[] = { "7", TERMINAL, "-n", "scratchtagwin7",  NULL };
static const char *scratchtagwin8[] = { "8", TERMINAL, "-n", "scratchtagwin8",  NULL };
static const char *scratchtagwin9[] = { "9", TERMINAL, "-n", "scratchtagwin9",  NULL };


// static const char *scratchtagwin1[] = { "1", "tabbed", "-p", "s+1", "-n", "scratchtagwin1", "-g", "1195x672", "-c", TERMINAL, "-w", NULL };
// static const char *scratchtagwin2[] = { "2", "tabbed", "-p", "s+1", "-n", "scratchtagwin2", "-g", "1195x672", "-c", TERMINAL, "-w", NULL };
// static const char *scratchtagwin3[] = { "3", "tabbed", "-p", "s+1", "-n", "scratchtagwin3", "-g", "1195x672", "-c", TERMINAL, "-w", NULL };
// static const char *scratchtagwin4[] = { "4", "tabbed", "-p", "s+1", "-n", "scratchtagwin4", "-g", "1195x672", "-c", TERMINAL, "-w", NULL };
// static const char *scratchtagwin5[] = { "5", "tabbed", "-p", "s+1", "-n", "scratchtagwin5", "-g", "1195x672", "-c", TERMINAL, "-w", NULL };
// static const char *scratchtagwin6[] = { "6", "tabbed", "-p", "s+1", "-n", "scratchtagwin6", "-g", "1195x672", "-c", TERMINAL, "-w", NULL };
// static const char *scratchtagwin7[] = { "7", "tabbed", "-p", "s+1", "-n", "scratchtagwin7", "-g", "1195x672", "-c", TERMINAL, "-w", NULL };
// static const char *scratchtagwin8[] = { "8", "tabbed", "-p", "s+1", "-n", "scratchtagwin8", "-g", "1195x672", "-c", TERMINAL, "-w", NULL };
// static const char *scratchtagwin9[] = { "9", "tabbed", "-p", "s+1", "-n", "scratchtagwin9", "-g", "1195x672", "-c", TERMINAL, "-w", NULL };





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
	{ term,          "" },
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
	{ MODKEY|ShiftMask,             XK_p, spawn, SHCMD("dmenupac") },
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
	{ MODKEY,                       XK_Return, spawn,          {.v = term } },
	{ MODKEY|ControlMask,           XK_t,      spawn,          {.v = termfloat } },

	{ MODKEY,                       XK_y,      spawn,          {.v = notetaker } },
	{ MODKEY|ShiftMask,             XK_y,      spawn,          {.v = notepdf } },
	{ MODKEY,                       XK_b,      spawn,          {.v = brave } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = surf } },

	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = clementine } },
	{ MODKEY,                       XK_plus,   spawn,          {.v = clementineup } },
	{ MODKEY,                       XK_minus,  spawn,          {.v = clementinedown } },
	{ MODKEY|ControlMask,           XK_plus,   spawn,          {.v = clementinenexttrack } },
	{ MODKEY|ControlMask,           XK_minus,  spawn,          {.v = clementineprevioustrack} },
	{ MODKEY|ControlMask,           XK_m,      spawn,          {.v = musicmute } },
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
	{ MODKEY,           XK_c,  togglescratch,  {.v = scratchpad_bc } },
	{ MODKEY,           XK_x,  togglescratch,  {.v = scratchpad_htop } },
	{ MODKEY|ShiftMask, XK_x,  togglescratch,  {.v = scratchpad } },

	SCRATCHTAGWIN_KEY (scratchtagwin1, 1)
	SCRATCHTAGWIN_KEY (scratchtagwin2, 2)
	SCRATCHTAGWIN_KEY (scratchtagwin3, 3)
	SCRATCHTAGWIN_KEY (scratchtagwin4, 4)
	SCRATCHTAGWIN_KEY (scratchtagwin5, 5)
	SCRATCHTAGWIN_KEY (scratchtagwin6, 6)
	SCRATCHTAGWIN_KEY (scratchtagwin7, 7)
	SCRATCHTAGWIN_KEY (scratchtagwin8, 8)
	SCRATCHTAGWIN_KEY (scratchtagwin9, 9)
	{ Mod4Mask|Mod1Mask|ShiftMask,     XK_0,  makescratchtagwin,  {.i = 0} },
	{ Mod4Mask|Mod1Mask|ShiftMask,     XK_s,  makescratchtagwin,  {.i = 's'} },

	{ MODKEY|ShiftMask,		XK_KP_Add, changeopacity,	{.f = +0.1}},
	{ MODKEY|ShiftMask,		XK_KP_Subtract, changeopacity,  {.f = -0.1}},

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


