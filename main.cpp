#include <iostream>
#include <environment.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {


    auto* environment = new class environment();
    environment->env_init((char*)"CLOTH",SCREEN_WIDTH,SCREEN_HEIGHT);
    environment->run();
    environment->close();

    return 0;
}
