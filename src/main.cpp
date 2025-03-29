#include <iostream>
#include "system/system_manager.hpp"
#include "exceptions/exceptions.hpp"

int main() {
    SystemManager systemM;
    bool exitProgram = false;

    try {
        while(!exitProgram) {
            Utils::clearConsole();
            std::cout <<"<<< To select one of the items, write the number below >>>" << std::endl;
            std::cout << "\n";
            std::cout <<"\t1 *Admin registration" << std::endl;
            std::cout <<"\t2 *Admin login" << std::endl;
            std::cout <<"\t3 *Student registration" << std::endl;
            std::cout <<"\t4 *Student login" << std::endl;
            std::cout <<"\t5 *Exit" << std::endl;

            int choice;

            std::cout <<"\nNumber #";
            std::cin >> choice;
            Utils::ignoreEnter();

            User* currentUser = nullptr;

            switch(choice) {
                case 1:
                    systemM.registration(true);
                    break;
                case 2:
                    currentUser = systemM.login(true);
                    if(currentUser) {
                        currentUser->showMenu();
                        delete currentUser;
                    }
                    break;
                case 3:
                    systemM.registration(false);
                    break;
                case 4:
                    currentUser = systemM.login(false);
                    if(currentUser) {
                        currentUser->showMenu();
                        delete currentUser;
                    }
                    break;
                case 5:
                    exitProgram = true;
                    break;
                default:
                    std::cout << "Invalid command!" << std::endl;
            }
        }
    }
    catch(const MyExceptions::ErrorAnswerAdmin& e) {
        std::cerr << e.what() << '\n';
    }
    catch(const MyExceptions::ErrorAnswerUser& e) {
        std::cerr << e.what() << '\n';
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
