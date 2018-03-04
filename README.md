# PoG
###### ===
###### Protector of the Garden
###### Sidescroller
###### =======

###### Development Dependencies
#!/bin/bash

if [[ $(uname) = "Darwin" ]] && [[ -n $(which brew) ]]; then
        brew install sdl2
        brew install sdl2_image
        brew install sdl2_ttf

elif [[ -n $(which apt) ]]; then
    sudo apt install            \
        libsdl2-dev             \
        libsdl2-image-dev       \
        libsdl2-ttf-dev

else
    echo Install failed.

fi

