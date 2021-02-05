#!/bin/bash
pkexec sed -i 's/Current=.*/Current=koompi-dark/g' /etc/sddm.conf.d/kde_settings.conf
kvantummanager --set McMojave
lookandfeeltool -a org.koompi.theme.koompi-mosx-dark --resetLayout
sleep 10
plugin_line=$(grep -n "plugin=launchpadPlasmaMod" ${HOME}/.config/plasma-org.kde.plasma.desktop-appletsrc)

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

sed -i "s/plugin=launchpadPlasmaMod/plugin=launchpadPlasmaMod\n\n${header}\n${config}\n/" ${HOME}/.config/plasma-org.kde.plasma.desktop-appletsrc
sed -i '/Launchpad/d' $HOME/.config/kglobalshortcutsrc
sed -i '/Tiled\ Menu/d' $HOME/.config/kglobalshortcutsrc
kwriteconfig5 --file "$HOME/.config/kglobalshortcutsrc" \
    --group "plasmashell" \
    --key "activate widget ${widget_id}" \
    "Alt+F1,none,Activate Launchpad Plasma Transparent Widget"

# Update latte dock
if ! pgrep -x "latte-dock" >/dev/null; then
    cp /usr/share/applications/org.kde.latte-dock.desktop ${HOME}/.config/autostart/
    latte-dock </dev/null &>/dev/null &
    echo -e "Done"
fi

# Lock screen
kwriteconfig5 --file kscreenlockerrc --group Greeter --group Wallpaper --group org.kde.image --group General --key Image "file:///usr/share/wallpapers/abstract-colorful-dispersion-digital-art-uhdpaper.com-4K-4.1950.jpg"
