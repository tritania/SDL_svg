#include "SDL_svg.h"

#ifdef _WIN32
#include <SDL.h>
#endif

#ifdef __linux__ 
#include <SDL2/SDL.h>
#endif

#include <signal.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480

int main(int argc, char *argv[])
{
int dx=0, dy=0;
SDL_Surface *screen;
SDL_Window* gWin = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* image_one = NULL;
int done;
SDL_Event event;
SDL_Rect full;
double Scalex, Scaley;
int redraw=0;
int code;

	if(argc<2)
	{
		printf("Usage: %s <filename> [dx] [dy]\n",argv[0]);
		exit(0);
	}

    printf("asdasdasdsadasda");
    
	/* Initialize SDL */
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		//fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		exit(1);
	}
    
    printf("asdasdasda");
    
	/* Set 640x480 32 bpp video mode */
    gWin = SDL_CreateWindow( "Hold", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if( gWin == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        exit(1);
    }
    
    printf("asdasdasda");
    gRenderer = SDL_CreateRenderer( gWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        exit(1);
    }
    printf("sdad");
	full.x = 0;
	full.y = 0;
	full.w = screen->w;
	full.h = screen->h;
	SDL_FillRect(screen, &full, SDL_MapRGB(screen->format, 0x80, 0x80, 0x80));


	SDL_svg_context *TestImage = SVG_Load (argv[1]);
	SVG_SetOffset (TestImage,SVG_Width(TestImage)/2,SVG_Height(TestImage)/2);

	if(argc>2) sscanf(argv[2], "%d", &dx);
	if(argc>3) sscanf(argv[3], "%d", &dy);

	Scalex = screen->w / SVG_Width(TestImage);
	Scaley = screen->h / SVG_Height(TestImage);
	SVG_SetScale (TestImage, Scalex, Scaley);
	SVG_RenderToSurface (TestImage,screen->w/2+dx,screen->h/2+dy,screen);
    
    image_one = SDL_CreateTextureFromSurface(gRenderer, screen);
    if (image_one == NULL) 
    {
        fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
        exit(1);
    }
    //SDL_FreeSurface(screen);
    //screen = NULL;



	done = 0;
	while ( !done )
	{
        SDL_SetRenderDrawColor( gRenderer, 0xD1, 0xD1, 0xE0, 0xFF );
        SDL_RenderClear( gRenderer );
        SDL_RenderCopy(gRenderer, image_one, NULL, NULL);
        SDL_RenderPresent( gRenderer );
	}
	SVG_Free (TestImage);
	return 0;
}
