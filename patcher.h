#pragma once
//21.03.23

#include <SFML/Graphics.hpp>

using namespace sf;

typedef struct
{
    Texture*    texture;
    Sprite*     sprite;

    int         start_X;
    int         start_Y;
    int         height;
    int         width;

    int         frame_amount;

    double     current_frame;
    double     frame_speed;
    float      move_speed;
} SCharacter;

void draw_project (void);

SCharacter* init_character (Texture* texture);

void simple_walk_sprite (Sprite* sprite);

void complex_walk_sprite (SCharacter* Character, double timegap);

void move_frame_right (SCharacter* Character);

void move_frame_left (SCharacter* Character);


void exit_window (RenderWindow* window);
