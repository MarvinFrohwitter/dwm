#!/bin/sh

cat  <<EOF | xmenu
[]=  tile	0
[M]  monocle	1
[@]  spiral	2
[\\] dwindle	3
H[]  deck	4
TTT  bstack	5
===  bstackhoriz	6
HHH  grid	7
###  nrowgrid	8
---  horizgrid	9
:::  gaplessgrid	10
|||  col	11
[S]  stairs	12
|M|  centeredmaster	13
>M>  centeredfloatingmaster	14
III  horizontal 15
><>  Floating Layout	16
EOF
