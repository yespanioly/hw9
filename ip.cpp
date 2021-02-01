#include "ip.h"
#include "field.h"
#include <cstring>

#define MASK_SEGMENT 2
#define SEGMENTS 4
//Ip constructor
Ip::Ip(String pattern): Field(pattern) {
    this->low  = 0;
    this->high = 0;
}
//Sets the rule values of IP, namely this->low and this->high according to
//the value we get from the rule
bool Ip::set_value(String val) {
    size_t words_num=0;
    String *separate_ip_wrds;
    val=val.trim();
    val.split("./ ", &separate_ip_wrds, &words_num);
    unsigned int segmnt=0, ip=0;
    //calculating IP from segments of the rule
    for (size_t i=0; i<SEGMENTS; i++) {
        separate_ip_wrds[i]=separate_ip_wrds[i].trim();
    	segmnt = separate_ip_wrds[i].to_integer();
        //checking if each segment is within the allowed range
    	if (0<=segmnt && segmnt<=255) {
    		ip=(ip<<8)+segmnt;
    	}
    	else {
            delete[] separate_ip_wrds;
    		return false;
    	}
    }
    //calculating the number of important bits (which we named mask)
    separate_ip_wrds[4]=separate_ip_wrds[4].trim();
    unsigned int mask = separate_ip_wrds[4].to_integer();
    if (mask>=0 && mask<=32) {
    	if (mask==32) {
    		this->low  = ip;
    		this->high = this->low;
    	} else if (mask==0) {
            this->low=0;
            this->high=0xffffffff;
        } else {
            //creating 32 bits with ones where the bits aren't
            //important and zeroes where they are (needs inverting)
            int num_n = (1<<(32-mask))-1;
            //inverting the ones and zeroes and taking important bits only
    		this->low  = ~num_n & ip;
    		this->high = (this->low) | num_n;
    	}
        delete[] separate_ip_wrds;
    	return true;
    }
    delete[] separate_ip_wrds;
    return 	false;
}
//checks if the val taken from part of the packet applies to the rule set 
//by set_value
bool Ip::match_value(String val) const {
    String *separate_ip_pkt;
    size_t size=0;
    val=val.trim();
    val.split(".", &separate_ip_pkt, &size);
    unsigned int ip=0, segmnt=0;
    //calculating IP
    for (size_t i=0; i<SEGMENTS; i++) {
    	segmnt = separate_ip_pkt[i].to_integer();
        //checking if each segment is within the allowed range
    	if (segmnt>=0 && segmnt<=255) {
    		ip=(ip<<8)+segmnt;
    	} 
    	else {
            delete [] separate_ip_pkt;
    		return false;
    	}
    }
    delete [] separate_ip_pkt;
    //if ip of packet word is within the range set by set_value return true
    if (ip<=this->high && ip>=this->low) {
    	return true;
    }
    return false;
}