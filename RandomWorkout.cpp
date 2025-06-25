#include "RandomWorkout.h"

std::string randomWorkout() {
    std::vector<std::string> workoutChoices {"Strength", "Running", "Team Sport", "Hiking", "Walking", "Cycling", "Yoga", "Dance", "Pilates", "Crossfit", "Climbing", "Rowing", "Martial Arts", "Other"};
    std::random_device device;
    unsigned long randomSeed = device();

    std::default_random_engine engine(randomSeed);
    std::uniform_int_distribution integerDistribution(0, 12);

    std::string randomWorkout;

    randomWorkout = workoutChoices.at(integerDistribution(engine));

    return randomWorkout;
}   