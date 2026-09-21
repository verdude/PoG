#include <SDL3/SDL_main.h>
#include "PoG.h"

using namespace std;

int main(int argc, char** argv) {
	PoG pog;
	return pog.play() ? 0 : 1;
}
