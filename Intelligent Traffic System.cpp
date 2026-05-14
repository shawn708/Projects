#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// ======================= ENCAPSULATION =======================
class Vehicle {
private:
    string vehicleID;
    string vehicleType;
    int speed;
    bool emergencyVehicle;

public:
    Vehicle(string id, string type, int spd, bool emergency = false) {
        vehicleID = id;
        vehicleType = type;
        speed = spd;
        emergencyVehicle = emergency;
    }

    string getVehicleID() {
        return vehicleID;
    }

    string getVehicleType() {
        return vehicleType;
    }

    int getSpeed() {
        return speed;
    }

    bool isEmergencyVehicle() {
        return emergencyVehicle;
    }
};

// ======================= ABSTRACTION =======================
class Sensor {
public:
    virtual int detectVehicles() = 0;
    virtual bool detectEmergencyVehicle() = 0;
};

// ======================= INHERITANCE =======================
class RoadLane : public Sensor {
protected:
    string laneName;
    vector<Vehicle> vehicles;

public:
    RoadLane(string name) {
        laneName = name;
    }

    void addVehicle(Vehicle v) {
        vehicles.push_back(v);
    }

    int detectVehicles() override {
        return vehicles.size();
    }

    bool detectEmergencyVehicle() override {

        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i].isEmergencyVehicle()) {
                return true;
            }
        }

        return false;
    }

    string getLaneName() {
        return laneName;
    }

    void displayVehicles() {

        cout << "\nVehicles in " << laneName << ":\n";

        if (vehicles.empty()) {
            cout << "No vehicles detected.\n";
            return;
        }

        for (int i = 0; i < vehicles.size(); i++) {

            cout << i + 1 << ". "
                 << vehicles[i].getVehicleType()
                 << " | ID: " << vehicles[i].getVehicleID()
                 << " | Speed: " << vehicles[i].getSpeed()
                 << " km/h";

            if (vehicles[i].isEmergencyVehicle()) {
                cout << " | EMERGENCY VEHICLE";
            }

            cout << endl;
        }
    }
};

// ======================= POLYMORPHISM =======================
class TrafficLight {
protected:
    string currentLight;
    int timer;

public:

    virtual void controlTraffic(int vehicleCount, bool emergency) {

        if (emergency) {
            currentLight = "GREEN";
            timer = 15;
        }
        else if (vehicleCount >= 5) {
            currentLight = "GREEN";
            timer = 10;
        }
        else if (vehicleCount > 0) {
            currentLight = "GREEN";
            timer = 5;
        }
        else {
            currentLight = "RED";
            timer = 0;
        }
    }

    virtual void displayLight() {

        cout << "Traffic Light: "
             << currentLight
             << " | Timer: "
             << timer
             << " seconds\n";
    }

    void countdown() {

        for (int i = timer; i > 0; i--) {

            cout << "Time Remaining: "
                 << i << " sec\r";

            cout.flush();

            this_thread::sleep_for(chrono::seconds(1));
        }

        cout << endl;
    }
};

// Smart Traffic Light
class SmartTrafficLight : public TrafficLight {
public:

    void controlTraffic(int vehicleCount, bool emergency) override {

        if (emergency) {

            currentLight = "GREEN (Emergency Priority)";
            timer = 15;
        }
        else if (vehicleCount >= 5) {

            currentLight = "GREEN (Heavy Traffic)";
            timer = 10;
        }
        else if (vehicleCount > 0) {

            currentLight = "GREEN";
            timer = 5;
        }
        else {

            currentLight = "RED";
            timer = 0;
        }
    }

    void displayLight() override {

        cout << "Smart Traffic Light Status: "
             << currentLight
             << " | Timer: "
             << timer
             << " seconds\n";
    }
};

// ======================= TRAFFIC CONTROLLER =======================
class TrafficController {
private:
    SmartTrafficLight light1;
    SmartTrafficLight light2;

public:

    void manageTraffic(RoadLane &lane1, RoadLane &lane2) {

        int lane1Vehicles = lane1.detectVehicles();
        int lane2Vehicles = lane2.detectVehicles();

        bool lane1Emergency = lane1.detectEmergencyVehicle();
        bool lane2Emergency = lane2.detectEmergencyVehicle();

        cout << "\n================ SMART TRAFFIC ANALYSIS ================\n";

        cout << lane1.getLaneName()
             << " Vehicles: " << lane1Vehicles << endl;

        cout << lane2.getLaneName()
             << " Vehicles: " << lane2Vehicles << endl;

        // ================= EMERGENCY PRIORITY =================
        if (lane1Emergency) {

            cout << "\nEMERGENCY VEHICLE DETECTED IN "
                 << lane1.getLaneName() << endl;

            light1.controlTraffic(lane1Vehicles, true);
            light2.controlTraffic(0, false);
        }

        else if (lane2Emergency) {

            cout << "\nEMERGENCY VEHICLE DETECTED IN "
                 << lane2.getLaneName() << endl;

            light1.controlTraffic(0, false);
            light2.controlTraffic(lane2Vehicles, true);
        }

        // ================= NORMAL TRAFFIC =================
        else {

            if (lane1Vehicles > lane2Vehicles) {

                cout << "\nPriority Given To: "
                     << lane1.getLaneName() << endl;

                light1.controlTraffic(lane1Vehicles, false);
                light2.controlTraffic(0, false);
            }

            else if (lane2Vehicles > lane1Vehicles) {

                cout << "\nPriority Given To: "
                     << lane2.getLaneName() << endl;

                light1.controlTraffic(0, false);
                light2.controlTraffic(lane2Vehicles, false);
            }

            else {

                cout << "\nEqual Traffic Detected.\n";

                light1.controlTraffic(lane1Vehicles, false);
                light2.controlTraffic(lane2Vehicles, false);
            }
        }

        // ================= DISPLAY RESULTS =================
        cout << "\n" << lane1.getLaneName() << " ";
        light1.displayLight();

        cout << lane2.getLaneName() << " ";
        light2.displayLight();

        cout << "\nStarting Traffic Countdown...\n";

        light1.countdown();
        light2.countdown();
    }
};

// ======================= MAIN FUNCTION =======================
int main() {

    RoadLane laneA("Lane A");
    RoadLane laneB("Lane B");

    // Normal Vehicles
    laneA.addVehicle(Vehicle("KDA123A", "Car", 20));
    laneA.addVehicle(Vehicle("KDB456B", "Bus", 25));
    laneA.addVehicle(Vehicle("KDC789C", "Truck", 35));

    // Emergency Vehicle
    laneB.addVehicle(Vehicle("AMB001", "Ambulance", 100, true));

    laneB.addVehicle(Vehicle("KDD111D", "Car", 30));

    // Display Vehicles
    laneA.displayVehicles();
    laneB.displayVehicles();

    // Traffic Controller
    TrafficController controller;

    // Intelligent Traffic Handling
    controller.manageTraffic(laneA, laneB);

    return 0;
}