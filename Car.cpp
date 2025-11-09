#include "Car.h"
#include <iostream>

int Car::current_id = 0;

Car::Car(int year, std::string model){
	this->id = Car::current_id++;
	this->year = year;
	this->model = model;
}

Car::Car(const Car& other) {
    //std::cout << "Copy constructor called" << std::endl;

    this->id = Car::current_id++;
    this->year = other.year;
    this->model = other.model;
}

Car& Car::operator=(const Car& other) {
    std::cout << "Copy assignment operator called" << std::endl;

    if (this != &other) {
        this->id = other.id;
        this->year = other.year;
        this->model = other.model;
    } 
    
    return *this;
}

Car::Car(Car&& other) noexcept {
    //std::cout << "Move constructor called" << std::endl;

    this->id = other.id;
    this->year = other.year;
    this->model = other.model; 
    this->records = other.records;

    //we still want to keep the data in the other Car object because we use it in makeTrade
}

Car& Car::operator=(Car&& other) noexcept {
    std::cout << "Move assignment operator called" << std::endl;

    if (this != &other) {
        this->id = other.id;
        this->year = other.year;
        this->model = other.model;
        this->records = other.records;
    }
    
    return *this;
}

int Car::getId() const {
	return this->id;
}

void Car::setYear(int year){
	this->year = year;
}

int Car::getYear() const {
	return year;
}

void Car::setModel(std::string model){
	this->model = model;
}

std::string Car::getModel() const {
	return model;
}

std::vector<ServiceRecord> Car::getRecords() const {
	return records;
}

void Car::addRecord(ServiceRecord record){
	records.push_back(record);
}

std::ostream& operator<<(std::ostream& os, const Car& car){
	os << car.id << ":" << car.year << " " << car.model << std::endl;
	os << "=========================" << std::endl;
	for(auto it=car.records.begin(); it != car.records.end(); ++it){
		os << "\t" << it->getCost() << ": " << it->getNotes() << std::endl;
	}
	return os;
}
