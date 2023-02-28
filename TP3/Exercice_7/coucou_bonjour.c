#include <stdio.h>
#include <assert.h>




int main(int argc, char const *argv[])
{
	char str1[8] = "BONJOUR"; // 7 lettres + 1 caractère nul = 8
	char str2[7] = "COUCOU";
	
	str1[12] = 'H';
	str2[6] = 'K';

	printf("%s\n", str2);
	printf("%s\n", str1);


	return 0;
}