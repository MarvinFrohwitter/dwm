/* custom functions declarations */
// static void movetotag2forrule(const Arg *arg);
// static void movetotag3forrule(const Arg *arg);
// static void movetotag4forrule(const Arg *arg);
// static void movetotag5forrule(const Arg *arg);
// static void movetotag6forrule(const Arg *arg);
// static void movetotag7forrule(const Arg *arg);
// static void movetotag8forrule(const Arg *arg);
// static void movetotag9forrule(const Arg *arg);
static void reloadafterquit(const Arg *arg);

void reloadafterquit(const Arg *arg) {
  spawn(arg);
  quit(0);
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
