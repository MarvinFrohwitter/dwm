/* See LICENSE file for copyright and license details.
 *
 * dynamic window manager is designed like any other X client as well. It is
 * driven through handling X events. In contrast to other X clients, a window
 * manager selects for SubstructureRedirectMask on the root window, to receive
 * events about window (dis-)appearance. Only one X connection at a time is
 * allowed to select for this event mask.
 *
 * The event handlers of dwm are organized in an array which is accessed
 * whenever a new event has been fetched. This allows event dispatching
 * in O(1) time.
 *
 * Each child of the root window is called a client, except windows which have
 * set the override_redirect flag. Clients are organized in a linked client
 * list on each monitor, the focus history is remembered through a stack list
 * on each monitor. Each client contains a bit array to indicate the tags of a
 * client.
 *
 * Keys and tagging rules are organized as arrays and defined in config.h.
 *
 * To understand everything else, start reading main().
 */
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xresource.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/keysym.h>
#include <errno.h>
#include <locale.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#ifdef XINERAMA
#include <X11/extensions/Xinerama.h>
#endif /* XINERAMA */
#include <X11/Xft/Xft.h>
#include <X11/Xlib-xcb.h>
#include <xcb/res.h>
#ifdef __OpenBSD__
#include <kvm.h>
#include <sys/sysctl.h>
#endif /* __OpenBSD */

#include "drw.h"
#include "util.h"

/* macros */
#define BUTTONMASK (ButtonPressMask | ButtonReleaseMask)
#define CLEANMASK(mask)                                                        \
  (mask & ~(numlockmask | LockMask) &                                          \
   (ShiftMask | ControlMask | Mod1Mask | Mod2Mask | Mod3Mask | Mod4Mask |      \
    Mod5Mask))
#define INTERSECT(x, y, w, h, m)                                               \
  (MAX(0, MIN((x) + (w), (m)->wx + (m)->ww) - MAX((x), (m)->wx)) *             \
   MAX(0, MIN((y) + (h), (m)->wy + (m)->wh) - MAX((y), (m)->wy)))
#define INTERSECTC(x, y, w, h, z)                                              \
  (MAX(0, MIN((x) + (w), (z)->x + (z)->w) - MAX((x), (z)->x)) *                \
   MAX(0, MIN((y) + (h), (z)->y + (z)->h) - MAX((y), (z)->y)))
#define ISVISIBLE(C)                                                           \
  ((C->tags & C->mon->tagset[C->mon->seltags]) || C->issticky)
#define LENGTH(X) (sizeof X / sizeof X[0])
#define MOUSEMASK (BUTTONMASK | PointerMotionMask)
#define WIDTH(X) ((X)->w + 2 * (X)->bw)
#define HEIGHT(X) ((X)->h + 2 * (X)->bw)
#define TAGMASK ((1 << LENGTH(tags)) - 1)
#define TEXTW(X) (drw_fontset_getwidth(drw, (X)) + lrpad)
#define TEXTWITH(X) (drw_fontset_getwidth(drw, (X)) + lrpad + 7)

#define SYSTEM_TRAY_REQUEST_DOCK 0
#define _NET_SYSTEM_TRAY_ORIENTATION_HORZ 0
/* XEMBED messages */
#define XEMBED_EMBEDDED_NOTIFY 0
#define XEMBED_WINDOW_ACTIVATE 1
#define XEMBED_FOCUS_IN 4
#define XEMBED_MODALITY_ON 10
#define XEMBED_MAPPED (1 << 0)
#define XEMBED_WINDOW_ACTIVATE 1
#define XEMBED_WINDOW_DEACTIVATE 2
#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define XEMBED_EMBEDDED_VERSION (VERSION_MAJOR << 16) | VERSION_MINOR

#define OPAQUE 0xffU

/* enums */
enum { Manager, Xembed, XembedInfo, XLast };     /* Xembed atoms */
enum { CurNormal, CurResize, CurMove, CurLast }; /* cursor */
enum {
  SchemeNorm,
  SchemeTitle,
  SchemeTray,
  SchemeSel,
  SchemeN /* keeplast */
}; /* color schemes */
enum {
  NetSupported,
  NetSystemTray,
  NetSystemTrayOP,
  NetSystemTrayOrientation,
  NetSystemTrayVisual,
  NetWMName,
  NetWMState,
  NetWMFullscreen,
  NetActiveWindow,
  NetWMWindowType,
  NetWMWindowTypeDock,
  NetSystemTrayOrientationHorz,
  NetWMWindowTypeDialog,
  NetClientList,
  NetClientInfo,
  NetWMCheck,
  NetWMWindowsOpacity,
  NetLast
}; /* EWMH atoms */
enum {
  WMProtocols,
  WMDelete,
  WMState,
  WMTakeFocus,
  WMLast
}; /* default atoms */
enum {
  ClkTagBar,
  ClkLtSymbol,
  ClkStatusText,
  ClkWinTitle,
  ClkClientWin,
  ClkRootWin,
  ClkLast
}; /* clicks */

typedef union {
  int i;
  unsigned int ui;
  float f;
  const void *v;
} Arg;

typedef struct {
  char *gname;
  void (*func)(const Arg *arg);
  const Arg arg;
} Gesture;

typedef struct {
  unsigned int click;
  unsigned int mask;
  unsigned int button;
  void (*func)(const Arg *arg);
  const Arg arg;
} Button;

typedef struct Monitor Monitor;
typedef struct Client Client;
struct Client {
  char name[256];
  float mina, maxa;
  float cfact;
  int x, y, w, h;
  int oldx, oldy, oldw, oldh;
  int basew, baseh, incw, inch, maxw, maxh, minw, minh, hintsvalid;
  int bw, oldbw;
  unsigned int tags;
  unsigned int switchtotag;
  int isfixed, isfloating, iscentered, canfocus, isurgent, isalwaysontop,
      neverfocus, oldstate, isfullscreen, resizehints, isterminal, noswallow,
      issticky, isforegrounded;
  int beingmoved;
  int floatborderpx;
  int hasfloatbw;
  pid_t pid;
  char scratchkey;
  int allowkill;
  Client *next;
  Client *snext;
  Client *tnext;
  Client *swallowing;
  double opacity;
  int wasruleopacity;
  Monitor *mon;
  Window win;
  Client *crop;
};

typedef struct {
  unsigned int mod;
  KeySym keysym;
  void (*func)(const Arg *);
  const Arg arg;
} Key;

typedef struct {
  const char *symbol;
  void (*arrange)(Monitor *);
} Layout;

typedef struct Pertag Pertag;
struct Monitor {
  char ltsymbol[16];
  float mfact;
  int nmaster;
  int num;
  int by;             /* bar geometry */
  int mx, my, mw, mh; /* screen size */
  int wx, wy, ww, wh; /* window area  */
  int gappih;         /* horizontal gap between windows */
  int gappiv;         /* vertical gap between windows */
  int gappoh;         /* horizontal outer gaps */
  int gappov;         /* vertical outer gaps */
  unsigned int seltags;
  unsigned int sellt;
  unsigned int tagset[2];
  int rmaster;
  int showbar;
  int topbar;
  Client *clients;
  Client *sel;
  Client *stack;
  Client *foregrounded;
  Client *tagmarked[32];
  Monitor *next;
  Window barwin;
  const Layout *lt[2];
  unsigned int alttag;
  Pertag *pertag;
};

typedef struct {
  const char *class;
  const char *instance;
  const char *title;
  unsigned int tags;
  unsigned int switchtotag;
  int allowkill;
  int isfloating;
  int canfocus;
  int isterminal;
  int noswallow;
  double opacity;
  int monitor;
  int resizehints;
  int floatx, floaty, floatw, floath;
  int floatborderpx;
  int bw;
  const char scratchkey;
} Rule;

typedef struct {
  const char **cmd;
  unsigned int tags;
} Autostarttag;

typedef struct Systray Systray;
struct Systray {
  Window win;
  Client *icons;
};

/* Xresources preferences */
enum resource_type { STRING = 0, INTEGER = 1, FLOAT = 2 };

typedef struct {
  char *name;
  enum resource_type type;
  void *dst;
} ResourcePref;

typedef struct {
  const char **command;
  const char *name;
} Launcher;

/* function declarations */
static void alttab(const Arg *arg);
static void applyrules(Client *c);
static int applysizehints(Client *c, int *x, int *y, int *w, int *h,
                          int interact);
static void arrange(Monitor *m);
static void arrangemon(Monitor *m);
static void attach(Client *c);
static void attachbottom(Client *c);
static void attachstack(Client *c);
static void buttonpress(XEvent *e);
static void changeopacity(const Arg *arg);
static void checkotherwm(void);
static void cleanup(void);
static void cleanupmon(Monitor *mon);
static void clientmessage(XEvent *e);
static void col(Monitor *);
static void configure(Client *c);
static void configurenotify(XEvent *e);
static void configurerequest(XEvent *e);
static Monitor *createmon(void);
static void cyclelayout(const Arg *arg);
static void destroynotify(XEvent *e);
static void detach(Client *c);
static void detachstack(Client *c);
static Monitor *dirtomon(int dir);
static Monitor *numtomon(int num);
static void drawbar(Monitor *m);
static void drawbars(void);
static void enternotify(XEvent *e);
static void expose(XEvent *e);
static Client *findbefore(Client *c);
static void focus(Client *c);
static void focusin(XEvent *e);
static void focusmaster(const Arg *arg);
static void focusmon(const Arg *arg);
static void focusnext(const Arg *arg);
static void focusnthmon(const Arg *arg);
static void focusvisibletagstacks(const Arg *arg);
static void focusstack(const Arg *arg);
static Atom getatomprop(Client *c, Atom prop);
static int getrootptr(int *x, int *y);
static long getstate(Window w);
static unsigned int getsystraywidth();
static pid_t getstatusbarpid();
static int gettextprop(Window w, Atom atom, char *text, unsigned int size);
static void grabbuttons(Client *c, int focused);
static void grabkeys(void);
static void horizontal(Monitor *m);
static void incnmaster(const Arg *arg);
static void keypress(XEvent *e);
static void keyrelease(XEvent *e);
static void killthis(Window w);
static void killclient(const Arg *arg);
static void layoutmenu(const Arg *arg);
static void manage(Window w, XWindowAttributes *wa);
static void mappingnotify(XEvent *e);
static void maprequest(XEvent *e);
static void monocle(Monitor *m);
static void motionnotify(XEvent *e);
static void gesture(const Arg *arg);
static void moveresize(const Arg *arg);
static void moveresizeedge(const Arg *arg);
static void movemouse(const Arg *arg);
static void moveorplace(const Arg *arg);
static Client *nexttiled(Client *c);
static void opacity(Client *c, double opacity);
static void placemouse(const Arg *arg);
// static void pop(Client *c);
static void propertynotify(XEvent *e);
static void quit(const Arg *arg);
static Client *recttoclient(int x, int y, int w, int h);
static Monitor *recttomon(int x, int y, int w, int h);
static void removesystrayicon(Client *i);
static void resize(Client *c, int x, int y, int w, int h, int interact);
static void resizeclient(Client *c, int x, int y, int w, int h);
static void resizemouse(const Arg *arg);
static void resizerequest(XEvent *e);
static void restack(Monitor *m);
static void run(void);
static void runautostart(void);
static void scan(void);
static void scratchpad_hide();
static _Bool scratchpad_last_showed_is_killed(void);
static void scratchpad_remove();
static void scratchpad_show();
static _Bool scratchpad_show_client_by_pid(pid_t pid);
static void scratchpad_show_client(Client *c);
static void scratchpad_show_first(void);
static int sendevent(Window w, Atom proto, int m, long d0, long d1, long d2,
                     long d3, long d4);
static void sendmon(Client *c, Monitor *m);
static void setclientstate(Client *c, long state);
static void setclienttagprop(Client *c);
static void setfocus(Client *c);
static void setfullscreen(Client *c, int fullscreen);
static void fullscreen(const Arg *arg);
static void setlayout(const Arg *arg);
static void setcfact(const Arg *arg);
static void setmfact(const Arg *arg);
static void setscheme(const Arg *arg);
static void setup(void);
static void seturgent(Client *c, int urg);
static void showhide(Client *c);
static void sighup(int unused);
static void sigterm(int unused);
static void sigstatusbar(const Arg *arg);
static void spawn(const Arg *arg);
static void autostarttagsspawner(void);
static void applyautostarttags(Client *c);
static void spawnscratch(const Arg *arg);
static Monitor *systraytomon(Monitor *m);
static void stairs(Monitor *m);
static void tag(const Arg *arg);
static void tagmon(const Arg *arg);
static void tagnthmon(const Arg *arg);
/* static void tile(Monitor *m); */
static void toggleall(const Arg *arg);
static void togglealttag(const Arg *arg);
static void togglebar(const Arg *arg);
static void toggleforegrounded(const Arg *arg);
static void togglefloating(const Arg *arg);
static void toggleallowkill(const Arg *arg);
static void togglealwaysontop(const Arg *arg);
static void togglermaster(const Arg *arg);
static void togglescratch(const Arg *arg);
static void togglefullscr(const Arg *arg);
static void toggleopacity(const Arg *arg);
static void togglesticky(const Arg *arg);
static void toggletag(const Arg *arg);
static void toggleview(const Arg *arg);
static void unfocus(Client *c, int setfocus);
static void unmanage(Client *c, int destroyed);
static void unmapnotify(XEvent *e);
static void updatebarpos(Monitor *m);
static void updatebars(void);
static void updateclientlist(void);
static int updategeom(void);
static void updatenumlockmask(void);
static void updatesizehints(Client *c);
static void updatestatus(void);
// static void updatesystray(void);
static void updatesystray(int updatebar);
static void updatesystrayicongeom(Client *i, int w, int h);
static void updatesystrayiconstate(Client *i, XPropertyEvent *ev);
static void updatetitle(Client *c);
static void updatewindowtype(Client *c);
static void updatewmhints(Client *c);
static void view(const Arg *arg);
static void cycleview(const Arg *arg);
static Client *wintoclient(Window w);
static Monitor *wintomon(Window w);
static Client *wintosystrayicon(Window w);
static void winview(const Arg *arg);
static int xerror(Display *dpy, XErrorEvent *ee);
static int xerrordummy(Display *dpy, XErrorEvent *ee);
static int xerrorstart(Display *dpy, XErrorEvent *ee);
static void xinitvisual();
static void zoom(const Arg *arg);
static void focussame(const Arg *arg);
static void swaptags(const Arg *arg);
static void load_xresources(void);
static void resource_load(XrmDatabase db, char *name, enum resource_type rtype,
                          void *dst);

static pid_t getparentprocess(pid_t p);
static int isdescprocess(pid_t p, pid_t c);
static Client *swallowingclient(Window w);
static Client *termforwin(const Client *c);
static pid_t winpid(Window w);

/* variables */
static Bool defaultfakefullscreenmode;
static const char autostartblocksh[] = "autostart_blocking.sh";
static const char autostartsh[] = "autostart.sh";
static Client *prevzoom = NULL;
static Client *lastfocused = NULL;
static Window lastfocusedwin = None;
static const char broken[] = "broken";
static const char dwmdir[] = "dwm";
static const char localshare[] = ".local/share";
static char stext[256];
static int statusw;
static int statussig;
static pid_t statuspid = -1;
static int screen;
static int sw, sh; /* X display screen geometry width, height */
static int bh;     /* bar height */
static int lrpad;  /* sum of left and right padding for text */
static int vp;     /* vertical padding for bar */
static int sp;     /* side padding for bar */
static int (*xerrorxlib)(Display *, XErrorEvent *);
static unsigned int numlockmask = 0;
static void (*handler[LASTEvent])(XEvent *) = {
    [ButtonPress] = buttonpress,
    [ClientMessage] = clientmessage,
    [ConfigureRequest] = configurerequest,
    [ConfigureNotify] = configurenotify,
    [DestroyNotify] = destroynotify,
    [EnterNotify] = enternotify,
    [Expose] = expose,
    [FocusIn] = focusin,
    [KeyPress] = keypress,
    [KeyRelease] = keyrelease,
    [MappingNotify] = mappingnotify,
    [MapRequest] = maprequest,
    [MotionNotify] = motionnotify,
    [PropertyNotify] = propertynotify,
    [ResizeRequest] = resizerequest,
    [UnmapNotify] = unmapnotify};
static int restart = 0;
static Atom wmatom[WMLast], netatom[NetLast], xatom[XLast];
static int running = 1;
static Cur *cursor[CurLast];
static Clr **schemes, **scheme;
static Display *dpy;
static Drw *drw;
static Monitor *mons, *selmon;
static Window root, wmcheckwin;
static unsigned int autostarttags = 0;
static int autostartcomplete = 0;
static int autostartcmdscomplete = 0;
static Systray *systray = NULL;
static unsigned long systrayorientation = _NET_SYSTEM_TRAY_ORIENTATION_HORZ;
/* scratchpad */
#define SCRATCHPAD_MASK (1u << sizeof tags / sizeof *tags)
static Client *scratchpad_last_showed = NULL;

static int useargb = 0;
static Visual *visual;
static int depth;
static Colormap cmap;
static xcb_connection_t *xcon;
static int alt_tab_direction = 0;

/*The hard coded 9 was previously LENGTH(tags), but we get and dependency
 * problem*/
struct Pertag {
  unsigned int curtag, prevtag;   /* current and previous tag */
  int nmasters[9 + 1];            /* number of windows in master area */
  float mfacts[9 + 1];            /* mfacts per tag */
  unsigned int sellts[9 + 1];     /* selected layouts */
  const Layout *ltidxs[9 + 1][2]; /* matrix of tags and layouts indexes  */
  int showbars[9 + 1];            /* display bar for the current tag */
  int enablegaps[9 + 1];
  unsigned int gaps[9 + 1];
};

/* configuration, allows nested code to access above variables */
#include "config.h"
/* compile-time check if all tags fit into an unsigned int bit array. */
struct NumTags {
  char limitexceeded[LENGTH(tags) > 30 ? -1 : 1];
};

/* function implementations */

static void alttab(const Arg *arg) {

  view(&(Arg){.ui = ~0});
  focusnext(&(Arg){.i = alt_tab_direction});

  int grabbed = 1;
  int grabbed_keyboard = 1000;
  for (int i = 0; i < 100; i += 1) {
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000;

    if (grabbed_keyboard != GrabSuccess) {
      grabbed_keyboard =
          XGrabKeyboard(dpy, DefaultRootWindow(dpy), True, GrabModeAsync,
                        GrabModeAsync, CurrentTime);
    }
    if (grabbed_keyboard == GrabSuccess) {
      XGrabButton(dpy, AnyButton, AnyModifier, None, False, BUTTONMASK,
                  GrabModeAsync, GrabModeAsync, None, None);
      break;
    }
    nanosleep(&ts, NULL);
    if (i == 100 - 1)
      grabbed = 0;
  }

  XEvent event;
  Client *c;
  Monitor *m;
  XButtonPressedEvent *ev;

  while (grabbed) {
    XNextEvent(dpy, &event);
    switch (event.type) {
    case KeyPress:
      if (event.xkey.keycode == tabCycleKey)
        focusnext(&(Arg){.i = alt_tab_direction});
      break;
    case KeyRelease:
      if (event.xkey.keycode == tabModKey) {
        XUngrabKeyboard(dpy, CurrentTime);
        XUngrabButton(dpy, AnyButton, AnyModifier, None);
        grabbed = 0;
        alt_tab_direction = !alt_tab_direction;
        winview(0);
      }
      break;
    case ButtonPress:
      ev = &(event.xbutton);
      if ((m = wintomon(ev->window)) && m != selmon) {
        unfocus(selmon->sel, 1);
        selmon = m;
        focus(NULL);
      }
      if ((c = wintoclient(ev->window)))
        focus(c);
      XAllowEvents(dpy, AsyncBoth, CurrentTime);
      break;
    case ButtonRelease:
      XUngrabKeyboard(dpy, CurrentTime);
      XUngrabButton(dpy, AnyButton, AnyModifier, None);
      grabbed = 0;
      alt_tab_direction = !alt_tab_direction;
      winview(0);
      break;
    }
  }
  return;
}

Client *cropwintoclient(Window w) {
  Client *c;
  Monitor *m;

  for (m = mons; m; m = m->next)
    for (c = m->clients; c; c = c->next)
      if (c->crop && c->crop->win == w)
        return c;
  return NULL;
}

void cropwindow(Client *c) {
  int x, y;
  XEvent ev;
  XSetWindowAttributes wa = {.event_mask = SubstructureRedirectMask};

  if (!getrootptr(&x, &y))
    return;
  if (!c->crop) {
    c->crop = ecalloc(1, sizeof(Client));
    memcpy(c->crop, c, sizeof(Client));
    c->crop->crop = NULL;
    c->crop->x = c->crop->y = c->crop->bw = 0;
    c->basew = c->baseh = c->mina = c->maxa = 0;
    c->maxw = c->maxh = c->incw = c->inch = 0;
    c->minw = c->minh = 1;
    if (!c->isfloating)
      togglefloating(NULL);
    c->win =
        XCreateWindow(dpy, root, x, y, 1, 1, c->bw, 0, 0, 0, CWEventMask, &wa);
    XReparentWindow(dpy, c->crop->win, c->win, 0, 0);
    XMapWindow(dpy, c->win);
    focus(c);
    XCheckTypedWindowEvent(dpy, c->crop->win, UnmapNotify, &ev);
    if (XCheckTypedWindowEvent(dpy, root, UnmapNotify, &ev) &&
        ev.xunmap.window != c->crop->win)
      XPutBackEvent(dpy, &ev);
  }
  resizeclient(c->crop, c->crop->x + c->x - x, c->crop->y + c->y - y,
               c->crop->w, c->crop->h);
  resizeclient(c, x, y, 1, 1);
}

void cropdelete(Client *c) {
  Client *crop;
  XEvent ev;

  c->crop->x += c->x;
  c->crop->y += c->y;
  c->crop->bw = c->bw;
  c->crop->next = c->next;
  c->crop->snext = c->snext;
  c->crop->tags = c->tags;
  c->crop->mon = c->mon;
  XReparentWindow(dpy, c->crop->win, root, c->crop->x, c->crop->y);
  XDestroyWindow(dpy, c->win);
  crop = c->crop;
  memcpy(c, c->crop, sizeof(Client));
  free(crop);
  resize(c, c->x, c->y, c->w, c->h, 0);
  focus(c);
  XCheckTypedWindowEvent(dpy, c->win, UnmapNotify, &ev);
}

void cropresize(Client *c) {
  resizeclient(c->crop, BETWEEN(c->crop->x, -(c->crop->w), 0) ? c->crop->x : 0,
               BETWEEN(c->crop->y, -(c->crop->h), 0) ? c->crop->y : 0,
               c->crop->w, c->crop->h);
  resize(c, c->x, c->y, MIN(c->w, c->crop->x + c->crop->w),
         MIN(c->h, c->crop->y + c->crop->h), 0);
}

void applyrules(Client *c) {
  const char *class, *instance;
  unsigned int i;
  const Rule *r;
  Monitor *m;
  XClassHint ch = {NULL, NULL};

  /* rule matching */
  c->isfloating = 0;
  c->canfocus = 1;
  c->tags = 0;
  c->allowkill = allowkill;
  c->bw = borderpx;
  c->scratchkey = 0;
  c->opacity = defaultopacity;
  c->wasruleopacity = 0;
  XGetClassHint(dpy, c->win, &ch);
  class = ch.res_class ? ch.res_class : broken;
  instance = ch.res_name ? ch.res_name : broken;

  for (i = 0; i < LENGTH(rules); i++) {
    r = &rules[i];
    if ((!r->title || strstr(c->name, r->title)) &&
        (!r->class || strstr(class, r->class)) &&
        (!r->instance || strstr(instance, r->instance))) {
      c->isterminal = r->isterminal;
      c->noswallow = r->noswallow;
      c->isfloating = r->isfloating;
      c->canfocus = r->canfocus;
      c->tags |= r->tags;
      c->resizehints = r->resizehints;
      c->allowkill = r->allowkill;
      if (r->bw != -1)
        c->bw = r->bw;
      c->scratchkey = r->scratchkey;
      if (r->opacity != c->opacity) {
        c->opacity = r->opacity;
        c->wasruleopacity = 1;
      }
      if (r->floatborderpx >= 0) {
        c->floatborderpx = r->floatborderpx;
        c->hasfloatbw = 1;
      }
      if (r->isfloating) {
        if (r->floatx >= 0)
          c->x = c->mon->mx + r->floatx;
        if (r->floaty >= 0)
          c->y = c->mon->my + r->floaty;
        if (r->floatw >= 0)
          c->w = r->floatw;
        if (r->floath >= 0)
          c->h = r->floath;
      }
      for (m = mons; m && m->num != r->monitor; m = m->next)
        ;
      if (m)
        c->mon = m;
      if (r->switchtotag) {
        Arg a = {.ui = r->tags};
        c->switchtotag = selmon->tagset[selmon->seltags];
        view(&a);
      }
    }
  }
  if (ch.res_class)
    XFree(ch.res_class);
  if (ch.res_name)
    XFree(ch.res_name);

  if (c->tags != SCRATCHPAD_MASK) {
    c->tags =
        c->tags & TAGMASK ? c->tags & TAGMASK : c->mon->tagset[c->mon->seltags];
  }
}

static void focusnext(const Arg *arg) {
  Monitor *m;
  Client *c;
  m = selmon;
  c = m->sel;
  if (!c)
    return;

  if (arg->i) {
    if (c->next)
      c = c->next;
    else
      c = m->clients;
  } else {
    Client *last = c;
    if (last == m->clients)
      last = NULL;
    for (c = m->clients; c->next != last; c = c->next)
      ;
  }
  focus(c);
  return;
}

int applysizehints(Client *c, int *x, int *y, int *w, int *h, int interact) {
  int baseismin;
  Monitor *m = c->mon;

  /* set minimum possible */
  *w = MAX(1, *w);
  *h = MAX(1, *h);
  if (interact) {
    if (*x > sw)
      *x = sw - WIDTH(c);
    if (*y > sh)
      *y = sh - HEIGHT(c);
    if (*x + *w + 2 * c->bw < 0)
      *x = 0;
    if (*y + *h + 2 * c->bw < 0)
      *y = 0;
  } else {
    if (*x >= m->wx + m->ww)
      *x = m->wx + m->ww - WIDTH(c);
    if (*y >= m->wy + m->wh)
      *y = m->wy + m->wh - HEIGHT(c);
    if (*x + *w + 2 * c->bw <= m->wx)
      *x = m->wx;
    if (*y + *h + 2 * c->bw <= m->wy)
      *y = m->wy;
  }
  if (*h < bh)
    *h = bh;
  if (*w < bh)
    *w = bh;
  if (c->resizehints || c->isfloating || !c->mon->lt[c->mon->sellt]->arrange) {
    if (!c->hintsvalid)
      updatesizehints(c);
    /* see last two sentences in ICCCM 4.1.2.3 */
    baseismin = c->basew == c->minw && c->baseh == c->minh;
    if (!baseismin) { /* temporarily remove base dimensions */
      *w -= c->basew;
      *h -= c->baseh;
    }
    /* adjust for aspect limits */
    if (c->mina > 0 && c->maxa > 0) {
      if (c->maxa < (float)*w / *h)
        *w = *h * c->maxa + 0.5;
      else if (c->mina < (float)*h / *w)
        *h = *w * c->mina + 0.5;
    }
    if (baseismin) { /* increment calculation requires this */
      *w -= c->basew;
      *h -= c->baseh;
    }
    /* adjust for increment value */
    if (c->incw)
      *w -= *w % c->incw;
    if (c->inch)
      *h -= *h % c->inch;
    /* restore base dimensions */
    *w = MAX(*w + c->basew, c->minw);
    *h = MAX(*h + c->baseh, c->minh);
    if (c->maxw)
      *w = MIN(*w, c->maxw);
    if (c->maxh)
      *h = MIN(*h, c->maxh);
  }
  return *x != c->x || *y != c->y || *w != c->w || *h != c->h;
}

void arrange(Monitor *m) {
  XEvent ev;
  if (m)
    showhide(m->stack);
  else
    for (m = mons; m; m = m->next)
      showhide(m->stack);
  if (m) {
    arrangemon(m);
    restack(m);
  } else {
    for (m = mons; m; m = m->next)
      arrangemon(m);
    XSync(dpy, False);
    while (XCheckMaskEvent(dpy, EnterWindowMask, &ev))
      ;
  }
}

void arrangemon(Monitor *m) {
  strncpy(m->ltsymbol, m->lt[m->sellt]->symbol, sizeof m->ltsymbol);
  if (m->lt[m->sellt]->arrange)
    m->lt[m->sellt]->arrange(m);
}

void attach(Client *c) {
  c->next = c->mon->clients;
  c->mon->clients = c;
}

void attachbottom(Client *c) {
  Client **tc;
  c->next = NULL;
  for (tc = &c->mon->clients; *tc; tc = &(*tc)->next)
    ;
  *tc = c;
}

void attachstack(Client *c) {
  c->snext = c->mon->stack;
  c->mon->stack = c;
}

void swallow(Client *p, Client *c) {

  if (c->noswallow || c->isterminal)
    return;
  if (c->noswallow && !swallowfloating && c->isfloating)
    return;

  detach(c);
  detachstack(c);

  setclientstate(c, WithdrawnState);
  XUnmapWindow(dpy, p->win);

  p->swallowing = c;
  c->mon = p->mon;

  Window w = p->win;
  p->win = c->win;
  c->win = w;
  updatetitle(p);
  XMoveResizeWindow(dpy, p->win, p->x, p->y, p->w, p->h);
  arrange(p->mon);
  configure(p);
  updateclientlist();
}

void unswallow(Client *c) {
  c->win = c->swallowing->win;

  free(c->swallowing);
  c->swallowing = NULL;

  /* unfullscreen the client */
  setfullscreen(c, 0);
  updatetitle(c);
  arrange(c->mon);
  XMapWindow(dpy, c->win);
  XMoveResizeWindow(dpy, c->win, c->x, c->y, c->w, c->h);
  setclientstate(c, NormalState);
  focus(NULL);
  arrange(c->mon);
}

void attachforegrounded(Client *c) {
  c->tnext = c->mon->foregrounded;
  c->mon->foregrounded = c;
}

void detachforegrounded(Client *c) {
  Client **tc;
  for (tc = &c->mon->foregrounded; *tc && *tc != c; tc = &(*tc)->tnext)
    ;
  *tc = c->tnext;
}

void buttonpress(XEvent *e) {
  unsigned int i, x, click;
  int stw = getsystraywidth();
  Arg arg = {0};
  Client *c;
  Monitor *m;
  XButtonPressedEvent *ev = &e->xbutton;
  char *text, *s, ch;

  click = ClkRootWin;
  /* focus monitor if necessary */
  if ((m = wintomon(ev->window)) && m != selmon) {
    unfocus(selmon->sel, 1);
    selmon = m;
    focus(NULL);
  }
  if (ev->window == selmon->barwin) {
    i = x = 0;
    unsigned int occ = 0;
    for (c = m->clients; c; c = c->next)
      occ |= c->tags == 255 ? 0 : c->tags;
    do {
      /* Do not reserve space for vacant tags */
      if (!(occ & 1 << i || m->tagset[m->seltags] & 1 << i))
        continue;
      x += TEXTW(tags[i]);
    } while (ev->x >= x && ++i < LENGTH(tags));
    if (i < LENGTH(tags)) {
      click = ClkTagBar;
      arg.ui = 1 << i;
      goto execute_handler;
    } else if (ev->x < x + TEXTW(selmon->ltsymbol)) {
      click = ClkLtSymbol;
      goto execute_handler;
    }

    x += TEXTW(selmon->ltsymbol);
    for (i = 0; i < LENGTH(launchers); i++) {
      x += TEXTW(launchers[i].name);

      if (ev->x < x) {
        Arg a;
        a.v = launchers[i].command;
        spawn(&a);
        return;
      }
    }

    if (ev->x > selmon->ww - statusw - stw - 2 * sp - 7 - 2) {
      x = selmon->ww - statusw - stw - 2 * sp - 7 - 2;
      click = ClkStatusText;
      statussig = 0;
      for (text = s = stext; *s && x <= ev->x; s++) {
        if ((unsigned char)(*s) < ' ') {
          ch = *s;
          *s = '\0';
          x += TEXTW(text) - lrpad;
          *s = ch;
          text = s + 1;
          if (x >= ev->x)
            break;
          statussig = ch;
        }
      }
    } else
      click = ClkWinTitle;
  } else if ((c = wintoclient(ev->window))) {
    focus(c);
    restack(selmon);
    XAllowEvents(dpy, ReplayPointer, CurrentTime);
    click = ClkClientWin;
  }
execute_handler:
  for (i = 0; i < LENGTH(buttons); i++)
    if (click == buttons[i].click && buttons[i].func &&
        buttons[i].button == ev->button &&
        CLEANMASK(buttons[i].mask) == CLEANMASK(ev->state))
      buttons[i].func(
          click == ClkTagBar && buttons[i].arg.i == 0 ? &arg : &buttons[i].arg);
}

Client *nextforegrounded(Client *c) {
  for (; c && (!c->isforegrounded || !ISVISIBLE(c)); c = c->tnext)
    ;
  return c;
}

void arrangeforegrounded(Monitor *m) {
  unsigned int n, i, x, y, w, h;
  Client *c;

  for (n = 0, c = nextforegrounded(m->foregrounded); c;
       c = nextforegrounded(c->tnext), n++)
    ;
  if (n == 0)
    return;

  for (i = 0, c = nextforegrounded(m->foregrounded); c;
       c = nextforegrounded(c->tnext), i++) {
    if (n == 1) {
      x = m->mx + (m->mw - m->mw * fgw) / 2;
      y = m->my + (m->mh - m->mh * fgh) / 2;
      w = (m->mw * fgw) - (2 * (m->foregrounded->bw));
      h = (m->mh * fgh) - (2 * (m->foregrounded->bw));
    } else {
      x = (n - 1 - i) * (m->mw / n);
      y = m->my + (m->mh - m->mh * fgh) / 2;
      w = (m->mw * (1 / (float)n)) - (2 * (m->foregrounded->bw));
      h = (m->mh * fgh) - (2 * (m->foregrounded->bw));
    }
    resize(c, x, y, w, h, 0);
  }
}

void changeopacity(const Arg *arg) {
  if (!selmon->sel)
    return;
  selmon->sel->opacity += arg->f;
  if (selmon->sel->opacity > 1.0)
    selmon->sel->opacity = 1.0;

  if (selmon->sel->opacity < 0)
    selmon->sel->opacity = 0;

  opacity(selmon->sel, selmon->sel->opacity);
}

void checkotherwm(void) {
  xerrorxlib = XSetErrorHandler(xerrorstart);
  /* this causes an error if some other window manager is running */
  XSelectInput(dpy, DefaultRootWindow(dpy), SubstructureRedirectMask);
  XSync(dpy, False);
  XSetErrorHandler(xerror);
  XSync(dpy, False);
}

void cleanup(void) {
  Arg a = {.ui = ~0};
  Layout foo = {"", NULL};
  Monitor *m;
  size_t i;

  view(&a);
  selmon->lt[selmon->sellt] = &foo;
  for (m = mons; m; m = m->next)
    while (m->stack)
      unmanage(m->stack, 0);
  XUngrabKey(dpy, AnyKey, AnyModifier, root);
  while (mons)
    cleanupmon(mons);

  if (showsystray) {
    XUnmapWindow(dpy, systray->win);
    XDestroyWindow(dpy, systray->win);
    free(systray);
  }

  for (i = 0; i < CurLast; i++)
    drw_cur_free(drw, cursor[i]);
  for (i = 0; i < LENGTH(colors) * SchemeN; i++)
    free(schemes[i]);
  free(schemes);
  XDestroyWindow(dpy, wmcheckwin);
  drw_free(drw);
  XSync(dpy, False);
  XSetInputFocus(dpy, PointerRoot, RevertToPointerRoot, CurrentTime);
  XDeleteProperty(dpy, root, netatom[NetActiveWindow]);
}

void cleanupmon(Monitor *mon) {
  Monitor *m;

  if (mon == mons)
    mons = mons->next;
  else {
    for (m = mons; m && m->next != mon; m = m->next)
      ;
    m->next = mon->next;
  }
  XUnmapWindow(dpy, mon->barwin);
  XDestroyWindow(dpy, mon->barwin);
  free(mon);
}

void clientmessage(XEvent *e) {
  XWindowAttributes wa;
  XSetWindowAttributes swa;
  XClientMessageEvent *cme = &e->xclient;
  Client *c = wintoclient(cme->window);

  if (showsystray && cme->window == systray->win &&
      cme->message_type == netatom[NetSystemTrayOP]) {
    /* add systray icons */
    if (cme->data.l[1] == SYSTEM_TRAY_REQUEST_DOCK) {
      if (!(c = (Client *)calloc(1, sizeof(Client))))
        die("fatal: could not malloc() %u bytes\n", sizeof(Client));
      if (!(c->win = cme->data.l[2])) {
        free(c);
        return;
      }

      c->mon = selmon;
      c->next = systray->icons;
      systray->icons = c;
      XGetWindowAttributes(dpy, c->win, &wa);
      c->x = c->oldx = c->y = c->oldy = 0;
      c->w = c->oldw = wa.width;
      c->h = c->oldh = wa.height;
      c->oldbw = wa.border_width;
      c->bw = 0;
      c->isfloating = True;
      /* reuse tags field as mapped status */
      c->tags = 1;
      updatesizehints(c);
      updatesystrayicongeom(c, wa.width, wa.height);
      XAddToSaveSet(dpy, c->win);
      XSelectInput(dpy, c->win,
                   StructureNotifyMask | PropertyChangeMask |
                       ResizeRedirectMask);
      XReparentWindow(dpy, c->win, systray->win, 0, 0);
      /* use parents background color */
      swa.background_pixel = scheme[SchemeNorm][ColBg].pixel;
      XChangeWindowAttributes(dpy, c->win, CWBackPixel, &swa);
      sendevent(c->win, netatom[Xembed], StructureNotifyMask, CurrentTime,
                XEMBED_EMBEDDED_NOTIFY, 0, systray->win,
                XEMBED_EMBEDDED_VERSION);
      XSync(dpy, False);
      setclientstate(c, NormalState);
      updatesystray(1);
    }
    return;
  }

  if (!c && !(c = cropwintoclient(cme->window)))
    return;
  if (cme->message_type == netatom[NetWMState]) {
    if (cme->data.l[1] == netatom[NetWMFullscreen] ||
        cme->data.l[2] == netatom[NetWMFullscreen]) {
      if (isfakefullscreen) {
        setfullscreen(c, (cme->data.l[0] == 1 /* _NET_WM_STATE_ADD    */
                          || cme->data.l[0] == 2 /* _NET_WM_STATE_TOGGLE */));
      } else {
        setfullscreen(c, (cme->data.l[0] == 1 /* _NET_WM_STATE_ADD    */
                          || (cme->data.l[0] == 2 /* _NET_WM_STATE_TOGGLE */ &&
                              !c->isfullscreen)));
      }
    }
  } else if (cme->message_type == netatom[NetActiveWindow]) {
    if (c != selmon->sel && !c->isurgent)
      seturgent(c, 1);
  }
}

void configure(Client *c) {
  XConfigureEvent ce;

  ce.type = ConfigureNotify;
  ce.display = dpy;
  ce.event = c->win;
  ce.window = c->win;
  ce.x = c->x;
  ce.y = c->y;
  ce.width = c->w;
  ce.height = c->h;
  ce.border_width = c->bw;
  ce.above = None;
  ce.override_redirect = False;
  XSendEvent(dpy, c->win, False, StructureNotifyMask, (XEvent *)&ce);
}

void configurenotify(XEvent *e) {
  Monitor *m;
  XConfigureEvent *ev = &e->xconfigure;
  int dirty;

  /* TODO: updategeom handling sucks, needs to be simplified */
  if (ev->window == root) {
    dirty = (sw != ev->width || sh != ev->height);
    sw = ev->width;
    sh = ev->height;
    if (updategeom() || dirty) {
      drw_resize(drw, sw, bh);
      updatebars();
      for (m = mons; m; m = m->next) {
        if (!isfakefullscreen) {
          Client *c;
          for (c = m->clients; c; c = c->next)
            if (c->isfullscreen)
              resizeclient(c, m->mx, m->my, m->mw, m->mh);
        }
        XMoveResizeWindow(dpy, m->barwin, m->wx + sp, m->by + vp,
                          m->ww - 2 * sp, bh);
      }
      focus(NULL);
      arrange(NULL);
    }
  }
}

void configurerequest(XEvent *e) {
  Client *c, *cc = NULL;
  Monitor *m;
  XConfigureRequestEvent *ev = &e->xconfigurerequest;
  XWindowChanges wc;

  if ((c = wintoclient(ev->window)) || (c = cc = cropwintoclient(ev->window))) {
    if (ev->value_mask & CWBorderWidth)
      c->bw = ev->border_width;
    else if (c->isfloating || !selmon->lt[selmon->sellt]->arrange) {
      m = c->mon;
      if (c->crop)
        c = c->crop;
      if (ev->value_mask & CWX) {
        c->oldx = c->x;
        c->x = m->mx + ev->x;
      }
      if (ev->value_mask & CWY) {
        c->oldy = c->y;
        c->y = m->my + ev->y;
      }
      if (ev->value_mask & CWWidth) {
        c->oldw = c->w;
        c->w = ev->width;
      }
      if (ev->value_mask & CWHeight) {
        c->oldh = c->h;
        c->h = ev->height;
      }
      if ((c->x + c->w) > m->mx + m->mw && c->isfloating)
        c->x = m->mx + (m->mw / 2 - WIDTH(c) / 2); /* center in x direction */
      if ((c->y + c->h) > m->my + m->mh && c->isfloating)
        c->y = m->my + (m->mh / 2 - HEIGHT(c) / 2); /* center in y direction */
      if ((ev->value_mask & (CWX | CWY)) &&
          !(ev->value_mask & (CWWidth | CWHeight)))
        configure(c);
      if (ISVISIBLE(c))
        XMoveResizeWindow(dpy, c->win, c->x, c->y, c->w, c->h);
      if (cc)
        cropresize(cc);
    } else
      configure(c);
  } else {
    wc.x = ev->x;
    wc.y = ev->y;
    wc.width = ev->width;
    wc.height = ev->height;
    wc.border_width = ev->border_width;
    wc.sibling = ev->above;
    wc.stack_mode = ev->detail;
    XConfigureWindow(dpy, ev->window, ev->value_mask, &wc);
  }
  XSync(dpy, False);
}

Monitor *createmon(void) {
  Monitor *m;
  unsigned int i;

  m = ecalloc(1, sizeof(Monitor));
  m->tagset[0] = m->tagset[1] = defaulttag;
  m->mfact = mfact;
  m->nmaster = nmaster;
  m->rmaster = rmaster;
  m->showbar = showbar;
  m->topbar = topbar;
  m->gappih = gappih;
  m->gappiv = gappiv;
  m->gappoh = gappoh;
  m->gappov = gappov;
  m->lt[0] = &layouts[0];
  m->lt[1] = &layouts[1 % LENGTH(layouts)];
  strncpy(m->ltsymbol, layouts[0].symbol, sizeof m->ltsymbol);
  m->pertag = ecalloc(1, sizeof(Pertag));
  m->pertag->curtag = m->pertag->prevtag = 1;

  for (i = 0; i <= LENGTH(tags); i++) {
    m->pertag->nmasters[i] = m->nmaster;
    m->pertag->mfacts[i] = m->mfact;

    m->pertag->ltidxs[i][0] = m->lt[0];
    m->pertag->ltidxs[i][1] = m->lt[1];
    m->pertag->sellts[i] = m->sellt;

    m->pertag->enablegaps[i] = 1;
    m->pertag->gaps[i] = ((gappoh & 0xFF) << 0) | ((gappov & 0xFF) << 8) |
                         ((gappih & 0xFF) << 16) | ((gappiv & 0xFF) << 24);
    m->pertag->showbars[i] = m->showbar;
  }

  return m;
}

void cyclelayout(const Arg *arg) {
  Layout *l;
  for (l = (Layout *)layouts; l != selmon->lt[selmon->sellt]; l++)
    ;
  if (arg->i > 0) {
    if (l->symbol && (l + 1)->symbol)
      setlayout(&((Arg){.v = (l + 1)}));
    else
      setlayout(&((Arg){.v = layouts}));
  } else {
    if (l != layouts && (l - 1)->symbol)
      setlayout(&((Arg){.v = (l - 1)}));
    else
      setlayout(&((Arg){.v = &layouts[LENGTH(layouts) - 2]}));
  }
}

void destroynotify(XEvent *e) {
  Client *c;
  XDestroyWindowEvent *ev = &e->xdestroywindow;

  if ((c = wintoclient(ev->window)) || (c = cropwintoclient(ev->window)))
    unmanage(c, 1);
  else if ((c = wintosystrayicon(ev->window))) {
    removesystrayicon(c);
    updatesystray(1);
  } else if ((c = swallowingclient(ev->window)))
    unmanage(c->swallowing, 1);
}

void detach(Client *c) {
  Client **tc;

  for (int i = 1; i < LENGTH(tags); i++)
    if (c == c->mon->tagmarked[i])
      c->mon->tagmarked[i] = NULL;

  for (tc = &c->mon->clients; *tc && *tc != c; tc = &(*tc)->next)
    ;
  *tc = c->next;
}

void detachstack(Client *c) {
  Client **tc, *t;

  for (tc = &c->mon->stack; *tc && *tc != c; tc = &(*tc)->snext)
    ;
  *tc = c->snext;

  if (c == c->mon->sel) {
    for (t = c->mon->stack; t && !ISVISIBLE(t); t = t->snext)
      ;
    c->mon->sel = t;
  }
}

Monitor *dirtomon(int dir) {
  Monitor *m = NULL;

  if (dir > 0) {
    if (!(m = selmon->next))
      m = mons;
  } else if (selmon == mons)
    for (m = mons; m->next; m = m->next)
      ;
  else
    for (m = mons; m->next != selmon; m = m->next)
      ;
  return m;
}

void drawbar(Monitor *m) {
  int indn;
  int x, w, wdelta, tw = 0, stw = 0;
  // int tlpad;
  int boxs = drw->fonts->h / 9;
  int boxw = drw->fonts->h / 6 + 2;
  unsigned int i, occ = 0, urg = 0;
  Client *c;

  if (!m->showbar)
    return;

  if (showsystray && m == systraytomon(m)) {
    stw = getsystraywidth();
    drw_setscheme(drw, scheme[SchemeTray]);
    drw_rect(drw, m->ww - stw, 0, 2 * stw, bh, 1, 1);
  }

  /* draw status first so it can be overdrawn by tags later */
  if (m == selmon || 1) { /* status is only drawn on selected monitor */
    char *text, *s, ch;
    drw_setscheme(drw, scheme[SchemeNorm]);

    x = 0;
    for (text = s = stext; *s; s++) {
      if ((unsigned char)(*s) < ' ') {
        ch = *s;
        *s = '\0';
        tw = TEXTW(text) - lrpad; /* 2px extra right padding */
        drw_text(drw, m->ww - statusw - stw + x - 2 * sp, 0, tw, bh, 0, text,
                 0);
        x += tw;
        *s = ch;
        text = s + 1;
      }
    }
    tw = TEXTWITH(text) - lrpad; /* 2px extra right padding */
    drw_text(drw, m->ww - statusw - stw + x - 2 * sp, 0, tw, bh, 0, text, 0);

    tw = statusw;
  }

  for (c = m->clients; c; c = c->next) {
    occ |= c->tags == 255 ? 0 : c->tags;
    if (c->isurgent)
      urg |= c->tags;
  }
  x = 0;
  for (i = 0; i < LENGTH(tags); i++) {
    /* Do not draw vacant tags */
    if (!(occ & 1 << i || m->tagset[m->seltags] & 1 << i))
      continue;
    indn = 0;
    w = TEXTW(tags[i]);
    wdelta = selmon->alttag ? abs(TEXTW(tags[i]) - TEXTW(tagsalt[i])) / 2 : 0;
    drw_setscheme(
        drw, scheme[m->tagset[m->seltags] & 1 << i ? SchemeSel : SchemeNorm]);
    drw_text(drw, x, 0, w, bh, wdelta + lrpad / 2,
             (selmon->alttag ? tagsalt[i] : tags[i]), urg & 1 << i);
    if (ulineall ||
        m->tagset[m->seltags] &
            1 << i) /* if there are conflicts, just move these lines directly
                       underneath both 'drw_setscheme' and 'drw_text' :) */

      drw_rect(drw, x + ulinepad, bh - ulinestroke - ulinevoffset,
               w - (ulinepad * 2), ulinestroke, 1, 0);
    // if (occ & 1 << i)
    //   drw_rect(drw, x + boxs, boxs, boxw, boxw,
    //            m == selmon && selmon->sel && selmon->sel->tags & 1 << i,
    //            urg & 1 << i);

    for (c = m->clients; c; c = c->next) {
      if (c->tags & (1 << i)) {
        drw_rect(drw, x, 1 + (indn * 2), selmon->sel == c ? 6 : 1, 1, 1,
                 urg & 1 << i);
        indn++;
      }
    }

    x += w;
  }
  w = TEXTW(m->ltsymbol);
  drw_setscheme(drw, scheme[SchemeNorm]);
  x = drw_text(drw, x, 0, w, bh, lrpad / 2, m->ltsymbol, 0);

  for (i = 0; i < LENGTH(launchers); i++) {
    w = TEXTW(launchers[i].name);
    drw_text(drw, x, 0, w, bh, lrpad / 2, launchers[i].name, urg & 1 << i);
    x += w;
  }

  if ((w = m->ww - tw - stw - x) > bh) {
    if (m->sel) {
      drw_setscheme(drw, scheme[m == selmon ? SchemeTitle : SchemeNorm]);

      // tlpad = MAX((m->ww - ((int)TEXTW(m->sel->name) - lrpad)) / 2 - x, lrpad
      // / 2); drw_text(drw, x, 0, w - 2 * sp, bh, tlpad, m->sel->name, 0);
      drw_text(drw, x, text_ypos, w - 2 * sp, bh, lrpad / 2, m->sel->name, 0);

      drw_setscheme(drw, scheme[SchemeNorm]);
      int MAGIC_FOR_BAR = 2 * sidepad;
      drw_rect(drw, x, dashpos_y, w - 2 * sp - MAGIC_FOR_BAR, dash_h, 1, 0);

      if (m->sel->isfloating) {
        drw_rect(drw, x + boxs, boxs, boxw, boxw, m->sel->isfixed, 0);
        // drw_rect(drw, x + boxs + tlpad - lrpad / 2, boxs, boxw, boxw,
        // m->sel->isfixed, 0);

        if (m->sel->isalwaysontop)
          drw_rect(drw, x + boxs, bh - boxw, boxw, boxw, 0, 0);
      }
      if (m->sel->issticky)
        drw_polygon(drw, x + boxs, m->sel->isfloating ? boxs * 2 + boxw : boxs,
                    stickyiconbb.x, stickyiconbb.y, boxw,
                    boxw * stickyiconbb.y / stickyiconbb.x, stickyicon,
                    LENGTH(stickyicon), Nonconvex,
                    m->sel->tags & m->tagset[m->seltags]);
    } else {
      drw_setscheme(drw, scheme[SchemeNorm]);
      drw_rect(drw, x, 0, w - 2 * sp, bh, 1, 1);
    }
  }
  // drw_map(drw, m->barwin, 0, 0, m->ww - stw, bh);
  drw_map(drw, m->barwin, 0, 0, m->ww, bh);
}

void drawbars(void) {
  Monitor *m;

  for (m = mons; m; m = m->next)
    drawbar(m);

  if (showsystray && !systraypinning)
    updatesystray(0);
}

void enternotify(XEvent *e) {
  Client *c;
  Monitor *m;
  XCrossingEvent *ev = &e->xcrossing;

  if ((ev->mode != NotifyNormal || ev->detail == NotifyInferior) &&
      ev->window != root)
    return;
  c = wintoclient(ev->window);
  if (!c)
    c = cropwintoclient(ev->window);
  m = c ? c->mon : wintomon(ev->window);
  if (m != selmon) {
    unfocus(selmon->sel, 1);
    selmon = m;
  } else if (!c || c == selmon->sel)
    return;
  focus(c);
}

void expose(XEvent *e) {
  Monitor *m;
  XExposeEvent *ev = &e->xexpose;

  if (ev->count == 0 && (m = wintomon(ev->window))) {
    drawbar(m);

    if (showsystray && m == systraytomon(m))
      updatesystray(0);
  }
}

void focussame(const Arg *arg) {
  Client *c;
  XClassHint ch = {NULL, NULL};
  char *class_name = NULL;
  int direction = arg->i;

  if (!selmon->sel)
    return;

  if (!XGetClassHint(dpy, selmon->sel->win, &ch))
    return;
  class_name = ch.res_class;

  Client *clients[32];
  int num_clients = 0;
  for (c = selmon->clients; c && num_clients < 32; c = c->next) {
    if (c->tags & selmon->tagset[selmon->seltags] &&
        XGetClassHint(dpy, c->win, &ch)) {
      if (strcmp(class_name, ch.res_class) == 0)
        clients[num_clients++] = c;
      XFree(ch.res_class);
      XFree(ch.res_name);
    }
  }

  Client *target_client = NULL;
  if (direction == +1) {
    for (int i = 0; i < num_clients; ++i) {
      if (clients[i]->win == lastfocusedwin) {
        target_client = clients[(i + 1) % num_clients];
        break;
      }
    }
    if (!target_client)
      target_client = clients[0];
  } else if (direction == -1) {
    for (int i = 0; i < num_clients; ++i) {
      if (clients[i]->win == lastfocusedwin) {
        target_client = clients[(i - 1 + num_clients) % num_clients];
        break;
      }
    }
    if (!target_client)
      target_client = clients[num_clients - 1];
  }

  if (target_client) {
    focus(target_client);
    restack(selmon);
    lastfocusedwin = target_client->win;
  }
}

void focus(Client *c) {
  if (!c || !ISVISIBLE(c))
    for (c = selmon->stack; c && !ISVISIBLE(c); c = c->snext)
      ;
  if (selmon->sel && selmon->sel != c)
    unfocus(selmon->sel, 0);
  if (c) {
    if (!c->canfocus)
      return;
    if (c->mon != selmon)
      selmon = c->mon;
    if (c->isurgent)
      seturgent(c, 0);
    detachstack(c);
    attachstack(c);
    grabbuttons(c, 1);
    /* set new focused border first to avoid flickering */
    XSetWindowBorder(dpy, c->win, scheme[SchemeSel][ColBorder].pixel);
    /* lastfocused may be us if another window was unmanaged */
    if (lastfocused && lastfocused != c)
      XSetWindowBorder(dpy, lastfocused->win,
                       scheme[SchemeNorm][ColBorder].pixel);
    setfocus(c);
    if (!c->wasruleopacity) {
      if (c->opacity != defaultopacity) {
        opacity(c, activeopacity);
      }
    }
    // Just raise in floating mode.
    if (selmon->lt[selmon->sellt]->arrange == NULL) {
      XRaiseWindow(dpy, c->win);
    }
  } else {
    XSetInputFocus(dpy, selmon->barwin, RevertToPointerRoot, CurrentTime);
    XDeleteProperty(dpy, root, netatom[NetActiveWindow]);
  }
  selmon->sel = c;
  drawbars();
}

/* there are some broken focus acquiring clients needing extra handling */
void focusin(XEvent *e) {
  XFocusChangeEvent *ev = &e->xfocus;

  if (selmon->sel && ev->window != selmon->sel->win)
    setfocus(selmon->sel);
}

void focusmaster(const Arg *arg) {
  Client *master;

  if (selmon->nmaster > 1)
    return;
  if (!selmon->sel || (selmon->sel->isfullscreen && lockfullscreen))
    return;

  master = nexttiled(selmon->clients);

  if (!master)
    return;

  int i;
  for (i = 0; !(selmon->tagset[selmon->seltags] & 1 << i); i++)
    ;
  i++;

  if (selmon->sel == master) {
    if (selmon->tagmarked[i] && ISVISIBLE(selmon->tagmarked[i]))
      focus(selmon->tagmarked[i]);
  } else {
    selmon->tagmarked[i] = selmon->sel;
    focus(master);
  }
}

void focusmon(const Arg *arg) {
  Monitor *m;

  if (!mons->next)
    return;
  if ((m = dirtomon(arg->i)) == selmon)
    return;
  unfocus(selmon->sel, 0);
  selmon = m;
  focus(NULL);
  if (selmon->sel)
    XWarpPointer(dpy, None, selmon->sel->win, 0, 0, 0, 0, selmon->sel->w / 2,
                 selmon->sel->h / 2);
}

void focusnthmon(const Arg *arg) {
  Monitor *m;

  if (!mons->next)
    return;

  if ((m = numtomon(arg->i)) == selmon)
    return;
  unfocus(selmon->sel, 0);
  selmon = m;
  focus(NULL);
}

/* loops through all the open windows on the visible tags of all the monitors */
/* the Arguments sets the direction for the monitors to loop through */
void focusvisibletagstacks(const Arg *arg) {
  Client *c = NULL;
  Monitor *beginm = selmon;
  if (selmon->sel) {
    if (selmon->sel->isfullscreen && lockfullscreen)
      return;
    for (c = selmon->sel->next; c && !ISVISIBLE(c); c = c->next)
      ;
  }
  if (!c) {
    do {
      focusmon(arg);

    } while (!selmon->clients &&
             selmon != beginm); // focus next monitor with clients
    for (c = selmon->clients; c && !ISVISIBLE(c); c = c->next)
      ;
  }
  focus(c);
}

void focusstack(const Arg *arg) {
  Client *c = NULL, *i;

  if (!selmon->sel || (selmon->sel->isfullscreen && lockfullscreen))
    return;
  if (arg->i > 0) {
    for (c = selmon->sel->next; c && (!ISVISIBLE(c) || !c->canfocus);
         c = c->next)
      ;
    if (!c)
      for (c = selmon->clients; c && (!ISVISIBLE(c) || !c->canfocus);
           c = c->next)
        ;
  } else {
    for (i = selmon->clients; i != selmon->sel; i = i->next)
      if (ISVISIBLE(i) && i->canfocus)
        c = i;
    if (!c)
      for (; i; i = i->next)
        if (ISVISIBLE(i) && i->canfocus)
          c = i;
  }
  if (c) {
    focus(c);
    restack(selmon);
    XWarpPointer(dpy, None, c->win, 0, 0, 0, 0, c->w / 2, c->h / 2);
  }
}

Atom getatomprop(Client *c, Atom prop) {
  int di;
  unsigned long dl;
  unsigned char *p = NULL;
  Atom da, atom = None;

  /* FIXME getatomprop should return the number of items and a pointer to
   * the stored data instead of this workaround */
  Atom req = XA_ATOM;
  if (prop == xatom[XembedInfo])
    req = xatom[XembedInfo];

  if (XGetWindowProperty(dpy, c->win, prop, 0L, sizeof atom, False, req, &da,
                         &di, &dl, &dl, &p) == Success &&
      p) {
    atom = *(Atom *)p;
    if (da == xatom[XembedInfo] && dl == 2)
      atom = ((Atom *)p)[1];
    XFree(p);
  }
  return atom;
}

unsigned int getsystraywidth() {
  unsigned int w = 0;
  Client *i;
  if (showsystray)
    for (i = systray->icons; i; w += i->w + systrayspacing, i = i->next)
      ;
  return w ? w + systrayspacing : 1;
}

pid_t getstatusbarpid() {
  char buf[32], *str = buf, *c;
  FILE *fp;

  if (statuspid > 0) {
    snprintf(buf, sizeof(buf), "/proc/%u/cmdline", statuspid);
    if ((fp = fopen(buf, "r"))) {
      fgets(buf, sizeof(buf), fp);
      while ((c = strchr(str, '/')))
        str = c + 1;
      fclose(fp);
      if (!strcmp(str, STATUSBAR))
        return statuspid;
    }
  }
  if (!(fp = popen("pidof -s " STATUSBAR, "r")))
    return -1;
  fgets(buf, sizeof(buf), fp);
  pclose(fp);
  return strtol(buf, NULL, 10);
}

int getrootptr(int *x, int *y) {
  int di;
  unsigned int dui;
  Window dummy;

  return XQueryPointer(dpy, root, &dummy, &dummy, x, y, &di, &di, &dui);
}

long getstate(Window w) {
  int format;
  long result = -1;
  unsigned char *p = NULL;
  unsigned long n, extra;
  Atom real;

  if (XGetWindowProperty(dpy, w, wmatom[WMState], 0L, 2L, False,
                         wmatom[WMState], &real, &format, &n, &extra,
                         (unsigned char **)&p) != Success)
    return -1;
  if (n != 0)
    result = *p;
  XFree(p);
  return result;
}

int gettextprop(Window w, Atom atom, char *text, unsigned int size) {
  char **list = NULL;
  int n;
  XTextProperty name;

  if (!text || size == 0)
    return 0;
  text[0] = '\0';
  if (!XGetTextProperty(dpy, w, &name, atom) || !name.nitems)
    return 0;
  if (name.encoding == XA_STRING) {
    strncpy(text, (char *)name.value, size - 1);
  } else if (XmbTextPropertyToTextList(dpy, &name, &list, &n) >= Success &&
             n > 0 && *list) {
    strncpy(text, *list, size - 1);
    XFreeStringList(list);
  }
  text[size - 1] = '\0';
  XFree(name.value);
  return 1;
}

void grabbuttons(Client *c, int focused) {
  updatenumlockmask();
  {
    unsigned int i, j;
    unsigned int modifiers[] = {0, LockMask, numlockmask,
                                numlockmask | LockMask};
    XUngrabButton(dpy, AnyButton, AnyModifier, c->win);
    if (!focused)
      XGrabButton(dpy, AnyButton, AnyModifier, c->win, False, BUTTONMASK,
                  GrabModeSync, GrabModeSync, None, None);
    for (i = 0; i < LENGTH(buttons); i++)
      if (buttons[i].click == ClkClientWin)
        for (j = 0; j < LENGTH(modifiers); j++)
          XGrabButton(dpy, buttons[i].button, buttons[i].mask | modifiers[j],
                      c->win, False, BUTTONMASK, GrabModeAsync, GrabModeSync,
                      None, None);
  }
}

void grabkeys(void) {
  updatenumlockmask();
  {
    unsigned int i, j;
    unsigned int modifiers[] = {0, LockMask, numlockmask,
                                numlockmask | LockMask};
    KeyCode code;

    XUngrabKey(dpy, AnyKey, AnyModifier, root);
    for (i = 0; i < LENGTH(keys); i++)
      if ((code = XKeysymToKeycode(dpy, keys[i].keysym)))
        for (j = 0; j < LENGTH(modifiers); j++)
          XGrabKey(dpy, code, keys[i].mod | modifiers[j], root, True,
                   GrabModeAsync, GrabModeAsync);
  }
}

void incnmaster(const Arg *arg) {
  unsigned int i;
  selmon->nmaster = MAX(selmon->nmaster + arg->i, 0);
  for (i = 0; i < LENGTH(tags); ++i)
    if (selmon->tagset[selmon->seltags] & 1 << i)
      selmon->pertag->nmasters[i + 1] = selmon->nmaster;

  if (selmon->pertag->curtag == 0) {
    selmon->pertag->nmasters[0] = selmon->nmaster;
  }
  arrange(selmon);
}

#ifdef XINERAMA
static int isuniquegeom(XineramaScreenInfo *unique, size_t n,
                        XineramaScreenInfo *info) {
  while (n--)
    if (unique[n].x_org == info->x_org && unique[n].y_org == info->y_org &&
        unique[n].width == info->width && unique[n].height == info->height)
      return 0;
  return 1;
}
#endif /* XINERAMA */

void keypress(XEvent *e) {
  unsigned int i;
  KeySym keysym;
  XKeyEvent *ev;

  ev = &e->xkey;
  keysym = XKeycodeToKeysym(dpy, (KeyCode)ev->keycode, 0);
  for (i = 0; i < LENGTH(keys); i++)
    if (keysym == keys[i].keysym &&
        CLEANMASK(keys[i].mod) == CLEANMASK(ev->state) && keys[i].func)
      keys[i].func(&(keys[i].arg));
}

void killthis(Window w) {
  if (!sendevent(w, wmatom[WMDelete], NoEventMask, wmatom[WMDelete],
                 CurrentTime, 0, 0, 0)) {
    XGrabServer(dpy);
    XSetErrorHandler(xerrordummy);
    XSetCloseDownMode(dpy, DestroyAll);
    XKillClient(dpy, w);
    XSync(dpy, False);
    XSetErrorHandler(xerror);
    XUngrabServer(dpy);
  }
}

void killclient(const Arg *arg) {
  Client *c;

  if (!selmon->sel || !selmon->sel->allowkill)
    return;

  if (!arg->ui || arg->ui == 0) {

    if (selmon->sel->crop)
      cropdelete(selmon->sel);

    // if (selmon->sel->scratchkey == 'l') {
    //   pskiller(selmon->sel->pid);
    // }

    killthis(selmon->sel->win);
    return;
  }

  for (c = selmon->clients; c; c = c->next) {
    if (!ISVISIBLE(c) || (arg->ui == 1 && c == selmon->sel))
      continue;

    if (arg->ui != 3)
      if (!c->allowkill)
        continue;

    if (c->crop)
      cropdelete(c);

    // if (c->scratchkey == 'l') {
    //   pskiller(c->pid);
    // }

    killthis(c->win);
  }
}

void keyrelease(XEvent *e) {
  unsigned int i;
  KeySym keysym;
  XKeyEvent *ev;

  ev = &e->xkey;
  keysym = XKeycodeToKeysym(dpy, (KeyCode)ev->keycode, 0);

  for (i = 0; i < LENGTH(keys); i++)
    if (momentaryalttags && keys[i].func && keys[i].func == togglealttag &&
        selmon->alttag &&
        (keysym == keys[i].keysym ||
         CLEANMASK(keys[i].mod) == CLEANMASK(ev->state)))
      keys[i].func(&(keys[i].arg));
}

void layoutmenu(const Arg *arg) {
  FILE *p;
  char c[3], *s;
  int i;

  if (!(p = popen(layoutmenu_cmd, "r")))
    return;
  s = fgets(c, sizeof(c), p);
  pclose(p);

  if (!s || *s == '\0' || c[0] == '\0')
    return;

  i = atoi(c);
  setlayout(&((Arg){.v = &layouts[i]}));
}

void manage(Window w, XWindowAttributes *wa) {
  Client *c, *t = NULL, *term = NULL;
  Window trans = None;
  XWindowChanges wc;

  c = ecalloc(1, sizeof(Client));
  c->win = w;
  c->pid = winpid(w);
  /* geometry */
  c->x = c->oldx = wa->x;
  c->y = c->oldy = wa->y;
  c->w = c->oldw = wa->width;
  c->h = c->oldh = wa->height;
  c->oldbw = wa->border_width;
  c->resizehints = resizehints;
  c->cfact = 1.0;

  updatetitle(c);
  if (XGetTransientForHint(dpy, w, &trans) && (t = wintoclient(trans))) {
    c->mon = t->mon;
    c->tags = t->tags;
  } else {
    c->mon = selmon;
    if (autostarttags) {
      applyautostarttags(c);
    } else {
      applyrules(c);
    }
    term = termforwin(c);
  }
  opacity(c, c->opacity);

  if (c->x + WIDTH(c) > c->mon->wx + c->mon->ww)
    c->x = c->mon->wx + c->mon->ww - WIDTH(c);
  if (c->y + HEIGHT(c) > c->mon->wy + c->mon->wh)
    c->y = c->mon->wy + c->mon->wh - HEIGHT(c);
  c->x = MAX(c->x, c->mon->wx);
  c->y = MAX(c->y, c->mon->wy);
  if (c->hasfloatbw && c->isfloating) {
    c->bw = c->floatborderpx;
  }
  // Removed for the border rule
  //   else {
  //   c->bw = borderpx;
  // }

  wc.border_width = c->bw;
  XConfigureWindow(dpy, w, CWBorderWidth, &wc);
  XSetWindowBorder(dpy, w, scheme[SchemeNorm][ColBorder].pixel);
  configure(c); /* propagates border_width, if size doesn't change */
  updatewindowtype(c);
  updatesizehints(c);
  updatewmhints(c);
  {
    int format;
    unsigned long *data, n, extra;
    Monitor *m;
    Atom atom;
    if (XGetWindowProperty(dpy, c->win, netatom[NetClientInfo], 0L, 2L, False,
                           XA_CARDINAL, &atom, &format, &n, &extra,
                           (unsigned char **)&data) == Success &&
        n == 2) {
      c->tags = *data;
      for (m = mons; m; m = m->next) {
        if (m->num == *(data + 1)) {
          c->mon = m;
          break;
        }
      }
    }
    if (n > 0)
      XFree(data);
  }
  setclienttagprop(c);

  c->x = c->mon->mx + (c->mon->mw - WIDTH(c)) / 2;
  c->y = c->mon->my + (c->mon->mh - HEIGHT(c)) / 2;
  XSelectInput(dpy, w,
               EnterWindowMask | FocusChangeMask | PropertyChangeMask |
                   StructureNotifyMask);
  grabbuttons(c, 0);
  if (!c->isfloating)
    c->isfloating = c->oldstate = trans != None || c->isfixed;
  if (c->isfloating)
    XRaiseWindow(dpy, c->win);
  attachbottom(c);
  attachstack(c);
  XChangeProperty(dpy, root, netatom[NetClientList], XA_WINDOW, 32,
                  PropModeAppend, (unsigned char *)&(c->win), 1);
  XMoveResizeWindow(dpy, c->win, c->x + 2 * sw, c->y, c->w,
                    c->h); /* some windows require this */
  setclientstate(c, NormalState);
  if (selmon->sel && selmon->sel->isfullscreen && !c->isfloating)
    setfullscreen(selmon->sel, 0);
  if (c->mon == selmon)
    unfocus(selmon->sel, 0);
  c->mon->sel = c;
  arrange(c->mon);
  XMapWindow(dpy, c->win);
  if (c && c->mon == selmon)
    XWarpPointer(dpy, None, c->win, 0, 0, 0, 0, c->w / 2, c->h / 2);
  if (term)
    swallow(term, c);
  focus(NULL);
}

void mappingnotify(XEvent *e) {
  XMappingEvent *ev = &e->xmapping;

  XRefreshKeyboardMapping(ev);
  if (ev->request == MappingKeyboard)
    grabkeys();
}

void maprequest(XEvent *e) {
  static XWindowAttributes wa;
  XMapRequestEvent *ev = &e->xmaprequest;

  Client *i;
  if (showsystray && (i = wintosystrayicon(ev->window))) {
    sendevent(i->win, netatom[Xembed], StructureNotifyMask, CurrentTime,
              XEMBED_WINDOW_ACTIVATE, 0, systray->win, XEMBED_EMBEDDED_VERSION);
    updatesystray(1);
  }

  if (!XGetWindowAttributes(dpy, ev->window, &wa) || wa.override_redirect)
    return;
  if (!wintoclient(ev->window))
    manage(ev->window, &wa);
}

void monocle(Monitor *m) {
  unsigned int n = 0;
  Client *c;

  for (c = m->clients; c; c = c->next)
    if (ISVISIBLE(c))
      n++;
  if (n > 0) /* override layout symbol */
    snprintf(m->ltsymbol, sizeof m->ltsymbol, "%s",
             monocles[MIN(n, LENGTH(monocles)) - 1]);
  for (c = nexttiled(m->clients); c; c = nexttiled(c->next))
    resize(c, m->wx, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, 0);
}

void motionnotify(XEvent *e) {
  static Monitor *mon = NULL;
  Monitor *m;
  XMotionEvent *ev = &e->xmotion;

  if (ev->window != root)
    return;
  if ((m = recttomon(ev->x_root, ev->y_root, 1, 1)) != mon && mon) {
    unfocus(selmon->sel, 1);
    selmon = m;
    focus(NULL);
  }
  mon = m;
}

void gesture(const Arg *arg) {
  int x, y, dx, dy, q;
  int valid = 0, listpos = 0, gestpos = 0, count = 0;
  char move, currGest[10];
  XEvent ev;

  if (XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                   None, cursor[CurMove]->cursor, CurrentTime) != GrabSuccess)
    return;
  if (!getrootptr(&x, &y))
    return;
  do {
    XMaskEvent(dpy, MOUSEMASK | ExposureMask | SubstructureRedirectMask, &ev);
    switch (ev.type) {
    case ConfigureRequest:
    case Expose:
    case MapRequest:
      handler[ev.type](&ev);
      break;
    case MotionNotify:
      if (count++ < 10)
        break;
      count = 0;
      dx = ev.xmotion.x - x;
      dy = ev.xmotion.y - y;
      x = ev.xmotion.x;
      y = ev.xmotion.y;

      if (abs(dx) / (abs(dy) + 1) == 0)
        move = dy < 0 ? 'u' : 'd';
      else
        move = dx < 0 ? 'l' : 'r';

      if (move != currGest[gestpos - 1]) {
        if (gestpos > 9) {
          ev.type++;
          break;
        }

        currGest[gestpos] = move;
        currGest[++gestpos] = '\0';

        valid = 0;
        for (q = 0; q < LENGTH(gestures); q++) {
          if (!strcmp(currGest, gestures[q].gname)) {
            valid++;
            listpos = q;
          }
        }
      }
    }
  } while (ev.type != ButtonRelease);

  if (valid)
    gestures[listpos].func(&(gestures[listpos].arg));

  XUngrabPointer(dpy, CurrentTime);
}

void movemouse(const Arg *arg) {
  int x, y, ocx, ocy, nx, ny;
  Client *c;
  Monitor *m;
  XEvent ev;
  Time lasttime = 0;

  if (!(c = selmon->sel))
    return;
  if (!isfakefullscreen) {
    if (c->isfullscreen) /* no support moving fullscreen windows by mouse */
      return;
  }
  restack(selmon);
  ocx = c->x;
  ocy = c->y;
  if (arg->i == 1 && c->crop) {
    ocx = c->crop->x;
    ocy = c->crop->y;
  }
  if (XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                   None, cursor[CurMove]->cursor, CurrentTime) != GrabSuccess)
    return;
  if (!getrootptr(&x, &y))
    return;
  do {
    XMaskEvent(dpy, MOUSEMASK | ExposureMask | SubstructureRedirectMask, &ev);
    switch (ev.type) {
    case ConfigureRequest:
    case Expose:
    case MapRequest:
      handler[ev.type](&ev);
      break;
    case MotionNotify:
      if ((ev.xmotion.time - lasttime) <= (1000 / 60))
        continue;
      lasttime = ev.xmotion.time;

      nx = ocx + (ev.xmotion.x - x);
      ny = ocy + (ev.xmotion.y - y);
      if (arg->i == 1 && c->crop) {
        c->crop->x = nx;
        c->crop->y = ny;
        cropresize(c);
        continue;
      }
      if (abs(selmon->wx - nx) < snap)
        nx = selmon->wx;
      else if (abs((selmon->wx + selmon->ww) - (nx + WIDTH(c))) < snap)
        nx = selmon->wx + selmon->ww - WIDTH(c);
      if (abs(selmon->wy - ny) < snap)
        ny = selmon->wy;
      else if (abs((selmon->wy + selmon->wh) - (ny + HEIGHT(c))) < snap)
        ny = selmon->wy + selmon->wh - HEIGHT(c);
      if (!c->isfloating && selmon->lt[selmon->sellt]->arrange &&
          (abs(nx - c->x) > snap || abs(ny - c->y) > snap))
        togglefloating(NULL);
      if (!selmon->lt[selmon->sellt]->arrange || c->isfloating)
        resize(c, nx, ny, c->w, c->h, 1);
      break;
    }
  } while (ev.type != ButtonRelease);
  XUngrabPointer(dpy, CurrentTime);
  if ((m = recttomon(c->x, c->y, c->w, c->h)) != selmon) {
    sendmon(c, m);
    selmon = m;
    focus(NULL);
  }
}

void moveorplace(const Arg *arg) {
  if ((!selmon->lt[selmon->sellt]->arrange ||
       (selmon->sel && selmon->sel->isfloating)))
    movemouse(arg);
  else
    placemouse(arg);
}

void placemouse(const Arg *arg) {
  int x, y, px, py, ocx, ocy, nx = -9999, ny = -9999, freemove = 0;
  Client *c, *r = NULL, *at, *prevr;
  Monitor *m;
  XEvent ev;
  XWindowAttributes wa;
  Time lasttime = 0;
  int attachmode, prevattachmode;
  attachmode = prevattachmode = -1;

  if (!(c = selmon->sel) ||
      !c->mon->lt[c->mon->sellt]->arrange) /* no support for placemouse when
                                              floating layout is used */
    return;
  if (c->isfullscreen) /* no support placing fullscreen windows by mouse */
    return;
  restack(selmon);
  prevr = c;
  if (XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                   None, cursor[CurMove]->cursor, CurrentTime) != GrabSuccess)
    return;

  c->isfloating = 0;
  c->beingmoved = 1;

  XGetWindowAttributes(dpy, c->win, &wa);
  ocx = wa.x;
  ocy = wa.y;

  if (arg->i == 2) // warp cursor to client center
    XWarpPointer(dpy, None, c->win, 0, 0, 0, 0, WIDTH(c) / 2, HEIGHT(c) / 2);

  if (!getrootptr(&x, &y))
    return;

  do {
    XMaskEvent(dpy, MOUSEMASK | ExposureMask | SubstructureRedirectMask, &ev);
    switch (ev.type) {
    case ConfigureRequest:
    case Expose:
    case MapRequest:
      handler[ev.type](&ev);
      break;
    case MotionNotify:
      if ((ev.xmotion.time - lasttime) <= (1000 / 60))
        continue;
      lasttime = ev.xmotion.time;

      nx = ocx + (ev.xmotion.x - x);
      ny = ocy + (ev.xmotion.y - y);

      if (!freemove && (abs(nx - ocx) > snap || abs(ny - ocy) > snap))
        freemove = 1;

      if (freemove)
        XMoveWindow(dpy, c->win, nx, ny);

      if ((m = recttomon(ev.xmotion.x, ev.xmotion.y, 1, 1)) && m != selmon)
        selmon = m;

      if (arg->i ==
          1) { // tiled position is relative to the client window center point
        px = nx + wa.width / 2;
        py = ny + wa.height / 2;
      } else { // tiled position is relative to the mouse cursor
        px = ev.xmotion.x;
        py = ev.xmotion.y;
      }

      r = recttoclient(px, py, 1, 1);

      if (!r || r == c)
        break;

      attachmode = 0; // below
      if (((float)(r->y + r->h - py) / r->h) >
          ((float)(r->x + r->w - px) / r->w)) {
        if (abs(r->y - py) < r->h / 2)
          attachmode = 1; // above
      } else if (abs(r->x - px) < r->w / 2)
        attachmode = 1; // above

      if ((r && r != prevr) || (attachmode != prevattachmode)) {
        detachstack(c);
        detach(c);
        if (c->mon != r->mon) {
          arrangemon(c->mon);
          c->tags = r->mon->tagset[r->mon->seltags];
        }

        c->mon = r->mon;
        r->mon->sel = r;

        if (attachmode) {
          if (r == r->mon->clients)
            attach(c);
          else {
            for (at = r->mon->clients; at->next != r; at = at->next)
              ;
            c->next = at->next;
            at->next = c;
          }
        } else {
          c->next = r->next;
          r->next = c;
        }

        attachstack(c);
        arrangemon(r->mon);
        prevr = r;
        prevattachmode = attachmode;
      }
      break;
    }
  } while (ev.type != ButtonRelease);
  XUngrabPointer(dpy, CurrentTime);

  if ((m = recttomon(ev.xmotion.x, ev.xmotion.y, 1, 1)) && m != c->mon) {
    detach(c);
    detachstack(c);
    arrangemon(c->mon);
    c->mon = m;
    c->tags = m->tagset[m->seltags];
    attach(c);
    attachstack(c);
    selmon = m;
  }

  focus(c);
  c->beingmoved = 0;

  if (nx != -9999)
    resize(c, nx, ny, c->w, c->h, 0);
  arrangemon(c->mon);
}

void moveresize(const Arg *arg) {
  /* only floating windows can be moved */
  Client *c;
  c = selmon->sel;
  int x, y, w, h, nx, ny, nw, nh, ox, oy, ow, oh;
  char xAbs, yAbs, wAbs, hAbs;
  int msx, msy, dx, dy, nmx, nmy;
  unsigned int dui;
  Window dummy;

  if (!c || !arg)
    return;
  if (selmon->lt[selmon->sellt]->arrange && !c->isfloating)
    return;
  if (sscanf((char *)arg->v, "%d%c %d%c %d%c %d%c", &x, &xAbs, &y, &yAbs, &w,
             &wAbs, &h, &hAbs) != 8)
    return;

  /* compute new window position; prevent window from be positioned outside the
   * current monitor */
  nw = c->w + w;
  if (wAbs == 'W')
    nw = w < selmon->mw - 2 * c->bw ? w : selmon->mw - 2 * c->bw;

  nh = c->h + h;
  if (hAbs == 'H')
    nh = h < selmon->mh - 2 * c->bw ? h : selmon->mh - 2 * c->bw;

  nx = c->x + x;
  if (xAbs == 'X') {
    if (x < selmon->mx)
      nx = selmon->mx;
    else if (x > selmon->mx + selmon->mw)
      nx = selmon->mx + selmon->mw - nw - 2 * c->bw;
    else
      nx = x;
  }

  ny = c->y + y;
  if (yAbs == 'Y') {
    if (y < selmon->my)
      ny = selmon->my;
    else if (y > selmon->my + selmon->mh)
      ny = selmon->my + selmon->mh - nh - 2 * c->bw;
    else
      ny = y;
  }

  ox = c->x;
  oy = c->y;
  ow = c->w;
  oh = c->h;

  XRaiseWindow(dpy, c->win);
  Bool xqp =
      XQueryPointer(dpy, root, &dummy, &dummy, &msx, &msy, &dx, &dy, &dui);
  resize(c, nx, ny, nw, nh, True);

  /* move cursor along with the window to avoid problems caused by the sloppy
   * focus */
  if (xqp && ox <= msx && (ox + ow) >= msx && oy <= msy && (oy + oh) >= msy) {
    nmx = c->x - ox + c->w - ow;
    nmy = c->y - oy + c->h - oh;
    /* make sure the cursor stays inside the window */
    if ((msx + nmx) > c->x && (msy + nmy) > c->y)
      XWarpPointer(dpy, None, None, 0, 0, 0, 0, nmx, nmy);
  }
}

void moveresizeedge(const Arg *arg) {
  /* move or resize floating window to edge of screen */
  Client *c;
  c = selmon->sel;
  char e;
  int nx, ny, nw, nh, ox, oy, ow, oh, bp;
  int msx, msy, dx, dy, nmx, nmy;
  int starty;
  unsigned int dui;
  Window dummy;

  nx = c->x;
  ny = c->y;
  nw = c->w;
  nh = c->h;

  starty = selmon->showbar && topbar ? bh : 0;
  bp = selmon->showbar && !topbar ? bh : 0;

  if (!c || !arg)
    return;
  if (selmon->lt[selmon->sellt]->arrange && !c->isfloating)
    return;
  if (sscanf((char *)arg->v, "%c", &e) != 1)
    return;

  if (e == 't')
    ny = starty;

  if (e == 'b')
    ny = c->h > selmon->mh - 2 * c->bw ? c->h - bp
                                       : selmon->mh - c->h - 2 * c->bw - bp;

  if (e == 'l')
    nx = selmon->mx;

  if (e == 'r')
    nx = c->w > selmon->mw - 2 * c->bw
             ? selmon->mx + c->w
             : selmon->mx + selmon->mw - c->w - 2 * c->bw;

  if (e == 'T') {
    /* if you click to resize again, it will return to old size/position */
    if (c->h + starty == c->oldh + c->oldy) {
      nh = c->oldh;
      ny = c->oldy;
    } else {
      nh = c->h + c->y - starty;
      ny = starty;
    }
  }

  if (e == 'B')
    nh = c->h + c->y + 2 * c->bw + bp == selmon->mh
             ? c->oldh
             : selmon->mh - c->y - 2 * c->bw - bp;

  if (e == 'L') {
    if (selmon->mx + c->w == c->oldw + c->oldx) {
      nw = c->oldw;
      nx = c->oldx;
    } else {
      nw = c->w + c->x - selmon->mx;
      nx = selmon->mx;
    }
  }

  if (e == 'R')
    nw = c->w + c->x + 2 * c->bw == selmon->mx + selmon->mw
             ? c->oldw
             : selmon->mx + selmon->mw - c->x - 2 * c->bw;

  ox = c->x;
  oy = c->y;
  ow = c->w;
  oh = c->h;

  XRaiseWindow(dpy, c->win);
  Bool xqp =
      XQueryPointer(dpy, root, &dummy, &dummy, &msx, &msy, &dx, &dy, &dui);
  resizeclient(c, nx, ny, nw, nh);

  /* move cursor along with the window to avoid problems caused by the sloppy
   * focus */
  if (xqp && ox <= msx && (ox + ow) >= msx && oy <= msy && (oy + oh) >= msy) {
    nmx = c->x - ox + c->w - ow;
    nmy = c->y - oy + c->h - oh;
    /* make sure the cursor stays inside the window */
    if ((msx + nmx) > c->x && (msy + nmy) > c->y)
      XWarpPointer(dpy, None, None, 0, 0, 0, 0, nmx, nmy);
  }
}

Client *nexttiled(Client *c) {
  for (; c && (c->isfloating || !ISVISIBLE(c)); c = c->next)
    ;
  return c;
}

void opacity(Client *c, double opacity) {
  if (bUseOpacity && opacity > 0 && opacity < 1) {
    unsigned long real_opacity[] = {opacity * 0xffffffff};
    XChangeProperty(dpy, c->win, netatom[NetWMWindowsOpacity], XA_CARDINAL, 32,
                    PropModeReplace, (unsigned char *)real_opacity, 1);
  } else
    XDeleteProperty(dpy, c->win, netatom[NetWMWindowsOpacity]);
}

// void pop(Client *c) {
//   int i;
//   for (i = 0; !(selmon->tagset[selmon->seltags] & 1 << i); i++)
//     ;
//   i++;

//   c->mon->tagmarked[i] = nexttiled(c->mon->clients);
//   detach(c);
//   attach(c);
//   focus(c);
//   arrange(c->mon);
// }

void toggleforegrounded(const Arg *arg) {
  if (!selmon->sel)
    return;
  if (selmon->sel->isfullscreen) /* no support for fullscreen windows */
    return;

  selmon->sel->isforegrounded || selmon->sel->isfloating
      ? detachforegrounded(selmon->sel)
      : attachforegrounded(selmon->sel);

  selmon->sel->isforegrounded = selmon->sel->isfloating =
      !selmon->sel->isfloating && !selmon->sel->isforegrounded;

  arrangeforegrounded(selmon);
  arrange(selmon);
}

Client *recttoclient(int x, int y, int w, int h) {
  Client *c, *r = NULL;
  int a, area = 0;

  for (c = nexttiled(selmon->clients); c; c = nexttiled(c->next)) {
    if ((a = INTERSECTC(x, y, w, h, c)) > area) {
      area = a;
      r = c;
    }
  }
  return r;
}

void propertynotify(XEvent *e) {
  Client *c;
  Window trans;
  XPropertyEvent *ev = &e->xproperty;

  if (showsystray && (c = wintosystrayicon(ev->window))) {
    if (ev->atom == XA_WM_NORMAL_HINTS) {
      updatesizehints(c);
      updatesystrayicongeom(c, c->w, c->h);
    } else
      updatesystrayiconstate(c, ev);
    updatesystray(1);
  }

  if ((ev->window == root) && (ev->atom == XA_WM_NAME))
    updatestatus();
  else if (ev->state == PropertyDelete)
    return; /* ignore */
  else if ((c = wintoclient(ev->window)) || (c = cropwintoclient(ev->window))) {
    if (c->crop)
      c = c->crop;
    switch (ev->atom) {
    default:
      break;
    case XA_WM_TRANSIENT_FOR:
      if (!c->isfloating && (XGetTransientForHint(dpy, c->win, &trans)) &&
          (c->isfloating = (wintoclient(trans)) != NULL))
        arrange(c->mon);
      break;
    case XA_WM_NORMAL_HINTS:
      c->hintsvalid = 0;
      break;
    case XA_WM_HINTS:
      updatewmhints(c);
      drawbars();
      break;
    }
    if (ev->atom == XA_WM_NAME || ev->atom == netatom[NetWMName]) {
      updatetitle(c);
      if (c == c->mon->sel)
        drawbar(c->mon);
    }
    if (ev->atom == netatom[NetWMWindowType])
      updatewindowtype(c);
  }
}

void quit(const Arg *arg) {
  if (arg->i)
    restart = 1;
  running = 0;
}

Monitor *recttomon(int x, int y, int w, int h) {
  Monitor *m, *r = selmon;
  int a, area = 0;

  for (m = mons; m; m = m->next)
    if ((a = INTERSECT(x, y, w, h, m)) > area) {
      area = a;
      r = m;
    }
  return r;
}

void removesystrayicon(Client *i) {
  Client **ii;

  if (!showsystray || !i)
    return;
  for (ii = &systray->icons; *ii && *ii != i; ii = &(*ii)->next)
    ;
  if (ii)
    *ii = i->next;
  free(i);
}

void resize(Client *c, int x, int y, int w, int h, int interact) {
  if (applysizehints(c, &x, &y, &w, &h, interact))
    resizeclient(c, x, y, w, h);
}

void resizeclient(Client *c, int x, int y, int w, int h) {
  XWindowChanges wc;

  c->oldx = c->x;
  c->x = wc.x = x;
  c->oldy = c->y;
  c->y = wc.y = y;
  c->oldw = c->w;
  c->w = wc.width = w;
  c->oldh = c->h;
  c->h = wc.height = h;

  if (c->isfloating && c->hasfloatbw && !c->isfullscreen)
    wc.border_width = c->floatborderpx;
  else
    wc.border_width = c->bw;
  if (c->beingmoved)
    return;
  XConfigureWindow(dpy, c->win, CWX | CWY | CWWidth | CWHeight | CWBorderWidth,
                   &wc);
  configure(c);
  XSync(dpy, False);
}

void resizerequest(XEvent *e) {
  XResizeRequestEvent *ev = &e->xresizerequest;
  Client *i;

  if ((i = wintosystrayicon(ev->window))) {
    updatesystrayicongeom(i, ev->width, ev->height);
    updatesystray(1);
  }
}

void resizemouse(const Arg *arg) {
  int ocx, ocy, nw, nh;
  int ocx2, ocy2, nx, ny;
  Client *c;
  Monitor *m;
  XEvent ev;
  int horizcorner, vertcorner;
  int di;
  unsigned int dui;
  Window dummy;
  Time lasttime = 0;

  if (!(c = selmon->sel))
    return;
  if (!isfakefullscreen) {
    if (c->isfullscreen) /* no support resizing fullscreen windows by mouse */
      return;
  }
  restack(selmon);
  if (arg->i == 1)
    cropwindow(c);
  ocx = c->x;
  ocy = c->y;
  ocx2 = c->x + c->w;
  ocy2 = c->y + c->h;
  if (XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                   None, cursor[CurResize]->cursor, CurrentTime) != GrabSuccess)
    return;

  if (!XQueryPointer(dpy, c->win, &dummy, &dummy, &di, &di, &nx, &ny, &dui))
    return;
  horizcorner = nx < c->w / 2;
  vertcorner = ny < c->h / 2;

  if (arg->i != 1) {
    if (c->isfloating || NULL == c->mon->lt[c->mon->sellt]->arrange) {
      XWarpPointer(dpy, None, c->win, 0, 0, 0, 0,
                   horizcorner ? (-c->bw) : (c->w + c->bw - 1),
                   vertcorner ? (-c->bw) : (c->h + c->bw - 1));

    } else {
      XWarpPointer(dpy, None, root, 0, 0, 0, 0,
                   selmon->mx + (selmon->ww * selmon->mfact),
                   selmon->my + (selmon->wh / 2));
    }
  }

  do {
    XMaskEvent(dpy, MOUSEMASK | ExposureMask | SubstructureRedirectMask, &ev);
    switch (ev.type) {
    case ConfigureRequest:
    case Expose:
    case MapRequest:
      handler[ev.type](&ev);
      break;
    case MotionNotify:
      if ((ev.xmotion.time - lasttime) <= (1000 / 60))
        continue;
      lasttime = ev.xmotion.time;

      // nw = MAX(ev.xmotion.x - ocx - 2 * c->bw + 1, 1);
      // nh = MAX(ev.xmotion.y - ocy - 2 * c->bw + 1, 1);

      nx = horizcorner ? ev.xmotion.x : c->x;
      ny = vertcorner ? ev.xmotion.y : c->y;
      nw = MAX(horizcorner ? (ocx2 - nx) : (ev.xmotion.x - ocx - 2 * c->bw + 1),
               1);
      nh = MAX(vertcorner ? (ocy2 - ny) : (ev.xmotion.y - ocy - 2 * c->bw + 1),
               1);

      if (c->crop) {
        nw = MIN(nw, c->crop->w + c->crop->x);
        nh = MIN(nh, c->crop->h + c->crop->y);
      }

      if (!selmon->lt[selmon->sellt]->arrange || c->isfloating)
        resize(c, nx, ny, nw, nh, 1);
      break;
    }
  } while (ev.type != ButtonRelease);

  if (c->isfloating || NULL == c->mon->lt[c->mon->sellt]->arrange) {
    XWarpPointer(dpy, None, c->win, 0, 0, 0, 0,
                 horizcorner ? (-c->bw) : (c->w + c->bw - 1),
                 vertcorner ? (-c->bw) : (c->h + c->bw - 1));

  } else {
    selmon->mfact =
        (double)(ev.xmotion.x_root - selmon->mx) / (double)selmon->ww;
    arrange(selmon);
    XWarpPointer(dpy, None, root, 0, 0, 0, 0,
                 selmon->mx + (selmon->ww * selmon->mfact),
                 selmon->my + (selmon->wh / 2));
  }

  XUngrabPointer(dpy, CurrentTime);
  while (XCheckMaskEvent(dpy, EnterWindowMask, &ev))
    ;
  if ((m = recttomon(c->x, c->y, c->w, c->h)) != selmon) {
    sendmon(c, m);
    selmon = m;
    focus(NULL);
  }
}

void restack(Monitor *m) {
  Client *c;
  XEvent ev;
  XWindowChanges wc;

  drawbar(m);
  if (!m->sel)
    return;
  if (m->sel->isfloating || !m->lt[m->sellt]->arrange)
    XRaiseWindow(dpy, m->sel->win);

  /* raise the aot window */
  for (Monitor *m_search = mons; m_search; m_search = m_search->next) {
    for (c = m_search->clients; c; c = c->next) {
      if (c->isalwaysontop) {
        XRaiseWindow(dpy, c->win);
        break;
      }
    }
  }

  if (m->lt[m->sellt]->arrange) {
    wc.stack_mode = Below;
    wc.sibling = m->barwin;
    for (c = m->stack; c; c = c->snext)
      if (!c->isfloating && ISVISIBLE(c)) {
        XConfigureWindow(dpy, c->win, CWSibling | CWStackMode, &wc);
        wc.sibling = c->win;
      }
  }
  XSync(dpy, False);
  while (XCheckMaskEvent(dpy, EnterWindowMask, &ev))
    ;
}

void run(void) {
  XEvent ev;
  /* main event loop */
  XSync(dpy, False);
  while (running && !XNextEvent(dpy, &ev)) {
    if (!(autostartcomplete || autostarttags))
      autostarttagsspawner();
    if (handler[ev.type])
      handler[ev.type](&ev); /* call handler */
  }
}

void col(Monitor *m) {
  unsigned int i, n, h, w, x, y, mw;
  Client *c;

  for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
    ;
  if (n == 0)
    return;

  if (n > m->nmaster)
    mw = m->nmaster ? m->ww * (m->rmaster ? 1.0 - m->mfact : m->mfact) : 0;
  else
    mw = m->ww;
  for (i = x = y = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
    if (i < m->nmaster) {
      w = (mw - x) / (MIN(n, m->nmaster) - i);
      // The positioning is correct but client pos update is sometime wrong
      resize(c, (m->rmaster ? x + m->wx + m->ww - mw : x + m->wx), m->wy,
             w - (2 * c->bw), m->wh - (2 * c->bw), 0);
      // resize(c, (x + m->wx), m->wy, w - (2 * c->bw), m->wh - (2 * c->bw), 0);
      x += WIDTH(c);
    } else {
      h = (m->wh - y) / (n - i);
      // This is correct resize function for the rmaster
      resize(c, (m->rmaster ? x + m->wx - m->ww : x + m->wx), m->wy + y,
             m->ww - x - (2 * c->bw), h - (2 * c->bw), 0);
      // resize(c, x + m->wx, m->wy + y, m->ww - x - (2 * c->bw), h - (2 *
      // c->bw),
      //        0);
      y += HEIGHT(c);
    }
}

void runautostart(void) {
  char *pathpfx;
  char *path;
  char *xdgdatahome;
  char *xdgconfighome;
  char *home;
  struct stat sb;

  if ((home = getenv("HOME")) == NULL)
    /* this is almost impossible */
    return;

  /* if $XDG_DATA_HOME is set and not empty, use $XDG_DATA_HOME/dwm,
   * otherwise use ~/.local/share/dwm as autostart script directory
   */
  xdgdatahome = getenv("XDG_DATA_HOME");
  xdgdatahome = getenv("XDG_CONFIG_HOME");
  if (xdgconfighome != NULL && *xdgconfighome != '\0') {
    /* space for path segments, separators and nul */
    pathpfx = ecalloc(1, strlen(xdgconfighome) + strlen(dwmdir) + 2);

    if (sprintf(pathpfx, "%s/%s", xdgconfighome, dwmdir) <= 0) {
      free(pathpfx);
      return;
    }
  } else if (xdgdatahome != NULL && *xdgdatahome != '\0') {
    /* space for path segments, separators and nul */
    pathpfx = ecalloc(1, strlen(xdgdatahome) + strlen(dwmdir) + 2);

    if (sprintf(pathpfx, "%s/%s", xdgdatahome, dwmdir) <= 0) {
      free(pathpfx);
      return;
    }
  } else {
    /* space for path segments, separators and nul */
    pathpfx =
        ecalloc(1, strlen(home) + strlen(localshare) + strlen(dwmdir) + 3);

    if (sprintf(pathpfx, "%s/%s/%s", home, localshare, dwmdir) < 0) {
      free(pathpfx);
      return;
    }
  }

  /* check if the autostart script directory exists */
  if (!(stat(pathpfx, &sb) == 0 && S_ISDIR(sb.st_mode))) {
    /* the XDG conformant path does not exist or is no directory
     * so we try ~/.dwm instead
     */
    char *pathpfx_new = realloc(pathpfx, strlen(home) + strlen(dwmdir) + 3);
    if (pathpfx_new == NULL) {
      free(pathpfx);
      return;
    }
    pathpfx = pathpfx_new;

    if (sprintf(pathpfx, "%s/.%s", home, dwmdir) <= 0) {
      free(pathpfx);
      return;
    }
  }

  /* try the blocking script first */
  path = ecalloc(1, strlen(pathpfx) + strlen(autostartblocksh) + 2);
  if (sprintf(path, "%s/%s", pathpfx, autostartblocksh) <= 0) {
    free(path);
    free(pathpfx);
  }

  if (access(path, X_OK) == 0)
    system(path);

  /* now the non-blocking script */
  if (sprintf(path, "%s/%s", pathpfx, autostartsh) <= 0) {
    free(path);
    free(pathpfx);
  }

  if (access(path, X_OK) == 0)
    system(strcat(path, " &"));

  free(pathpfx);
  free(path);
}

void scan(void) {
  unsigned int i, num;
  Window d1, d2, *wins = NULL;
  XWindowAttributes wa;

  if (XQueryTree(dpy, root, &d1, &d2, &wins, &num)) {
    for (i = 0; i < num; i++) {
      if (!XGetWindowAttributes(dpy, wins[i], &wa) || wa.override_redirect ||
          XGetTransientForHint(dpy, wins[i], &d1))
        continue;
      if (wa.map_state == IsViewable || getstate(wins[i]) == IconicState)
        manage(wins[i], &wa);
    }
    for (i = 0; i < num; i++) { /* now the transients */
      if (!XGetWindowAttributes(dpy, wins[i], &wa))
        continue;
      if (XGetTransientForHint(dpy, wins[i], &d1) &&
          (wa.map_state == IsViewable || getstate(wins[i]) == IconicState))
        manage(wins[i], &wa);
    }
    if (wins)
      XFree(wins);
  }
}

static void scratchpad_hide() {
  if (selmon->sel) {
    selmon->sel->tags = SCRATCHPAD_MASK;
    selmon->sel->isfloating = 1;
    focus(NULL);
    arrange(selmon);
  }
}

static _Bool scratchpad_last_showed_is_killed(void) {
  _Bool killed = 1;
  for (Client *c = selmon->clients; c != NULL; c = c->next) {
    if (c == scratchpad_last_showed) {
      killed = 0;
      break;
    }
  }
  return killed;
}

static void scratchpad_remove() {
  if (selmon->sel && scratchpad_last_showed != NULL &&
      selmon->sel == scratchpad_last_showed)
    scratchpad_last_showed = NULL;
}

static void scratchpad_show() {
  if (scratchpad_last_showed == NULL || scratchpad_last_showed_is_killed())
    scratchpad_show_first();
  else {
    if (scratchpad_last_showed->tags != SCRATCHPAD_MASK) {
      scratchpad_last_showed->tags = SCRATCHPAD_MASK;
      focus(NULL);
      arrange(selmon);
    } else {
      _Bool found_current = 0;
      _Bool found_next = 0;
      for (Client *c = selmon->clients; c != NULL; c = c->next) {
        if (found_current == 0) {
          if (c == scratchpad_last_showed) {
            found_current = 1;
            continue;
          }
        } else {
          if (c->tags == SCRATCHPAD_MASK) {
            found_next = 1;
            scratchpad_show_client(c);
            break;
          }
        }
      }
      if (found_next == 0)
        scratchpad_show_first();
    }
  }
}

static _Bool scratchpad_show_client_by_pid(pid_t pid) {
  for (Client *c = selmon->clients; c != NULL; c = c->next) {
    if (c->pid == pid) {
      scratchpad_show_client(c);
      return 1;
    }
  }
  return 0;
}

static void scratchpad_show_client(Client *c) {
  scratchpad_last_showed = c;
  c->tags = selmon->tagset[selmon->seltags];
  applyrules(c);
  focus(c);
  arrange(selmon);
}

static void scratchpad_show_first(void) {
  for (Client *c = selmon->clients; c != NULL; c = c->next) {
    if (c->tags == SCRATCHPAD_MASK) {
      scratchpad_show_client(c);
      break;
    }
  }
}

void sendmon(Client *c, Monitor *m) {
  if (c->mon == m)
    return;
  unfocus(c, 1);
  detach(c);
  detachstack(c);
  c->mon = m;
  c->tags = m->tagset[m->seltags]; /* assign tags of target monitor */
  attachbottom(c);
  attachstack(c);
  setclienttagprop(c);
  focus(NULL);
  arrange(NULL);
}

void setclientstate(Client *c, long state) {
  long data[] = {state, None};

  if (c->crop)
    c = c->crop;
  XChangeProperty(dpy, c->win, wmatom[WMState], wmatom[WMState], 32,
                  PropModeReplace, (unsigned char *)data, 2);
}

int sendevent(Window w, Atom proto, int mask, long d0, long d1, long d2,
              long d3, long d4) {
  int n;
  Atom *protocols, mt;
  int exists = 0;
  XEvent ev;

  if (proto == wmatom[WMTakeFocus] || proto == wmatom[WMDelete]) {
    mt = wmatom[WMProtocols];
    if (XGetWMProtocols(dpy, w, &protocols, &n)) {
      while (!exists && n--)
        exists = protocols[n] == proto;
      XFree(protocols);
    }
  } else {
    exists = True;
    mt = proto;
  }

  if (exists) {
    ev.type = ClientMessage;
    ev.xclient.window = w;
    ev.xclient.message_type = mt;
    ev.xclient.format = 32;
    ev.xclient.data.l[0] = d0;
    ev.xclient.data.l[1] = d1;
    ev.xclient.data.l[2] = d2;
    ev.xclient.data.l[3] = d3;
    ev.xclient.data.l[4] = d4;
    XSendEvent(dpy, w, False, mask, &ev);
  }
  return exists;
}

void setfocus(Client *c) {
  if (c->crop)
    c = c->crop;
  if (!c->neverfocus) {
    XSetInputFocus(dpy, c->win, RevertToPointerRoot, CurrentTime);
    XChangeProperty(dpy, root, netatom[NetActiveWindow], XA_WINDOW, 32,
                    PropModeReplace, (unsigned char *)&(c->win), 1);
  }
  sendevent(c->win, wmatom[WMTakeFocus], NoEventMask, wmatom[WMTakeFocus],
            CurrentTime, 0, 0, 0);
}

void setfullscreen(Client *c, int fullscreen) {
  if (c->crop)
    c = c->crop;
  if (fullscreen && !c->isfullscreen) {
    XChangeProperty(dpy, c->win, netatom[NetWMState], XA_ATOM, 32,
                    PropModeReplace, (unsigned char *)&netatom[NetWMFullscreen],
                    1);
    c->isfullscreen = 1;
    if (!isfakefullscreen) {
      c->oldstate = c->isfloating;
      c->oldbw = c->bw;
      c->bw = 0;
      c->isfloating = 1;
      resizeclient(c, c->mon->mx, c->mon->my, c->mon->mw, c->mon->mh);
      XRaiseWindow(dpy, c->win);
      isfakefullscreen = defaultfakefullscreenmode;
    }
  } else if (!fullscreen && c->isfullscreen) {
    XChangeProperty(dpy, c->win, netatom[NetWMState], XA_ATOM, 32,
                    PropModeReplace, (unsigned char *)0, 0);
    c->isfullscreen = 0;
    if (!isfakefullscreen) {
      c->isfloating = c->oldstate;
      c->bw = c->oldbw;
      c->x = c->oldx;
      c->y = c->oldy;
      c->w = c->oldw;
      c->h = c->oldh;
      resizeclient(c, c->x, c->y, c->w, c->h);
      arrange(c->mon);
      isfakefullscreen = defaultfakefullscreenmode;
    }
  }
}

Layout *last_layout;
void fullscreen(const Arg *arg) {
  if (selmon->showbar) {
    for (last_layout = (Layout *)layouts;
         last_layout != selmon->lt[selmon->sellt]; last_layout++)
      ;
    setlayout(&((Arg){.v = &layouts[1]}));
  } else {
    setlayout(&((Arg){.v = last_layout}));
  }
  togglebar(arg);
}

void setlayout(const Arg *arg) {
  unsigned int i;
  if (!arg || !arg->v || arg->v != selmon->lt[selmon->sellt])
    selmon->sellt ^= 1;
  if (arg && arg->v)
    selmon->lt[selmon->sellt] = (Layout *)arg->v;
  strncpy(selmon->ltsymbol, selmon->lt[selmon->sellt]->symbol,
          sizeof selmon->ltsymbol);

  for (i = 0; i < LENGTH(tags); ++i)
    if (selmon->tagset[selmon->seltags] & 1 << i) {
      selmon->pertag->ltidxs[i + 1][selmon->sellt] = selmon->lt[selmon->sellt];
      selmon->pertag->sellts[i + 1] = selmon->sellt;
    }

  if (selmon->pertag->curtag == 0) {
    selmon->pertag->ltidxs[0][selmon->sellt] = selmon->lt[selmon->sellt];
    selmon->pertag->sellts[0] = selmon->sellt;
  }

  if (selmon->sel)
    arrange(selmon);
  else
    drawbar(selmon);
}

void setcfact(const Arg *arg) {
  float f;
  Client *c;

  c = selmon->sel;

  if (!arg || !c || !selmon->lt[selmon->sellt]->arrange)
    return;
  f = arg->f + c->cfact;
  if (arg->f == 0.0)
    f = 1.0;
  else if (f < 0.25 || f > 4.0)
    return;
  c->cfact = f;
  arrange(selmon);
}

/* arg > 1.0 will set mfact absolutely */
void setmfact(const Arg *arg) {
  float f;
  unsigned int i;

  if (!arg || !selmon->lt[selmon->sellt]->arrange)
    return;
  f = arg->f < 1.0 ? arg->f + selmon->mfact : arg->f - 1.0;

  if (arg->f == 0.0)
    f = mfact;
  if (f < 0.05 || f > 0.95)
    return;
  selmon->mfact = f;
  for (i = 0; i < LENGTH(tags); ++i)
    if (selmon->tagset[selmon->seltags] & 1 << i)
      selmon->pertag->mfacts[i + 1] = f;

  if (selmon->pertag->curtag == 0) {
    selmon->pertag->mfacts[0] = f;
  }

  arrange(selmon);
}

void setscheme(const Arg *arg) {
  ptrdiff_t si = (scheme - schemes) + arg->i * SchemeN;

  /* wrap around, won't work if (abs(arg->i) > LENGTH(colors)) */
  if (si < 0)
    si += LENGTH(colors) * SchemeN;
  else if (si >= LENGTH(colors) * SchemeN)
    si -= LENGTH(colors) * SchemeN;

  scheme = &schemes[si];
  drawbars();
}

void setup(void) {
  int i, j;
  XSetWindowAttributes wa;
  Atom utf8string;
  struct sigaction sa;

  /* do not transform children into zombies when they terminate */
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT | SA_RESTART;
  sa.sa_handler = SIG_IGN;
  sigaction(SIGCHLD, &sa, NULL);

  signal(SIGHUP, sighup);
  signal(SIGTERM, sigterm);

  /* clean up any zombies (inherited from .xinitrc etc) immediately */
  while (waitpid(-1, NULL, WNOHANG) > 0)
    ;

  /* init screen */
  defaultfakefullscreenmode = isfakefullscreen;
  screen = DefaultScreen(dpy);
  sw = DisplayWidth(dpy, screen);
  sh = DisplayHeight(dpy, screen);
  root = RootWindow(dpy, screen);
  xinitvisual();
  drw = drw_create(dpy, screen, root, sw, sh, visual, depth, cmap);
  if (!drw_fontset_create(drw, fonts, LENGTH(fonts)))
    die("no fonts could be loaded.");
  lrpad = drw->fonts->h;
  bh = user_bh ? user_bh : drw->fonts->h + 2;
  sp = sidepad;
  vp = (topbar == 1) ? vertpad : -vertpad;
  updategeom();

  /* init atoms */
  utf8string = XInternAtom(dpy, "UTF8_STRING", False);
  wmatom[WMProtocols] = XInternAtom(dpy, "WM_PROTOCOLS", False);
  wmatom[WMDelete] = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
  wmatom[WMState] = XInternAtom(dpy, "WM_STATE", False);
  wmatom[WMTakeFocus] = XInternAtom(dpy, "WM_TAKE_FOCUS", False);
  netatom[NetActiveWindow] = XInternAtom(dpy, "_NET_ACTIVE_WINDOW", False);
  netatom[NetSupported] = XInternAtom(dpy, "_NET_SUPPORTED", False);
  netatom[NetSystemTray] = XInternAtom(dpy, "_NET_SYSTEM_TRAY_S0", False);
  netatom[NetSystemTrayOP] = XInternAtom(dpy, "_NET_SYSTEM_TRAY_OPCODE", False);
  netatom[NetSystemTrayOrientation] =
      XInternAtom(dpy, "_NET_SYSTEM_TRAY_ORIENTATION", False);
  netatom[NetSystemTrayOrientationHorz] =
      XInternAtom(dpy, "_NET_SYSTEM_TRAY_ORIENTATION_HORZ", False);
  netatom[NetSystemTrayVisual] =
      XInternAtom(dpy, "_NET_SYSTEM_TRAY_VISUAL", False);
  netatom[NetWMName] = XInternAtom(dpy, "_NET_WM_NAME", False);
  netatom[NetWMState] = XInternAtom(dpy, "_NET_WM_STATE", False);
  netatom[NetWMCheck] = XInternAtom(dpy, "_NET_SUPPORTING_WM_CHECK", False);
  netatom[NetWMFullscreen] =
      XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False);
  netatom[NetWMWindowType] = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", False);
  netatom[NetWMWindowTypeDock] =
      XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DOCK", False);
  netatom[NetWMWindowTypeDialog] =
      XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DIALOG", False);
  netatom[NetClientList] = XInternAtom(dpy, "_NET_CLIENT_LIST", False);
  netatom[NetClientInfo] = XInternAtom(dpy, "_NET_CLIENT_INFO", False);
  netatom[NetWMWindowsOpacity] =
      XInternAtom(dpy, "_NET_WM_WINDOW_OPACITY", False);
  xatom[Manager] = XInternAtom(dpy, "MANAGER", False);
  xatom[Xembed] = XInternAtom(dpy, "_XEMBED", False);
  xatom[XembedInfo] = XInternAtom(dpy, "_XEMBED_INFO", False);
  /* init cursors */
  cursor[CurNormal] = drw_cur_create(drw, XC_left_ptr);
  cursor[CurResize] = drw_cur_create(drw, XC_sizing);
  cursor[CurMove] = drw_cur_create(drw, XC_fleur);
  /* init appearance */
  schemes = ecalloc(LENGTH(colors), SchemeN * sizeof(Clr *));
  for (j = LENGTH(colors) - 1; j >= 0; j--) {
    scheme = &schemes[j * SchemeN];
    for (i = 0; i < SchemeN; i++)
      scheme[i] = drw_scm_create(drw, colors[j][i], alphas[i], 3);
  }
  /* init system tray */
  if (showsystray)
    updatesystray(0);
  /* init bars */
  updatebars();
  updatestatus();
  /* supporting window for NetWMCheck */
  wmcheckwin = XCreateSimpleWindow(dpy, root, 0, 0, 1, 1, 0, 0, 0);
  XChangeProperty(dpy, wmcheckwin, netatom[NetWMCheck], XA_WINDOW, 32,
                  PropModeReplace, (unsigned char *)&wmcheckwin, 1);
  XChangeProperty(dpy, wmcheckwin, netatom[NetWMName], utf8string, 8,
                  PropModeReplace, (unsigned char *)"dwm", 3);
  XChangeProperty(dpy, root, netatom[NetWMCheck], XA_WINDOW, 32,
                  PropModeReplace, (unsigned char *)&wmcheckwin, 1);
  /* EWMH support per view */
  XChangeProperty(dpy, root, netatom[NetSupported], XA_ATOM, 32,
                  PropModeReplace, (unsigned char *)netatom, NetLast);
  XDeleteProperty(dpy, root, netatom[NetClientList]);
  XDeleteProperty(dpy, root, netatom[NetClientInfo]);
  /* select events */
  wa.cursor = cursor[CurNormal]->cursor;
  wa.event_mask = SubstructureRedirectMask | SubstructureNotifyMask |
                  ButtonPressMask | PointerMotionMask | EnterWindowMask |
                  LeaveWindowMask | StructureNotifyMask | PropertyChangeMask;
  XChangeWindowAttributes(dpy, root, CWEventMask | CWCursor, &wa);
  XSelectInput(dpy, root, wa.event_mask);
  grabkeys();
  focus(NULL);
}

void seturgent(Client *c, int urg) {
  XWMHints *wmh;

  c->isurgent = urg;
  if (!(wmh = XGetWMHints(dpy, c->win)))
    return;
  wmh->flags = urg ? (wmh->flags | XUrgencyHint) : (wmh->flags & ~XUrgencyHint);
  XSetWMHints(dpy, c->win, wmh);
  XFree(wmh);
}

void showhide(Client *c) {
  if (!c)
    return;
  if (ISVISIBLE(c)) {
    /* show clients top down */
    XMoveWindow(dpy, c->win, c->x, c->y);
    if (isfakefullscreen) {
      if (!c->mon->lt[c->mon->sellt]->arrange || c->isfloating)
        resize(c, c->x, c->y, c->w, c->h, 0);
    } else {
      if ((!c->mon->lt[c->mon->sellt]->arrange || c->isfloating) &&
          !c->isfullscreen)
        resize(c, c->x, c->y, c->w, c->h, 0);
    }
    showhide(c->snext);
  } else {
    /* hide clients bottom up */
    showhide(c->snext);
    XMoveWindow(dpy, c->win, WIDTH(c) * -2, c->y);
  }
}

void sigstatusbar(const Arg *arg) {
  union sigval sv;

  if (!statussig)
    return;
  sv.sival_int = arg->i;
  if ((statuspid = getstatusbarpid()) <= 0)
    return;

  sigqueue(statuspid, SIGRTMIN + statussig, sv);
}

void sighup(int unused) {
  Arg a = {.i = 1};
  quit(&a);
}

void sigterm(int unused) {
  Arg a = {.i = 0};
  quit(&a);
}

void spawn(const Arg *arg) {
  struct sigaction sa;

  if (arg->v == dmenucmd)
    dmenumon[0] = '0' + selmon->num;
  if (fork() == 0) {
    if (dpy) {
      close(ConnectionNumber(dpy));
    }

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SIG_DFL;
    sigaction(SIGCHLD, &sa, NULL);

    pid_t pid = setsid();
    _Bool pid_found = 0;
    pid_found = scratchpad_show_client_by_pid(pid);

    if (pid_found) {
      die("dwm: process '%s' allready exists:", ((char **)arg->v)[0]);
    } else {
      execvp(((char **)arg->v)[0], (char **)arg->v);
      die("dwm: execvp '%s' failed:", ((char **)arg->v)[0]);
    }
  }
}

void spawnscratch(const Arg *arg) {
  if (fork() == 0) {
    if (dpy)
      close(ConnectionNumber(dpy));
    setsid();
    execvp(((char **)arg->v)[1], ((char **)arg->v) + 1);
    fprintf(stderr, "dwm: execvp %s", ((char **)arg->v)[1]);
    perror(" failed");
    exit(EXIT_SUCCESS);
  }
}

void setclienttagprop(Client *c) {
  long data[] = {(long)c->tags, (long)c->mon->num};
  XChangeProperty(dpy, c->win, netatom[NetClientInfo], XA_CARDINAL, 32,
                  PropModeReplace, (unsigned char *)data, 2);
}

Monitor *systraytomon(Monitor *m) {
  Monitor *t;
  int i, n;
  if (!systraypinning) {
    if (!m)
      return selmon;
    return m == selmon ? m : NULL;
  }
  for (n = 1, t = mons; t && t->next; n++, t = t->next)
    ;
  for (i = 1, t = mons; t && t->next && i < systraypinning; i++, t = t->next)
    ;
  if (systraypinningfailfirst && n < systraypinning)
    return mons;
  return t;
}

void horizontal(Monitor *m) {
  Client *c;
  unsigned int n, i;

  /* Count windows */
  for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
    ;

  if (!n)
    return;
  else /* Split vertically */
    for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
      resize(c, m->wx + i * m->mw / n, m->wy, m->mw / n - (2 * c->bw),
             m->wh - (2 * c->bw), False);
}

void stairs(Monitor *m) {
  unsigned int i, n, h, mw, my;
  unsigned int ox, oy, ow, oh; /* stair offset values */
  Client *c;

  for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
    ;
  if (n == 0)
    return;

  if (n > m->nmaster)
    mw = m->nmaster ? m->ww * (m->rmaster ? 1.0 - m->mfact : m->mfact) : 0;
  else
    mw = m->ww;

  for (i = my = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
    if (i < m->nmaster) {
      h = (m->wh - my) / (MIN(n, m->nmaster) - i);
      resize(c, (m->rmaster ? m->wx + m->ww - mw : m->wx), m->wy + my,
             mw - (2 * c->bw), h - (2 * c->bw), 0);
      if (my + HEIGHT(c) < m->wh)
        my += HEIGHT(c);
    } else {
      oy = i - m->nmaster;
      ox = stairdirection ? n - i - 1 : (stairsamesize ? i - m->nmaster : 0);
      ow = stairsamesize ? n - m->nmaster - 1 : n - i - 1;
      oh = stairsamesize ? ow : i - m->nmaster;
      resize(
          c,
          (m->rmaster ? m->wx + (ox * stairpx) : m->wx + mw + (ox * stairpx)),
          m->wy + (oy * stairpx), m->ww - mw - (2 * c->bw) - (ow * stairpx),
          m->wh - (2 * c->bw) - (oh * stairpx), 0);
    }
  }
}

void tag(const Arg *arg) {
  Client *c;
  if (!selmon->sel)
    return;
  if (arg->ui & TAGMASK) {
    c = selmon->sel;
    selmon->sel->tags = arg->ui & TAGMASK;
    setclienttagprop(c);
    focus(NULL);
    arrange(selmon);
    if (viewontag && ((arg->ui & TAGMASK) != TAGMASK)) {
      view(arg);
    }
  } else {
    selmon->sel->tags = selmon->tagset[selmon->seltags ^ 1];
    focus(NULL);
    arrange(selmon);
  }
}

void autostarttagsspawner(void) {
  int i;
  Arg arg;

  for (i = autostartcmdscomplete; i < LENGTH(autostarttaglist); i++) {
    autostartcmdscomplete += 1;
    autostarttags = autostarttaglist[i].tags;
    arg.v = autostarttaglist[i].cmd;
    spawn(&arg);
    return;
  }
  autostartcomplete = 1;
  return;
}

void applyautostarttags(Client *c) {
  if (!c)
    return;
  c->tags = autostarttags;
  autostarttags = 0;
  return;
}

void tagmon(const Arg *arg) {
  if (!selmon->sel || !mons->next)
    return;
  sendmon(selmon->sel, dirtomon(arg->i));
}

void tagnthmon(const Arg *arg) {
  if (!selmon->sel || !mons->next)
    return;
  sendmon(selmon->sel, numtomon(arg->i));
}

Monitor *numtomon(int num) {
  Monitor *m = NULL;
  int i = 0;

  for (m = mons, i = 0; m->next && i < num; m = m->next) {
    i++;
  }
  return m;
}

void togglebar(const Arg *arg) {
  unsigned int i;
  selmon->showbar = !selmon->showbar;
  for (i = 0; i < LENGTH(tags); ++i)
    if (selmon->tagset[selmon->seltags] & 1 << i)
      selmon->pertag->showbars[i + 1] = selmon->showbar;

  if (selmon->pertag->curtag == 0) {
    selmon->pertag->showbars[0] = selmon->showbar;
  }
  updatebarpos(selmon);
  XMoveResizeWindow(dpy, selmon->barwin, selmon->wx + sp, selmon->by + vp,
                    selmon->ww - 2 * sp, bh);
  if (showsystray) {
    XWindowChanges wc;
    if (!selmon->showbar)
      wc.y = -bh;
    else if (selmon->showbar) {
      wc.y = vp;
      if (!selmon->topbar)
        wc.y = selmon->mh - bh + vp;
    }
    XConfigureWindow(dpy, systray->win, CWY, &wc);
  }
  updatesystray(1);
  arrange(selmon);
}

void toggleall(const Arg *arg) {
  int i;
  unsigned int tmptag;

  Monitor *m;
  for (m = mons; m; m = m->next) {

    if ((arg->ui & TAGMASK) == m->tagset[m->seltags])
      return;
    m->seltags ^= 1; /* toggle sel tagset */
    if (arg->ui & TAGMASK) {
      m->tagset[m->seltags] = arg->ui & TAGMASK;
      m->pertag->prevtag = m->pertag->curtag;

      if (arg->ui == ~0)
        m->pertag->curtag = 0;
      else {
        for (i = 0; !(arg->ui & 1 << i); i++)
          ;
        m->pertag->curtag = i + 1;
      }
    } else {
      tmptag = m->pertag->prevtag;
      m->pertag->prevtag = m->pertag->curtag;
      m->pertag->curtag = tmptag;
    }

    m->nmaster = m->pertag->nmasters[m->pertag->curtag];
    m->mfact = m->pertag->mfacts[m->pertag->curtag];
    m->sellt = m->pertag->sellts[m->pertag->curtag];
    m->lt[m->sellt] = m->pertag->ltidxs[m->pertag->curtag][m->sellt];
    m->lt[m->sellt ^ 1] = m->pertag->ltidxs[m->pertag->curtag][m->sellt ^ 1];

    if (m->showbar != m->pertag->showbars[m->pertag->curtag])
      togglebar(NULL);

    focus(NULL);
    arrange(m);
  }
}

void toggleallowkill(const Arg *arg) {
  if (!selmon->sel)
    return;
  selmon->sel->allowkill = !selmon->sel->allowkill;
}

void togglealttag(const Arg *arg) {
  selmon->alttag = !selmon->alttag;
  drawbar(selmon);
}

void togglefloating(const Arg *arg) {
  if (!selmon->sel)
    return;
  if (!isfakefullscreen) {
    if (selmon->sel->isfullscreen) /* no support for fullscreen windows */
      return;
  }
  selmon->sel->isfloating = !selmon->sel->isfloating || selmon->sel->isfixed;
  if (selmon->sel->isfloating) {

    if (selmon->sel != 0) {
      Client *c = selmon->sel;
      c->x = c->mon->mx + (c->mon->mw - WIDTH(c)) / 2;
      c->y = c->mon->my + (c->mon->mh - HEIGHT(c)) / 2;
      resize(selmon->sel, c->x, c->y, c->w, c->h, 0);
    } else {
      resize(selmon->sel, selmon->sel->x, selmon->sel->y + user_bh,
             selmon->sel->w, selmon->sel->h, 0);
    }

    if (selmon->sel->isforegrounded) {
      selmon->sel->isforegrounded = 0;
      detachforegrounded(selmon->sel);
      arrangeforegrounded(selmon);
    }

  } else {
    selmon->sel->isalwaysontop = 0; /* disabled, turn this off too */
  }
  if (!selmon->sel->isfloating && selmon->sel->crop)
    cropdelete(selmon->sel);
  arrange(selmon);
}

void togglealwaysontop(const Arg *arg) {
  if (!selmon->sel)
    return;
  if (selmon->sel->isfullscreen)
    return;

  if (selmon->sel->isalwaysontop) {
    selmon->sel->isalwaysontop = 0;
  } else {
    /* disable others */
    for (Monitor *m = mons; m; m = m->next)
      for (Client *c = m->clients; c; c = c->next)
        c->isalwaysontop = 0;

    /* turn on, make it float too */
    selmon->sel->isfloating = 1;
    selmon->sel->isalwaysontop = 1;
  }

  arrange(selmon);
}

void togglermaster(const Arg *arg) {
  selmon->rmaster = !selmon->rmaster;
  /* now mfact represents the left factor */
  selmon->mfact = 1.0 - selmon->mfact;
  if (selmon->lt[selmon->sellt]->arrange)
    arrange(selmon);
}

void togglescratch(const Arg *arg) {
  Client *c;
  unsigned int found = 0;

  for (c = selmon->clients;
       c && !(found = c->scratchkey == ((char **)arg->v)[0][0]); c = c->next)
    ;
  if (found) {
    c->tags = ISVISIBLE(c) ? 0 : selmon->tagset[selmon->seltags];

    focus(NULL);
    arrange(selmon);

    if (ISVISIBLE(c)) {
      focus(c);
      restack(selmon);
    }

  } else {
    spawnscratch(arg);
  }
}

Client *findbefore(Client *c) {
  Client *tmp;
  if (c == selmon->clients)
    return NULL;
  for (tmp = selmon->clients; tmp && tmp->next != c; tmp = tmp->next)
    ;
  return tmp;
}

void togglefullscr(const Arg *arg) {

  if (isfakefullscreen) {
    isfakefullscreen = False;
  }
  if (selmon->sel)
    setfullscreen(selmon->sel, !selmon->sel->isfullscreen);
}

void togglesticky(const Arg *arg) {
  if (!selmon->sel)
    return;
  selmon->sel->issticky = !selmon->sel->issticky;
  arrange(selmon);
}

void toggleopacity(const Arg *arg) {
  bUseOpacity = !bUseOpacity;
  for (Monitor *m = mons; m; m = m->next)
    for (Client *c = m->clients; c; c = c->next)
      opacity(c, (bUseOpacity && c != selmon->sel) ? inactiveopacity
                                                   : activeopacity);
}

void toggletag(const Arg *arg) {
  unsigned int newtags;

  if (!selmon->sel)
    return;
  newtags = selmon->sel->tags ^ (arg->ui & TAGMASK);
  if (newtags) {
    selmon->sel->tags = newtags;
    setclienttagprop(selmon->sel);
    focus(NULL);
    arrange(selmon);
  }
}

void toggleview(const Arg *arg) {
  unsigned int newtagset =
      selmon->tagset[selmon->seltags] ^ (arg->ui & TAGMASK);
  int i;

  if (newtagset) {
    selmon->tagset[selmon->seltags] = newtagset;

    if (newtagset == ~0) {
      selmon->pertag->prevtag = selmon->pertag->curtag;
      selmon->pertag->curtag = 0;
    }

    /* test if the user did not select the same tag */
    if (!(newtagset & 1 << (selmon->pertag->curtag - 1))) {
      selmon->pertag->prevtag = selmon->pertag->curtag;
      for (i = 0; !(newtagset & 1 << i); i++)
        ;
      selmon->pertag->curtag = i + 1;
    }

    /* apply settings for this view */
    selmon->nmaster = selmon->pertag->nmasters[selmon->pertag->curtag];
    selmon->mfact = selmon->pertag->mfacts[selmon->pertag->curtag];
    selmon->sellt = selmon->pertag->sellts[selmon->pertag->curtag];
    selmon->lt[selmon->sellt] =
        selmon->pertag->ltidxs[selmon->pertag->curtag][selmon->sellt];
    selmon->lt[selmon->sellt ^ 1] =
        selmon->pertag->ltidxs[selmon->pertag->curtag][selmon->sellt ^ 1];

    selmon->gappoh = (selmon->pertag->gaps[selmon->pertag->curtag] & 0xff) >> 0;
    selmon->gappov =
        (selmon->pertag->gaps[selmon->pertag->curtag] & 0xff00) >> 8;
    selmon->gappih =
        (selmon->pertag->gaps[selmon->pertag->curtag] & 0xff0000) >> 16;
    selmon->gappiv =
        (selmon->pertag->gaps[selmon->pertag->curtag] & 0xff000000) >> 24;
    if (selmon->showbar != selmon->pertag->showbars[selmon->pertag->curtag])
      togglebar(NULL);

    focus(NULL);
    arrange(selmon);
  }
}

void unfocus(Client *c, int setfocus) {
  if (!c)
    return;
  grabbuttons(c, 0);
  opacity(c, inactiveopacity);
  lastfocused = c;
  if (setfocus) {
    XSetInputFocus(dpy, root, RevertToPointerRoot, CurrentTime);
    XDeleteProperty(dpy, root, netatom[NetActiveWindow]);
  }
}

void unmanage(Client *c, int destroyed) {
  Monitor *m = c->mon;
  XWindowChanges wc;

  if (c->swallowing) {
    unswallow(c);
    return;
  }

  if (c->switchtotag) {
    if (m->sel->next == 0) {
      Arg a = {.ui = c->switchtotag};
      view(&a);
    }
  }

  Client *s = swallowingclient(c->win);
  if (s) {
    free(s->swallowing);
    s->swallowing = NULL;
    arrange(m);
    if (m == selmon && m->sel)
      XWarpPointer(dpy, None, m->sel->win, 0, 0, 0, 0, m->sel->w / 2,
                   m->sel->h / 2);
    focus(NULL);
    return;
  }

  if (c->crop)
    cropdelete(c);
  detach(c);
  detachstack(c);

  if (c->isforegrounded) {
    detachforegrounded(c);
    arrangeforegrounded(m);
  }

  if (!destroyed) {
    wc.border_width = c->oldbw;
    XGrabServer(dpy); /* avoid race conditions */
    XSetErrorHandler(xerrordummy);
    XSelectInput(dpy, c->win, NoEventMask);
    XConfigureWindow(dpy, c->win, CWBorderWidth, &wc); /* restore border */
    XUngrabButton(dpy, AnyButton, AnyModifier, c->win);
    setclientstate(c, WithdrawnState);
    XSync(dpy, False);
    XSetErrorHandler(xerror);
    XUngrabServer(dpy);
  }
  if (scratchpad_last_showed == c)
    scratchpad_last_showed = NULL;
  if (lastfocused == c)
    lastfocused = NULL;
  free(c);

  if (!s) {
    arrange(m);
    focus(NULL);
    updateclientlist();
  }
}

void unmapnotify(XEvent *e) {
  Client *c;
  XUnmapEvent *ev = &e->xunmap;

  if ((c = wintoclient(ev->window)) || (c = cropwintoclient(ev->window))) {
    if (ev->send_event)
      setclientstate(c, WithdrawnState);
    else
      unmanage(c, 0);
  } else if ((c = wintosystrayicon(ev->window))) {
    /* KLUDGE! sometimes icons occasionally unmap their windows, but do
     * _not_ destroy them. We map those windows back */
    XMapRaised(dpy, c->win);
    updatesystray(1);
  }
}

void updatebars(void) {
  unsigned int w;
  Monitor *m;
  XSetWindowAttributes wa = {.override_redirect = True,
                             .background_pixel = 0,
                             .border_pixel = 0,
                             .colormap = cmap,
                             .event_mask = ButtonPressMask | ExposureMask};
  XClassHint ch = {"dwm", "dwm"};
  for (m = mons; m; m = m->next) {
    if (m->barwin)
      continue;
    w = m->ww;
    m->barwin = XCreateWindow(dpy, root, m->wx + sp, m->by + vp, w - 2 * sp, bh,
                              0, depth, InputOutput, visual,
                              CWOverrideRedirect | CWBackPixel | CWBorderPixel |
                                  CWColormap | CWEventMask,
                              &wa);
    XDefineCursor(dpy, m->barwin, cursor[CurNormal]->cursor);
    if (showsystray && m == systraytomon(m))
      XMapRaised(dpy, systray->win);
    XMapRaised(dpy, m->barwin);
    XSetClassHint(dpy, m->barwin, &ch);
  }
}

void updatebarpos(Monitor *m) {
  m->wy = m->my;
  m->wh = m->mh;
  if (m->showbar) {
    m->wh = m->wh - vertpad - bh;
    m->by = m->topbar ? m->wy : m->wy + m->wh + vertpad;
    m->wy = m->topbar ? m->wy + bh + vp : m->wy;
  } else
    m->by = -bh - vp;
}

void updateclientlist() {
  Client *c;
  Monitor *m;

  XDeleteProperty(dpy, root, netatom[NetClientList]);
  for (m = mons; m; m = m->next)
    for (c = m->clients; c; c = c->next)
      XChangeProperty(dpy, root, netatom[NetClientList], XA_WINDOW, 32,
                      PropModeAppend, (unsigned char *)&(c->win), 1);
}

int updategeom(void) {
  int dirty = 0;

#ifdef XINERAMA
  if (XineramaIsActive(dpy)) {
    int i, j, n, nn;
    Client *c;
    Monitor *m;
    XineramaScreenInfo *info = XineramaQueryScreens(dpy, &nn);
    XineramaScreenInfo *unique = NULL;

    for (n = 0, m = mons; m; m = m->next, n++)
      ;
    /* only consider unique geometries as separate screens */
    unique = ecalloc(nn, sizeof(XineramaScreenInfo));
    for (i = 0, j = 0; i < nn; i++)
      if (isuniquegeom(unique, j, &info[i]))
        memcpy(&unique[j++], &info[i], sizeof(XineramaScreenInfo));
    XFree(info);
    nn = j;

    /* new monitors if nn > n */
    for (i = n; i < nn; i++) {
      for (m = mons; m && m->next; m = m->next)
        ;
      if (m)
        m->next = createmon();
      else
        mons = createmon();
    }
    for (i = 0, m = mons; i < nn && m; m = m->next, i++)
      if (i >= n || unique[i].x_org != m->mx || unique[i].y_org != m->my ||
          unique[i].width != m->mw || unique[i].height != m->mh) {
        dirty = 1;
        m->num = i;
        m->mx = m->wx = unique[i].x_org;
        m->my = m->wy = unique[i].y_org;
        m->mw = m->ww = unique[i].width;
        m->mh = m->wh = unique[i].height;
        updatebarpos(m);
      }
    /* removed monitors if n > nn */
    for (i = nn; i < n; i++) {
      for (m = mons; m && m->next; m = m->next)
        ;
      while ((c = m->clients)) {
        dirty = 1;
        m->clients = c->next;
        detachstack(c);
        c->mon = mons;
        attachbottom(c);
        attachstack(c);
      }
      if (m == selmon)
        selmon = mons;
      cleanupmon(m);
    }
    free(unique);
  } else
#endif /* XINERAMA */
  {    /* default monitor setup */
    if (!mons)
      mons = createmon();
    if (mons->mw != sw || mons->mh != sh) {
      dirty = 1;
      mons->mw = mons->ww = sw;
      mons->mh = mons->wh = sh;
      updatebarpos(mons);
    }
  }
  if (dirty) {
    selmon = mons;
    selmon = wintomon(root);
  }
  return dirty;
}

void updatenumlockmask(void) {
  unsigned int i, j;
  XModifierKeymap *modmap;

  numlockmask = 0;
  modmap = XGetModifierMapping(dpy);
  for (i = 0; i < 8; i++)
    for (j = 0; j < modmap->max_keypermod; j++)
      if (modmap->modifiermap[i * modmap->max_keypermod + j] ==
          XKeysymToKeycode(dpy, XK_Num_Lock))
        numlockmask = (1 << i);
  XFreeModifiermap(modmap);
}

void updatesizehints(Client *c) {
  long msize;
  XSizeHints size;

  if (!XGetWMNormalHints(dpy, c->win, &size, &msize))
    /* size is uninitialized, ensure that size.flags aren't used */
    size.flags = PSize;
  if (size.flags & PBaseSize) {
    c->basew = size.base_width;
    c->baseh = size.base_height;
  } else if (size.flags & PMinSize) {
    c->basew = size.min_width;
    c->baseh = size.min_height;
  } else
    c->basew = c->baseh = 0;
  if (size.flags & PResizeInc) {
    c->incw = size.width_inc;
    c->inch = size.height_inc;
  } else
    c->incw = c->inch = 0;
  if (size.flags & PMaxSize) {
    c->maxw = size.max_width;
    c->maxh = size.max_height;
  } else
    c->maxw = c->maxh = 0;
  if (size.flags & PMinSize) {
    c->minw = size.min_width;
    c->minh = size.min_height;
  } else if (size.flags & PBaseSize) {
    c->minw = size.base_width;
    c->minh = size.base_height;
  } else
    c->minw = c->minh = 0;
  if (size.flags & PAspect) {
    c->mina = (float)size.min_aspect.y / size.min_aspect.x;
    c->maxa = (float)size.max_aspect.x / size.max_aspect.y;
  } else
    c->maxa = c->mina = 0.0;
  c->isfixed = (c->maxw && c->maxh && c->maxw == c->minw && c->maxh == c->minh);
  c->hintsvalid = 1;
}

void updatestatus(void) {
  Monitor *m;
  if (!gettextprop(root, XA_WM_NAME, stext, sizeof(stext))) {
    strcpy(stext, "dwm-" VERSION);
    statusw = TEXTW(stext) - lrpad + 2;
  } else {
    char *text, *s, ch;

    statusw = 0;
    for (text = s = stext; *s; s++) {
      if ((unsigned char)(*s) < ' ') {
        ch = *s;
        *s = '\0';
        statusw += TEXTW(text) - lrpad;
        *s = ch;
        text = s + 1;
      }
    }
    statusw += TEXTW(text) - lrpad + 2;
  }

  for (m = mons; m; m = m->next)
    drawbar(m);
}

void updatesystray(int updatebar) {
  XSetWindowAttributes wa;
  XWindowChanges wc;
  Client *i;
  Monitor *m = systraytomon(NULL);
  unsigned int x = m->mx + m->mw;
  unsigned int w = 1, xpad = 0, ypad = 0;
  xpad = sp;
  ypad = vp;

  if (!showsystray)
    return;
  if (!systray) {
    /* init systray */
    if (!(systray = (Systray *)calloc(1, sizeof(Systray))))
      die("fatal: could not malloc() %u bytes\n", sizeof(Systray));

    wa.override_redirect = True;
    wa.event_mask = ButtonPressMask | ExposureMask;
    wa.background_pixel = 0;
    wa.border_pixel = 0;
    wa.colormap = cmap;
    systray->win = XCreateWindow(dpy, root, x - xpad, m->by + ypad, w, bh, 0,
                                 depth, InputOutput, visual,
                                 CWOverrideRedirect | CWBackPixel |
                                     CWBorderPixel | CWColormap | CWEventMask,
                                 &wa);
    XSelectInput(dpy, systray->win, SubstructureNotifyMask);
    XChangeProperty(dpy, systray->win, netatom[NetSystemTrayOrientation],
                    XA_CARDINAL, 32, PropModeReplace,
                    (unsigned char *)&systrayorientation, 1);
    XChangeProperty(dpy, systray->win, netatom[NetSystemTrayVisual],
                    XA_VISUALID, 32, PropModeReplace,
                    (unsigned char *)&visual->visualid, 1);
    XChangeProperty(dpy, systray->win, netatom[NetWMWindowType], XA_ATOM, 32,
                    PropModeReplace,
                    (unsigned char *)&netatom[NetWMWindowTypeDock], 1);
    XMapRaised(dpy, systray->win);
    XSetSelectionOwner(dpy, netatom[NetSystemTray], systray->win, CurrentTime);
    if (XGetSelectionOwner(dpy, netatom[NetSystemTray]) == systray->win) {
      sendevent(root, xatom[Manager], StructureNotifyMask, CurrentTime,
                netatom[NetSystemTray], systray->win, 0, 0);
      XSync(dpy, False);
    } else {
      fprintf(stderr, "dwm: unable to obtain system tray.\n");
      free(systray);
      systray = NULL;
      return;
    }
  }

  for (w = 0, i = systray->icons; i; i = i->next) {
    wa.background_pixel = 0;
    XChangeWindowAttributes(dpy, i->win, CWBackPixel, &wa);
    XMapRaised(dpy, i->win);
    w += systrayspacing;
    i->x = w;
    XMoveResizeWindow(dpy, i->win, i->x, 0, i->w, i->h);
    w += i->w;
    if (i->mon != m)
      i->mon = m;
  }
  w = w ? w + systrayspacing : 1;
  x -= w;
  XMoveResizeWindow(dpy, systray->win, x - xpad, m->by + ypad, w, bh);
  wc.x = x - xpad;
  wc.y = m->by + ypad;
  wc.width = w;
  wc.height = bh;
  wc.stack_mode = Above;
  wc.sibling = m->barwin;
  XConfigureWindow(dpy, systray->win,
                   CWX | CWY | CWWidth | CWHeight | CWSibling | CWStackMode,
                   &wc);
  XMapWindow(dpy, systray->win);
  XMapSubwindows(dpy, systray->win);
  XSync(dpy, False);

  if (updatebar)
    drawbar(m);
}

void updatesystrayicongeom(Client *i, int w, int h) {
  if (i) {
    i->h = bh;
    if (w == h)
      i->w = bh;
    else if (h == bh)
      i->w = w;
    else
      i->w = (int)((float)bh * ((float)w / (float)h));
    applysizehints(i, &(i->x), &(i->y), &(i->w), &(i->h), False);
    /* force icons into the systray dimensions if they don't want to */
    if (i->h > bh) {
      if (i->w == i->h)
        i->w = bh;
      else
        i->w = (int)((float)bh * ((float)i->w / (float)i->h));
      i->h = bh;
    }
    if (i->w > 2 * bh)
      i->w = bh;
  }
}

void updatesystrayiconstate(Client *i, XPropertyEvent *ev) {
  long flags;
  int code = 0;

  if (!showsystray || !i || ev->atom != xatom[XembedInfo] ||
      !(flags = getatomprop(i, xatom[XembedInfo])))
    return;

  if (flags & XEMBED_MAPPED && !i->tags) {
    i->tags = 1;
    code = XEMBED_WINDOW_ACTIVATE;
    XMapRaised(dpy, i->win);
    setclientstate(i, NormalState);
  } else if (!(flags & XEMBED_MAPPED) && i->tags) {
    i->tags = 0;
    code = XEMBED_WINDOW_DEACTIVATE;
    XUnmapWindow(dpy, i->win);
    setclientstate(i, WithdrawnState);
  } else
    return;
  sendevent(i->win, xatom[Xembed], StructureNotifyMask, CurrentTime, code, 0,
            systray->win, XEMBED_EMBEDDED_VERSION);
}

void updatetitle(Client *c) {
  if (!gettextprop(c->win, netatom[NetWMName], c->name, sizeof c->name))
    gettextprop(c->win, XA_WM_NAME, c->name, sizeof c->name);
  if (c->name[0] == '\0') /* hack to mark broken clients */
    strcpy(c->name, broken);
}

void updatewindowtype(Client *c) {
  Atom state = getatomprop(c, netatom[NetWMState]);
  Atom wtype = getatomprop(c, netatom[NetWMWindowType]);

  if (state == netatom[NetWMFullscreen])
    setfullscreen(c, 1);
  if (wtype == netatom[NetWMWindowTypeDialog])
    c->isfloating = 1;
}

void updatewmhints(Client *c) {
  XWMHints *wmh;

  if ((wmh = XGetWMHints(dpy, c->win))) {
    if (c == selmon->sel && wmh->flags & XUrgencyHint) {
      wmh->flags &= ~XUrgencyHint;
      XSetWMHints(dpy, c->win, wmh);
    } else
      c->isurgent = (wmh->flags & XUrgencyHint) ? 1 : 0;
    if (wmh->flags & InputHint)
      c->neverfocus = !wmh->input;
    else
      c->neverfocus = 0;
    XFree(wmh);
  }
}

void cycleview(const Arg *arg) {
  unsigned int newtag;
  if (arg->ui) { /* if ui is 1 goto the left if 0 goto the right */
    newtag = selmon->tagset[selmon->seltags] >> 1;
    if (newtag == 0)
      newtag = (1 << (LENGTH(tags) - 1));
  } else {
    newtag = selmon->tagset[selmon->seltags] << 1;
    if (newtag > (1 << (LENGTH(tags) - 1)))
      newtag = 1;
  }
  Arg a = {.ui = newtag};
  view(&a);
}

void view(const Arg *arg) {
  int i;
  unsigned int tmptag;

  if ((arg->ui & TAGMASK) == selmon->tagset[selmon->seltags])
    return;
  selmon->seltags ^= 1; /* toggle sel tagset */
  if (arg->ui & TAGMASK) {
    selmon->tagset[selmon->seltags] = arg->ui & TAGMASK;
    selmon->pertag->prevtag = selmon->pertag->curtag;

    if (arg->ui == ~0)
      selmon->pertag->curtag = 0;
    else {
      for (i = 0; !(arg->ui & 1 << i); i++)
        ;
      selmon->pertag->curtag = i + 1;
    }
  } else {
    tmptag = selmon->pertag->prevtag;
    selmon->pertag->prevtag = selmon->pertag->curtag;
    selmon->pertag->curtag = tmptag;
  }

  selmon->nmaster = selmon->pertag->nmasters[selmon->pertag->curtag];
  selmon->mfact = selmon->pertag->mfacts[selmon->pertag->curtag];
  selmon->sellt = selmon->pertag->sellts[selmon->pertag->curtag];
  selmon->lt[selmon->sellt] =
      selmon->pertag->ltidxs[selmon->pertag->curtag][selmon->sellt];
  selmon->lt[selmon->sellt ^ 1] =
      selmon->pertag->ltidxs[selmon->pertag->curtag][selmon->sellt ^ 1];

  selmon->gappoh = (selmon->pertag->gaps[selmon->pertag->curtag] & 0xff) >> 0;
  selmon->gappov = (selmon->pertag->gaps[selmon->pertag->curtag] & 0xff00) >> 8;
  selmon->gappih =
      (selmon->pertag->gaps[selmon->pertag->curtag] & 0xff0000) >> 16;
  selmon->gappiv =
      (selmon->pertag->gaps[selmon->pertag->curtag] & 0xff000000) >> 24;

  if (selmon->showbar != selmon->pertag->showbars[selmon->pertag->curtag])
    togglebar(NULL);

  focus(NULL);
  arrange(selmon);
}

pid_t winpid(Window w) {

  pid_t result = 0;

#ifdef __linux__
  xcb_res_client_id_spec_t spec = {0};
  spec.client = w;
  spec.mask = XCB_RES_CLIENT_ID_MASK_LOCAL_CLIENT_PID;

  xcb_generic_error_t *e = NULL;
  xcb_res_query_client_ids_cookie_t c =
      xcb_res_query_client_ids(xcon, 1, &spec);
  xcb_res_query_client_ids_reply_t *r =
      xcb_res_query_client_ids_reply(xcon, c, &e);

  if (!r)
    return (pid_t)0;

  xcb_res_client_id_value_iterator_t i =
      xcb_res_query_client_ids_ids_iterator(r);
  for (; i.rem; xcb_res_client_id_value_next(&i)) {
    spec = i.data->spec;
    if (spec.mask & XCB_RES_CLIENT_ID_MASK_LOCAL_CLIENT_PID) {
      uint32_t *t = xcb_res_client_id_value_value(i.data);
      result = *t;
      break;
    }
  }

  free(r);

  if (result == (pid_t)-1)
    result = 0;

#endif /* __linux__ */

#ifdef __OpenBSD__
  Atom type;
  int format;
  unsigned long len, bytes;
  unsigned char *prop;
  pid_t ret;

  if (XGetWindowProperty(dpy, w, XInternAtom(dpy, "_NET_WM_PID", 0), 0, 1,
                         False, AnyPropertyType, &type, &format, &len, &bytes,
                         &prop) != Success ||
      !prop)
    return 0;

  ret = *(pid_t *)prop;
  XFree(prop);
  result = ret;

#endif /* __OpenBSD__ */
  return result;
}

pid_t getparentprocess(pid_t p) {
  unsigned int v = 0;

#ifdef __linux__
  FILE *f;
  char buf[256];
  snprintf(buf, sizeof(buf) - 1, "/proc/%u/stat", (unsigned)p);

  if (!(f = fopen(buf, "r")))
    return 0;

  fscanf(f, "%*u %*s %*c %u", &v);
  fclose(f);
#endif /* __linux__*/

#ifdef __OpenBSD__
  int n;
  kvm_t *kd;
  struct kinfo_proc *kp;

  kd = kvm_openfiles(NULL, NULL, NULL, KVM_NO_FILES, NULL);
  if (!kd)
    return 0;

  kp = kvm_getprocs(kd, KERN_PROC_PID, p, sizeof(*kp), &n);
  v = kp->p_ppid;
#endif /* __OpenBSD__ */

  return (pid_t)v;
}

int isdescprocess(pid_t p, pid_t c) {
  while (p != c && c != 0)
    c = getparentprocess(c);

  return (int)c;
}

Client *termforwin(const Client *w) {
  Client *c;
  Monitor *m;

  if (!w->pid || w->isterminal)
    return NULL;

  for (m = mons; m; m = m->next) {
    for (c = m->clients; c; c = c->next) {
      if (c->isterminal && !c->swallowing && c->pid &&
          isdescprocess(c->pid, w->pid))
        return c;
    }
  }

  return NULL;
}

Client *swallowingclient(Window w) {
  Client *c;
  Monitor *m;

  for (m = mons; m; m = m->next) {
    for (c = m->clients; c; c = c->next) {
      if (c->swallowing && c->swallowing->win == w)
        return c;
    }
  }

  return NULL;
}

Client *wintoclient(Window w) {
  Client *c;
  Monitor *m;

  for (m = mons; m; m = m->next)
    for (c = m->clients; c; c = c->next)
      if (c->win == w)
        return c;
  return NULL;
}

Client *wintosystrayicon(Window w) {
  Client *i = NULL;

  if (!showsystray || !w)
    return i;
  for (i = systray->icons; i && i->win != w; i = i->next)
    ;
  return i;
}

Monitor *wintomon(Window w) {
  int x, y;
  Client *c;
  Monitor *m;

  if (w == root && getrootptr(&x, &y))
    return recttomon(x, y, 1, 1);
  for (m = mons; m; m = m->next)
    if (w == m->barwin)
      return m;
  if ((c = wintoclient(w)) || (c = cropwintoclient(w)))
    return c->mon;
  return selmon;
}

/* Selects for the view of the focused window. The list of tags */
/* to be displayed is matched to the focused window tag list. */
void winview(const Arg *arg) {
  Window win, win_r, win_p, *win_c;
  unsigned nc;
  int unused;
  Client *c;
  Arg a;

  if (!XGetInputFocus(dpy, &win, &unused))
    return;
  while (XQueryTree(dpy, win, &win_r, &win_p, &win_c, &nc) && win_p != win_r)
    win = win_p;

  if (!(c = wintoclient(win))) {
    a.ui = 0;
    view(&a);
    return;
  }

  a.ui = c->tags;
  view(&a);
}

/* There's no way to check accesses to destroyed windows, thus those cases are
 * ignored (especially on UnmapNotify's). Other types of errors call Xlibs
 * default error handler, which may call exit. */
int xerror(Display *dpy, XErrorEvent *ee) {
  if (ee->error_code == BadWindow ||
      (ee->request_code == X_SetInputFocus && ee->error_code == BadMatch) ||
      (ee->request_code == X_PolyText8 && ee->error_code == BadDrawable) ||
      (ee->request_code == X_PolyFillRectangle &&
       ee->error_code == BadDrawable) ||
      (ee->request_code == X_PolySegment && ee->error_code == BadDrawable) ||
      (ee->request_code == X_ConfigureWindow && ee->error_code == BadMatch) ||
      (ee->request_code == X_GrabButton && ee->error_code == BadAccess) ||
      (ee->request_code == X_GrabKey && ee->error_code == BadAccess) ||
      (ee->request_code == X_CopyArea && ee->error_code == BadDrawable))
    return 0;
  fprintf(stderr, "dwm: fatal error: request code=%d, error code=%d\n",
          ee->request_code, ee->error_code);
  return xerrorxlib(dpy, ee); /* may call exit */
}

int xerrordummy(Display *dpy, XErrorEvent *ee) { return 0; }

/* Startup Error handler to check if another window manager
 * is already running. */
int xerrorstart(Display *dpy, XErrorEvent *ee) {
  die("dwm: another window manager is already running");
  return -1;
}

void xinitvisual() {
  XVisualInfo *infos;
  XRenderPictFormat *fmt;
  int nitems;
  int i;

  XVisualInfo tpl = {.screen = screen, .depth = 32, .class = TrueColor};
  long masks = VisualScreenMask | VisualDepthMask | VisualClassMask;

  infos = XGetVisualInfo(dpy, masks, &tpl, &nitems);
  visual = NULL;
  for (i = 0; i < nitems; i++) {
    fmt = XRenderFindVisualFormat(dpy, infos[i].visual);
    if (fmt->type == PictTypeDirect && fmt->direct.alphaMask) {
      visual = infos[i].visual;
      depth = infos[i].depth;
      cmap = XCreateColormap(dpy, root, visual, AllocNone);
      useargb = 1;
      break;
    }
  }

  XFree(infos);

  if (!visual) {
    visual = DefaultVisual(dpy, screen);
    depth = DefaultDepth(dpy, screen);
    cmap = DefaultColormap(dpy, screen);
  }
}

void zoom(const Arg *arg) {
  Client *c = selmon->sel;
  Client *at = NULL, *cold, *cprevious = NULL;

  if (!selmon->lt[selmon->sellt]->arrange || !c || c->isfloating)
    return;
  if (c == nexttiled(selmon->clients)) {
    at = findbefore(prevzoom);
    if (at)
      cprevious = nexttiled(at->next);
    if (!cprevious || cprevious != prevzoom) {
      prevzoom = NULL;
      if (!c || !(c = nexttiled(c->next)))
        return;
    } else
      c = cprevious;
  }
  cold = nexttiled(selmon->clients);
  if (c != cold && !at)
    at = findbefore(c);
  detach(c);
  attach(c);
  /* swap windows instead of pushing the previous one down */
  if (c != cold && at) {
    prevzoom = cold;
    if (cold && at != cold) {
      detach(cold);
      cold->next = at->next;
      at->next = cold;
    }
  }
  focus(c);
  arrange(c->mon);
}

void swaptags(const Arg *arg) {
  unsigned int newtag = arg->ui & TAGMASK;
  unsigned int curtag = selmon->tagset[selmon->seltags];

  if (newtag == curtag || !curtag || (curtag & (curtag - 1)))
    return;

  for (Client *c = selmon->clients; c != NULL; c = c->next) {
    if ((c->tags & newtag) || (c->tags & curtag))
      c->tags ^= curtag ^ newtag;

    if (!c->tags)
      c->tags = newtag;
  }

  selmon->tagset[selmon->seltags] = newtag;

  focus(NULL);
  arrange(selmon);
}

void resource_load(XrmDatabase db, char *name, enum resource_type rtype,
                   void *dst) {
  char *sdst = NULL;
  int *idst = NULL;
  float *fdst = NULL;

  sdst = dst;
  idst = dst;
  fdst = dst;

  char fullname[256];
  char *type;
  XrmValue ret;

  snprintf(fullname, sizeof(fullname), "%s.%s", "dwm", name);
  fullname[sizeof(fullname) - 1] = '\0';

  XrmGetResource(db, fullname, "*", &type, &ret);
  if (!(ret.addr == NULL || strncmp("String", type, 64))) {
    switch (rtype) {
    case STRING:
      strcpy(sdst, ret.addr);
      break;
    case INTEGER:
      *idst = strtoul(ret.addr, NULL, 10);
      break;
    case FLOAT:
      *fdst = strtof(ret.addr, NULL);
      break;
    }
  }
}

void load_xresources(void) {
  Display *display;
  char *resm;
  XrmDatabase db;
  ResourcePref *p;

  display = XOpenDisplay(NULL);
  resm = XResourceManagerString(display);
  if (!resm)
    return;

  db = XrmGetStringDatabase(resm);
  for (p = resources; p < resources + LENGTH(resources); p++)
    resource_load(db, p->name, p->type, p->dst);
  XCloseDisplay(display);
}

int main(int argc, char *argv[]) {
  if (argc == 2 && !strcmp("-v", argv[1]))
    die("dwm-" VERSION);
  else if (argc != 1)
    die("usage: dwm [-v]");
  if (!setlocale(LC_CTYPE, "") || !XSupportsLocale())
    fputs("warning: no locale support\n", stderr);
  if (!(dpy = XOpenDisplay(NULL)))
    die("dwm: cannot open display");
  if (!(xcon = XGetXCBConnection(dpy)))
    die("dwm: cannot get xcb connection\n");
  checkotherwm();
  XrmInitialize();
  load_xresources();
  setup();
#ifdef __OpenBSD__
  if (pledge("stdio rpath proc exec ps", NULL) == -1)
    die("pledge");
#endif /* __OpenBSD__ */
  scan();
  runautostart();
  run();
  if (restart)
    execvp(argv[0], argv);
  cleanup();
  XCloseDisplay(dpy);
  return EXIT_SUCCESS;
}
