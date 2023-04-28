//
// Created by Avery Drennan on 4/27/23.
//

#ifndef CLOTH_SIM_STICK_H
#define CLOTH_SIM_STICK_H

#include <point.h>
#include <cstdint>

class point;
class stick {
private:
    bool is_highlighted;
    bool is_active;
    point* p0;
    point* p1;
    double length;

public:
    stick(point* p0,point* p1,double length);
    void highlight();
    bool highlighted();
    void remove_highlight();
    void Break();
    bool active();

    void update();
    point* get_p0();
    point* get_p1();



};


#endif //CLOTH_SIM_STICK_H
