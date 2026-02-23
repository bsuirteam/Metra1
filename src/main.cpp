

#include<iostream>
#include "include/file.h"
#include"include/string_service.h"

int main(){

    std::string path = "/home/udainoko/Documents/BSUIR/Sem4/Metra/PZ1/analyz/main.scala";
    std::string text = proccedFile(path);


    std::vector<std::string> words = split(text);
    for (const auto& w: words){
        std::cout<< w << "\n";
    }

    

}