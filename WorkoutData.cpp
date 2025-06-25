#include "WorkoutData.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 
DataProcessing::DataProcessing(const std::filesystem::path& path) : filePath(path) {}

void DataProcessing::saveUserInput(const std::string& data) {
    std::ofstream outputStream{filePath, std::ios::app};
    if (!outputStream) {
        std::cout << "Could not open file: " << filePath << std::endl;
        return;
    } else {
        outputStream << data << std::endl;
        outputStream.close();
        std::cout << "Data saved" << std::endl;
    }
}

double DataProcessing::roundToTwoDecimals(double value) {
    return round(value * 100.0) / 100.0;
}

std::vector<WorkoutEntry> DataProcessing::readUserInput() {
    std::ifstream inputStream{filePath};
    std::string line;
    workouts.clear();
    totalWorkouts = 0;
    workoutsPerWeek.clear();

    if (!inputStream) {
        std::cout << "Could not open file: " << filePath << std::endl;
        return workouts;
    } else {
        while (std::getline(inputStream, line)) {

            // Hold telling på hvor mange treningsøkter for stolpediagrammet
            totalWorkouts++;

            WorkoutEntry workout; 

            //Finne kommaene i txt-filen, brukte litt ChatGPT for å finne ut hvordan man håndterer data med komma

            size_t firstComma = line.find(',');
            size_t secondComma = line.find(',', firstComma + 1);
            size_t thirdComma = line.find(',', secondComma + 1);
            size_t fourthComma = line.find(',', thirdComma + 1);
            size_t fifthComma = line.find(',', fourthComma + 1);

            // Trekk ut dataene, med feilhåndtering for å sjekke om data ble lagt inn og om av riktig type
            std::string workoutTypeString = line.substr(0, firstComma);
            if (workoutTypeString.empty()) {
                workout.workoutType = "Unknown";
            } else {
                workout.workoutType = workoutTypeString;
            }

            std::string difficultyLevelString = line.substr(firstComma + 1, secondComma - firstComma - 1);
            if (difficultyLevelString.empty()) {
                workout.difficultyLevel = "Unknown"; 
            } else {
                workout.difficultyLevel = difficultyLevelString;
            }

            std::string durationString = line.substr(secondComma + 1, thirdComma - secondComma - 1);
            try {
                if (durationString.empty()) {
                    workout.duration = 0;  
                } else {
                    workout.duration = roundToTwoDecimals(std::stof(durationString));  
                }
            } catch (const std::invalid_argument& e) {
                std::cout << "Invalid argument for duration: " << durationString << std::endl;
                workout.duration = 0;  
            } catch (const std::out_of_range& e) {
                std::cout << "Duration out of range: " << durationString << std::endl;
                workout.duration = 0;
            }

            std::string distanceString = line.substr(thirdComma + 1, fourthComma - thirdComma - 1);
            try {
                if (distanceString.empty()) {
                    workout.distance = 0.0;  
                } else {
                    workout.distance = roundToTwoDecimals(std::stof(distanceString));
                }
            } catch (const std::invalid_argument& e) {
                std::cout << "Invalid argument for distance: " << distanceString << std::endl;
                workout.distance = 0.0;  
            } catch (const std::out_of_range& e) {
                std::cout << "Distance out of range: " << distanceString << std::endl;
                workout.distance = 0.0; 
            }

            std::string dateString = line.substr(fourthComma + 1, fifthComma - fourthComma - 1);
            workout.date = dateString;

            std::string notesString = line.substr(fifthComma + 1);
        
            if (notesString.empty()) {
                workout.notes = "None";  
            } else {
                workout.notes = notesString;
            }

            //brukte w3-skoler og chatgpt for å hjelpe med denne delen, 
            //men hvordan det fungerer er at vi bruker en std::tm-struktur 
            //for å bryte ned klokkeslett/dato-informasjonen og deretter bruke inndatastrengstrømmen 
            //slik at vi kan behandle den som en input og få nødvendig informasjon

            std::tm tm = {};
            std::istringstream ss(dateString);
            ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
            std::mktime(&tm);

            // Generert av ChatGPT, en metode for å finne ISO uke nummer
            char week_str[6];
            strftime(week_str, sizeof(week_str), "%V", &tm);
            int week = std::stoi(week_str);

            workoutsPerWeek[week]++;
            workouts.push_back(workout);
        }

        inputStream.close();
    }
    return workouts;
}


void DataProcessing::pbSystem() {

    // Iterer gjennom treningsvektoren og sjekk for personlige rekorder
    for (const WorkoutEntry& workout : workouts) {
        if (workout.duration > longestDuration) {
            longestDuration = roundToTwoDecimals(workout.duration);
        }
        if (workout.distance > longestDistance) {
            longestDistance = roundToTwoDecimals(workout.distance);
        }

        if (workout.distance > 0.01) {
            try {
                double pace = roundToTwoDecimals(workout.duration / workout.distance);
                if (pace < fastestPace) {
                    fastestPace = pace;
                }
            } catch (const std::exception& e) {
                std::cout << "Unexpected error while calculating pace: " << e.what() << std::endl;
            }
        } else {
            std::cout << "Divide by zero warning" << std::endl;
        }
    }
}

