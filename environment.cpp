//
// Created by Avery Drennan on 4/27/23.
//

#include "environment.h"
#include "event_data.h"

#define cloth_spacing 5

void environment::env_init(char* title,int window_width, int window_height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Error: %s\n",SDL_GetError());
    }

    window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
    window_width,window_height,SDL_WINDOW_SHOWN);

    if(!window)
    {
        printf("Error: %s\n",SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    if(!renderer)
    {
        printf("Error: %s\n",SDL_GetError());
    }

    this->fps_manager = static_cast<FPSmanager *>(malloc(sizeof(*fps_manager)));
    SDL_setFramerate(this->fps_manager,100);

    //sets up the cloth
    int cloth_width = 300/cloth_spacing;
    int cloth_height = 300/cloth_spacing;

    int start_x = window_width * 0.5f - cloth_width * cloth_spacing * 0.5f;
    int start_y = window_height * 0.1f;

    this->cloth = new class cloth(cloth_width,cloth_height,
            cloth_spacing,start_x,start_y);

    this->last_update_time = SDL_GetTicks();

}

environment::environment()
{
    window = nullptr;
    renderer = nullptr;
    this->event_data = new struct event_data();
}

void environment::run()
{
    SDL_Event event;
    while(!this->event_data->close)
    {
        this->event_handler(event);
        this->update();
        this->render();
        SDL_framerateDelay(this->fps_manager);
    }
}

void environment::event_handler(SDL_Event &event)
{
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            this->event_data->close = true;
        }

        else if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_m)
            {
                if(!event_data->wire_frame)
                    this->event_data->wire_frame = true;
                else
                    this->event_data->wire_frame = false;

            }
        }

        else if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(SDL_BUTTON_LEFT == event.button.button) {
                event_data->left_click = true;
            }

            if(SDL_BUTTON_RIGHT == event.button.button)
                event_data->right_click = true;

        }

        else if(event.type == SDL_MOUSEBUTTONUP)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
                event_data->left_click = false;

            else if(event.button.button == SDL_BUTTON_RIGHT)
                event_data->right_click = false;

            for(auto stick : cloth->sticks)
            {
                if(stick->highlighted())
                {
                    stick->Break();
                }
            }

        }

        else if(event_data->left_click && event.type == SDL_MOUSEMOTION)
        {
            printf("(%f,%f)\n",event_data->mouse_pos.first,event_data->mouse_pos.second);
            for(auto point: cloth->points)
            {
                if(distance_mouse_point(point) < 20)
                {
                    point->sticks.first->highlight();
                    point->sticks.second->highlight();

                }
            }
        }
    }
}

void environment::render()
{
    SDL_SetRenderDrawColor(this->renderer,0x0,0x0,0x0,SDL_ALPHA_OPAQUE);
    SDL_RenderSetViewport(this->renderer,nullptr);
    SDL_RenderClear(this->renderer);

    this->cloth->render(renderer,this->event_data->wire_frame);

    SDL_RenderPresent(renderer);
}

void environment::update() {
    double dt = calc_dt();
    this->mouse_pos();
    cloth->update(dt);
}

void environment::close() {
    delete(this);
}

environment::~environment() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    delete(this->event_data);

}

double environment::calc_dt() {
    uint32_t current_time = SDL_GetTicks();
    double delta_time = (current_time - last_update_time)/1000.f;
    this->last_update_time = current_time;
    return delta_time;
}

void environment::mouse_pos()
{
    int x,y;
    SDL_GetMouseState((&x), (&y));
    this->event_data->mouse_pos.first = x;
    this->event_data->mouse_pos.second = y;
}

double environment::distance_mouse_point(point* point)
{
    return sqrt(pow(event_data->mouse_pos.first - point->get_x(),2) +
                        pow(event_data->mouse_pos.second - point->get_y(),2));
}
