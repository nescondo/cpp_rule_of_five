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
    std::cout<< "Nikolai Escondo, collaborated with Benjamin Kolhoff" << std::endl;
	Car a(1985, "Toyota Hilux");
	ServiceRecord first("Oil change.", 9.95f);
	a.addRecord(first);
    //std::cout << "Car a: " << a << std::endl;
    //std::cout << "Car a id: " << a.getId() << std::endl; //ensure unique car a id

	Car b(a);
	first = ServiceRecord("Radiator flush.", 19.95);
	b.addRecord(first); 
    //std::cout << "Car b: " << b << std::endl;
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
    
    //std::cout << "Before trade, inventory is: " << std::endl; //check if copy constructor is getting called in makeTrade
    //for (auto it = inventory.begin(); it != inventory.end(); ++it) {
    //    std::cout << *it << std::endl;
    //} 

	makeTrade(inventory, c, a);

	std::cout << "After trade, inventory is: " << std::endl;
	std::cout << "===========================" << std::endl;
	for(auto it = inventory.begin(); it != inventory.end(); ++it){
		std::cout << *it << std::endl;
	}
    
    std::vector<Car> usedInventory;
    
    Car d(c);
    d.setYear(2025);
    d.setModel("Tesla");
    first = ServiceRecord("Unbrick iPad drivers.", 2999.95);
    d.addRecord(first);
    
    Car e(d);
    e.setYear(2017);
    e.setModel("Jeep Wrangler");
    first = ServiceRecord("Radiator flush.", 29.95);
    e.addRecord(first);
    ServiceRecord second("Oil change.", 99.95);
    e.addRecord(second);
    
    Car f(e);
    f.setYear(2024);
    f.setModel("Subaru Outback");
    first = ServiceRecord("Oil change.", 9.95);
    f.addRecord(first);
    
    Car g(f);
    g.setYear(2019);
    g.setModel("Honda HRV");
    first = ServiceRecord("Replace tires.", 1199.95);
    g.addRecord(first);
    
    Car h(g);
    h.setYear(2012);
    h.setModel("Ford Fusion");
    first = ServiceRecord("Radiator flush.", 29.95);
    h.addRecord(first);
    
    usedInventory.push_back(std::move(d));
    usedInventory.push_back(std::move(e));
    usedInventory.push_back(std::move(f));
    usedInventory.push_back(std::move(g));
    usedInventory.push_back(std::move(h));
    
    std::sort(usedInventory.begin(), usedInventory.end());
 
    std::cout << "Used inventory: " << std::endl;
    std::cout << "================" << std::endl;
    for (auto it = usedInventory.begin(); it != usedInventory.end(); ++it) {
        std::cout << *it << std::endl;
    }
}
