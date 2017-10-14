// encfile.cpp : Defines the entry point for the console application.
// Linux: gcc -o cryptoDemo cryptoDemo.cpp -lcrypto
//suthor: SA17011009 陈伟

#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "openssl/aes.h"

#pragma comment(lib,"libeay32.lib")

void EncAes(char inString[], int inLen, char passwd[], int pwdLen)
{
	int i,j, len, nLoop, nRes;
	char enString[1024];//加密后保存密文的数组

	unsigned char buf[16];
	unsigned char buf2[16];
	unsigned char aes_keybuf[32];
	AES_KEY aeskey;

	// 准备32字节(256位)的AES密码字节
	memset(aes_keybuf,0x90,32);//memset函数，让aes_keybuf的32位都初始化为0x90
	//如果加密串的长度pwdLen小于32，就取len为pwdLen，如果大于就取32
	if(pwdLen<32){ len=pwdLen; } else { len=32;}	
	//让aes_keybuf的前len位都被赋值为passwd中的字符
	for(i=0;i<len;i++) aes_keybuf[i]=passwd[i];	
	// 输入字节串分组成16字节的块，最后一块不一定等于16，需要取余数
	nLoop=inLen/16; nRes = inLen%16;	
	// 加密输入的字节串，调用函数AES_set_encrypt_key
	AES_set_encrypt_key(aes_keybuf,256,&aeskey);
	for(i=0;i<nLoop;i++){
		memset(buf,0,16);
		for(j=0;j<16;j++) buf[j]=inString[i*16+j];
		AES_encrypt(buf,buf2,&aeskey);//加密函数
		for(j=0;j<16;j++) enString[i*16+j]=buf2[j];
	}
	
	if(nRes>0){
		memset(buf,0,16);
		for(j=0;j<nRes;j++) buf[j]=inString[i*16+j];
		AES_encrypt(buf,buf2,&aeskey);
		for(j=0;j<16;j++) enString[i*16+j]=buf2[j];
		
	}
	enString[i*16+j]=0;
	
	FILE *fp = fopen("encrypted", "w+");
    if (fp==0) {
        printf("“encrypted file can not open”\n");
		exit(0);
        }
	
        fwrite(enString, sizeof(char)*strlen(enString), 1, fp);
        fclose(fp);
        printf("The original string is:\n  %s \n", inString);
		printf("The encrypted string is:\n  %s \n", enString);
	
}
	// 密文串的解密
void DecAes(char inString[], int inLen, char passwd[], int pwdLen)
{	
	int i,j, len, nLoop, nRes;
	char deString[1024];//解密后保存原文的数组
	
	unsigned char buf[16];
	unsigned char buf2[16];
	unsigned char aes_keybuf[32];
	AES_KEY aeskey;

	// 准备32字节(256位)的AES密码字节
	memset(aes_keybuf,0x90,32);
	if(pwdLen<32){ len=pwdLen; } else { len=32;}
	for(i=0;i<len;i++) aes_keybuf[i]=passwd[i];
	// 输入字节串分组成16字节的块	
	nLoop=inLen/16; nRes = inLen%16;
	
	//下面才是具体解码
	AES_set_decrypt_key(aes_keybuf,256,&aeskey);
	for(i=0;i<nLoop;i++){
		memset(buf,0,16);
		//for(j=0;j<16;j++) buf[j]=enString[i*16+j];注意读取的加密文件函数参数名改为inString了
        for(j=0;j<16;j++) buf[j]=inString[i*16+j];
		AES_decrypt(buf,buf2,&aeskey);
		for(j=0;j<16;j++) deString[i*16+j]=buf2[j];
	}
	if(nRes>0){
		memset(buf,0,16);
		//for(j=0;j<16;j++) buf[j]=enString[i*16+j];注意读取的加密文件函数参数名改为inString了
        for(j=0;j<16;j++) buf[j]=inString[i*16+j];
		AES_decrypt(buf,buf2,&aeskey);
		for(j=0;j<16;j++) deString[i*16+j]=buf2[j];
		//puts("decrypt");
	}
	deString[i*16+nRes]=0;
	
    printf("The original string is:\n  %s \n", inString);
   	printf("The decrypted string is:\n  %s \n", deString);
	FILE *fp = fopen("decrypted", "w+");
    if (fp==0) {
        printf("“decrypted file can not open”\n");
		exit(0);
        }
	
    fwrite(deString, sizeof(char)*strlen(deString), 1, fp);
    fclose(fp);
	
}

char* FileOpen(char filename[])
{
	long flen;//读入文件长度
	char *enString;//读入文件内容
	
	//读取文件转换成字符串数组
	FILE *fp;
	fp=fopen(filename,"r");
	if(fopen==0){
		printf("“encrypted file can not open”\n");
		exit(0);
	}	
	
	//转换成字符串
	fseek(fp,0L,SEEK_END); /* 定位到文件末尾 */
	flen=ftell(fp); /* 得到文件大小 */
	enString=(char *)malloc(sizeof(char)*(flen+1)); /* 根据文件大小动态分配内存空间 */
	fseek(fp,0,SEEK_SET);
    fread(enString,flen,1,fp);
	
	return enString;
}


int main(int argc, char* argv[])
{
	char flag[3],filename[128],passwd[1024];
		
	printf("\nPlease input parameter1(enc/dec),parameter2(file name),parameter3(key):\n");
	scanf("%s%s%s",flag,filename,passwd);
		
	if(!FileOpen(filename)){//判断读入文件是否可用
		printf("File can not open!\n");
		exit(0);
	}
			
	if (strcmp(flag,"enc")==0){
            EncAes(FileOpen(filename), strlen(FileOpen(filename)), passwd, strlen(passwd));
		}
        else if (strcmp(flag,"dec")==0){
			DecAes(FileOpen(filename), strlen(FileOpen(filename)), passwd, strlen(passwd));
		}
        else {
               printf("error!!! \n");
               exit(0);
        }
	
	return 0;
}




	