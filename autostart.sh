while true; do
	bash $HOME/.scripts/vboxres &
	dwmblocks &
	feh ~/Git/dwm/wallpapers/tokyonight/tokyonight.jpg --bg-fill &
	dwm >/dev/null 2>&1 
done &
