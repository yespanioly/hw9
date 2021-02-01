#include "field.h"
#include "string.h"
#include "port.h"
#include "ip.h"
#include <cstring>

//Field constructor that takes pattern and type
Field::Field(String pattern, field_type type) {
    pattern=pattern.trim();
    this->pattern=pattern;
    this->type=type;
}
//Field constructor that takes pattern only
Field::Field(String pattern) {
    pattern=pattern.trim();
    if (pattern.equals("src-port") || pattern.equals("dst-port")) {
    	this->type=PORT;
        this->pattern=pattern;
    } else if (pattern.equals("src-ip") || pattern.equals("dst-ip")) {
    	this->type=IP;
        this->pattern=pattern;
    } else {
        this->pattern=pattern;
        this->type=GENERIC;
    }
}

//Field destructor
Field::~Field() { 
}

//returns type of field
field_type Field::get_type() const {
    return this->type;
}
//calls set_value of IP or PORT accordingly
bool Field::set_value(String val) { 
    val=val.trim();
	if (this->type==PORT) {
        Port *port=(Port*)this;
		return port->set_value(val);
	} else if (this->type==IP) {
        Ip *ip = (Ip*)this;
		return ip->set_value(val);
	}
    return false;
}

//calls match_value of IP or PORT accordingly
bool Field::match_value(String val) const { 
    val=val.trim();
	if (this->type==PORT) {
        Port *port=(Port*)this;
		return port->match_value(val);

	} else if (this->type==IP) {
        Ip *ip=(Ip*)this;
		return ip->match_value(val);
	}
    return false;
}
//takes packet splits it and calles match value upon finding a pattern that
//matches that of the rule 
bool Field::match(String packet) {
    String *pkt;
    size_t pkt_size=0;
    packet=packet.trim();
    packet.split("=, ", &pkt, &pkt_size);
    bool matched=false;
    for (size_t i=0; i<pkt_size; i++) {
        pkt[i]=pkt[i].trim();
        if (pkt[i].equals(this->pattern)) {
            //if pattern matches check if the next segment is legal
            if (i+1<pkt_size) {
                matched=match_value(pkt[i+1]);
            }
        }
    }
    delete[] pkt;
    return matched;
}