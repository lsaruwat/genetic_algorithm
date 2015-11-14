#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unistd.h>

using namespace std;


class City;
class Organism;
class Generation;
class BogoEvo;
class GenEvo;



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

	public: 
		int fitness, distance, differentCities;
		vector<City> cities;
		bool isTour;
	
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

		this->isTour = true;
		this->differentCities = this->cities.size();
		this->distance = this->getDistance();
	}

	public: 

	void shuffle(){
		random_shuffle(this->cities.begin(),this->cities.end());
	}

	string orgToString(){
		string orgString = "";

		for(int i=0; i < this->cities.size(); i++){
			orgString += this->cities[i].name + "-> "; 
		}


		orgString += this->cities[0].name;
		return orgString;
	}

	int getDistance(){
		this->distance = 0;
		for(int i=0; i < this->cities.size()-1;  i++){
			// euclidean distance between cities
			this->distance += sqrt( pow((this->cities[i].x - this->cities[i+1].x), 2.0 ) + pow((this->cities[i].y - this->cities[i+1].y), 2.0 ) );
		}
		// return to the beginning of your journey
		this->distance += sqrt( pow((this->cities[this->cities.size()-1].x - this->cities[0].x), 2.0 ) + pow((this->cities[this->cities.size()-1].y - this->cities[0].y), 2.0 ) );
		return this->distance;
	}

	int getFitness(){
		int tourPenalty = (this->isTour ? 1 : 2);

		this->fitness = (pow(this->differentCities,2) - this->distance) / (tourPenalty);
		//this->fitness = 1000 - this->distance;
		return this->fitness;
	}

	int getDiversity(){

		for(int i=0; i < this->cities.size(); i++){
			int cityCount = 0; 
			for(int j=0; j < this->cities.size(); j++){
				if(this->cities[i].name == this->cities[j].name) cityCount++;
				
				if(cityCount >= 2) {// if a city shows up more than once then it is not a tour and we decrease number of different cities
					this->isTour = false;
					this->differentCities --;
				}
			}
		}


	}
};

bool compareByFitness(const Organism &s1, const Organism &s2){
   		return s1.fitness < s2.fitness;
	}


class Generation{
	public: Organism alpha;
	public: vector<Organism> organisms;

	Generation(){
	
	}

	Generation(int _genCapacity){
		for(int i=0; i < _genCapacity; i++){
			Organism org;
			org.shuffle();
			org.getDistance();
			org.getDiversity();
			org.getFitness();
			this->organisms.push_back(org);
		}

	}

	Generation(vector<Organism> &_organisms){
		for(int i=0; i<_organisms.size(); i++){
			this->organisms.push_back(_organisms[i]);
		}
	}

	void nextGenShit(int _genCapacity){
		for(int i=0; i < _genCapacity; i++){
			Organism org;
			org.getDistance();
			org.getDiversity();
			org.getFitness();
		}
	}

	void sortGen(){
		sort(organisms.begin(), organisms.end(), compareByFitness);
	}

	void getAlpha(){
		alpha = organisms.back();
	}

	void listFirstCity(){
		for(int i=0; i<organisms.size(); i++){
			cout << organisms[i].cities.front().name << "->" << organisms[i].cities.back().name << organisms[i].fitness <<  endl;
		}
	}

	Organism mutate(Organism org){
		int randInt1 = rand() % org.cities.size();
		int randInt2 = rand() % org.cities.size();
		
		City temp  = org.cities[randInt1];
		org.cities[randInt1] = org.cities[randInt2];
		org.cities[randInt2] = temp;

		return org;
	}

	Organism makeABaby(Organism mommy, Organism daddy){
		Organism baby;
		int randPivot = rand() % mommy.cities.size();
		for(int i=0; i<randPivot; i++){
			baby.cities[i] = daddy.cities[i];
		}

		for(int i=randPivot; i < mommy.cities.size(); i++){
			baby.cities[i] = mommy.cities[i];
		}

		return baby;
	}

	/*
	Organism makeABaby(Organism mommy, Organism daddy){
		Organism baby;
		baby.cities.clear();

		for(int i=0; i<12; i++){
			baby.cities.push_back(daddy.cities[i]);
		}

		for(int i=12; i < mommy.cities.size(); i++){
			baby.cities.push_back(mommy.cities[i]);
		}

		return baby;
	}*/


};

class BogoEvo{
public:
	vector<Generation> gens;
	vector<Organism> alphas;
	Organism winner;

	BogoEvo(int _numGens){
		
		for(int i=0; i < _numGens; i++){
			Generation x(1000);
			x.sortGen();
			x.getAlpha();
			this->alphas.push_back(x.alpha);
			//gens.push_back(x);
		}
		sortAlphas();
		getWinner();
		cout << "winner: " << this->winner.fitness <<  " distance " << this->winner.distance << endl;
	}

	void sortAlphas(){
		sort(this->alphas.begin(), this->alphas.end(), compareByFitness);
	}

	void getWinner(){
		winner = this->alphas.back();
	}

};

class GenEvo{
public:
	vector<Generation> gens;
	vector<Organism> alphas;
	Organism winner;
	int genSize = 100;

	GenEvo(int _numGens){
		Organism o;
		this->alphas.push_back(o);
		Generation x(this->genSize); // first generation
		int i=0;
		for(int i=0; i < _numGens; i++){
		//while(this->alphas.back().distance >=150){
			i++;
			Generation nextGen;

			x.sortGen();
			x.getAlpha();

			this->alphas.push_back(x.alpha);
			if(i % _numGens == 0)cout<<i<< " " << x.alpha.distance << endl; 
			//get the top 10% of the organisms from previous generation and add them to new gen
			for(int i=x.organisms.size(); i > .9*x.organisms.size(); i--){
				nextGen.organisms.push_back(x.organisms[i]);
			}

			//add crossover to makeup 70% of new population
			for(int i=0; i < .5*x.organisms.size(); i++){
				int randInt1 = rand() % x.organisms.size()*.1 + (.9*x.organisms.size()); // random int for top 10% of organisms
				int randInt2 = rand() % x.organisms.size()*.1 + (.9*x.organisms.size()); // random int for top 10% of organisms
				nextGen.organisms.push_back(x.makeABaby(x.organisms[randInt1], x.organisms[randInt2]));
			}

			//add mutations of the top 10% of the population
			for(int i=0; i < .15*x.organisms.size(); i++){
				int randInt = rand() % x.organisms.size()*.1 + (.9*x.organisms.size()); // random int for top 10% of organisms
				nextGen.organisms.push_back(x.mutate(x.organisms[randInt]));
			}

			//add variety of 1% of random organisms
			for(int i=0; i<.25*x.organisms.size(); i++){
				int randInt = rand() % x.organisms.size()*.9; // random int from 0 to size -1
				Organism shuffledOrg;
				shuffledOrg.shuffle();
				nextGen.organisms.push_back(shuffledOrg);
			}



			//do next gen shit
			nextGen.nextGenShit(this->genSize);
			
			//replace the old gen with the new one
			x.organisms.clear();
			for(int i=0; i < nextGen.organisms.size(); i++){
				x.organisms.push_back(nextGen.organisms[i]);
			}


			//gens.push_back(x);
			this->sortAlphas();
		}

		this->getWinner();
		string _isTour;
		this->winner.isTour ? _isTour = "isTour" : _isTour = "nope";
		cout << "winner: " << this->winner.fitness <<  " distance: " << this->winner.distance << " isTour: " << _isTour << endl;
		cout << this->winner.orgToString() << endl;
	}


	void sortAlphas(){
		sort(this->alphas.begin(), this->alphas.end(), compareByFitness);
	}

	void getWinner(){
		winner = this->alphas.back();
	}

};

int main(int argc, char* argv[]){
	//string numGens = argv[1];
	cout << "genetic algorithm in motion" << endl;
	
	//BogoEvo x(1000);
	
	GenEvo(3000);
	
	return 0;
}