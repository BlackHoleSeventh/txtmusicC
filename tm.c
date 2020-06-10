#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <direct.h>
#include <mmsystem.h>

#include <fcntl.h>  
#include <process.h> 

#define MAXPATH  1024 

int hpipe[2] = {0,0};

void setbgm(int b)
{
	int bgm=b;
	hpipe[0] = bgm;
	//printf("%d\n",bgm);
}
 
 
void main(int argc,char *argv[]){
	 
	 system("mode con cols=100 lines=3");
	 system("color F1");
	 if(argv[1] == NULL){
       printf("txt音乐地址不能为空！\n");
       system("pause");
       return; 
 	 }
	 if(argv[2] == NULL){
       printf("间隔时间不能为空！\n");
       system("pause");
       return; 
 	 }
 	 
	 printf("%s %s\n", argv[1], argv[2]);
	 void begin(char url[],int sleepTime);
	 
	 int st  = atoi(argv[2]);
	 
	 if(st<=0 || st>5000){
	 	printf("%d\n",st);
	 	st = 500;	
 	 }
	 
	 begin(argv[1], st);	
	 return;
	 
}


void begin(char url[],int sleepTime){
	//#pragma comment (lib , "winmm.lib")
	//char type;
	char tp[2] = {NULL,'\0'};	
	//char level;
	char lv[2] = {NULL,'\0'};
	
	/*	
	printf("%c", *tp);
	tp = "a";
	printf("%c", *tp);
	tp = "b";
	printf("%c", *tp);
	*/
	
	int* st = &sleepTime; 
	
	/*	
	printf("%d", *st);
	*st = 200;
	printf("%d", *st);
	*st = 300;
	printf("%d", *st);
	*/
	
	void choose(char c, char* tp, char* lv, int* st); 
	void play(char c, char* tp, char* lv, int* st);
   		 
	int isPlay = 1;
	int current = 0; 
	
	char c;
	
	FILE *f = fopen(url, "r");
	if(f == NULL){
		printf("不能打开文件!\n");
		system("pause"); 
		return 1;
	}
	
	while(!feof(f)){
		
	  c = fgetc(f);
	  //printf("%c", c);
	  
	  if(isPlay){
	  	 
		 current++ ;
         choose(c, tp, lv, st);
      }
      else{
          break;
      }
	  
	}
	

	fclose(f);
	
return 0;	
}

void choose(char c, char* tp, char* lv, int* st){
	void play(char c, char* tp, char* lv, int* st); 
	
     //printf("%c",c);
     
	 /*
	 printf("1");
	 printf("%c", *tp);
	 printf("%c", *lv);
	 printf("%d", *st);
	 printf("2");
	 */
	    char c2[2] = {c, '\0'};
	    
        if(strstr("#",c2)){
            tp[0] = 'b';
            return;
        }

        if(strstr("\r",c2)){
            return;
        }

        if(strstr(" ",c2)){
            Sleep(*st);
            return;
        }

        if(strstr("1234567",c2)){
        	//HANDLE hThread = (HANDLE)_beginthreadex(NULL,0,play,NULL,0,NULL);
            play(c, tp, lv, st);
            tp[0] = '\0';
        }else if(strstr(c2,"(")){
            lv[0] = 'd';
        }else if(strstr(c2,")")){
            lv[0] = 'z';
        }else if(strstr(c2,"[")){
            lv[0] = 'g';
        }else if(strstr(c2,"]")){
            lv[0] = 'z';
        }else{
            //否则不处理
        }	
}


void play(char c, char* tp, char* lv, int* st){
	 
    //获取当前路径 
	char buffer[MAXPATH];
    _getcwd(buffer,MAXPATH);  
    //printf("%s",buffer);  
    
	//获取目标文件名 
    char type[2] = {tp[0],'\0'};
    char level[2] = {lv[0],'\0'};
    char c2[2] = {c,'\0'};
    
	strcat(buffer, "\\");
	strcat(buffer, "wavFile");
	strcat(buffer, "\\");
    strcat(buffer, type);
    strcat(buffer, level);
    strcat(buffer, c2);
    strcat(buffer, ".wav");
   
    //播放文件 
	//printf("%s\n", buffer); 
	
	
     char url[MAXPATH];
     strcat(url, "play ");
     strcat(url, buffer);
 	 		
	switch(hpipe[0])
		{
		//子程序退出
		case -1:exit(0);
		case  0:setbgm(1);PlaySound(buffer, NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT);break;
		case  1:setbgm(0);mciSendString(TEXT(url), NULL, 0, NULL);break;
		/*
		case  2:setbgm(3);PlaySound(buffer, NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT);break;
		case  3:setbgm(4);PlaySound(buffer, NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT);break;
		case  4:setbgm(5);PlaySound(buffer, NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT);break;
		case  5:setbgm(6);PlaySound(buffer, NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT);break;
		case  6:setbgm(7);PlaySound(buffer, NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT);break;
		case  7:setbgm(8);PlaySound(buffer, NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT);break;
		case  8:setbgm(9);PlaySound(buffer, NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT);break;
		case  9:setbgm(10);PlaySound(buffer, NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT);break;
		case  10:setbgm(0);PlaySound(buffer, NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT);break;
		*/
		}
	memset(url, 0, sizeof url); 
	 	
     /* 
     char ourl[MAXPATH];
     strcat(ourl, "open ");
     strcat(ourl, buffer);
     mciSendString(TEXT(ourl), NULL, 0, NULL);
     memset(ourl, 0, sizeof url); 
	*/
     /*
     char url[MAXPATH];
     strcat(url, "play ");
     strcat(url, buffer);
     mciSendString(TEXT(url), NULL, 0, NULL);
 	 printf("%s\n",url);
	 memset(url, 0, sizeof url); 
	 */

	//mciSendString("play Data\\1.wav",NULL,0,NULL);
	//printf("%c,%c", tp[0], lv[0]);   
	//printf("%c", c);
}
