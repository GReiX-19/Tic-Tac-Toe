#include "GameState.h"
#include "Renderer.h"

int main() {
	EngineCore::GameState game;
	Renderer::Renderer renderer(game);
	renderer.run();
}