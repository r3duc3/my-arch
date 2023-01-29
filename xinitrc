# Fix cursor
xsetroot -cursor_name left_ptr

# Polkit agent
/usr/lib/xfce-polkit/xfce-polkit &

# power management
xfce4-power-manager &

# super keys
ksuperkey -e 'Super_L=Alt_L|F1' &

# dwmbar

# notification daemon

# compositor

# Fix Java problems
wmname "LG3D"
export _JAVA_AWT_WM_NONREPARENTING=1

# clipboard manager
xfce4-clipman &
test
