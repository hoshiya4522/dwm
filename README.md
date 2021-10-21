# Hoshiya's Fork Of Dynamic Window Manager(DWM)
My custom build of [dwm](https://dwm.suckless.org)

## Installation
```bash
git clone https://github.com/hoshiya4522/dwm
cd dwm
sudo make clean install
```

## Applied Patches
- ### [Bar Height](https://dwm.suckless.org/patches/bar_height)
> This patch allows user to change dwm's default bar height.
- ### [Useless Gap](https://dwm.suckless.org/patches/uselessgap)
> For aesthetic purposes, this patch:
> - adds "useless gaps" around windows
> - removes everything (gaps and borders) when in monocle mode for aesthetic purpose.
- ### [Moveresize](https://dwm.suckless.org/patches/moveresize)
> This changes allows you to move and resize dwm's clients using keyboard bindings.
- ### [Swallow](https://dwm.suckless.org/patches/swallow)
> This patch helps users spawning a lot of graphical programs from their command line by avoiding cluttering the screen with many unusable terminals. Being deep down in a directory hierarchy just does not make the use of dmenu feasible.
>
> Dependencies
> - libxcb
> - Xlib-libxcb
> - xcb-res

Better explanation [Luke Smith's Video on window swallowing](https://youtube.com/watch?v=92uo5OBOKfY)
