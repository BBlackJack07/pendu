# Jeu du Pendu C++
Ceci est un Jeu du Pendu programmé en C++, le programme lit chaque ligne du fichier 'wordlist' qui contient 836 mots (un par ligne) et en range le contenu dans un std::vector&lt;std::string&gt;. Ensuite il tire au "hazard" un nombre entre 0 et vector.size() - 1 pour sélectionner le mot mystère.

### Installation
Sous GNU/Linux vous pouvez télécharger et compiler ce jeu du pendu grâce aux commandes suivantes : 
*	git clone https://github.com/BBlackJack07/pendu.git  
*	cd pendu  
*	make install   
Ceci créera un éxécutable sous le nom de "pendu.out" dans le répertoire ../jeu_du_pendu (nécessite les paquets g++, git et make).
