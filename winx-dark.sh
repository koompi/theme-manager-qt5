#!/bin/bash
pkexec sed -i 's/Current=.*/Current=koompi-dark/g' /etc/sddm.conf.d/kde_settings.conf

kvantummanager --set Fluent-Dark
lookandfeeltool -a org.koompi.theme.koompi-winx-dark --resetLayout

sleep 10
plugin_line=$(grep -n "plugin=com.github.zren.tiledmenu" ${HOME}/.config/plasma-org.kde.plasma.desktop-appletsrc)

target_line=$((${plugin_line%:*} - 2))

id_line=$(sed "${target_line}q;d" ${HOME}/.config/plasma-org.kde.plasma.desktop-appletsrc)

c1=$(sed -e "s/[a-zA-Z]//g" <<<$id_line)
c2=$(sed -e "s/[[]]//g" <<<$c1)
c3=$(sed -e "s/\]\[/-/g" <<<$c2)
c4=$(sed -e "s/\]//g" <<<$c3)
c5=$(sed -e "s/\[//g" <<<$c4)

containment_id=${c5%-*}
echo $containment_id
widget_id=${c5##*-}
echo $widget_id

header="[Containments][$containment_id][Applets][${widget_id}][Shortcuts]"
config="global=Alt+F1"

sed -i "s/plugin=com.github.zren.tiledmenu/plugin=com.github.zren.tiledmenu\n\n${header}\n${config}\n/" ${HOME}/.config/plasma-org.kde.plasma.desktop-appletsrc
sed -i '/Launchpad/d' $HOME/.config/kglobalshortcutsrc
sed -i '/Tiled\ Menu/d' $HOME/.config/kglobalshortcutsrc
kwriteconfig5 --file "$HOME/.config/kglobalshortcutsrc" \
    --group "plasmashell" \
    --key "activate widget ${widget_id}" \
    "Alt+F1,none,Activate Tiled Menu Widget"

if pgrep -x "latte-dock" >/dev/null; then
    rm -rf ${HOME}/.config/autostart/org.kde.latte-dock.desktop
    killall latte-dock
fi

# Lock screen
kwriteconfig5 --file kscreenlockerrc --group Greeter --group Wallpaper --group org.kde.image --group General --key Image "file:///usr/share/wallpapers/sunset-art-scenery-landscape-uhdpaper.com-4K-8.277.jpg"
