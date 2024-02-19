//
// Created by maaya on 07/01/2024.
//

#ifndef WINTERAVLTREE_EXCEPTIONS_H
#define WINTERAVLTREE_EXCEPTIONS_H

#include <exception>
#include <string>



class Name_Error : public std::exception {
public:
    const char* what() const noexcept override {
            return "The name contains characters that are not in English letters or with space";
    }
};

class DeckFileNotFound : public std::exception {
public:
    const char* what() const noexcept override {
            return "Deck File Error: File not found.";
    }
};

class DeckFileInvalidSize : public std::exception {
public:
    const char* what() const noexcept override {
            return "Deck File Error: Deck size is invalid.";
    }
};

class DeckFileFormatError : public std::exception {
    int m_line;
    std::string* m_returnString;
public:
    explicit DeckFileFormatError(int line) : m_line(line) {
        m_returnString = new std::string(std::string("Deck File Error: File format error in line ") + std::to_string(m_line));
    };
    const char* what() const noexcept override {
            return (*m_returnString).c_str();
    }
    ~DeckFileFormatError() override
    {
        delete m_returnString;
    }

};




#endif //WINTERAVLTREE_EXCEPTIONS_H
