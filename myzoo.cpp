#include <iostream>		//Библиотека ввода/вывода данных
#include <vector>		//Библиотека динамический массив
#include <string>		//Библиотека работа со строками
#include <ctime>		//Библиотека для случайных событий
#include <cstdlib>		//Библиотека для случайных событий
#include <algorithm>	//Библиотека поиск и сортировка
#include <map>			//Библиотека ассоциативный контейнер
#include <memory>		//Библиотека умные указатели
#include <stdexcept>	//Библиотека обработка ошибок

using namespace std;

//Генерация случайных чисел
class Random {
public:
	static int range(int min, int max) {
		return rand() % (max - min + 1) + min;
	}
	static bool chance(int percent) {
		return rand() % 100 < percent;
	}
};

//Реализация события "Котик-анекдотер"
class JokeCat {
private:
	vector<string> jokes = {
		"Идёт охотник по лесу. Видит - берлога. Ну, снял ружьё, пальнул пару раз, ждёт.\n"
		"Тут ему неожиданно по плечу медведь стучит:\n"
		"- Выбирай, либо я тебя съем, либо поимею.\n"
		"Ну, мужик, естественно, выбрал второе. Отпялил его медведь. На следующий день охотник конкретно вооружился: гранат набрал, автомат, патронов дофига. Нашёл берлогу, минут десять стоял расстреливал.\n"
		"Устал, стоит довольный. Тут опять сзади медведь по плечу стучит:\n"
		"- Выбирай, либо я тебя съем, либо поимею.\n"
		"Опять выбрал мужик второе. На третий день взял охотник полтонны тротила, прикатал кое-как к берлоге.\n"
		"Рвануло так, что пол леса разнесло. Стоит мужик довольный, думает уж точно звездец медведю настал. Тут снова медведь по плечу стучит и нахмурившись спрашивает:\n"
		"- Мужик, ты сюда точно охотиться приходишь?",

		"- Мужик, а чё это у тебя два уха перевязаны?\n"
		"- Да я бельё гладил и тут телефон зазвонил.\n"
		"- Так и?\n"
		"- И вместо трубки в утюг алло сказал...\n"
		"- Аа..а со вторым ухом что?\n"
		"- Так, это..скорую вызывал.",

		"Встречаются два медведя в лесу. Один другому:\n"
		"- Ты слышал, вчера охотник одного нашего так наколол?\n"
		"- Нет, а что?\n"
		"- Да предложил ему выбор: либо он его съест, либо... ну ты понял.\n"
		"- И что?\n"
		"- Ну медведь выбрал второе...\n"
		"- Ну и?\n"
		"- Да вроде ничего, только теперь этот охотник каждый день к берлоге приходит!"
	};

public:
	bool tellJoke() {
		// 5% шанс, что котик появится
		if (Random::chance(5)) { 
			cout << "=== В зоопарк забежал оранжевый котик и говорит:\n";
			//реализуется выбор случайного анекдота из списка
			cout << "\033[1;33m" << jokes[Random::range(0, jokes.size() - 1)] << "\033[0m\n\n"; 
			return true;
		}
		return false;
	}
};

//Моделирование животных
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
	//Инициализирует параметры, к примеру: имя, вид, климат, цена, пол, максимальный возраст
	Animal(string n, string sp, int cp, int t, int p, char g, int mA,
		Animal* p1 = nullptr, Animal* p2 = nullptr, bool born = false) :
		name(n), species(sp), age(0), weight(Random::range(10, 100)),
		climatePref(cp), type(t), price(p), isSick(false), isAlive(true),
		gender(g), maxAge(mA), parent1(p1), parent2(p2), bornInZoo(born) {}

	//Увелечение возраста, смена веса и проверка смерти от старости
	void grow() {
		age++;
		weight += Random::range(-2, 5);
		if (weight < 5) die();

		if (age > maxAge && Random::chance(age)) {
			die();
		}
	}

	//10%, что животное заболеет
	void getSick() {
		if (Random::chance(10)) isSick = true;
	}

	//Метод лечения и смерти животного
	void heal() { isSick = false; }
	void die() { isAlive = false; }
	void rename(const string& newName) { name = newName; }

	//Реализация размножения животных
	Animal operator+(Animal& other) {
		if (species != other.species) {
			throw runtime_error("Нельзя скрещивать разные виды животных");
		}
		if (gender == other.gender) {
			throw runtime_error("Нельзя скрещивать животных одного пола");
		}
		if (age < 5 || other.age < 5) {
			throw runtime_error("Животные слишком молодые для размножения");
		}

		string babyName = "Детеныш " + species;
		char babyGender = Random::chance(50) ? 'M' : 'F';
		int babyPrice = (price + other.price) / 2;

		return Animal(babyName, species, climatePref, type, babyPrice, babyGender, maxAge, this, &other, true);
	}

	//Информация о животных
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
	//Возвращает информацию о родителях животного
	string getParentsInfo() const {
		if (!bornInZoo) return "Куплен в магазине";
		string p1 = parent1 ? parent1->getName() : "Неизвестен";
		string p2 = parent2 ? parent2->getName() : "Неизвестен";
		return p1 + " и " + p2;
	}
	//Возвращает текстовое представление типа питания
	string getTypeStr() const { return type == 0 ? "Травоядное" : "Хищник"; }
	//Возвращает предпочитаемый климат в текстовом виде
	string getClimateStr() const { return climatePref == 0 ? "Холодный" : "Тёплый"; }
	//Определяет текущий статус животного
	string getStatus() const {
		if (!isAlive) return "Мёртв";
		return isSick ? "Болен" : "Здоров";
	}
};

//Отвечает за хранение животных, проверку условий их содержания и управление состоянием вольера
class Enclosure {
private:
	int id;
	int capacity;
	int animalType;
	int climate;
	int dailyCost;
	vector<Animal*> animals;

public:
	//Индификатор, вместимость, тип животных, климат, ежедневная стоимость содержания вольера
	Enclosure(int i, int cap, int aType, int clim, int cost) :
		id(i), capacity(cap), animalType(aType), climate(clim), dailyCost(cost) {}
	//Происходит проверка на наличие мест в вольере, совпадает ли тип животного с вольером и подходит ли климат
	bool addAnimal(Animal* animal) {
		if (animals.size() >= capacity) return false;
		if (animal->getType() != animalType) return false;
		if (animal->getClimatePref() != climate) return false;

		animals.push_back(animal);
		return true;
	}

	//Удаление животного из вольера
	void removeAnimal(Animal* animal) {
		animals.erase(remove(animals.begin(), animals.end(), animal), animals.end());
	}

	//Очистка вольеров от мёртвых животных
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

	string getAnimalTypeStr() const { return animalType == 0 ? "Травоядные" : "Хищники"; }
	string getClimateStr() const { return climate == 0 ? "Холодный" : "Тёплый"; }
};

//Моделирование сотрудников зоопарка
class Employee {
private:
	string name;
	string position;
	int salary;
	int maxAnimals;

public:
	Employee(string n, string pos) : name(n), position(pos) {
		if (pos == "Ветеринар") {
			salary = 5000;
			maxAnimals = 20;
		}
		else if (pos == "Уборщик") {
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

//Генерация посетителей
class Visitor {
private:
	string type;
	int popularityBonus;

public:
	Visitor() {
		int r = Random::range(1, 100);
		if (r <= 1) {
			type = "Знаменитость";
			popularityBonus = 10;
		}
		else if (r <= 6) {
			type = "Фотограф";
			popularityBonus = 5;
		}
		else {
			type = "Обычный";
			popularityBonus = Random::chance(10) ? 2 : 1;
		}
	}

	string getType() const { return type; }
	int getPopularityBonus() const { return popularityBonus; }
};

//Управление всей игровой логикой
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

	//Константы (настройки игры)
	const int START_MONEY = 50000;
	const int START_FOOD = 100;
	const int START_POPULARITY = 10;
	const int WIN_DAYS = 100;
	const int MAX_MARKET_ANIMALS = 10;

	//Данные о видах животных
	map<string, tuple<int, int, int, int>> speciesData = {
		{ "Лев",{ 1, 1, 15000, 20 } },
		{ "Тигр",{ 1, 1, 12000, 18 } },
		{ "Медведь",{ 1, 0, 10000, 25 } },
		{ "Жираф",{ 0, 1, 8000, 22 } },
		{ "Зебра",{ 0, 1, 5000, 18 } },
		{ "Пингвин",{ 0, 0, 3000, 15 } }
	};

//Стартовая информация
public:
	AlienZoo(string zooName) : name(zooName), day(0), food(100),
		money(500000), popularity(0),
		visitorsToday(0), totalVisitors(0), animalsPurchasedToday(0) {
		//Добавление директора
		employees.push_back(new Employee("Кэтрик", "Директор"));
		//Создание вольера (id, вместимость, текущее количество, тип, цена)
		enclosures.push_back(new Enclosure(1, 5, 0, 1, 100));
		srand(time(0));
		//Заполнение рынка животными
		refreshMarket();
		//Вывод стартовой информации
		showStartInfo();
	}

	void showStartInfo() {
		cout << "\n=== ИНИЦИАЛИЗАЦИЯ ЗООПАРКА ===" << endl;
		//Отображение стартовой информации о зоопарке
		cout << "Название: " << name << endl;
		cout << "Стартовый капитал: " << money << endl;
		cout << "Стартовый запас еды: " << food << endl;
		cout << "Начальная популярность: " << popularity << endl;
		cout << "Стартовый вольер: #1 (Травоядные, Тёплый климат)" << endl;
		cout << "Директор: Вы" << endl;
		cout << "Доступно животных на рынке: " << marketAnimals.size() << endl;
	}

	//Запускается основной игровой цикл
	void run() {
		showStatus();

		while (money >= 0 && day < WIN_DAYS) {
			processDay();
			showStatus();
		}

		if (money < 0) {
			cout << "Вы обанкротились на " << day << " день! Игра окончена." << endl;
		}
		else {
			cout << "Поздравляем! Вы успешно управляли зоопарком " << name
				<< " в течение " << WIN_DAYS << " дней!" << endl;
		}
	}

	//Показ текущего состояния зоопарка
	void showStatus() {
		cout << "\n=== " << name << " === День " << day << " ===" << endl;
		cout << "Еда: " << food << " | Деньги: " << money
			<< " | Популярность: " << popularity << endl;
		cout << "Животных: " << animals.size()
			<< " | Вольеров: " << enclosures.size()
			<< " | Работников: " << employees.size() << endl;
		cout << "Вчерашние посетители: " << visitorsToday
			<< " | Всего посетителей: " << totalVisitors << endl;

		cout << "\nМеню действий:" << endl;
		cout << "1. Управление животными" << endl;
		cout << "2. Управление закупками" << endl;
		cout << "3. Управление постройками" << endl;
		cout << "4. Управление персоналом" << endl;
		cout << "5. Перейти к следующему дню" << endl;
		cout << "0. Выход" << endl;
	}

	//Основной обработчик игрового меню
	void processDay() {
		int choice;
		cout << "\nВыберите действие: ";
		cin >> choice;

		switch (choice) {
		case 1: manageAnimals(); break;
		case 2: managePurchases(); break;
		case 3: manageBuildings(); break;
		case 4: manageEmployees(); break;
		case 5: nextDay(); break;
		case 0: day = WIN_DAYS; break;
		default: cout << "Неверный выбор!" << endl;
		}
	}

	//Обновляет ассортимент на рынке животных
	void refreshMarket(bool force = false) {
		if (!force && day > 0 && !marketAnimals.empty()) return;

		marketAnimals.clear();								//очищение текущего списка животных
		int count = Random::range(5, MAX_MARKET_ANIMALS);   //генерация случайного количества животных

		for (int i = 0; i < count; i++) {
			auto it = speciesData.begin();
			advance(it, Random::range(0, speciesData.size() - 1));
			string species = it->first;

			//Извлечения параметров вида
			auto& data = it->second;
			int type = get<0>(data);
			int climate = get<1>(data);
			int price = get<2>(data);
			int maxAge = get<3>(data);

			//Генерация пола и имени
			char gender = Random::chance(50) ? 'M' : 'F'; string name = species + " " + to_string(i + 1);

			//Добавления животного на рынок
			marketAnimals.emplace_back(name, species, climate, type,
				price, gender, maxAge);
		}
	}

	//Отображает текущий ассортимент рынка
	void showMarket() {
		cout << "\n=== РЫНОК ЖИВОТНЫХ ===" << endl;
		cout << "(Обновляется каждый день, можно обновить за 1000)\n" << endl;

		for (size_t i = 0; i < marketAnimals.size(); i++) {
			auto& a = marketAnimals[i];
			cout << i + 1 << ". " << a.getName() << " (" << a.getSpecies() << ")" << endl;
			cout << "   Пол: " << a.getGender() << " | Возраст: " << a.getAge() << " дней" << endl;
			cout << "   Тип: " << a.getTypeStr() << " | Климат: " << a.getClimateStr() << endl;
			cout << "   Цена: " << a.getPrice() << " | Макс. возраст: " << a.getMaxAge() << endl;
			cout << "---------------------------------" << endl;
		}

		if (marketAnimals.empty()) {
			cout << "На рынке нет животных!" << endl;
		}
	}

	//Реализация покупки животных
	void buyAnimal() {
		//Проверка наличия животных на рынке
		if (marketAnimals.empty()) {
			cout << "На рынке нет животных для покупки!" << endl;
			return;
		}
		//После 10 дней, мы можем покупать лишь одно животное
		if (day > 10 && animalsPurchasedToday >= 1) {
			cout << "После 10 дня можно покупать только 1 животное в день!" << endl;
			return;
		}

		//Показ рынка
		showMarket();
		//Происходит выбор животного
		int choice;
		cout << "Выберите номер животного для покупки (0 - отмена): ";
		cin >> choice;
		//Проверка корректности выбора
		if (choice < 1 || choice > marketAnimals.size()) return;
		//Ссылка на выбранное животное
		Animal& animal = marketAnimals[choice - 1];
		//Проверка баланса, хватит ли на покупку
		if (money < animal.getPrice()) {
			cout << "Недостаточно денег!" << endl;
			return;
		}
		//Совершается покупка
		money -= animal.getPrice();
		animals.push_back(make_unique<Animal>(animal));
		cout << "Животное " << animal.getName() << " куплено!" << endl;
		//Удаление животного с рынка
		marketAnimals.erase(marketAnimals.begin() + choice - 1);
		animalsPurchasedToday++;
	}
	
	//Разведение животных
	void breedAnimals() {
		if (animals.size() < 2) {
			cout << "Нужно как минимум 2 животных для размножения!" << endl;
			return;
		}
		//Список животных и запрос на выбор
		showAnimals();
		cout << "Выберите номер первого животного: ";
		int a1;
		cin >> a1;
		cout << "Выберите номер второго животного: ";
		int a2;
		cin >> a2;
		//Проверка корректности выбора
		bool invalidChoice = (a1 < 1) ||
			(a1 > static_cast<int>(animals.size())) ||
			(a2 < 1) ||
			(a2 > static_cast<int>(animals.size())) ||
			(a1 == a2);

		if (invalidChoice) {
			cout << "Неверный выбор животных!" << endl;
			return;
		}

		try {
			//Попытка создать детеныша через перегруженный оператор
			Animal baby = *animals[a1 - 1] + *animals[a2 - 1];
			//Поиск вольера, где обитают родители
			Enclosure* parentsEnclosure = nullptr;
			for (auto enc : enclosures) {
				auto& encAnimals = enc->getAnimals();
				if (find(encAnimals.begin(), encAnimals.end(), animals[a1 - 1].get()) != encAnimals.end() ||
					find(encAnimals.begin(), encAnimals.end(), animals[a2 - 1].get()) != encAnimals.end()) {
					parentsEnclosure = enc;
					break;
				}
			}
			//Проверка мест в вольере
			if (!parentsEnclosure || parentsEnclosure->getAnimalCount() >= parentsEnclosure->getCapacity()) {
				cout << "Нет места в вольере родителей для детеныша!" << endl;
				return;
			}
			//Добавление детеныша в зоопарк и вольер
			animals.push_back(make_unique<Animal>(baby));
			parentsEnclosure->addAnimal(animals.back().get());
			cout << "Родился новый детеныш: " << baby.getName() << endl;

		}
		catch (const exception& e) {
			cout << "Ошибка размножения: " << e.what() << endl;
		}
	}

	void showAnimals() {
		if (animals.empty()) {
			cout << "В зоопарке нет животных!" << endl;
			return;
		}

		cout << "\nСписок животных:" << endl;
		for (size_t i = 0; i < animals.size(); ++i) {
			Animal* a = animals[i].get();
			cout << i + 1 << ". " << a->getName() << " (" << a->getSpecies() << ")" << endl;
			cout << "   Пол: " << a->getGender() << " | Возраст: " << a->getAge() << "/" << a->getMaxAge() << " дней" << endl;
			cout << "   Тип: " << a->getTypeStr() << " | Климат: " << a->getClimateStr() << endl;
			cout << "   Вес: " << a->getWeight() << " | Цена: " << a->getPrice() << endl;
			cout << "   Статус: " << a->getStatus() << " | Родители: " << a->getParentsInfo() << endl;
			cout << "---------------------------------" << endl;
		}
	}

	//Реализация переименования животного
	void renameAnimal() {
		if (animals.empty()) {
			cout << "Нет животных для переименования!" << endl;
			return;
		}

		showAnimals();
		int index;
		cout << "Выберите номер животного для переименования (0 - отмена): ";
		cin >> index;

		if (index < 1 || index > animals.size()) return;

		string newName;
		cout << "Введите новое имя: ";
		cin.ignore();
		getline(cin, newName);

		animals[index - 1]->rename(newName);
		cout << "Животное переименовано!" << endl;
	}

	 //Перемещение животного между вольерами
	void moveAnimal() {
		if (animals.empty()) {
			cout << "Нет животных для перемещения!" << endl;
			return;
		}

		//Показ списка животных
		showAnimals();
		int animalIndex;
		cout << "Выберите номер животного (0 - отмена): ";
		cin >> animalIndex;

		if (animalIndex < 1 || animalIndex > animals.size()) return;

		//Получаем указатель на выбранное животное
		Animal* animal = animals[animalIndex - 1].get();

		//Показ доступных вольеров
		cout << "\nДоступные вольеры:" << endl;
		for (size_t i = 0; i < enclosures.size(); ++i) {
			Enclosure* enc = enclosures[i];
			cout << i + 1 << ". Вольер #" << enc->getId() << " (" << enc->getAnimalTypeStr()
				<< ", " << enc->getClimateStr() << ")" << endl;
			cout << "   Вместимость: " << enc->getAnimalCount() << "/" << enc->getCapacity() << endl;
		}

		int encIndex;
		cout << "Выберите номер вольера (0 - оставить без вольера): ";
		cin >> encIndex;

		if (encIndex == 0) {
			for (auto enc : enclosures) {
				enc->removeAnimal(animal);
			}
			cout << "Животное теперь без вольера" << endl;
			return;
		}

		//Проверка корректности выбора
		if (encIndex < 1 || encIndex > enclosures.size()) return;

		Enclosure* enc = enclosures[encIndex - 1];

		//Удаление животных из всех вольеров
		for (auto e : enclosures) {
			e->removeAnimal(animal);
		}

		if (enc->addAnimal(animal)) {
			cout << "Животное перемещено в вольер #" << enc->getId() << endl;
		}
		else {
			cout << "Не удалось поместить животное в этот вольер!" << endl;
			cout << "Проверьте тип животного, климат и вместимость вольера" << endl;
		}
	}

	//Меню для управления животными
	void manageAnimals() {
		int choice;
		do {
			cout << "\nУправление животными:" << endl;
			cout << "1. Купить животное" << endl;
			cout << "2. Продать животное" << endl;
			cout << "3. Посмотреть список животных" << endl;
			cout << "4. Переместить животное в вольер" << endl;
			cout << "5. Размножить животных" << endl;
			cout << "6. Переименовать животное" << endl;
			cout << "0. Назад" << endl;
			cout << "Выберите действие: ";
			cin >> choice;

			//Обработка выбора пользователя
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

	//Продажа животного
	void sellAnimal() {
		//Проверка наличия животных для продажи
		if (animals.empty()) {
			cout << "Нет животных для продажи!" << endl;
			return;
		}

		showAnimals();
		int index;
		cout << "Выберите номер животного для продажи (0 - отмена): ";
		cin >> index;

		if (index < 1 || index > animals.size()) return;

		Animal* animal = animals[index - 1].get();

		//Начисление денег (50% от исходной цены)
		money += animal->getPrice() / 2;
		cout << "Животное " << animal->getName() << " продано за " << animal->getPrice() / 2 << endl;

		//Удаление животного из вольера
		for (auto enc : enclosures) {
			enc->removeAnimal(animal);
		}
		//Удаление животного из зоопарка
		animals.erase(animals.begin() + index - 1);
	}

	//Меню управления закупками
	void managePurchases() {
		int choice;
		do {
			cout << "\nУправление закупками:" << endl;
			cout << "1. Купить еду (100 ед. за 1000)" << endl;
			cout << "2. Купить рекламу (+5 популярности за 2000)" << endl;
			cout << "3. Обновить рынок животных (1000)" << endl;
			cout << "0. Назад" << endl;
			cout << "Выберите действие: ";
			cin >> choice;

			//Обработка выбора пользователя
			switch (choice) {
			case 1:
				if (money >= 1000) {
					money -= 1000;
					food += 100;
					cout << "Куплено 100 еды!" << endl;
				}
				else {
					cout << "Недостаточно денег!" << endl;
				}
				break;
			case 2:
				if (money >= 2000) {
					money -= 2000;
					popularity += 5;
					cout << "Популярность увеличена на 5!" << endl;
				}
				else {
					cout << "Недостаточно денег!" << endl;
				}
				break;
			case 3:
				if (money >= 1000) {
					money -= 1000;
					refreshMarket(true);
					cout << "Рынок животных обновлен!" << endl;
					showMarket();
				}
				else {
					cout << "Недостаточно денег!" << endl;
				}
				break;
			}
		} while (choice != 0);
	}

	//Меню управления вольерами
	void manageBuildings() {
		int choice;
		do {
			cout << "\nУправление постройками:" << endl;
			cout << "1. Купить вольер для травоядных (холодный климат) - 5000" << endl;
			cout << "2. Купить вольер для травоядных (тёплый климат) - 6000" << endl;
			cout << "3. Купить вольер для хищников (холодный климат) - 8000" << endl;
			cout << "4. Купить вольер для хищников (тёплый климат) - 10000" << endl;
			cout << "5. Посмотреть список вольеров" << endl;
			cout << "0. Назад" << endl;
			cout << "Выберите действие: ";
			cin >> choice;

			//Параметры нового вольера
			int price = 0;
			int type = 0;
			int climate = 0;
			int capacity = 5;

			//Установка параметров по выбору
			switch (choice) {
			case 1: price = 5000; type = 0; climate = 0; break;
			case 2: price = 6000; type = 0; climate = 1; break;
			case 3: price = 8000; type = 1; climate = 0; break;
			case 4: price = 10000; type = 1; climate = 1; break;
			case 5: showEnclosures(); continue;
			case 0: continue;
			default: cout << "Неверный выбор!" << endl; continue;
			}

			//Покупка вольера
			if (choice >= 1 && choice <= 4) {
				if (money >= price) {
					money -= price;
					int newId = enclosures.empty() ? 1 : enclosures.back()->getId() + 1;
					enclosures.push_back(new Enclosure(newId, capacity, type, climate, price / 10));
					cout << "Новый вольер куплен!" << endl;
				}
				else {
					cout << "Недостаточно денег!" << endl;
				}
			}
		} while (choice != 0);
	}

	//Отображение информации о вольерах
	void showEnclosures() {
		if (enclosures.empty()) {
			cout << "Нет вольеров!" << endl;
			return;
		}

		cout << "\nСписок вольеров:" << endl;
		//Перебор всех вольеров
		for (auto enc : enclosures) {
			cout << "Вольер #" << enc->getId() << " (" << enc->getAnimalTypeStr()
				<< ", " << enc->getClimateStr() << ")" << endl;
			cout << "Вместимость: " << enc->getAnimalCount() << "/" << enc->getCapacity()
				<< " | Расходы: " << enc->getDailyCost() << " в день" << endl;

			//Список животных в вольере (если есть)
			if (enc->getAnimalCount() > 0) {
				cout << "Животные в вольере:" << endl;
				for (auto a : enc->getAnimals()) {
					cout << "- " << a->getName() << " (" << a->getStatus() << ")" << endl;
				}
			}
			cout << endl;
		}
	}

	//Меню управления персоналом
	void manageEmployees() {
		int choice;
		do {
			cout << "\nУправление персоналом:" << endl;
			cout << "1. Нанять работника" << endl;
			cout << "2. Уволить работника" << endl;
			cout << "3. Посмотреть список работников" << endl;
			cout << "0. Назад" << endl;
			cout << "Выберите действие: ";
			cin >> choice;

			switch (choice) {
			case 1: hireEmployee(); break;
			case 2: fireEmployee(); break;
			case 3: showEmployees(); break;
			}
		} while (choice != 0);
	}

	//Наём нового сотрудника
	void hireEmployee() {
		string name;
		cout << "Введите имя работника: ";
		cin >> name;

		//Выбор должности
		int type;
		cout << "Выберите должность:" << endl;
		cout << "1. Ветеринар (5000 в день)" << endl;
		cout << "2. Уборщик (1000 в день)" << endl;
		cout << "3. Кормильщик (2000 в день)" << endl;
		cout << "0. Отмена" << endl;
		cout << "Выберите тип: ";
		cin >> type;

		if (type < 1 || type > 3) return;

		//Определение должности
		string position;
		switch (type) {
		case 1: position = "Ветеринар"; break;
		case 2: position = "Уборщик"; break;
		case 3: position = "Кормильщик"; break;
		}

		//Добавление нового сотрудника
		employees.push_back(new Employee(name, position));
		cout << "Новый работник нанят!" << endl;
	}

	//Увольнение сотрудника
	void fireEmployee() {
		//Защита от удаления директора
		if (employees.size() <= 1) {
			cout << "Нельзя уволить единственного работника (директора)!" << endl;
			return;
		}

		showEmployees();

		int index;
		cout << "Выберите номер работника для увольнения (0 - отмена): ";
		cin >> index;

		if (index < 1 || index >= employees.size()) return;

		//Процесс увольнения
		cout << "Работник " << employees[index]->getName() << " уволен!" << endl;
		delete employees[index];
		employees.erase(employees.begin() + index);
	}

	//Список рабников, которых уже наняли
	void showEmployees() {
		cout << "\nСписок работников:" << endl;
		for (size_t i = 0; i < employees.size(); ++i) {
			Employee* emp = employees[i];
			cout << i + 1 << ". " << emp->getName() << " - " << emp->getPosition()
				<< " (Зарплата: " << emp->getSalary() << " в день)" << endl;
		}
	}

	//Логика нового дня
	void nextDay()
	{
		//Обновление счётчиков
		day++;
		animalsPurchasedToday = 0;
		cout << "\n=== Наступает день " << day << " ===" << endl;

		//Случайное событие с шуткой кота
		if (jokeCat.tellJoke()) {
			popularity += 100;
		}

		//Старение животных и болезни
		for (auto& a : animals) {
			a->grow();
			if (a->getIsAlive() && Random::chance(10)) {
				a->getSick();
			}
		}

		//Лечение животных ветеринаром (если он есть)
		bool hasVet = any_of(employees.begin(), employees.end(),
			[](Employee* e) { return e->getPosition() == "Ветеринар"; });

		if (hasVet) {
			for (auto& a : animals) {
				if (a->getIsSick() && money >= 5000) {
					money -= 5000;
					a->heal();
					cout << a->getName() << " вылечен ветеринаром за 5000" << endl;
				}
			}
		}

		//Кормление животных кормильщиком (если он есть)
		bool hasFeeder = any_of(employees.begin(), employees.end(), [](Employee* e) { return e->getPosition() == "Кормильщик"; });

		if (hasFeeder && food >= animals.size()) {
			food -= animals.size();
			cout << "Животные накормлены (-" << animals.size() << " еды)" << endl;
		}
		else if (hasFeeder) {
			cout << "Недостаточно еды для всех животных!" << endl;
			for (auto& a : animals) {
				if (Random::chance(50)) {
					a->die();
					cout << a->getName() << " умер от голода!" << endl;
				}
			}
		}
		else {
			cout << "Некому кормить животных! Они голодают!" << endl;
			for (auto& a : animals) {
				if (Random::chance(50)) {
					a->die();
					cout << a->getName() << " умер от голода!" << endl;
				}
			}
		}

		//Уборка вольеров уборщиком (если он есть)
		int cleaners = count_if(employees.begin(), employees.end(),
			[](Employee* e) { return e->getPosition() == "Уборщик"; });

		if (cleaners > 0) {
			int cleaned = min(cleaners, (int)enclosures.size());
			for (int i = 0; i < cleaned; ++i) {
				enclosures[i]->clean();
			}
			cout << cleaned << " вольеров убрано" << endl;
		}
		else {
			cout << "Некому убирать вольеры!" << endl;
		}

		//Расчёт ежедневных расходов
		int dailyCost = 0;
		for (auto enc : enclosures) {
			dailyCost += enc->getDailyCost();
		}
		for (auto emp : employees) {
			dailyCost += emp->getSalary();
		}
		money -= dailyCost;
		cout << "Расходы на содержание: -" << dailyCost << " денег" << endl;

		//Расчет посетителей и доходов
		visitorsToday = 2 * popularity;
		vector<Visitor> visitors;
		int totalBonus = 0;
		for (int i = 0; i < visitorsToday; ++i) {
			Visitor v;
			visitors.push_back(v);
			totalBonus += v.getPopularityBonus();
		}

		//Считаем средний бонус
		if (!visitors.empty()) {
			popularity += totalBonus / visitors.size();
		}

		//Колебание популярности
		popularity += Random::range(-popularity / 10, popularity / 10);
		if (popularity < 5) popularity = 5;

		//Доход от посетителей
		int income = visitorsToday * animals.size();
		money += income;
		totalVisitors += visitorsToday;

		cout << "Посетители сегодня: " << visitorsToday << " (+" << income << " денег)" << endl;
		cout << "Новая популярность: " << popularity << endl;

		//Удаление мертвых животных
		animals.erase(remove_if(animals.begin(), animals.end(),
			[](const unique_ptr<Animal>& a) { return !a->getIsAlive(); }),
			animals.end()

		);
	
	}
};

//Главная функция программы
int main() {
	//Настройка локали для корректного отображения кириллицы
	setlocale(LC_ALL, "rus");
	//Запрос названия зоопарка у пользователя
	string name;
	cout << "Введите название вашего инопланетного зоопарка: ";
	getline(cin, name);
	//Создание экземпляра зоопарка
	AlienZoo zoo(name);
	//Запуск основного игрового цикла
	zoo.run();
	//Завершение программы
	return 0;
}
