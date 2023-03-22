//21.03.23
#include <SFML/Graphics.hpp>

#include "patcher.h"
#include "stdlib.h"
#include "stdio.h"


using namespace sf;

#define FRAME_CNT 14

#define PRINTED(PRINTED_KEY) if (Keyboard::isKeyPressed (Keyboard::PRINTED_KEY))

void draw_project (void)
{
    unsigned int window_height = 300;
    unsigned int window_width  = 300;

    RenderWindow window(VideoMode(window_width, window_height), "");

    Texture texture;
    texture.loadFromFile ("MEDIA/Character.png");
    SCharacter* Character = init_character (&texture);

    double timegap = 800;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        complex_walk_sprite (Character, timegap);

        exit_window (&window);

        window.clear();
        window.draw (MySimpleCircle);
        window.draw (*(Character->sprite));
        window.display();
    }

    free (Character);

    return;
}

SCharacter* init_character (Texture* texture)
{
    SCharacter* Character = (SCharacter*) calloc (1, sizeof (*Character));

    Character->texture  = texture;
    Character->sprite   = (Sprite*) calloc (1, sizeof (*Character->sprite));

    Character->sprite->setTexture (*texture);

    Character->start_X  = 0;
    Character->start_Y  = 0;
    Character->height   = 300;
    Character->width    = 100;
    Character->sprite->setTextureRect (IntRect (Character->start_X, Character->start_Y, Character->width, Character->height));

    Character->current_frame = 0;
    Character->move_speed = 0.00001;
    Character->frame_speed = 0.005;

    Character->frame_amount = 10;
    //sprite->setPosition (0, 0);

    return Character;
}

void simple_walk_sprite (Sprite* sprite)
{
    float roll_speed = 0.5;

    PRINTED (A)
    {
        sprite->move (- roll_speed, 0);
    }

    PRINTED (D)
    {
        sprite->move (roll_speed, 0);
    }

    PRINTED (W)
    {
        sprite->move (0, - roll_speed);
    }

    PRINTED (S)
    {
        sprite->move (0, roll_speed);
    }

    return;
}

void complex_walk_sprite (SCharacter* Character, double timegap)
{
    float movegap  = (float) ( Character->move_speed * timegap);

    PRINTED (A)
    {
        Character->sprite->move (- Character->move_speed , 0);
        move_frame_left (Character);

    }

    PRINTED (D)
    {
        Character->sprite->move (Character->move_speed , 0);
        move_frame_right (Character);
    }

    PRINTED (W)
    {
        Character->sprite->move (0, - Character->move_speed );
    }

    PRINTED (S)
    {
        Character->sprite->move (0, Character->move_speed );
    }

    return;
}

void move_frame_right (SCharacter* Character)
{
    Character->current_frame += Character->frame_speed;

    if (Character->current_frame >= Character->frame_amount)
    {
        Character->current_frame -= Character->frame_amount;
    }

    Character->sprite->setTextureRect (IntRect (
        Character->width * ((int) Character->current_frame),
        Character->start_Y,
        Character->width,
        Character->height));

    return;
}

void move_frame_left (SCharacter* Character)
{
    Character->current_frame += Character->frame_speed;

    if (Character->current_frame >= Character->frame_amount)
    {
        Character->current_frame -= Character->frame_amount;
    }

    Character->sprite->setTextureRect (IntRect (
        Character->width * ((int) Character->current_frame) + Character->width,
        Character->start_Y,
        - Character->width,
        Character->height));

    return;
}

void exit_window (RenderWindow* window)
{
    if (Keyboard::isKeyPressed (Keyboard::Escape))
    {
        window->close ();
    }

    return;
}
