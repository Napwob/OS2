#include <cmath>
#include <iostream>
#include <sys/time.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <dirent.h>
#include <fcntl.h> 
#include <pwd.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>   
#include <unistd.h>
#include <malloc.h>
using namespace std;

long sizf(char *fname) {
  long size = 0;

  int descriptor = open(fname, O_RDONLY);

  if (descriptor != -1) {
    FILE *file = fdopen(descriptor, "rb");

    if (file) {
      struct stat statistics;

      if (fstat(descriptor, &statistics) != -1) {
        if (S_ISDIR(statistics.st_mode)) {

          DIR *dir;
          struct dirent *ent;
          if ((dir = opendir(fname)) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
              if (!((strcmp(ent->d_name, ".") == 0) ||
                    (strcmp(ent->d_name, "..") == 0))) {
                char buf_path[256] = "";
                strcat(buf_path, fname);
                strcat(buf_path, "/");
                strcat(buf_path, ent->d_name);
                size += sizf(buf_path);
              }
            }
            closedir(dir);
          }
          printf("Size of %s = %ld bytes\n", fname, size);
          return size;
        }
        size = statistics.st_size;
        printf("Size of %s = %ld bytes\n",fname, statistics.st_size);
      }
      fclose(file);
    }
    close(descriptor);
  } 

  return size;
}


int shop() {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir("/proc/")) != NULL) {
    printf("UID\tPID\tPPID\tC\tTIME\tSTIME\tCMD\n");
    while ((ent = readdir(dir)) != NULL) {
      if (atoi(ent->d_name) != 0) {
        char pwd[256] = "/proc/";
        strcat(pwd, ent->d_name);

        FILE *tmp;
        char pwd_tmp[256] = "";
        strcat(pwd_tmp, pwd);
        tmp = fopen(strcat(pwd_tmp, "/loginuid"), "r");
        if (!tmp) {
          return 1;
        }
        int uid;
        if (fscanf(tmp, "%d", &uid) == EOF) {
          return 1;
        }
        if (uid < 0)
          uid = 0;
        struct passwd *newPasswd;

        newPasswd = getpwuid(uid);
        
        char *name =(char *)malloc(sizeof(char) * 256);
        strcpy(name, newPasswd->pw_name);

        int pid;
        int ppid;
        long c;
        unsigned long time;
        unsigned long stime;
        char *cmd = (char *)malloc(sizeof(char) * 256);

        strcpy(pwd_tmp, pwd);
        tmp = fopen(strcat(pwd_tmp, "/stat"), "r");
        if (!tmp) {
          return 1;
        }

        int buf1;
        long buf2;
        char buf3;
        char buf4[256];
        if (fscanf(tmp,
                   "%d %s %c %d %d %d %d %d %lu %lu %lu %lu %lu %lu %lu %ld "
                   "%ld %ld %ld",
                   &pid, buf4, &buf3, &ppid, &buf1, &buf1, &buf1, &buf1, &buf2,
                   &buf2, &buf2, &buf2, &buf2, &time, &stime, &buf2, &buf2,
                   &buf2, &c) == EOF) {
          return 1;
        }
        fclose(tmp);

        strcpy(pwd_tmp, pwd);
        tmp = fopen(strcat(pwd, "/cmdline"), "r");
        if (!tmp) {
          return 1;
        }
        if (fscanf(tmp, "%s", cmd) == EOF) {
          cmd = "";
        }

        printf("%s\t%d\t%d\t%ld\t%lu s\t%lu s\t%s\n", name, pid, ppid, c,
               time / sysconf(_SC_CLK_TCK), stime / sysconf(_SC_CLK_TCK), cmd);
      }
    }
    closedir(dir);
  } else {
    return -1;
  }
  return 0;
}

void delf(char *fname)
{
	remove(fname);
}

void copf(char *fname, char *fnamed)
{
	ifstream cfile;
	cfile.open(fname);
	
	ofstream cfilep;
	cfilep.open(fnamed);
	
	string a;	
	
	while(true)
	{
		getline(cfile, a, '\n');
		if(a[0] == NULL ) break;
		cfilep<< a<<endl;
		
		a[0]=NULL;	
	}	
			
}

void movf(char *fname, char *fnamed)
{	
	//char *wh;
	//strcat (wh, fnamed);
	//strcat (fnamed, fname);
	copf(fname, fnamed);
	delf(fname);
}

void shof(char *fname)
{
	if (auto dir = opendir(fname)) {
	    while (auto f = readdir(dir)) {
	        if (!f->d_name || f->d_name[0] == '.')
	            continue; // Skip everything that starts with a dot
	
	        printf("%s\n", f->d_name);
	    }
	    closedir(dir);
	}	
}

void spravka() {
cout<<"Авторы: Русманов Владислав ИВ-822, Крюков Илья ИВ-822, Сысоева Анастасия ИВ-822"<<endl;
cout<<"Краткое описание проекта:"<<endl;
cout<<"Данная программа позволяет выполнять простейшие действия по работе с файловой системой"<<endl;
cout<<"    Если ввести ключ--help или -h, то выведится справка"<<endl;
cout<<"    -d 'название файла' - Удаление указанного файла "<<endl;
cout<<"    -с 'название нужного файла' 'новое имя файла' - Копирование указанного файла" <<endl;
cout<<"    -m 'название нужного файла' 'путь перемещения с указанием нужного файла' - Перемещене файла "<<endl;
cout<<"    -w 'указать директорию' - Вывод всех файлов в директории"<<endl;
cout<<"    -p Отображение всех процессов из файловой системы procfs"<<endl;
cout<<"    -s Подсчет общего размера указанной директории или файла"<<endl;
cout<<"Все доступные аргументы:"<<endl;
cout<<"    --help"<<endl;
cout<<"    -h"<<endl;
cout<<"    -d"<<endl;
cout<<"    -c"<<endl;
cout<<"    -m"<<endl;
cout<<"    -w"<<endl;
cout<<"    -p"<<endl;
cout<<"    -s"<<endl;
cout<<"Примеры запуска:"<<endl;
cout<<"    ./lab —help"<<endl;
cout<<"    ./lab -h"<<endl;
cout<<"    ./lab -d prog.cpp"<<endl;
cout<<"    ./lab -c lab2.cpp lab.cpp"<<endl;
cout<<"    ./lab -m lab.cpp dir/lab.cpp"<<endl;
cout<<"    ./lab -w dir"<<endl;
cout<<"    ./lab -p"<<endl;
cout<<"    ./lab -s dir"<<endl;
}


int main(int argc, char *argv[])
{
	//argv[1]="-d";
	//argv[2]="main";
	//argv[3]="";
	
if (strcmp(argv[1],"-d")==0) delf(argv[2]);

if (strcmp(argv[1],"-c")==0) copf(argv[2], argv[3]);

if (strcmp(argv[1],"-m")==0) movf(argv[2], argv[3]);
	
if (strcmp(argv[1],"-w")==0) shof(argv[2]);

if (strcmp(argv[1],"-p")==0) shop();

if (strcmp(argv[1],"-s")==0) sizf(argv[2]);
    
if (strcmp(argv[1],"-h")==0) spravka();
    
if (strcmp(argv[1],"--help")==0) spravka();
		
return 0;	
}



