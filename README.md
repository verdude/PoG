# PoG

Protector of the Garden — a sidescroller.

Requires a C++11 compiler, Make, pkg-config, SDL3 (3.2 or newer), and
SDL3_image (3.2 or newer) with PNG support.

Install development dependencies:

```bash
# macOS (Homebrew)
brew install pkg-config sdl3 sdl3_image

# Arch Linux
sudo pacman -S --needed base-devel pkgconf sdl3 sdl3_image

# Debian/Ubuntu releases that provide SDL3 packages
sudo apt install build-essential pkg-config libsdl3-dev libsdl3-image-dev
```

If your distribution does not provide SDL3 packages, build and install
[SDL3](https://github.com/libsdl-org/SDL/blob/main/INSTALL.md) and
[SDL3_image](https://github.com/libsdl-org/SDL_image/blob/main/INSTALL.md)
from source. For a custom installation prefix, add its `lib/pkgconfig`
directory to `PKG_CONFIG_PATH`.

Build and run from the repository root so the game can find its image assets:

```bash
make
./build
```

Use the left/right arrow keys to move and Space to jump. Close the window to quit.
Run `make clean` to remove the executable.
