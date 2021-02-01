#include "string.h"
#include <stddef.h>
#include <iostream>
#include <cstring>


/**
* @brief Initiates an empty string
*/
String::String() {
    data = new char[1];
    *data='\0';
    length= 1;
}

/**
 * @brief Initiates string from other string
 */
String::String(const String &str) {
    this->length= str.length;
    this->data = new char[this->length];
    for (size_t i=0; i<this->length; i++) {
        this->data[i] = str.data[i];
    }
}

/**
 * @brief Initiates a string from char array
 */
String::String(const char *str) {
    //std::cout<< "start const "<< str << std::endl;
    this->length=0;
    size_t j=0;
    if (str) {
        while (*(str+j)) {
            this->length++;
            j++;
        }
        //increase length by 1 for '\0'
        this->length++;
        this->data = new char[this->length];
        for (size_t i=0; i<this->length; i++) {
            this->data[i] = str[i];
        }
    }
}

//String destructor
String::~String() {
    delete[] this->data;
}

/**
 * @brief Changes this from String
 */
String& String::operator=(const String &rhs) {
    delete[] this->data;
    this->length=rhs.length;
    this->data = new char[this->length];
    for (size_t i=0; i<this->length; i++) {
        this->data[i]=rhs.data[i];
    }
    return *this;
}

/**
 * @brief Changes this from char array
 */
String& String::operator=(const char *str) {
    delete[] this->data;
    size_t i=0;
    while (*(str+i)) {
        this->length++;
        i++;
    }
    this->data = new char[this->length];
    for (size_t i=0; i<this->length; i++) {
        this->data[i]=str[i];
    }
    return *this;
}

/**
 * @brief Returns true iff the contents of this equals to the
 * contents of rhs
 */
bool String::equals(const String &rhs) const {
    for (size_t i=0; i<this->length; i++) {
        if (this->data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Returns true iff the contents of this equals to rhs
 */
bool String::equals(const char *rhs) const {
    if (rhs) {
        for (size_t i=0; i<this->length; i++) {
            if (this->data[i] == rhs[i]) {
                continue;
            } else {
                return false;
            }
        }
        return true;
    }
    return false;
}

/**
 * @brief Splits this to several sub-strings according to delimiters.
 * Allocates memory for output that the user must delete (using delete[]).
 * @note Does not affect this.
 * @note If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 */
void String::split(const char *delimiters, String **output, size_t *size) const {
    //in order to use strtok we need to initialize a char array with the same 
    //data as this->data
    char *str= new char[this->length];
    for (size_t i=0; i<this->length; i++) {
        str[i] = this->data[i];
    }
    char *token;
    token = strtok(str, delimiters);
    (*size)=0;
    //calculate number of strings to be splitted
    while (token) {
        (*size)=(*size)+1;
        token = strtok(NULL, delimiters);
    }
    if (output) {
        *(output) = new String[*size];
    } else {
        delete[] str;
        return;
    }
    //reset the place where we place the strings
    (*size)=0;
    char *str2= new char[this->length];
    for (size_t i=0; i<this->length; i++) {
        str2[i] = this->data[i];
    }
    //same as before but we use a new str to keep track of pointers
    char *token2;
    token2 = strtok(str2, delimiters);
    while (token2) {
        if (token2==NULL) {
            break;
        } else {
            (*output)[*size] = token2;
        }
        (*size)=(*size)+1;
        token2 = strtok(NULL, delimiters);
    }
    delete[] str;
    delete[] str2;
    for (size_t i = 0; i < *size; ++i) {
        (*output)[i] =(*output)[i].trim();
    }
}


/**
 * @brief Try to convert this to an integer. Returns 0 on error.
 */
int String::to_integer() const {
    //atoi turns str into integer
    return atoi(this->data);
}

String String::trim() const {
    if (this->data==NULL) {
        return 0;
    }
    //calculate first index of non white space
    int start=0, end=this->length-2;
    while (this->data[start]==' ') {
        start++;
    }
    //calculate index of last non space
    while (this->data[end]==' ') {
        end--;
    }
    //if for some reason end<start give up and return this->data
    if (end<=start) {
        return this->data;
    }
    String str =  String();
    delete[] str.data;
    str.data   = new char[end-start+2];
    //set str length as: (end-start+1) which is number of characters
    // and another +1 for the '\0'
    str.length = end-start+2;
    size_t i=0;
    //hard copy the data
    for (i=0; i<str.length-1; i++) {
        str.data[i]=this->data[i+start];
    }
    //DO NOT FORGET TO HARD COPY '\0'
    str.data[i]='\0';
    return str;



}