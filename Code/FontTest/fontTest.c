#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

void Get_GBK_DZK(uint8_t *code);

FILE *fd;

int main(void){  
	//字库所在目录
	if(NULL == (fd=fopen("./ziku.bin","rb"))){
		printf("Open dir error\r\n");
	}
    Get_GBK_DZK("你");
    printf("\r\n");
	Get_GBK_DZK("好");
    printf("\r\n");
	Get_GBK_DZK("！");
	fclose(fd);
	
}

//得到字模 
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
	
	//获取字符在bin文件中的偏移量
    offset=((uint32_t)192*GBKH+GBKL)*32;
	
    if((-1 ==fseek(fd,offset,SEEK_SET))){
    	printf("Fseek error\r\n"); 
	}
	//得到字符指针
	fread(character,1,32,fd);
	characterPtr = character;
	//显示字符
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