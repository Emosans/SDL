#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<stdio.h>
#undef main
#include<string>
using namespace std;

class LTexture {
public:
	LTexture();
	~LTexture();
	void free();
	bool loadImageFromFile(string path);
	int getWidth();
	int getHeight();
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
	SDL_Texture* finalTexture;
	int finalWidth;
	int finalHeight;
};

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer;
SDL_Surface* gScreenSurface = NULL;
LTexture gArrowTexture;

LTexture::LTexture() {
	finalTexture = NULL;
	finalWidth = 0;
	finalHeight = 0;
}

LTexture::~LTexture() {
	free();
}

void LTexture::free() {
	if (finalTexture != NULL) {
		finalTexture = NULL;
		finalWidth = 0;
		finalHeight = 0;
	}
}

bool LTexture::loadImageFromFile(string path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (!loadedSurface) {
		printf("Failed");
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
		if (!newTexture) {
			printf("Failed");
		}
		else {
			finalWidth = loadedSurface->w;
			finalHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	finalTexture = newTexture;
	return finalTexture != NULL;
}

void LTexture::render(int x, int y, SDL_Rect* clips, double angle,SDL_Point*center, SDL_RendererFlip flip) {
	SDL_Rect quadRect = { 0,0,finalWidth,finalHeight };

	if (clips != NULL) {
		quadRect.w = clips->w;
		quadRect.h = clips->h;
	}

	SDL_RenderCopyEx(gRenderer, finalTexture, clips, &quadRect, angle, center, flip);
}

int LTexture::getWidth() {
	return finalWidth;
}

int LTexture::getHeight() {
	return finalHeight;
}

bool init() {
	bool success = true;

	if (SDL_INIT_VIDEO < 0) {
		printf("Failed");
		success = false;
	}
	else {
		gWindow = SDL_CreateWindow("Rotation and flipping", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Failed");
		}
		else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				printf("Failed");
				success = false;
			}
			else {
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}
	return success;
}

bool loadmedia() {
	bool success = true;

	if (!gArrowTexture.loadImageFromFile("Images/arrow.png")) {
		printf("Failed");
		success=false;
	}
	return success;
}

void close() {
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);

	gArrowTexture.free();
	IMG_Quit();
	SDL_Quit();
}

int main() {
	bool quit = false;
	SDL_Event e;
	double degreesOfRotation = 0.0;
	SDL_RendererFlip flippedState = SDL_FLIP_NONE;

	if (!init()) {
		printf("Failed");
	}
	else {
		if (!loadmedia()) {
			printf("Failed");
		}
		else {
			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else if(e.type==SDL_KEYDOWN) {
						switch (e.key.keysym.sym){
						case SDLK_d:
							degreesOfRotation += 60;
							break;
						case SDLK_r:
							degreesOfRotation -= 60;
							break;
						case SDLK_h:
							flippedState = SDL_FLIP_HORIZONTAL;
							break;
						case SDLK_w:
							flippedState = SDL_FLIP_NONE;
							break;
						case SDLK_v:
							flippedState = SDL_FLIP_VERTICAL;
							break;
						default:
							break;
						}
					}
				}
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				gArrowTexture.render((500 - gArrowTexture.getWidth()) / 2, (500 - gArrowTexture.getHeight()) / 2, NULL, degreesOfRotation, NULL, flippedState);

				SDL_RenderPresent(gRenderer);
			}
		}
	}
}