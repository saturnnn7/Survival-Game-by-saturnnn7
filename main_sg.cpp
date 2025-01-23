#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> // for system
#include <windows.h>
#include <stdlib.h>
using namespace std;

// Survival Game by saturn
// version 1.0.0
// Files
string filename_amination = "data/animations.txt";
string filename_stats = "data/stats.txt";

// Global variables
bool first_open = true;
bool first_time_play = true;
int start_menu = 0;
int day_count = 1;
int time_count = 0;
string time_print = "    ";

int health_count = 100;
int food_count = 5;
int energy_count = 100;
int wood_count = 0;
int stone_count = 0;

int game_choice = 0;
int build_shop_choice = 0;

int logging_camp = 0;
int logging_camp_choice = 0;
int shack = 0;
int shack_choice = 0;
int quarry = 0;
int quarry_choice = 0;
int workshop = 0;
int workshop_choice = 0;

int buildings_choice = 0;
int workshop_buy_choice = 0;

int upgrade_axe = 0;
int upgrade_axe_choice = 0;
int chainsaw = 0;
int chainsaw_choice = 0;
int upgrade_quarry = 0;
int upgrade_quarry_choice = 0;

// Leaderboard
const int leaderboard_rows = 5;
const int leaderboard_cols = 3;
string leaderboard[leaderboard_rows][leaderboard_cols] = {  {"1", "Mirrox",               "29 days" },
                                                            {"2", "Lemon4ik",             "31 days" },
                                                            {"3", "xXx_Ultra_Player_xXx", "32 days" },
                                                            {"4", "D_O_M_I_N_A_T_O_R",    "37 days" },
                                                            {"5", "Cherry",               "41 days" } };

HANDLE hOut; // Color
// Function prototypes
void Save_Game(const string& filename_stats);
void Load_Game(const string& filename_stats, bool& first_time_play, int& day_count, int& time_count, string& time_print, int& health_count, int& food_count, int& energy_count, int& wood_count, int& stone_count, int& logging_camp, int& shack, int& quarry, int& workshop, int& upgrade_axe, int& chainsaw, int& upgrade_quarry);
void Delay_Print(string message);
void Leaderboard();
void Game();
void Animation(ifstream& file, int startLine, int endLine);
void Start_Anim();
void Sleep_night();
void hud();
void Mine_Wood();
void Hunting();
void build_shop();
void buildings();
void workshop_func();
void Game_Over();

int main()
{
    hOut = GetStdHandle( STD_OUTPUT_HANDLE ); // Colors

    do // Start Menu
    {
        system("cls");

        SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        if (first_open) { Delay_Print("Welcome to Survival Game!\n\n"); } else { cout << "Welcome to Survival Game!\n\n"; }
        SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
        if (first_open) { Delay_Print("Chose one option.\n1. "); } else { cout << "Chose one option.\n1. "; }
        SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        if (first_open) { Delay_Print("Start New Game\n"); } else { cout << "Start New Game\n"; }
        SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
        if (first_open) { Delay_Print("2. "); } else { cout << "2. "; }
        SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        if (first_open) { Delay_Print("Load Game\n"); } else { cout << "Load Game\n"; }
        SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
        if (first_open) { Delay_Print("3. "); } else { cout << "3. "; }
        SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        if (first_open) { Delay_Print("Save Game\n"); } else { cout << "Save Game\n"; }
        SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
        if (first_open) { Delay_Print("4. "); } else { cout << "4. "; }
        SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        if (first_open) { Delay_Print("Leaderboard\n"); } else { cout << "Leaderboard\n"; }
        SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
        if (first_open) { Delay_Print("5. "); } else { cout << "5. "; }
        SetConsoleTextAttribute( hOut, FOREGROUND_RED);
        if (first_open) { Delay_Print("Exit\n"); } else { cout << "Exit\n"; }
        SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
        first_open = false;

        cout << "Enter your choice: ";
        cin >> start_menu;
        switch (start_menu)
        {
            case 1:
                first_time_play = true;
                day_count = 1;
                time_count = 0;
                time_print = "    ";

                health_count = 100;
                food_count = 5;
                energy_count = 100;
                wood_count = 0;
                stone_count = 0;

                logging_camp = 0;
                shack = 0;
                quarry = 0;
                workshop = 0;
                upgrade_axe = 0;
                chainsaw = 0;
                upgrade_quarry = 0;

                Start_Anim();
                Game();
                break;
            case 2:
                Load_Game(filename_stats, first_time_play, day_count, time_count, time_print, health_count, food_count, energy_count, wood_count, stone_count, logging_camp, shack, quarry, workshop, upgrade_axe, chainsaw, upgrade_quarry);
                system("cls");
                Start_Anim();
                Game();
                break;
            case 3:
                Save_Game(filename_stats);
                break;
            case 4:
                system("cls");
                cout << "Leaderboard:" << endl;
                cout << "-------------------" << endl;
                for (int i = 0; i < leaderboard_rows; i++) {
                    cout << leaderboard[i][0] << ". ";
                    SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    cout << leaderboard[i][1];
                    SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                    cout << " -- ";
                    SetConsoleTextAttribute( hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    cout << leaderboard[i][2] << endl;
                    SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                }
                system("pause");
                break;
            case 5:
                break;
            default:
                cout << endl << "Invalid choice. Please select a valid option." << endl;
                system("pause");
                break;
        }
    } while (start_menu != 5);

    return 0;
}


// Function implementations
void Save_Game(const string& filename_stats)
{
    ofstream file_stats(filename_stats);
    if (!file_stats) {
        cout << "Error: failed to open the file for writing." << endl;
        return;
    }
    file_stats << "first_time_play=" << first_time_play << endl;
    file_stats << "day_count=" << day_count << endl;
    file_stats << "time_count=" << time_count << endl;
    file_stats << "time_print=" << time_print << endl;
    file_stats << "health_count=" << health_count << endl;
    file_stats << "food_count=" << food_count << endl;
    file_stats << "energy_count=" << energy_count << endl;
    file_stats << "wood_count=" << wood_count << endl;
    file_stats << "stone_count=" << stone_count << endl;
    file_stats << "logging_camp=" << logging_camp << endl;
    file_stats << "shack=" << shack << endl;
    file_stats << "quarry=" << quarry << endl;
    file_stats << "workshop=" << workshop << endl;
    file_stats << "upgrade_axe=" << upgrade_axe << endl;
    file_stats << "chainsaw=" << chainsaw << endl;
    file_stats << "upgrade_quarry=" << upgrade_quarry << endl;

    file_stats.close();
}

void Load_Game(const string& filename_stats, bool& first_time_play, int& day_count, int& time_count, string& time_print, int& health_count, int& food_count, int& energy_count, int& wood_count, int& stone_count, int& logging_camp, int& shack, int& quarry, int& workshop, int& upgrade_axe, int& chainsaw, int& upgrade_quarry)
{
    
    ifstream file_stats(filename_stats);
    if (!file_stats) {
        cout << "Error: failed to open the file for reading." << endl;
        return;
    }

    string line;
    while (getline(file_stats, line)) {
        size_t delimiterPos = line.find("=");
        if (delimiterPos != string::npos) {

            string key = line.substr(0, delimiterPos);
            string value = line.substr(delimiterPos + 1);

            if (key == "first_time_play")     { first_time_play = stoi(value); }
            else if (key == "day_count")      { day_count = stoi(value); }
            else if (key == "time_count")     { time_count = stoi(value); }
            else if (key == "time_print")     { time_print = value; }
            else if (key == "health_count")   { health_count = stoi(value); }
            else if (key == "food_count")     { food_count = stoi(value); }
            else if (key == "energy_count")   { energy_count = stoi(value); }
            else if (key == "wood_count")     { wood_count = stoi(value); }
            else if (key == "stone_count")    { stone_count = stoi(value); }
            else if (key == "logging_camp")   { logging_camp = stoi(value); }
            else if (key == "shack")          { shack = stoi(value); }
            else if (key == "quarry")         { quarry = stoi(value); }
            else if (key == "workshop")       { workshop = stoi(value); }
            else if (key == "upgrade_axe")    { upgrade_axe = stoi(value); }
            else if (key == "chainsaw")       { chainsaw = stoi(value); }
            else if (key == "upgrade_quarry") { upgrade_quarry = stoi(value); }
        }
    }

    file_stats.close();
}

void Delay_Print(string message)
{
    for (char c : message) {
        cout << c << flush;
        Sleep(50);
    }
}

void Leaderboard()
{

}

void Game()
{
    do {
        if (first_time_play) {
            first_time_play = false;
            system("cls");
            Delay_Print("Hello newbie,");
            Sleep(300);
            Delay_Print(" welcome to Survival Game.\n");
            Sleep(300);
            Delay_Print("Here you will have adventures and survival in a harsh environment.\n");
            Sleep(300);
            Delay_Print("Try to acquire everything in the shortest possible time.\n");
            Sleep(500);
            system("pause");
        }

        system("cls");
        hud();
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "Welcome to Home" << endl << endl;
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);

        cout << "1. Mine Wood (4H)" << endl;
        cout << "2. Hunting (4H)" << endl;
        cout << "3. Sleep (for the next day)" << endl;
        cout << "4. Build shop" << endl;
        cout << "5. Buildings" << endl;
        cout << "6. ";
        SetConsoleTextAttribute( hOut, FOREGROUND_RED);
        cout << "Exit" << endl;
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
        cout << "Enter your choice: ";
        cin >> game_choice;

        switch (game_choice) {
            case 1:
                system("cls");
                Mine_Wood();
                time_count += 4;
                break;
            case 2:
                system("cls");
                Hunting();
                time_count += 4;
                break;
            case 3:
                cout << "You slept for next day" << endl;
                Sleep_night();
                break;
            case 4:
                build_shop();
                break;
            case 5:
                buildings();
                break;
            case 6:
                cout << "Exiting the game. Goodbye!" << endl;
                break;
            default:
                cout << endl << "Invalid choice. Please select a valid option." << endl;
                system("pause");
                break;
        }

    } while (game_choice != 6);
}
void Game_Over() {
    system("cls");

    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "GAME OVER!" << endl;
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
    if (food_count == 0) {
        Delay_Print("You've run out of food.\n");
    }
    Delay_Print("Thank you for playing!\n");
    system("pause");

    exit(0);
}



void hud()
{   
    if (health_count <= 0) {
        Game_Over();
    }

    if (time_count == 0) {
        time_print = "    "; 
    } else if (time_count == 4) {
        time_print = "#   "; 
    } else if (time_count == 8) {
        time_print = "##  ";
    } else if (time_count == 12) {
        time_print = "### ";
    } else {
        
        Sleep_night();
    }
    
    system("cls");
    
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "Day: ";
    cout << day_count;
    cout << "   |";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << time_print;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "|    ";
    cout << "Health: ";
    SetConsoleTextAttribute( hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << health_count;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "    ";
    cout << "Food: ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << food_count;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "    ";
    cout << "Energy: ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << energy_count;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "    ";
    cout << "Wood: ";
    SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << wood_count;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "    ";
    cout << "Stone: ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << stone_count << endl << endl;


}

void Animation(ifstream& file, int startLine, int endLine)
{
    system("cls");
    string line;
    int currentLine = 0;

    while (currentLine < startLine - 1 && getline(file, line)) {
        ++currentLine;
    }

    while (currentLine < endLine && getline(file, line)) {
        ++currentLine;
        cout << line << endl;
    }
}

void Start_Anim()
{
    ifstream file(filename_amination);
    if (!file.is_open()) {
        cout << "Error: Unable to open file '" << filename_amination << "'." << endl;
    }

    Sleep(100);
    for (int j = 0; j < 3; j++) {
        for (int i = 911; i < 1232; i += 46) {
            Animation(file, i, i + 44);
            Beep(i+200, 100);
            file.clear();
            file.seekg(0);
        }
    }
    file.close();
}

void Sleep_night()
{
    ifstream file(filename_amination);
    if (!file.is_open()) {
        cout << "Error: Unable to open file '" << filename_amination << "'." << endl;
    }

    Sleep(100);
    for (int j = 0; j < 3; j++) {
        for (int i = 737; i < 910; i += 29) {
            Animation(file, i, i + 27);
            Beep(1737 - i ,100);
            file.clear();
            file.seekg(0);
        }
    }
    file.close();

    time_count = 0;
    time_print = "    ";
    day_count++;
    if (food_count <= 0) {
        health_count -= 34;
    }
    if (food_count > 0) {
        food_count--;
    }
    if (energy_count <= 0) {
        health_count -= 34;
    }
    if (logging_camp == 1) {
        wood_count += 2;
    } 
    if (shack == 1) {
        if (energy_count >= 80) {
            energy_count = 100;
        } else {
            energy_count += 20;
        }
    } 
    if (shack == 0) {
        if (energy_count >= 90) {
            energy_count = 100;
        } else {
            energy_count += 10;
        }
    } 
    if (quarry == 1) {
        stone_count += 1;
    }
    if (upgrade_quarry == 1) {
        stone_count += 1;
    }

    Sleep(500);
}

void Mine_Wood()
{
    // Loading animation.txt
    ifstream file(filename_amination);
    if (!file.is_open()) {
        cout << "Error: Unable to open file '" << filename_amination << "'." << endl;
    }
    // Axe or Chainsaw animation
    if (chainsaw == 0) {
        for (int j = 0; j < 3; j++) {
            for (int i = 2; i < 246; i += 35) {
                Beep(i + 300, 100);
                Animation(file, i, i + 33);
                file.clear();
                file.seekg(0);
            }
            Beep(1000, 100);
        }
    } else if (chainsaw == 1) { 
        for (int j = 0; j < 3; j++) {
            for (int i = 247; i < 491; i += 35) {
                Beep(i + 55, 100);
                Animation(file, i, i + 33);
                file.clear();
                file.seekg(0);
            }
            Beep(1000, 100);
        }
    }
    file.close();
    Sleep(300);

    if (energy_count > 0) {
    energy_count -= 5;
    }
    
    system("cls");
    if (chainsaw == 1) {
        wood_count += 3;
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
        Delay_Print("You have recieved ");
        SetConsoleTextAttribute( hOut, FOREGROUND_RED| FOREGROUND_INTENSITY );
        Delay_Print("3");
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED| FOREGROUND_INTENSITY);
        Delay_Print(" wood");
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
        Delay_Print(" with your ");
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED| FOREGROUND_INTENSITY);
        Delay_Print("Chainsaw.");
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    } else {
        if (upgrade_axe == 1) {
            wood_count += 2;
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
            Delay_Print("You have recieved ");
            SetConsoleTextAttribute( hOut, FOREGROUND_RED| FOREGROUND_INTENSITY );
            Delay_Print("2");
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED| FOREGROUND_INTENSITY);
            Delay_Print(" wood");
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
            Delay_Print(" with your ");
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN);
            Delay_Print("Upgraded Axe.");
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
        } else {
            wood_count += 1;
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
            Delay_Print("You have recieved ");
            SetConsoleTextAttribute( hOut, FOREGROUND_RED| FOREGROUND_INTENSITY );
            Delay_Print("1");
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED| FOREGROUND_INTENSITY);
            Delay_Print(" wood");
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
            Delay_Print(" with your ");
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN| FOREGROUND_INTENSITY );
            Delay_Print("Axe.");
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
        }
    }
    Sleep(4000);
}


void Hunting()
{
    // Loading animation.txt
    ifstream file(filename_amination);
    if (!file.is_open()) {
        cout << "Error: Unable to open file '" << filename_amination << "'." << endl;
    }
    for (int j = 0; j < 3; j++) {
        for (int i = 492; i < 736; i += 35) {
            Beep(1200, 50);
            Animation(file, i, i + 33);
            Beep(800, 50);
            file.clear();
            file.seekg(0);
        }
    }
    file.close();
    Sleep(300);

    energy_count -= 8;
    food_count += 1;

    system("cls");
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << "You have recieved ";
    SetConsoleTextAttribute( hOut, FOREGROUND_RED| FOREGROUND_INTENSITY );
    cout << "1";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << " food";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " with your Sword.";
    Sleep(4000);
}


void build_shop()
{
    system("cls");
    hud();

    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "Welcome to Build shop!" << endl << endl;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << "Chose what you want to build." << endl;

    cout << "1. ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED);
    cout << "Logging camp";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout <<"  | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    cout << "wood 30";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout <<" |          | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "energy 15";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " |" << endl;

    cout << "2. ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED);
    cout << "Shack";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << "         | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    cout << "wood 25";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout <<" |          | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "energy 10";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " |" << endl;

    cout << "3. ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED);
    cout << "Quarry";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << "        | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    cout << "wood 100";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout <<"|          | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "energy 25";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " |" << endl;

    cout << "4. ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED);
    cout << "Workshop";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << "      | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    cout << "wood 50";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " | stone 15 | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "energy 15";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " |" << endl;

    cout << "5. ";
    SetConsoleTextAttribute( hOut, FOREGROUND_RED);
    cout << "Back" << endl;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << "Enter your choice: ";
    cin >> build_shop_choice;

    do {
        switch (build_shop_choice)
        {
            case 1:
                if (logging_camp == 0) {
                    if (energy_count > 15) {
                        if (wood_count >= 30) {
                            if (time_count == 0) {
                                cout << "You want to build the Logging camp? ";
                                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN);
                                cout << "(1 for yes|0 for no)" << endl;
                                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                cout << "Enter your choice: ";
                                cin >> logging_camp_choice;
                                if (logging_camp_choice == 1) {
                                    logging_camp = 1;
                                    energy_count -= 15;
                                    time_count = 16;
                                    cout << endl << "Congratulations, you've built the ";
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                                    cout << "Logging camp!" << endl;
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                    Beep(900,100);
                                    Beep(1300,100);
                                    system("pause");
                                    build_shop();
                                } else { 
                                    build_shop();
                                }
                        } else {
                            cout << endl << "You don't have enough ";
                            SetConsoleTextAttribute( hOut, FOREGROUND_RED);
                            cout << "time";
                            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                            cout << ". Come here at the beginning of the day." << endl;
                            system("pause");
                            build_shop();
                        } 
                        } else {
                            cout << endl << "You don't have enough " << endl;
                            SetConsoleTextAttribute( hOut, FOREGROUND_RED);
                            cout << "resources";
                            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                            cout << ". Come back here later." << endl;
                            system("pause");
                            build_shop();
                        }
                    } else {
                        cout << endl << "You don't have enough " << endl;
                        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        cout << "energy";
                        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                        cout << ". Come back here after sleep." << endl;
                        system("pause");
                        build_shop();
                    }
                } else {
                    cout << endl << "You've already build the ";
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    cout << "Logging camp." << endl;
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                    system("pause");
                    build_shop();
                }
                break;
            case 2:
                if (shack == 0) {
                    if (energy_count > 10) {
                        if (wood_count >= 25) {
                            if (time_count == 0) {
                                cout << "You want to build the Shack? ";
                                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN);
                                cout << "(1 for yes|0 for no)" << endl;
                                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                cout << "Enter your choice: ";
                                cin >> shack_choice;
                                if (shack_choice == 1) {
                                    shack = 1;
                                    wood_count -= 25;
                                    energy_count -= 10;
                                    time_count = 16;
                                    cout << "Congratulations, you've built the ";
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                                    cout << "Shack!" << endl;
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                    Beep(900,100);
                                    Beep(1300,100);
                                    system("pause");
                                    build_shop();
                                } else {
                                    build_shop();
                                }
                        } else {
                            cout << "You don't have enough ";
                            SetConsoleTextAttribute( hOut, FOREGROUND_RED);
                            cout << "time";
                            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                            cout << ". Come here at the beginning of the day." << endl;
                            system("pause");
                            build_shop();
                        }
                        } else {
                            cout << "You don't have enough " << endl;
                            SetConsoleTextAttribute( hOut, FOREGROUND_RED);
                            cout << "resources";
                            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                            cout << ". Come back here later." << endl;
                            system("pause");
                            build_shop();
                        }
                    } else {
                        cout << endl << "You don't have enough " << endl;
                        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        cout << "energy";
                        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                        cout << ". Come back here after sleep." << endl;
                        system("pause");
                        build_shop();
                    }
                } else {
                    cout << "You've already build the ";
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    cout << "Shack." << endl;
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                    system("pause");
                    build_shop();
                }
                break;
            case 3:
                if (quarry == 0) {
                    if (energy_count > 25) {
                        if (wood_count >= 100) {
                            if (time_count == 0) {
                                cout << "You want to build the Quarry? ";
                                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN);
                                cout << "(1 for yes|0 for no)" << endl;
                                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                cout << "Enter your choice: ";
                                cin >> quarry_choice;
                                if (quarry_choice == 1) {
                                    quarry = 1;
                                    wood_count -= 100;
                                    energy_count -= 25;
                                    time_count = 16;
                                    cout << endl << "Congratulations, you've built the ";
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                                    cout << "Quarry!" << endl;
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                    Beep(900,100);
                                    Beep(1300,100);
                                    system("pause");
                                    build_shop();
                                } else {
                                    build_shop();
                                }
                            } else {
                                cout << endl << "You don't have enough ";
                                SetConsoleTextAttribute( hOut, FOREGROUND_RED);
                                cout << "time";
                                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                cout << ". Come here at the beginning of the day." << endl;
                                system("pause");
                                build_shop();
                            }
                        } else {
                            cout << endl << "You don't have enough " << endl;
                            SetConsoleTextAttribute( hOut, FOREGROUND_RED);
                            cout << "resources";
                            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                            cout << ". Come back here later." << endl;
                            system("pause");
                            build_shop();
                        }
                    } else {
                        cout << endl << "You don't have enough " << endl;
                        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        cout << "energy";
                        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                        cout << ". Come back here after sleep." << endl;
                        system("pause");
                        build_shop();
                    }
                } else {
                    cout << endl << "You've already build the ";
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    cout << "Quarry." << endl;
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                    system("pause");
                    build_shop();
                }
                break;
            case 4:
                if (workshop == 0) {
                    if (energy_count > 25) {
                        if (wood_count >= 50 && stone_count >= 15) {
                            if (time_count == 0) {
                                cout << "You want to build the Workshop? ";
                                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN);
                                cout << "(1 for yes|0 for no)" << endl;
                                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                cout << "Enter your choice: ";
                                cin >> workshop_choice;
                                if (workshop_choice == 1) {
                                    workshop = 1;
                                    wood_count -= 50;
                                    stone_count -= 15;
                                    energy_count -= 25;
                                    time_count = 16;
                                    cout << endl << "Congratulations, you've built the ";
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                                    cout << "Workshop!" << endl;
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                    Beep(900,100);
                                    Beep(1300,100);
                                    system("pause");
                                    build_shop();
                                } else {
                                    build_shop();
                                }
                            } else {
                                cout << endl << "You don't have enough ";
                                SetConsoleTextAttribute( hOut, FOREGROUND_RED);
                                cout << "time";
                                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                cout << ". Come here at the beginning of the day." << endl;
                                system("pause");
                                build_shop();
                            }
                        } else {
                            cout << endl << "You don't have enough " << endl;
                            SetConsoleTextAttribute( hOut, FOREGROUND_RED);
                            cout << "resources";
                            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                            cout << ". Come back here later." << endl;
                            system("pause");
                            build_shop();
                        }
                    } else {
                        cout << endl << "You don't have enough " << endl;
                        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        cout << "energy";
                        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                        cout << ". Come back here after sleep." << endl;
                        system("pause");
                        build_shop();
                    }
                } else {
                    cout << endl << "You've already build the ";
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    cout << "Workshop" << endl;
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                    system("pause");
                    build_shop();
                }
                break;
            case 5:
                return;
            default:
                cout << endl << "Invalid choice. Please select a valid option." << endl;
                system("pause");
                build_shop();
                break;
            }
    } while (build_shop_choice != 5);
}


void buildings() 
{
    system("cls");
    hud();

    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "Welcome to your Buildings!" << endl << endl;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);

    cout << "You've already built: " << endl;
    if (logging_camp == 1) {
        cout << " 1. ";
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN| FOREGROUND_INTENSITY );
        cout << "Logging camp" << endl;
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    } else {
        cout << " 1. Logging camp" << endl;
    }
    if (shack == 1) {
        cout << " 2. ";
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN| FOREGROUND_INTENSITY );
        cout << "Shack" << endl;
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    } else {
        cout << " 2. Shack" << endl;
    }
    if (quarry == 1) {
        cout << " 3. ";
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN| FOREGROUND_INTENSITY );
        cout << "Quarry" << endl;
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    } else {
        cout << " 3. Quarry" << endl;
    }
    if (workshop == 1) {
        cout << " 4. ";
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN| FOREGROUND_INTENSITY );
        cout << "Workshop" << endl;
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    } else {
        cout << " 4. Workshop" << endl;
    }

    cout << "5. ";
    SetConsoleTextAttribute( hOut, FOREGROUND_RED);
    cout << "Back" << endl;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << "Enter your choice: ";
    cin >> buildings_choice;
    do{
        switch (buildings_choice) 
        {
            case 1:
                if (logging_camp == 1) {
                    cout << endl << "Logging camp doubles daily ";
                    SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    cout << "wood";
                    SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                    cout << " production." << endl;
                    system("pause");
                    buildings();
                } else {
                    cout << endl << "Logging camp doubles daily ";
                    SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    cout << "wood";
                    SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                    cout << " production." << endl;
                    cout << "You don't have Logging camp yet." << endl;
                    system("pause");
                    buildings();
                }
                break;
            case 2:
                if (shack == 1) {
                    cout << endl << "Shack doubles ";
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    cout << "energy";
                    SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                    cout << " recovery through sleep." << endl;
                    system("pause");
                    buildings();
                } else {
                    cout << endl << "Shack doubles ";
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    cout << "energy";
                    SetConsoleTextAttribute( hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                    cout << " recovery through sleep." << endl;
                    cout << "You don't have Shack yet" << endl;
                    system("pause");
                    buildings();
                }
                break;
            case 3:
                if (quarry == 1) {
                    cout << endl << "Quarry allows you to mine 1 stone per day." << endl;
                    system("pause");
                    buildings();
                } else {
                    cout << endl << "Quarry allows you to mine 1 stone per day." << endl;
                    cout << "You don't have Quarry yet" << endl;
                    system("pause");
                    buildings();
                }
                break;
            case 4:
                if (workshop == 1) {
                    workshop_func();
                } else {
                    cout << endl << "You don't have Workshop yet. To build it, go to Build shop" << endl;
                    system("pause");
                    buildings();
                }
                break;
            case 5:
                return;
            default:
                cout << endl << "Invalid choice. Please select a valid option." << endl;
                system("pause");
                break;
        }
    } while (buildings_choice != 5);
}


void workshop_func()
{
    system("cls");
    hud();

    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "Welcome to Workshop!" << endl << endl;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);

    cout << "You can ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN| FOREGROUND_INTENSITY);
    cout << "buy/Upgrade";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " tools to improve your production." << endl;

    cout << "1. ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED);
    cout << "Upgrade your Axe";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << "      | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    cout << "wood 40";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " | stone 10 | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "energy 15";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " |" << endl;

    cout << "2. ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED);
    cout << "Buy Chainsaw";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << "          | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    cout << "wood 60";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " | stone 40 | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "energy 20";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " |" << endl;

    cout << "3. ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED);
    cout << "Upgrade your Quarry";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << "   | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    cout << "wood 80";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " | stone 90 | ";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "energy 30";
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
    cout << " |" << endl;

    cout << "4. ";
    SetConsoleTextAttribute( hOut, FOREGROUND_RED);
    cout << "Back" << endl;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);

    cout << "Enter your choice: ";
    cin >> workshop_buy_choice;
    do{
        switch (workshop_buy_choice)
        {
            case 1:
                system("cls");

                cout << "1. ";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED);
                cout << "Upgrade your Axe";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << "      | ";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
                cout << "wood 40";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << " | stone 10 | ";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << "energy 15";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << " |" << endl;

                cout << "That will increase the extraction of wood by ";
                SetConsoleTextAttribute( hOut, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                cout << "2";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << " times" << endl;

                cout << "You want upgrade your Axe? " << endl;
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN);
                cout << "(1 for yes|0 for no)" << endl;
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << "Enter your choice: ";
                cin >> upgrade_axe_choice;
                do{
                    switch (upgrade_axe_choice)
                    {
                        case 1:
                            if (upgrade_axe == 0) {
                                if (energy_count >= 15) {
                                    if (wood_count >= 40 && stone_count >= 10) {
                                        upgrade_axe = 1;
                                        energy_count -= 15;
                                        time_count = 16;
                                        wood_count -= 40;
                                        stone_count -= 10;
                                        cout << "Congratulations, you've upgraded your axe!" << endl;
                                        Beep(900,100);
                                        Beep(1300,100);
                                        system("pause");
                                        return;
                                    } else {
                                        cout << "You don't have enough resources" << endl;
                                        system("pause");
                                        return;
                                    }
                                } else {
                                    cout << endl << "You don't have enough " << endl;
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                                    cout << "energy";
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                    cout << ". Come back here after sleep." << endl;
                                    system("pause");
                                    build_shop();
                                }
                            } else {
                                cout << "You've already upgraded your axe. Now you can buy Chainsaw" << endl;
                                system("pause");
                                return;
                            }
                            break;
                        case 0:
                            return;
                            break;
                        default:
                            cout << endl << "Invalid choice. Please select a valid option." << endl;
                            system("pause");
                            return;
                            break;
                    }
                } while (upgrade_axe_choice != 0);

                break;
            case 2:
                system("cls");

                cout << "2. ";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED);
                cout << "Buy Chainsaw";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << "          | ";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
                cout << "wood 60";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << " | stone 40 | ";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << "energy 20";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << " |" << endl;

                cout << "That will increase the extraction of wood by ";
                SetConsoleTextAttribute( hOut, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                cout << "3";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << " times" << endl;

                cout << "You want buy the Chainsaw?" << endl;
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN);
                cout << "(1 for yes|0 for no)" << endl;
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << "Enter your choice: ";
                cin >> chainsaw_choice;
                do{
                    switch (chainsaw_choice)
                    {
                        case 1:
                            if (chainsaw == 0) {
                                if (energy_count >= 20) {
                                    if (upgrade_axe == 1) {
                                        if (wood_count >= 60 && stone_count >= 40) {
                                            chainsaw = 1;
                                            energy_count -= 20;
                                            time_count = 16;
                                            wood_count -= 60;
                                            stone_count -= 40;
                                            cout << "Congratulations, you've buy the Chainsaw!" << endl;
                                            Beep(900,100);
                                            Beep(1300,100);
                                            system("pause");
                                            return;
                                        } else {
                                            cout << "You don't have enough resources" << endl;
                                            system("pause");
                                            return;
                                        }
                                    } else if (upgrade_axe == 0) {
                                        cout << "First, you have to upgrade your axe" << endl;
                                        system("pause");
                                        return;
                                    }
                                } else {
                                    cout << endl << "You don't have enough " << endl;
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                                    cout << "energy";
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                    cout << ". Come back here after sleep." << endl;
                                    system("pause");
                                    build_shop();
                                }
                            } else {
                                cout << "You've already bought the Chainsaw." << endl;
                                system("pause");
                                return;
                            }
                            break;
                        case 0:
                            return;
                            break;
                        default:
                            cout << endl << "Invalid choice. Please select a valid option." << endl;
                            system("pause");
                            return;
                            break;
                    }

                } while (chainsaw_choice != 0);
            case 3:
                system("cls");

                cout << "3. ";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED);
                cout << "Upgrade your Quarry";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << "          | ";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
                cout << "wood 80";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << " | stone 90 | ";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << "energy 30";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << " |" << endl;

                cout << "That will increase the stone production by ";
                SetConsoleTextAttribute( hOut, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                cout << "2";
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << " times" << endl;

                cout << "You want Upgrade your Quarry?" << endl;
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN);
                cout << "(1 for yes|0 for no)" << endl;
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                cout << "Enter your choice: ";
                cin >> upgrade_quarry_choice;
                do{
                    switch (upgrade_quarry_choice)
                    {
                        case 1:
                            if (upgrade_quarry == 0) {
                                if (energy_count >= 30) {
                                    if (quarry == 1) {
                                        if (wood_count >= 80 && stone_count >= 90) {
                                            upgrade_quarry = 1;
                                            energy_count -= 30;
                                            day_count++;
                                            time_count = 16;
                                            wood_count -= 80;
                                            stone_count -= 90;
                                            cout << "Congratulations, you've Upgraded your Quarry!" << endl;
                                            Beep(900,100);
                                            Beep(1300,100);
                                            system("pause");
                                            return;
                                        } else {
                                            cout << "You don't have enough resources" << endl;
                                            system("pause");
                                            return;
                                        }
                                    } else if (quarry == 0) {
                                        cout << "First, you have to build the Quarry" << endl;
                                        system("pause");
                                        return;
                                    }
                                } else {
                                    cout << endl << "You don't have enough " << endl;
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                                    cout << "energy";
                                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
                                    cout << ". Come back here after sleep." << endl;
                                    system("pause");
                                    build_shop();
                                }
                            } else {
                                    cout << "You've already Upgraded your Quarry." << endl;
                                    system("pause");
                                    return;
                            }
                            break;
                            
                        case 0:
                            return;
                            break;
                        default:
                            cout << endl << "Invalid choice. Please select a valid option." << endl;
                            system("pause");
                            return;
                            break;
                    }

                } while (upgrade_quarry_choice != 0);

            case 4:
                buildings();
                break;
            default:
                cout << endl << "Invalid choice. Please select a valid option." << endl;
                system("pause");
                workshop_func();
                break; 
        }
    } while (workshop_buy_choice != 4);
}
