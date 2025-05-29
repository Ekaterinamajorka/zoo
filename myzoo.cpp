#include <iostream>		//���������� �����/������ ������
#include <vector>		//���������� ������������ ������
#include <string>		//���������� ������ �� ��������
#include <ctime>		//���������� ��� ��������� �������
#include <cstdlib>		//���������� ��� ��������� �������
#include <algorithm>	//���������� ����� � ����������
#include <map>			//���������� ������������� ���������
#include <memory>		//���������� ����� ���������
#include <stdexcept>	//���������� ��������� ������

using namespace std;

//��������� ��������� �����
class Random {
public:
	static int range(int min, int max) {
		return rand() % (max - min + 1) + min;
	}
	static bool chance(int percent) {
		return rand() % 100 < percent;
	}
};

//���������� ������� "�����-���������"
class JokeCat {
private:
	vector<string> jokes = {
		"��� ������� �� ����. ����� - �������. ��, ���� �����, ������� ���� ���, ���.\n"
		"��� ��� ���������� �� ����� ������� ������:\n"
		"- �������, ���� � ���� ����, ���� ������.\n"
		"��, �����, �����������, ������ ������. ������� ��� �������. �� ��������� ���� ������� ��������� ����������: ������ ������, �������, �������� ������. ����� �������, ����� ������ ����� ������������.\n"
		"�����, ����� ���������. ��� ����� ����� ������� �� ����� ������:\n"
		"- �������, ���� � ���� ����, ���� ������.\n"
		"����� ������ ����� ������. �� ������ ���� ���� ������� �������� �������, �������� ���-��� � �������.\n"
		"������� ���, ��� ��� ���� ��������. ����� ����� ���������, ������ �� ����� ������� ������� ������. ��� ����� ������� �� ����� ������ � ������������ ����������:\n"
		"- �����, �� ���� ����� ��������� ���������?",

		"- �����, � �� ��� � ���� ��� ��� ����������?\n"
		"- �� � ����� ������ � ��� ������� ��������.\n"
		"- ��� �?\n"
		"- � ������ ������ � ���� ���� ������...\n"
		"- ��..� �� ������ ���� ���?\n"
		"- ���, ���..������ �������.",

		"����������� ��� ������� � ����. ���� �������:\n"
		"- �� ������, ����� ������� ������ ������ ��� �������?\n"
		"- ���, � ���?\n"
		"- �� ��������� ��� �����: ���� �� ��� �����, ����... �� �� �����.\n"
		"- � ���?\n"
		"- �� ������� ������ ������...\n"
		"- �� �?\n"
		"- �� ����� ������, ������ ������ ���� ������� ������ ���� � ������� ��������!"
	};

public:
	bool tellJoke() {
		// 5% ����, ��� ����� ��������
		if (Random::chance(5)) { 
			cout << "=== � ������� ������� ��������� ����� � �������:\n";
			//����������� ����� ���������� �������� �� ������
			cout << "\033[1;33m" << jokes[Random::range(0, jokes.size() - 1)] << "\033[0m\n\n"; 
			return true;
		}
		return false;
	}
};

//������������� ��������
class Animal {
private:
	string name;		
	string species;		
	int age;			
	double weight;		
	int climatePref;	
	int type;
	int price;
	bool isSick;
	bool isAlive;
	char gender;
	int maxAge;
	Animal* parent1;
	Animal* parent2;
	bool bornInZoo;

public:
	//�������������� ���������, � �������: ���, ���, ������, ����, ���, ������������ �������
	Animal(string n, string sp, int cp, int t, int p, char g, int mA,
		Animal* p1 = nullptr, Animal* p2 = nullptr, bool born = false) :
		name(n), species(sp), age(0), weight(Random::range(10, 100)),
		climatePref(cp), type(t), price(p), isSick(false), isAlive(true),
		gender(g), maxAge(mA), parent1(p1), parent2(p2), bornInZoo(born) {}

	//���������� ��������, ����� ���� � �������� ������ �� ��������
	void grow() {
		age++;
		weight += Random::range(-2, 5);
		if (weight < 5) die();

		if (age > maxAge && Random::chance(age)) {
			die();
		}
	}

	//10%, ��� �������� ��������
	void getSick() {
		if (Random::chance(10)) isSick = true;
	}

	//����� ������� � ������ ���������
	void heal() { isSick = false; }
	void die() { isAlive = false; }
	void rename(const string& newName) { name = newName; }

	//���������� ����������� ��������
	Animal operator+(Animal& other) {
		if (species != other.species) {
			throw runtime_error("������ ���������� ������ ���� ��������");
		}
		if (gender == other.gender) {
			throw runtime_error("������ ���������� �������� ������ ����");
		}
		if (age < 5 || other.age < 5) {
			throw runtime_error("�������� ������� ������� ��� �����������");
		}

		string babyName = "������� " + species;
		char babyGender = Random::chance(50) ? 'M' : 'F';
		int babyPrice = (price + other.price) / 2;

		return Animal(babyName, species, climatePref, type, babyPrice, babyGender, maxAge, this, &other, true);
	}

	//���������� � ��������
	string getName() const { return name; }
	string getSpecies() const { return species; }
	int getAge() const { return age; }
	double getWeight() const { return weight; }
	int getClimatePref() const { return climatePref; }
	int getType() const { return type; }
	int getPrice() const { return price; }
	bool getIsSick() const { return isSick; }
	bool getIsAlive() const { return isAlive; }
	char getGender() const { return gender; }
	int getMaxAge() const { return maxAge; }
	bool isBornInZoo() const { return bornInZoo; }
	//���������� ���������� � ��������� ���������
	string getParentsInfo() const {
		if (!bornInZoo) return "������ � ��������";
		string p1 = parent1 ? parent1->getName() : "����������";
		string p2 = parent2 ? parent2->getName() : "����������";
		return p1 + " � " + p2;
	}
	//���������� ��������� ������������� ���� �������
	string getTypeStr() const { return type == 0 ? "����������" : "������"; }
	//���������� �������������� ������ � ��������� ����
	string getClimateStr() const { return climatePref == 0 ? "��������" : "Ҹ����"; }
	//���������� ������� ������ ���������
	string getStatus() const {
		if (!isAlive) return "̸���";
		return isSick ? "�����" : "������";
	}
};

//�������� �� �������� ��������, �������� ������� �� ���������� � ���������� ���������� �������
class Enclosure {
private:
	int id;
	int capacity;
	int animalType;
	int climate;
	int dailyCost;
	vector<Animal*> animals;

public:
	//�����������, �����������, ��� ��������, ������, ���������� ��������� ���������� �������
	Enclosure(int i, int cap, int aType, int clim, int cost) :
		id(i), capacity(cap), animalType(aType), climate(clim), dailyCost(cost) {}
	//���������� �������� �� ������� ���� � �������, ��������� �� ��� ��������� � �������� � �������� �� ������
	bool addAnimal(Animal* animal) {
		if (animals.size() >= capacity) return false;
		if (animal->getType() != animalType) return false;
		if (animal->getClimatePref() != climate) return false;

		animals.push_back(animal);
		return true;
	}

	//�������� ��������� �� �������
	void removeAnimal(Animal* animal) {
		animals.erase(remove(animals.begin(), animals.end(), animal), animals.end());
	}

	//������� �������� �� ������ ��������
	void clean() {
		animals.erase(remove_if(animals.begin(), animals.end(),
			[](Animal* a) { return !a->getIsAlive(); }), animals.end());
	}

	int getId() const { return id; }
	int getCapacity() const { return capacity; }
	int getAnimalType() const { return animalType; }
	int getClimate() const { return climate; }
	int getDailyCost() const { return dailyCost; }
	int getAnimalCount() const { return animals.size(); }
	vector<Animal*> getAnimals() const { return animals; }

	string getAnimalTypeStr() const { return animalType == 0 ? "����������" : "�������"; }
	string getClimateStr() const { return climate == 0 ? "��������" : "Ҹ����"; }
};

//������������� ����������� ��������
class Employee {
private:
	string name;
	string position;
	int salary;
	int maxAnimals;

public:
	Employee(string n, string pos) : name(n), position(pos) {
		if (pos == "���������") {
			salary = 5000;
			maxAnimals = 20;
		}
		else if (pos == "�������") {
			salary = 1000;
			maxAnimals = 1;
		}
		else {
			salary = 2000;
			maxAnimals = 2;
		}
	}
	string getName() const { return name; }
	string getPosition() const { return position; }
	int getSalary() const { return salary; }
	int getMaxAnimals() const { return maxAnimals; }
};

//��������� �����������
class Visitor {
private:
	string type;
	int popularityBonus;

public:
	Visitor() {
		int r = Random::range(1, 100);
		if (r <= 1) {
			type = "������������";
			popularityBonus = 10;
		}
		else if (r <= 6) {
			type = "��������";
			popularityBonus = 5;
		}
		else {
			type = "�������";
			popularityBonus = Random::chance(10) ? 2 : 1;
		}
	}

	string getType() const { return type; }
	int getPopularityBonus() const { return popularityBonus; }
};

//���������� ���� ������� �������
class AlienZoo {
private:
	string name;
	int day;
	int food;
	int money;
	int popularity;
	int visitorsToday;
	int totalVisitors;
	int animalsPurchasedToday;

	vector<unique_ptr<Animal>> animals; vector<Enclosure*> enclosures;
	vector<Employee*> employees;
	vector<Animal> marketAnimals;
	JokeCat jokeCat;

	//��������� (��������� ����)
	const int START_MONEY = 50000;
	const int START_FOOD = 100;
	const int START_POPULARITY = 10;
	const int WIN_DAYS = 100;
	const int MAX_MARKET_ANIMALS = 10;

	//������ � ����� ��������
	map<string, tuple<int, int, int, int>> speciesData = {
		{ "���",{ 1, 1, 15000, 20 } },
		{ "����",{ 1, 1, 12000, 18 } },
		{ "�������",{ 1, 0, 10000, 25 } },
		{ "�����",{ 0, 1, 8000, 22 } },
		{ "�����",{ 0, 1, 5000, 18 } },
		{ "�������",{ 0, 0, 3000, 15 } }
	};

//��������� ����������
public:
	AlienZoo(string zooName) : name(zooName), day(0), food(100),
		money(500000), popularity(0),
		visitorsToday(0), totalVisitors(0), animalsPurchasedToday(0) {
		//���������� ���������
		employees.push_back(new Employee("������", "��������"));
		//�������� ������� (id, �����������, ������� ����������, ���, ����)
		enclosures.push_back(new Enclosure(1, 5, 0, 1, 100));
		srand(time(0));
		//���������� ����� ���������
		refreshMarket();
		//����� ��������� ����������
		showStartInfo();
	}

	void showStartInfo() {
		cout << "\n=== ������������� �������� ===" << endl;
		//����������� ��������� ���������� � ��������
		cout << "��������: " << name << endl;
		cout << "��������� �������: " << money << endl;
		cout << "��������� ����� ���: " << food << endl;
		cout << "��������� ������������: " << popularity << endl;
		cout << "��������� ������: #1 (����������, Ҹ���� ������)" << endl;
		cout << "��������: ��" << endl;
		cout << "�������� �������� �� �����: " << marketAnimals.size() << endl;
	}

	//����������� �������� ������� ����
	void run() {
		showStatus();

		while (money >= 0 && day < WIN_DAYS) {
			processDay();
			showStatus();
		}

		if (money < 0) {
			cout << "�� ������������� �� " << day << " ����! ���� ��������." << endl;
		}
		else {
			cout << "�����������! �� ������� ��������� ��������� " << name
				<< " � ������� " << WIN_DAYS << " ����!" << endl;
		}
	}

	//����� �������� ��������� ��������
	void showStatus() {
		cout << "\n=== " << name << " === ���� " << day << " ===" << endl;
		cout << "���: " << food << " | ������: " << money
			<< " | ������������: " << popularity << endl;
		cout << "��������: " << animals.size()
			<< " | ��������: " << enclosures.size()
			<< " | ����������: " << employees.size() << endl;
		cout << "��������� ����������: " << visitorsToday
			<< " | ����� �����������: " << totalVisitors << endl;

		cout << "\n���� ��������:" << endl;
		cout << "1. ���������� ���������" << endl;
		cout << "2. ���������� ���������" << endl;
		cout << "3. ���������� �����������" << endl;
		cout << "4. ���������� ����������" << endl;
		cout << "5. ������� � ���������� ���" << endl;
		cout << "0. �����" << endl;
	}

	//�������� ���������� �������� ����
	void processDay() {
		int choice;
		cout << "\n�������� ��������: ";
		cin >> choice;

		switch (choice) {
		case 1: manageAnimals(); break;
		case 2: managePurchases(); break;
		case 3: manageBuildings(); break;
		case 4: manageEmployees(); break;
		case 5: nextDay(); break;
		case 0: day = WIN_DAYS; break;
		default: cout << "�������� �����!" << endl;
		}
	}

	//��������� ����������� �� ����� ��������
	void refreshMarket(bool force = false) {
		if (!force && day > 0 && !marketAnimals.empty()) return;

		marketAnimals.clear();								//�������� �������� ������ ��������
		int count = Random::range(5, MAX_MARKET_ANIMALS);   //��������� ���������� ���������� ��������

		for (int i = 0; i < count; i++) {
			auto it = speciesData.begin();
			advance(it, Random::range(0, speciesData.size() - 1));
			string species = it->first;

			//���������� ���������� ����
			auto& data = it->second;
			int type = get<0>(data);
			int climate = get<1>(data);
			int price = get<2>(data);
			int maxAge = get<3>(data);

			//��������� ���� � �����
			char gender = Random::chance(50) ? 'M' : 'F'; string name = species + " " + to_string(i + 1);

			//���������� ��������� �� �����
			marketAnimals.emplace_back(name, species, climate, type,
				price, gender, maxAge);
		}
	}

	//���������� ������� ����������� �����
	void showMarket() {
		cout << "\n=== ����� �������� ===" << endl;
		cout << "(����������� ������ ����, ����� �������� �� 1000)\n" << endl;

		for (size_t i = 0; i < marketAnimals.size(); i++) {
			auto& a = marketAnimals[i];
			cout << i + 1 << ". " << a.getName() << " (" << a.getSpecies() << ")" << endl;
			cout << "   ���: " << a.getGender() << " | �������: " << a.getAge() << " ����" << endl;
			cout << "   ���: " << a.getTypeStr() << " | ������: " << a.getClimateStr() << endl;
			cout << "   ����: " << a.getPrice() << " | ����. �������: " << a.getMaxAge() << endl;
			cout << "---------------------------------" << endl;
		}

		if (marketAnimals.empty()) {
			cout << "�� ����� ��� ��������!" << endl;
		}
	}

	//���������� ������� ��������
	void buyAnimal() {
		//�������� ������� �������� �� �����
		if (marketAnimals.empty()) {
			cout << "�� ����� ��� �������� ��� �������!" << endl;
			return;
		}
		//����� 10 ����, �� ����� �������� ���� ���� ��������
		if (day > 10 && animalsPurchasedToday >= 1) {
			cout << "����� 10 ��� ����� �������� ������ 1 �������� � ����!" << endl;
			return;
		}

		//����� �����
		showMarket();
		//���������� ����� ���������
		int choice;
		cout << "�������� ����� ��������� ��� ������� (0 - ������): ";
		cin >> choice;
		//�������� ������������ ������
		if (choice < 1 || choice > marketAnimals.size()) return;
		//������ �� ��������� ��������
		Animal& animal = marketAnimals[choice - 1];
		//�������� �������, ������ �� �� �������
		if (money < animal.getPrice()) {
			cout << "������������ �����!" << endl;
			return;
		}
		//����������� �������
		money -= animal.getPrice();
		animals.push_back(make_unique<Animal>(animal));
		cout << "�������� " << animal.getName() << " �������!" << endl;
		//�������� ��������� � �����
		marketAnimals.erase(marketAnimals.begin() + choice - 1);
		animalsPurchasedToday++;
	}
	
	//���������� ��������
	void breedAnimals() {
		if (animals.size() < 2) {
			cout << "����� ��� ������� 2 �������� ��� �����������!" << endl;
			return;
		}
		//������ �������� � ������ �� �����
		showAnimals();
		cout << "�������� ����� ������� ���������: ";
		int a1;
		cin >> a1;
		cout << "�������� ����� ������� ���������: ";
		int a2;
		cin >> a2;
		//�������� ������������ ������
		bool invalidChoice = (a1 < 1) ||
			(a1 > static_cast<int>(animals.size())) ||
			(a2 < 1) ||
			(a2 > static_cast<int>(animals.size())) ||
			(a1 == a2);

		if (invalidChoice) {
			cout << "�������� ����� ��������!" << endl;
			return;
		}

		try {
			//������� ������� �������� ����� ������������� ��������
			Animal baby = *animals[a1 - 1] + *animals[a2 - 1];
			//����� �������, ��� ������� ��������
			Enclosure* parentsEnclosure = nullptr;
			for (auto enc : enclosures) {
				auto& encAnimals = enc->getAnimals();
				if (find(encAnimals.begin(), encAnimals.end(), animals[a1 - 1].get()) != encAnimals.end() ||
					find(encAnimals.begin(), encAnimals.end(), animals[a2 - 1].get()) != encAnimals.end()) {
					parentsEnclosure = enc;
					break;
				}
			}
			//�������� ���� � �������
			if (!parentsEnclosure || parentsEnclosure->getAnimalCount() >= parentsEnclosure->getCapacity()) {
				cout << "��� ����� � ������� ��������� ��� ��������!" << endl;
				return;
			}
			//���������� �������� � ������� � ������
			animals.push_back(make_unique<Animal>(baby));
			parentsEnclosure->addAnimal(animals.back().get());
			cout << "������� ����� �������: " << baby.getName() << endl;

		}
		catch (const exception& e) {
			cout << "������ �����������: " << e.what() << endl;
		}
	}

	void showAnimals() {
		if (animals.empty()) {
			cout << "� �������� ��� ��������!" << endl;
			return;
		}

		cout << "\n������ ��������:" << endl;
		for (size_t i = 0; i < animals.size(); ++i) {
			Animal* a = animals[i].get();
			cout << i + 1 << ". " << a->getName() << " (" << a->getSpecies() << ")" << endl;
			cout << "   ���: " << a->getGender() << " | �������: " << a->getAge() << "/" << a->getMaxAge() << " ����" << endl;
			cout << "   ���: " << a->getTypeStr() << " | ������: " << a->getClimateStr() << endl;
			cout << "   ���: " << a->getWeight() << " | ����: " << a->getPrice() << endl;
			cout << "   ������: " << a->getStatus() << " | ��������: " << a->getParentsInfo() << endl;
			cout << "---------------------------------" << endl;
		}
	}

	//���������� �������������� ���������
	void renameAnimal() {
		if (animals.empty()) {
			cout << "��� �������� ��� ��������������!" << endl;
			return;
		}

		showAnimals();
		int index;
		cout << "�������� ����� ��������� ��� �������������� (0 - ������): ";
		cin >> index;

		if (index < 1 || index > animals.size()) return;

		string newName;
		cout << "������� ����� ���: ";
		cin.ignore();
		getline(cin, newName);

		animals[index - 1]->rename(newName);
		cout << "�������� �������������!" << endl;
	}

	 //����������� ��������� ����� ���������
	void moveAnimal() {
		if (animals.empty()) {
			cout << "��� �������� ��� �����������!" << endl;
			return;
		}

		//����� ������ ��������
		showAnimals();
		int animalIndex;
		cout << "�������� ����� ��������� (0 - ������): ";
		cin >> animalIndex;

		if (animalIndex < 1 || animalIndex > animals.size()) return;

		//�������� ��������� �� ��������� ��������
		Animal* animal = animals[animalIndex - 1].get();

		//����� ��������� ��������
		cout << "\n��������� �������:" << endl;
		for (size_t i = 0; i < enclosures.size(); ++i) {
			Enclosure* enc = enclosures[i];
			cout << i + 1 << ". ������ #" << enc->getId() << " (" << enc->getAnimalTypeStr()
				<< ", " << enc->getClimateStr() << ")" << endl;
			cout << "   �����������: " << enc->getAnimalCount() << "/" << enc->getCapacity() << endl;
		}

		int encIndex;
		cout << "�������� ����� ������� (0 - �������� ��� �������): ";
		cin >> encIndex;

		if (encIndex == 0) {
			for (auto enc : enclosures) {
				enc->removeAnimal(animal);
			}
			cout << "�������� ������ ��� �������" << endl;
			return;
		}

		//�������� ������������ ������
		if (encIndex < 1 || encIndex > enclosures.size()) return;

		Enclosure* enc = enclosures[encIndex - 1];

		//�������� �������� �� ���� ��������
		for (auto e : enclosures) {
			e->removeAnimal(animal);
		}

		if (enc->addAnimal(animal)) {
			cout << "�������� ���������� � ������ #" << enc->getId() << endl;
		}
		else {
			cout << "�� ������� ��������� �������� � ���� ������!" << endl;
			cout << "��������� ��� ���������, ������ � ����������� �������" << endl;
		}
	}

	//���� ��� ���������� ���������
	void manageAnimals() {
		int choice;
		do {
			cout << "\n���������� ���������:" << endl;
			cout << "1. ������ ��������" << endl;
			cout << "2. ������� ��������" << endl;
			cout << "3. ���������� ������ ��������" << endl;
			cout << "4. ����������� �������� � ������" << endl;
			cout << "5. ���������� ��������" << endl;
			cout << "6. ������������� ��������" << endl;
			cout << "0. �����" << endl;
			cout << "�������� ��������: ";
			cin >> choice;

			//��������� ������ ������������
			switch (choice) {
			case 1: buyAnimal(); break;
			case 2: sellAnimal(); break;
			case 3: showAnimals(); break;
			case 4: moveAnimal(); break;
			case 5: breedAnimals(); break;
			case 6: renameAnimal(); break;
			}
		} while (choice != 0);
	}

	//������� ���������
	void sellAnimal() {
		//�������� ������� �������� ��� �������
		if (animals.empty()) {
			cout << "��� �������� ��� �������!" << endl;
			return;
		}

		showAnimals();
		int index;
		cout << "�������� ����� ��������� ��� ������� (0 - ������): ";
		cin >> index;

		if (index < 1 || index > animals.size()) return;

		Animal* animal = animals[index - 1].get();

		//���������� ����� (50% �� �������� ����)
		money += animal->getPrice() / 2;
		cout << "�������� " << animal->getName() << " ������� �� " << animal->getPrice() / 2 << endl;

		//�������� ��������� �� �������
		for (auto enc : enclosures) {
			enc->removeAnimal(animal);
		}
		//�������� ��������� �� ��������
		animals.erase(animals.begin() + index - 1);
	}

	//���� ���������� ���������
	void managePurchases() {
		int choice;
		do {
			cout << "\n���������� ���������:" << endl;
			cout << "1. ������ ��� (100 ��. �� 1000)" << endl;
			cout << "2. ������ ������� (+5 ������������ �� 2000)" << endl;
			cout << "3. �������� ����� �������� (1000)" << endl;
			cout << "0. �����" << endl;
			cout << "�������� ��������: ";
			cin >> choice;

			//��������� ������ ������������
			switch (choice) {
			case 1:
				if (money >= 1000) {
					money -= 1000;
					food += 100;
					cout << "������� 100 ���!" << endl;
				}
				else {
					cout << "������������ �����!" << endl;
				}
				break;
			case 2:
				if (money >= 2000) {
					money -= 2000;
					popularity += 5;
					cout << "������������ ��������� �� 5!" << endl;
				}
				else {
					cout << "������������ �����!" << endl;
				}
				break;
			case 3:
				if (money >= 1000) {
					money -= 1000;
					refreshMarket(true);
					cout << "����� �������� ��������!" << endl;
					showMarket();
				}
				else {
					cout << "������������ �����!" << endl;
				}
				break;
			}
		} while (choice != 0);
	}

	//���� ���������� ���������
	void manageBuildings() {
		int choice;
		do {
			cout << "\n���������� �����������:" << endl;
			cout << "1. ������ ������ ��� ���������� (�������� ������) - 5000" << endl;
			cout << "2. ������ ������ ��� ���������� (����� ������) - 6000" << endl;
			cout << "3. ������ ������ ��� �������� (�������� ������) - 8000" << endl;
			cout << "4. ������ ������ ��� �������� (����� ������) - 10000" << endl;
			cout << "5. ���������� ������ ��������" << endl;
			cout << "0. �����" << endl;
			cout << "�������� ��������: ";
			cin >> choice;

			//��������� ������ �������
			int price = 0;
			int type = 0;
			int climate = 0;
			int capacity = 5;

			//��������� ���������� �� ������
			switch (choice) {
			case 1: price = 5000; type = 0; climate = 0; break;
			case 2: price = 6000; type = 0; climate = 1; break;
			case 3: price = 8000; type = 1; climate = 0; break;
			case 4: price = 10000; type = 1; climate = 1; break;
			case 5: showEnclosures(); continue;
			case 0: continue;
			default: cout << "�������� �����!" << endl; continue;
			}

			//������� �������
			if (choice >= 1 && choice <= 4) {
				if (money >= price) {
					money -= price;
					int newId = enclosures.empty() ? 1 : enclosures.back()->getId() + 1;
					enclosures.push_back(new Enclosure(newId, capacity, type, climate, price / 10));
					cout << "����� ������ ������!" << endl;
				}
				else {
					cout << "������������ �����!" << endl;
				}
			}
		} while (choice != 0);
	}

	//����������� ���������� � ��������
	void showEnclosures() {
		if (enclosures.empty()) {
			cout << "��� ��������!" << endl;
			return;
		}

		cout << "\n������ ��������:" << endl;
		//������� ���� ��������
		for (auto enc : enclosures) {
			cout << "������ #" << enc->getId() << " (" << enc->getAnimalTypeStr()
				<< ", " << enc->getClimateStr() << ")" << endl;
			cout << "�����������: " << enc->getAnimalCount() << "/" << enc->getCapacity()
				<< " | �������: " << enc->getDailyCost() << " � ����" << endl;

			//������ �������� � ������� (���� ����)
			if (enc->getAnimalCount() > 0) {
				cout << "�������� � �������:" << endl;
				for (auto a : enc->getAnimals()) {
					cout << "- " << a->getName() << " (" << a->getStatus() << ")" << endl;
				}
			}
			cout << endl;
		}
	}

	//���� ���������� ����������
	void manageEmployees() {
		int choice;
		do {
			cout << "\n���������� ����������:" << endl;
			cout << "1. ������ ���������" << endl;
			cout << "2. ������� ���������" << endl;
			cout << "3. ���������� ������ ����������" << endl;
			cout << "0. �����" << endl;
			cout << "�������� ��������: ";
			cin >> choice;

			switch (choice) {
			case 1: hireEmployee(); break;
			case 2: fireEmployee(); break;
			case 3: showEmployees(); break;
			}
		} while (choice != 0);
	}

	//��� ������ ����������
	void hireEmployee() {
		string name;
		cout << "������� ��� ���������: ";
		cin >> name;

		//����� ���������
		int type;
		cout << "�������� ���������:" << endl;
		cout << "1. ��������� (5000 � ����)" << endl;
		cout << "2. ������� (1000 � ����)" << endl;
		cout << "3. ���������� (2000 � ����)" << endl;
		cout << "0. ������" << endl;
		cout << "�������� ���: ";
		cin >> type;

		if (type < 1 || type > 3) return;

		//����������� ���������
		string position;
		switch (type) {
		case 1: position = "���������"; break;
		case 2: position = "�������"; break;
		case 3: position = "����������"; break;
		}

		//���������� ������ ����������
		employees.push_back(new Employee(name, position));
		cout << "����� �������� �����!" << endl;
	}

	//���������� ����������
	void fireEmployee() {
		//������ �� �������� ���������
		if (employees.size() <= 1) {
			cout << "������ ������� ������������� ��������� (���������)!" << endl;
			return;
		}

		showEmployees();

		int index;
		cout << "�������� ����� ��������� ��� ���������� (0 - ������): ";
		cin >> index;

		if (index < 1 || index >= employees.size()) return;

		//������� ����������
		cout << "�������� " << employees[index]->getName() << " ������!" << endl;
		delete employees[index];
		employees.erase(employees.begin() + index);
	}

	//������ ��������, ������� ��� ������
	void showEmployees() {
		cout << "\n������ ����������:" << endl;
		for (size_t i = 0; i < employees.size(); ++i) {
			Employee* emp = employees[i];
			cout << i + 1 << ". " << emp->getName() << " - " << emp->getPosition()
				<< " (��������: " << emp->getSalary() << " � ����)" << endl;
		}
	}

	//������ ������ ���
	void nextDay()
	{
		//���������� ���������
		day++;
		animalsPurchasedToday = 0;
		cout << "\n=== ��������� ���� " << day << " ===" << endl;

		//��������� ������� � ������ ����
		if (jokeCat.tellJoke()) {
			popularity += 100;
		}

		//�������� �������� � �������
		for (auto& a : animals) {
			a->grow();
			if (a->getIsAlive() && Random::chance(10)) {
				a->getSick();
			}
		}

		//������� �������� ����������� (���� �� ����)
		bool hasVet = any_of(employees.begin(), employees.end(),
			[](Employee* e) { return e->getPosition() == "���������"; });

		if (hasVet) {
			for (auto& a : animals) {
				if (a->getIsSick() && money >= 5000) {
					money -= 5000;
					a->heal();
					cout << a->getName() << " ������� ����������� �� 5000" << endl;
				}
			}
		}

		//��������� �������� ������������ (���� �� ����)
		bool hasFeeder = any_of(employees.begin(), employees.end(), [](Employee* e) { return e->getPosition() == "����������"; });

		if (hasFeeder && food >= animals.size()) {
			food -= animals.size();
			cout << "�������� ���������� (-" << animals.size() << " ���)" << endl;
		}
		else if (hasFeeder) {
			cout << "������������ ��� ��� ���� ��������!" << endl;
			for (auto& a : animals) {
				if (Random::chance(50)) {
					a->die();
					cout << a->getName() << " ���� �� ������!" << endl;
				}
			}
		}
		else {
			cout << "������ ������� ��������! ��� ��������!" << endl;
			for (auto& a : animals) {
				if (Random::chance(50)) {
					a->die();
					cout << a->getName() << " ���� �� ������!" << endl;
				}
			}
		}

		//������ �������� ��������� (���� �� ����)
		int cleaners = count_if(employees.begin(), employees.end(),
			[](Employee* e) { return e->getPosition() == "�������"; });

		if (cleaners > 0) {
			int cleaned = min(cleaners, (int)enclosures.size());
			for (int i = 0; i < cleaned; ++i) {
				enclosures[i]->clean();
			}
			cout << cleaned << " �������� ������" << endl;
		}
		else {
			cout << "������ ������� �������!" << endl;
		}

		//������ ���������� ��������
		int dailyCost = 0;
		for (auto enc : enclosures) {
			dailyCost += enc->getDailyCost();
		}
		for (auto emp : employees) {
			dailyCost += emp->getSalary();
		}
		money -= dailyCost;
		cout << "������� �� ����������: -" << dailyCost << " �����" << endl;

		//������ ����������� � �������
		visitorsToday = 2 * popularity;
		vector<Visitor> visitors;
		int totalBonus = 0;
		for (int i = 0; i < visitorsToday; ++i) {
			Visitor v;
			visitors.push_back(v);
			totalBonus += v.getPopularityBonus();
		}

		//������� ������� �����
		if (!visitors.empty()) {
			popularity += totalBonus / visitors.size();
		}

		//��������� ������������
		popularity += Random::range(-popularity / 10, popularity / 10);
		if (popularity < 5) popularity = 5;

		//����� �� �����������
		int income = visitorsToday * animals.size();
		money += income;
		totalVisitors += visitorsToday;

		cout << "���������� �������: " << visitorsToday << " (+" << income << " �����)" << endl;
		cout << "����� ������������: " << popularity << endl;

		//�������� ������� ��������
		animals.erase(remove_if(animals.begin(), animals.end(),
			[](const unique_ptr<Animal>& a) { return !a->getIsAlive(); }),
			animals.end()

		);
	
	}
};

//������� ������� ���������
int main() {
	//��������� ������ ��� ����������� ����������� ���������
	setlocale(LC_ALL, "rus");
	//������ �������� �������� � ������������
	string name;
	cout << "������� �������� ������ ������������� ��������: ";
	getline(cin, name);
	//�������� ���������� ��������
	AlienZoo zoo(name);
	//������ ��������� �������� �����
	zoo.run();
	//���������� ���������
	return 0;
}
