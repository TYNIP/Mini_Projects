#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Structures section
typedef struct {
    int numberOfLaps;
    int currentLap;
    char firstPlaceDriverName[50];
    char firstPlaceRaceCarColor[20];
} Race;

typedef struct {
    char driverName[50];
    char raceCarColor[20];
    int totalLapTime;
} RaceCar;

// Print functions section
void printIntro() {
    printf("Welcome to our main event digital race fans!\n");
    printf("I hope everybody has their snacks because we are about to begin!\n");
}

void printCountDown() {
    printf("Racers Ready! In...\n");
    for (int i = 5; i > 0; i--) {
        printf("%d\n", i);
    }
    printf("Race!\n");
}

void printFirstPlaceAfterLap(Race race) {
    printf("After lap number %d\n", race.currentLap);
    printf("First Place Is: %s in the %s race car!\n", race.firstPlaceDriverName, race.firstPlaceRaceCarColor);
}

void printCongratulation(Race race) {
    printf("Let's all congratulate %s in the %s race car for an amazing performance.\n", race.firstPlaceDriverName, race.firstPlaceRaceCarColor);
    printf("It truly was a great race and everybody have a goodnight!\n");
}

// Logic functions section
int calculateTimeToCompleteLap() {
    int speed = rand() % 3 + 1;
    int acceleration = rand() % 3 + 1;
    int nerves = rand() % 3 + 1;
    return speed + acceleration + nerves;
}

void updateRaceCar(RaceCar* raceCar) {
    int lapTime = calculateTimeToCompleteLap();
    raceCar->totalLapTime += lapTime;
}

void updateFirstPlace(Race* race, RaceCar* raceCar1, RaceCar* raceCar2) {
    if (raceCar1->totalLapTime <= raceCar2->totalLapTime) {
        strcpy(race->firstPlaceDriverName, raceCar1->driverName);
        strcpy(race->firstPlaceRaceCarColor, raceCar1->raceCarColor);
    } else {
        strcpy(race->firstPlaceDriverName, raceCar2->driverName);
        strcpy(race->firstPlaceRaceCarColor, raceCar2->raceCarColor);
    }
}

// Race logic
void startRace(RaceCar* raceCar1, RaceCar* raceCar2) {
    Race race = {5, 1, "", ""};  // Initialize the race

    for (int lap = 1; lap <= race.numberOfLaps; lap++) {
        race.currentLap = lap;

        updateRaceCar(raceCar1);
        updateRaceCar(raceCar2);

        updateFirstPlace(&race, raceCar1, raceCar2);

        printFirstPlaceAfterLap(race);
    }

    printCongratulation(race);
}

// Main function
int main() {
    srand(time(0));  // Seed for random number generator

    // Initialize RaceCars
    RaceCar raceCar1 = {"Cosmo", "orange", 0};
    RaceCar raceCar2 = {"George", "yellow", 0};

    // Print race intro and countdown
    printIntro();
    printCountDown();

    // Start the race
    startRace(&raceCar1, &raceCar2);

    return 0;
}
