#include <iostream>
#include <string>


class Vehicle {
protected:
    std::string make;
    std::string model;
    int year;
    double fuelEfficiency;

public:
    Vehicle(const std::string& make = "", const std::string& model = "",
            int year = 0, double fuelEfficiency = 0.0)
        : make(make), model(model), year(year), fuelEfficiency(fuelEfficiency) {}

    virtual ~Vehicle() = default;
    virtual void startEngine() = 0;
    virtual void stopEngine() = 0;
    virtual std::string getDescription() const = 0;
    virtual double calculateRange(double fuelAmount) const = 0;
};


class Car : public Vehicle {
private:
    int numberOfDoors;
    double trunkCapacity;

public:
    Car(const std::string& make = "", const std::string& model = "",
        int year = 0, double fuelEfficiency = 0.0,
        int doors = 4, double trunk = 500.0)
        : Vehicle(make, model, year, fuelEfficiency),
          numberOfDoors(doors), trunkCapacity(trunk) {}

    void startEngine() override {
        std::cout << "Автомобиль " << make << " " << model << " запускает двигатель.\n";
    }

    void stopEngine() override {
        std::cout << "Автомобиль " << make << " " << model << " останавливает двигатель.\n";
    }

    std::string getDescription() const override {
        return "Автомобиль: " + make + " " + model + ", " + std::to_string(year) +
               " год, " + std::to_string(numberOfDoors) + " дверей, багажник " +
               std::to_string(trunkCapacity) + " л.";
    }

    double calculateRange(double fuelAmount) const override {
        if (fuelEfficiency <= 0) return 0.0;
        return (fuelAmount / fuelEfficiency) * 100.0;
    }

    void openTrunk() {
        std::cout << "Открывается багажник автомобиля " << make << " " << model << ".\n";
    }
};

class Truck : public Vehicle {
private:
    double cargoCapacity; // в кг
    bool hasTrailer;

public:
    Truck(const std::string& make = "", const std::string& model = "",
          int year = 0, double fuelEfficiency = 0.0,
          double capacity = 1000.0, bool trailer = false)
        : Vehicle(make, model, year, fuelEfficiency),
          cargoCapacity(capacity), hasTrailer(trailer) {}

    void startEngine() override {
        std::cout << "Грузовик " << make << " " << model << " запускает двигатель.\n";
    }

    void stopEngine() override {
        std::cout << "Грузовик " << make << " " << model << " останавливает двигатель.\n";
    }

    std::string getDescription() const override {
        return "Грузовик: " + make + " " + model + ", " + std::to_string(year) +
               " год, грузоподъёмность " + std::to_string(cargoCapacity) + " кг" +
               (hasTrailer ? ", с прицепом" : ", без прицепа");
    }

    double calculateRange(double fuelAmount) const override {
        if (fuelEfficiency <= 0) return 0.0;
        return (fuelAmount / fuelEfficiency) * 100.0;
    }

    void loadCargo(double weight) {
        if (weight <= cargoCapacity) {
            std::cout << "Загружено " << weight << " кг груза в грузовик " << make << " " << model << ".\n";
        } else {
            std::cout << "Перегруз! Максимальная загрузка: " << cargoCapacity << " кг.\n";
        }
    }
};


class Motorcycle : public Vehicle {
private:
    int engineSizeCC;
    bool hasSideCar;

public:
    Motorcycle(const std::string& make = "", const std::string& model = "",
               int year = 0, double fuelEfficiency = 0.0,
               int cc = 500, bool sidecar = false)
        : Vehicle(make, model, year, fuelEfficiency),
          engineSizeCC(cc), hasSideCar(sidecar) {}

    void startEngine() override {
        std::cout << "Мотоцикл " << make << " " << model << " запускает двигатель.\n";
    }

    void stopEngine() override {
        std::cout << "Мотоцикл " << make << " " << model << " останавливает двигатель.\n";
    }

    std::string getDescription() const override {
        return "Мотоцикл: " + make + " " + model + ", " + std::to_string(year) +
               " год, " + std::to_string(engineSizeCC) + " см³" +
               (hasSideCar ? ", с коляской" : ", без коляски");
    }

    double calculateRange(double fuelAmount) const override {
        if (fuelEfficiency <= 0) return 0.0;
        return (fuelAmount / fuelEfficiency) * 100.0;
    }

    void performWheelie() {
        std::cout << "Мотоцикл " << make << " " << model << " делает вилли!\n";
    }
};


int main() {
    Car car("Toyota", "Camry", 2022, 7.5, 4, 520.0);
    Truck truck("Volvo", "FH16", 2021, 28.0, 20000.0, true);
    Motorcycle moto("Harley-Davidson", "Sportster", 2023, 4.5, 1200, false);

    Vehicle* vehicles[] = { &car, &truck, &moto };

    for (Vehicle* v : vehicles) {
        v->startEngine();
        std::cout << v->getDescription() << "\n";
        std::cout << "Запас хода на 50 литрах топлива: " << v->calculateRange(50.0) << " км\n";
        v->stopEngine();
        std::cout << "----------------------------------------\n";
    }

    car.openTrunk();
    truck.loadCargo(15000.0);
    moto.performWheelie();

    return 0;
}