#include "Animal.h"

int Animal::animal_count_ = 0;

Animal::Animal(std::string name, int age) : name_(name), age_(age) {
    ++animal_count_;
}

Animal::Animal(const Animal& other) : name_(other.name_), age_(other.age_) {
    ++animal_count_;
}

Animal& Animal::operator=(const Animal& other) {
    if (this != &other) {
        name_ = other.name_;
        age_ = other.age_;
    }
    return *this;
}

std::string Animal::get_name() const {
    return name_;
}

int Animal::get_age() const {
    return age_;
}

int Animal::get_animal_count() {
    return animal_count_;
}

std::ostream& operator<<(std::ostream& os, const Animal& animal) {
    os << animal.to_string();
    return os;
}

Dog::Dog(std::string name, int age, std::string breed) : Animal(name, age), breed_(breed) {}

std::string Dog::to_string() const {
    return "Dog: " + name_ + ", " + std::to_string(age_) + " years old, " + breed_ + " breed";
}

void Dog::make_sound() const {
    std::cout << "Bark bark!" << std::endl;
}

Cat::Cat(std::string name, int age, std::string color) : Animal(name, age), color_(color) {}

std::string Cat::to_string() const {
    return "Cat: " + name_ + ", " + std::to_string(age_) + " years old, " + color_ + " color";
}

void Cat::make_sound() const {
    std::cout << "Meow meow!" << std::endl;
}

std::unique_ptr<Animal> create_animal(int choice) {
    std::unique_ptr<Animal> animal;
    std::string name;
    int age;
    std::string breed;
    std::string color;
    switch (choice) {
        case 1:
            std::cout << "Creating a dog." << std::endl;
            std::cout << "Enter dog's name: ";
            std::cin >> name;
            std::cout << "Enter dog's age: ";
            std::cin >> age;
            std::cout << "Enter dog's breed: ";
            std::cin >> breed;
            animal = std::make_unique<Dog>(name, age, breed);
            break;
        case 2:
            std::cout << "Creating a cat." << std::endl;
            std::cout << "Enter cat's name: ";
            std::cin >> name;
            std::cout << "Enter cat's age: ";
            std::cin >> age;
            std::cout << "Enter cat's color: ";
            std::cin >> color;
            animal = std::make_unique<Cat>(name, age, color);
            break;
        default:
            throw InvalidChoiceException("Invalid choice.");
    }
    return animal;
}

