/**************************************************************
 * File:    Exceptions.h
 * Project: CMSC 341 - Project 3 - Word Frequency
 * Author : Dean Orenstein
 * Date   : 04/10/2020
 * Section: 518
 * E-mail:  dean27@tamu.edu
 *
 * Exceptions exception implementations.
 * 
 *************************************************************/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <iostream>

using namespace std;

class Exceptions : public exception {
private:
    string message;

public:
    explicit Exceptions(const string& m) {
        message = m;
    }
    const char* GetMessage() const throw() {
        return message.c_str();
    }
    virtual ~Exceptions() throw() {}
};

#endif