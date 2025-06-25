#pragma once
#include "AnimationWindow.h"
#include "widgets/DropdownList.h"
#include "widgets/Button.h"
#include "widgets/TextInput.h"
#include "WorkoutData.h"


class WorkoutWindow : public TDT4102::AnimationWindow {
    private:
        std::vector<std::string> dropdownOptions {"Strength Training", "Running", "Team Sport", "Hiking", "Walking", "Cycling", "Yoga", "Dance", "Pilates", "Crossfit", "Climbing", "Rowing", "Martial Arts", "Other"};
        TDT4102::DropdownList workoutOptions;
        TDT4102::Button easyButton;
        TDT4102::Button moderateButton;
        TDT4102::Button maxEffortButton;
        TDT4102::TextInput durationText;
        TDT4102::TextInput notes;
        TDT4102::Button saveButton;
        TDT4102::TextInput distanceText;
        std::string difficultySelected;
        TDT4102::Button randomButton;
        std::string randomWorkoutText; 
        TDT4102::TextInput workoutDisplay;

    public:
        WorkoutWindow(TDT4102::Point position, int width, int height, const std::string& title);
        bool isRandomTrue = false;
        void onDropdownSelection();
        void onEasyButtonClick();
        void onModerateButtonClick();
        void onMaxEffortButtonClick();
        void onDurationInput();
        void onNotesInput();
        void onRandomButton();
        void saveData();
        void BarGraph(DataProcessing& data);
        void drawLastFourWorkouts(DataProcessing& data);
};
