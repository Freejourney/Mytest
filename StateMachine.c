#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char config[] = " abc =b\\n  ;c=\\x61d;d=234;t=\\n;d=\"test;yes\";";

/*
state 0: 初始状态扫描key
state 1: 扫描value，非引号字符
state 2: 扫描value，引号字符内
state 3: 扫描value，value读取结束
*/

struct Pair
{
  char *key;
  char *value;
};


int main()
{
	int i = 0;
	int state = 0;
	int begin = 0;
	while (i < strlen(config)) {
		Pair pair; 
		switch(state)
		{
			case 0:
				if(config[i] == '=')
				{
					state = 1;
//					printf("key--从%c开始取到%c结束,长度为%d\n", config[begin], config[i-1], i-begin);
					pair.key = (char *)malloc((i-begin)*sizeof(char));
					strncpy(pair.key, config+begin, i-begin);
					
					begin = i+1;					
				}
				break;
			case 1:
				if(config[i] == '"')
				{
					state = 2;
					
				} 
				else if(config[i] == ';')
				{
					state = 3;
					if(i == strlen(config)-1) 
					{
						pair.value = (char *)malloc((i-begin)*sizeof(char));
						strncpy(pair.value, config+begin, i-begin);
						printf("key为%s, value为%s\n", pair.key, pair.value);
					}
				}
				break;
			case 2:
				if(config[i] == '"')
				{
					state = 1;
				}
				break;
			case 3:
//				printf("从%c开始取到%c结束,长度为%d", config[begin], config[i-2], i-begin-1);
				pair.value = (char *)malloc((i-begin-1)*sizeof(char));
				strncpy(pair.value, config+begin, i-begin-1);
				printf("key为%s, value为%s\n", pair.key, pair.value);
				begin = i;
				i--;
				state = 0;
				break;
			default: break;
		}
		i++;
	}
	return 0;
}
