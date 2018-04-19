// #include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h> //using printf over cout because it is more thread safe???


//screen dimension constants [probably shouldn't be global]
const int SCREEN_WIDTH = 640;
const int SCREEN_HIEGHT = 480;

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close(); //naming would cause conflits in a C project, ok with C++

/****** GLOBAL Vars here not good, but ok-ish with smaller project *******/
//The window we will be rendering too
SDL_Window* gWindow = NULL;
//The surface contained by window;
SDL_Surface* gScreenSurface = NULL;
//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;


int main(int argc, const char * argv[]) {
    
    //Start up SDL and create window
    if( !init() ){
        printf( "Failed to initialize.\n" );

    }
    else {
        //Load Media
        if( !loadMedia() ){
            printf( "Faild to load media.\n" );
        }
        else {
            //Apply the image
            SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
            //update the surface
            SDL_UpdateWindowSurface( gWindow );
            //wait two seconds
            SDL_Delay( 2000 );
        }
    }

    //Free resources and close SDL
    close();
    
    return 0;
}

bool init(){
    //Initialization flag
    bool success = true;

    //initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize. SDL_Error: %s\n", SDL_GetError() );
    }
    else{
        //Create Widnow
        gWindow = SDL_CreateWindow( "SDL Practice", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HIEGHT, SDL_WINDOW_SHOWN);
        if( gWindow == NULL ) {
            printf( "Window could not be created. SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadMedia(){
    //Loading success flag
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP( "hello_world.bmp" );
    if( gHelloWorld == NULL ){
        printf( "Unable to load image %s SDL Error: %s\n", "hello_world.bmp", SDL_GetError() );
        success = false;
    }
    return success;
}

void close() {
    //Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //quit SDL subsystems
    SDL_Quit();
}