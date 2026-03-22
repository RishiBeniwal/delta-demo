#include <stdio.h> #include <gmp.h> #include <string.h>

#define BLOCK_SIZE 8
void compute_mac(char *message, mpz_t key, mpz_t mac)
{
mpz_t T, block; mpz_init_set_ui(T,0); mpz_init(block);
int len = strlen(message);

for(int i=0;i<len;i+=BLOCK_SIZE)
{
unsigned char buffer[BLOCK_SIZE]; memset(buffer,0,BLOCK_SIZE);

int copy_len = BLOCK_SIZE; if(i + BLOCK_SIZE > len)
copy_len = len - i;

memcpy(buffer, message+i, copy_len); mpz_import(block, BLOCK_SIZE, 1, 1, 0, 0, buffer); mpz_xor(T, T, block);
}

mpz_xor(mac, T, key); mpz_clear(T); mpz_clear(block);
}

int main()
{
char message[1024];
 
mpz_t key, mac; mpz_init(key); mpz_init(mac);

printf("Enter message: "); fgets(message,sizeof(message),stdin); message[strcspn(message,"\n")] = 0;

printf("Enter key (hex): "); gmp_scanf("%Zx",key);

compute_mac(message,key,mac);

printf("MAC:\n"); gmp_printf("%Zx\n",mac);
mpz_clear(key); mpz_clear(mac);

return 0;
}
