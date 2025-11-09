#include "Car.h"
#include "ServiceRecord.h"
#include <iostream>

void findInInventory(std::vector<Car>::iterator it, std::vector<Car>& inventory, int id){
	while(it != inventory.end()){
		if(it->getId() == id){
			break;
		}
		++it;
	}
}

void makeTrade(std::vector<Car>& inventory, Car& tradein, Car& tradeout){
	ServiceRecord outInspection("Sale inspection.", 0.0);
	tradeout.addRecord(outInspection);

	ServiceRecord inInspection("Presale inspection.", 19.95);
	tradein.addRecord(inInspection);

	auto it=inventory.begin();
	findInInventory(it, inventory, tradeout.getId());
	if(it != inventory.end()){
		inventory.erase(it);
	}
	inventory.push_back(std::move(tradein));
}

int main(int argc, char** argv){
	Car a(1985, "Toyota Hilux");
	ServiceRecord first("Oil change.", 9.95f);
	a.addRecord(first);
    std::cout << "Car a: " << a << std::endl;
    //std::cout << "Car a id: " << a.getId() << std::endl; //ensure unique car a id

	Car b(a);
	first = ServiceRecord("Radiator flush.", 19.95);
	b.addRecord(first); 
    std::cout << "Car b: " << b << std::endl;
    //std::cout << "Car b id: " << b.getId() << std::endl; //ensure unique car b id
    
   
	std::vector<Car> inventory;
    //std::cout << "after inventory is created" << std::endl;
	inventory.push_back(std::move(a));
	inventory.push_back(std::move(b)); //copy constructor called twice here because b initially takes on a as an argument, calling it once THEN using b in push_back calls copy constructor again

    //std::cout << "inside inventory: " << std::endl; //check inventory
    //for (auto it = inventory.begin(); it != inventory.end(); ++it) {
    //    std::cout << *it << std::endl;
    //} 

	Car c(b);
    //std::cout << "Check to see if c.setModel calls copy const" << std::endl;
	c.setModel("Ford F150");
    //std::cout << "Car c id: " << c.getId() << std::endl; //ensure unique car c id

	std::cout << "Customer wants to trade in " << c << std::endl;
	std::cout << "They want to get " << a << std::endl;
    
    std::cout << "Before trade, inventory is: " << std::endl; //check if copy constructor is getting called in makeTrade
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        std::cout << *it << std::endl;
    } 
	makeTrade(inventory, c, a);

	std::cout << "After trade, inventory is: " << std::endl;
	std::cout << "===========================" << std::endl;
	for(auto it = inventory.begin(); it != inventory.end(); ++it){
		std::cout << *it << std::endl;
	}
}
