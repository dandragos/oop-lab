#include "Animal.h"

void display_menu() {
    std::cout << "1. Add a dog" << std::endl;
    std::cout << "2. Add a cat" << std::endl;
    std::cout << "3. Print all animals" << std::endl;
    std::cout << "4. Print only dogs" << std::endl;
    std::cout << "5. Print only cats" << std::endl;
    std::cout << "6. Exit" << std::endl;
}


int main() {
    std::vector<std::unique_ptr<Animal>> animals;
    int choice = 0;
    while (choice != 4) {
        try {
            display_menu();
            std::cin >> choice;
            switch (choice) {
                case 1:
                case 2:
                    animals.push_back(create_animal(choice));
                    break;
                case 3:
                    std::cout << "Number of animals: " << Animal::get_animal_count() << std::endl;
                    for (const auto& animal : animals) {
                        std::cout << *animal << std::endl;
                        animal->make_sound();
                    }
                    break;
                case 4:
                    std::cout << "Printing only dogs:" << std::endl;
                    for (const auto& animal : animals) {
                        Dog* dog = dynamic_cast<Dog*>(animal.get());
                        if (dog) {
                            std::cout << *dog << std::endl;
                            dog->make_sound();
                        }
                    }
                    break;
                case 5:
                    std::cout << "Printing only cats:" << std::endl;
                    for (const auto& animal : animals) {
                        Cat* cat = dynamic_cast<Cat*>(animal.get());
                        if (cat) {
                            std::cout << *cat << std::endl;
                            cat->make_sound();
                        }
                    }
                    break;
                case 6:
                    std::cout << "Exiting program." << std::endl;
                    break;
                default:
                    throw InvalidChoiceException("Invalid choice.");
            }
        } catch (const AnimalException& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}
