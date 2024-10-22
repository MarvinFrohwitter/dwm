/* custom functions declarations */
// static void movetotag2forrule(const Arg *arg);
// static void movetotag3forrule(const Arg *arg);
// static void movetotag4forrule(const Arg *arg);
// static void movetotag5forrule(const Arg *arg);
// static void movetotag6forrule(const Arg *arg);
// static void movetotag7forrule(const Arg *arg);
// static void movetotag8forrule(const Arg *arg);
// static void movetotag9forrule(const Arg *arg);

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
static void toggleactualfullscr(const Arg *arg);
static void reloadafterquit(const Arg *arg);
static void reloadafterquitwithsig(const Arg *arg);
static void pskiller(pid_t pid);

void pskiller(pid_t pid) {
  char *s_pid;
  int err = sprintf(s_pid, "kill -9 %d\n", pid);
  if (err < 0) {
    return;
  }
  system(s_pid);
}

void reloadafterquit(const Arg *arg) {
  spawn(arg);
  Arg a;
  a.i = 0;
  quit(&a);
}

void reloadafterquitwithsig(const Arg *arg) {
  spawn(arg);
  Arg a;
  a.i = 1;
  quit(&a);
}
void toggleactualfullscr(const Arg *arg) {
  Client *c;
  if (isfakefullscreen) {
    isfakefullscreen = False;
    togglefullscr(0);
  } else {
    isfakefullscreen = True;
  }
  for (c = selmon->clients; c; c = c->next)
    resizeclient(c, selmon->mx, selmon->my, selmon->mw, selmon->mh);
  arrange(selmon);
}

// void movetotag2forrule(const Arg *arg) {
//   Arg a2;
//   a2.ui = 1 << 1;
//   spawn(arg);
//   view(&a2);
// }

// void movetotag3forrule(const Arg *arg) {
//   Arg a3;
//   a3.ui = 1 << 2;
//   spawn(arg);
//   view(&a3);
// }

// void movetotag4forrule(const Arg *arg) {
//   Arg a4;
//   a4.ui = 1 << 3;
//   spawn(arg);
//   view(&a4);
// }

// void movetotag5forrule(const Arg *arg) {
//   Arg a5;
//   a5.ui = 1 << 4;
//   spawn(arg);
//   view(&a5);
// }

// void movetotag6forrule(const Arg *arg) {
//   Arg a6;
//   a6.ui = 1 << 5;
//   spawn(arg);
//   view(&a6);
// }

// void movetotag7forrule(const Arg *arg) {
//   Arg a7;
//   a7.ui = 1 << 6;
//   spawn(arg);
//   view(&a7);
// }

// void movetotag8forrule(const Arg *arg) {
//   Arg a8;
//   a8.ui = 1 << 7;
//   spawn(arg);
//   view(&a8);
// }

// void movetotag9forrule(const Arg *arg) {
//   Arg a9;
//   a9.ui = 1 << 8;
//   spawn(arg);
//   view(&a9);
// }
