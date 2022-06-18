* [33m6b8c401[m[33m ([m[1;36mHEAD -> [m[1;32mpatches[m[33m)[m dwm-autostart-20210120-cb3f58a.diff
* [33mc893bc3[m dwm-fullscreen-6.2.diff
* [33m5c7c53f[m dwm-warp-6.2.diff
* [33ma7981fb[m dwm-bar-height-6.2.diff
* [33m4f1a9f0[m dwm-attachbottom-20201227-61bb8b2.diff
* [33m2b5fe11[m dwm-alwayscenter-20200625-f04cac6.diff
* [33mdfc9f5c[m dwm-movestack-20211115-a786211.diff
* [33m738d5b8[m dwm-fullgaps-toggle-20200830.diff
* [33mb463fb1[m dwm-pertag-perseltag-6.2.diff
* [33m38f03b3[m dwm-alpha-20201019-61bb8b2.diff
* [33mbece862[m[33m ([m[1;31morigin/master[m[33m, [m[1;31morigin/HEAD[m[33m, [m[1;32mmaster[m[33m)[m manage: For isfloating/oldstate check/set, ensure trans client actually exists
* [33m60e9a14[m fix mem leak in cleanup()
* [33md39e2f3[m[33m ([m[1;33mtag: 6.3[m[33m)[m bump version to 6.3
* [33m8657aff[m drawbar: Don't expend effort drawing bar if it is occluded
* [33ma786211[m Revert "Improve speed of drw_text when provided with large strings"
* [33m7162335[m Improve speed of drw_text when provided with large strings
* [33m138b405[m Add a configuration option for fullscreen locking
* [33m67d76bd[m Do not allow focus to drift from fullscreen client via focusstack()
* [33m61bb8b2[m Fix x coordinate calculation in buttonpress.
* [33mbb2e722[m dwm.1: fix wrong text in man page
* [33mf04cac6[m Fix memory leaks in drw
* [33mf09418b[m dwm crashes when opening 50+ clients (tile layout)
* [33med3ab6b[m drawbar: Don't shadow sw global
* [33mf087d20[m getatomprop: Add forward declaration
* [33ma8e9513[m setmfact: Unify bounds for compile-time and runtime mfact
* [33mc82db69[m config.mk: fix POSIX_C_SOURCE macro for feature test for snprintf()
* [33mcb3f58a[m[33m ([m[1;33mtag: 6.2[m[33m)[m Prepare 6.2 release.
* [33mb69c870[m pledge: add rpath promise for the ugly Xft font fallback
* [33me78b4a9[m Makefile: just show the compiler output
* [33m3cd4023[m Do not strip at link stage
* [33mf40f86f[m Pledge on OpenBSD
* [33mc3a2e01[m config.def.h: ClkTagBar missing from comment
* [33mc8e9479[m Function declarations in correct order.
* [33m10dfa65[m remove old TODO and BUGS entries
* [33m3bd8466[m update README: remove mentioning the old dextra repo
* [33m76c8c16[m All functions in alphabetical order except for this one.
* [33m3cb3483[m ColBorder has been moved to the enum with ColFg and ColBg.
* [33mdb22360[m dont NUL terminate _NET_WM_NAME
* [33m3756f7f[m sync dmenu drw.{c,h} code: use Clr* (was Scm)
* [33m99f78fa[m gettextprop: check result of XGetTextProperty (undefined behaviour for XFree)
* [33ma9b6a31[m Set class name on status bar
* [33m6aa8e37[m simplify isfixed conditions
* [33mceac8c9[m yet another cleanup
* [33m5b238c8[m Don't restrict snap in mousemove
* [33m022d076[m Button passthrough when client is not focused
* [33m2952b68[m cleanup
* [33mbb3bd6f[m applied Markus' tagset purge of alternative view on _NET_ACTIVE_WINDOW event
* [33me63bf22[m applied Ivan Delalande's NET_SUPPORTING_WM_CHECK patch for gtk3 compatibility
* [33m5376947[m applied Ian Remmler's man page adjustment suggestions
* [33m975c898[m applied Markus' decouple color-scheme patch
* [33ma137a86[m applied Markus' clarify status text padding patch
* [33m839c7f6[m LICENSE: update people
* [33m7a59cd1[m dwm.1: add keybinding for spawning dmenu
* [33m24849ac[m die() on calloc failure
* [33mab9571b[m die() consistency: always add newline
* [33m56a31dc[m config.def.h: style improvement, use color Scheme enum
* [33m7af4d43[m import new drw from libsl and minor fixes.
* [33mcd2d754[m Configure geometry before applying rules
* [33m3465bed[m fix fullscreen clients not resized on X display resolution change
* [33m4ec3a67[m Shut up glibc about _BSD_SOURCE being deprecated
* [33m5ed9c48[m[33m ([m[1;33mtag: 6.1[m[33m)[m code-style consistency
* [33m3c91283[m unboolification
* [33me941181[m sort include + whitespace fix
* [33m43e82ad[m separate program-specific c99 bool and X11
* [33m42cf1c7[m Makefile: package all files with make dist
* [33mdce4fb3[m setfullscreen: don't process the property twice
* [33m646b351[m sync updated drw code from dmenu
* [33me3b7e1d[m dwm: use ecalloc, prevent theoretical overflow
* [33m04db03a[m cleanup, dont use c++ style comments
* [33m4a4817b[m dwm: cleanup: free schemes and cursors as array
* [33m7e1182c[m config.h: use common default font, pass Xft font name to dmenu
* [33m40529e1[m config.mk: add $FREETYPELIBS and $FREETYPEINC, simpler to override (ports and *BSDs)
* [33m14343e6[m Add Xft and follback-fonts support to graphics lib
* [33m35db6d8[m removed .hgtags, thanks Dimitris for spotting
* [33m3d1090b[m applied Hiltjo's resize/move limitation
* [33m18248eb[m same as before with dwm.c as well
* [33mb468873[m updated copyright notice in LICENSE file
* [33mcdec978[m applied Lukas' focus suggestion at startup, thanks
* [33m6af2737[m applied improved version of Martti Kühne's dmenu/multi monitor approach from dwm, no dmenuspawn required
* [33m4fb31e0[m do not take our font declaration as default for st
* [33mb800a1d[m applied Jochen's drw_text patch, thanks
* [33m33a7448[m applied Julian's enum approach, 	however renamed theme into scheme resp. Theme into ClrScheme
* [33m5364697[m finished libsl/drw integration
* [33m7edc596[m include font argument for st by default
* [33m68b400e[m added st to SEE ALSO section
* [33m656882d[m use st as default terminal from now on
* [33m1479e76[m shut up about deprecated Xlib functions
* [33mf2544a3[m renamed draw into drw
* [33maafeaf7[m continued with draw.c and draw.h implementation, now the integration begins
* [33mf21d46e[m continued with draw.c abstraction, also started util.{h,c} implementation, that will be used by draw.c as well
* [33mc0ba635[m removed DDC, all is Draw-dependent
* [33m0a673ad[m continued, distinction of Draw and DDC is bad, needs to be merged
* [33m3aabc08[m reverting the xkb dependency, I don't care if this function is deprecated, it seems it breaks other stuff instead.
* [33md456617[m basic draw.c structure
* [33m61fe833[m reverting to plain X11 fonts in order to implement draw.c default
* [33m917e281[m removed obsolete bugs from BUGS file
* [33m31451c3[m compile fix
* [33m344f35f[m applied Neil Klopfstein's patch, slightly modified
* [33m87adcd2[m starting with initial draw.h
* [33mfd3c19b[m incorporating Xft instead of cairo, cairo provides far too many options
* [33m1bdb393[m keep 6.1 intact
* [33m940feed[m reverted to old updategeom() after several complains, we need to optimize the old way
* [33m606b441[m applied James Turner's XkbKeycodeToKeysym patch, thanks
* [33m20f6917[m drastically changed updategeom() handling, see comment in updategeom() for details
* [33m820cbb3[m reversed Andreas Amann's fullscreen fix with the approach proposed by Gary Langshaw: - idea is not supporting movemouse/resizemouse/togglefloating for fullscreen windows - as fullscreen windows are broken anyways, they should only be adjusted by their own means
* [33m90f3238[m added kludge to fix some input focus misbehavior in gedit and anjuta, thanks Martti Kühne
* [33m3bfc43c[m applied Andreas Amanns' netwm_client_list patch, but with some indentation fixes
* [33mc112841[m applied Andreas Amann's netwm_active_window patch, thx
* [33m1b62f8f[m applied Andreas Amann fullscreen fix, some minor modifications
* [33m54c3044[m unfocus on slow sloppy monitor focus
* [33m51336aa[m applied Eckehard Berns fix fix, sorry that this took so long
* [33mc4b6ac8[m added 20h's clarification
* [33m873bcb9[m applied Eckehard Berns barwin leak fix and his suggestion to deal with restack() -- the latter aspect needs further investigation.
* [33m907db0a[m config.mk cleanup
* [33m4e7c469[m Added tag 6.0 for changeset ec4baab78314
* [33m26445a0[m[33m ([m[1;33mtag: 6.0[m[33m)[m bump version to 6.0
* [33mb5068e3[m add sloppy monitor focus
* [33mf099d2d[m new default colour scheme
* [33m80a9da5[m calculate window/monitor intersection
* [33md21026f[m honour fullscreen hint on map
* [33me5a1e77[m testing Brians multiscreen issue fix
* [33m8262d9e[m make ewmh dialog windows float
* [33m90af1ce[m allow 0 nmaster
* [33m5ccd42f[m fix big-border corner case
* [33m1586b7a[m added keyrelease remark to TODO
* [33m2420071[m improve tile spacing
* [33m04c2657[m add nmaster binds to manpage
* [33mb1a28ae[m apply nmaster patch
* [33mf68a01c[m apply resize hints in floating layout
* [33m2b625eb[m hide clients to the left, not the right
* [33m0f1f30d[m applied Connors cleanup patch of Eckehards proposed fix of applyrules(), thanks everyone involved
* [33mdec4850[m applied Connors and Valentins patch to improve the unmapnotify handling of broken clients
* [33m0de4197[m applied Peter Hartlichs nice interim Xinerama and map fix patches, for debugging purposes I also added his transient test driver
* [33ma372248[m applied anonymous code cleanup patch
* [33m69e7d7d[m added a marker for the flash fullscreen issue
* [33mc99fe7d[m changed sleep 20 into sleep 1 in example script as suggested by Snader_LB
* [33md6670a8[m applied Connors aesthitic buf fix in tile(), thanks
* [33m6288c44[m applied Peters magic float mode bugfix
* [33md5c5c52[m applied lolilolicon's floating center patch, further investigation wrt his second issue reported needed
* [33md0b4575[m thanks to recursions on IRC for his remark
* [33m03518ce[m Added tag 5.9 for changeset dd74622a4785
* [33mcd8bb06[m[33m ([m[1;33mtag: 5.9[m[33m)[m enabled release flags
* [33m3150a8a[m applied Peters wintoclient/wintomon optimisation in enternotify()
* [33mb3c5f54[m removed unneeded offset recalculation, thanks Jukka, let's see if this breaks some other client
* [33ma692bdc[m undo the focus optimisation patch for 5.9
* [33md83454f[m applied Peters two patches, please test hg tip, if nothing breaks this is 5.9
* [33m27b0142[m applied Garys patch in a slightly modified way
* [33m867ba36[m applied Nicolas Capit's patch as interim solution until the multiscreen support is reworked in 6.0
* [33me83f36d[m fixed scroll lock (thanks bogdan)
* [33m212f417[m fix numlock (thanks mikhail)
* [33m3a392b8[m making enternotify less focus hungry
* [33m92fe06b[m applied Andreas Amann's patch from Oct 2010, thanks
* [33m6cf29bf[m applied Rudys barwidth patch, thanks Rudy
* [33m60c06a7[m don't check for monocle layout in zoom() exit condition
* [33m1147546[m Thanks for the pedantic review :)
* [33md384cee[m fixing some minor issues, next week is dwm-5.9 release time
* [33m5c710cf[m rm draw.c from 5.9 branch
* [33m8a111c1[m fix typo
* [33m2255bf4[m cleaner drawing
* [33m0479734[m update draw.c
* [33me7d41cc[m added draw.h, draw.c
* [33m22d8818[m applied Evil_Bobs cleanup patch
* [33m6784429[m applied another minor change to the README
* [33m37fea84[m applied Thomas' README patch
* [33mc14d293[m applied Jack's mplayer fullscreen patch
* [33m79b1657[m missed declaration
* [33md24837f[m minor fix of the NetActiveWindow multi-monitor flaw, slight rearrangement
* [33m3c2d303[m applied Peter/Andreas NetActiveWindow patch in a slightly modified version
* [33m1e20a0f[m applied Brendan MacDonell's WM_TAKE_FOCUS patch, thanks Brendan!
* [33m96f9855[m applied another patch of Hiltjo, thanks
* [33m3c48858[m applied Hiltjos' BUGS patch from 23 Mar, sorry took a while :)
* [33mdd46d5b[m applied Hiltjo's multimon mouse-based resize fix
* [33m0bc4e41[m applied anonymous patch, I don't think the reversed array access has semantic side-effects
* [33m703c4dd[m added a todo
* [33mb68528d[m applied Hiltjo's cleanup patch
* [33ma644baf[m applied Hiltjo's tiny cleanup fix
* [33mc1f8688[m applied Hiltjo's tiny cleanup patch, thanks!
* [33mbea4dd2[m does this make a difference?
* [33m83d10be[m added TODO and bumped version to 5.9
* [33m1529058[m applied Hiltjo Posthuma's line saver patch
* [33m36311d8[m applied Hiltjo Posthuma's double-XineramaQueryScreens() patch, thanks Hiltjo!
* [33mf1a2a3c[m Added tag 5.8.2 for changeset a043f0800805
* [33mee734fa[m[33m ([m[1;33mtag: 5.8.2[m[33m)[m increased version
* [33m62d3caa[m implemented better fullscreen handling, please test
* [33m4c9b397[m Added tag 5.8.1 for changeset 1ed1e75c9c2e
* [33m5c6545a[m[33m ([m[1;33mtag: 5.8.1[m[33m)[m removing Sylvain's patch because it breaks more than it fixes unfortunately, re-issuing a bugfix release 5.8.1
* [33ma704b1e[m Added tag 5.8 for changeset 60ea8fed13ab
* [33mf83d61d[m[33m ([m[1;33mtag: 5.8[m[33m)[m removed DEBUG code and added 2010 to the copyright list
* [33mc618094[m applied Sylvain Laurent's EWMH fullscreen state patch, simplified his patch a bit
* [33m1973ab0[m added the related bug reported by voltaic
* [33m427053f[m pretty printing bugs a bit
* [33ma88e037[m selmon optimisation is needed
* [33maa9f2be[m more debug output, experimental focus optimisation
* [33mc53b29e[m quick typo fix
* [33md6bdd03[m it's debug season for upcoming dwm 5.8, so only use this if you really want to run experimental code or debug code
* [33m1144e98[m another bug report
* [33m7671d03[m removed misleading comment, thanks Romain Bertrand
* [33mbc554d4[m added nsz's last bug corner case
* [33mac4caea[m added BUGS, next version is 5.8
* [33m161f2d9[m Added tag 5.7.2 for changeset 15761ac5e2f1
* [33m210378f[m[33m ([m[1;33mtag: 5.7.2[m[33m)[m applied Ryan Zheng's patch and re-releasing 5.7.2
* [33m7879616[m Added tag 5.7.1 for changeset 48c3f87c335d
* [33m9e8dd34[m[33m ([m[1;33mtag: 5.7.1[m[33m)[m fixed the layout symbol bug reported by Nibble (but using a different approach as he suggested) - optimised drawbar() and arrange() handling for multiple monitors, arrange only arranges the relevant monitors when applicable, same with drawbar - need to release 5.7.1
* [33m0b72be9[m Added tag 5.7 for changeset 257403d4cd96
* [33m91e902f[m[33m ([m[1;33mtag: 5.7[m[33m)[m switching to release flags
* [33m30fed9a[m implemented nn < n case, k-zed please recheck
* [33mc45d46a[m use buffer instead of pointer for mon->ltsymbol
* [33m6f55de8[m added missing scan
* [33m07ad298[m implemented different version of updategeom
* [33mf0a4845[m added TODO to updategeom in order to implement a decent version of it soon
* [33m82ec7a7[m new experimental updategeom() additions that should avoid several problems with Xinerama, this is EXPERIMENTAL and might break something, the algorithms in use are quite complex and cumbersome, patches and comments welcome
* [33me7300e0[m implemented dynamic layout symbol stuff
* [33mc3feffa[m applied Tony Lainson's config.def.h patch
* [33m956a430[m update
* [33m01056b6[m hard-core destruction
* [33meb260b1[m renaming isdestroyed into destroyed
* [33m7fe8135[m sync when a client is being killed
* [33ma3a859b[m added isdestroyed flag to unmanage
* [33m9c066c2[m always updategeom when root is configured
* [33m0a66892[m another small optimisation
* [33m5762964[m also update title if the client is on an unfocused monitor
* [33mcba6b21[m applied nsz's dwm.1 patch, also added wmname
* [33m42750a6[m applied Jukka's cosmetic patch
* [33m8ef465d[m applied Jukka's sigchld patch
* [33m33fe200[m added merged patch of anydot and Neale
* [33m91fffb3[m fixed nn declaration
* [33m1fa31ef[m Added tag 5.6.1 for changeset e47a47bd3ed4
* [33m244addb[m[33m ([m[1;33mtag: 5.6.1[m[33m)[m applied nsz patch
* [33mc13be8d[m updategeom fix for same geom screens
* [33mdc39ae8[m applied nsz' man page comment, thanks!
*   [33m966d76a[m merge
[32m|[m[33m\[m  
[32m|[m *   [33mdfecd46[m merge
[32m|[m [34m|[m[35m\[m  
[32m|[m * [35m|[m [33m5bc4db0[m applied nsz' dwm.1 fixes, thanks Szabolcs!
* [35m|[m [35m|[m [33m7151bf8[m removed Standard input hint
[35m|[m [35m|[m[35m/[m  
[35m|[m[35m/[m[35m|[m   
* [35m|[m [33m999d6e7[m removed misleading comment
* [35m|[m [33m6360752[m merge
[36m|[m[35m\[m[35m|[m 
[36m|[m * [33m0927d63[m Added tag 5.6 for changeset 555070221577
* [1;31m|[m [33m6877a00[m it's all nsz's hard investigation effort, hail nsz! ;)
[1;31m|[m[1;31m/[m  
* [33m450b08d[m[33m ([m[1;33mtag: 5.6[m[33m)[m final style fixes
* [33mda80487[m removed int cast in TAGMASK as suggested by nsz
* [33md9779c0[m some stylistic changes
* [33m20996c6[m removed obsolete BUG
* [33m8dc9fcf[m mark broken clients as broken
* [33mfc21dd4[m fixing updatetitle
* [33m758b100[m extended rule to apply monitors if set up accordingly
* [33m8420fb1[m reverting to optimised compiler options, current state seems stable
* [33mf6128a1[m extended man page to mention number of visible windows
* [33m87526be[m added client number printing right of layout symbol
* [33m565050a[m removed monsyms, useless
* [33m5e408d8[m restricting number of mons by length of monsyms
* [33m1724f7f[m introducing const where it might make some sense
* [33m3e6fe6b[m no that's definately better
* [33m6620615[m some minor changes
* [33m61c3095[m die if malloc sizeof(Monitor) fails
* [33ma72dc2f[m applied Mate's patch, added Mate to LICENSE
* [33m8b17f55[m some cleanups
* [33mcd96232[m hotfix
* [33ma9e145f[m changed focusmon/tagmon to work on prev/next instead (-1/+1), changed shortcuts to Mod1-, Mod1-. and Mod1-Shift-, Mod1-Shift-.
* [33m5dd92c7[m removed some empty lines
* [33m52bd69c[m interactive resizals allow display dimensions again
* [33mca37697[m more sensible
* [33m8352f2b[m hmm, can't decide on the default monitor symbol set
* [33md4bfde7[m update
* [33m7ac8c1d[m introduced monitor symbols
* [33m16e1ef5[m minor fix
* [33m1d72938[m several bugfixes
* [33m25c1eb2[m some minor fix if xinerama is disabled, still some odd behavior in there
* [33md719cc9[m updated year ranges
* [33m9cde657[m fixed usage of sx, sy, sw, sh
* [33me408ca9[m don't draw monitor number, if there is just one monitor
* [33m183dc67[m fixed order of transient monitor applicaion and rule application
* [33m25947bc[m hotfix
* [33m1ddfc57[m several simplifications
* [33m21cd59a[m play safe
* [33m6cbe47d[m applied a collection of Christof Musik patches, and fixed an issue reported by waistcoats on IRC
* [33m029655b[m some cleanup handling for index based mon search
* [33m27db9d4[m using mon in function names for consistency reasons
* [33m176408a[m fixed several issues with focus handling via mouse, also added sending clients to the right monitor they belong to after mouse moves/resizals
* [33m64674c3[m fixed focusmon brokeness
* [33mb9dee2c[m tag fix
* [33ma73ff90[m typo fix
* [33me3f0445[m assign selected tags of target monitor to client when tagmon is performed (less obtrusive imho)
* [33mab06f74[m added some TODOs, some other focus fixes
* [33ma2a3590[m disabled XINULATOR code for now
* [33me8aafb8[m made bar based monitor switching working
* [33m18b1312[m several other focus fixes, introduced unfocus()
* [33m80ee954[m some focus fixes
* [33m454a04a[m fixed title rendering on non-active screen
* [33m891831f[m fixed getclient brokeness
* [33mcdb8e27[m some hotfix cleanup related to wild selmon-> destruction
* [33m5c4913e[m some restack fixes, still odd behavior if n>1 on unmanaging clients
* [33mfa5ae54[m added some dual head simulator code
* [33m7de5341[m simplified left over re-assignment
* [33m54dc0d5[m fixed tagmon, re-using detach/detachstack and attach/attachstack
* [33m913333f[m simplified ISVISBLE and nexttiled
* [33md702f39[m moved clients/stack/sel to Monitor, that's a per monitor structure from now on
* [33m0d8671a[m declare buf only if XINERAMA support is used
* [33m38e9b67[m if compiled without XINERAMA support assume 1 monitor by default (n = 1)
* [33ma3bbdb1[m some more refactoring, bar toggle fixes
* [33md53ceee[m hotfixes
* [33m78f5667[m changes monitor structure to be a list
* [33mc2fff60[m we need a tagset per monitor, removed tagset declaration from config.h
* [33m6644a6a[m some minor fixes regarding the new xinerama support
* [33m3da2453[m several fixes through ISVISIBLE change (takes Monitor into account)
* [33m2ce37bc[m experimental xinerama support, two new actions, Mod1-w/e and Mod1-Shift-w/e
* [33mf27ccc5[m introduction of Monitor for better Xinerama support, work in progress
* [33m2dbfda7[m removed MAXTAGLEN
* [33m7df39f3[m next version will be 5.6, shortened some very long lines
* [33m0b45199[m Added tag 5.5 for changeset deaa276abac1
* [33m3632d71[m[33m ([m[1;33mtag: 5.5[m[33m)[m applied Marc Andre Tanners showhide patch, the removal of ntiled
* [33m5656970[m applied Gottox' patches, and also removed usegrab
* [33mea0008c[m applied the patch I missed from Gottox, thanks mate!
* [33maf508c2[m applied Gottox' resizehints patch, thanks Gottox!
* [33mf0d1d52[m some NULL fixes
* [33m1c80c05[m override_redirect is Bool
* [33m1e350be[m applied Gottox' adjustborder removal patch (thanks!)
* [33m1a26389[m applied nsz' remark
* [33mbf9da23[m fix of typo, thx to Enno Gottox Boland
* [33m2373940[m Added tag 5.4.1 for changeset 85a78d8afa0f
* [33m9068748[m[33m ([m[1;33mtag: 5.4.1[m[33m)[m fixed an issue reported by Nibble, also fixed s/2008/2009/
* [33m5ab627c[m Added tag 5.4 for changeset 8b7836a471f8
* [33m76d7e80[m[33m ([m[1;33mtag: 5.4[m[33m)[m avoid reverting the border if it's not necessary (avoids some flashing on view())
* [33maf8049b[m spotted missing spaces
* [33m2bb51b3[m reverting some border patches
* [33mb16d828[m changed adjustborder to be a macro
* [33mfef4614[m applied yiyus applyrules() patch
* [33mbe39ddd[m implemented noborder for 1 client in the view
* [33m6d209b9[m made status script example of .xinitrc more useful
* [33m57a0788[m ok, using signal.h for portability reasons
* [33m3ad906e[m removed unnecessary closure of stdin reported by Frederic Chardon, thx
* [33m0be9fb8[m added sys/signal.h inclusion for BSD compliance
* [33m62a491e[m re-applied Neale's spawn patch, credited Neale in LICENSE
* [33m0b5dcf2[m applied Neale Pickett's xprop status reading patch, updated README and dwm.1 accordingly
* [33mfda92f4[m applied yiyus fix
* [33ma62ea40[m fix
* [33m7dc28d1[m Added tag 5.3.1 for changeset 335301ed102f
* [33mfbce733[m[33m ([m[1;33mtag: 5.3.1[m[33m)[m integrated yiyus clearurgent refactoring
* [33me757280[m reverted spawn
* [33med1bef1[m Added tag 5.3 for changeset 4004d6116035
* [33m2b047e4[m[33m ([m[1;33mtag: 5.3[m[33m)[m added Neale Pickett's spawn patch, thanks Neale
* [33m5f74dc5[m applied Gottox' comment fix (thanks)
* [33mea8a4ca[m several changes towards 5.3, XINERAMA is disabled by default, introduced usegrab Bool for grabbing the server during mouse-based resizals/movements (disabled by default), continued debugging tile() with resizehints == True and a lot of terminals supporting resizehints, still no optimal solution, I need to think about it, considering recursive algorithm for the space optimization
* [33m4883a06[m removed NOBORDER(broken and badly used), introduce WIDTH/HEIGHT macros for computing client size with border added, fixes bug announced by sergey_m
* [33m4dea532[m Added tag 5.2 for changeset e4bcaca8e6ef
* [33m53cac17[m[33m ([m[1;33mtag: 5.2[m[33m)[m using malloc() instead of calloc() and sticking to static initializer and struct assignment, not using *c = (Client){}; right now to avoid some ugly gcc warning, possibly a gcc bug since we are using -std=c99
* [33m83abfc0[m applied XGetWMNormalHints fix
* [33m862b0d5[m I prefer doing the check in showhide
* [33mc1c6fdc[m applied Donald Chai's showhide patch in slightly modified ways
* [33m9a4d07d[m applied Martin Hurton's checkotherwm simplification
* [33m3041010[m applied Peter Hartlichs aspect revert fix
* [33m753e0e0[m applied Gottox' grabkey patch
* [33md15d4ba[m applied yiyus tagbar patch
*   [33m815f9c0[m merged merge
[1;32m|[m[1;33m\[m  
[1;32m|[m * [33maddc52c[m fixed
[1;32m|[m * [33m26f41c9[m checking result of XGetClassHint, removed some obsolete lines in initfont()
[1;32m|[m * [33m73ec124[m merged my changes
[1;32m|[m[1;32m/[m[1;35m|[m 
[1;32m|[m * [33m4b3b597[m WM_NAME is builtin atom
* [1;35m|[m [33mec11a34[m introduced NOBORDER macro to hide the nasty - 2 * c->bw in various calculations, moved tagset to config.def.h
[1;35m|[m[1;35m/[m  
* [33m288cf78[m grabbuttons() and grabkeys() are now independent from prior numlockmask initialization
* [33m6411aa9[m reverted some resize() changes, reverted setlocale removal
* [33mdb5db88[m applied Peter Hartlich's patch regarding aspect calculation with slight modifications
* [33m258c338[m removed artifact from wmii
* [33m85da537[m changed grabkeys, removed initmodmap
* [33m2b4157e[m applied Peter Hartlich's initmodmap patch
* [33m0f26de9[m applied fix of toggletag by Jan Kaliszewski
* [33m840f937[m Martin Hurtons typo fix
* [33m6975a7e[m fixed error I did when applying Martin Hurton's drawtext patch
* [33m47f63dc[m applied Martin Hurtons resizemouse patch
* [33m02a8ca9[m applied Martin Hurton's movemouse() patch
* [33m2ce50a9[m using None instead of 0 for trans
* [33mbfa5869[m abc...
* [33m087a55f[m removed the i = textnw... as remarked by Martin Hurton
* [33m6d7285f[m applied Martin Hurton's scan() patch with slight modifications
* [33m69c7b4b[m changed order of variables in drawtext
* [33m97699e5[m applied Martin Hurton's drawtext() patch
* [33m2dc7f42[m applied Martin Hurton's view() simplification, not checking arg
* [33m9f3a5cb[m making a comment more explicit
* [33mb48fa3f[m removed setlocale() stuff, not necessary if Xmb in use
* [33m051a404[m added a comment about FAQ regarding mfact meaning
* [33md8d733c[m added some comments regarding FAQ about s{x,y,w,h}, w{x,y,w,h}, b{y,h,lw}
* [33mbb01e5a[m initialize trans with 0
* [33m06f7eed[m fix of XGetTransientForHint in manage()
* [33m0ffa6d1[m applied cleanup from M. Hurton and S. Nagy
* [33m15ce143[m fixes using arg->i instead of arg->ui
* [33m63d7190[m applied Johannes Hofmann's patch, please test
* [33mb279cef[m made readin a config.h variable
* [33m6254ef9[m Added tag 5.1 for changeset ce355cea9bb8
* [33m4a2902e[m[33m ([m[1;33mtag: 5.1[m[33m)[m forcing fullscreen windows to bw=0, though most fullscreen apps are broken anyways
* [33m6fad4c4[m potential crash fix if xinerama behaves broken, though I doubt it
* [33m78f0f85[m make hg tip compilable with default config
* [33m7ecadce[m local use of xidx is useless, got rid of it, falling back to screen 0 if pointer query fails for whatever reason
* [33mc86ed46[m got rid of compile time xidx configuration, querying mouse pointer instead
* [33m9086f98[m reverted uint redefinition
* [33m9aa4a90[m applied anydot's urgency hint patch, thanks!
* [33md5893f5[m renamed eprint die
* [33mf529d41[m simplified detach()
* [33m45768ee[m removed aux* stuff from Client
* [33ma6d23fb[m removed useless comment
* [33mbf76cef[m minor fix to view()
* [33m9bb0f20[m applied Frederik Ternerot's grabbuttons patch with slight modifications
* [33m2431ae7[m locale update
* [33m829b6b5[m removed useless characters
* [33m7b4c512[m applied James Turner's dwm.1 patch, thanks James!
* [33m7f7c314[m fix of monocle
*   [33m277155c[m another merge
[1;36m|[m[31m\[m  
[1;36m|[m * [33mdeef4c9[m fixed Gottox' buttonpress/ClkTagBar code
* [31m|[m [33m0c38ec7[m does this fix anything?
[31m|[m[31m/[m  
* [33mb86c818[m applied Gottox' ClkTagBar patch
* [33mc2a916b[m made arrange again like it was once
* [33m2bd46d1[m fix
* [33m6e0ce46[m use sel instead of seeking the list
* [33mc853d5e[m resize should apply if !banned
* [33m31da0b7[m applied Gottox patch
* [33m12ea925[m untested monocle
* [33m79ecbec[m non-zero
* [33mcf98ea2[m Added tag 5.0 for changeset 06eb9644e2da
*   [33md8fad9b[m[33m ([m[1;33mtag: 5.0[m[33m)[m branch merge
[32m|[m[33m\[m  
[32m|[m * [33mae1d865[m s/tags ref/tags mask/
* [33m|[m [33mf25cc56[m tiled layout resizehints should be respected by default
* [33m|[m [33m5a92420[m restored y-coordinate fixing of client windows
[33m|[m[33m/[m  
* [33m1ce1734[m updated man page regarding Mod1-m
* [33ma06b919[m minor fixes towards 5.0
* [33m43bb77a[m removed explicit warp in movemouse
* [33me3da222[m removed scroll-wheel based focussing on window title clicks
* [33m66608a6[m fix of swapped focusstack mouse buttons
* [33mb6aa84e[m removed the ButtonPressMask for root windows as well
* [33m9ff5143[m removed root window click handling
* [33m1edf6a7[m removed font and color definitions
* [33m4db2f44[m minor fix
* [33m1f1a132[m fixed tag click handling, however ClkRootWin doesn't work for me
* [33m512541b[m update
* [33m709da0b[m some bugfixes of the patch application yesterday
* [33m5cd65f8[m integrated yiyus mouse.diff (though the bar click handling is slightly broken, I'm to tired to debug it now, yiyus could you please?)
* [33me3838e8[m made Xinerama screen index customizable
* [33m016dca4[m removed trailing spaces reported by Soleen
* [33m8f05259[m crash fix
* [33m9463d53[m made lt visible again in config.def.h
* [33md662f98[m added nsz' patch
* [33me5a965a[m added SHCMD support for pipe-based commands due the new spawn() versio
* [33m5d422bb[m using foo layout during cleanup (suggested by Gottox), add Arg->v handling for togglelayout() suggested by anydot
* [33m38a43c2[m lt will point to a foo-layout during cleanup now (Gottox' suggestion), and togglelayout respects Arg->v
* [33mc565336[m integrated Peter Hartlich's patch, removed const char *c from union, simplified togglelayout
* [33ma8e0772[m applied anydot's patchset.diff
* [33m98e7950[m final version -- Gottox verified it using the test driver
* [33m88e6eb4[m revert of introduced problem
* [33m0840c13[m applied nsz' textnw patch thank you
* [33m077d3e4[m updated the for-loop with Gottox' proposal
* [33md26b60b[m minor change
* [33m32f36ab[m applied nsz's patches (many thanks!)
* [33m08bcf72[m small change to drawtext
* [33mfc578c5[m fixed the tile() issue with xpdf
* [33mc8eaab2[m using anydot's memcpy-approach in drawtext, however it still looks awkward to me
* [33mc26e22c[m Gottox' drawtext simplification
* [33mc2784e4[m applied noviewprev.diff, fix.diff and unusedflags.diff
* [33m6e93877[m fix
* [33m92f3c18[m lt->arrange in mfact
* [33md589f76[m isfixed implies isfloating
* [33m75690c8[m applied nibbles fixes, slightly modified
* [33mfde58d5[m applied yiyus tip patch from tue
* [33me100274[m core dump fix in cleanup
* [33m940a4cc[m updated the initial comment to reflect the use of bit arrays
* [33m64243ab[m slight changes
* [33m32c5046[m removed bx and bw, unnecessary
* [33m6c8618f[m renamed domax into ismax
* [33m9189f7a[m simplified tile()
* [33m2d4faae[m removed Layout->updategeom, unnecessary
* [33m5d2385b[m removed TEXTW
* [33m0fe2e78[m applied yiyus domax patch with slight modifications
* [33mcd3d83f[m replaced isvisible with a macro
* [33m0a9ef56[m removed emallocz
* [33m0528a37[m s/int/uint/ in config.h
* [33m56b2fec[m removed debug output, sanitized tag limit check
* [33m9f569fa[m setmfact argument was wrong
* [33m48d0c56[m Key.mod is uint, Client.[old]bw is int
* [33m825d6cb[m s/unsigned long/ulong/
* [33mf852504[m s/nextunfloating/nexttiled/, changed zoom() behavior
* [33mc3fa9e8[m s/unsigned int/uint/
* [33m8e05f6c[m s/void */const void */
* [33m39d1ecd[m applied Gottox bitmask + void *arg patch
* [33m103fb58[m some minor fixes
* [33m5f55af4[m simplification
* [33mf806a17[m reverted dist target in Makefile
* [33m822101d[m merged tile.c again into dwm.c
* [33m6bdef73[m take bar into account
* [33m234b12e[m be more polite to clients which like to appear outside the window area, but still on the screen
* [33mbd4deae[m fixed comment
* [33m499315c[m fix
* [33mf22d047[m make it easier for the user, if Xinerama support is given, always use the screen 0 as window area/bar area, everything else can be used for floating clients
* [33m4a5c8d8[m improving space usage if master is left of stack (default)
* [33m71365a5[m only snap within window area
* [33m3afca3e[m s/DEFGEOM/CUSTOMGEOM/
* [33mbdc80bd[m update
* [33m64707da[m updatetilegeom should be fine for setmfact
* [33m5497268[m recent changes, introduced togglebar, changed some defines into variable declarations where possible
* [33m42cb2bd[m new stuff
* [33m585294c[m removed the <M> togglelayout call
* [33ma864a82[m s/tilegeom/updatetilegeom/
* [33mbd67a82[m removed monocle for now
* [33m14d8d82[m removed the exact focus mechanism of next/prev window
* [33m4246aff[m moved all tile()-related stuff into tile.c which is included from config.def.h, the default dwm is now nearly independent from the arrange() algorithm in use
* [33m42c4b31[m removed tileh, renamed tilev into tile again, removed counttiles, tilemaster
* [33ma785a0d[m removed Layout->isfloating
* [33m489ac07[m removed reapply() -- unnecessary
* [33m349d768[m renamed setlayout into togglelayout
* [33m6dfa7ca[m removed temporary wildcard handling
* [33m71681c2[m added wild-card handling for tags
* [33m7047818[m applied nsz's another style patch
* [33md7cc0f6[m applied nsz's style.diff patch
* [33m6b79f3f[m just added a comment
* [33m446fa8c[m minor fixes
* [33mfa244aa[m having monocle on Mod1-m
* [33m7ac4f8a[m hotfix
* [33m7eb2628[m removed Geom stuff, introduced updategeom() again, still view is somewhat broken?
* [33m93a4fe1[m cleaned up config.def.h
* [33m5602f44[m implemented exact focus next, if arg != NULL to focus{next,prev}
* [33mb848f4b[m applied the proposal by nsz
* [33m86c4797[m applied JUCE patch
* [33mc094ed2[m simplification of view() as proposed by anydot
* [33mbfd6079[m applied yiyus tagset patch
* [33m7f70d90[m applied yiyus fgeom patch
* [33m858251d[m applied dfenze drawtext simplifications
* [33md26c28c[m this is the correct way
* [33mb633577[m copyright notice is in LICENSE
* [33mc059625[m applied Ph's seltags-simplification with some modifications
* [33m874837f[m applied Ph's MIN/MAX patch, nice work!
* [33m5fa559d[m applied Ph's patch regarding geom and lt initialization
* [33m146ff22[m applied Gottox' applyrules() fix
* [33mbb0a328[m geometry fix proposed by Jukka
* [33m721b208[m applied applyrules-fix by Jukka, thank you Jukka!
* [33m6229ed2[m fix
* [33m940240e[m applied the proposed monocle patch from the mailinglist
* [33m08c596e[m next version is 5.0
* [33m9ce6abb[m Added tag 4.9 for changeset 22c669b2dd36
* [33m0e21794[m[33m ([m[1;33mtag: 4.9[m[33m)[m yet another cleanup
* [33md477fb6[m some cleanup changes
* [33m3d6630b[m uncommented dual layout in preparation of dwm 4.9
* [33mc982bb1[m applied Peter Hartlich's simplification patch of setmfact and his revival of MFACT, appliead Janness Hofmann's simplification of grabbuttons() -- thanks guys!
* [33m6cf73e7[m aspects hints seem broken for fullscreen apps
* [33ma520ba3[m removed uneccessary line
* [33m0c71b16[m bugfix
* [33m00c28a7[m setmfact should not have any effect if in floating layout
* [33m5a3a2d6[m minor fix
* [33ma355782[m revival of mfact and setmfact
* [33m20cd336[m setlayout and setgeom are now togglable again
* [33ma6a216f[m geom indicator and layout indicator is only displayed if there are several geoms/layouts
* [33m2c2063b[m hotfix of idxoftag
* [33me6ede46[m blw/bgw calculation bugfix
* [33m6877205[m updated configurenotify
* [33mfb5f99d[m minor bugfix in applyrules
* [33m7ebab75[m added sample of {grow,shrink}master to config.def.h
* [33m9fa5ca3[m renamed c->border into c->bw, fixed monocle to subtract c->bw from each h/w value
* [33mfe6b0c0[m geoms are now drawed in the status bar
* [33maa2395b[m removed the string-based setgeom approach, introduced a new Geom type instead and a helper macro
* [33mdba2284[m made the string-based setgeom working
* [33m33b1960[m some experimental state DO NOT USE THIS, I plan to have a nicer interface to change geometries
* [33me237b2a[m some changes towards 4.9
* [33mdd9ee6d[m Added tag 4.8 for changeset 607015ddb091
* [33m1380569[m[33m ([m[1;33mtag: 4.8[m[33m)[m removed the comment again
* [33m831428b[m some polishing in tileh/tilev
* [33m6943971[m minor bugfix
* [33mf2e98f4[m added a new comment
* [33mc19d4b2[m some cleanup
* [33mf77a3d0[m updated my geoms function
* [33m8aa1533[m update
* [33m2fc9cff[m set layout already here
* [33m3c5b6f0[m well I use a different default tile
* [33m0267353[m added updatebarpos()
* [33m95eae7b[m removed all defines of geoms, implemented setgeoms() instead, added config.anselm.h to show how I'd like to see that people edit their geoms
* [33m5910775[m some polishing
* [33md05d09b[m updated dwm(1)
* [33m47b1974[m added bx, by, bw, wx, wy, ww, wh, mx, my, mw, mh, mox, moy, mow, moh, tx, ty, tw, th, wx, wy, ww, wh ad variables
* [33m247ba66[m changed config.def.h
* [33md7b074f[m new stuff
* [33mc917018[m implemented setlayout in the way proposed on the ml, split tile() into two functions, a third will follow soon
* [33mf7a45ff[m allow for vstack
* [33madd7df6[m added some comments what the TODOs are for 4.8
* [33m3a79b82[m changed config.def.h
* [33mb31b430[m integrated the new -x -y -w toggles of dmenu into my setup
* [33m88c8ead[m removed some more useless clunk
* [33m2e95837[m implemented the stuff as I discussed on dwm@
* [33m5d9ae3f[m fixed urgent hint handling
* [33m2e38296[m renamed maximise to monocle again.
* [33m59aa02a[m fixed urgency hint, though Xinerama integration is still ongoing
* [33me3c2d32[m next on TODO
* [33m295ad21[m renamed MAXLEN into MAXTAGLEN (backward compliance)
* [33m39af3c2[m renamed monocle into maxmise, documented the keybindings in dwm(1)
* [33m96ee9d8[m monocle goes mainstream
* [33ma82cba2[m fixed applyrules bug
* [33mf7c097e[m removed View cruft, now back to the roots
* [33mda1b3fa[m made tag names snappier
* [33mad0a2fa[m fixed some issues nsz reported in IRC log
* [33m9804726[m well, AIM_XINERAMA should not be enabled
* [33m7bc272a[m made the basics of the tagging concept working -- if people want dynamic tags, that's even possible with this concept, the vtags[] array needs to be modified during runtime for this -- the new code is quite experimental, ugly and needs polishing
* [33mf1719ac[m removed initags -- we autoselect the first tag in each view instead
* [33md99ec61[m a small fix to buttonpress
* [33m2f70a14[m some more changes towards a better dwm
* [33m00ca643[m 	proceeded, though we still miss a real Tag struct
* [33m0271ac0[m disabled AIM_XINERAMA
* [33md517829[m simplified dwm
* [33m2bfd3ff[m certain fixes, though still a lot of the mutex stuff missing
* [33ma3d8c05[m pushing my changes of tonight upstream (hg tip is NOW very UNSTABLE -- but those changes are necessary to get a decent multihead support) -- I renamed Monitor into View, to reflect in a better way the dwm terminology of the past
* [33mfd01413[m fixed Gottox' mail address
* [33md6e24f7[m well typo fix
* [33mc43d7b7[m added Gottox to Copyright holders after all his contributions, applied his last patch
* [33mde5b294[m some other fixes, resize contains a minor bug
* [33m8e0f8ff[m crash fix
* [33mdd21823[m made arrange() Monitor-dependent as well, fixed the movemouse/resizemouse issues
* [33m9cb9c32[m minor
* [33m4076e2f[m applied Gottox' monitor.diff patch (thanks btw)
* [33m55edd2d[m made restack, drawbar also Monitor-related only
* [33m2e8e550[m changed arrange functions to contain the Monitor as first argument
* [33m4426032[m applied Jukka's zoom-patch
* [33me0f0397[m resize handles offscreen issues
* [33mca3e847[m applied some necessary changes
* [33mc2737b7[m removed Monitor->dc, unnecessary
* [33m191cb9c[m removed Monitor->root, since we do not support classical multihead
* [33m6ab163c[m some drawbar() polishing, and certain related fixes
* [33me824439[m urgency hook handling needs also to invert the square if present
* [33m954db46[m Chris pointed me to the fact, that the window geoms calculation can be done once for each monitor, so I applied this remark
* [33m508922b[m fixed missing else branch
* [33m4adfdc9[m applied dme's patch to prevent changing prevtags if nothing actually changed
* [33mc619363[m applied dwm-4.8-snaptileds.diff
* [33m012710a[m implemented urgent hint handling (with multihead support)
* [33mc2c54cc[m got initial Xinerama support working, though there is a lot work todo
* [33ma62630a[m some more polishing/consistency changes
* [33m62b18fb[m proceeded with multihead/Xinerama support
* [33me0d6451[m removed maximize, there will be monocle soon
* [33m7a496e9[m fixed wrong tagging stuff
* [33m308f95a[m added dmenu_run to config.h
* [33m40a734b[m root window and screen have to be in Monitor struct, we want side-by-side Xinerama and Multihead support (only Xinerama when enabled and present)
* [33m985e330[m merged Christof Musik's Xinerama support patches, though this needs some polishing!
* [33m5f19423[m simplified Mod-m
* [33md66ad14[m implemented reapply for re-applying the tagging rules during runtime, Mod-r
* [33m8497f9f[m next version will be 4.8
* [33m91bb749[m Added tag 4.7 for changeset d6d3085307d8
* [33m68ff133[m[33m ([m[1;33mtag: 4.7[m[33m)[m fixed focus steeling bug done by clients like opera
* [33m4380db4[m removed support for the NetSupportingWmCheck stuff, netbeans, argouml and others also don't work with compiz, so it is Suns problem to provide a fix
* [33m123a565[m yeah compiz didn't did the trick, but identifying dwm as LookingGlass (LG3D)
* [33md0e0505[m foo
* [33m762b66a[m hack that adds NET_SUPPORTING_WM_CHECK handling, dwm identifies itself as compiz, hence I believe this might workaround the JDK 1.6+ XToolkit bug
* [33mcb4951d[m applied Ritesh's patch to stext handling with some minor modifications
* [33m667da18[m initialize prevtags in setup, now users can setup which seltags should be selectedin config.h
* [33me9a0733[m Using a new tags definition (const char [][MAXTAGLEN] - thanks go to Szabolcs!
* [33m198502f[m moved LENGTH to dwm.c, moved prevtags to dwm.c
* [33m35efafe[m we check variable == value, and not the other way - the other way is for beginner programmers.
* [33m951d022[m removed a misleading comment about client title windows, which don't exist anymore
* [33m54bde0f[m full names in -v output of dwm
* [33m260a55e[m doing it in a shorter way
* [33m0e98090[m removed fgets usage, increment offset until a line is read, dwm will drop all lines read in one call, except the first!!! one (previously it preferred the last) - but the current approach is simplier and works better for general purpose in conjunction with the offset handling
* [33maf4667a[m simplified
* [33ma98b5e5[m made error handling more proper
* [33mb8985dc[m replaced low-level stext reading with an fgets call
* [33m6f60b2e[m revival of RESIZEHINTS
* [33m3033d45[m sanders patch for b2 toggle
* [33m34e7872[m replaced Nmacros with LENGTH(x) macro
* [33mc36f7c3[m replaced ISTILE with domwfact/dozoom bools, removed nrules, nlayouts and ltidx, added NRULES, NLAYOUTS and Layout *layout as alternatives, removed isarrange(), checking against layout->arrange instead.
* [33m3fd39fe[m some sanity changes
* [33m93eee24[m going toward 4.7
* [33md5e8edc[m Added tag 4.6 for changeset bcd7e18e196a
* [33m13577b1[m[33m ([m[1;33mtag: 4.6[m[33m)[m fixed a comment
* [33m5473e76[m also consider width for tile fallback enforcing
* [33mcdd6c3e[m removed RESIZEHINTS and enhanced tile for fixed or aspect-ratio'ed clients
* [33m29f2b15[m some cleanup, removed ntags variable, defined NTAGS macro, simplified tag(), view() and idxoftag(), fixed some NULL comparisions
* [33m7b65b76[m parenthized use of ISTILE macro in dwm.c
* [33me94774d[m thx to Toni Lainson
* [33maf0034f[m fixed two comments
* [33mcd7ebaa[m removed dwm.h, just include C-files in config.h if you extend dwm, that's simplier and most flexible than all other possibilities
* [33m8dc03d6[m small cosmetic fix
* [33m1dcb18c[m uncommented DEBUG CFLGAS/LDFLAGS
* [33m206eb34[m just making dwm.h saner
* [33m04de572[m applied Eric Mertens patch to mainstream dwm, however this needs testing
* [33m5a04ede[m cleaned up dwm.c/dwm.h somewhat that it allows easier integration of patches
* [33m24c125c[m small comment
* [33m0453c1d[m recreated dwm.h
* [33m0b5c14c[m added Mod1-Tab description to dwm.1
* [33ma73de0c[m added antoszka's viewprev patch with some minor modifications, restored Client->tags as Bool *, however kept the static initialization of ntags and seltags (prevtags) - this seems to be the best compromise
* [33meeea4ef[m applied Brandon MacDone's static initialization patch for seltags and Client->tags
* [33m883e09b[m removing NULL-terminating **tags definition in config.h
* [33m7e25897[m removed two spaces reported by Soleen
* [33m95091dc[m reverted Peters patch to tile, I will discuss the reasons at dwm@
* [33m5767699[m s/xterm/uxterm/
* [33m60adbab[m added hint for downloading dextra
* [33mc3eca4d[m fixed font definition
* [33md1f4fbb[m fixed man page
* [33m635b643[m fixed an issue in Peter's patch (it is no good idea to restack() all clients on enternotify()
* [33mbedbe59[m applied Peter Hartlich's border collapse patch
* [33m3f3086f[m improved tile() for the RESIZEHINTS == True case, now more space is consumed by the clients (esp. if those clients use increment handling heavily)
* [33mf92a4e4[m fixed colors
* [33m2fc8a13[m fixed inclusion order
* [33m6372500[m updated with my favorite colorscheme
* [33me9348dc[m applied colors depend from lavishs proposal
* [33mfa857b2[m switching to white normal bg, renaming tag 9 into www, for static use in conjunction with ff
* [33mc77663f[m btw 4.6 will be the next release
* [33m17d39ee[m renamed config.h into config.def.h, config.h will be created if not present, this seems less annoying after all
* [33m8d1810c[m introduced ISTILE, which can be easily extended with other layout functions to allow reuse of setmwfact() and zoom()
* [33m60444da[m setmwfact and zoom check isarrange(floating) now, not !isarrange(tile) - this makes it easier to play well with bstack and nmtile patches
* [33mb0477c3[m Added tag 4.5 for changeset 2acc60d6dfe2
* [33m24dae7d[m[33m ([m[1;33mtag: 4.5[m[33m)[m cosmetic fix
* [33mfa1ce22[m fixed a comment
* [33m1fafcb1[m applied Peters patch, applied yiyus hint to initfont
* [33m08c2d92[m applied Peter Hartlich's togglemax patch to allow toggling tiled clients to maximum
* [33mfe2775a[m made all stuff non-static - so you can choose wether to use dwm the static or the extern way when extending it
* [33m01022b9[m there might be envs which need Xlib.h
* [33mb2f276b[m Mod1-Button2 on a floating but not-fixed client will make it tiled again
* [33md1ce3ea[m now tiled windows can be resized/moved, their floating state will be toggled implicitely
* [33m9449ea3[m some more rearrangements
* [33m49197fe[m ordered all functions alphabetically
* [33m11cfff2[m corrected a misleading comment
* [33ma026617[m macros which have been defined in config.h can only be used at function level, however you can nest code into config.h now for implementing a different layout (just for example), eg. #include "supertile.c"
* [33ma6df995[m ordered function forward definitions
* [33me041ff7[m backporting my intro-comment of old dwm.h
* [33m2d7bb8d[m removed grabkeys, not necessary
* [33m0235a84[m micromizing dwm step 1
* [33m2091200[m new colorscheme (16-bit compliant)
* [33m7e476fb[m moved bar-related stuff to bar.c (merged draw.c into that)
* [33m9800518[m renamed drawstatus into drawbar
* [33m5d831ea[m renamed config.default.h into config.h
* [33me0a6dee[m dist target only needs to add config.default.h
* [33m73e2aba[m removed config.arg.h, only 1 config.h necessary
* [33m9f88fd0[m small changes of the colors
* [33m0e515a0[m other color
* [33mc4b3c0d[m using light colorscheme, preparing merge of config.arg.h with config.default.h
* [33mf3a5116[m I work with enabled RESIZEHINTS, simply because I force myself to continue the st development ;)
* [33mae760f3[m introduced new define RESIZEHINTS, which allows to enable/disable size hint handling in tiled resizals
* [33m169d96a[m 14px fonts drives me nuts
* [33mf651435[m Added tag 4.4.1 for changeset 7c117df5d202
* [33ma92cf49[m[33m ([m[1;33mtag: 4.4.1[m[33m)[m prepared 4.4.1 bugfix and minor feature enhancement release
* [33mcc79700[m Added tag 4.4 for changeset 408014d21261
* [33m67a1141[m[33m ([m[1;33mtag: 4.4[m[33m)[m removed unnecessary include, prepared dwm-4.4
* [33m8be3f3e[m setlayout should perform strcmp's if arg != NULL, because Layout is local to screen.o
* [33m5762e92[m reverted release CFLAGs
* [33m36672d0[m removed the _DWM_PROPERTIES handling, reverted ban/unban to XMoveWindow(), and changed argument of setlayout to layout[N].symbol check
* [33mb18e684[m renamed char prop[] into buf[]
* [33mfc109ea[m fixed misappearance of iconified windows on SIGKILL
* [33mb975c47[m moved updatebarpos to screen
* [33m47765f7[m added screen.c, removed layout.c and tag.c
* [33m96d7fe1[m prepared merging layout.c and tag.c into screen.c
* [33m78d1a22[m small fix
* [33m0c60620[m hmm I doubt the usefulness of storing this information...
* [33m50be6c8[m cleaned up settags-handling
* [33m7d156de[m applied Gottox mwfact patch
* [33m55d8dda[m replaced static Layout *lt with static unsigned int sellayout... (will be adapted later when _DWM_CONFIG is serialized as root window property)
* [33m86953bd[m renamed seltag into seltags
* [33ma923298[m applied Jukka Salmi's setmwfact patch
* [33m04dec4c[m made plural arrays
* [33me40448f[m fixed the issue observed by various people, that clients appeared on empty tags
* [33m10bc0ce[m made tag/view/toggle{tag,view} work on pointer to tags-array, there was the need to define Key key[] not static to do this. split focusclient into focusnext/prev, fixed config.*.h's
* [33me8792d9[m applied Jukka's patch
* [33mfeec92d[m fixed _DWM_CONFIG persistation, fixed the client disapperance bug during restarts
* [33m10d13f0[m fififi
* [33m8fcc4ff[m fix of resize (thanks Sander for the hint!)
* [33mf251224[m fixed a typo
* [33mb32cd44[m small bugfix
* [33m9e56e1d[m tags should be persistent now during X server run
* [33me4ad320[m small bugfix
* [33ma200c39[m made tile simplier
* [33m77044e8[m made Layout a static struct in layout.c, added some convenience getters in layout.c, now lt->arrange accesses are not possible anymore, arrange() is the super-arrange function which sets up all layouts
* [33m2feb3af[m made resize more precise
* [33m0937cc7[m moved floating to layout.c, kept tile.c outside
* [33mf6e41b0[m renamed MASTER into MWFACT, master into mwfact, and incmaster into addtomwfact
* [33m2c6087e[m fixed a comment
* [33m2d81b78[m separated layout-specific stuff into separate .h and .c files which are included in config.h resp. config.mk - this allows writing layouts for dwm without any need to patch existing code
* [33mb5eea45[m let not overlap the borders
* [33maa53e39[m removed VRATIO, NMASTER, inc*(), renamed HRATIO into MASTER, see mailinglist for details
* [33m4216bf8[m slight change of my color scheme
* [33m2cd1609[m removed spow(x, 0); calls, I did them for consistency's sake, but it should be rather obvious how the scaling works anyways
* [33m85c9ebf[m applied Jukka's dwm.1 patch
* [33m7969250[m changed shortcuts as described on the mailinglist, added sanity checks for ratios during tile (fallback to wah if clients would get too small), documented that new stuff/shortcuts in dwm(1)
* [33mda91dfc[m small fix of static function order
* [33m4135e34[m I introduced {H,V}RATIO and inc{h,v,}ratio() functions - the default behaves like in dwm-4.3, config.arg.h shows how I prefer the ratio being handled (for the future I plan to change const char *arg into ..., and renaming Client into Win.)
* [33m846128a[m removed a C++ style comment
* [33me461e60[m implemented ratio tile as described on the mailinglist
* [33m28c1033[m changed the fix of yesterday, the resize should only be necessary at manage() time, not on any unban()
* [33m0d40590[m foo
* [33m8fda28b[m set client state to iconic on maprequest
* [33ma54cf2e[m changed ban/unban implementation to not move the windows anymore, but map/unmap them instead - PLEASE TEST THIS
* [33m4b9337a[m removed shiftview(), if you scroll the views in the tag area, you can also use Button1 instead removed focusclient([-]1) bound to scroll wheel - if you slightly move the mouse you will focus the first client anways which is in the way
* [33m1544975[m applied Jeroen's {clean,spell}.diff patches, thanks Jeroen!
* [33me0cfe07[m applied Jeroen Schot's shiftview patch
* [33m82be289[m applied dwm-windowscrolling patch
* [33mf2190c8[m Added tag 4.3 for changeset e0ec0d5d8b1e
* [33mc31648d[m[33m ([m[1;33mtag: 4.3[m[33m)[m restoring tip to be a working dwm again (switching FONT to terminus in config.arg.h)
* [33m52250e7[m please recheck this patch with Mathematica from Wolfram Research - lemme know if it fixes the geyish blob window bug
* [33m51a94a2[m removed crappy createnotify handler
* [33mc95bf3d[m applied restack patch of anydot, with slight changes
* [33m4bf3b01[m I change the style of init somewhat, init as early as possible.
* [33mff957d1[m uncommented creatnotify
* [33m83aa110[m added an creatnotify event handler
* [33m5a1a2ed[m applied anudots [un]ban repair patch
* [33mb3419f4[m making variable declarations in dwm.h extern, this seems to be more ansi compliant
* [33m141beb2[m replaced BORDERPX with sel->border in togglemax(), in other places this is not possible.
* [33m4e49d5a[m Added tag 4.2 for changeset c13cb8c6b7a5
* [33m2c6be72[m[33m ([m[1;33mtag: 4.2[m[33m)[m referred to LICENSE file
* [33md934296[m Jukka also belongs to Copyright holders after all he has contributed and done for dwm, updated -v as well
* [33m39ae286[m applied Jukkas patch
* [33m59e65d1[m changed -v output (now also anydot and nsz are contained in this output)
* [33m9fdd2cd[m added nsz to copyright holders as well, because he did a lot recently
* [33me1deda9[m added anydot to Copyright holders, because he contributed a lot recently
* [33m199a601[m applied anydot's 3 minor patches, thank you anydot
* [33m492c6f1[m applied Sanders patch
* [33mcaa7ab5[m applied anydots proposal to let togglefloating restore fixed windows
* [33mf3e672e[m fix if n < nmaster of remainer calculation for master windows
* [33m02d5ddd[m rev 900, cool
* [33mc789941[m fo
* [33me45b3ce[m calculating the remainder for master and stack area correctly
* [33m5a9af49[m fixed issue reported by Christian Garbs
* [33m32563ab[m removed the only one and superfloues strncmp
* [33m70c7b43[m foo
* [33m69dfcaa[m reverted last change after Sander pointed out the original decision
* [33m6ee8e3e[m applied anydots remark of togglefloating()
* [33m8439369[m applied Szabolcs proposal for zoom() as well
* [33m81658ea[m applied Szabolcs proposal to simplify setlayout()
* [33m81aebf8[m Added tag 4.1 for changeset 00f4180df72b
* [33mfa32f02[m[33m ([m[1;33mtag: 4.1[m[33m)[m no that change breaks fullscreen apps
* [33m598e229[m raise barwin in restack, that's the most elegant solution I think
* [33m1e826dd[m simplification
* [33ma967d7f[m raising the barwin has no effect becasue of restack
* [33mce450c5[m fix
* [33m8f5f7a5[m barwindow raising
* [33m5ad2828[m using BarTop as fallback if BARPOS is set to BarOff as default for toggling
* [33mb896b58[m removed strip, added -s to LDFLAGS
* [33mfef6c5c[m added new Mod1-b functionality to dwm(1)
* [33m37e062b[m another fix, call lt->arrange() in togglebar only
* [33mcf58091[m fixed bpos init
* [33m2aef8b9[m made bar togglalble
* [33md96307c[m thanks to Jukka
* [33m124866e[m added the GTK Save-As bug report to BUGS section of dwm(1)
* [33mab3d6a7[m applied dfenze cleanups, fixed some comments in dwm.h
* [33mc67dbb2[m small fix of fix
* [33mb8bccb4[m fixed a potential security flaw
* [33mb6b2f58[m applied Maarten Maathuis recenter-patch for floating clients only requesting new width and height exceeding the screen space
* [33mf7bdb39[m s/remain/remainder/
* [33mecd9c3e[m fixing remaining space calculation
* [33m216099d[m thanks to Juka to check -Wall ;)
* [33mfc2e3ea[m next version is 4.1
* [33mf9e7a33[m applied patch of Paul Liu to allow onthefly resizing due to xrandr changes
* [33m7c9fa25[m Added tag 4.0 for changeset 018c38468422
* [33m22399a3[m[33m ([m[1;33mtag: 4.0[m[33m)[m fixed the border issue for mplayer, ff is definately broken when using F11 (fullscreen mode)
* [33mad2508f[m touch border
* [33mb078599[m set border at manage time
* [33m1e80207[m using pixelcarnage-monospace (proggyclean), because this is better to the eyes
* [33m464fc2c[m changed border handling
* [33mbe8d6d4[m changing order of c->border restorage
* [33mf0c2353[m I used 2006 in other places as well
* [33ma730213[m yet another fix of copyright compactisition
* [33m399993c[m making Copyright notices more compact
* [33m4d31806[m next version will be 4.0, so don't expect it within the next days
* [33m540d5ee[m make also transients floating when we do not know the main window
* [33m7d071ce[m Added tag 3.9 for changeset 55478328b242
* [33m93aeaa5[m[33m ([m[1;33mtag: 3.9[m[33m)[m next version will be 3.9, but don't expect it this week
* [33m06f9f34[m add an additional check in resize() to prevent a crash of dwm
* [33m5c48012[m Added tag 3.8 for changeset 2ea201354cf0
* [33ma686c9c[m[33m ([m[1;33mtag: 3.8[m[33m)[m we don't need to set the font all the time
* [33m9ca5c3b[m some changes to updatesizehints, I don't change the aspect ratio algorithm now - I can't think, it is a mess
* [33mbab5b11[m removed sendevent
* [33mee8fb0c[m Escape -s in dwm.1
* [33m0d9d3e7[m Added tag 3.7 for changeset baee494346e5
* [33m12280f0[m[33m ([m[1;33mtag: 3.7[m[33m)[m prepared 3.7, ready to rambo
* [33ma58731e[m removed an unnecessary newline
* [33m1df4559[m removed superfluous externs (except for tags, because tags is defined in the source)
* [33m2122e39[m replacing Mod1-i with Mod1-Shift-j, Mod1-d with Mod1-Shift-k
* [33me701394[m oops, small bugfix in my config
* [33m3d1d75a[m default masterwidth should also be at 600
* [33m35f08f4[m changed order if h/l
* [33m0ea0343[m well I agree to several people claiming h/j/k/l is the better default than Tab/S-Tab/g/s for focus and master resizing
* [33m338c083[m renamed untiled into floating, keeping tiled instead of tiling (afaik tiled sounds more correct) - English speakers convinced me
* [33m671442e[m hahaha, untiled and non-untiled sounded really cumbersome
* [33m8d11163[m made Fnt an anonymous inner struct
* [33mfe5acb9[m made Fnt an anonymous inner struct
* [33mcac492b[m nah, I don't want 640 as MASTERWIDTH
* [33mef9b3e1[m using MASTERWIDTH=640 and 32px steps by default (incmasterw())
* [33m5a13632[m simplified focusclient()
* [33m5871008[m renamed versatile into untiled
* [33m27b0595[m merged focus{prev.next} into focusclient(1/-1)
* [33m12d5a26[m made dwm.h more tidy (thx Jukka for the zoom() hint)
* [33m89b7f15[m oops
* [33m5711609[m small bugfix
* [33m825b7c3[m fixed some issues due to the Arg->const char * transition
* [33mba96131[m restoring default keybindings as Sander complained
* [33m2c477cf[m replaced Arg union with const char *arg, seems cleaner to me, even if we need atoi() in some places
* [33m986ca73[m re-added xterm to config.default.h
* [33m2880988[m removed button4/5-bindings for incnmaster on mode label - that is misleading
* [33mcb9607c[m fixed order of key bindings described in dwm.1
* [33m4bd4f42[m status needs update even in togglemax() - since we got an indicator for this
* [33m84432e6[m reusing drawsquare for client title, empty square before title means versatile window, filled square before title means versatile maximized window.
* [33m1a25414[m dwm draws a small caret before the client title if it's a versatile client
* [33m3171371[m nah grouped keybindings by context
* [33m92105e7[m fixed exit condition in togglemax()
* [33m6ee9f13[m fixing missing extern declars in dwm.h for {de,at}tach()
* [33m352cae4[m several changes, made togglemax extern and separated it from zoom() - moved zoom() and togglemax() into layout.c, changed void (*func)(Arg *) into void (*func)(Arg), changed default keybindings of focusnext/focusprev and incmasterw to h/j/k/l accordingly, made keys in config*h appear alphabetically (special keys first), renamed resizemaster into incmasterw, renamed MASTER into MASTERWIDTH
* [33mb3b58c0[m just ignore the FD_ISSET check in main.c of xfd, just call XPending (which does the same afair)
* [33m204f0a3[m optimizing background color of terminals
* [33m78666b9[m using 333 as background, hey proggyclean is really good
* [33m0bdcf75[m switching to 13pt proggyclean (this fits better my 1920x1200 resolution than 12pt terminus which is too small or 14pt terminus which is too fat)
* [33mf100928[m using smaller font
* [33mf76b3a4[m using a green selborder
* [33m84ae6e1[m reverting to bg 555
* [33m7846595[m s/555/357/ for SELCOLOR
* [33m7ae0c19[m switching to urxvtcd for the moment (the uxterm flicker makes me headaches, st is really highest prio now)
* [33mdc66237[m Added tag 3.6.1 for changeset 20ec6976cee1
* [33m7541f1a[m[33m ([m[1;33mtag: 3.6.1[m[33m)[m creating 3.6.1
* [33m74cbbe5[m reverted accidental removal of sx, sy
* [33m52f0b9e[m removed some global vars which should be static instead
* [33m29c26b8[m moved focus{next,prev} and nexttiled from client.c to layout.c (because those are not client-specific), moved toggleversatile() from layout.c to client.c (because those are client-specific)
* [33mf196b71[m cleaned up and commented the config.*.h
* [33mab83872[m Added tag 3.6 for changeset 75b1b25fe0d7e29400baf30568153f668324928b
* [33mad4962c[m[33m ([m[1;33mtag: 3.6[m[33m)[m fixed quoting and a comment
* [33md180ba4[m renamed setfont to initfont, getcolor to initcolor
* [33m138b7fb[m fixed order
* [33me750878[m added draw.c again (except getcolor and setfont which are helpers in main.c)
* [33mf4d15b1[m separating drawsquare from drawtext, made drawtext extern
* [33m355beb5[m rechecked with OpenBSD
* [33m8012fcf[m split screen.c into layout.c and tag.c (because the view is an implicit mixture of both)
* [33m6bc4556[m using eprint instead of fputs
* [33m879241c[m replaced togglelayout with setlayout
* [33m3794c62[m changed some odering in config*.h
* [33m5a03daf[m renamed Client->versatile and Rule->versatile into Client->isversatile resp. Rule->isversatile
* [33m6d5f67a[m renames swim[ming] into versatile
* [33mcee56d3[m renamed floating into swimming (this does not clash with C naming conventions and fits better the fish symbol) - also in man page
* [33m7c4da24[m removed debug compile flags
* [33mcdbc84b[m introduced Layout struct
* [33mb2f8951[m some more code polishing
* [33mebe68f6[m forgot an extern declaration
* [33mdf9fd28[m bugfix of transient handling
* [33me9c49dd[m removed procevent, more refactoring
* [33mf841501[m draw.c is useless (belongs to main.c now)
* [33m238dd5d[m renamed view.c into screen.c
* [33m64871a7[m renamed manage.c to view.c
* [33m2e95bc0[m renamed Rule members, renamed RReg into Regexps
* [33m4cdbd52[m merged tag.c, view.c and tile.c to manage.c
* [33mb3d7e07[m some more refactoring
* [33m30af19d[m added some new convenience functions
* [33m5d9146f[m some more refactoring
* [33m5cc27f1[m introduced tile.c, some refactoring of functions
* [33m39ed54a[m simplified configurerequest to a bare minimum, removed wrong ban() calls
* [33mb61f913[m fixed configurerequest according to Jukkas complains
* [33m3167373[m fixed configurerequest according to the problem Jukka reported
* [33m4cff744[m don't resize master if not in tiled mode
* [33mc3527be[m removed useless space
* [33mde66957[m well, resize should be called in dofloat anyways ;)
* [33m6e22ccf[m removed ugly ban(), extended resize() that it only resets the size if necessary, added border_width commit to manage()
* [33m8a5f002[m removed getnext/getprev, redundant
* [33m3ce8c9f[m added ban() which takes care than a banned window is not banned again... (this reduces the overall ConfigureNotify's to clients)
* [33m0d095ae[m Added tag 3.5 for changeset 63ad05e7f9e1
* [33m2d7f594[m[33m ([m[1;33mtag: 3.5[m[33m)[m simplifying regexps in config samples
* [33me256afe[m made for/if/else constructs more consistent, some code polishing
* [33m64cfebc[m made configurerequest more tidy
* [33m7a095d0[m I didn't knew of c->isfixed, that should fix Jukkas issue with gkrellm ;)
* [33m5052c53[m making it more sure that transient checks will work in any case
* [33m22d8c6f[m stupid me, one needs to set c->{x,y,w,h} in configurerequest obviously ;)
* [33m71857b8[m simplified configurerequest
* [33m6ba400e[m yet another consistency fix of dwm
* [33m35e65ea[m I don't see any reason why we should select for input on override-redirect windows?
* [33md0d986d[m bugfix of bugfix (thx to Sander)
* [33m9685e7d[m fixed a bug
* [33m37f39af[m during writing 2wm.1 I noticed some bugs in dwm.1
* [33mdc9f62f[m removing all EnterNotifys after resize
* [33m7055315[m added pointer warp on drop in resize
* [33mfd995da[m pneubeck pointed out an obvious thing, that a second p = stext + strlen(stext) - 1 is unnecessary
* [33me5765cd[m treating acroread and mplayer floating by default
* [33m8d0e58f[m adapting John Grahor's patch to dwm-3.5
* [33m8fcd1bf[m fixed copyright notice in Makefile
* [33me39e697[m fixed order of Bool declarations
* [33md2dd58e[m added TOPBAR option for making the bar appear what the user likes
* [33mc6fc6b1[m next version is 3.5
* [33m4590d78[m making the  bar appear at bottom
* [33mf577fe4[m Added tag 3.4 for changeset 9ede7b2d2450
* [33m9ed5de0[m[33m ([m[1;33mtag: 3.4[m[33m)[m removed debug flags
* [33m28ffff8[m replaced getproto with a saner function, now old-school artifacts of WM times in the early 90s completely disappeared, no punned pointer warning anymore ;)
* [33m44ef3f5[m yet another fix
* [33mdafbd0d[m simplification
* [33m2ddc787[m implemented aspect ratio support of windows
* [33m7ece30e[m made some changes more concistent
* [33m3d48f33[m got rid of LD (inspired by JGs patch to wmii)
* [33m19fd903[m applied apm's patch proposal, getting rid of XDrawLines
* [33m5732e47[m Added tag 3.3 for changeset 0f91934037b0
* [33m042297b[m[33m ([m[1;33mtag: 3.3[m[33m)[m applied Sander's drop_bh patch
* [33ma5cb80b[m handling WM_STATE seems to make DnD in gtk/qt apps working, well let's handle this in dwm as well
* [33m7e98db2[m regarding to http://plan9.bell-labs.com/sources/contrib/rsc/man.ps the BUGS section should appear after SEE ALSO section.
* [33mbced907[m renamed CAVEATS into BUGS
* [33m82fed98[m Added tag 3.2.2 for changeset d3876aa79292
* [33m2c1db7e[m[33m ([m[1;33mtag: 3.2.2[m[33m)[m prepared yet another hotfix release
* [33mea4827a[m Added tag 3.2.1 for changeset f2cabc83a18f
* [33m55be4d6[m[33m ([m[1;33mtag: 3.2.1[m[33m)[m hotfix release 3.2.1
* [33m1f18466[m applied offscreen appearance hotfix
* [33mb65a1e3[m Added tag 3.2 for changeset 4ce65f61f01b
* [33m87836d7[m[33m ([m[1;33mtag: 3.2[m[33m)[m renamed activescreen into selscreen
* [33mc8a12a0[m implemented Sanders remarks
* [33m71b84c2[m small changes
* [33medb2660[m removed a blank line
* [33m17ec726[m this version should also work with cornercases (like unmanage during !issel, etc.)
* [33m373b11d[m I think this is the best solution of multihead support
* [33m04a2b74[m darker border
* [33mfcd9830[m this variant is known to work, but focus() is ugly - we need in general a better way to handle multihead, this issel-stuff looks awkward (maybe it might be a good idea to set sel to NULL but to introduce a Client *revert which is set if a screen is unfocused, have to think about it further).
* [33mb233089[m applied Sanders all5.patch (thanks for your weekend session, Sander!)
* [33m201c56f[m leavenotify also don't needs the check
* [33m1e051d7[m deciding for focus(NULL);
* [33mddc7960[m replaced XSetBorder.../focus()
* [33mdee5ea2[m yet another multihead fix by Christof Musik
* [33mb1c9f5f[m I prefer BORDERPX=1
* [33ma542bdf[m personally I prefer 2px borders
* [33m96e1b25[m applied a modified version of Christof Musik's multihead patch (though this is not sure if it works in all cases, have to wait for an ACK by Christof)
* [33mcaf5a16[m moved BORDERPX to config.*.h
* [33m936e11f[m Added tag 3.1 for changeset e1c8bef05e6e
* [33m9715ba8[m[33m ([m[1;33mtag: 3.1[m[33m)[m removed erealloc (not used)
* [33m3c35b90[m removed unnecessary bx, by, bw variables
* [33m1d63030[m s/444/555/g - enlightened selected background
* [33m6a5b412[m removed firefox rule from default.h
* [33mfbd3109[m applied new default colors
* [33m3059c9c[m applied sanders patch of my config
* [33m3b18f17[m Jukka, thanks for being faster than me!
* [33m72faa19[m changed restack, to fix undrawed tag indicators
* [33mf8181f6[m removed drawclient and drawall (they performed useless operations/consumed useless cpu cycles)
* [33m0045ad8[m implemented new color scheme accordingly to Sanders proposal
* [33mceea528[m removed mode label stuff
* [33m6c5dc70[m removed client title bar
* [33mae0b4fd[m added missing space
* [33mb3cea4d[m nah the last change feels bad
* [33md296081[m changed incnmaster shortcuts in config.arg.h
* [33m177ed7e[m Added tag 3.0 for changeset 76b58d21ea98
* [33mf679125[m[33m ([m[1;33mtag: 3.0[m[33m)[m removing to allow nmaster=0
* [33m58beead[m this looks better now ;)
* [33me1811c3[m switching to arabic tags
* [33ma24a670[m small fix of initial numlockmask value
* [33md108cfa[m allowing nmaster=0 (I think that's a straight idea)
* [33m92cb5eb[m added Button{4,5} description to dwm.1
* [33m6538265[m added comment to %u in config.default.h, added Button{4.5} support on mode label
* [33m5a5851b[m reorganized
* [33m1d4a24d[m implemented nmaster appearance in mode label (using %u)
* [33ma768ea9[m Added tag 2.9 for changeset 3a5910fac3cc
* [33mc95fe6e[m[33m ([m[1;33mtag: 2.9[m[33m)[m I received Sander's complain just in time ;)
* [33mc751681[m changed status fg
* [33m3a96c9a[m fofofo
* [33m1617b95[m extended default tags to 1-9
* [33m726ae5b[m small grammar fix of dwm.1
* [33m3e11b38[m changed a term in dwm.1
* [33m16ed879[m using shorter tags, using mon instead of cert
* [33m20d7b5d[m roman numerals suck badly, reverting
* [33m11a08b9[m switching to roman tags, I need more tags
* [33mc2b753d[m I inc/decrease on the fly, feels better
* [33m6c76707[m allowing swap() for first master client
* [33me9cfae7[m prevent pop() if first sel == nexttiled(clients)
* [33m7ac0de8[m removed swap(), implemented pop for everything
* [33m0b7c0f1[m preserving c1->snext and c2->snext in swap() as well.
* [33m51f6405[m fixing some minor issues
* [33m6096f8a[m removed the term clients from dwm.1
* [33md939f30[m adding some prevention that master clients get smaller than bh
* [33m8c4623d[m changed shortcuts to M-i and M-d
* [33m0faaba0[m allowing zoom within master area as well
* [33mec7a5ff[m changed plus key to MODKEY-Shift-plus (US-layout restrictions ;)
* [33m98afb7b[m I prefer two master windows by default
* [33m06bae9d[m added MODKEY-{plus,minus} shortcuts (increasing/decreasing master clients)
* [33m0b80d18[m experimental version which allows master clients being increased/decreased
* [33md7ec23a[m fixed comment of drawclient()
* [33m2cf8ef9[m switching bakc to my previous color favorit
* [33m184471b[m renamed drawtitle into drawclient
* [33m21898c6[m using more thinkpad compliant colors
* [33m6a9300e[m changed arg's color scheme
* [33mac24f13[m corrections
* [33mcb4aa5b[m next version will contain updated copyright notice
* [33mbeac539[m Added tag 2.8 for changeset 107719a9ce3bd0c79f9f1f626596eb338a276561
* [33mb5d297f[m[33m ([m[1;33mtag: 2.8[m[33m)[m fixed cleanup, using clients instead of sel
* [33m9056d7e[m changed comment of updatesizehints
* [33mebd17e4[m renamed updatesize into updatesizehints (thx to Sander for this hint)
* [33m7e59c89[m small simplification to dotile() (thx to Ross for this hint)
* [33m9e4e4d9[m migrated arg's config.h to new dmenu command line options
* [33m71fd06f[m added Solaris hints
* [33m58e6866[m Added tag 2.7 for changeset 21951c0dfbae5af68ed77821a4d87253ee91803f
* [33mc7da124[m[33m ([m[1;33mtag: 2.7[m[33m)[m applied Sanders patch
* [33m21bd90d[m fixed man page, status bar displays EOF instead of "broken pipe"
* [33mc8f96b5[m added the java odyssee to CAVEATS section
* [33mded6036[m removed Client->grav
* [33m629647d[m removed gravitate for the moment
* [33m4ca3d86[m disabling configure() during resize
* [33m069e7a6[m made gravitate effectless, waiting for complains ;)
* [33mac6e34e[m fixed diagnostic error message
* [33ma308b75[m removed the hardcoded fixed fallback, it is useless in non-Latin1 environments
* [33m630e7ff[m we don't use the term clients anymore, windows is the better term
* [33m3764ab4[m Added tag 2.6 for changeset 5308dd22b6ee8e3218c81d9e7e4125f235bb5778
* [33ma3319c6[m[33m ([m[1;33mtag: 2.6[m[33m)[m found compromise for fonts
* [33m66c699a[m nah, people should define 'fixed' to be compatible with their locale
* [33maaf1e44[m using a UTF-8 capable fixed font
* [33m1ef2307[m switching to uxterm again, I get kretze from this urxvt crap
* [33md42c3ba[m with this patch everything works fine for me
* [33m4b06155[m don't use Xlocale crap, let's use locale.h instead
* [33m857d825[m using the portable Xmb+UTF-8 way of life, will see if this works well...
* [33m6b34535[m improved the memory leak prevention
* [33mab3b3a8[m making terminus more explicit a regular font (otherwise olique font might be used in some setups like mine).
* [33m71b82fb[m also setting LC_CTYPE only
* [33m9bd9ea4[m enforcing using fontsets even if they are incomplete for some encodings
* [33m9996439[m Added tag 2.5.1 for changeset c7f84f23ec5aef29988dcdc4ec22a7352ee8f58e
* [33m7009ebf[m[33m ([m[1;33mtag: 2.5.1[m[33m)[m hotfix of a serious crashing bug
* [33m760e23d[m Added tag 2.5 for changeset dcbbfabc8ecc5f33a6cc950584de87da1a368045
* [33mc53d9d5[m[33m ([m[1;33mtag: 2.5[m[33m)[m applied Manuel's regex patch
* [33m7739e6b[m made squares equally sized, and 1px bigger
* [33m4881857[m if client is focused, the emptysquare don't needs to be drawed
* [33mc73d5cb[m and the winner is
* [33m6458803[m sander1 proposal
* [33m6e72d78[m dood
* [33m4e926a9[m darkening the fg colors somewhat
* [33m4ba3cfa[m less obtrusive indicator (only a top line)
* [33me655e8a[m final2 indicator
* [33mc34e4e4[m removing the -1 on final indicators, looks cleaner
* [33ma678ee6[m final indicators
* [33m49f0ee3[m changed things like I described in last mail
* [33m0c9d9a3[m improved tag indicator
* [33m89e1acb[m removed viewall signature from dwm.h
* [33mc2ed26b[m next version will be 2.5
* [33m42fd392[m removed viewall(), replaced with view(-1); added tag(-1) to tag a client with all tags (new key combo MODKEY-Shift-0)
* [33me06447e[m Added tag 2.4 for changeset 32b246925086910d63147483160281a91a47479f
* [33m683dabe[m[33m ([m[1;33mtag: 2.4[m[33m)[m extended dwm.1 with last change
* [33m3aff961[m togglefloat should only work in dotile mode (thanks to Sander for this hint)
* [33m0a915eb[m applied Alex Elide's tricky patch, thanks!
* [33m19dcbc5[m returning to old Key struct
* [33md2a4952[m applied Szabolcs Nagy's patch (thank you!)
* [33m0c97b21[m applied patch by Jukka
* [33m19390b1[m changing Key.func into Key.func[NFUNCS], this allows sequences execution of functions per keypress (avoids implementing useless masterfunctions which call atomic ones)
* [33m8dc8605[m added man page entry
* [33m46d5f9d[m added togglefloat to hg tip (i consider this useful for some cases), using MODKEY-Shift-space as shortcut
* [33m35e96b8[m applied Jukka's patch preventing some cornercases and making the EOF error message correct
* [33m2210ea7[m applied yet another proposal of Manuel
* [33m61a1910[m applied Jukka's sizeof K&R compliance patch, applied Manuels' last-line printage proposal for stdin reading.
* [33m27ef735[m applied Jukka's stdinread patch
* [33m2b35fb6[m next version will be 2.4
* [33m478f6f9[m applied Manuels patch (thanks to Manuel!)
* [33m44411d2[m small fix of man page
* [33ma2175cf[m Added tag 2.3 for changeset 719b37b37b0df829d7cf017ac70e353088fe5849
* [33m4606d21[m[33m ([m[1;33mtag: 2.3[m[33m)[m using the term 'indicated' instead of 'higlighted'
* [33md37d0f2[m updated man page with the bottom right corner indicator
* [33m321e8d5[m fififif
* [33m78f4b51[m added a similiar patch to Daves solution to indicate if there are clients with a specific tag
* [33m7d168a2[m returning to old bar colorization behavior, like sander proposed for consistency reasons
* [33m931e712[m applied Gottox patches
* [33m4ec0420[m using iso10646 explicitely in arg's config.h
* [33m82ddba8[m Added tag 2.2 for changeset 7e92f58754ae6edb3225f26d754bd89c1ff458cf
* [33m52a8cc8[m[33m ([m[1;33mtag: 2.2[m[33m)[m nah reverting to my prev style, that's really the best
* [33md175df8[m applying aluminium style for arg's config.h
* [33mb003a35[m applied Gottox' windowarea patch
* [33mdf1a0f9[m using a more blue-ish color...
* [33m5b07b85[m making the selected color more lightning
* [33mf320cd2[m next release will be 2.2
* [33mf78c16f[m applied Jukkas patch
* [33m0c5f47e[m Added tag 2.1 for changeset a2c465098a3b972bbed00feda9804b6aae1e9531
* [33m4b5b3d9[m[33m ([m[1;33mtag: 2.1[m[33m)[m renamed resizecol into resizemaster
* [33m2cce4b9[m applied Gottox patch to simplify the resizing of col, instead of resizing the current area, it only resizes the master area in the future (seems more predictable)
* [33m8e6eb52[m Added tag 2.0 for changeset 12deea36603da407e3f32640048846a3bd74a9ec
* [33m04b633d[m[33m ([m[1;33mtag: 2.0[m[33m)[m make sure that changing sx has no impact on snapping
* [33mb76561a[m in a 1920x1200 setup 40 pixels of snap value are much better than 20
* [33m51c7589[m fixed stupid bug of snap-to-screen
* [33m9978538[m changing snap priority
* [33mdc1690c[m removed useless abs() calls
* [33mb661426[m added screen-border snapping in floating mode, feels quite well
* [33m91e569c[m and another fix
* [33m0f395c1[m applied sanders try2 patch
* [33m2b13e74[m applied sanders max size fix
* [33m0982e47[m stupid urxvt needs bg to highlight selections in a sane way, though that makes sense to some extend
* [33mb93ebcf[m reverting to original
* [33ma08d83b[m applied sander's config.*h nitpick patch
* [33m2b7c275[m some other change
* [33m040d0f4[m apply small fix to prevent apps like mplayer wandering when toggling fullscreen
* [33m724f35a[m forgot to use -tr, which actually prevents the ugly flicker (using xsetroot -solid black as root window pixmap to make this work nicely)
* [33m6f3872e[m using MASTER 600 again, it is definately better, and using urxvtc for the moment (it doesn't flickers on refreshes, but this is not because of Marc Lehmann, it is because of the original rxvt code)
* [33m87324e6[m changing MASTER in config.arg.h from 600 to 550 per thousand
* [33mc2b908f[m my new 1920x1200 Z61p arrived, now I can use terminus in a sane way...
* [33md7734f9[m moved MOUSEMASK into event.c (not used in other places)
* [33m8b68890[m now being at v2.0
* [33mb60406c[m using lsx instead of Jukka's shell construct
* [33mce9a993[m hotfix
* [33m720b2ab[m Added tag 1.9 for changeset a5567a0d30112822db2627a04a2e7aa3b6c38148
* [33m5983c00[m[33m ([m[1;33mtag: 1.9[m[33m)[m do* has no Arg arument anymore (never called directly)
* [33m6651dd7[m code polishing, removed unnecessary newlines
* [33macdea31[m yet another small fix and simplification of dotile
* [33m10885d3[m removed the stack position stuff
* [33m1c1d09f[m small boundary check fix
* [33m0384fae[m changing MASTER value from percent into per mill
* [33m6cca399[m Added tag 1.8 for changeset c71952fa3c7ca848ec38a6923b5c6d0e18fff431
* [33m69408d3[m[33m ([m[1;33mtag: 1.8[m[33m)[m simplified dotile(), removed misleading line
* [33m4aea423[m final fix for man page
* [33m6fc8a63[m keep master ratio on resizecol -> arrange
* [33m2583a7c[m yet another simplification of dotile()
* [33m0ef6e31[m simplified dotile()
* [33m7c052b3[m applied resizecol fix by Jukka
* [33md9c475d[m Button3 click on mode label toggles stack position now
* [33mc8e5733[m applied dave's highlight patch for big fonts
* [33mc045459[m using ff tiled again, seems to work perfectly with new bottom stack
* [33me0f64e6[m applied ality's hardcode-0 patches
* [33mdddd58a[m added symbols for different modes
* [33m010fd21[m removed useless updatemaster
* [33m1802fad[m documented the new behavior in man page
* [33mf833d10[m fixed small offset issue
* [33m7225c99[m fixed the z-layer issue described on mailinglist
* [33m3617893[m removed the direction flipping
* [33mad0da9a[m small fix of a corner case
* [33m6646468[m small change
* [33mfee8df6[m added the new dotile as described on ml
* [33m8fa47ac[m prelim of dotile()
* [33mb427a2c[m I changed sanders patch to fix the ff issue to be simplier, though it needs testing if this really fixes the issue
* [33m14d05e7[m first step to a more flexible dotile() algorithm
* [33ma118a57[m renamed column into area
* [33m02cea3b[m small change to README
* [33m1c2d673[m applied Jukkas patch
* [33mc34df2c[m Added tag 1.7.1 for changeset d5ad819f2a66a40fa75dd2e44429f3bfc884d07b
* [33m6092aa9[m[33m ([m[1;33mtag: 1.7.1[m[33m)[m fixing the settags issue, preparing 1.7.1
* [33mc9cc2b3[m removed an unused var
* [33mb39d0c5[m Added tag 1.7 for changeset 4dbdb61c8b8ce21dee5c7050a6b103855964ed20
* [33me87bed6[m[33m ([m[1;33mtag: 1.7[m[33m)[m updated README
* [33m4ee05b3[m small change
* [33me81eb46[m added slight error check to getcolor
* [33mf315832[m small fix
* [33m97ced11[m changed order of colordefs in config.h's, changed config.arg.h to fit to new dmenu
* [33m4d6c4d3[m removed useless debug info
* [33mb4d53bf[m added configure(), but this doesn't really fix those frking broken SDL apps
* [33m67bc08d[m slight change of event handling order
* [33mbcb07de[m simplified mouse resizals
* [33m7d7cde0[m applied sanders jukka patch
* [33m6b25d06[m applied Jukkas patch
* [33mcff951c[m removed all dotile checks
* [33m114cc3e[m applied Jukkas remark (dunno if this is correct though)
* [33m3c4b767[m applied jukkas patch
* [33m6de149e[m man page fix
* [33mda909dd[m ismax toggling on mouse based action
* [33m67986e8[m hotfix
* [33m346bdea[m small change to achieve Jukka's last proposal
* [33m05c10c5[m fixed issue pointed out by Jukka
* [33mb2cb925[m patched resizemouse according to sanders remark
* [33m9fb6502[m small man page fix
* [33m9eb226f[m sander check this
* [33me34c4ea[m slight change to config.arg.h (I use ff floating)
* [33m9e75bcf[m updated man page
* [33md800ec0[m implemented the maximization as I described on the mailinglist, this feels better to me.
* [33mbda53ac[m reviewed client.c
* [33m4230932[m reviewed util.c
* [33mf17e898[m fixed a nuance in dwm.1
* [33m886b208[m improved intro comment in dwm.h, updated config.mk
* [33m551d6bb[m some simplifications to intro in dwm.h
* [33md504005[m Added tag 1.6 for changeset ad3fa2d185426c51fd5deceae809770363f8d33c
* [33m2511b5c[m[33m ([m[1;33mtag: 1.6[m[33m)[m added visibility check to enternotify as well
* [33m28aba06[m offscreen client appearance fixes
* [33m8e37c78[m focus() enforces visibility of a client if not NULL
* [33mca68975[m removed useless inclusion
* [33m529be52[m fixed executing of dmenu output to handle args correctly
* [33mca65478[m removed a bunch of lines through making function signatures more consistent with my style ( { does not belong to a new line, if function args are single-lined)
* [33ma1e9362[m some more simplifications of intro comment in dwm.h, this should suffice for comments in dwm
* [33mcbfc69e[m made introduction comment in dwm.h shorter
* [33m1d7674b[m applied Christof Musik's multihead patch for a pathologic cornercase
* [33me6cc223[m added a general comment to dwm.h how dwm is basically organized
* [33m868159f[m some other simplifications
* [33mb597fa4[m fixed some other comments, now also the code side seems to be at a level to be reviewed by experienced programmers
* [33md2d394e[m small change to comments, renamed two set* functions in client.c into update*
* [33m438beea[m small fix
* [33m281f098[m added some comments
* [33m6ff346b[m Added tag 1.5 for changeset 728c9089b079721b43c3347124639a29baa22a97
* [33m0925dd5[m[33m ([m[1;33mtag: 1.5[m[33m)[m applied sanders patch of not manipulating sel
* [33m6f20315[m really small changes to dwm.1
* [33m2e68f22[m hotfix
* [33m8aa860d[m simplified unmanage
* [33m15abade[m using a global stack for focus recovery on arrange() - seems to work great
* [33m7ab8c87[m made markups in dwm.1 more consistent
* [33m4ff8f71[m small addition to dwm.1
* [33md22abee[m this patch keeps track of global z-layer order of clients which are floating or if floating mode is enabled
* [33ma33150e[m no this is better
* [33mfd00b3a[m does this preserve z order for anthony?
* [33me8389a4[m maybe this might work
* [33m6078d75[m Added tag 1.4 for changeset 3cff9403766bf83a9fc2a0aef230115d68de2a8e
* [33m57c49fe[m[33m ([m[1;33mtag: 1.4[m[33m)[m prepared dwm-1.4 update
* [33mc60de1a[m drawstatus even if no client exists
* [33m69b738c[m sanders solution is convincing and elegant
* [33mda0b2a2[m seems to preserve floating client z-layer order (even with reorder() calls)
* [33m2378a55[m Added tag 1.4 for changeset a6b8994af16491220db0199623bd57d061e06143
* [33mf18ed61[m small fix
* [33mf6656ff[m made args mode symbols the default ones (the default ones look too ugly)
* [33maaad7bf[m moved transient_for tag inheritance to settags
* [33m0915da8[m no, reodering floating clients definately breaks the manage() policy which attaches all clients zoomed (otherwise higher-weight clients couldn't be attached zoomed, which sucks)
* [33m0d0e8bd[m no, ordering floating clients at the end seems better
* [33m838a1ff[m fix
* [33me1315fd[m this makes sure the issue mentioned by sander
* [33m52a3ab1[m fixing zoom
* [33ma82e7b7[m fixing two off-by-ones
* [33m0ed0fa4[m ach ich will auch Alt-s
* [33mec85fdd[m applied checking existance of >2 tiles patch (proposed by sander) to zoom and resizecol
* [33m3a1343a[m renamed resizetile into resizecol
* [33m9066ee2[m well ok, added Mod-s to default bindings (however, I don't need it)
* [33m40bd21c[m s/growcol/resizetile/g
* [33m4633fbe[m right, multihead issue is not involved with growcol
* [33m2506003[m hotfix
* [33mc7ae633[m applied a fix related to Sanders remark to growcol
* [33meac0488[m sanders toggletag patch is much more elegant
* [33m6499fc4[m I really need column growing, now pushing upstream
* [33m04f27a5[m don't access sel in restack without checking for NULL (multihead crashing bug)
* [33m1b3903d[m fixing c->weight handling
* [33mcc05093[m removed some useless tags
* [33m6436dd4[m after 1.3
* [33m26c50c7[m Added tag 1.3 for changeset f5f5cbf016a94b48a8fe9c47f0736e96d166d5d4
* [33m01d13b0[m[33m ([m[1;33mtag: 1.3[m[33m)[m retagged
* [33mf15f45a[m simplified manage
* [33m1b2e149[m removed html crap
* [33m6136640[m Added tag 1.3 for changeset dd44dc937e8b0a46abf1a15a333dba5304e4fe89
* [33m95d8423[m hotfixing with sanders hint
* [33mde6411c[m Added tag 1.3 for changeset 6413ea66b1c2496cfc2173fe58df67cb965eb1da
* [33me316cf5[m fixing the issue that new clients appear lowered
* [33mc107db5[m removed unused vars
* [33md39d000[m reducing focus calls (sanders patch)
* [33m26157e6[m applied Sanders max_and_focus.patch
* [33m6d22782[m simplified buttonpress
* [33m1836b67[m applied sanders patch
* [33m924a088[m reorder was misssing in Ross version of viewall
* [33mbab575c[m changed shortcut into Mod1-0
* [33mdaae3bb[m added viewall to mainstream (only Ross Mohns version, not the toggle)
* [33m05fbbbd[m implemented Button2 press on tags for toggletag on the focused client
* [33m4c368bc[m applied sanders patch to remove unnecessary commit()
* [33m9927b9e[m small fix in config.arg.h
* [33m1b492df[m Added tag 1.2 for changeset e3179ce2b90451d2807cd53b589d768412b8666b
* [33m140be1b[m[33m ([m[1;33mtag: 1.2[m[33m)[m prepared 1.2
* [33m79259ac[m now using Salmi's menu command
* [33m5a3bea2[m removed a warning reported by Jukka
* [33m30d9285[m simplified configurerequest
* [33m70a3e62[m now dwm enforces max screen size also in tiled mode on non-floating clients which are maximized
* [33m6828fba[m fixed
* [33maa1bda8[m configurenotify remembers max geom now, and restores this if necessary, however it accepts to touch the max size on configurerequest, this shouldn't break fillscreen apps (tested with mplayer)
* [33m157ea53[m applied patch similiar proposed by dave tweed
* [33mc3c94c0[m improved selection policy
* [33m9d73909[m still something wrong with reorder()
* [33m016c541[m this algorithm seems to keep order for any scenario
* [33m5056bb9[m fix client position in list also on tag and toggletag
* [33m8a6679b[m added attach/detach functions which don't attach at the begin of list, but at the slot of a first match of the tags of a client
* [33m7b6d5ff[m removed crappy variables
* [33m8468509[m changed config.arg.h - I really need the 4th tag
* [33m4e6c513[m updated html page
* [33mdb9cda6[m Added tag 1.1 for changeset 44a55e6e46bf6c231780b09d919977d6f01083de
* [33ma50b15a[m[33m ([m[1;33mtag: 1.1[m[33m)[m added a comment to spawn
* [33m0a25fe9[m applied sanders focus_ patches
* [33m2dd5212[m applied sanders somepatches.patch
* [33m00e95e1[m oh frking dear big font...
* [33m0a07591[m term enlightened
* [33m5cf362c[m switching to darker colorscheme with larger font
* [33m413be11[m patched arg.h
* [33m8233dc8[m new stuff
* [33mafa8b3b[m switching to dark colors again
* [33mc518345[m updated man page of dwm
* [33mafe6ac9[m changed order of options
* [33me995c1b[m trying a different configuration
* [33me369292[m removed small 1px gap, somehow without it things feel better
* [33m03128f7[m oops
* [33m7d4a5e6[m fixed typo
* [33m41ba7a7[m s/TILED/TILE/g
* [33maa471f2[m removed a bunch of lines, made mode symbols configurable
* [33md37dfa1[m changed symbols for float/tiled mode, added mouse-driven mode toggle to buttonpress()
* [33m9f35cc5[m small fix to separate client title from right-most tag
* [33mf1fe19b[m restored config.arg.h
* [33mb55bd70[m new color stuff/new rendering stuff
* [33m9833610[m back to 3 colors
* [33mde7fc00[m fixed
* [33m2e0c767[m 3->4 colors
* [33ma5379e9[m Added tag 1.0 for changeset bbc98e77ae89a7c9232a5be0835f60ea00d8036e
* [33ma039d51[m[33m ([m[1;33mtag: 1.0[m[33m)[m prepared dwm-1.0
* [33m60b3dce[m yet another fix
* [33mc2ac851[m small man page fix
* [33mc976bc6[m found less intrusive way
* [33m2e834e9[m changing tag indicator through underline
* [33m77e5f31[m black on light is really better, I notice this after all
* [33m7e597ae[m updated man page
* [33mc39df91[m applied tag drawing change to man page
* [33maf1158d[m implemented right tag drawing in the status bar and titlebars
* [33mb739721[m removed a blank line
* [33m7711ab6[m eliminated sentinel warning
* [33md370c32[m small fix of man page
* [33md6a6eca[m implemented class:inst:title matching
* [33m39ffc18[m applied zero_to_five patch
* [33m3e972ec[m tags appear in the left again
* [33mb5159df[m separated setup stuff into main.c:setup() - this makes main() more readable
* [33m07c2659[m updated man page
* [33mdc83b9e[m titlebars contain tags in the right now
* [33m8b4bc82[m fixed default key bindings (indexes of tags were screwed up)
* [33m0ff8065[m rearranged getproto
* [33m352e1b4[m removed winprop (merged into getproto)
* [33maa13727[m separated several functions into view.c
* [33m5950286[m removed DEFTAG
* [33m6a3ae5e[m removed badmalloc (thx for the pointer to Uriel)
* [33m8c334ee[m rxvt is quite slow under OpenBSD
* [33mf60fe2a[m font fix
* [33mb112257[m slight change of my config.h
* [33meb88adc[m fixed
* [33m950a1ab[m windows which have set transient_for hint inherit the transient_for window tags now
* [33m1b9fe55[m after switching to OpenBSD again, I switched back to a saner color scheme
* [33m2272df9[m applied Sanders focus_* patches, removed the unnecessary clean-prefix from the new function names
* [33m08d85d6[m small renamings of two static functions
* [33mb439892[m small changes to dwm.1, rearranged order within main event loop
* [33m2eebebf[m applied Sanders patch
* [33m8c1fffe[m made a new client position strategy similiar to that one proposed by Sander, but which takes top bar into account
* [33m5e9acbc[m fixed a bug reported by sander
* [33ma420cea[m applied the shorter xprop command
* [33m0e1c649[m centering apps only if transient_for is not(!) set
* [33m67c2124[m fixed issue Sander reported
* [33ma635743[m corrected order of cleanup code
* [33mb5c2412[m condition was insufficient
* [33mad2e77d[m fixed issue reported by sander
* [33ma20b10d[m added general centralization rule for new clients (works around various borken apps)
* [33m4cc0551[m removed leading ;
* [33m56130c3[m added sample command to config.default.h to highlight how to query class:instance info with a one-liner of shell commands
* [33m14f7380[m applied another config.mk patch made by sander
* [33m727449d[m we close stdin as well
* [33m80bf2aa[m simplified sort | uniq into sort -u (on my boxes all sort support -u)
* [33mb9cd0c4[m fixing small bug in config.mk
* [33mf77a871[m adding forgetten whitespace
* [33m65dfe8f[m added gmane archive to dwm.html
* [33me3bb595[m Added tag 0.9 for changeset fae61afa861755636c4a1070694209ace8efbb6c
* [33ma1682b8[m[33m ([m[1;33mtag: 0.9[m[33m)[m prepared dwm-0.9
* [33m24d91e3[m extended cleanup
* [33mce04a66[m applied Sanders changes to config.arg.h
* [33mdf74b26[m applied jk_to_tab patch
* [33mb6ad663[m changed main event loop
* [33mee31e38[m removed NUMLOCKMASK, added dynamically calculated numlockmask instead
* [33m4423346[m added Sander to LICENSE (since he has contributed/revised big portions)
* [33mdfa5ea6[m applied viewsel.patch
* [33m3e06ede[m applied sanders man page patch, removed button2 from bar click
* [33m78b050c[m applied sanders tag()/toggletag() fixes
* [33m4ad20ff[m fixed
* [33m57e6e3b[m added missing arrange
* [33m19da197[m changed replacetag into toggletag
* [33m666fae9[m added some flicker prevention
* [33m823fb11[m remove unnecessary XSync
* [33mdb1d62e[m changed order of selecting input at root window
* [33md26ffc7[m removed finished message
* [33m0f3acce[m added mappingnotify event for kb refreshes
* [33m9eef9f7[m removed unneecessary crap
* [33maff4c78[m applied the saner patch (removed the pathetic one)
* [33mfe3dfbb[m pplied Sanders appendtag patch
* [33m2ffdc19[m some other small fixes
* [33m0fe52c6[m removed ungrabkeys again (because of sander's mail)
* [33m28a5219[m fixed string cutting
* [33m2c0d1cc[m fixed a core dump
* [33m375a251[m implemented ungrabkeys() which is called in cleanup()
* [33md4b7a9a[m implemented restack behavior (floats are on top in tiled mode)
* [33m4d67199[m fixed string cutting in draw.c
* [33m95766d6[m applied Sanders LD and resize patches
* [33m4cb78a1[m removed viewnext/viewprev
* [33m2c66b42[m supplying NULL args in select
* [33me571de8[m reducing ConnectionNumber calls to a bare minimum
* [33m4bb89e2[m updated man page, added CAVEATS section
* [33m349cada[m made shortcuts like proposed by Sander, renamed viewextend to toggleview (more clear)
* [33m292ccc4[m implemented viewextend and added M-S-C-n shortcuts for extending the current view... updated man page (works great!) nice feature
* [33md7413ff[m implement multi-tag selection through button3 click on the specific tag
* [33m50729a2[m after some days of experimenting with grey background, I finally give up and switch to white on black ;)
* [33ma3e3f0b[m applied Sanders fixes to dwm.1
* [33m45aea23[m fixed dwm.1, added Mod1-Shift-c (was missing for an odd reason)
* [33m975b459[m simplified drawtext
* [33m2b35fae[m updated dwm(1)
* [33m84818bd[m upgraded version info
* [33m895902b[m applied Sander's patch as well
* [33m7d4184d[m realized that client focussing through the bar is pretty useless, better is sloppy view focussing for B1/B3 as well instead
* [33m8278f0a[m implemented focusprev on button1 press in the bar, and focusnext on button3 press in the bar
* [33md396963[m simplified unmanage
* [33m735ca9c[m removed the if(clients) check from popping code
* [33m4ee661d[m added dwm favicon
* [33m9fce821[m applied Sanders zoom_update patch
* [33m6521c2d[m respecting inc hints in floating mode on togglemax
* [33m9ee9ce7[m reverting last patch, that sucks, I don't care about retarded apps like gvim
* [33m9d39da6[m togglemax repects inc-hints (this way gvim can be toggle'maxed as well)
* [33m0228dcd[m applied grammar correction by ILF
* [33m3d35ea9[m Added tag 0.8 for changeset cd15de32e173f8ce97bfe1c9b6607937b59056b4
* [33m0680c76[m[33m ([m[1;33mtag: 0.8[m[33m)[m prepared 0.8
* [33mc3e5f5c[m updated html
* [33m1c620d2[m fixed the issue reported by sander (gaps at left columns button due to round-offs)
* [33mfde45eb[m applied sumik's multihead patch
* [33m4bd0d33[m applied sander's patch
* [33m0025572[m readded border color, this sucks least
* [33m4b0328f[m drawing border with fg color
* [33m30561a0[m removed unnecessary border color
* [33ma4c4998[m swapping my default colors (bg with fg)
* [33m8e053b6[m made terminals darker, that is better indeed
* [33mb79b5fa[m disallow zoom on maximized clients
* [33mc53f0fc[m added zoom on Mod1-Button1 on managed clients only (there is no moving possible)
* [33mc225e1a[m removed NET_ACTIVE_WINDOW handling
* [33m92e55c7[m implemented NET_ACTIVE_WINDOW support
* [33mc86f131[m fixed typo
* [33me943234[m it always takes a while until one sticks to a colorscheme, but this one feels well
* [33m9fc24e3[m default colors are best
* [33mcac467d[m without borders it looks cleaner
* [33m04f17d2[m red is easier to my eyes with ffffaa bg
* [33mdff15a0[m using a better colorscheme (ffffaa is the best background for black)
* [33m42277b1[m applied Sanders tiny patches
* [33m095f9e1[m removed some "
* [33m9fbb2eb[m I really only need 3 tags
* [33mdbcf87c[m added a trailing '.' to shortcut descriptions in dwm(1)
* [33m4250c26[m changed signature of drawtext
* [33me48de30[m applied grabbing-- and shell_minimal
* [33m1f0060c[m updated screenshot section
* [33mc732cc9[m changed font size, I'm not blind...
* [33m4e2c5b5[m small fix of a comment
* [33md9386a0[m typo fix
* [33m66e16c9[m applied Sanders man page/Makefile patch
* [33m6a8e176[m settle with grey
* [33m632c7f3[m next version is 0.8
* [33m045f184[m made my colors tasting better with the background
* [33m45d16d0[m status box should have a border in my eyes
* [33m525c5ff[m next attempt for w on black switch
* [33m5952157[m Added tag 0.7 for changeset 3fb41412e2492f66476d92ce8f007a8b48fb1d2a
* [33mf777d21[m[33m ([m[1;33mtag: 0.7[m[33m)[m prepared dwm.html
* [33m82064af[m added stripping to dwm target in Makefile
* [33md54444c[m changed getproto, maybe that might fix the killclient issue reported on the list
* [33m525ef3c[m applied endless loop prevention on zoom()
* [33m5ef6ef1[m updated man page
* [33mf4208e7[m small fix of the last commit
* [33mecc95c9[m using -Os again, zoom is ignored in floating mode or on floating clients
* [33ma207949[m mouse grab needs also to grab for combinations of numlock/lockmask
* [33m86d1224[m slight fix
* [33mb098c94[m small performance tweak ;)
* [33m6a39a49[m fixed xterm font change (all other related apps should work fine with this fix as well)
* [33m3d73084[m fixed view-change bug reported on the list
* [33m12b1d43[m no need for -g anymore, regexp matching works now
* [33m1076161[m fixed dmenu link (thx to deifl)
* [33me21d93b[m switched to regexp matching for Rules
* [33mf504aea[m fixed a bug in dmenu call
* [33m9955ddc[m using execl now, argv changed, using cmd and const char defs directly in the KEYS struct
* [33m0dfe729[m added dmenu to dwm.html
* [33m8f698bd[m small stylistic fix
* [33m99b126d[m removed CONFIG
* [33ma2d56f6[m make config.h not a time dependence
* [33mdb876f9[m removed rm config.h from clean
* [33m05a618b[m added gmake compliance
* [33m72608f0[m s/tag2/two/g
* [33mbba044d[m applied Jukka's diff
* [33m4d55eee[m applied Sanders Makefile patch
* [33md41b232[m stylistic chnage
* [33mb355755[m removed TLast tag enum, now tags is simple defined as char *[] array, the rest is calculated correctly, rules take an int array for the tags
* [33m666b456[m hotfix of settags
* [33m7315bb0[m using SRC instead of *.c
* [33mf80688f[m changed the files included in make dist
* [33mdc5c070[m applied Sanders doc changes, added a PHONY line and changed the output of config.h creation somewhat
* [33m8cc7f3b[m changed Client->tags and Rule->tags to be Bool (I'll also try to remove the TLast enum)
* [33m5d3fd37[m implemented the idea presented by Sander for dwm target
* [33m1bf0c4a[m changing MASTERW value from 52 to 60 (in both, default and arg), I feel this is better now
* [33m863656d[m fixed a type in README, and patched config.mk
* [33mf1a34ae[m updated dwm.html
* [33m3000cad[m Added tag 0.6 for changeset c11f86db4550cac5d0a648a3fe4d6d3b9a4fcf7e
* [33m0f8249f[m[33m ([m[1;33mtag: 0.6[m[33m)[m removed config.h (stupid hg)
* [33mb515765[m removed the CONFIG variable from config.mk, renamed config.h into config.default.h, after first clone/extract one needs to copy config.default.h to config.h, that is easier than always heavy typing make CONFIG=blafasel
* [33m85e6d59[m added Acroread.* and MPlayer.* to config.arg.h rules
* [33m95e8d12[m made fullscreen apps working fine in floating mode (there is no sane way to make them work in tiled mode, thus I switch to floating mode if I run such kind of app), also fixed the xterm issue reported by Sander
* [33ma55f0e1[m new stuff
* [33m0cf3ba0[m dwm is now exit, if stdin is closed due broken pipe
* [33m1d85225[m implemented focus on enterwindow on titlebars
* [33m3af6434[m applied Sanders patches (numlock2)
* [33m5787141[m reverting to old resize policy
* [33m5202185[m new resize stuff (using XConfigureWindow instead of XSendEvent)
* [33m080a38d[m renamed WM_PROTOCOL_DELWIN into PROTODELWIN
* [33mab7a11c[m renamed ARRANGE into DEFMODE
* [33md8675f6[m small fixes to dwm.html
* [33meff4478[m simplified README
* [33m8168335[m removed 1 missing LOC
* [33mb38905b[m removed 5LOC
* [33md9a6a3b[m removed artefacts of single-linked list (thanx to Jukka, I must have been mad)
* [33m7c2e3bb[m cleaned config.*h to prevent some confusion
* [33mb01a51a[m saved 2LOC
* [33m77f8c07[m uppercasing all define'd values (uppercase-prefixed should only be enum field qualifiers)
* [33m33b4821[m fixed config.h files
* [33ma73a882[m centralized/externalized configuration to config.h
* [33m57416be[m applied Cedric's NumLock patch
* [33m1b63f83[m applied Jukkas prev/next patch with XK_{h,l}
* [33m7b5638f[m applied Sanders patches
* [33m937cabf[m committed a patch which fixes the hints of Jukka
* [33mdeba506[m updated html
* [33m956113b[m Added tag 0.5 for changeset 22213b9a2114167ee8ba019a012e27da0422a61a
* [33mdb98a7d[m[33m ([m[1;33mtag: 0.5[m[33m)[m prepared 0.5
* [33m0464e42[m some cleanups/fixes inspired by Jukka Salmi's feedback
* [33m4970ef9[m simplified main.c, switching back to single urxvt usage
* [33mf85b163[m s/sleep 5/sleep 2/
* [33m2b66f7a[m changed the status info README hint (more simple now, no extra script necessary)
* [33m67b3083[m s/0.5/0.6/ - my steps are wider than the reality
* [33m0c7bcc2[m applied sanders maxfix patch
* [33m98c6a92[m added a note how to achieve status info in the bar
* [33mba59bc8[m preparing 0.6 which will be available in the evening after sanders patch approx.
* [33mcd8d8e1[m sanitization of several clunky stuff, removed heretag (rarely of use), simplified pop(), changed shortcuts to always contain MODKEY
* [33m04eb016[m applied sanders no_sizehints for tiled mode patch (thx!)
* [33m0a43420[m serious mistake in pop() (forgot to set c->prev to NULL on pop)
* [33m72707c2[m using double-linked list in order to get correct prev focus handling
* [33m06dc514[m added yet another CUTOMIZE tag
* [33m2b5553b[m cleaned the CUSTOMIZE flags
* [33m4688ad1[m made status bar drawing more robust, implemented togglemax and togglemode, works quite well
* [33mdc5d967[m cleaned up code
* [33mfe3756c[m Added tag 0.4 for changeset eb3165734f00fe7f7da8aeebaed00e60a57caac9
* [33m01b151f[m[33m ([m[1;33mtag: 0.4[m[33m)[m prepared 0.4
* [33m8bb4a93[m using O3 instead of Os, binary size still < 40kb
* [33m5ec04b7[m fixed version in man page
* [33m3657eae[m yet another html patch
* [33m9291283[m updated html
* [33meccd02d[m makefile now sets permissions for executables and man pages
* [33m1173723[m removed c->f{x,y,w,h} and c->t{x,y,w,h} in favor for the new rule handling remembering two kinds of geometries is unnecessary, removed the randomized (x,y) setting on dofloat startup, was kind too random und unpredictable
* [33mbcaf6a7[m implemented regexp matching for rules
* [33mf95eed3[m applied Jukka's patch with s/ModKeyMask/MODKEY/g
* [33m1eaffa3[m removed TODO, because dwm is nearly finished
* [33mb1697e8[m reapplied my default keybindings
* [33m801d11c[m alternate dwm.png
* [33m1b855fc[m Added tag 0.3 for changeset 7e66082e5092fb0bccd18a3695a0bec52c80fdb2
* [33md34b4c7[m[33m ([m[1;33mtag: 0.3[m[33m)[m some changes in the html page
* [33m1f9614f[m prepared 0.3
* [33m4491bdd[m fixed the bug mentioned by Sander
* [33m8af1d97[m refactored Sanders code somewhat
* [33m79cd408[m implemented fallback for too many clients in stacked mode
* [33m18be893[m and another fix...
* [33m0fb1842[m yet another typo fix
* [33mf522930[m fixed a typo
* [33maebd745[m floating clients get random (x,y) offsets now
* [33mc53980c[m applied Sanders resize patch, fixed lower bug
* [33m95e56ff[m changed CFLAGs
* [33mf129435[m firefox instance is different now
* [33m6649dcc[m changed occurrences of wmii.de into 10kloc.org in dwm.html, because 10kloc.org is already working
* [33m58f2fe3[m implemened distinguishing float/managed geometries of clients (works quite well)
* [33m0aaa9a2[m pop on heretag
* [33m4f8b08d[m added heretag command which allows to tag a client of a foreign tag with current tag
* [33m849e631[m using EXIT_stuff in exit() now
* [33m789717d[m simplified Makefile
* [33m605630c[m added new stuff
* [33m1e7e57d[m updated html
* [33meb184e0[m patched dwm
* [33med41473[m updated README
* [33mee5ba14[m Added tag 0.2 for changeset 0a6472e2203994bc5738d40a340d26f7ec9d6062
* [33mb706893[m[33m ([m[1;33mtag: 0.2[m[33m)[m updated html
* [33mbf35794[m ordered variables in structs and source files alphabetically
* [33me743836[m slight change to dwm.1
* [33m0c3544d[m simplified man page
* [33m94f7c27[m another XSync
* [33m901b3ed[m several additions in mouse handling ;)
* [33me6cbe9c[m fixed XSync handling and finished man page
* [33mf60c597[m changing XFlush into XSync
* [33mc09bf8d[m sanitized other stuff
* [33madaa28a[m proceeded with cleaning up, sorting functions, etc
* [33mdba2306[m rearranged several stuff
* [33mc0705ee[m sanitized names
* [33m29355bd[m rearranged
* [33m91a1f69[m I prefer the tiled/floating indicator on the right side
* [33m54775e0[m bar shows if currently is tiled (Mod1-space) or floating (Mod1-Shift-space) mode
* [33m59b4a5e[m draw bar on exposure ;)
* [33m82384e3[m Added tag 0.1 for changeset d31b5ad96b0ba7b5b0a30928fcf000428339a577
* [33m7faa8a9[m[33m ([m[1;33mtag: 0.1[m[33m)[m prep 0.1
* [33m6797ff8[m fixed crash on zoom if only 1 client exists
* [33me7fa504[m removed a bunch of lines through swap removal
* [33m5b44976[m if stdin writer stops working, dwm consumed much IO load because it still tried to select on this fd, fixed
* [33m6475be9[m removed a bottleneck
* [33ma1d0f81[m searching for a better way to discard enter notifies
* [33mc2cf829[m focus on view change as well
* [33me3fd306[m small fix
* [33meb756ee[m made stdin reader more robust
* [33m0e5c819[m implemented dwm reading status text from stdin
* [33m6458d72[m made barclick to select the specific tag
* [33m9cd686c[m implemented bar for dwm (I miss status text), I plan that status text is read from stdin in dwm
* [33m1549faf[m continued with man page
* [33m72655f0[m continued with man page
* [33m86d9851[m except improvements to the mouse handling this is already nearly feature complete
* [33m66da153[m added mini stuff
* [33m7fe717c[m fixed several things, nearly feature complete
* [33m3aad922[m new stuff
* [33mefa7e51[m several other additions/fixes, dwm is quite usable already
* [33mc47da14[m implemented tagging a client
* [33mb725887[m several fixes
* [33mb2e98bf[m added philosophy section
* [33mce846e9[m added xlock command (I need it regularly)
* [33m0a638a4[m added pointer warps on kb-driven/manage-driven focus
* [33m21553f9[m changed back to urxvt, dwm has no problems with it, because it doesn't use frame windows ;)
* [33m9e8b325[m changed default colors
* [33m44f2e8b[m added dev.c instead of kb.c
* [33m3f942f9[m removed obsolete stuff
* [33m7e43369[m fixed grammar bug reported by John-Galt
* [33mf33a30a[m another change
* [33m4ae1105[m updated man page
* [33m01a8d44[m small changes to README
* [33m3791ec0[m last change to dwm.html
* [33m80c7add[m renamed/changed
* [33m650a1fb[m added logo+description
* [33md7e1708[m new stuff (some warning elimination)
* [33m8b59083[m removed unnecessary crap
* [33mda2bbd3[m before leaning things up
* [33mb1701ad[m new stuff, fixed several issues
* [33m2e836ec[m added gravity stuff
* [33m6db5ffb[m added max
* [33m4641aa2[m added grid mode on Mod1Mask g
* [33mdfd84f9[m simplified several portions of code through replacing rect structs with x,y,h,w counterparts (much more readable)
* [33m7696c89[m fixed configurerequest
* [33mb41c56a[m new colors
* [33m2a0fc84[m some more additions/fixes
* [33m896f08d[m fixed several other stuff, coming closer to something useful
* [33m83d2390[m implemented draw_client stuff
* [33ma05beb6[m made code more readable
* [33m48b6e9a[m added basic mouse support (actually we don't need more)
* [33mb9da4b0[m added mouse-based resizals
* [33m5ed16fa[m updated README
* [33md6e0e6e[m several changes, new stuff
* [33mb1669b5[m removed unnecessary sel stuff
* [33m586f663[m added bar event timer
* [33m3399650[m added protocol killing stuff
* [33m272e15c[m new stuff
* [33m26e134b[m added gridsel to gridwm
* [33m0053620[m changed how manage client works
* [33m16c67f3[m fixed several stuff (gridwm gets better and better)
* [33m366d81e[m added key handling
* [33m8a8b795[m new stuff
* [33m3a69c51[m implemented pipe_spawn
* [33m439e15d[m added several other stuff
* [33m2de59d0[m renamed gridmenu.c into menu.c
* [33m39677ec[m several new changes, made gridmenu working
* [33m8a34fa5[m added new stuff
* [33mdbf7e03[m added gridmenu
* [33m1076f2b[m initial import
