#include<SDL.h>
#undef main;
#include<SDL_image.h>
#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer;
SDL_Surface* gScreenSurface = NULL;

class LTexture {
public:
	//allocate
	LTexture();

	//deallocate
	~LTexture();

	//free
	void free();

	//load the image file
	bool loadFromFile(string path);

	//set rgb
	void setColor(Uint8 red, Uint8 green, Uint8 blue);


	//render the images at x,y
	void render(int x, int y, SDL_Rect* srcRect = NULL);

private:
	SDL_Texture* finalTexture;
	int mWidth;
	int mHeight;
};

LTexture gModulatedTexture;

LTexture::LTexture() {
	finalTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	free();
}

void LTexture::free() {
	if (finalTexture != NULL) {
		finalTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

bool LTexture::loadFromFile(string path) {
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL) {
		printf("Failed");
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
		if (newTexture != NULL) {

		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;
		}
		else {
			printf("Failed");
		}
		SDL_FreeSurface(loadedSurface);
	}
	finalTexture = newTexture;
	return finalTexture != NULL;
}

void LTexture::setColor(Uint8 red,Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(finalTexture, red, green, blue);
}

void LTexture::render(int x, int y, SDL_Rect* srcRect) {
	SDL_Rect maxRect = { 0,0,mWidth,mHeight };
	SDL_RenderCopy(gRenderer, finalTexture, NULL, NULL);
}



bool init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not be loaded");
		success = false;
	}
	else {
		gWindow = SDL_CreateWindow("SDL Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be loaded");
			success = false;
		}
		else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
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

	if (!gModulatedTexture.loadFromFile("Images/white.jpg")) {
		printf("False");
		success = false;
	}
	return success;
}

void close() {
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gModulatedTexture.free();
	IMG_Quit();
	SDL_Quit();
}

int main() {
	bool quit = false;
	SDL_Event e;

	Uint8 r = 255;
	Uint8 g = 255;
	Uint8 b = 255;

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
					else if(e.type==SDL_KEYDOWN){
						switch (e.key.keysym.sym) {
						case SDLK_r:
							r += 32;
							break;
						case SDLK_g:
							g += 32;
							break;
						case SDLK_b:
							b += 32;
							break;
						case SDLK_w:
							r -= 32;
							break;
						case SDLK_a:
							g -= 32;
							break;
						case SDLK_s:
							b -= 32;
							break;
						default:
							break;
						}
					}
				}
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Modulate and render texture
				gModulatedTexture.setColor(r, g, b);
				gModulatedTexture.render(0, 0);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}	
	}
		return 0;
}