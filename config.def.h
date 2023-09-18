/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 10;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;        /* vert inner gap between windows */
static const unsigned int gappoh    = 10;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;        /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int snap      = 15;       /* snap pixel, controls how far the window must be from the
                                                   window area border until it snaps against that border */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 5;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first 
                                                   monitor, False: display systray on the last monitor */
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */

/* Some app's icons may not work properly with 11-12 font size in the system tray */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=13", "NotoColorEmoji:pixelsize=18:antialias=true:autohint=true", "monospace:size=13" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=13" ;

static const char norm_fg[] = "#fafafa";
static const char norm_bg[] = "#1a1b26";
static const char norm_border[] = "#000000";
static const char sel_fg[] = "#7aa2f7";
static const char sel_bg[] = "#1a1b26";
static const char sel_border[] = "#000000";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "" };
static const char *alttags[] = { "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* To get the class name use "xprop WM_CLASS" command */

    /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
    { "tauonmb",          NULL,     NULL,           0,         1,          0,           0,        -1 },
    { "KeePassXC",        NULL,     NULL,           0,         1,          0,           0,        -1 },
    { "transmission-gtk", NULL,     NULL,           0,         1,          0,           0,        -1 },
    { "firefox",          NULL,     NULL,           1 << 1,    0,          0,          -1,        -1 },
    { "st",               NULL,     NULL,           0,         0,          1,           0,        -1 },
    { "Alacritty",        NULL,     NULL,           0,         0,          1,           0,        -1 },
    { "TelegramDesktop",  NULL,     NULL,           0,         1,          0,           0,        -1 },
    { "Blueman-manager",  NULL,     NULL,           0,         1,          0,           0,        -1 },
    { NULL,               NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "shiftview.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
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
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont };
static const char *dmenucmd[] = { "dmenu-recent-aliases" };

static const char *termcmd[]  = { "alacritty", NULL };
static const char scratchpadname[] = "scratchpad";
// static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "80x20", NULL };
static const char *scratchpadcmd[] = { "alacritty", "-T", scratchpadname, NULL };

static const Key keys[] = {
    /* modifier                     key        function        argument */
    /* Dmenu */
    { Mod1Mask,                       XK_space,      spawn,          {.v = dmenucmd } },
    /* Lanunch terminal */
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    /* Launch scratchpad */
    { MODKEY|ShiftMask,             XK_Return,  togglescratch,  {.v = scratchpadcmd } },
    /* Toggle status bar    */
    { MODKEY,                       XK_b,      togglebar,      {0} },
    /* Move to another terminal     */
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    /* Move to another ternminal    */
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    /* Increase the amount of windows in master area */
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    /* Decrease the amount of windows in master area    */
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    /* Make the primary area smaller */
    { MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
    /* Make the primary area larger */
    { MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
    /* Toggle master and stack  */
    { MODKEY,                       XK_f,      zoom,           {0} },
    /* Increase all gaps */
    { MODKEY,                       XK_equal,      incrgaps,       {.i = +1 } },
    /* Decrease all gaps*/
    { MODKEY,                       XK_minus,      incrgaps,       {.i = -1 } },
    /* Increase inner gaps */
    /* { MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },*/
    /* Decrease inner gaps */
    /* { MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },*/
    /*  Increase outer gaps */
    /* { MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },*/
    /*  Decrease outer gaps */
    /* { MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },*/
    /*  Increase inner horizontal gaps */
    /* { MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },*/
    /*  Decrease inner horizontal gaps */
    /* { MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },*/
    /*  Increase inner vertical gaps */
    /* { MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },*/
    /*  Decrease inner vertical gaps */
    /* { MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },*/
    /*  Increase outer horizontal gaps */
    /* { MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },*/
    /*  Decrease outer horizontal gaps */
    /* { MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },*/
    /*  Increase outer vertical gaps */
    /* { MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },*/
    /*  Decrease outer vertical gaps */
    /* { MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },*/
    /*  Toggle gaps */
    /* { MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },*/
    /* Reset gaps back to default */
    { MODKEY|ShiftMask,             XK_equal,      defaultgaps,    {0} },
    /* Cycle through the two last tags  */
    { MODKEY,                       XK_Tab,    view,           {0} },
    /* Kill a window    */
    { MODKEY,                       XK_q,      killclient,     {0} },
    /* Tiled layout */
    { MODKEY,                       XK_w,      setlayout,      {.v = &layouts[0]} },
    /* Floating layout  */
    { MODKEY,                       XK_e,      setlayout,      {.v = &layouts[1]} },
    /* Monocle layout   */
    { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[2]} },
    /* Spiral layout */
    /* { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },*/
    /* Dwindle layout */
    /* { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[4]} },*/
    /* Deck layout */
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[5]} },
    /* Bstack layout */
    /* { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[6]} },*/
    /* Bstackhoriz layout */
    /* { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[7]} },*/
    /* Grid layout */
    /* { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[8]} },*/
    /* Nrowgrid layout */
    /* { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[9]} },*/
    /* Horizgrid layout */
    /* { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[10]} },*/
    /* Gaplessgrid layout */
    /* { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[11]} },*/
    /* Centeredmaster layout */
    /* { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[12]} },*/
    /* Centeredfloatingmaster layout */
    /* { MODKEY,                     XK_r,      setlayout,      {.v = &layouts[13]} },*/
    /* Cycle through the two last layouts   */
    /*{ MODKEY|ShiftMask,             XK_w,  setlayout,      {0} },*/
    /* Toggle floating mode on the active window    */
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    /* Toggle always-on-top for one floating window    */
    { MODKEY|ShiftMask,             XK_p,  togglealwaysontop, {0} },
    /* Toggl full screen */
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
    /* Show all windows */
    /* { MODKEY,                       XK_0,      view,           {.ui = ~0 } }, */
    /* Move a window to all tags    */
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    /* Move focus to the other monitor */
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    /* Move focus to the other monitor */
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    /* Move the active window to the other monitor */
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    /* Move the active window to the other monitor */
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    /* Move to the next tag */
    { MODKEY|ShiftMask,             XK_k,      shiftview,      { .i = +1 } },
    /* Move to the previous tag */
    { MODKEY|ShiftMask,             XK_j,      shiftview,      { .i = -1 } },
    /* Move floating windows */
    { MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
    { MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
    { MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
    { MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
    /* Resize floating windows */
    { MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
    { MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
    { MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
    { MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
    /* Move floating windows to edge of screen */
    { MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
    { MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
    { MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
    { MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
    /* Resize floating windows to edge of screen */
    { MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
    { MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
    { MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
    { MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
    /* Navigate tags */
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    /* Quit DWM */
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    /* [left mouse button on layout tag] - cycle through the two last layouts */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    /* [middle mouse button on status text] - open the terminal */
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    /* [MODKEY] + [left mouse button on window] - move window */
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    /* [MODKEY] + [middle mouse button on window] - toogle window in being floating */
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    /* [MODKEY] + [right mouse button on window] - resize window */
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    /* Shift view */
    { ClkTagBar,            0,              Button4,        shiftview,     { .i = -1 } },
    { ClkTagBar,            0,              Button5,        shiftview,     { .i = +1 } },
};
