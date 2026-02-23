#include "../include/string_service.h"
std::vector<std::string> split (std::string str){


    str = add_space(str);
    std::istringstream iss(str);
    std::vector <std::string> words;
    std::string word;

    while( iss >> word){
        words.push_back(word);
    }

    return words;
}


std::string add_space(std::string str){
    
    for (size_t i = 0; i < str.size(); ++i){
        if(str[i] == '(' || str[i] == ')'|| str[i] == ']' || str[i] == '[' || str[i] == '{' || str[i] == '}'){
            str.insert(str.begin() + i, ' ');
            i+=2;
            str.insert(str.begin() + i, ' ');

        }
    } 
    return str;
}