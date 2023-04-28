//
// Created by Avery Drennan on 4/27/23.
//

#ifndef CLOTH_SIM_EVENT_DATA_H
#define CLOTH_SIM_EVENT_DATA_H
#include <utility>

struct event_data{

    bool close;
    std::pair<double,double> mouse_pos;
    bool left_click;
    bool right_click;
    event_data();
    void set_mouse_pos(double x, double y);

};


#endif //CLOTH_SIM_EVENT_DATA_H
