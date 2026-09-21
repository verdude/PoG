CXX ?= g++
PKG_CONFIG ?= pkg-config
CXXFLAGS ?= -std=c++11
SDL_PACKAGES = sdl3 sdl3-image
SDL_CFLAGS = $(shell $(PKG_CONFIG) --cflags $(SDL_PACKAGES))
SDL_LIBS = $(shell $(PKG_CONFIG) --libs $(SDL_PACKAGES))

.PHONY: all make clean check-deps
all: build
make: build

check-deps:
	@$(PKG_CONFIG) --exists $(SDL_PACKAGES) || { \
		echo "SDL3 and SDL3_image development packages are required (see README.md)." >&2; \
		exit 1; \
	}

build: $(wildcard *.cpp *.h) Makefile | check-deps
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SDL_CFLAGS) -o $@ $(wildcard *.cpp) $(LDFLAGS) $(SDL_LIBS) $(LDLIBS)

clean:
	rm -f build
