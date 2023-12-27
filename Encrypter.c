//Message Encrypter 

#include<lpc21xx.h> 
char rx (void); 
void tx (char); 

int main() 
{ 
	PINSEL0=0x000000005; 
	U0LCR=0x9B; 
	U0DLL=0xC3; 
	U0DLM=0x00; 
	U0LCR=0x1B; 

	while(1) 
	{ 
		char b; 
		b = rx(); 
		tx(b); 
	} 
} 

char rx (void) 
{
	char a, d; 
	int c, q; 

	while(!(U0LSR & 0x01)); 
	{ 
		a = U0RBR; 
		c = (int) a; 

		if(c>=65 && c<=77) 
		{ 
			c = c+13+32; 
		} 	
		else if(c>=78 && c<=90) 
		{ 
			c = c-13+32; 
		} 
		else if(c>=97 && c<=109) 
		{ 
			c = c+13-32; 
		} 
		else if(c>=110 && c<=122) 
		{ 
			c = c-13-32; 
		} 	

		c = (c ==  40) ?  41 : ((c ==  41) ?  40 : c); 
		c = (c ==  60) ?  62 : ((c ==  62) ?  60 : c); 
		c = (c ==  91) ?  93 : ((c ==  93) ?  91 : c); 
		c = (c == 123) ? 125 : ((c == 125) ? 123 : c); 
		c = (c ==  47) ?  92 : ((c ==  92) ?  47 : c); 
		c = (c ==  43) ?  45 : ((c ==  45) ?  43 : c); 
		c = (c ==  38) ? 124 : ((c == 124) ?  38 : c); 
		c = (c ==  37) ?  42 : ((c ==  42) ?  37 : c); 
		c = (c ==  46) ?  63 : ((c ==  63) ?  46 : c); 
		c = (c ==  58) ?  59 : ((c ==  59) ?  58 : c); 

		d = (char) c; 
		return (d); 
	}	 
} 

void tx (char a) 
{ 
	while(!(U0LSR & 0x20)); 
	{ 
		U0THR = a; 
	} 
} 