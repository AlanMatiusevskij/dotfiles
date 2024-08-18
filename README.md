# dotfiles
> If something does not work or is missing, let me know (most likely some dependencies are missing.)

### Packages:
Make sure you have the packages listed below installed.

`blueman pipewire networkmanager calcurse hyprland hyprlock hyprpaper waybar wayland yazi wofi vim neovim kitty wl-clipboard neofetch mako`

### Configlist/Themes:

Configlist binary is a small terminal application to brute-force manage themes.

You can either copy and replace the directories found within ~/.config/configlist/<THEME_NAME>/<CONFIG_DIRECTORIES>

or

> Before using the `-s` flag, make sure that `hyprpaper.sh` and `waybar.sh` bash scripts are in your HOME (~/) directory. (later will make it so c++ will replace those)

use command `configlist -s <THEMENAME>`. The list of already existing ones you can see by using `configlist -l`.

#### The way it works:

You simply edit the current ~/.config/ folder and when you are done, use `configlist -c` (-create) flag to make a copy of specified config folders. 
Then use `configlist -s` (-switch) to delete the current ~/.config/ folders that were specified doing 'creation' and replaces them.

Do note that you might need to edit source code (it's a mess, don't look) if you want it to restart processes besides `hyprland, waybar, hyprpaper`.

When deleting the current ~/.config/ folders to replace with the ones specified during 'creation', 
the applicaiton creates a one-time backup of the current .config directories that are going to be replaced. Find the backup in ~/.config/configlist/last_replaced/

---

#### Fonts (i have quite a few, can't say which specifically are used):

`gsfonts noto-fonts`

#### Things to manually change:

Required:
1) In `.config/hypr/Scripts/quote_gacha`, line 3, enter your user name.
2) In `.config/hypr/hyprpaper.conf`, change active wallpapers and their paths (by default looks for them in ~/Pictures).
3) In `.config/hypr/hyprlock.conf`, change lockscreen wallpaper path.

Optional: 
* In `.config/waybar/modules/volume.sh`, change script accordingly if volume control in waybar doesn't work right.
* To use `configlist` binary from terminal, put it in your PATH folder /usr/local/bin.
