#include "field.h"
#include "port.h"
#include <cstring>
//Port constructor
Port::Port(String pattern): Field(pattern) {
    this->range[0]=0;
    this->range[1]=0;
}
//Sets the rule values of PORT, namely this->range[0] and this->range[1] 
//according to the value we get from the rule
bool Port::set_value(String val) {
    String *separate_port_law;
   	size_t size=0;
    val=val.trim();
   	val.split("-", &separate_port_law, &size);
    for (size_t i=0; i<size; i++) {
      separate_port_law[i]=separate_port_law[i].trim();
    }
    //calculate lower and upper limits
   	this->range[0] = separate_port_law[0].to_integer();
   	this->range[1] = separate_port_law[1].to_integer();
    //check if values are within the allowed range
   	if ((0<=this->range[0] && this->range[0]<=65535) && 
    							 (0<=this->range[1] && this->range[1]<=65535) && 
    										  (this->range[0]<=this->range[1])) {
      delete[] separate_port_law;
    	return true;
    }
    delete[] separate_port_law; 
    return false;
}
//checks if the val taken from part of the packet applies to the rule set 
//by set_value
bool Port::match_value(String val) const {
    val=val.trim();
    int num = val.to_integer();
   	if ((num>=this->range[0]) && (num<=this->range[1])) {
    	return true;
    }
    return false;
}