/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 0;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:pixelsize=15:antialias=true:autohint=true", "JoyPixels:size=12:antialias=true:autohint=true" };
/* static const char *fonts2[]          = { "NotoColorEmoji:pixelsize=15:antialias=true:autohint=true" }; */
static const char dmenufont[]       = "JetBrainsMono Nerd Font:pixelsize=12:antialias=true:autohint=true";


/* For using fonts with Xresources, uncoment the folowing an coment the old static font chars */

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






/* static const char col_gray1[]       = "#222222"; */
/* static const char col_gray2[]       = "#444444"; */
/* static const char col_gray3[]       = "#bbbbbb"; */
/* static const char col_gray4[]       = "#eeeeee"; */
/* static const char col_cyan[]        = "#005577"; */
static const unsigned int baralpha = 0xdd;
static const unsigned int borderalpha = OPAQUE;
/* static const char *colors[][3]      = { */
/* 	/1*               fg         bg         border   *1/ */
/* 	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 }, */
/* 	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  }, */
/* }; */




static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", " ", "ﭮ ", "", "", "", "爵 ", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance    title       tags mask     isfloating   monitor */
	{ "discord",     NULL,        NULL,        1<<3,         0,           -1 },
	{ "Thunderbird", NULL,        NULL,        4,            0,           -1 },
	{ "Clementine",  NULL,        NULL,        1 << 4,       0,           -1 },
	{ "Alacritty",   NULL,        "notetaker", 0,            1,           -1 },
	{ "Gimp",        NULL,        NULL,        0,            1,           -1 },
	{ "Firefox",     NULL,        NULL,        1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, "-l", "20", NULL };
static const char *st[]  = { "st", NULL };
static const char *alacritty[]  = { "alacritty", NULL };
static const char *ranger[]  = { "alacritty","-e","ranger", NULL };
static const char *lf[]  = { "alacritty", "-e", "lfueberzug", NULL };
static const char *slock[]  = { "slock", NULL };
static const char *brave[]  = { "brave", NULL };
static const char *nemo[]  = { "nemo", NULL };
static const char *thunderbird[]  = { "thunderbird", NULL };
static const char *newsboat[]  = { "alacritty","-e","newsboat", NULL };
static const char *discord[]  = { "discord", NULL };

static const char *clementine[]  = { "clementine", NULL };
static const char *clementinemute[]  = { "clementine", "-t", NULL };
static const char *clementineprevioustrack[]  = { "clementine", "-r", NULL };
static const char *clementinenexttrack[]  = { "clementine", "-f", NULL };
static const char *clementineup[]  = { "clementine", "--volume-up", NULL };
static const char *clementinedown[]  = { "clementine", "--volume-down", NULL };

static const char *notetaker[]  = { "alacritty", "--title=notetaker", "-e", "notetaker", NULL };
static const char *notepdf[]  = { "notepdf", NULL };


/* You obviously need the X11 development packages installed, X11proto in particular */
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
static const char *mutemicvol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
static const char *brightnessup[] = { "light", "-A", "10", NULL };
static const char *brightnessdown[] = { "light", "-U", "10", NULL };


/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color0",       STRING,  &normbordercolor },
		{ "color8",       STRING,  &selbordercolor },
		{ "color0",       STRING,  &normbgcolor },
		{ "color0",       STRING,  &selbgcolor },
		{ "color4",       STRING,  &normfgcolor },
		{ "color4",       STRING,  &selfgcolor },
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


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                  XK_Super_L,         spawn,          {.v = dmenucmd } },
    { 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                       XF86XK_AudioMute,        spawn, {.v = mutevol } },
	{ 0,                       XF86XK_AudioMicMute,     spawn, {.v = mutemicvol } },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
	{ 0,                       XF86XK_MonBrightnessUp,  spawn, {.v = brightnessup   } },
	{ 0,                       XF86XK_MonBrightnessDown,spawn, {.v = brightnessdown   } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = ranger } },
	{ MODKEY,                       XK_a,      spawn,          {.v = lf } },
	{ MODKEY,                       XK_Return, spawn,          {.v = st } },
	{ MODKEY|ControlMask,           XK_t,      spawn,          {.v = alacritty } },

	{ MODKEY,                       XK_y,      spawn,          {.v = notetaker } },
	{ MODKEY|ShiftMask,             XK_y,      spawn,          {.v = notepdf } },
	{ MODKEY,                       XK_b,      spawn,          {.v = brave } },

	{ MODKEY,                       XK_c,      spawn,          {.v = clementine } },
	{ MODKEY,                       XK_plus,   spawn,          {.v = clementineup } },
	{ MODKEY,                       XK_minus,  spawn,          {.v = clementinedown } },
	{ MODKEY|ControlMask,           XK_plus,   spawn,          {.v = clementinenexttrack } },
	{ MODKEY|ControlMask,           XK_minus,  spawn,          {.v = clementineprevioustrack} },
	{ MODKEY|ControlMask,           XK_m,      spawn,          {.v = clementinemute } },

	{ MODKEY,                       XK_n,      spawn,          {.v = nemo } },
	{ MODKEY,                       XK_t,      spawn,          {.v = thunderbird } },
	{ MODKEY,                       XK_d,      spawn,          {.v = discord } },
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
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },

	{ MODKEY|ControlMask|ShiftMask, XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },

	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	{ MODKEY|ControlMask,           XK_k,  setgaps,        {.i = -5 } },
	{ MODKEY|ControlMask,           XK_j,  setgaps,        {.i = +5 } },
	{ MODKEY|ControlMask,           XK_u,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ControlMask,           XK_o,  setgaps,        {.i = GAP_TOGGLE} },

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

	{ MODKEY,                       XK_s,      spawn,          {.v = slock } },
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = st } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

