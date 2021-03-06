#include "hangman.hpp"

Hangman::Hangman(std::string path_to_wordlist)
{
    std::ifstream file (path_to_wordlist);
    if (!file)
        throw "Error: the file '" + path_to_wordlist  + "' was not found!";
    wordlist << file;
    file.close();
}


void Hangman::start_game()
{
    errors = 0;
    win = false;
    foundLetters.clear();
    triedLetters.clear();

    word = getRandomElement(wordlist);
    std::transform(word.begin(), word.end(), word.begin(), ::toupper);

    unsigned short int round {1};
    
    while(errors < 9 && !win)
    {   
        std::cout << "\033[H\033[2J";std::cout.flush();

        std::cout << std::endl << drawHangman() << std::endl;
        std::cout << "Vous avez déjà essayé les lettres suivantes : "; pprint(std::cout, begin(triedLetters), end(triedLetters), " ");
        
        std::cout << "\n\n" << "========== Round " << round << " ==========" << std::endl;
        std::cout << " " << showWord() << std::endl << std::endl;
        std::cout << " Entrez une lettre ou un mot : ";
        std::string inputWord {};
        std::cin >> inputWord;
        
        if(wordsAreEqual(inputWord))
        {
            std::cout << " Génial ! Vous avez trouvé le mot !" << std::endl;
            win = true;
        }	
        else if(inputWord.size() == 1 && letterIsInWord(inputWord))
        {
            std::cout << " Bien joué, vous avez trouvé une lettre ! " << std::endl;
            if(isWordFound())
            {
                std::cout << " Génial ! Vous avez trouvé toutes les lettres du mot ! Celui-ci était : " << word  << " !" << std::endl;
                win = true;
            }
        }
        else
        {
            if(inputWord.size() == 1 && triedLetters != inputWord[0]) triedLetters.push_back(inputWord[0]);
            errors++;
            std::cout << " Zut... vous vous êtes trompé." << std::endl;
            std::cout << drawHangman() << std::endl;
        }
        std::cout << "=============================" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        round++;

    }

    if(!win)
    {
        std::cout << " Dommage, vous avez perdu. Le mot était : " << word << std::endl;
    }
    else
    {
        std::cout << " Vous avez gagné !" << std::endl;
    }
}


bool Hangman::wordsAreEqual(std::string inputWord)
{
    std::transform(inputWord.begin(), inputWord.end(), inputWord.begin(), ::toupper);
    return inputWord == word;
}


bool Hangman::letterIsInWord(std::string inputWord)
{
    for(unsigned short int i {0}; i < word.size(); i++)
    {
        if(toupper(inputWord[0]) == word[i])
        {
            foundLetters.push_back(word[i]);
            return true;
        }
    }
    return false;
}


bool Hangman::isWordFound()
{
    for(unsigned short int i {0}; i < word.size(); i++)
    {
        if(foundLetters != word[i])
            return false;
    }
    return true;
}

std::string Hangman::showWord()
{
    std::string showWord {};

    for(unsigned int i {0}; i < word.size(); i++)
    {
        if(foundLetters == word[i])
        {
            showWord += word[i];
            showWord += " ";
        }
        else
        {
            showWord += "_ ";
        }
    }
    return showWord;
}

std::string Hangman::drawHangman()
{
    switch (this->errors)
    {
        case 1:
            return "_____\n";
        case 2:
            return "|\n|\n|\n|_____\n";
        case 3:
            return "__________\n|\n|\n|\n|_____\n";
        case 4:
            return "__________\n|/\n|\n|\n|_____\n";
        case 5:
            return "__________\n|/       |\n|        |\n|\n|_____\n";
        case 6:
            return "__________\n|/       |\n|        |\n|        O\n|_____\n";
        case 7:
            return "__________\n|/       |\n|        |\n|        O\n|_____   |\n         |\n";
        case 8:
            return "__________\n|/       |\n|        |\n|        O\n|_____  \\|/\n         |\n";
        case 9:
            return "__________\n|/       |\n|        |\n|        O\n|_____  \\|/\n         |\n        ( )\n";
        default:
            return "";
        /*__________
          |/       |
          |        |
          |        O
          |_____  \|/
                   |
                  ( )*/
    }
}

