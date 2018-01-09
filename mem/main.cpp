#include <iostream>
#include <stdio.h>
#include <sys/sysinfo.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// g++ -Wall main.cpp -o killmem


int main(int argc, char* argv[]) {
     int ch=0;
     int time = 10;
     double percent = 0.2;
     while((ch = getopt(argc, argv, "p:t:h")) != -1) {  
        switch(ch){  
            case 'p':  
                printf("选项是%c, 选项内容: %s\n", ch, optarg);  
                percent = atof(optarg);
                break;  
            case 't':  
                printf("选项是%c, 选项内容: %s\n", ch, optarg);  
                time = atoi(optarg);
                break;  
            case 'h':  
                printf("选项是%c\n", ch);  
                printf("-p 内存百分比\n");   
                printf("-t 保留时间(秒)\n");  
                printf("-h");  
                break;  
            default:  
                printf("other option: %c\n", ch);  
                break;  
        }  
    }  
    struct sysinfo s_info;
    int error;

    error = sysinfo(&s_info);
    printf("\n\ncode error=%d\n",error);
    printf( "RAM: total %lu / free %lu /shared%lu\n Memory in buffers = %lu\nSwap:total%lu/free%lu\n",
           s_info.totalram, s_info.freeram,s_info.totalswap, s_info.freeswap);



    int64_t used = static_cast<int64_t>(percent * static_cast<double>(s_info.totalram));
    printf("used : %lu\n",used);
    char *pChar = new char[used];
    memset(pChar,1,used);
    sleep(time);

    error = sysinfo(&s_info);
    printf("RAM: total %lu / free %lu /shared%lu\n Memory in buffers = %lu\nSwap:total%lu/free%lu\n",
           s_info.totalram, s_info.freeram,s_info.totalswap, s_info.freeswap);

    delete pChar;

    return 0;
}