#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;


class City{
	public:string name;
	public: int x, y;

	City(string _name, int _x, int _y){
		this->name = _name;
		this->x = _x;
		this->y = _y;
	}
};

class Organism{

	public: int fitness, distance;
	public: vector<City> cities;
	
	Organism(){
		this->fitness = 0;
		this->distance = 0;
		this->cities.push_back(City("Aspen", 5, 2));
		this->cities.push_back(City("Boulder", 16, 3));
		this->cities.push_back(City("Columbine",13 , 5));
		this->cities.push_back(City("Denver", 15, 9));
		this->cities.push_back(City("Eagle", 10, 10));
		this->cities.push_back(City("Fruita", 4, 9));
		this->cities.push_back(City("Grand Junction", 6, 12));
		this->cities.push_back(City("Hotchkiss", 12, 13));
		this->cities.push_back(City("Idaho Springs", 9, 14));
		this->cities.push_back(City("Jamestown", 16, 20));
		this->cities.push_back(City("Keystone", 18, 18));
		this->cities.push_back(City("Leadville", 2, 5));
		this->cities.push_back(City("Montrose", 7, 5));
		this->cities.push_back(City("Nucla", 2, 16));
		this->cities.push_back(City("Ouray", 11, 18));
		this->cities.push_back(City("Palisade", 8, 18));
		this->cities.push_back(City("Rifle", 5, 11));
		this->cities.push_back(City("Silverton", 16, 1));
		this->cities.push_back(City("Telluride", 12, 4));
		this->cities.push_back(City("Vail", 3, 11));
		this->cities.push_back(City("Westminster", 7, 14));
		this->cities.push_back(City("Yuma", 1, 1));
		this->distance = this->getDistance();
	}

	public: void shuffle(){
		random_shuffle(this->cities.begin(),this->cities.end());
		City start = this->cities.front(); //get the starting city
		this->cities.push_back(start); // add the starting city to the end of the vector
	}

	int getDistance(){
		for(int i=0; i < this->cities.size()-1;  i++){
			// euclidean distance between cities
			this->distance += sqrt( pow( this->cities[i].x - this->cities[i+1].x, 2.0 ) + ( pow( this->cities[i].y - this->cities[i+1].y, 2.0 ) ) );
		}
		return this->distance;
	}

	int getFitness(){
		this->fitness = 1000- this->distance;
		return this->fitness;
	}
};

class Generation{
	//public: const int size = 100;
	public: vector<Organism> organisms;

	Generation(){
		for(int i=0; i < 100; i++){
			Organism org;
			org.shuffle();
			organisms.push_back(org);
		}
	}

	void listFirstCity(){
		for(int i=0; i<organisms.size(); i++){
			cout << organisms[i].cities.front().name << "->" << organisms[i].cities.back().name << organisms[i].getDistance() <<  endl;
		}
	}

};

class Darwin{

};

int main(){
	cout << "genetic algorithm in motion" << endl;
	Generation x;
	x.listFirstCity();
	return 0;
}