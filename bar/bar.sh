#!/bin/sh

# ^c$var^ = fg color
# ^b$var^ = bg color

interval=0

# load colors!
. ~/Git/dwm/bar/themes/tokyonight.sh
# . ~/Git/dwm/bar/themes/nord.sh

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

vol(){
	mute="婢 "
	ico="墳 "

	vol=$(pactl list sinks | grep '^[[:space:]]Volume:' | \
	    head -n $(( $SINK + 1 )) | tail -n 1 | sed -e 's,.* \([0-9][0-9]*\)%.*,\1,')

	m=$(pactl list sinks | grep '^[[:space:]]Mute:' | \
		head -n $(( $SINK + 1 )) | tail -n 1 | cut -d":" -f2)


	if [[ $m == " no" ]]; then 
		icon=$ico
	else 
		icon=$mute
	fi

	p="%%"
	printf "^c$black^ ^b$yellow^ $icon ^c$yellow^^b$bg^ $vol$p " 
}

battery() {
	x=$(cat /sys/class/power_supply/BAT0/capacity )
	i100="󰁹"
	i90="󰂂"
	i80="󰂁"
	i70="󰂀"
	i60="󰁿"
	i50="󰁾"
	i40="󰁽"
	i30="󰁼"
	i20="󰁻"
	i10="󰁺"
	i00="󱃍"
	if [[ x -gt 95 ]] 
	then
		ico=$i100
	elif [[ x -gt 90 ]] 
	then
		ico=$i90
	elif [[ x -gt 80 ]] 
	then
		ico=$i80
	elif [[ x -gt 70 ]] 
	then
		ico=$i70
	elif [[ x -gt 60 ]] 
	then
		ico=$i60
	elif [[ x -gt 50 ]] 
	then
		ico=$i50
	elif [[ x -gt 40 ]] 
	then 
		ico=$i40
	elif [[ x -gt 30 ]] 
	then
		ico=$i30
	elif [[ x -gt 20 ]] 
	then
		ico=$i20
	elif [[ x -gt 10 ]] 
	then
		ico=$i10
	elif [[ x -lt 10 ]] 
	then
		ico=$i00
	fi

	case "$(cat /sys/class/power_supply/BAT[01]/status 2>&1)" in
		"Full") status=$i100 ;;
		"Discharging") status=$ico;;
		"Charging") status="⚡" ;;
		"Not charging") status=$ico;;
		"Unknown") status="?" ;;
		*) exit 1 ;;
	esac

	p="%%"
	# printf "^c$blue^   $get_capacity$p"
	printf "^c$black^ ^b$purple^ $status ^c$purple^^b$bg^ $x$p " 
}

divider(){
	printf "^c$black^^b$black^|"
}

up(){
	rx=$(update /sys/class/net/[ew]*/statistics/rx_bytes)
	n=$(numfmt --to=iec $rx)
	letterb="B"
	printf "^c$black^^b$green^ 󰤨 ^c$green^^b$bg^ $n$letterb " 
}

wlan() {
	case "$(cat /sys/class/net/[ew]*/operstate 2>/dev/null)" in
		up) up ;;
		down) printf "^c$black^ ^b$red^ 󰤭 ^d^%s" " ^c$red^ Disconnected" ;;
	esac
}

clock() {
	printf "^c$black^ ^b$darkblue^ 󱑆 "
	# printf "^c$black^^b$blue^│"
	printf "^c$black^^b$blue^ $(date '+%I:%M %p') "

	# printf "^c$black^ ^b$blue^ 󱑆 "
	# printf "^c$blue^^b$bg^ $(date '+%I:%M %p') "
}

while true; do

	# [ $interval = 0 ] || [ $(($interval % 3600)) = 0 ] 
	interval=$((interval + 1))

	sleep 1 && xsetroot -name "$(wlan)$(divider)$(vol)$(divider)$(battery)$(divider)$(clock)"
	# sleep 1 && echo "$(wlan)  $(vol)  $(battery)  $(clock)"
done

