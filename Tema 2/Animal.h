#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <vector>

class AnimalException : public std::runtime_error {
public:
    explicit AnimalException(const std::string& msg) : std::runtime_error(msg) {}
};

class InvalidChoiceException : public AnimalException {
public:
    explicit InvalidChoiceException(const std::string& msg) : AnimalException(msg) {}
};

class Animal {
public:
    Animal(std::string name, int age);
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    virtual ~Animal() = default;

    std::string get_name() const;
    int get_age() const;

    virtual std::string to_string() const = 0;
    virtual void make_sound() const = 0;

    static int get_animal_count();

protected:
    std::string name_;
    int age_;

private:
    static int animal_count_;
};

std::ostream& operator<<(std::ostream& os, const Animal& animal);

class Dog : public Animal {
public:
    Dog(std::string name, int age, std::string breed);
    Dog(const Dog& other) = default;
    Dog& operator=(const Dog& other) = default;

    std::string to_string() const override;
    void make_sound() const override;

private:
    std::string breed_;
};

class Cat : public Animal {
public:
    Cat(std::string name, int age, std::string color);
    Cat(const Cat& other) = default;
    Cat& operator=(const Cat& other) = default;

    std::string to_string() const override;
    void make_sound() const override;

private:
    std::string color_;
};

std::unique_ptr<Animal> create_animal(int choice);

#endif // ANIMAL_H
