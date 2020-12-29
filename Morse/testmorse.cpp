#include <iostream>
#include <string>
#include <map>
#include "morse.h"

int main() {
    std::cout << mapmorse["S"] << ' ' << mapmorse["O"] << ' ' << mapmorse["S"] << std::endl; // ... --- ...
    std::cout << encode_lettre("A") << std::endl; // .-
    std::cout << encode_lettre("é") << std::endl; // Erreur, cette lettre n'est pas codée
    std::cout << encode_lettre("à") << std::endl; // Idem
    std::cout << encode_lettre("a") << std::endl; // .- avec ToUpper
    std::cout << encode_mot("salut") << std::endl; // ... .- .-.. ..- -
    std::cout << encode_msg("John Cena") << std::endl; // Correct !
    std::cout << decode_lettre(".--") << std::endl; // W
    std::cout << decode_lettre(".-.-.-") << std::endl; // Erreur car aucune lettre ne correspond à ce code
    std::cout << decode_mot("... --- ...") << std::endl; // ...SOS évidemment
    std::cout << decode_msg(".--- . / - .----. .- .. -- .") << std::endl; // JE T'AIME
    std::string message = "SAUCISSE DE MORTEAU"; // Un message codé, à protéger des Anglois...
    std::string messagecode = encode_msg(message);
    std::string messagedecode = decode_msg(messagecode);
    std::cout << "'" << message << "'" << ' ' << messagecode << ' ' << "'" << messagedecode << "'" << std::endl;
    std::cout << std::boolalpha << pareil(message,messagedecode) << std::endl; // Et le message que l'on récupère est bien le même !
    return 0;
}

