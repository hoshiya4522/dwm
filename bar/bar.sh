#!/bin/sh

# ^c$var^ = fg color
# ^b$var^ = bg color

interval=0

# load colors!
. ~/Git/dwm/bar/themes/nord.sh

update() {
    sum=0
    for arg; do
        read -r i < "$arg"
        sum=$(( sum + i ))
    done
    cache=${XDG_CACHE_HOME:-$HOME/.cache}/${1##*/}
    [ -f "$cache" ] && read -r old < "$cache" || old=0
    printf %d\\n "$sum" > "$cache"
    printf %d\\n $(( sum - old ))
}

cpu() {
	cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)

	printf "^c$black^ ^b$green^ CPU"
	printf "^c$white^ ^b$grey^ $cpu_val"
}


battery() {
	get_capacity="$(cat /sys/class/power_supply/BAT0/capacity)"
	printf "^c$blue^   $get_capacity"
}

brightness() {
	printf "^c$red^   "
	printf "^c$red^%.0f\n" $(cat /sys/class/backlight/*/brightness)
}

mem() {
	printf "^c$blue^^b$black^  "
	printf "^c$blue^ $(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

up(){
	rx=$(update /sys/class/net/[ew]*/statistics/rx_bytes)
	n=$(numfmt --to=iec $rx)
	printf "^c$black^ ^b$blue^ 󰤨 ^d^%s" " ^c$blue^$n" 
}

wlan() {
	case "$(cat /sys/class/net/[ew]*/operstate 2>/dev/null)" in
		up) up ;;
		down) printf "^c$black^ ^b$blue^ 󰤭 ^d^%s" " ^c$blue^Disconnected" ;;
	esac
}

clock() {
	printf "^c$black^ ^b$darkblue^ 󱑆 "
	printf "^c$black^^b$blue^ $(date '+%I:%M %p') "
}

while true; do

	# [ $interval = 0 ] || [ $(($interval % 3600)) = 0 ] 
	interval=$((interval + 1))

	sleep 1 && xsetroot -name "$(wlan) $(battery) $(cpu) $(mem) $(clock)"
done

