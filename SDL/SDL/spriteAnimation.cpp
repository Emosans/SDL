//#include<SDL.h>
//#undef main;
//#include<SDL_image.h>
//#include<stdio.h>
//#include<string>
//#include<iostream>
//using namespace std;
//
//class LTexture {
//public:
//	//define functions
//	LTexture();
//	~LTexture();
//	void free();
//	bool loadFromFile(string path);
//	void render(int x, int y, SDL_Rect* clips = NULL);
//private:
//	SDL_Texture* finalTexture;
//	int mWidth;
//	int mHeight;
//};
//
////define global variables and objects
//SDL_Window* gWindow = NULL;
//SDL_Renderer* gRenderer;
//SDL_Surface* gScreenSurface = NULL;
//LTexture gLoadedTexture;
//SDL_Rect gSpriteClips[4];
//
////write methods for all functions in classes
//LTexture::LTexture() {
//	finalTexture = NULL;
//	mWidth = 0;
//	mHeight = 0;
//}
//
//LTexture::~LTexture() {
//	free();
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
//bool LTexture::loadFromFile(string path) {
//	SDL_Texture* newTexture=NULL;
//
//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//	if (!loadedSurface) {
//		printf("Failed");
//	}
//	else {
//		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
//		if (!newTexture) {
//			printf("failed");
//		}
//		else {
//			mWidth = loadedSurface->w;
//			mHeight = loadedSurface->h;
//		}
//		SDL_FreeSurface(loadedSurface);
//	}
//	finalTexture = newTexture;
//	return finalTexture != NULL;
//}
//
//void LTexture::render(int x, int y, SDL_Rect* clips) {
//	SDL_Rect quadRect = { x,y,mWidth,mHeight };
//
//	if (clips != NULL) {
//		quadRect.w = clips->w;
//		quadRect.h = clips->h;
//	}
//	SDL_RenderCopy(gRenderer, finalTexture,clips,&quadRect);
//}
//
////write init
//bool init() {
//	bool success = true;
//
//	if (SDL_INIT_VIDEO < 0) {
//		printf("failed");
//		success = false;
//	}
//	else {
//		gWindow = SDL_CreateWindow("sprite animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);
//		if (!gWindow) {
//			printf("Failed");
//			success = false;
//		}
//		else {
//			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
////write loadmedia (load all sprites of the png file)
//bool loadmedia() {
//	bool success = true;
//
//	if (!gLoadedTexture.loadFromFile("Images/sprite.png")) {
//		printf("Failed to load");
//	}
//	else {
//		//separate the sprites
//		gSpriteClips[0].x = 0;
//		gSpriteClips[0].y = 0;
//		gSpriteClips[0].w = 64;
//		gSpriteClips[0].h = 205;
//
//		gSpriteClips[1].x = 64;
//		gSpriteClips[1].y = 0;
//		gSpriteClips[1].w = 64;
//		gSpriteClips[1].h = 205;
//
//		gSpriteClips[2].x = 128;
//		gSpriteClips[2].y = 0;
//		gSpriteClips[2].w = 64;
//		gSpriteClips[2].h = 205;
//
//		gSpriteClips[3].x = 192;
//		gSpriteClips[3].y = 0;
//		gSpriteClips[3].w = 64;
//		gSpriteClips[3].h = 205;
//	}
//	return success;
//}
//
////write close
//void close() {
//	SDL_DestroyWindow(gWindow);
//	SDL_DestroyRenderer(gRenderer);
//
//	gLoadedTexture.free();
//
//	IMG_Quit();
//	SDL_Quit();
//}
//
////main() (define the frames that need to rendered at that frame time)
//int main() {
//	bool quit = false;
//	SDL_Event e;
//	int frames = 0;
//
//	if (!init()) {
//		printf("Failed");
//	}
//	else {
//		if (!loadmedia()) {
//			printf("Failed");
//		}
//		bool quit = false;
//		SDL_Event e;
//		int frames = 0;
//		const int frameDelay = 100;
//		Uint32 frameStart = 0;
//
//		while (!quit) {
//			while (SDL_PollEvent(&e) != 0) {
//				if (e.type == SDL_QUIT) {
//					quit = true;
//				}
//			}
//
//			Uint32 currentTime = SDL_GetTicks();
//
//			if (currentTime - frameStart >= frameDelay) {
//				// Move to the next frame
//				++frames;
//				if (frames >= 4) {
//					frames = 0;
//				}
//				frameStart = currentTime;
//			}
//
//			// Render the current frame
//			SDL_Rect* currentClip = &gSpriteClips[frames];
//			gLoadedTexture.render((500 - currentClip->w) / 2, (500 - currentClip->h) / 2, currentClip);
//
//			SDL_RenderPresent(gRenderer);
//		}
//		close();
//		return 0;
//	}
//}
