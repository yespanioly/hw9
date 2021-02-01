#include "field.h"
#include "string.h"
#include "port.h"
#include "ip.h"
#include "input.h"
#include <cstring>

int main(int argc, char *argv[]) {
   //if arguments are not legal exit main
	if(check_args(argc, argv)) {
      return 1;
   }
   //create String from the rule
	String law_str = String(argv[1]);
	String *out;
  	size_t size=0;
   law_str=law_str.trim();
 	law_str.split("=", &out, &size);
   out[0]=out[0].trim();
   out[1]=out[1].trim();
   //if first segment of the rule matches IP or PORT create a field and
   //call the correct set_value accordingly 
  	if ( (out[0].equals("src-ip")) || (out[0].equals("dst-ip")) ) {
  		Ip law_ip = Ip(out[0]);
  		law_ip.set_value(out[1]);
  		parse_input(law_ip);
  	}
  	if ( (out[0].equals("src-port")) || (out[0].equals("dst-port")) ) {
  		Port law_prt = Port(out[0]);
  		law_prt.set_value(out[1]);
  		parse_input(law_prt);
  	}
delete[] out;
return 0;
}