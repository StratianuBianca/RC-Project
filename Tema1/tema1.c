#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/stat.h>
#include<time.h>
#include<errno.h>
#include<sys/socket.h>
//int conectat=0;
char home[]="/home/seby";
int isf(char *cale){
    struct stat st;
    if(0!=stat(cale, &st)){
        if(errno==ENOENT)
            return 2;
    }
    if((st.st_mode&S_IFMT)==S_IFDIR)
        return 1;
return 0;
}
int find(char *cale, char *numef, char rezultat[]){
    DIR *dir;
    struct dirent *de;
    char nume[256];
    int ok;
    if((ok=isf(cale))==0)
        return 0;
    if(NULL==(dir=opendir(cale))){
        if(errno==ENOENT)
            return 0;
    }
    while(NULL!=(de=readdir(dir))){
        if(strcmp(de->d_name, numef)==0){
            char *afis;
            afis=nume+strlen(home);
            strcpy(rezultat, "Am gasit ");
            strcat(rezultat, de->d_name);
            strcat(rezultat, " , iar calea este ");
            strcat(rezultat, cale);
            //printf("Am gasit %s/%s\n", cale, de->d_name);
            strcat(rezultat, "\n");
            struct stat fis;
            char s[256];
            strcpy(s, de->d_name);
            if((stat(s, &fis))<0){
                printf("Eroare\n");
                exit(4);
            }

            char c[256];
        strcat(rezultat, "\n");
            sprintf(c, "Detalii despre fisier:    \n\n Dimensiunea:           \t%lu bytes\n Data modificarii: \t%s\n Data ultimei accesari: \t%s\n", fis.st_size,ctime(&fis.st_mtime), ctime(&fis.st_atime));
            strcat(rezultat, c);
	    //printf("daa");
	    //printf("%s", rezultat);
            strcat(rezultat, "Permisiuni ");
            int k=0;
            if(S_ISDIR(fis.st_mode)){
                strcat(rezultat, "d");
                }
            else{
                strcat(rezultat, " - ");
                }
            if(fis.st_mode & S_IRUSR){
                strcat(rezultat, " r ");
                k=k+4;
                }
            else{
                strcat(rezultat, " - ");
                }
           if(fis.st_mode &S_IWUSR){
                strcat(rezultat, " w ");
                k=k+2;
                }
            else{
                strcat(rezultat, " - ");
                }
            if(fis.st_mode &S_IXUSR){
                k=k+1;
                strcat(rezultat, " x ");
                }
            else{
                strcat(rezultat, " - ");
                }
                char nr[5]="0";
                //nr[0]='0'+0;
                nr[1]='0'+k;
                k=0;
            if(fis.st_mode &S_IRGRP){
                strcat(rezultat, " r ");
                k=k+4;
                }
            else{
                strcat(rezultat, " - ");
                }
            if(fis.st_mode & S_IWGRP){
                strcat(rezultat, " w ");
                k=k+2;
                }
            else{
                strcat(rezultat, " - ");
                }
            if(fis.st_mode & S_IXGRP){
                strcat(rezultat, " x ");
                k=k+1;
                }
            else{
                strcat(rezultat, " - ");
                }
                nr[2]='0'+k;
                k=0;
            if(fis.st_mode & S_IROTH){
                strcat(rezultat, " r ");
                k=k+4;
                }
            else{
                strcat(rezultat, " - ");
                }
            if(fis.st_mode & S_IWOTH){
                strcat(rezultat, " w ");
                k=k+2;
                }
            else{
                strcat(rezultat, " - ");
                }
            if(fis.st_mode & S_IXOTH){
                strcat(rezultat, " x ");
                k=k+1;
                }
            else{
                strcat(rezultat, " - ");
                }
                nr[3]='0'+k;
                strcat(rezultat , nr);
        strcat(rezultat, "\n");
//printf("%s", rezultat);
            }

        find(nume, numef, rezultat);
    }

    return 1;
}
void quit(char mesaj[256], char rezultat[256]){
    strcpy(rezultat, mesaj);
    rezultat[strlen(rezultat)-1]='\0';
}
void logare(char mesaj[], char rezultat[], int *conectat, char parola[]){
    char user[256];
    strcpy(user, mesaj+8);
    user[strlen(user)-1]='\0';
    FILE* fin=fopen("utilizatori", "r");
    int ok=0;
    char nume[256];
    int nr=0;
    if(fin!=NULL){
    while(fgets(nume, 256, fin)!=NULL){
        nume[strlen(nume)-1]='\0';
        if(strcmp(nume, user)==0){
            ok=1;
            break;
        }
	nr++;
    }
}
    int ok2=0;
    char pas[256];
    int nr2=0;
    parola[strlen(parola)-1]='\0';
    FILE* f=fopen("parole", "r");
    while(fgets(pas, 256, f)!=NULL){
	pas[strlen(pas)-1]='\0';
	if(strcmp(pas, parola)==0){
	    ok2=1;
	    if(nr==nr2){
		break;
}	
	    else{
	    ok2=0;
}
}
nr2++;
}
    if(ok==1){
	if(ok2==1){
        *conectat=1;
        char rezultat1[]="Acum esti conectat!";
        strcpy(rezultat, rezultat1);
}
    else{
	*conectat=0;
	char rezultat1[]="Ai gresit parola!";
	strcpy(rezultat, rezultat1);
}
    }
    else{
//        *conectat=0;
        char rezultat2[]="Utilizator respins!";
        strcpy(rezultat, rezultat2);
    }
}
void verifica(char mesaj[256], int *nr){
    *nr=0;
    int ok=1;
    char log[]="login : ";
    char find[]="myfind ";
    char stat[]="mystat ";
    char quit[]="quit";
    char fil[]="file ";
    int i;
    for(i=0;i<strlen(log);i++){
        if(log[i]!=mesaj[i])
            ok=0;
    }
    if(strlen(mesaj)<=strlen(log))
        ok=0;
    if(ok==1){
        *nr=1;
        return;
    }
    ok=1;
    for(i=0;i<strlen(find);i++){
        if(find[i]!=mesaj[i])
            ok=0;
    }
    if(strlen(mesaj)<=strlen(find))
        ok=0;
    if(ok==1){
        *nr=2;
        return;
    }
    ok=1;
    for(i=0;i<strlen(stat);i++){
        if(mesaj[i]!=stat[i])
            ok=0;
        }
    if(strlen(mesaj)<=strlen(stat)){
        ok=0;
    }
    if(ok==1){
        *nr=3;
        return;
    }
    ok=1;
    for(i=0;i<strlen(quit);i++){
        if(mesaj[i]!=quit[i])
            ok=0;
    }
//    if(strlen(mesaj)>strlen(quit)){
//      ok=0;
//    }
    if(ok==1){
        *nr=4;
        return;
    }
    ok=1;
    for(i=0;i<strlen(fil);i++){
	if(mesaj[i]!=fil[i])
	    ok=0;
}
    if(strlen(mesaj)<=strlen(stat))
	ok=0;
    if(ok==1){
	*nr=5;
	return;
    }
    printf("comanda gresita\n");
    return;
}
void mstat(char rezultat[], char* nume){
    //printf("daaa");
    char eroare[]="Fisierul nu exista";
    struct stat fis;
    if((stat(nume, &fis))<0){
        strcpy(rezultat, eroare);
        return ;
    }
    else{
/*    strcpy(rezultat, "Detalii despre fisier: Dimensiunea :");
    strcat(rezultat, fis.st_size);
    strcat(rezultat, " Numarul de link-uri: ");
    strcat(rezultat, fis.st_nlink);
    strcat(rezultat, " Seria fisierului: ");
    strcat(rezultat, fis.st_ino);
    strcat(rezultat, " Data ultimei accesari: ");
    strcat(rezultat, ctime(&fis.st_atime));
    strcat(rezultat," Data ultimei modificari: " );
    strcat(rezultat, ctime(&fis.st_mtime));
    strcat(rezultat, " ");
    }*/
    char rez1[10000];
  sprintf(rez1, "Detalii despre fisier: \n\n  Dimensiunea fisierului: \t%lu\n Numarul de link-uri: \t%lu\n I-nodul: \t%lu\n Ultima accesare: \t%s\nUltima modificare:  \t%s\n Ultimul status modificat \t%s\n\n UID: \t%d\n GID: \t%d\n UID device: \t%lu\n Block I/0: \t%lu\n Block: \t%lu\n ", fis.st_size, fis.st_nlink, fis.st_ino, ctime(&fis.st_atime), ctime(&fis.st_mtime),ctime(&fis.st_ctime), fis.st_uid, fis.st_gid, fis.st_dev, fis.st_blksize, fis.st_blocks);
    //sprintf(rez1, "Detalii despre fisier: \n \n Dimensiunea fisierului: \t

//    strcat(rez1, "Permisiuni");
    strcpy(rezultat, rez1);
    strcat(rezultat, "Permisiuni  ");
    char nr[5]="0";
//    nr[0]='0'+0;
    int k=0;
    if(S_ISDIR(fis.st_mode)){
        strcat(rezultat, "director");
    }

    else{
        strcat(rezultat, "-");
    }
    if(fis.st_mode & S_IRUSR){
        strcat(rezultat, "r");
        k=k+4;
    }
    else{
        strcat(rezultat, "-");
    }
    if(fis.st_mode & S_IWUSR){
        strcat(rezultat, "w");
        k=k+2;
    }
    else{
        strcat(rezultat, "-");
    }
    if(fis.st_mode & S_IXUSR){
        strcat(rezultat, "x");
        k=k+1;
    }
    else{
        strcat(rezultat, "-");
    }
    nr[1]='0'+k;
    k=0;
    if(fis.st_mode & S_IRGRP){
        strcat(rezultat, "r");
    k=k+4;
    }
    else{
    strcat(rezultat, "-");
    }
    if(fis.st_mode & S_IWGRP){
        strcat(rezultat, "w");
    k=k+2;
    }
    else{
        strcat(rezultat, "-");
    }
    if(fis.st_mode & S_IXGRP){
        strcat(rezultat, "x");
    k=k+1;
    }
    else{
        strcat(rezultat, "-");
    }
    nr[2]='0'+k;
    k=0;
    if(fis.st_mode & S_IROTH){
        strcat(rezultat, "r");
        k=k+4;
        }
    else
        strcat(rezultat, "-");
    if(fis.st_mode & S_IWOTH){
        strcat(rezultat, "w");
    k=k+2;
    }
    else{
        strcat(rezultat, "-");
    }
    if(fis.st_mode &S_IXOTH){
        strcat(rezultat, "x");
    k=k+1;
    }
    else{
        strcat(rezultat, "-");
        }
        nr[3]='0'+k;
        strcat(rezultat, "->");
        strcat(rezultat, nr);
    strcat(rezultat, "\n");
    if(S_ISDIR(fis.st_mode)){
        strcat(rezultat, "Fisierul este un director");
    }
    else
        if(S_ISFIFO(fis.st_mode))
            strcat(rezultat, "Este un fisier FIFO");
            else
            if(S_ISLNK(fis.st_mode))
                strcat(rezultat, "Este un link symbolic");
                else
                if(S_ISREG(fis.st_mode))
                    strcat(rezultat, "Fisierul este unul regular");	
                    else
                    if(S_ISSOCK(fis.st_mode))
                        strcat(rezultat,"Fisierul este un socket");
                        else
                        if(S_ISBLK(fis.st_mode))
                            strcat(rezultat, "Fisierul este un dispozitiv blocant");
                            else
                            if(S_ISCHR(fis.st_mode))
                                strcat(rezultat, "Fisierul este un dispozitiv de caractere");
                                else
                                if(S_ISDIR(fis.st_mode))
                                    strcat(rezultat, "Fisierul este un director");
                                    else
                                        strcat(rezultat, "Nu am putut gasi tipul fisierului");

//    printf(rezultat);
}
strcat(rezultat, "\n");
}
void fill(char rezultat[], char f[]){
    struct stat fis;
    if((stat(f, &fis))<0){
	strcpy(rezultat, "Fisierul nu exista");
	return;
}
    
 if(S_ISDIR(fis.st_mode)){
        strcat(rezultat, "Fisierul este un director");
    }
    else
        if(S_ISFIFO(fis.st_mode))
            strcat(rezultat, "Este un fisier FIFO");
            else
            if(S_ISLNK(fis.st_mode))
                strcat(rezultat, "Este un link symbolic");
                else
                if(S_ISREG(fis.st_mode))
                    strcat(rezultat, "Fisierul este unul regular");	
                    else
                    if(S_ISSOCK(fis.st_mode))
                        strcat(rezultat,"Fisierul este un socket");
                        else
                        if(S_ISBLK(fis.st_mode))
                            strcat(rezultat, "Fisierul este un dispozitiv blocant");
                            else
                            if(S_ISCHR(fis.st_mode))
                                strcat(rezultat, "Fisierul este un dispozitiv de caractere");
                                else
                                if(S_ISDIR(fis.st_mode))
                                    strcat(rezultat, "Fisierul este un director");
                                    else
                                        strcat(rezultat, "Nu am putut gasi tipul fisierului");
return;

}
int main(){
int con=0;
char uss[256];
while(1){
//printf("%d", conectat);
    char mesaj[256], rezultat[256];
    int nr=0;
    //pipe(proc1);
    //int proc1[0], proc1[1];
    //FILE* fin=fdopen(proc1[0],"r");
    //FILE* fin=fdopen(proc1[1],"w");
    char numef[]="fifo";
    remove(numef);
    if(mkfifo(numef, 0666)==-1){
	printf("Eroare la fifo");
    exit(5);
}
    if(con==0){
        printf("Momentan nu esti conectat, poti alege din urmatoarele comenzi: 'login', 'quit'\n");

    }
    else{
        if(con==1){
            printf("Poti alege din urmatoarele comenzi: 'myfind', 'mystat', 'file', 'quit'\n");

        }
        }
    fgets(mesaj, 256, stdin);
    verifica(mesaj, &nr);
    pid_t pid;
    int pfd[2], pfd1[2];
    int fd,f;
    int sockp[2];
    int sockp1[2];

    if(socketpair(AF_UNIX, SOCK_STREAM, 0, sockp)<0){
        printf("Eroare la socketpair\n");
        exit(2);
    }
    if(socketpair(AF_UNIX, SOCK_STREAM,0, sockp1)<0){
        printf("Eroare la al 2 lea socketpair\n");
        exit(3);
    }
    if(pipe(pfd)==-1){
        printf("Eroare la pipe\n");
    }
    if(pipe(pfd1)==-1)
	printf("Eroare la pipe\n");
    int lungime;
    pid=fork();
    if(pid<0){
        printf("Eroare la fork()\n");
    }
    //printf("%d",nr);
    if(pid==0){//copil,
    close(pfd[0]);
    close(sockp[0]);
    close(sockp1[0]);
    close(pfd1[0]);

    //printf("daaa");
        if(nr==1){
	    char parola[256];
	    printf("Scrie parola:");
	    
	    fgets(parola, 256, stdin);
            logare(mesaj, rezultat, &con, parola);
	    if(con==1){
		strcpy(uss, mesaj);
	//	printf("%s", mesaj);
		strcpy(uss, uss+8);
}
	    //printf("%d", con);
            //rezultat[strlen(rezultat)-1]='\0';
            lungime=strlen(rezultat);
            printf("%s",uss);
            write(sockp[1], &lungime, sizeof(int));
            write(sockp[1], rezultat, lungime);
	    write(sockp[1], &con, sizeof(int));
        }
        if(nr==2){
    if(con==1){
            char f[256];
            strcpy(f, mesaj+7);
            f[strlen(f)-1]='\0';
	    //printf("daaa");
            char home[]="/home/seby";
            find(home, f, rezultat);
            rezultat[strlen(rezultat)]='\0';
            lungime=strlen(rezultat);
            write(pfd[1], &lungime, sizeof(int));
            write(pfd[1], rezultat, lungime);
            //rezultat[strlen(rezuultat)-1]='\0';
        //    printf("%s",rezultat);
        //    printf("\n");
}
	else{
	    strcpy(rezultat, "Momentan nu poti folosi aceasta functie\n");
	    lungime=strlen(rezultat);
	    write(pfd[1],&lungime, sizeof(int));
	    write(pfd[1], rezultat, lungime);
}
        }
//printf("daa");
        if(nr==3){
if(con==1){
            char f[256];
char rezultat[100000];
            strcpy(f, mesaj+7);
            f[strlen(f)-1]='\0';
            //printf("daaaa");
            //printf("%s",f);
            mstat(rezultat, f);
            //printf(rezultat);
            lungime=strlen(rezultat);
            write(sockp1[1], &lungime, sizeof(int));
            write(sockp1[1], rezultat, lungime);
}
	else{
	    strcpy(rezultat,"Momentat nu poti folosi aceasta functie\n");
	    lungime=strlen(rezultat);
	    write(sockp1[1], &lungime, sizeof(int));
	    write(sockp1[1], rezultat, lungime);
}
        }
	if(nr==5){
	    if(con==1){
		char f[256];
		strcpy(f, mesaj+5);
		f[strlen(f)-1]='\0';
		fill(rezultat, f);
}
	    else{	
		strcpy(rezultat, "Momentan nu poti folosi aceasta functie");
}
	    lungime=strlen(rezultat);
	    write(pfd1[1], &lungime, sizeof(int));
	    write(pfd1[1], rezultat, lungime);

}
        if(nr==4){
            //close(pfd[0]);
            quit(mesaj, rezultat);
            lungime=strlen(rezultat);
            f=open(numef, O_WRONLY);
            write(f, &lungime, sizeof(int));
            write(f, rezultat, lungime);
//printf("%s",rezultat);
        //    if(n==-1){
        //        printf("Eroare la scrierea in FIFO\n");
        //    }
            //write(pfd[1], &lungime, sizeof(int));
            //write(pfd[1], rezultat, lungime);
        }
	exit(0);


    }
    else{//parinte
    char rezultat[256];
    close(pfd[1]);
    close(sockp[1]);
    close(sockp1[1]);
    close(pfd1[1]);
    if(nr==1){
        if(read(sockp[0], &lungime, sizeof(int))<0){
            printf("Eroare la citire\n");
        }
        read(sockp[0], rezultat, lungime);
	rezultat[lungime]='\0';
	read(sockp[0], &con, sizeof(int));
        printf("%s",rezultat);
        printf("\n");
    }
    if(nr==2){
        read(pfd[0], &lungime, sizeof(int));
        read(pfd[0], rezultat, lungime);
        rezultat[lungime]='\0';
        printf("%s",rezultat);
//printf(rezultat);
        printf("\n");
    }
    if(nr==3){
    if(read(sockp1[0],&lungime, sizeof(int))<0){
        printf("Eroare la citire\n");
    }
    read(sockp1[0], rezultat, lungime);
    rezultat[lungime]='\0';
    printf("%s",rezultat);
    }
    if(nr==5){
	read(pfd1[0], &lungime, sizeof(int));
	read(pfd1[0], rezultat, lungime);
	rezultat[lungime]='\0';
	printf("%s", rezultat);
	printf("\n");

}
//printf("%d", conectat);
    if(nr==4){
//FILE *outp;
        //read(pfd[0], &lungime, sizeof(int));
        //read(pfd[0], rezultat, lungime);
    //    mknod("fifo_n", S_IFIFO | 0666, 0);
        f=open(numef, O_RDONLY);
        read(f, &lungime, sizeof(int));
        read(f, rezultat, lungime);
        //if(n0==-1)
        //    printf("Eroare la citirea din FIFO\n");

        rezultat[lungime]='\0';
        //printf("%s",rezultat);
        printf("La revedere\n");
//	wait(NULL);
	close(f);
	return 0;
        exit(1);
    }


    }
}
    return 0;

}