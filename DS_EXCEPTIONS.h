/**************************************************************
 * File:    DS_Exceptions.h
 * Project: CMSC 341 - Project 3 - Word Frequency
 * Author : Dean Orenstein
 * Date   : 04/10/2020
 * Section: 518
 * E-mail:  dean27@tamu.edu
 *
 * DS_EXCEPTIONS exception implementations.
 * 
 *************************************************************/

#ifndef DSEXCEPTIONS_H
#define DSEXCEPTIONS_H

#include <string>
#include <exception>
#include <iostream>

using namespace std;

class UnderflowException : public exception {
private:
	string message;
public:
	explicit UnderflowException(const string& m) {
        message = m;
    }
	virtual const char* what() const throw() {
		return message.c_str();
	}
	// Need to override the destructor
	virtual ~UnderflowException() throw() {}
};


class IllegalArgumentException : public exception {
private:
	string message;
public:
	explicit IllegalArgumentException(const string& m) {
        message = m;
    }
	virtual const char* what() const throw() {
		return message.c_str();
	}
	virtual ~IllegalArgumentException() throw() {}
};


class ArrayIndexOutOfBoundsException : public exception {
private:
	string message;
public:
	explicit ArrayIndexOutOfBoundsException(const string& m) {
        message = m;
    }
	virtual const char* what() const throw() {
		return message.c_str();
	}
	virtual ~ArrayIndexOutOfBoundsException() throw() {}
};


class IteratorOutOfBoundsException : public exception {
private:
	string message;
public:
	explicit IteratorOutOfBoundsException(const string& m) {
        message = m;
    }
	virtual const char* what() const throw() {
		return message.c_str();
	}
	virtual ~IteratorOutOfBoundsException() throw() {}
};


class IteratorMismatchException : public exception {
private:
	string message;
public:
	explicit IteratorMismatchException(const string& m) {
        message = m;
    }
	virtual const char* what() const throw() {
		return message.c_str();
	}
	virtual ~IteratorMismatchException() throw() {}
};


class IteratorUninitializedException : public exception {
private:
	string message;
public:
	explicit IteratorUninitializedException(const string& m) {
        message = m;
    }
	virtual const char* what() const throw() {
		return message.c_str();
	}
	virtual ~IteratorUninitializedException() throw() {}
};

#endif