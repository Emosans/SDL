//#include <SDL.h>
//#include <stdio.h>
//#include<iostream>
//#include<SDL_image.h>
//
////#include "backgroundImageOnTop.cpp";
//using namespace std;
//
//enum KeySurfacePresses {
//	KEY_SURFACE_PRESS_DEF,
//	KEY_SURFACE_PRESS_UP,
//	KEY_SURFACE_PRESS_DOWN,
//	KEY_SURFACE_PRESS_LEFT,
//	KEY_SURFACE_PRESS_RIGHT,
//	KEY_SURFACE_PRESS_TOTAL
//};
//
//const int SCREEN_WIDTH = 300;
//const int SCREEN_HEIGHT = 300;
//
//SDL_Surface* gLoadImage(string path);
//SDL_Window* gWindow = NULL;
//SDL_Surface* gScreenSurface = NULL;
//SDL_Surface* gKeySurfacePresses[KEY_SURFACE_PRESS_TOTAL];
//SDL_Surface* gCurrentSurface = NULL;
//
//
//bool init() {
//	bool success = true;
//
//	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//		printf("SDL could not be loaded");
//		success = false;
//	}
//	else {
//		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//		if (gWindow == NULL) {
//			printf("Window could not be loaded");
//			success = false;
//		}
//		else {
//			gScreenSurface = SDL_GetWindowSurface(gWindow);
//		}
//	}
//	return success;
//}
//
//SDL_Surface* gLoadImage(string path) {
//	SDL_Surface* optimizedSurface = NULL;
//	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
//	if (loadedSurface == NULL) {
//		printf("Error");
//	}
//	else {
//		//convert to optimized surface version
//		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
//		if (optimizedSurface == NULL) {
//			printf("Failed");
//		}
//		SDL_FreeSurface(loadedSurface);
//	}
//	return optimizedSurface;
//}
//
//bool loadMedia()
//{
//	bool success = true;
//
//	//Load default surface
//	gKeySurfacePresses[KEY_SURFACE_PRESS_DEF] = gLoadImage("Images/default.bmp");
//	if (gKeySurfacePresses[KEY_SURFACE_PRESS_DEF] == NULL)
//	{
//		printf("Failed to load default image!\n");
//		success = false;
//	}
//
//	//Load up surface
//	gKeySurfacePresses[KEY_SURFACE_PRESS_UP] = gLoadImage("Images/up.bmp");
//	if (gKeySurfacePresses[KEY_SURFACE_PRESS_UP] == NULL)
//	{
//		printf("Failed to load up image!\n");
//		success = false;
//	}
//
//	//Load down surface
//	gKeySurfacePresses[KEY_SURFACE_PRESS_DOWN] = gLoadImage("Images/down.bmp");
//	if (gKeySurfacePresses[KEY_SURFACE_PRESS_UP] == NULL)
//	{
//		printf("Failed to load up image!\n");
//		success = false;
//	}
//
//	//Load left surface
//	gKeySurfacePresses[KEY_SURFACE_PRESS_LEFT] = gLoadImage("Images/left.bmp");
//	if (gKeySurfacePresses[KEY_SURFACE_PRESS_UP] == NULL)
//	{
//		printf("Failed to load up image!\n");
//		success = false;
//	}
//
//	//Load right surface
//	gKeySurfacePresses[KEY_SURFACE_PRESS_RIGHT] = gLoadImage("Images/right.bmp");
//	if (gKeySurfacePresses[KEY_SURFACE_PRESS_UP] == NULL)
//	{
//		printf("Failed to load up image!\n");
//		success = false;
//	}
//	return success;
//}
//
//void close()
//{
//	for (int i = 0; i < KEY_SURFACE_PRESS_TOTAL; ++i)
//	{
//		SDL_FreeSurface(gKeySurfacePresses[i]);
//	}
//
//	SDL_DestroyWindow(gWindow);
//	gWindow = NULL;
//
//	SDL_Quit();
//}
//
//void Tmain(int argc, char* args[])
//{
//		bool quit = false;
//		SDL_Event e;
//
//
//		if (!init()) {
//			printf("Failed");
//		}
//		else {
//			if (!loadMedia()) {
//				printf("Failed to load media!\n");
//			}
//			else {
//				//make current surface
//				gCurrentSurface = gKeySurfacePresses[KEY_SURFACE_PRESS_DEF];
//
//				while (!quit) {
//					while (SDL_PollEvent(&e) != 0) {
//						if (e.type == SDL_QUIT) {
//							quit = true;
//						}
//						else if (e.type == SDL_KEYDOWN) {
//							switch (e.key.keysym.sym) {
//							case SDLK_UP:
//								gCurrentSurface = gKeySurfacePresses[KEY_SURFACE_PRESS_UP];
//								break;
//							case SDLK_DOWN:
//								gCurrentSurface = gKeySurfacePresses[KEY_SURFACE_PRESS_DOWN];
//								break;
//							case SDLK_LEFT:
//								gCurrentSurface = gKeySurfacePresses[KEY_SURFACE_PRESS_LEFT];
//								break;
//							case SDLK_RIGHT:
//								gCurrentSurface = gKeySurfacePresses[KEY_SURFACE_PRESS_RIGHT];
//								break;
//							default:
//								gCurrentSurface = gKeySurfacePresses[KEY_SURFACE_PRESS_DEF];
//								break;
//							}
//						}
//
//						SDL_Rect rectToFitSurface = { 0,0,SCREEN_HEIGHT,SCREEN_WIDTH };
//						// blit the current surface
//						SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &rectToFitSurface);
//						SDL_UpdateWindowSurface(gWindow);
//					}
//				}
//			}
//		}
//
//		close();
//}
//
//int main() {
//	//runApp();
//	return 0;
//}