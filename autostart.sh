#!/bin/sh

while true; do
xrandr --output Virtual1 --mode 1920x1080 &
# killall -q dwmblocks; dwmblocks &
bash ~/.config/dwm/autostart.sh
dunst &
feh ~/Git/dwm/wallpapers/tokyonight/tokyonight2.jpg --bg-fill &
# dwm >/dev/null 2>&1 
done
