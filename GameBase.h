#pragma once
#include "GameBase.h"
#include "Utils.h"
#include "GameDefs.h"
#include "Screen.h"
#include "Player.h"
#include "Door.h"
#include "Key.h"
#include "Bomb.h"
#include "Spring.h"
#include "Maps.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class GameBase {
private:

    static constexpr int NUM_PLAYERS = 2;

    std::vector<Screen> screens;       // Array of all the available screens \ rooms

    Screen fixedScreens[NUM_SCREENS];  // Constant screens like menu\instructions
    int currRoomID;

    Player players[NUM_PLAYERS];       // Array of players in game
    int playerRoom[NUM_PLAYERS];       // Which room is each player at
    int roomsDone[NUM_PLAYERS];        // How many rooms did each player finish
    bool playerFinished[NUM_PLAYERS];  // Arr to follow the players who finished the game
    Point prevPos[NUM_PLAYERS];

    bool isRunning;     // True as long as player doesn't press pause or exit
    bool gameOver;      // True when all players finish 2 rooms
    size_t gameCycles=0;

public:

    // Functions
    void initGame();
    bool loadGameFiles();
    bool initGameFiles(std::vector<std::string>& outFiles);
    bool loadRiddles();
    bool loadRiddles(int loadRoomID);

    void run();
    void update();
    void render();

    virtual void delay(int ms);

    void displayLegend(const Screen& room);
    void displayFinalScoreboard() const;
    void drawPlayers();

    bool restartCurrentRoom();
    bool reloadRoom(int roomID);

    GameBase()=default;       // ctor
    virtual ~GameBase()=default;// d-ctor
    void setGame();
    void setRunning(bool option) {isRunning=option;}

    // Virtual
    virtual void handleInput() = 0;
    virtual int getDelay() = 0;

    size_t getGameCycle() const {return gameCycles;}

    // might need: getPlayer, getGameOver, getIsRunning getters etc


    // Game Loop Functions
    void moveRoom(Player& p, int dest);
    Point getStartPoint(Player& player, int idx) const;
    bool playersCollide(int currPlayerIndex, const Point& nextPos);
    void applyLifeLoss(Player& player);
    bool isFinalRoom(int dest) const { return dest == screens.size() - 1; }
    size_t getGameCycles() const {return gameCycles;}

    // Set Game Functions
    void showError(const std::string& msg);
    void showMessage(const std::string& msg);

    // Handle Functions
    void handleDoor(Player& player);
    void handleSwitch(Player& player);
    bool handleSprings(Player& p);
    void handleBombs();
    bool handleRiddles(Player& player);
    bool handleObstacles(Player& player, const Point& nextPos);
    void handleTorch(Player& player);
    void handleCollectibles(Player& player);
    bool handleTeleports(Player& player);
    bool handleDispose(Player& p);
    bool handleAcceleratedMovement(Player& player, int playerIndex);

    // Helper to Handle Functions
    bool isMatchingKey(Player& player, Screen& room, Door* door) const;
    void explodeBomb(Point center);
    void updateDoorBySwitches(int id);
    Spring* findAdjacentSpring(const Point& pos);
    bool compressSpring(Player& player, Spring& sp);
    void launchPlayer(Player& player, Spring& sp);

    int calcForce(const Player& pusher, const Obstacle* ob, Direction dir) const;
    bool canMoveObstacle(const std::vector<Point>& nextBody, const Obstacle* currOb);
    bool chainPushSuccess(int idx, Direction dir, const Point& obstaclePos);

    void processKey(char ch);
};
