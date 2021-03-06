#include "hangman.hpp"

int main()
{
    {
        using namespace std::chrono_literals;
        std::cout << " Bonjour,\n Bienvenue dans le Jeu du Pendu !" << std::endl;;
        std::this_thread::sleep_for(1000ms);
        std::cout << " Règles : " << std::endl; 
        std::this_thread::sleep_for(1000ms);
        std::cout << " - Vous avez le droit à 9 erreurs." << std::endl;
        std::this_thread::sleep_for(1500ms);
        std::cout << " - Ecrivez tous les mots et lettres sans accents.\n" << std::endl;
        std::this_thread::sleep_for(1500ms);
    }
    
    bool replay { true };

    try {
        Hangman hangman("res/wordlist");
        do
        {
            hangman.start_game();
            char answer {};
            std::cout << "Voulez-vous rejouer ? (o/n) ";
            std::cin >> answer;
            if (answer != 'o')
                replay = false; 
        }while(replay);
    } 
    catch (std::string str_error) {
        std::cout << str_error << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

