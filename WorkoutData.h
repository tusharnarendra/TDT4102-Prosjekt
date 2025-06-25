#pragma once
#include <string>
#include <filesystem>
#include <map>
#include <vector>

struct WorkoutEntry {
    std::string workoutType;
    std::string difficultyLevel;
    double duration;
    double distance;
    std::string notes;
    std::string date;
};


class DataProcessing {
    private:
        const std::filesystem::path filePath;

    public:
        DataProcessing(const std::filesystem::path& path);
        std::map<int, int> workoutsPerWeek;
        double longestDuration = 0.0;
        double longestDistance = 0.0;
        double fastestPace = 1000;
        void saveUserInput(const std::string& data);
        int totalWorkouts;
        std::vector<WorkoutEntry> workouts;
        std::vector<WorkoutEntry> readUserInput();
        double roundToTwoDecimals(double value);
        void pbSystem();
};


