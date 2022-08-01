## Setup nvim with ccls 
```bash
cd ~/dev/qmk_firmware
make handwired/dactyl_manuform/5x6:colemak-dh
ls ~/dev/qmk_firmware/.build/obj_handwired_dactyl_manuform_5x6_colemak-dh/cflags.txt
echo 'clang' > .ccls; cat ~/dev/qmk_firmware/.build/obj_handwired_dactyl_manuform_5x6_colemak-dh/cflags.txt | sed 's/ -/\ -/g' | sed 's/ //' | sed 's/ *$//' >> .ccls
```
