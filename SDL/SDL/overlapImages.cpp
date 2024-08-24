//#include<SDL.h>
//#undef main;
//#include<SDL_image.h>
//#include<stdio.h>
//#include<iostream>
//#include<string>
//using namespace std;
//
//class LTexture {
//public:
//	//allocate
//	LTexture();
//
//	//deallocate
//	~LTexture();
//
//	//free
//	void free();
//
//	//load tthe image file
//	bool loadFromFile(string path);
//
//	//render the images at x,y
//	void render(int x, int y);
//
//private:
//	SDL_Texture* finalTexture;
//	int mWidth;
//	int mHeight;
//};
//
//SDL_Window* gWindow = NULL;
//SDL_Surface* gScreenSurface = NULL;
//SDL_Renderer* gRenderer;
//LTexture foregroundTexture;
//LTexture backgroundTexture;
//
//LTexture::LTexture() {
//	//initialize the texture initially as null
//	finalTexture = NULL;
//
//	//initialize the heigh and width as null
//	mWidth = 0;
//	mHeight = 0;
//}
//
//LTexture::~LTexture() {
//	//deallocates all memory
//	free();
//}
//
//bool LTexture::loadFromFile(string path) {
//	//free any initial texture
//	free();
//
//	SDL_Texture* newTexture = NULL;
//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//	if (loadedSurface == NULL) {
//		printf("Failed");
//	}
//	else {
//		//set color key
//		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
//
//		//create texture from pixles
//		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
//
//		if (newTexture == NULL) {
//			printf("Failed to create texture");
//		}
//		else {
//			//load widht and height of the loaded image
//			mWidth = loadedSurface->w;
//			mHeight = loadedSurface->h;
//		}
//		//free the surface
//		SDL_FreeSurface(loadedSurface);
//	}
//	//copy the texture from newTexture to finalTexture
//	finalTexture = newTexture;
//	return finalTexture != NULL;
//}
//
//void LTexture::free() {
//	if (finalTexture != NULL) {
//		finalTexture = NULL;
//		mWidth = 0;
//		mHeight = 0;
//	}
//}
//
//void LTexture::render(int x, int y) {
//	//{x pos,y pos, width, height}
//	SDL_Rect renderMaxSize= { x,y,mWidth,mHeight };
//	SDL_RenderCopy(gRenderer, finalTexture, NULL, &renderMaxSize);
//}
//
//bool init() {
//	bool success = true;
//
//	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//		printf("SDL could not be loaded");
//		success = false;
//	}
//	else {
//		gWindow = SDL_CreateWindow("SDL Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);
//		if (gWindow == NULL) {
//			printf("Window could not be loaded");
//			success = false;
//		}
//		else {
//			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
//			if (gRenderer == NULL) {
//				printf("Failed");
//				success = false;
//			}
//			else {
//				gScreenSurface = SDL_GetWindowSurface(gWindow);
//			}
//		}
//	}
//	return success;
//}
//
//bool loadmedia() {
//	bool success = true;
//	//load foreground
//	if (!foregroundTexture.loadFromFile("Images/foo.png")) {
//		printf("FAiled");
//		success=false;
//	}
//
//	//load background
//	if (!backgroundTexture.loadFromFile("Images/background.png")) {
//		printf("failed");
//		success = false;
//	}
//	return success;
//}
//
//void close() {
//	SDL_DestroyRenderer(gRenderer);
//	SDL_DestroyWindow(gWindow);
//	foregroundTexture.free();
//	backgroundTexture.free();
//
//	IMG_Quit();
//	SDL_Quit();
//}
//
//int main() {
//	bool quit = false;
//	SDL_Event e;
//
//	if (!init()) {
//		printf("Failed");
//	}
//	else {
//		if (!loadmedia()) {
//			printf("Failed");
//		}
//		else {
//			while (!quit) {
//				while (SDL_PollEvent(&e) != 0) {
//					if (e.type == SDL_QUIT) {
//						quit = true;
//					}
//					else {
//						//clear render screen
//						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//						SDL_RenderClear(gRenderer);
//
//						//render background to screen
//						backgroundTexture.render(0, 0);
//
//						//render foreground to screen
//						foregroundTexture.render(240,120);
//
//						//update screen
//						SDL_RenderPresent(gRenderer);
//					}
//				}
//			}
//		}
//	}
//	return 0;
//}
