#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>

const int FRAMEBUFFER_WIDTH = 500, FRAMEBUFFER_HEIGHT = 200;

const int FRAMEBUFFER_SIZE = FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT;

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    Color(int red = 0, int green = 0, int blue = 0, int alpha = 255)
        : r(colorClamp(red)), g(colorClamp(green)), b(colorClamp(blue)), a(colorClamp(alpha)) {}

    private:
        //Clamp para evitar valores invalidos
        unsigned char colorClamp(const int value) {
            if (value > 255) return 255;
            else if (value < 0) return 0;
            else return value;
        }      

};

Color framebuffer[FRAMEBUFFER_SIZE];
Color backbuffer[FRAMEBUFFER_SIZE];
Color currentColor(255,255,255,255);
Color clearColor(0,0,0,255);

void setCurrentColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) {
	currentColor = Color(r, g, b, a);
}

void clear() {
    for (int i = 0; i < FRAMEBUFFER_SIZE; i++) {
        framebuffer[i] = clearColor;
    }
}

void point(int x, int y) {
    if (x >= 0 && x < FRAMEBUFFER_WIDTH && y >= 0 && y < FRAMEBUFFER_HEIGHT) {
        framebuffer[y * FRAMEBUFFER_WIDTH + x] = currentColor;
    }
}

void point(int x, int y, Color color) {
    if (x >= 0 && x < FRAMEBUFFER_WIDTH && y >= 0 && y < FRAMEBUFFER_HEIGHT) {
        framebuffer[y * FRAMEBUFFER_WIDTH + x] = color;
    }
}

void renderBuffer(SDL_Renderer* renderer) {
    // Create a texture
    SDL_Texture* texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,
        FRAMEBUFFER_WIDTH, 
        FRAMEBUFFER_HEIGHT
    );

    // Update the texture with the pixel data from the framebuffer
    SDL_UpdateTexture(
        texture, 
        NULL, 
        framebuffer, 
        FRAMEBUFFER_WIDTH * sizeof(Color)
    );

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}

bool isAlive(int x, int y) {
    if( x >= 0 && x < FRAMEBUFFER_WIDTH && y >= 0 && y < FRAMEBUFFER_HEIGHT ){

        if( backbuffer[y*FRAMEBUFFER_WIDTH + x].r == 255 && backbuffer[y*FRAMEBUFFER_WIDTH + x].g == 255 && backbuffer[y*FRAMEBUFFER_WIDTH + x].b == 255) {
            return true;
        }

    }
    
    return false;
}

void evalCell(int x, int y) {

    unsigned int count = 0;

    if( isAlive(x + 1, y) ) count += 1;
    if( isAlive(x - 1, y) ) count += 1;
    if( isAlive(x, y + 1) ) count += 1;
    if( isAlive(x, y - 1) ) count += 1;
    if( isAlive(x + 1, y + 1) ) count += 1;
    if( isAlive(x + 1, y - 1) ) count += 1;
    if( isAlive(x - 1, y + 1) ) count += 1;
    if( isAlive(x - 1, y - 1) ) count += 1;

    if(isAlive(x, y)) {
        if ( count < 2 || count > 3 ) {
            point(x, y, Color(0,0,0,255));
        } else {
            point(x, y);
        }
        
    }

    else {
        if( count == 3 ) {
            point(x, y);
        }else {
            point(x, y, Color(0,0,0,255));
        }
    }

    return;

}

void render(SDL_Renderer* renderer) {
    // Clear the framebuffer
    //clear();

    for (int x = 0; x < FRAMEBUFFER_WIDTH; x++) {
        for (int y = 0; y < FRAMEBUFFER_HEIGHT; y++){
            evalCell(x, y);
        }
    }

    // Render the framebuffer to the screen
    renderBuffer(renderer);
}

void square(int x, int y){
    point(x, y);
    point(x+1, y);
    point(x, y+1);
    point(x+1, y+1);
}

void gosperGun(int x, int y) {
    square(x, y);
    square(x + 34, y - 2);

    point(x + 10, y);
    point(x + 10, y + 1);
    point(x + 10, y + 2);
    point(x + 11, y - 1);
    point(x + 12, y - 2);
    point(x + 13, y - 2);
    point(x + 11, y + 3);
    point(x + 12, y + 4);
    point(x + 13, y + 4);
    point(x + 14, y + 1);
    point(x + 15, y - 1);
    point(x + 15, y + 3);
    point(x + 16, y);
    point(x + 16, y + 1);
    point(x + 16, y + 2);
    point(x + 17, y + 1);

    square(x + 20, y - 2);
    point(x + 20, y);
    point(x + 21, y);
    point(x + 22, y + 1);
    point(x + 22, y - 3);
    point(x + 24, y - 3);
    point(x + 24, y - 4);
    point(x + 24, y + 1);
    point(x + 24, y + 2);
}

void hivenudger(int x, int y) {

    point(x, y);
    point(x + 1, y - 1);
    point(x + 2, y - 2);
    point(x + 3, y - 2);
    point(x, y + 1);
    point(x, y + 2);
    point(x + 1, y + 2);
    point(x + 2, y + 2);
    point(x + 1, y + 3);
    point(x + 1, y + 4);
    point(x + 1, y + 5);
    point(x + 1, y + 6);
    point(x + 2, y + 4);
    point(x + 3, y + 5);
    point(x + 2, y + 6);
    point(x + 2, y + 7);

    point(x + 5, y - 3);
    point(x + 6, y - 4);
    point(x + 6, y - 3);
    point(x + 7, y - 3);
    point(x + 7, y - 5);
    point(x + 8, y - 5);
    point(x + 8, y - 6);
    point(x + 9, y - 7);

    point(x + 11, y - 7);
    point(x + 11, y - 6);

    point(x + 9, y - 3);
    point(x + 10, y - 4);

    point(x + 4, y);
    point(x + 5, y - 1);
    point(x + 6, y - 1);
    point(x + 7, y - 1);
    point(x + 8, y - 1);
    point(x + 9, y - 1);

    point(x + 6, y + 1);
    point(x + 7, y + 1);
    point(x + 6, y + 2);
    point(x + 7, y + 2);
    point(x + 8, y + 2);
    point(x + 9, y + 2);
    point(x + 9, y + 3);

    point(x + 4, y + 7);
    point(x + 5, y + 7);
    point(x + 6, y + 7);
    point(x + 5, y + 6);
    point(x + 6, y + 6);

    point(x + 17, y + 6);
    point(x + 19, y + 6);

    point(x + 8, y + 6);
    point(x + 8, y + 7);

    point(x + 12, y + 7);
    point(x + 14, y + 7);
    point(x + 15, y + 7);
    point(x + 16, y + 7);
    point(x + 17, y + 7);
    point(x + 19, y + 7);

    point(x + 9, y + 8);
    point(x + 10, y + 8);
    point(x + 12, y + 8);
    point(x + 14, y + 8);
    point(x + 15, y + 8);
    point(x + 18, y + 8);

    point(x + 4, y + 9);
    point(x + 5, y + 9);
    point(x + 6, y + 9);
    point(x + 7, y + 9);
    point(x + 8, y + 9);
    point(x + 9, y + 9);
    point(x + 11, y + 9);
    point(x + 12, y + 9);
    point(x + 16, y + 9);
    point(x + 17, y + 9);
    point(x + 18, y + 9);
    point(x + 19, y + 9);

    point(x + 5, y + 10);
    point(x + 10, y + 10);
    point(x + 11, y + 10);
    point(x + 12, y + 10);
    point(x + 19, y + 10);

    point(x + 6, y + 11);
    point(x + 7, y + 11);
    point(x + 13, y + 11);
    point(x + 14, y + 11);
    point(x + 17, y + 11);
    point(x + 18, y + 11);

    point(x + 7, y + 12);
    point(x + 10, y + 12);
    point(x + 16, y + 12);
    point(x + 17, y + 12);
    point(x + 18, y + 12);
    point(x + 19, y + 12);

    point(x + 8, y + 13);
    point(x + 10, y + 13);
    point(x + 12, y + 13);
    point(x + 13, y + 13);
    point(x + 19, y + 13);

    point(x + 17, y - 1);
    point(x + 18, y - 1);
    point(x + 19, y - 1);
    point(x + 20, y - 1);
    point(x + 26, y - 1);
    point(x + 29, y - 1);

    point(x + 17, y);
    point(x + 21, y);
    point(x + 25, y);

    point(x + 17, y + 1);
    point(x + 25, y + 1);
    point(x + 29, y + 1);

    point(x + 18, y + 2);
    point(x + 21, y + 2);
    point(x + 25, y + 2);
    point(x + 26, y + 2);
    point(x + 27, y + 2);
    point(x + 28, y + 2);

    point(x + 18, y + 16);
    point(x + 21, y + 16);
    point(x + 25, y + 16);
    point(x + 26, y + 16);
    point(x + 27, y + 16);
    point(x + 28, y + 16);

    point(x + 17, y + 17);
    point(x + 25, y + 17);
    point(x + 29, y + 17);

    point(x + 17, y + 18);
    point(x + 21, y + 18);
    point(x + 25, y + 18);

    point(x + 17, y + 19);
    point(x + 18, y + 19);
    point(x + 19, y + 19);
    point(x + 20, y + 19);
    point(x + 26, y + 19);
    point(x + 29, y + 19);

    square(x + 27, y + 8);
    square(x + 28, y + 8);
    square(x + 27, y + 9);
    square(x + 28, y + 9);

    square(x + 22, y + 4);
    square(x + 22, y + 6);
    square(x + 22, y + 8);
    square(x + 22, y + 10);
    square(x + 22, y + 12);
    point(x + 22, y + 14);
    point(x + 23, y + 14);

}

void thunderbird(int x, int y) {
    point(x, y);
    point(x + 1, y);
    point(x + 2, y);
    point(x + 1, y + 2);
    point(x + 1, y + 3);
    point(x + 1, y + 4);
}

void justyna(int x, int y) {
    point(x + 17, y);
    point(x + 16, y + 1);
    point(x + 19, y + 1);
    point(x + 17, y + 2);
    point(x + 18, y + 2);
    point(x + 19, y + 2);
    point(x + 20, y + 3);
    point(x + 17, y + 3);
    point(x, y + 5);
    point(x + 1, y + 5);
    point(x + 1, y + 6);
    point(x + 18, y + 5);
    point(x + 18, y + 6);
    point(x + 18, y + 7);
    point(x + 19, y + 15);
    point(x + 20, y + 15);
    point(x + 21, y + 15);
    point(x + 11, y + 16);
    point(x + 12, y + 16);
    point(x + 13, y + 16);

}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Game of Life", 50, 50, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    bool running = true;
    SDL_Event event;

    hivenudger(450,50);
    gosperGun(200, 50);
    thunderbird(250,100);
    justyna(150,100);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        std::copy_n(framebuffer, FRAMEBUFFER_SIZE, backbuffer);

        // Call our render function
        render(renderer);

        // Present the frame buffer to the screen
        SDL_RenderPresent(renderer);

        // Delay to limit the frame rate
        SDL_Delay(1000 / 60);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}