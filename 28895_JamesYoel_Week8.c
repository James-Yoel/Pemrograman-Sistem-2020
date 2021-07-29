#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

char *cwd;
struct stat st = {0};

void makeDir(){
  char dirName[30];
  char test[255];
  //empty test array
  memset(test, 0, sizeof test);
  printf("Create name for new Directory : ");
  scanf("%s",dirName);
  //get current directory
  cwd = getcwd(NULL, 0);
  if(!cwd){
    perror("getcwd");
    exit(EXIT_FAILURE);
  }
  //make path
  strcat(test, cwd);
  strcat(test, "/");
  strcat(test, dirName);
  //check directory exist or not
  if(stat(test, &st) == -1){
    //create directory
    if(mkdir(test, 0700)==0){
      printf("Directory Created Successfully ! \n");
    }
    else{
      perror("mkdir");
      exit(EXIT_FAILURE);
    }
  }
  else{
    printf("Directory already exist.\n");
  }
  printf("\n"); 
  return;
}

void showDir(){
  char dirName[30];
  char test[255];
  int i = 0;
  struct dirent *direntp;
  DIR *dirp;
  //empty test array
  memset(test, 0, sizeof test);
  printf("Name of directory to show : ");
  scanf("%s",dirName);
  //get current directory
  cwd = getcwd(NULL, 0);
  if(!cwd){
    perror("getcwd");
    exit(EXIT_FAILURE);
  }
  //Make path
  strcat(test, cwd);
  strcat(test, "/");
  strcat(test, dirName);
  //Check if directory exist or not
  if(stat(test, &st) != -1){
    //Opening directory
    if((dirp = opendir(test)) == NULL){
      perror("Failed to open directory ! \n");
      return;
    }
    else{
      //Reading directory
      while((direntp = readdir(dirp)) != NULL){
        printf("%s\n", direntp->d_name);
        i++;
      }
      //Closing directory
      while((closedir(dirp) == -1) && (errno == EINTR));
      printf("Total : %d\n", i);
    }
  }
  else{
    printf("No such directory exist ! \n");
  }
  printf("\n");
  return;
}

void nameDir(){
  char oldName[30];
  char newName[30];
  char oldTest[255];
  char newTest[255];
  //Empty oldTest & newTest array
  memset(oldTest, 0, sizeof oldTest);
  memset(newTest, 0, sizeof newTest);
  //Get current directory
  cwd = getcwd(NULL, 0);
  if(!cwd){
    perror("getcwd");
    exit(EXIT_FAILURE);
  }
  printf("Name of directory to rename : ");
  scanf("%s", oldName);
  //Make oldPath
  strcat(oldTest, cwd);
  strcat(oldTest, "/");
  strcat(oldTest, oldName);
  //Check if directory exist or not
  if(stat(oldTest, &st) != -1){
    printf("New name for the directory : ");
    scanf("%s", newName);
    //Make newPath
    strcat(newTest, cwd);
    strcat(newTest, "/");
    strcat(newTest, newName);
    //Check if directory exist or not
    if(stat(newTest, &st) == -1){
      //Rename directory
      if(rename(oldTest, newTest) == 0){
        printf("Rename successfully !\n");
      }
      else{
        perror("rename");
        exit(EXIT_FAILURE);
      }
    }
    else{
      printf("Directory already exist !\n");
    }
  }
  else{
    printf("No such directory exist !\n");
  }
  printf("\n");
  return;
}

void delDir(){
  char dirName[30];
  char test[255];
  //Empty test array
  memset(test, 0, sizeof test);
  printf("Name of directory to remove : ");
  scanf("%s",dirName);
  //Get current directory
  cwd = getcwd(NULL, 0);
  if(!cwd){
    perror("getcwd");
    exit(EXIT_FAILURE);
  }
  //Make path
  strcat(test, cwd);
  strcat(test, "/");
  strcat(test, dirName);
  if(stat(test, &st) != -1){
    //Removing directory
    if(rmdir(test) == 0){
      printf("Directory removed successfully ! \n");
    }
    else{
      printf("Failed to remove ! Directory not empty ! \n");
    }
  }
  else{
    printf("No such directory exist ! \n");
  }
  printf("\n");
  return;
}

int main(){
  int opt = 0;
  while(opt != 5){
    cwd = getcwd(NULL, 0);
    if(!cwd){
      perror("getcwd");
      exit(EXIT_FAILURE);
    }
    printf("Directory Manager (curdir = %s) \n", cwd);
    printf("1. Create New Directory\n");
    printf("2. Show Inside of Directory\n");
    printf("3. Rename Directory\n");
    printf("4. Remove Directory\n");
    printf("5. End Program\n");
    printf("Choose Option : ");
    scanf("%d", &opt);
    printf("\n");
    if(opt != 5){
      switch(opt){
        case 1: makeDir(); break;
        case 2: showDir(); break;
        case 3: nameDir(); break;
        case 4: delDir(); break;
        default: printf("Wrong Input...\n");
      }  
    }
  }
  printf("Thank You ! \n");
  free(cwd);
  return 0;
}
