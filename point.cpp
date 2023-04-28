//
// Created by Avery Drennan on 4/27/23.
//
#pragma once
#include "point.h"
#include <cmath>

point::point(double x, double y) {
    pos = std::make_pair(x,y);
    old_pos = pos;
    init_pos = pos;
    is_pinned = false;

}

double point::get_x() const {
    return pos.first;
}

double point::get_y() const {
    return pos.second;
}

void point::set_x(double x) {
    pos.first = x;
}

void point::set_y(double y) {
    pos.second = y;
}

void point::pin() {
    is_pinned = true;

}

void point::add_stick(stick *stick,int index)
{
    switch(index) {
        case 0:
            this->sticks.first = stick;
            break;

        case 1:
            this->sticks.second = stick;
            break;

        default:
            printf("stick indexing error on point :%p\n",this);
    }
}

void point::update(double delta_time,double drag,std::pair<double,double> acceleration)
{
    if(this->pinned()) {
        this->pos = init_pos;
        return;
    }
     double vel_x = pos.first - old_pos.first;
     double vel_y = pos.second - old_pos.second;
     double pos_x = pos.first + vel_x * (1.f - drag) + acceleration.first * (1.f - drag) * delta_time * delta_time;
     double pos_y = pos.second + vel_y * (1.f - drag) + acceleration.second * (1.f - drag) * delta_time * delta_time;

     old_pos = pos;

     pos.first = pos_x;
     pos.second = pos_y;
}

bool point::pinned() const {
    return is_pinned;
}

void point::keep_in_bounds()
{
    if(this->pos.second > 600)
        this->pos.second = 600;

    if(this->pos.second < 0)
        this->pos.second = 0;

    if(this->pos.first > 800)
        this->pos.first = 800;

    if(this->pos.first < 0)
        this->pos.first = 0;
}
