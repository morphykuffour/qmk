# Copyright 2019 Manna Harbour
# https://github.com/manna-harbour/miryoku

MOUSEKEY_ENABLE = yes # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
AUTO_SHIFT_ENABLE = yes # Auto Shift

SRC += morphy_miryoku.c # keymaps

include users/morphy_miryoku/custom_rules.mk

include users/morphy_miryoku/post_rules.mk
