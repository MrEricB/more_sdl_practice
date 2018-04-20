// #include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h> //using printf over cout because it is more thread safe???
#include <string>

//screen dimension constants [probably shouldn't be global]
const int SCREEN_WIDTH = 640;
const int SCREEN_HIEGHT = 480;

//Dey press surface constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close(); //naming would cause conflits in a C project, ok with C++

//Loads Individual image
SDL_Surface* loadSurface( std::string path );

//The window we will be rendering too
SDL_Window* gWindow = NULL;

//The surface contained by window;
SDL_Surface* gScreenSurface = NULL;

//The image the correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//current display image
SDL_Surface* gCurrentSurface = NULL;


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
            /******** main game loop *********/
            
            //Main loop flag
            bool quit = false;
            //Event handler
            SDL_Event e;

            //set default current surface
            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

            //While application is running
            while( !quit ){
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0){
                    //User requests quit
                    if( e.type == SDL_QUIT ){
                        quit = true;
                    }else if(e.type == SDL_KEYDOWN ){
                        //Select surfaces base on key press
                        switch( e.key.keysym.sym ){
                            case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                            break;

                            case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            break;

                            case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT] ;
                            break;

                            case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                            break;

                            default:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                            break;
                        }
                    }
                }

                //Apply the image
                SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
                //update the surface
                SDL_UpdateWindowSurface( gWindow );

            }
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

    //Laod default surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface("img/press.bmp");
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL ){
        printf( "Failed to load default image\n" );
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "img/up.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL ){
        printf( "Failed to laod UP Image\n" );
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface("img/down.bmp");
    if(gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN] == NULL ){
        printf("Faile to load DOWN image\n");
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface("img/left.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL){
        printf("Failed to load LEFT Image\n");
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface("img/right.bmp");
    if(gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL){
        printf("Failed to load RIGHT Image\n");
        success = false;
    }

    return success;
}

void close() {
    //Deallocate surfaces
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++){
        SDL_FreeSurface( gKeyPressSurfaces[i] );
        gKeyPressSurfaces[i] = NULL;
    }

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface( std::string path ){
    //Load image at given path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );

    if( loadedSurface == NULL ){
        printf( "Unalbe to lad image %s. SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
}