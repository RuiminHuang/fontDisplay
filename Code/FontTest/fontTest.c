﻿#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

void Get_GBK_DZK(uint8_t *code);

FILE *fd;

int main(void){  
	//�ֿ�����Ŀ¼
	if(NULL == (fd=fopen("./ziku.bin","rb"))){
		printf("Open dir error\r\n");
	}
    Get_GBK_DZK("��");
    printf("\r\n");
	Get_GBK_DZK("��");
    printf("\r\n");
	Get_GBK_DZK("��");
	fclose(fd);
	
}

//�õ���ģ 
void Get_GBK_DZK(uint8_t *code){
	uint8_t GBKH,GBKL;                 
    uint32_t offset;
	uint8_t  character[32]={0};
	uint8_t* characterPtr;
	
    GBKH=*code;
    GBKL=*(code+1);
	
    if(GBKH>0XFE||GBKH<0X81){
		return;
	}
    GBKH-=0x81;
    GBKL-=0x40;
	
	//��ȡ�ַ���bin�ļ��е�ƫ����
    offset=((uint32_t)192*GBKH+GBKL)*32;
	
    if((-1 ==fseek(fd,offset,SEEK_SET))){
    	printf("Fseek error\r\n"); 
	}
	//�õ��ַ�ָ��
	fread(character,1,32,fd);
	characterPtr = character;
	//��ʾ�ַ�
	int i,j;
	for(j=0; j<16; j++){
		for(i=0; i<16; i++){
			if(*characterPtr &(0x80>>(i % 8))){
				printf("*");
			}else{
				printf(" ");
			}
			if(i%8 == 7){
				characterPtr++;
			}
		}
		printf("\r\n");
	}
}