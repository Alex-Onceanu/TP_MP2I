#include "hash.h"

unsigned int hash(char* s){
 	unsigned int res = 0;
 	for (int i = 0; s[i] != 0; ++i)
 	{
 		res = (256 * res + s[i])%TAILLE_HASH;
 	}
 	return res;
}