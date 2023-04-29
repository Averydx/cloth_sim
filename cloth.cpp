//
// Created by Avery Drennan on 4/27/23.
//

#include "cloth.h"

cloth::cloth(int cloth_width, int cloth_height, int cloth_spacing,int start_x,int start_y) {
    this->gravity = std::make_pair<double,double>(0.f,100.f);
    this->wind = std::make_pair<double,double>(25.f,0.f);
    this->drag = 0.01f;
    this->elasticity = 10.0f;
    this->cloth_width = cloth_width;
    this->cloth_height = cloth_height;
    this->start_x = start_x;
    this->start_y = start_y;
    this->cloth_spacing = cloth_spacing;

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


    instantiate_neighbors();


}


void cloth::render(SDL_Renderer* renderer,bool wire_frame)
{

    texture_renderer(renderer);

    for(auto stick : sticks)
    {
        if(stick->active() && wire_frame) {
            if (stick->highlighted())
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_TRANSPARENT);
            else
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_TRANSPARENT);

            SDL_RenderDrawLine(renderer, stick->get_p0()->get_x(), stick->get_p0()->get_y(),
                               stick->get_p1()->get_x(), stick->get_p1()->get_y());
        }

//        else if(!stick->active() && wire_frame)
//        {
//            SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_TRANSPARENT);
//            SDL_RenderDrawLine(renderer, stick->get_p0()->get_x(), stick->get_p0()->get_y(),
//                               stick->get_p1()->get_x(), stick->get_p1()->get_y());
//
//        }
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
        if(!stick->get_p0()->sticks.first->active() || !stick->get_p0()->sticks.second->active()
        ||!stick->get_p1()->sticks.first->active() || !stick->get_p1()->sticks.second->active())
        {
            stick->is_loose = true;
        }

        if(stick->active())
            stick->update();
    }





}

void cloth::instantiate_neighbors()
{

    for(int i = 0; i < points.size();i++)
    {
        if(points[i]->get_x() == (start_x + cloth_width * cloth_spacing) ||
        points[i]->get_y() == (start_y + cloth_height * cloth_spacing))
        {
            //do nothing
        }

        else
        {
            points[i]->neighbors.push_back(points[i+1]);
            points[i]->neighbors.push_back(points[i+cloth_width + 1]);
            points[i]->neighbors.push_back(points[i+cloth_width + 2]);
        }
    }
}

void cloth::texture_renderer(SDL_Renderer* renderer)
{
    for(auto point: points)
    {
        if((point->sticks.first->active() && !point->sticks.first->is_loose) &&
        (point->sticks.second->active()&&!point->sticks.second->is_loose))
        {
            if (!point->neighbors.empty()) {
                const std::vector<SDL_Vertex> vertices_1 =
                        {
                                {SDL_FPoint{static_cast<float>(point->get_x()), static_cast<float>(point->get_y())},
                                                                                                  SDL_Color{255, 248, 220,
                                                                                                            SDL_ALPHA_TRANSPARENT}, SDL_FPoint{
                                        0},},
                                {SDL_FPoint{static_cast<float>(point->neighbors.at(0)->get_x()),
                                            static_cast<float>(point->neighbors.at(0)->get_y())}, SDL_Color{255, 248, 220,
                                                                                                            SDL_ALPHA_TRANSPARENT}, SDL_FPoint{
                                        0},},
                                {SDL_FPoint{static_cast<float>(point->neighbors.at(1)->get_x()),
                                            static_cast<float>(point->neighbors.at(1)->get_y())}, SDL_Color{255, 248, 220,
                                                                                                            SDL_ALPHA_TRANSPARENT}, SDL_FPoint{
                                        0},}
                        };

                if(point->sticks.first->active() && point->sticks.second->active()) {
                    SDL_RenderGeometry(renderer, nullptr, vertices_1.data(), vertices_1.size(), nullptr, 0);

                }
                const std::vector<SDL_Vertex> vertices_2 =
                        {
                                {SDL_FPoint{static_cast<float>(point->neighbors.at(2)->get_x()),
                                            static_cast<float>(point->neighbors.at(2)->get_y())},
                                                                                                  SDL_Color{255, 248, 220,
                                                                                                            SDL_ALPHA_TRANSPARENT}, SDL_FPoint{
                                        0},},
                                {SDL_FPoint{static_cast<float>(point->neighbors.at(0)->get_x()),
                                            static_cast<float>(point->neighbors.at(0)->get_y())}, SDL_Color{255, 248, 220,
                                                                                                            SDL_ALPHA_TRANSPARENT}, SDL_FPoint{
                                        0},},
                                {SDL_FPoint{static_cast<float>(point->neighbors.at(1)->get_x()),
                                            static_cast<float>(point->neighbors.at(1)->get_y())}, SDL_Color{255, 248, 220,
                                                                                                            SDL_ALPHA_TRANSPARENT}, SDL_FPoint{
                                        0},}
                        };
            if(point->neighbors.at(2)->sticks.first->active() && point->neighbors.at(2)->sticks.second->active())
                SDL_RenderGeometry(renderer, nullptr, vertices_2.data(), vertices_2.size(), nullptr, 0);


            }
        }
    }
}
