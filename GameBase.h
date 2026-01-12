#pragma once
#include "Utils.h"
#include "GameDefs.h"
#include "Screen.h"
#include "Player.h"
#include "Door.h"
//#include "Key.h"
//#include "Bomb.h"
#include "Spring.h"
//#include "Maps.h"
#include <fstream>
#include <string>
#include <vector>
//#include <sstream>
//#include <algorithm>

class GameBase {
// ============== PROTECTED - For Derived Classes ==============
protected:
    std::vector<Screen> screens;
    int currRoomID;

    Player players[NUM_PLAYERS];
    int playerRoom[NUM_PLAYERS];
    int roomsDone[NUM_PLAYERS];
    bool playerFinished[NUM_PLAYERS];
    Point prevPos[NUM_PLAYERS];

    bool isRunning;
    bool gameOver;
    size_t gameCycles = 0;

    // ----- Getters -----
    bool isFinalRoom(int dest) const { return dest == static_cast<int>(screens.size()) - 1; }
    PlayerID getPlayerID(const Player& p) const {
        return (&p == &players[PLAYER_1]) ? PLAYER_1 : PLAYER_2;
    }

    // ----- Setters -----
    void setGame();

    // ----- Core Game Loop -----
    void update();
    virtual void render();

    // ----- Init Functions -----
    void initGame();
    bool loadGameFiles();
    bool initGameFiles(std::vector<std::string>& outFiles);
    bool loadRiddles();
    bool loadRiddles(int loadRoomID);

    // ----- Game Logic Functions -----
    void moveRoom(Player& p, int dest);
    Point getStartPoint(Player& player, int idx) const;
    bool playersCollide(int currPlayerIndex, const Point& nextPos);
    virtual void applyLifeLoss(Player& player);

    // ----- Display Functions -----
    void displayLegend(const Screen &room);
    void displayFinalScoreboard() const;
    void drawPlayers();

    // ----- Handle Functions -----
    void handleDoor(Player& player);
    void handleSwitch(Player& player);
    bool handleSprings(Player& p);
    void handleBombs();

    virtual bool handleRiddles(Player &player);
    bool handleRiddles(Player &player, bool solved);
    bool handleObstacles(Player& player, const Point& nextPos);
    void handleTorch(Player& player);
    void handleCollectibles(Player& player);
    bool handleTeleports(Player& player);
    bool handleDispose(Player& p);
    bool handleAcceleratedMovement(Player& player, int playerIndex);

    // ----- Helper Functions -----
    void processKey(char ch);
    bool isMatchingKey(Player& player, Screen& room, Door* door) const;
    void updateDoorBySwitches(int id);

    void explodeBomb(Point center);

    Spring* findAdjacentSpring(const Point& pos);
    bool compressSpring(Player& player, Spring& sp);
    void launchPlayer(Player& player, Spring& sp);
    int calcForce(const Player& pusher, const Obstacle* ob, Direction dir) const;
    bool canMoveObstacle(const std::vector<Point>& nextBody, const Obstacle* currOb);
    bool chainPushSuccess(int idx, Direction dir, const Point& obstaclePos);

    // ============== PUBLIC ==============
public:
    GameBase() = default;
    virtual ~GameBase() = default;
    void run();

    // ----- Pure Virtual -----
    virtual void handleInput() = 0;
    virtual int getDelay() const = 0;
    virtual void onScreenChange(PlayerID player, int room) = 0;
    virtual void onLifeLost(PlayerID player) = 0;
    virtual void onRiddle(PlayerID player, bool correct) = 0;
    virtual void onGameEnd() = 0;
    virtual void handleError(const std::string& msg) = 0;
    virtual void handleMessage(const std::string& msg) = 0;

};