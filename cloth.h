//
// Created by Avery Drennan on 4/27/23.
//

#ifndef CLOTH_SIM_CLOTH_H
#define CLOTH_SIM_CLOTH_H
#include <vector>
#include <utility>
#include <point.h>
#include <stick.h>
#include <SDL.h>

class cloth{
private:
    std::pair<double,double> gravity;
    std::pair<double,double> wind;
    double drag;
    int cloth_width;
    int cloth_height;
    int start_x;
    int start_y;
    int cloth_spacing;
    void texture_renderer(SDL_Renderer* renderer);

public:
    std::vector<point*> points{};
    std::vector<stick*> sticks{};
    cloth(int cloth_width, int cloth_height, int cloth_spacing,int start_x,int start_y);
    void render(SDL_Renderer* renderer,bool wire_frame);
    void update(double delta_time);
    void instantiate_neighbors();
    ~cloth() = default;

    double elasticity;
};


#endif //CLOTH_SIM_CLOTH_H
