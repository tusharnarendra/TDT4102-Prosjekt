#include "GUI.h"
#include <string>
#include <ctime>
#include <iostream>
#include "WorkoutData.h"
#include "RandomWorkout.h"
#include <vector>
#include <sstream> 

std::string formatToTwoDecimals(double value) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    return stream.str();
}


WorkoutWindow::WorkoutWindow(TDT4102::Point position, int width, int height, const std::string& title)
    : AnimationWindow(position.x, position.y, width, height, title),
    workoutOptions{{75, 190}, 400, 40, dropdownOptions},
    easyButton{TDT4102::Point{75, 270}, 125, 50, "Easy"},
    moderateButton{TDT4102::Point{210, 270}, 125, 50, "Moderate"},
    maxEffortButton{TDT4102::Point{345, 270}, 125, 50, "Max Effort"}, 
    durationText{TDT4102::Point{75, 350}, 150, 50},
    distanceText{TDT4102::Point{275, 350}, 150, 50},
    notes{TDT4102::Point{75, 430}, 400, 175},
    saveButton{TDT4102::Point{75, 620}, 125, 50, "Save"},
    randomButton{TDT4102::Point{75,685}, 250, 75, "Click for a random workout!"},
    workoutDisplay{{335,700}, 130, 50, ""} {
    
    // Sette opp den grunnleggende utformingen av vinduet, inkludert tittelen/knapper

    //Bakgrunnsfarge
    TDT4102::Color backgroundFillColor = TDT4102::Color(225, 225, 227);
    draw_rectangle(TDT4102::Point{0,0}, 1200, 800, backgroundFillColor);


    // Bakgrunnsfarge bak tittelen
    TDT4102::Point rectangleCorner {10, 10};
    TDT4102::Color rectangleFillColor = TDT4102::Color(46,68,96);
    TDT4102::Color rectangleEdgeColor = TDT4102::Color::light_steel_blue;
    draw_rectangle(rectangleCorner, 1180, 100, rectangleFillColor, rectangleEdgeColor);

    // Tittelen
    TDT4102::Color titleColor = TDT4102::Color::white;
    int titleFontSize = 80;  
    TDT4102::Font titleFontFace = TDT4102::Font::courier_bold;
    draw_text(TDT4102::Point{355, 15}, "Workout Log", titleColor, titleFontSize, titleFontFace);

    // Dato
    time_t timestamp = time(nullptr);
    std::string date = ctime(&timestamp);
    date.erase(date.find('\n'));
    TDT4102::Color dateColor = TDT4102::Color(200,200,200);
    int dateFontSize = 20; 
    TDT4102::Font dateFontFace = TDT4102::Font::courier_bold;
    TDT4102::Point dateLocation{900, 55}; 
    draw_text(dateLocation, date, dateColor, dateFontSize, dateFontFace);

    //Dropdown list tekst
    TDT4102::Color subheadingColor= TDT4102::Color(51, 51, 51);
    int subheadingFontSize = 30;  
    TDT4102::Font subheadingFontFace = TDT4102::Font::courier_bold;
    draw_text(TDT4102::Point{75, 155}, "Workout Type:", subheadingColor, subheadingFontSize, subheadingFontFace);

    //Difficulty tekst
    draw_text(TDT4102::Point{75, 230}, "Exertion Level:", subheadingColor, subheadingFontSize, subheadingFontFace);

    //Duration/Distance tekst
    draw_text(TDT4102::Point{75, 310}, "Duration:", subheadingColor, subheadingFontSize, subheadingFontFace);
    int minsFontSize = 25;
    draw_text(TDT4102::Point{210, 360}, "mins", subheadingColor, minsFontSize, subheadingFontFace);
    draw_text(TDT4102::Point{275, 310}, "Distance:", subheadingColor, subheadingFontSize, subheadingFontFace);
    draw_text(TDT4102::Point{315, 355}, "N/A", TDT4102::Color(255,0,0),subheadingFontSize, subheadingFontFace);
    draw_text(TDT4102::Point{415, 360}, "km", subheadingColor, minsFontSize, subheadingFontFace);

    //Notes tekst
    draw_text(TDT4102::Point{75, 390}, "Notes: ", subheadingColor, subheadingFontSize, subheadingFontFace);

    //Widgets

    //Dropdown
    workoutOptions.setCallback(std::bind(&WorkoutWindow::onDropdownSelection, this));
    add(workoutOptions);

    //Knapper
    easyButton.setButtonColor(TDT4102::Color(107, 203, 119));
    moderateButton.setButtonColor(TDT4102::Color(244, 162, 97));
    maxEffortButton.setButtonColor(TDT4102::Color(230, 57, 70));

    easyButton.setLabelColor(TDT4102::Color::white);
    moderateButton.setLabelColor(TDT4102::Color::white);
    maxEffortButton.setLabelColor(TDT4102::Color::white);

    easyButton.setButtonColorHover(TDT4102::Color(85, 170, 100));
    moderateButton.setButtonColorHover(TDT4102::Color(220, 140, 80));
    maxEffortButton.setButtonColorHover(TDT4102::Color(200, 40, 55));

    easyButton.setButtonColorActive(TDT4102::Color(255, 0, 0));
    moderateButton.setButtonColorActive(TDT4102::Color(255,0,0));
    maxEffortButton.setButtonColorActive(TDT4102::Color(255,0,0));

    easyButton.setCallback(std::bind(&WorkoutWindow::onEasyButtonClick, this));
    moderateButton.setCallback(std::bind(&WorkoutWindow::onModerateButtonClick, this));
    maxEffortButton.setCallback(std::bind(&WorkoutWindow::onMaxEffortButtonClick, this));
    
    add(easyButton);
    add(moderateButton);
    add(maxEffortButton);

    saveButton.setButtonColor(TDT4102::Color(15, 90, 164));
    saveButton.setLabelColor(TDT4102::Color::white);
    saveButton.setButtonColorHover(TDT4102::Color(12, 72, 132));
    saveButton.setButtonColorActive(TDT4102::Color(255,0,0));

    saveButton.setCallback(std::bind(&WorkoutWindow::saveData, this));
    add(saveButton);

    randomButton.setButtonColor(TDT4102::Color(69, 180, 255));
    randomButton.setLabelColor(TDT4102::Color::white);
    randomButton.setButtonColorHover(TDT4102::Color(12, 72, 132));
    randomButton.setButtonColorActive(TDT4102::Color(255,0,0));
    randomButton.setCallback(std::bind(&WorkoutWindow::onRandomButton, this));
    add(randomButton);

    
    //Tekst
    durationText.setCallback(std::bind(&WorkoutWindow::onDurationInput, this));
    add(durationText);

    notes.setCallback(std::bind(&WorkoutWindow::onNotesInput, this));
    add(notes);

    add(distanceText);
    distanceText.setVisible(false);

    add(workoutDisplay);

    std::filesystem::path file{"workoutdata.txt"};
    DataProcessing data(file);

    //Stolpediagrammet
    BarGraph(data);
    // Siste 4 treningsøkter
    drawLastFourWorkouts(data);

}


// Sjekk om brukeren har valgt en kondisjonstrening, slik at vi kan be om distansen
void WorkoutWindow::onDropdownSelection() {
    std::string selectedWorkout = workoutOptions.getSelectedValue();
    if (selectedWorkout == "Running" || selectedWorkout == "Cycling" || selectedWorkout == "Rowing" || selectedWorkout == "Hiking" || selectedWorkout == "Walking") {
        distanceText.setVisible(true);
    }
}

//Funksjon som lager et søylediagram som viser hvor mange treningsøkter per uke
void WorkoutWindow::BarGraph(DataProcessing& data) {
    data.readUserInput(); 
    std::vector<int> workouts_per_week;
    std::vector<int> weekNumbers;

    auto recentWeekElement = data.workoutsPerWeek.end(); 

    // Feilsøking
    for (const auto& pair : data.workoutsPerWeek) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    // Brukes for å sjekke at vi kun samler inn 5 uker med data
    int count = 0;

    if (recentWeekElement != data.workoutsPerWeek.begin()) {
        recentWeekElement = std::prev(recentWeekElement); // Flytt til forrige element i std::map
    }

    while (recentWeekElement != data.workoutsPerWeek.begin() && count < 5) {
        workouts_per_week.push_back(recentWeekElement->second);
        weekNumbers.push_back(recentWeekElement->first);
        recentWeekElement = std::prev(recentWeekElement);
        ++count;
    };

    // Hvis vi ikke har data for 5 uker
    if (count < 5 && recentWeekElement == data.workoutsPerWeek.begin()) {
        workouts_per_week.push_back(recentWeekElement->second);
        weekNumbers.push_back(recentWeekElement->first);
        ++count;
    }

    //Snu vektorene slik at vi har den siste uken som siste element
    std::reverse(workouts_per_week.begin(), workouts_per_week.end());
    std::reverse(weekNumbers.begin(), weekNumbers.end());

    const int bar_width = 50;    
    const int spacing = 20;      
    const int x_start = 650;   
    const int x_end = 1050;      
    const int y_start = 725;  
    const int y_end = 525;

    const int chart_width = x_end - x_start; 
    const int chart_height = y_start - y_end; 
    int x_position = x_start +15;

    //x-aksen
    draw_line({x_start, y_start}, {x_end, y_start}, TDT4102::Color::black);

    //y-aksen
    draw_line({x_start, y_start}, {x_start, y_end}, TDT4102::Color::black);
    draw_text(TDT4102::Point{560, 525}, "Relative", TDT4102::Color(51, 51, 51), 17, TDT4102::Font::courier_bold );
    draw_text(TDT4102::Point{560, 550}, "Workouts", TDT4102::Color(51, 51, 51), 17, TDT4102::Font::courier_bold);
    draw_text(TDT4102::Point{560, 575}, "Per Week", TDT4102::Color(51, 51, 51), 17, TDT4102::Font::courier_bold );


    if (workouts_per_week.empty()) {
        std::cout << "no workouts" << std::endl;
    } else {
        auto workoutCount = workouts_per_week.begin();
        auto weekNum = weekNumbers.begin();

        //Parallel Iterator
        while (workoutCount != workouts_per_week.end() && weekNum != weekNumbers.end()) {
            int currentWorkouts = *workoutCount;
            int currentWeek = *weekNum;
            int bar_height = currentWorkouts * chart_height / 10;

            // Tegn grafen
            draw_rectangle({x_position, y_start}, bar_width, -bar_height, TDT4102::Color::royal_blue); 

            // Uke nummer
            std::string weekLabel = "Week " + std::to_string(currentWeek);
            TDT4102::Point labelPosition = {x_position -5, y_start + 10};  
            draw_text(labelPosition, weekLabel, TDT4102::Color::black, 15, TDT4102::Font::courier_bold);

            x_position += bar_width + spacing;

            workoutCount++;
            weekNum++;
        }
    }

    // Feilsøking
    for (size_t i = 0; i < workouts_per_week.size(); ++i) {
        std::cout << "Week " << i + 1 << ": " << workouts_per_week[i] << " workouts\n";
    }

}

//Funksjon for å vise de siste 4 treningsøktene
void WorkoutWindow::drawLastFourWorkouts(DataProcessing& data) {
    data.readUserInput(); 
    // Lage vektorer for å lagre de siste 4 treningsøktene
    std::vector<std::string> lastFourWorkouts;
    std::vector<std::string> lastFourDifficulties;
    std::vector<double> lastFourDurations;
    std::vector<double> lastFourDistances;
    std::vector<std::string> lastFourNotes;
    std::vector<std::string> lastFourDates;
    std::cout << "Total workouts: " << data.totalWorkouts << std::endl;

    // Fyll vektorene med data fra workouts vektoren
    int total = static_cast<int>(data.workouts.size());
    int displayTotal = std::min(total,4);
    for (int i = total - 1; i >= std::max(0, total - displayTotal); --i) {
        lastFourWorkouts.push_back(data.workouts.at(i).workoutType);
        lastFourDifficulties.push_back(data.workouts.at(i).difficultyLevel);
        lastFourDurations.push_back(data.workouts.at(i).duration);
        lastFourDistances.push_back(data.workouts.at(i).distance);
        lastFourNotes.push_back(data.workouts.at(i).notes);
        lastFourDates.push_back(data.workouts.at(i).date);
    }

    // Snu vektorene
    std::reverse(lastFourWorkouts.begin(), lastFourWorkouts.end());
    std::reverse(lastFourDifficulties.begin(), lastFourDifficulties.end());
    std::reverse(lastFourDurations.begin(), lastFourDurations.end());
    std::reverse(lastFourDistances.begin(), lastFourDistances.end());
    std::reverse(lastFourNotes.begin(), lastFourNotes.end());
    std::reverse(lastFourDates.begin(), lastFourDates.end());

    // Sjekk om brukeren har noen PBs i disse 4 treningsøktene
    data.pbSystem();
    std::vector<std::string> pbTexts;
    for (int i = 0; i < displayTotal; ++i) {
        std::string pbTextDuration = "";
        std::string pbTextDistance = "";
        std::string pbTextPace = "";

        if (lastFourDurations.at(i) == data.longestDuration) {
            pbTextDuration = "Duration PB!";
        }
        if (lastFourDistances.at(i) == data.longestDistance) {
            pbTextDistance = "Distance PB!";
        }
        if (data.roundToTwoDecimals(lastFourDurations.at(i) / lastFourDistances.at(i)) == data.fastestPace) {
            pbTextPace = "Pace PB!";
        }
        pbTexts.push_back(pbTextDuration + " " + pbTextDistance + " " + pbTextPace);
    }

    // Skriv ut tittelen
    draw_text(TDT4102::Point{700, 155}, "Past 4 Workouts", TDT4102::Color(51, 51, 51), 30, TDT4102::Font::courier_bold);

    TDT4102::Color smallTextColor = TDT4102::Color(0,0,0);
    int smallTextFontSize = 20;
    TDT4102::Font smallTextFontFace = TDT4102::Font::courier;


    // Tegn de 4 siste treningsøktene
    for (int i = 0; i < displayTotal; ++i) {
        int posY = 0;
        if(i<2){
            posY = 200;
        } else {
            posY = 350;
        }
        int posX = 0;
        if (i%2 == 0) {
            posX = 550;
        } else {
            posX = 850;
        }

        std::string workoutTypeText = "Workout: " + lastFourWorkouts.at(i);
        std::string difficultyText = "Difficulty: " + lastFourDifficulties.at(i);
        std::string durationText = "Duration: " + formatToTwoDecimals(lastFourDurations.at(i));
        std::string distanceText = "Distance: " + formatToTwoDecimals(lastFourDistances.at(i));
        std::string pbText = "PBs?: " + pbTexts.at(i);
        std::string dateText = lastFourDates.at(i);

        draw_text(TDT4102::Point{posX, posY}, workoutTypeText, smallTextColor, smallTextFontSize, smallTextFontFace);
        draw_text(TDT4102::Point{posX, posY + 20}, difficultyText, smallTextColor, smallTextFontSize, smallTextFontFace);
        draw_text(TDT4102::Point{posX, posY + 40}, durationText, smallTextColor, smallTextFontSize, smallTextFontFace);
        draw_text(TDT4102::Point{posX, posY + 60}, distanceText, smallTextColor, smallTextFontSize, smallTextFontFace);
        draw_text(TDT4102::Point{posX, posY + 80}, pbText, smallTextColor, 17, smallTextFontFace);
        draw_text(TDT4102::Point{posX - 10, posY + 100}, dateText, smallTextColor, smallTextFontSize, smallTextFontFace);
}

}
   

// Callback funksjoner, bare for å sjekke at alt fungerer greit

void WorkoutWindow::onEasyButtonClick() {
    std::cout << "Easy workout selected!" << std::endl;
    difficultySelected = "easy";
}

void WorkoutWindow::onModerateButtonClick() {
    std::cout << "Moderate workout selected!" << std::endl;
    difficultySelected = "moderate";
}

void WorkoutWindow::onMaxEffortButtonClick() {
    std::cout << "Max effort workout selected!" << std::endl;
    difficultySelected = "max";
}

void WorkoutWindow::onDurationInput() {
    std::cout << "The text field now contains: " << durationText.getText() << std::endl;
}

void WorkoutWindow::onNotesInput() {
    std::cout << "The text field now contains: " << notes.getText() << std::endl;
}

void WorkoutWindow::onRandomButton() {
    std::string result = randomWorkout();
    workoutDisplay.setText(result);  
}

void WorkoutWindow::saveData() {
    //Funksjon som tar brukerens input og skriver til en txt-fil
    std::string workoutType = workoutOptions.getSelectedValue();
    std::string difficultyLevel = difficultySelected;
    std::string duration = durationText.getText();
    std::string distance = distanceText.getText();  
    std::string notesData = notes.getText();

    //Sett numeriske verdier til 0 hvis vi får ingen input fra brukeren
    if (duration.empty()) {
        duration = "0";
    }
    if (distance.empty()) {
        distance = "0";
    }

    // Formater datoen
    time_t timestamp = time(nullptr);   
    std::string date = ctime(&timestamp);
    date.erase(date.find('\n'));

    std::string data = workoutType + ", " + difficultySelected + ", " + duration + ", " + distance + ", " + date + ", "+ notesData;

    // Skriv til filen
    std::filesystem::path path{"workoutdata.txt"};
    DataProcessing file(path);
    file.saveUserInput(data);
}
