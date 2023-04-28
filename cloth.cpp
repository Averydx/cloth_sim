//
// Created by Avery Drennan on 4/27/23.
//

#include "cloth.h"

cloth::cloth(int cloth_width, int cloth_height, int cloth_spacing,int start_x,int start_y) {
    this->gravity = std::make_pair<double,double>(0.f,100.f);
    this->wind = std::make_pair<double,double>(25.f,0.f);
    this->drag = 0.01f;
    this->elasticity = 10.0f;

    for(int y = 0; y <= cloth_height; y++)
    {
        for(int x = 0; x <= cloth_width; x++)
        {
            auto* point = new class point(start_x + x * cloth_spacing, start_y + y * cloth_spacing);

            if(x!=0)
            {
                auto* left_point = points[this->points.size()-1];
                auto* s = new stick(point,left_point,cloth_spacing);
                point->add_stick(s,0);
                left_point->add_stick(s,0);
                sticks.push_back(s);
            }

            if(y!=0)
            {
                auto* up_point = points[x + (y - 1) * (cloth_width + 1)];
                auto* s = new stick(point,up_point,cloth_spacing);
                point->add_stick(s,1);
                up_point->add_stick(s,1);
                sticks.push_back(s);
            }

            if(x % 2 == 0 && y ==0)
                point->pin();

            points.push_back(point);




        }


    }



}


void cloth::render(SDL_Renderer* renderer)
{
    for(auto stick : sticks)
    {
        if(stick->active()) {
            if (stick->highlighted())
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            else
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

            SDL_RenderDrawLine(renderer, stick->get_p0()->get_x(), stick->get_p0()->get_y(),
                               stick->get_p1()->get_x(), stick->get_p1()->get_y());
        }
    }

}

void cloth::update(double delta_time) {



    for(auto point: points)
    {
            std::pair<double,double> acc = std::make_pair(wind.first + gravity.first,
                                                          gravity.second + wind.second);
            point->update(delta_time, drag, acc);
            point->keep_in_bounds();
    }

    for(auto stick : sticks)
    {
        if(stick->active())
            stick->update();
    }





}
