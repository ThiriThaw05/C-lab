#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CarbonEmitters{
protected:
    string id;
public:
    CarbonEmitters(string id) : id(id){}
    virtual double getCarbonFootprint()const = 0;
    virtual void displayDetails()const{
        cout<<"(ID: "<<id<<")"<<endl;
        cout<<"Carbon Footprints: "<<getCarbonFootprint()<<endl;
    }
    virtual ~CarbonEmitters(){}
};

class Factory : public CarbonEmitters{
private:
    int productionHours, energyPerHour, wastePerHour;
public:
    using CarbonEmitters::CarbonEmitters;
    Factory(string id,int production,int energy, int waste):CarbonEmitters(id),productionHours(production),energyPerHour(energy),wastePerHour(waste){
        if (productionHours >= 0 && productionHours <= 24){
            productionHours = production;
        }else{
            cout<<"production hours must be between 0 and 24"<<endl;
        }
    }
    double getCarbonFootprint()const override{
        return (energyPerHour*productionHours*0.5) + (wastePerHour*productionHours*0.2);
    }
    void displayDetails()const override{
        cout<<"Factory ";
        CarbonEmitters::displayDetails();
    }
};

class Car : public CarbonEmitters{
protected:
    double milesDriven, fuelEffiency;
public:
    Car(string id,double miles, double fuel): CarbonEmitters(id),milesDriven(miles),fuelEffiency(fuel){}
    virtual double getCarbonFootprint()const{
        return (milesDriven/fuelEffiency)*8.8;
    }
    void displayDetails()const override{
        cout<<"Car ";
        CarbonEmitters::displayDetails();
    }
};

class ElectricCar : public Car{
private:
    double batteryCapacity,chargeEffiency;
public:
    ElectricCar(string id,double battery, double charge) : Car(id,milesDriven,fuelEffiency), batteryCapacity(battery), chargeEffiency(charge){
        if (chargeEffiency >= 0 && chargeEffiency <= 1){
            chargeEffiency = charge;
        }else{
            cout<<"Charge Effiency must be 0 or 1"<<endl;
        }
    }
    double getCarbonFootprint()const override{
        return (milesDriven/fuelEffiency)*(1/chargeEffiency)*0.5;
    }
    void displayDetails()const override{
        cout<<"Electric Car ";
        CarbonEmitters::displayDetails();
    }
};

class Building : public CarbonEmitters{
private:
    double energyUsage, numberOfOccupants;
public:
    Building(string id,double energy, double occupants) : CarbonEmitters(id),energyUsage(energy), numberOfOccupants(occupants){}
    double getCarbonFootprint()const{
        return (energyUsage/numberOfOccupants)*0.5*numberOfOccupants;
    }
    void displayDetails()const override{
        cout<<"Building ";
        CarbonEmitters::displayDetails();
    }
};

class Bicycle : public CarbonEmitters{
private:
    double milesRidden, manufacturingEmissions;
public: 
    Bicycle(string id,double miles, double manufacturing) : CarbonEmitters(id), milesRidden(miles), manufacturingEmissions(manufacturing){}
    double getCarbonFootprint()const{
        return manufacturingEmissions/365;
    }
    void displayDetails()const override{
        cout<<"Bicycle ";
        CarbonEmitters::displayDetails();
    }
};

int main(){
    vector<CarbonEmitters*> emitters;
    char choice;
    do{
        cout<<"Select object type to create: ";
        cout<<"\n1. Factory"<<endl;
        cout<<"2. Electric Car"<<endl;
        cout<<"3. Building"<<endl;
        cout<<"4. Car"<<endl;
        cout<<"5. Bicycle"<<endl;
        cout<<"Enter choice (1-5): ";
        int type;
        cin>>type;
        cout<<"Enter object ID: ";
        string id;
        cin>>id;
        switch(type){
            case 1: { //Factory
                double production,energy,waste;
                cout<<"Enter Production hours, energy/hour, waste/hour: ";
                cin>>production>>energy>>waste;
                emitters.push_back(new Factory(id,production,energy,waste));
                break;
            }
            case 2: { //Electric Car
                double battery,charge;
                cout<<"Enter Battery Capacity, Charge Effiency: ";
                cin>>battery>>charge;
                emitters.push_back(new ElectricCar(id,battery,charge));
                break;
            }
            case 3: { //Building
                double energyUsage,numberOfOccupants;
                cout<<"Enter Energy Usage, Number of Occupants: ";
                cin>>energyUsage>>numberOfOccupants;
                emitters.push_back(new Building(id,energyUsage,numberOfOccupants));
                break;
            }
            case 4: { //Car
                double miles,fuel;
                cout<<"Enter Miles Driven, Fuel Effiency: ";
                cin>>miles>>fuel;
                emitters.push_back(new Car(id,miles,fuel));
                break;
            }
            case 5: { //Bicycle
                double miles,manufacturing;
                cout<<"Enter Miles Ridden, Manufacturing Emission: ";
                cin>>miles>>manufacturing;
                emitters.push_back(new Bicycle(id,miles,manufacturing));
                break;
            }
            default:
                cout<<"Invalid Choice!";
                break;
        }
        cout<<"Add another object? (y/n): ";
        cin>>choice;
    }while(choice == 'y');

    cout<<"\nCarbon Footprint Report\n";
    cout<<"-----------------------------\n";
    double totalFootprint = 0;

    for (const auto emitter : emitters){
        emitter->displayDetails();
        totalFootprint += emitter->getCarbonFootprint();
        cout<<"--------------------------------"<<endl;
    }
    cout<<"Total carbon footprint: "<<totalFootprint<<endl;
    return 0;
}