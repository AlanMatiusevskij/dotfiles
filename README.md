# dotfiles
> If something does not work or is missing, let me know (most likely some dependencies are missing.)

Make sure you have the packages listed below installed.

`blueman pipewire networkmanager calcurse hyprland hyprlock hyprpaper waybar wayland yazi wofi vim neovim kitty wl-clipboard neofetch mako`

Arch install:

`sudo pacman -S blueman pipewire networkmanager calcurse hyprland hyprlock hyprpaper waybar wayland yazi wofi vim neovim kitty wl-clipboard neofetch mako`

Fonts (i have quite a few, can't say which specifically are used):

`gsfonts noto-fonts`

Things to manually change:

1) In `.config/hypr/Scripts/quote_gacha`, line 3, enter your user name.
2) In `.config/hypr/hyprpaper.conf`, change active wallpapers and their paths (by default looks for them in ~/Pictures).
3) In `.config/waybar/modules/volume.sh`, change script accordingly if volume control in waybar doesn't work right.
4) To use `configlist` binary from terminal, put it in your PATH folder /usr/local/bin.
