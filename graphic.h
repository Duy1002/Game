#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED



#include <SDL.h>
#include "button.h"
#include "menu.h"
#include "logic.h"
#include "enemy.h"
#include "bullet.h"
#include "tower.h"
#include <vector>
#include <list>
#include <tuple>



//#define VIRTUAL_MACHINE



namespace graphic {
    #define SCREEN_WIDTH 1120
    #define SCREEN_HEIGHT 630
    #define WINDOW_TITLE "Tower Defense"

    SDL_Window *window;
    SDL_Renderer *renderer;

    void log_error_and_exit(const char *message, const char *error) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", message, error);
        SDL_Quit();
    }

    void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING)) log_error_and_exit("SDL_Init", SDL_GetError());
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) log_error_and_exit("CreateWindow", SDL_GetError());
        #ifdef VIRTUAL_MACHINE
            renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
        #else
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        #endif // VIRTUAL_MACHINE
        if (renderer == nullptr) log_error_and_exit("CreateRenderer", SDL_GetError());
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    void quit_SDL() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void present() {
        #ifdef VIRTUAL_MACHINE
            SDL_UpdateWindowSurface(window);
        #else
            SDL_RenderPresent(renderer);
        #endif
    }

    void reset_screen() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void draw_rectangle(int x, int y, int w, int h) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect filled_rect;
        filled_rect.x = x, filled_rect.y = y, filled_rect.w = w, filled_rect.h = h;
        SDL_RenderFillRect(renderer, &filled_rect);
    }

    void draw_black_rectangle(int x, int y, int w, int h) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect filled_rect;
        filled_rect.x = x, filled_rect.y = y, filled_rect.w = w, filled_rect.h = h;
        SDL_RenderFillRect(renderer, &filled_rect);
    }

    void draw_circle(int x, int y, int r, int w) {
        --w;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = r + w, j = 0; i >= 0; --i) {
            while (i * i + j * j < r * r) ++j;
            for (int k = j; k <= r + w; ++k) {
                if (i * i + k * k > (r + w) * (r + w)) break;
                SDL_RenderDrawPoint(renderer, x + i, y + k);
            }
        }
        for (int i = r + w, j = 0; i >= 0; --i) {
            while (i * i + j * j < r * r) --j;
            for (int k = j; k >= -r - w; --k) {
                if (i * i + k * k > (r + w) * (r + w)) break;
                SDL_RenderDrawPoint(renderer, x + i, y + k);
            }
        }
        for (int i = 0, j = r + w; i >= -r - w; --i) {
            while (i * i + j * j > (r + w) * (r + w)) --j;
            for (int k = j; k >= 0; --k) {
                if (i * i + k * k < r * r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + k);
            }
        }
        for (int i = 0, j = -r - w; i >= -r - w; --i) {
            while (i * i + j * j > (r + w) * (r + w)) ++j;
            for (int k = j; k <= 0; ++k) {
                if (i * i + k * k < r * r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + k);
            }
        }
    }

    void draw_filled_circle(int x, int y, int r) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = r; i >= 0; --i) {
            for (int j = 0; j <= r; ++j) {
                if (i * i + j * j > r * r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
        for (int i = r; i >= 0; --i) {
            for (int j = 0; j >= -r; --j) {
                if (i * i + j * j > r * r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
        for (int i = 0; i >= -r; --i) {
            for (int j = 0; j <= r; ++j) {
                if (i * i + j * j > r * r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
        for (int i = 0; i >= -r; --i) {
            for (int j = 0; j >= -r; --j) {
                if (i * i + j * j > r * r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
    }

    void draw_filled_black_circle(int x, int y, int r) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int i = r; i >= 0; --i) {
            for (int j = 0; j <= r; ++j) {
                if (i * i + j * j > r * r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
        for (int i = r; i >= 0; --i) {
            for (int j = 0; j >= -r; --j) {
                if (i * i + j * j > r * r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
        for (int i = 0; i >= -r; --i) {
            for (int j = 0; j <= r; ++j) {
                if (i * i + j * j > r * r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
        for (int i = 0; i >= -r; --i) {
            for (int j = 0; j >= -r; --j) {
                if (i * i + j * j > r * r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
    }

    void draw_diamond(int x, int y, int r, int w) {
        --w;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = r + w, j = 0; i >= 0; --i) {
            while (i + j < r) ++j;
            for (int k = j; k <= r + w; ++k) {
                if (i + k > r + w) break;
                SDL_RenderDrawPoint(renderer, x + i, y + k);
            }
        }
        for (int i = r + w, j = 0; i >= 0; --i) {
            while (i - j < r) --j;
            for (int k = j; k >= -r - w; --k) {
                if (i - k > r + w) break;
                SDL_RenderDrawPoint(renderer, x + i, y + k);
            }
        }
        for (int i = 0, j = r + w; i >= -r - w; --i) {
            while (-i + j > r + w) --j;
            for (int k = j; k >= 0; --k) {
                if (-i + k < r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + k);
            }
        }
        for (int i = 0, j = -r - w; i >= -r - w; --i) {
            while (-i - j > r + w) ++j;
            for (int k = j; k <= 0; ++k) {
                if (-i - k < r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + k);
            }
        }
    }

    void draw_filled_black_diamond(int x, int y, int r) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int i = 0; i > -r; --i) {
            for (int j = 0; j > -r; --j) {
                if (-i - j >= r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j > -r; --j) {
                if (i - j >= r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
        for (int i = 0; i > -r; --i) {
            for (int j = 0; j < r; ++j) {
                if (-i + j >= r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < r; ++j) {
                if (i + j >= r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
    }

    void draw_half_filled_diamond(int x, int y, int r) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i > -r; --i) {
            for (int j = 0; j > -r; --j) {
                if (-i - j >= r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j > -r; --j) {
                if (i - j >= r) break;
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
    }

    void draw_A(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size, y + size * 3, size * 3, size);
        draw_rectangle(x, y + size, size, size * 5);
        draw_rectangle(x + size * 4, y + size, size, size * 5);
    }

    void draw_B(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
        draw_rectangle(x, y, size, size * 6);
        draw_rectangle(x + size * 4, y + size, size, size * 3 / 2);
        draw_rectangle(x + size, y + size * 5 / 2, size * 3, size);
        draw_rectangle(x + size * 4, y + size * 7 / 2, size, size * 3 / 2);
    }

    void draw_C(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
        draw_rectangle(x, y + size, size, size * 4);
        draw_rectangle(x + size * 4, y + size, size, size);
        draw_rectangle(x + size * 4, y + size * 4, size, size);
    }

    void draw_D(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
        draw_rectangle(x, y, size, size * 6);
        draw_rectangle(x + size * 4, y + size, size, size * 4);
    }

    void draw_E(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 4, size);
        draw_rectangle(x + size, y + size * 5, size * 4, size);
        draw_rectangle(x, y, size, size * 6);
        draw_rectangle(x + size, y + size * 5 / 2, size * 4, size);
    }

    void draw_F(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 4, size);
        draw_rectangle(x, y, size, size * 6);
        draw_rectangle(x + size, y + size * 5 / 2, size * 4, size);
    }

    void draw_G(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
        draw_rectangle(x, y + size, size, size * 4);
        draw_rectangle(x + size * 4, y + size, size, size);
        draw_rectangle(x + size * 4, y + size * 4, size, size);
        draw_rectangle(x + size * 3, y + size * 3, size * 2, size);
    }

    void draw_H(int x, int y, int size) {
        draw_rectangle(x, y, size, size * 6);
        draw_rectangle(x + size * 4, y, size, size * 6);
        draw_rectangle(x + size, y + size * 5 / 2, size * 3, size);
    }

    void draw_I(int x, int y, int size) {
        draw_rectangle(x, y, size * 5, size);
        draw_rectangle(x, y + size * 5, size * 5, size);
        draw_rectangle(x + size * 2, y + size, size, size * 4);
    }

    void draw_J(int x, int y, int size) {
        draw_rectangle(x + size * 2, y, size * 3, size);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
        draw_rectangle(x + size * 4, y + size, size, size * 4);
        draw_rectangle(x, y + size * 4, size, size);
    }

    void draw_K(int x, int y, int size) {
        draw_rectangle(x, y, size, size * 6);
        draw_rectangle(x + size, y + size * 2, size * 2, size);
        draw_rectangle(x + size * 3, y + size, size, size);
        draw_rectangle(x + size * 4, y, size, size);
        draw_rectangle(x + size * 3, y + size * 3, size, size);
        draw_rectangle(x + size * 4, y + size * 4, size, size * 2);
    }

    void draw_L(int x, int y, int size) {
        draw_rectangle(x, y, size, size * 6);
        draw_rectangle(x + size, y + size * 5, size * 4, size);
    }

    void draw_M(int x, int y, int size) {
        draw_rectangle(x, y, size, size * 6);
        draw_rectangle(x + size * 4, y, size, size * 6);
        draw_rectangle(x + size, y + size, size, size);
        draw_rectangle(x + size * 3, y + size, size, size);
        draw_rectangle(x + size * 2, y + size * 2, size, size * 3);
    }

    void draw_N(int x, int y, int size) {
        draw_rectangle(x, y, size, size * 6);
        draw_rectangle(x + size * 4, y, size, size * 6);
        draw_rectangle(x + size, y + size, size, size);
        draw_rectangle(x + size * 3, y + size * 4, size, size);
        draw_rectangle(x + size * 2, y + size * 2, size, size * 2);
    }

    void draw_O(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
        draw_rectangle(x, y + size, size, size * 4);
        draw_rectangle(x + size * 4, y + size, size, size * 4);
    }

    void draw_P(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x, y, size, size * 6);
        draw_rectangle(x + size * 4, y + size, size, size * 2);
        draw_rectangle(x + size, y + size * 3, size * 3, size);
    }

    void draw_Q(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size, y + size * 5, size * 2, size);
        draw_rectangle(x, y + size, size, size * 4);
        draw_rectangle(x + size * 4, y + size, size, size * 3);
        draw_rectangle(x + size * 3, y + size * 4, size, size);
        draw_rectangle(x + size * 4, y + size * 5, size, size);
    }

    void draw_R(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x, y, size, size * 6);
        draw_rectangle(x + size * 4, y + size, size, size * 2);
        draw_rectangle(x + size, y + size * 3, size * 3, size);
        draw_rectangle(x + size * 4, y + size * 4, size, size * 2);
    }

    void draw_S(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 4, size);
        draw_rectangle(x, y + size * 5, size * 4, size);
        draw_rectangle(x, y + size, size, size * 3 / 2);
        draw_rectangle(x + size, y + size * 5 / 2, size * 3, size);
        draw_rectangle(x + size * 4, y + size * 7 / 2, size, size * 3 / 2);
    }

    void draw_T(int x, int y, int size) {
        draw_rectangle(x, y, size * 5, size);
        draw_rectangle(x + size * 2, y + size, size, size * 5);
    }

    void draw_U(int x, int y, int size) {
        draw_rectangle(x, y, size, size * 5);
        draw_rectangle(x + size * 4, y, size, size * 5);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
    }

    void draw_V(int x, int y, int size) {
        draw_rectangle(x, y, size, size * 4);
        draw_rectangle(x + size * 4, y, size, size * 4);
        draw_rectangle(x + size, y + size * 4, size, size);
        draw_rectangle(x + size * 2, y + size * 5, size, size);
        draw_rectangle(x + size * 3, y + size * 4, size, size);
    }

    void draw_W(int x, int y, int size) {
        draw_rectangle(x, y, size, size * 6);
        draw_rectangle(x + size * 4, y, size, size * 6);
        draw_rectangle(x + size, y + size * 4, size, size);
        draw_rectangle(x + size * 3, y + size * 4, size, size);
        draw_rectangle(x + size * 2, y + size, size, size * 3);
    }

    void draw_X(int x, int y, int size) {
        draw_rectangle(x, y, size, size * 3 / 2);
        draw_rectangle(x + size, y + size * 3 / 2, size, size);
        draw_rectangle(x + size * 4, y, size, size * 3 / 2);
        draw_rectangle(x + size * 3, y + size * 3 / 2, size, size);
        draw_rectangle(x + size * 2, y + size * 5 / 2, size, size);
        draw_rectangle(x + size, y + size * 7 / 2, size, size);
        draw_rectangle(x, y + size * 9 / 2, size, size * 3 / 2);
        draw_rectangle(x + size * 3, y + size * 7 / 2, size, size);
        draw_rectangle(x + size * 4, y + size * 9 / 2, size, size * 3 / 2);
    }

    void draw_Y(int x, int y, int size) {
        draw_rectangle(x, y, size, size * 2);
        draw_rectangle(x + size * 4, y, size, size * 2);
        draw_rectangle(x + size, y + size * 2, size, size);
        draw_rectangle(x + size * 2, y + size * 3, size, size * 3);
        draw_rectangle(x + size * 3, y + size * 2, size, size);
    }

    void draw_Z(int x, int y, int size) {
        draw_rectangle(x, y, size * 5, size);
        draw_rectangle(x + size * 4, y + size, size, size / 2);
        draw_rectangle(x + size * 3, y + size * 3 / 2, size, size);
        draw_rectangle(x + size * 2, y + size * 5 / 2, size, size);
        draw_rectangle(x + size, y + size * 7 / 2, size, size);
        draw_rectangle(x, y + size * 9 / 2, size, size / 2);
        draw_rectangle(x, y + size * 5, size * 5, size);
    }

    void draw_0(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
        draw_rectangle(x, y + size, size, size * 4);
        draw_rectangle(x + size * 4, y + size, size, size * 4);
        draw_rectangle(x + size, y + size * 7 / 2, size, size);
        draw_rectangle(x + size * 2, y + size * 5 / 2, size, size);
        draw_rectangle(x + size * 3, y + size * 3 / 2, size, size);
    }

    void draw_1(int x, int y, int size) {
        draw_rectangle(x, y + size * 2, size, size);
        draw_rectangle(x + size, y + size, size, size);
        draw_rectangle(x + size * 2, y, size, size * 5);
        draw_rectangle(x, y + size * 5, size * 5, size);
    }

    void draw_2(int x, int y, int size) {
        draw_rectangle(x, y + size, size, size);
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size * 4, y + size, size, size * 2);
        draw_rectangle(x + size, y + size * 3, size * 3, size);
        draw_rectangle(x, y + size * 4, size, size);
        draw_rectangle(x, y + size * 5, size * 5, size);
    }

    void draw_3(int x, int y, int size) {
        draw_rectangle(x, y, size * 4, size);
        draw_rectangle(x + size * 4, y + size, size, size * 4);
        draw_rectangle(x, y + size * 5, size * 4, size);
        draw_rectangle(x, y + size * 5 / 2, size * 4, size);
    }

    void draw_4(int x, int y, int size) {
        draw_rectangle(x, y, size, size * 5 / 2);
        draw_rectangle(x + size, y + size * 5 / 2, size * 3, size);
        draw_rectangle(x + size * 4, y, size, size * 6);
    }

    void draw_5(int x, int y, int size) {
        draw_rectangle(x, y, size * 5, size);
        draw_rectangle(x, y + size, size, size);
        draw_rectangle(x, y + size * 2, size * 4, size);
        draw_rectangle(x + size * 4, y + size * 3, size, size * 2);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
        draw_rectangle(x, y + size * 4, size, size);
    }

    void draw_6(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size, y + size * 5 / 2, size * 3, size);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
        draw_rectangle(x, y + size, size, size * 4);
        draw_rectangle(x + size * 4, y + size, size, size);
        draw_rectangle(x + size * 4, y + size * 7 / 2, size, size * 3 / 2);
    }

    void draw_7(int x, int y, int size) {
        draw_rectangle(x, y, size * 5, size);
        draw_rectangle(x + size * 4, y + size, size, size * 3 / 2);
        draw_rectangle(x + size * 3, y + size * 5 / 2, size, size * 3 / 2);
        draw_rectangle(x + size * 2, y + size * 4, size, size * 2);
    }

    void draw_8(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size, y + size * 5 / 2, size * 3, size);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
        draw_rectangle(x, y + size, size, size * 3 / 2);
        draw_rectangle(x, y + size * 7 / 2, size, size * 3 / 2);
        draw_rectangle(x + size * 4, y + size, size, size * 3 / 2);
        draw_rectangle(x + size * 4, y + size * 7 / 2, size, size * 3 / 2);
    }

    void draw_9(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size, y + size * 5 / 2, size * 3, size);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
        draw_rectangle(x, y + size, size, size * 3 / 2);
        draw_rectangle(x, y + size * 4, size, size);
        draw_rectangle(x + size * 4, y + size, size, size * 4);
    }

    void draw_dot(int x, int y, int size) {
        draw_rectangle(x, y + size * 5, size, size);
    }

    void draw_colon(int x, int y, int size) {
        draw_rectangle(x, y + size * 3 / 2, size, size);
        draw_rectangle(x, y + size * 9 / 2, size, size);
    }

    void draw_x(int x, int y, int size) {
        draw_rectangle(x, y + size, size, size);
        draw_rectangle(x + size * 4, y + size, size, size);
        draw_rectangle(x + size, y + size * 2, size, size);
        draw_rectangle(x + size * 3, y + size * 2, size, size);
        draw_rectangle(x + size * 2, y + size * 3, size, size);
        draw_rectangle(x + size, y + size * 4, size, size);
        draw_rectangle(x + size * 3, y + size * 4, size, size);
        draw_rectangle(x, y + size * 5, size, size);
        draw_rectangle(x + size * 4, y + size * 5, size, size);
    }

    void draw_dollar(int x, int y, int size) {
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size, y + size * 5, size * 3, size);
        draw_rectangle(x, y + size, size, size * 4);
        draw_rectangle(x + size * 4, y + size, size, size * 4);
        draw_rectangle(x + size * 2, y + size * 2, size, size * 2);
    }

    void draw_question(int x, int y, int size) {
        draw_rectangle(x, y + size, size, size);
        draw_rectangle(x + size, y, size * 3, size);
        draw_rectangle(x + size * 4, y + size, size, size);
        draw_rectangle(x + size * 3, y + size * 2, size, size);
        draw_rectangle(x + size * 2, y + size * 3, size, size * 3 / 2);
        draw_rectangle(x + size * 2, y + size * 5, size, size);
    }

    void draw_char(int x, int y, int size, char c) {
        switch (c) {
            case 'A': draw_A(x, y, size); break;
            case 'B': draw_B(x, y, size); break;
            case 'C': draw_C(x, y, size); break;
            case 'D': draw_D(x, y, size); break;
            case 'E': draw_E(x, y, size); break;
            case 'F': draw_F(x, y, size); break;
            case 'G': draw_G(x, y, size); break;
            case 'H': draw_H(x, y, size); break;
            case 'I': draw_I(x, y, size); break;
            case 'J': draw_J(x, y, size); break;
            case 'K': draw_K(x, y, size); break;
            case 'L': draw_L(x, y, size); break;
            case 'M': draw_M(x, y, size); break;
            case 'N': draw_N(x, y, size); break;
            case 'O': draw_O(x, y, size); break;
            case 'P': draw_P(x, y, size); break;
            case 'Q': draw_Q(x, y, size); break;
            case 'R': draw_R(x, y, size); break;
            case 'S': draw_S(x, y, size); break;
            case 'T': draw_T(x, y, size); break;
            case 'U': draw_U(x, y, size); break;
            case 'V': draw_V(x, y, size); break;
            case 'W': draw_W(x, y, size); break;
            case 'X': draw_X(x, y, size); break;
            case 'Y': draw_Y(x, y, size); break;
            case 'Z': draw_Z(x, y, size); break;
            case '0': draw_0(x, y, size); break;
            case '1': draw_1(x, y, size); break;
            case '2': draw_2(x, y, size); break;
            case '3': draw_3(x, y, size); break;
            case '4': draw_4(x, y, size); break;
            case '5': draw_5(x, y, size); break;
            case '6': draw_6(x, y, size); break;
            case '7': draw_7(x, y, size); break;
            case '8': draw_8(x, y, size); break;
            case '9': draw_9(x, y, size); break;
            case '.': draw_dot(x, y, size); break;
            case ':': draw_colon(x, y, size); break;
            case 'x': draw_x(x, y, size); break;
            case '$': draw_dollar(x, y, size); break;
            case '?': draw_question(x, y, size); break;
            default: break;
        }
    }

    void draw_string(int x, int y, int size, const char *str) {
        for (int i = 0; str[i] != '\0'; ++i) {
            if (i) x += size;
            draw_char(x, y, size, str[i]);
            if (str[i] == '.' || str[i] == ':') x += size;
            else x += size * 5;
        }
    }

    void draw_button(button b) {
        if (b.big) {
            for (size_t i = 0; i < b.s.size(); ++i)
                graphic::draw_string(std::get<0>(b.s[i]), std::get<1>(b.s[i]), std::get<2>(b.s[i]), std::get<3>(b.s[i]));
            int x = (5 * b.x - b.z) / 4, y = (5 * b.y - b.t) / 4;
            int end_x = x + strlen(b.str) * 36 + 24;
            draw_string(x + 30, y + 30, 6, b.str);
            draw_rectangle(x + 24, y, end_x - x - 18, 6);
            draw_rectangle(x + 18, y + 6, 6, 6);
            draw_rectangle(x + 12, y + 12, 6, 6);
            draw_rectangle(x + 6, y + 18, 6, 6);
            draw_rectangle(x, y + 24, 6, 48);
            draw_rectangle(x + 6, y + 72, 6, 6);
            draw_rectangle(x + 12, y + 78, 6, 6);
            draw_rectangle(x + 18, y + 84, 6, 6);
            draw_rectangle(x + 24, y + 90, end_x - x - 18, 6);
            draw_rectangle(end_x + 6, y + 6, 6, 6);
            draw_rectangle(end_x + 12, y + 12, 6, 6);
            draw_rectangle(end_x + 18, y + 18, 6, 6);
            draw_rectangle(end_x + 24, y + 24, 6, 48);
            draw_rectangle(end_x + 18, y + 72, 6, 6);
            draw_rectangle(end_x + 12, y + 78, 6, 6);
            draw_rectangle(end_x + 6, y + 84, 6, 6);
        } else {
            int x = b.x, y = b.y;
            int end_x = x + strlen(b.str) * 24 + 16;
            draw_string(x + 20, y + 20, 4, b.str);
            draw_rectangle(x + 16, y, end_x - x - 12, 4);
            draw_rectangle(x + 12, y + 4, 4, 4);
            draw_rectangle(x + 8, y + 8, 4, 4);
            draw_rectangle(x + 4, y + 12, 4, 4);
            draw_rectangle(x, y + 16, 4, 32);
            draw_rectangle(x + 4, y + 48, 4, 4);
            draw_rectangle(x + 8, y + 52, 4, 4);
            draw_rectangle(x + 12, y + 56, 4, 4);
            draw_rectangle(x + 16, y + 60, end_x - x - 12, 4);
            draw_rectangle(end_x + 4, y + 4, 4, 4);
            draw_rectangle(end_x + 8, y + 8, 4, 4);
            draw_rectangle(end_x + 12, y + 12, 4, 4);
            draw_rectangle(end_x + 16, y + 16, 4, 32);
            draw_rectangle(end_x + 12, y + 48, 4, 4);
            draw_rectangle(end_x + 8, y + 52, 4, 4);
            draw_rectangle(end_x + 4, y + 56, 4, 4);
        }
    }

    void draw_menu(menu m) {
        for (size_t i = 0; i < m.rect.size(); ++i)
            draw_rectangle(std::get<0>(m.rect[i]), std::get<1>(m.rect[i]), std::get<2>(m.rect[i]), std::get<3>(m.rect[i]));
        for (size_t i = 0; i < m.b.size(); ++i) draw_button(std::get<0>(m.b[i]));
        for (size_t i = 0; i < m.s.size(); ++i)
            draw_string(std::get<0>(m.s[i]), std::get<1>(m.s[i]), std::get<2>(m.s[i]), std::get<3>(m.s[i]));
    }

    void draw_enemy(enemy e) {
        switch (e.type) {
            case 1:
                draw_circle(std::get<0>(logic::path[e.x]), std::get<1>(logic::path[e.x]), 20, 3);
                draw_filled_black_circle(std::get<0>(logic::path[e.x]), std::get<1>(logic::path[e.x]), 19);
                if (e.health < 10) {
                    draw_char(std::get<0>(logic::path[e.x]) - 5, std::get<1>(logic::path[e.x]) - 6, 2, '0' + e.health);
                } else {
                    draw_char(std::get<0>(logic::path[e.x]) - 11, std::get<1>(logic::path[e.x]) - 6, 2, '0' + e.health / 10);
                    draw_char(std::get<0>(logic::path[e.x]) + 1, std::get<1>(logic::path[e.x]) - 6, 2, '0' + e.health % 10);
                }
                break;
            default: break;
        }
    }

    void draw_bullet(bullet b) {
        switch (b.type) {
            case 1:
                draw_filled_circle(b.x, b.y, 5);
                break;
            default: break;
        }
    }

    void draw_tower(tower t) {
        switch (t.type) {
            case 1:
            draw_circle(t.x, t.y, 20, 5);
            draw_filled_circle(t.x, t.y, 5);
            break;
            default: break;
        }
    }

    void draw_enemy() {
        for (std::list<enemy>::iterator i = logic::e.begin(); i != logic::e.end(); ++i) draw_enemy(*i);
    }

    void draw_bullet() {
        for (std::list<bullet>::iterator i = logic::b.begin(); i != logic::b.end(); ++i) draw_bullet(*i);
    }

    void draw_tower() {
        for (std::list<tower>::iterator i = logic::t.begin(); i != logic::t.end(); ++i) draw_tower(*i);
    }

    void draw_grid() {
        draw_black_rectangle(0, 0, 1120, 90);
        draw_black_rectangle(960, 90, 160, 540);
        draw_black_rectangle(0, 510, 960, 120);
        draw_rectangle(0, 88, 1120, 4);
        draw_rectangle(958, 0, 4, 630);
        draw_rectangle(0, 508, 960, 4);
        draw_rectangle(0, 90, 2, 420);
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 16; ++j) {
                if (logic::grid[i][j]) {
                    if (i && logic::grid[i - 1][j] != 1) draw_rectangle(j * 60 - 2, i * 60 + 88, 64, 4);
                    if (j && logic::grid[i][j - 1] != 1) draw_rectangle(j * 60 - 2, i * 60 + 88, 4, 64);
                    if (i < 6 && logic::grid[i + 1][j] != 1) draw_rectangle(j * 60 - 2, i * 60 + 148, 64, 4);
                    if (j < 15 && logic::grid[i][j + 1] != 1) draw_rectangle(j * 60 + 58, i * 60 + 88, 4, 64);
                } else {
                    draw_rectangle(j * 60 - 1, i * 60 + 89, 62, 2);
                    draw_rectangle(j * 60 - 1, i * 60 + 89, 2, 62);
                    draw_rectangle(j * 60 - 1, i * 60 + 149, 62, 2);
                    draw_rectangle(j * 60 + 59, i * 60 + 89, 2, 62);
                }
            }
        }
    }

    void draw_info() {
        draw_string(33, 33, 4, logic::difficulty_name[logic::difficulty]);
        draw_string(400, 33, 4, "ROUND: ");
        if (logic::round > 99) {
            draw_char(548, 33, 4, char('0' + logic::round / 100));
            draw_char(572, 33, 4, char('0' + (logic::round / 10) % 10));
            draw_char(596, 33, 4, char('0' + logic::round % 10));
        } else if (logic::round > 9) {
            draw_char(548, 33, 4, char('0' + logic::round / 10));
            draw_char(572, 33, 4, char('0' + logic::round % 10));
        } else {
            draw_char(548, 33, 4, char('0' + logic::round));
        }
        draw_string(735, 33, 4, "LIVES: ");
        if (logic::lives > 9) {
            draw_char(883, 33, 4, char('0' + logic::lives / 10));
            draw_char(907, 33, 4, char('0' + logic::lives % 10));
        } else {
            draw_char(883, 33, 4, char('0' + logic::lives));
        }
        draw_char(1078, 27, 6, char('$'));
        if (logic::money > 999) {
            draw_char(972, 33, 4, char('0' + logic::money / 1000));
            draw_char(996, 33, 4, char('0' + (logic::money / 100) % 10));
            draw_char(1020, 33, 4, char('0' + (logic::money / 10) % 10));
            draw_char(1044, 33, 4, char('0' + logic::money % 10));
        } else if (logic::money > 99) {
            draw_char(996, 33, 4, char('0' + logic::money / 100));
            draw_char(1020, 33, 4, char('0' + (logic::money / 10) % 10));
            draw_char(1044, 33, 4, char('0' + logic::money % 10));
        } else if (logic::money > 9) {
            draw_char(1020, 33, 4, char('0' + logic::money / 10));
            draw_char(1044, 33, 4, char('0' + logic::money % 10));
        } else {
            draw_char(1044, 33, 4, char('0' + logic::money));
        }
    }

    void draw_next_round_button() {
        draw_rectangle(logic::next_round_x, logic::next_round_y, 6, 50);
        draw_rectangle(logic::next_round_x + 308, logic::next_round_y, 6, 50);
        draw_rectangle(logic::next_round_x + 6, logic::next_round_y + 44, 302, 6);
        draw_black_rectangle(logic::next_round_x + 6, logic::next_round_y, 302, 44);
        draw_string(logic::next_round_x + 39, logic::next_round_y + 10, 4, "NEXT ROUND");
    }

    void draw_home_button() {
        if (logic::home_big) {
            draw_rectangle(logic::home_x - 21, logic::home_y - 21, 122, 2);
            draw_rectangle(logic::home_x - 21, logic::home_y + 99, 122, 2);
            draw_rectangle(logic::home_x - 21, logic::home_y - 19, 2, 118);
            draw_rectangle(logic::home_x + 99, logic::home_y - 19, 2, 118);
            draw_rectangle(logic::home_x + 7, logic::home_y + 40, 24, 45);
            draw_rectangle(logic::home_x + 49, logic::home_y + 40, 24, 45);
            draw_rectangle(logic::home_x + 31, logic::home_y + 40, 18, 24);
            draw_half_filled_diamond(logic::home_x + 40, logic::home_y + 40, 45);
        } else {
            draw_rectangle(logic::home_x - 1, logic::home_y - 1, 82, 2);
            draw_rectangle(logic::home_x - 1, logic::home_y + 79, 82, 2);
            draw_rectangle(logic::home_x - 1, logic::home_y + 1, 2, 78);
            draw_rectangle(logic::home_x + 79, logic::home_y + 1, 2, 78);
            draw_rectangle(logic::home_x + 18, logic::home_y + 40, 16, 30);
            draw_rectangle(logic::home_x + 46, logic::home_y + 40, 16, 30);
            draw_rectangle(logic::home_x + 34, logic::home_y + 40, 12, 16);
            draw_half_filled_diamond(logic::home_x + 40, logic::home_y + 40, 30);
        }
    }

    void draw_tower1_button() {
        if (logic::tower1_big) {
            draw_rectangle(logic::tower1_x - 21, logic::tower1_y - 21, 122, 2);
            draw_rectangle(logic::tower1_x - 21, logic::tower1_y + 99, 122, 2);
            draw_rectangle(logic::tower1_x - 21, logic::tower1_y - 19, 2, 118);
            draw_rectangle(logic::tower1_x + 99, logic::tower1_y - 19, 2, 118);
            draw_circle(logic::tower1_x + 40, logic::tower1_y + 40, 30, 8);
            draw_filled_circle(logic::tower1_x + 40, logic::tower1_y + 40, 8);
            if (!logic::is_holding_tower()) {
                draw_circle(60, 570, 40, 10);
                draw_filled_circle(60, 570, 10);
            }
        } else {
            draw_rectangle(logic::tower1_x - 1, logic::tower1_y - 1, 82, 2);
            draw_rectangle(logic::tower1_x - 1, logic::tower1_y + 79, 82, 2);
            draw_rectangle(logic::tower1_x - 1, logic::tower1_y + 1, 2, 78);
            draw_rectangle(logic::tower1_x + 79, logic::tower1_y + 1, 2, 78);
            draw_circle(logic::tower1_x + 40, logic::tower1_y + 40, 20, 5);
            draw_filled_circle(logic::tower1_x + 40, logic::tower1_y + 40, 5);
        }
    }

    void draw_tower2_button() {
        if (logic::tower2_big) {
            draw_rectangle(logic::tower2_x - 21, logic::tower2_y - 21, 122, 2);
            draw_rectangle(logic::tower2_x - 21, logic::tower2_y + 99, 122, 2);
            draw_rectangle(logic::tower2_x - 21, logic::tower2_y - 19, 2, 118);
            draw_rectangle(logic::tower2_x + 99, logic::tower2_y - 19, 2, 118);
        } else {
            draw_rectangle(logic::tower2_x - 1, logic::tower2_y - 1, 82, 2);
            draw_rectangle(logic::tower2_x - 1, logic::tower2_y + 79, 82, 2);
            draw_rectangle(logic::tower2_x - 1, logic::tower2_y + 1, 2, 78);
            draw_rectangle(logic::tower2_x + 79, logic::tower2_y + 1, 2, 78);
        }
    }

    void draw_tower3_button() {
        if (logic::tower3_big) {
            draw_rectangle(logic::tower3_x - 21, logic::tower3_y - 21, 122, 2);
            draw_rectangle(logic::tower3_x - 21, logic::tower3_y + 99, 122, 2);
            draw_rectangle(logic::tower3_x - 21, logic::tower3_y - 19, 2, 118);
            draw_rectangle(logic::tower3_x + 99, logic::tower3_y - 19, 2, 118);
        } else {
            draw_rectangle(logic::tower3_x - 1, logic::tower3_y - 1, 82, 2);
            draw_rectangle(logic::tower3_x - 1, logic::tower3_y + 79, 82, 2);
            draw_rectangle(logic::tower3_x - 1, logic::tower3_y + 1, 2, 78);
            draw_rectangle(logic::tower3_x + 79, logic::tower3_y + 1, 2, 78);
        }
    }

    void draw_holding_tower1(int mouse_x, int mouse_y) {
        draw_circle(mouse_x, mouse_y, 20, 5);
        draw_filled_black_circle(mouse_x, mouse_y, 19);
        draw_filled_circle(mouse_x, mouse_y, 5);
        draw_circle(mouse_x, mouse_y, 210, 2);
        draw_char(440, 522, 16, 'x');
    }

    void draw_playing_screen(int mouse_x, int mouse_y) {
        draw_enemy();
        draw_bullet();
        draw_tower();
        draw_grid();
        draw_info();
        if (!logic::enemy_still_alive()) draw_next_round_button();
        draw_home_button();
        draw_tower1_button();
        draw_tower2_button();
        draw_tower3_button();
        if (logic::holding_tower1) draw_holding_tower1(mouse_x, mouse_y);
    }
};



#endif // GRAPHIC_H_INCLUDED
