//
// Created by Avery Drennan on 4/27/23.
//

#include "stick.h"
#include <cmath>
#pragma once

stick::stick(point *p0, point *p1, double length)
{
    is_highlighted = false;
    is_active = true;
    this->p0 = p0;
    this->p1 = p1;
    this->length = length;
}

point* stick::get_p0() {
    return p0;
}

point* stick::get_p1() {
    return p1;
}

void stick::update()
{
    std::pair<double,double>p0_pos = std::make_pair(p0->get_x(),p0->get_y());
    std::pair<double,double>p1_pos = std::make_pair(p1->get_x(),p1->get_y());

    std::pair<double,double> diff = std::make_pair(p0_pos.first - p1_pos.first,p0_pos.second - p1_pos.second);
    double distance = sqrt(diff.first * diff.first + diff.second * diff.second);
    double diff_factor = (length-distance)/distance;
    std::pair<double,double> offset = std::make_pair(diff.first * diff_factor * 0.5f,
                                                     diff.second * diff_factor * 0.5f);
    p0->set_x(p0_pos.first + offset.first);
    p0->set_y(p0_pos.second + offset.second);

    p1->set_x(p1_pos.first - offset.first);
    p1->set_y(p1_pos.second - offset.second);



}

void stick::highlight() {
    this->is_highlighted = true;

}

bool stick::highlighted() {
    return this->is_highlighted;
}

void stick::remove_highlight() {
is_highlighted = false;
}

void stick::Break() {
    is_active = false;

}

bool stick::active() {
    return is_active;
}


