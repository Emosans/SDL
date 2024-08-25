#include<stdio.h>
#include<SDL.h>
#undef main;
#include<SDL_image.h>
#include<string>
#include<iostream>
using namespace std;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer;

class LTexture {
public:
	LTexture();
	~LTexture();
	void free();
	bool loadImage(string path);
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setToBlend(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	void render(int x, int y, SDL_Rect* clip = NULL);

private:
	SDL_Texture* finalTexture = NULL;
	int mWidth = 0;
	int mHeight = 0;
};

LTexture gModulatedTexture;
LTexture gBackgroundTexture;

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

bool LTexture::loadImage(string path) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL) {
		printf("Failed");
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (!newTexture) {
			printf("Failed");
		}
		else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	finalTexture = newTexture;
	return finalTexture != NULL;
}

void LTexture::setToBlend(SDL_BlendMode blending) {
	//create the blend
	SDL_SetTextureBlendMode(finalTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(finalTexture, alpha);
}

void LTexture::render(int x, int y,SDL_Rect* clip) {
	SDL_Rect dRect = { x,y,mWidth,mHeight };
	SDL_RenderCopy(gRenderer, finalTexture, NULL, &dRect);
}

bool init() {
	bool success = true;

	if (SDL_INIT_VIDEO < 0) {
		printf("failed");
		success = false;
	}
	else {
		gWindow = SDL_CreateWindow("FadeinOut", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800,500,SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Failed");
			success = false;
		}
		else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("False");
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

	if (!gModulatedTexture.loadImage("Images/fadeout.png")) {
		printf("Failed");
		success = false;
	}
	else {
		gModulatedTexture.setToBlend(SDL_BLENDMODE_BLEND);
	}

	if (!gBackgroundTexture.loadImage("Images/fadein.png")) {
		printf("failed");
		success = false;
	}
	return success;
}

void close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gModulatedTexture.free();
	gBackgroundTexture.free();

	IMG_Quit();
	SDL_Quit();
}

int main() {
	bool quit = false;

	SDL_Event e;
	Uint8 a = 255;

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
					else if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym) {
							//increase alpha to display forground image
						case SDLK_w:
							if (a + 32 > 255) {
								a = 255;
							}
							else {
								a += 32;
							}
							break;
						case SDLK_s:
							//decrease alpha to display background image
							if (a - 32 < 0) {
								a = 0;
							}
							else {
								a -= 32;
							}
							break;
						default:
							break;
						}
					}
				}
				//clear renderer
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//set background
				gBackgroundTexture.render(0, 0);

				//set foreground
				gModulatedTexture.setAlpha(a);
				gModulatedTexture.render(0, 0);

				SDL_RenderPresent(gRenderer);


			}
		}
	}
	close();
	return 0;
}







