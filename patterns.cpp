#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//The Singleton Pattern
//---------------------
//Ensures that only 1 instance of a
//class exists throughout the 
//program. The getInstance Method
//provides global access to that
//single instance.

class Singleton {
private:
	static Singleton* instance;
	Singleton() {
	}
public:
	static Singleton* getInstance() {
		if(!instance) {
			instance = new Singleton();
		}
		return instance;
	}
};


//The Factory Design Pattern
//-----------------------
//Pass in a context and let the
//factory create the new object
//and return it. This provides
//a single place to create a 
//an object based on a given
//context.

enum class ShapeType {
	Circle,
	Square	
};

class Shape {
public:
	virtual ~Shape() = 0;
	virtual void draw() = 0;
};

Shape::~Shape() {
	std::cout << "Pure virtual destructor called" << std::endl;
}

class Circle : public Shape {
private:
	std::string name;	
public:
	Circle() {
		this->name = "Circle";
	}
	~Circle() {
		std::cout << this->name << " destructor called" << std::endl;
	}
	void draw() {
		std::cout << "drawing " << this->name << std::endl;
	}
};

class Square : public Shape {
private:
	std::string name;
public:
	Square() {
		this->name = "Square";
	}
	~Square() {
		std::cout << this->name << " destructor called" << std::endl;
	}
	void draw() {
		std::cout << "drawing " << this->name << std::endl;
	}
};

class ShapeFactory {
public:
	Shape* getShape(ShapeType type) {
		Shape* shape;
		switch(type) {
			case ShapeType::Circle:
					shape = new Circle();
					break;
			case ShapeType::Square:
					shape = new Square();
					break;
			default:
					shape = new Circle();
					break; 
		}
		return shape;
	}
};

//The Strategy Pattern
//--------------------
//Extract a family of algorithms
//or behaviours into external
//objects. This allows alogorithm
//selection at runtime. It also
//improves maintenance by decoupling
//the client and the implementations.

class QuackBehaviour {
public:
	virtual void doQuack() {
		std::cout << "Quack" << std::endl;
	}
};

class LoudQuackBehaviour : public QuackBehaviour {
public:
	void doQuack() {
		std::cout << "Quack!!" << std::endl;
	}
};

class Duck {
public:
	~Duck() {
		delete quacker;
	}
	void quack() {
		quacker->doQuack();
	}
	void setQuack(QuackBehaviour* quackBehaviour) {
		quacker = quackBehaviour;
	}
private:
	QuackBehaviour* quacker;
};

//The Decorator Pattern
//---------------------
//Add additional functionality to a 
//class at runtime. This is achieved by
//using wrapper classes which can extend
//the functionality of the standard class.

class Burger {
public:
	virtual std::string describe() = 0;
};

class BeefBurger : public Burger {
public:
	std::string describe() {
		return "I am a beef burger";
	}
};

class BurgerDecorator : public Burger {
public:
	BurgerDecorator(Burger* b) {
		burger = b;
	}
	std::string describe() {
		return burger->describe();
	}
private:
	Burger* burger;
};

class Bacon : public BurgerDecorator {
public:
	Bacon(Burger* b) : BurgerDecorator(b) {
	}
	std::string describe() {
		return BurgerDecorator::describe() + ", with added bacon";
	}
};

class Cheese : public BurgerDecorator {
public:
	Cheese(Burger* b) : BurgerDecorator(b) {
	}
	std::string describe() {
		return BurgerDecorator::describe() + ", with added cheese";
	}
};

//The Observer Pattern
//---------------------
//Facilitates notifications
//when an event occurs. Allows clients
//to register with a producer and from
//then on receive notifications when
//an update is performed on the 
//producer.

class Observer {
public:
	virtual void update() = 0;
};

class Observee {
public:
	virtual void registerListener(Observer* o) = 0;
	virtual void unregisterListener(Observer* o) = 0;	
};

class Database : public Observee {
public:
	void registerListener(Observer* o) {
		observers.push_back(o);
	}
	void unregisterListener(Observer* o) {
		observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
	}
	void updateData() {
		// some update to database...
		
		for(Observer* o : observers) {
			o->update();
		}
	}
private:
	std::vector<Observer*> observers;
};

class InterestedParty : public Observer {
public:
	void update() {
		std::cout << "Received notification" << std::endl;
	}
};

//The Builder Pattern
//-------------------
//Allows the client to assemble an
//object with the components they
//wish. Rather than having complex
//constructors which predefine what
//attributes should be.

class Pizza {
public:
	void setDough(const std::string& dough) {
		m_dough = dough;
	}
	void setSauce(const std::string& sauce) {
		m_sauce = sauce;
	}
	void setTopping(const std::string& topping) {
		m_topping = topping;
	}
	void describe() const {
		std::cout << "Pizza with " << m_dough << " dough, " << m_sauce << " sauce and "
			<< m_topping << " topping." << std::endl;
	}
private:
		std::string m_dough;
		std::string m_sauce;
		std::string m_topping;
};

class PizzaBuilder {
public:
	virtual ~PizzaBuilder() {};
	
	Pizza* getPizza() {
		return m_pizza;
	}
	void createNewPizzaProduct() {
		m_pizza = new Pizza();
	}
	virtual void buildDough() = 0;
	virtual void buildSauce() = 0;
	virtual void buildTopping() = 0;
protected:
	Pizza* m_pizza;
};

class HawaiianPizzaBuilder : public PizzaBuilder {
public:
	virtual ~HawaiianPizzaBuilder() {};
	
	virtual void buildDough()
	{
		m_pizza->setDough("cross");
	}
	virtual void buildSauce()
	{
		m_pizza->setSauce("mild");
	}
	virtual void buildTopping()
	{
		m_pizza->setTopping("Ham and Pineapple");
	}
};

class SpicyPizzaBuilder : public PizzaBuilder {
public:
    virtual ~SpicyPizzaBuilder() {}; 

	virtual void buildDough()
	{
		m_pizza->setDough("pan baked");
	}
	virtual void buildSauce()
	{
		m_pizza->setSauce("hot");
	}
	virtual void buildTopping()
	{
		m_pizza->setTopping("pepperoni+salami");
	}
};

class Cook {
public:
	void setPizzaBuilder(PizzaBuilder* pb)
	{
		m_pizzaBuilder = pb;
	}
	Pizza* getPizza()
	{
		return m_pizzaBuilder->getPizza();
	}
	void constructPizza()
	{
		m_pizzaBuilder->createNewPizzaProduct();
		m_pizzaBuilder->buildDough();
		m_pizzaBuilder->buildSauce();
		m_pizzaBuilder->buildTopping();
	}
private:
	PizzaBuilder* m_pizzaBuilder;
};

// Test patterns in main execution
int main(int argc, char** args) {
	
	// ######### BUILDER #########
	
	Cook cook;
	PizzaBuilder* hawaiianPizzaBuilder = new HawaiianPizzaBuilder();
	PizzaBuilder* spicyPizzaBuilder   = new SpicyPizzaBuilder();
 
	cook.setPizzaBuilder(hawaiianPizzaBuilder);
	cook.constructPizza();
 
	Pizza* hawaiianPizza = cook.getPizza();
	hawaiianPizza->describe();
 
	cook.setPizzaBuilder(spicyPizzaBuilder);
	cook.constructPizza();
 
	Pizza* spicyPizza = cook.getPizza();
	spicyPizza->describe();
 
	delete hawaiianPizzaBuilder;
	delete spicyPizzaBuilder;
	delete hawaiianPizza;  
	delete spicyPizza;
	
	getchar();
	return 0;
	
	// ######### OBSERVER #########
	
	Database* db = new Database();
	InterestedParty* ip = new InterestedParty();
	
	db->registerListener(ip);
	
	db->updateData();
	
	delete db;
	delete ip;
	
	getchar();
	return 0;
	
	// ######### DECORATOR #########
	
	Burger* burger = new Cheese(new Bacon(new BeefBurger()));

	std::cout << burger->describe() << std::endl;
	
	delete burger;
	
	getchar();
	return 0;
	
	// ######### STRATEGY #########
	
	Duck duck;
	
	// set the behaviour you want at runtime
	QuackBehaviour* loudQuack = new LoudQuackBehaviour();
	duck.setQuack(loudQuack);
	
	duck.quack();
	
	delete loudQuack;
	
	getchar();
	return 0;
	
	// ######### FACTORY METHOD #########
	
	ShapeFactory factory;
	
	Shape* shape = factory.getShape(ShapeType::Circle);
	shape->draw();

	Shape* anotherShape = factory.getShape(ShapeType::Square);
	anotherShape->draw();
	
	delete shape;
	delete anotherShape;
	
	getchar();
	return 0;
	
}