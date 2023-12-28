#include "functions.hpp"
#include <cctype>
#include <iostream>
bool Check(std::string checkInput) {
    for (unsigned int i = 0; i < checkInput.size(); i++) {
        unsigned char input = tolower(checkInput.at(i));
        if (input != 'p' 
        && input != 'k' && input != 'l' && input != 'm' 
        && input != 'n' && input != 'h' && input != 'a' 
        && input != 'e' && input != 'i' && input != 'o' 
        && input != 'u' && input != 'w' && input != '\'' && input != ' ') {
            return false;
    }
    }
    return true;
}
std::string OnlyVowel(char vowel) {
    if (vowel == 'a') {
        return "ah-";
    } 
    if (vowel == 'e') {
        return "eh-";
    } 
    if (vowel == 'i') {
        return "ee-";
    } 
    if (vowel == 'o') {
        return "oh-";
    } 
    return "oo-";
}
std::string HawaiianWords(std::string hww) {
    std::string pron;
    for (unsigned int i = 0; i < hww.size(); i++) {
        if (!Check(hww)) {
            return hww + " contains a character not a part of the Hawaiian language.";
        }
        unsigned char dup = tolower(hww.at(i));
        unsigned char next = tolower(hww[i + 1]);
        if (dup == 'a' && (next == 'i' || next == 'e')) {
            pron += "eye-";
        } else if (dup == 'a' && (next == 'o' || next == 'u')) {
            pron += "ow-";
        } else if (dup == 'e' && (next == 'i')) {
            pron += "ay-";
        } else if (dup == 'e' && (next == 'u')) {
            pron += "eh-oo-";
        } else if (dup == 'i' && (next == 'u')) {
            pron += "ew-";
        } else if (dup == 'o' && next == 'u') {
            pron += "ow-";
        } else if (dup == 'u' && next == 'i') {
            pron += "ooey-";
        } else if (dup == 'a' || dup == 'e' || dup == 'i' || dup == 'o' || dup == 'u') {
            pron += OnlyVowel(dup);
            if (hww[i + 1] == ' ' || hww[i + 1] == '\'') {
                pron = pron.substr(0, pron.size() - 1);
            }
            continue;
        } else { 
            if (i != 0 && dup == 'w' && (hww[i - 1] == 'i' || hww[i - 1] == 'e')) {
                pron += 'v';
            } else { pron += dup; }
            continue;
        }
        i = i + 1;
    }
    if (pron.at(pron.size() - 1) == '-') {
        return pron.substr(0, pron.size() - 1);
    }
    return pron;
}



// Your function definitions should go in this source file.