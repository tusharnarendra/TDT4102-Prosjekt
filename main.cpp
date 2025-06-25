#include "std_lib_facilities.h"
#include "GUI.h"

int main() {
    TDT4102::Point windowPlacement {350,150};
    WorkoutWindow workoutWindow(windowPlacement, 1200, 800, "Workout Log");
    workoutWindow.wait_for_close();
    return 0;
}

