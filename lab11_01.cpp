#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

class Spacecraft{
protected:
    string name;
    string propulsion;
    int hullStrength;
    int speed;
public:
    Spacecraft(const string& name, const string& propulsion, int hullStrength, int speed) : name(name), propulsion(propulsion), hullStrength(hullStrength), speed(speed){
        if (hullStrength < 0 || hullStrength >100){
            hullStrength = 50;
        }
        if (speed < 0 || speed >100){
            speed = 50;
        }
    }
    // void setHullStrength(int strength){
    //     if (hullStrength < 0 || hullStrength >100){
    //         hullStrength = 50;
    //     }else{
    //         hullStrength = strength;
    //     }
    // }
    // void setSpeed(int s){
    //     if (speed < 0 || speed >100){
    //         speed = 50;
    //     }else{
    //         speed = s;
    //     }
    // }
    string getName() const{
        return name;
    }
    string getPropulsion() const{
        return propulsion;
    }
    int getHullStrength() const{
        return hullStrength;
    }
    int getSpeed() const{
        return speed;
    }

};

class AlienShip : public Spacecraft{
private:
    int evasionChance;
public:
    AlienShip(const string& name, const string& propulsion, int hullStrength, int speed, int evasionChance) : Spacecraft(name, propulsion,hullStrength,speed), evasionChance(evasionChance){
        if (evasionChance < 0 || evasionChance >100){
            evasionChance = 50;
        }
    }
    // void setEvasionChance(int chance){
    //     if (chance < 0 || chance >100){
    //         chance = 50;
    //     }else{
    //         evasionChance = chance;
    //     }
    // }
    int getEvasionChance()const{
        return evasionChance;
    }
    bool attemptFlee()const{
        if ((rand()%100) < evasionChance){ 
            return true;
        }else{
            return false;
        }
    }

};

class FleetShip : public Spacecraft{
public:
    FleetShip(const string& name, const string& propulsion, int hullStrength, int speed) : Spacecraft(name, propulsion,hullStrength,speed){}
};

class Scanner{
private:
    string name;
    int range;

public:
    Scanner(const string& name, int range) : name(name), range(range){
        if (range < 0 || range > 100){
            range = 40;
        }
    }
    bool scanShip(const AlienShip& target)const{ 
        if ((rand()%100) < range){
            return true;
        }else{
            return false;
        }
    }
    string getName()const{
        return name;
    }
    int getRange()const{
        return range;
    }
};

class TractorBeam{
private:
    string name;
    int strength;
public:
    TractorBeam(const string& name, int strength) : name(name), strength(strength){
        if (strength < 0 || strength > 100){
            strength = 20;
        }
    }
    int captureShip(const AlienShip& target)const{
        return max(strength-(target.getHullStrength()/5),0);
    }
    string getName()const{
        return name;
    }
    int getStrength()const{
        return strength;
    }
};

class Player{
private:
    vector<Scanner> scanners;
    vector<FleetShip> fleet;
    TractorBeam* tractorBeam = nullptr;
public:
    Player() : tractorBeam(nullptr){}  //??????????
    void addScanner(const Scanner& scanner){
        scanners.push_back(scanner);
    }
    void equipTractorBeam(TractorBeam* beam){
        tractorBeam = beam;
    }
    bool captureShip(const AlienShip& target, int scannerIndex){
        if (scannerIndex < 0 || scannerIndex >= scanners.size()){
            return false;
        }
        if (!scanners[scannerIndex].scanShip(target)){
            scanners.erase(scanners.begin()+scannerIndex);
            return false;
        }
        int baseChance = 50;
        if (tractorBeam){
            baseChance += tractorBeam -> captureShip(target);
        }
        if ((rand()%100) < baseChance){
            fleet.push_back(FleetShip(target.getName(), target.getPropulsion(),target.getHullStrength(),target.getSpeed()));
            return true;
        }
        scanners.erase(scanners.begin()+scannerIndex);
        return false;
    }

    void displayInventory()const{
        cout<<"Scanners: "<<endl;
        for (const auto& scanner : scanners){
            cout<<scanner.getName()<<"(Range: "<<scanner.getRange()<<")"<<endl;
        }
        cout<<"Fleet: "<<endl;
        for (const auto& ship : fleet){
            cout<<ship.getName()<<"(Hull: "<<ship.getHullStrength()<<", Speed: "<<ship.getSpeed()<<endl;
        }
    }
};

class Galaxy{
private:
    vector<AlienShip> alienShips;
public:
    Galaxy(){}

    void addAlienShip(const AlienShip& ship){
        alienShips.push_back(ship);
    }

    AlienShip* explore(){
        if ((rand()%100) < 25 && !alienShips.empty()){
            return &alienShips[rand() % alienShips.size()];
        }else{
            return nullptr;
        }
    }

    void removeShip(int index){
        if (index >= 0 && index < alienShips.size()){
            alienShips.erase(alienShips.begin() + index);
        }
    }

    bool allCaptured()const{
        return alienShips.empty();
    }
};

int main() {
    srand(time(0));

    Player player;
    player.addScanner(Scanner("Basic", 40));
    player.addScanner(Scanner("Enhanced", 60));
    player.addScanner(Scanner("LongRange", 80));

    Galaxy galaxy;
    galaxy.addAlienShip(AlienShip("Scout", "Ion Drive", 30, 80, 70));
    galaxy.addAlienShip(AlienShip("Fighter", "Plasma Thruster", 50, 60, 40));
    galaxy.addAlienShip(AlienShip("Frigate", "Warp Engine", 80, 40, 20));
    galaxy.addAlienShip(AlienShip("Drone", "Solar Sail", 20, 90, 60));
    galaxy.addAlienShip(AlienShip("Destroyer", "Fusion Core", 90, 40, 30));

    std::cout << "Welcome to Space Explorer!\n";

    int choice;
    while (true) {
        std::cout << "Choose an action: 1. Explore, 2. Quit, 3. Check Inventory\n";
        std::cin >> choice;

        if (choice == 1) {
            AlienShip* encounteredShip = galaxy.explore();
            if (!encounteredShip) {
                std::cout << "No encounter.\n";
                continue;
            }

            std::cout << "Encountered " << encounteredShip->getName() << ". Scan? (0-No, 1-Yes): ";
            int scanChoice;
            std::cin >> scanChoice;

            if (scanChoice == 1) {
                std::cout << "Choose scanner (0-2): ";
                int scannerIndex;
                std::cin >> scannerIndex;

                if (player.captureShip(*encounteredShip, scannerIndex)) {
                    std::cout << "Captured " << encounteredShip->getName() << "!\n";
                    galaxy.removeShip(scannerIndex);
                } else {
                    std::cout << encounteredShip->getName() << " escaped!\n";
                }
            }
        } else if (choice == 2) {
            break;
        } else if (choice == 3) {
            player.displayInventory();
        }
    }

    std::cout << "Game Over. Final Inventory:\n";
    player.displayInventory();

    return 0;
}
