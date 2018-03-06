#include <iostream>
#include "stdint.h"
#include <fstream>
#include <string>

#define define "#define P"
#define type   "(volatile uint32_t *)0x"

using namespace std;

int main()
{
	ofstream x ;

	x.open("bit_specific_addressing.h");
	x<<hex;

	char port='A';
	x<<"//---------------------PORTS_BASE_ADDRESSES---------------------//"<<endl;
	for(int address=0x40004,i=0 ; i<6 ; i++,port++)
	{
		x<<define<<port<<" "<<type<<address<<"000"<<endl;
		address=(i<3)?++address:(i<4)?0x40024:0x40025;
	}
	x<<endl<<endl<<endl;





	port='A';
	for(int address = 0x40004,i=0; i<6 ; i++,port++)
	{
		x<<"//---------------------PORT"<<port<<"---------------------//"<<endl;
		for(int pinaddress=4,j=0 ; j<8 ; j++,pinaddress*=2)
		{
			if(j<2)
				x<<define<<port<<j<<" "<<type<<address<<"00"<<pinaddress<<endl;
			else if(j<6)
				x<<define<<port<<j<<" "<<type<<address<<"0"<<pinaddress<<endl;
			else
				x<<define<<port<<j<<" "<<type<<address<<pinaddress<<endl;
		}
		address=(i<3)?++address:(i<4)?0x40024:0x40025;
		x<<endl<<endl;
	}

	return 0;
}