//
// Created by Avery Drennan on 4/27/23.
//

#ifndef CLOTH_SIM_POINT_H
#define CLOTH_SIM_POINT_H
#include <utility>
#include "stick.h"


class stick;
class point {

private:

    std::pair<double,double> pos;
    std::pair<double,double> old_pos;
    std::pair<double,double> init_pos;

    bool is_pinned;

public:
    std::pair<stick*,stick*> sticks;
    point(double x, double y);
    [[nodiscard]] double get_x() const;
    [[nodiscard]] double get_y() const;
    void set_x(double x);
    void set_y(double y);
    void pin();
    void add_stick(stick* stick,int index);
    void update(double delta_time,double drag,std::pair<double,double> acceleration);
    [[nodiscard]] bool pinned() const;
    void keep_in_bounds();
};


#endif //CLOTH_SIM_POINT_H
