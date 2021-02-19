#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define max_len 69
#define MAX_LINE_LEN 1024

int profile_data_nitems = 0;
int input_number = 0;

struct date{
    int y;
    int m;
    int d;
};
struct profile{
    int id;
    char name[max_len+1];
    struct date birthday;
    char adress[max_len+1];
    char *comment;
    int num;
};
struct profile profile_data_store[10000];

int subst(char *str, char c1, char c2);
int get_line(char *line, FILE *fp);
void parse_line(char line[]);
int count(char *line, char sep);
void cmd_quit();
void cmd_check();
void cmd_print(char *param);
void cmd_read(char *param);
void cmd_write(char *param);
void cmd_find(char *param);
void cmd_sort(char *param);
void heap_sort(int column);
int compare_profile(struct profile *p1, struct profile *p2, int column);
int compare_name_adress(char *s1, char *s2);
int compare_date(struct date *p1, struct date *p2);
void cmd_delete(char *param);
void swap_profile(struct profile *p1, struct profile *p2);
void cmd_edit(char *param);
void exec_command(char cmd, char *param);
struct profile *new_profile(struct profile *p, char *str);
int split(char *str,char *ret[],char sep,int max);
int myatoi(char *str);


int main(){
    char line[MAX_LINE_LEN + 1];

    while (get_line(line, stdin)) {
    parse_line(line);
    }
    return 0;
}

int subst(char *str, char c1, char c2){
    int n=0;
    char *p;

    if(c1 == c2)return 0;
    else{
    p = str;
    while(*p != '\0'){
        if(*p == c1){
            *p = c2;
            n++;
        }
        p++;
    }

    return n;
    }
}

int get_line(char *line, FILE *fp){

    if(fgets(line, MAX_LINE_LEN + 1, fp) == NULL){
        return 0;
    }else{
        subst(line,'\n','\0');
        return 1;
    }
}

void parse_line(char line[])
{   char cmd, *param=NULL;

    if (line[0] == '%') {
    cmd = line[1];
    param = &line[3];
    exec_command(cmd, param);
  }else if(count(line, ',')==5){
      new_profile(&profile_data_store[profile_data_nitems],line);
  }
  return;
}

int count(char *line, char sep){
    int n=1;

    while(*line != '\0'){
        if(*line==sep)n++;
        line++;
    }
    return n;
}

void cmd_quit(){
    exit(0);
}

void cmd_check(){
    printf("%d profile(s).\n", profile_data_nitems);
}

void cmd_print(char *param){
    int n=0,i;

    n = myatoi(param);
    if(n==-10001){
        fprintf(stderr,"Input a proper argument．\n");
        return;
    }
    if(n==0){for(i=0;i<profile_data_nitems;i++){
        printf("Id\t:\t%d\nName\t:\t%s\nBirth\t:\t%d-%d-%d\nAddr.\t:\t%s\nComm.\t:\t%s\n\n",
        profile_data_store[i].id, profile_data_store[i].name, profile_data_store[i].birthday.y,
        profile_data_store[i].birthday.m, profile_data_store[i].birthday.d,
        profile_data_store[i].adress, profile_data_store[i].comment);}
    }
    if((0<n)&&(n<=profile_data_nitems)){for(i=0;i<n;i++){
        printf("Id\t:\t%d\nName\t:\t%s\nBirth\t:\t%d-%d-%d\nAddr.\t:\t%s\nComm.\t:\t%s\n\n",
        profile_data_store[i].id, profile_data_store[i].name, profile_data_store[i].birthday.y,
        profile_data_store[i].birthday.m, profile_data_store[i].birthday.d,
        profile_data_store[i].adress, profile_data_store[i].comment);}
    }
    if(n>profile_data_nitems||-n>profile_data_nitems-1){for(i=0;i<profile_data_nitems;i++){
        printf("Id\t:\t%d\nName\t:\t%s\nBirth\t:\t%d-%d-%d\nAddr.\t:\t%s\nComm.\t:\t%s\n\n",
        profile_data_store[i].id, profile_data_store[i].name, profile_data_store[i].birthday.y,
        profile_data_store[i].birthday.m, profile_data_store[i].birthday.d,
        profile_data_store[i].adress, profile_data_store[i].comment);}
        printf("File don't hava enough data so output　%d　data, all that exists.",profile_data_nitems);
    }
    if((0>n)&&(-n<profile_data_nitems)){for(i=n+profile_data_nitems;i<profile_data_nitems;i++){
        printf("Id\t:\t%d\nName\t:\t%s\nBirth\t:\t%d-%d-%d\nAddr.\t:\t%s\nComm.\t:\t%s\n\n",
        profile_data_store[i].id, profile_data_store[i].name, profile_data_store[i].birthday.y,
        profile_data_store[i].birthday.m, profile_data_store[i].birthday.d,
        profile_data_store[i].adress, profile_data_store[i].comment);}
    }

    return;
}

void cmd_read(char *param){
    FILE *fp;
    char line[MAX_LINE_LEN+1];

    fp = fopen(param,"r");
    if(fp == NULL){
        fprintf(stderr, "Couldn't read data of '%s'. \n",param);
    }else{
    while(get_line(line, fp)){
        new_profile(&profile_data_store[profile_data_nitems],line);
    }
    fprintf(stderr, "Read data of '%s' \n",param);
    fclose(fp);
    }
    return;
}

void cmd_write(char *param){
    FILE *fp;
    int i;

    fp = fopen(param,"a");
    if(fp == NULL){
        fprintf(stderr, "Couldn't output data to '%s'. \n",param);
    }else{
    fprintf(stderr, "Output data to '%s'. \n",param);
    for(i=0;i<profile_data_nitems;i++){
        fprintf(fp, "%d,%s,%d-%d-%d,%s,%s\n",
        profile_data_store[i].id, profile_data_store[i].name, profile_data_store[i].birthday.y,
        profile_data_store[i].birthday.m, profile_data_store[i].birthday.d,
         profile_data_store[i].adress, profile_data_store[i].comment);}
    }
    fclose(fp);
    return;
}

void cmd_find(char *param){
    int i,n;
    char *a,*b,*c,*d,*e,*f,*g;

    if(*param == '\0'){
        fprintf(stderr,"Input the string you are searching for ．");
        return;
    }
    for(i=0;i<profile_data_nitems;i++){

        n = log10(profile_data_store[i].id) + 1;
        a = (char*)malloc(sizeof(char)*n);
        sprintf(a, "%d", profile_data_store[i].id);
        b = strstr(a, param);

        c = strstr(profile_data_store[i].name,param);

        d = (char*)malloc(sizeof(char)*10 + 1);
        sprintf(d, "%d-%d-%d", profile_data_store[i].birthday.y,
        profile_data_store[i].birthday.m,profile_data_store[i].birthday.d);
        e = strstr(d, param);

        f = strstr(profile_data_store[i].adress,param);

        g = strstr(profile_data_store[i].comment,param);

        if(b != NULL||c != NULL||e != NULL||f != NULL||g != NULL){
        printf("Id\t:\t%d\nName\t:\t%s\nBirth\t:\t%d-%d-%d\nAddr.\t:\t%s\nComm.\t:\t%s\n\n",
        profile_data_store[i].id, profile_data_store[i].name, profile_data_store[i].birthday.y,
        profile_data_store[i].birthday.m, profile_data_store[i].birthday.d,
        profile_data_store[i].adress, profile_data_store[i].comment);
        }
    }

    return;
}

void cmd_sort(char *param){
    int column,i,j,k;
    struct profile x;

    column = myatoi(param);
    if(column==-10001){
        fprintf(stderr,"Input a proper argument．\n");
        return;
    }

    heap_sort(column);

    for(k=profile_data_nitems-2; k>=0; k--){
        x = profile_data_store[k+1];
        profile_data_store[k+1] = profile_data_store[0];
        i=0; j=1;
        while(j<=k){
            if(j<k && compare_profile(&profile_data_store[j], &profile_data_store[j+1],
            column)<0)j++;
            if(compare_profile(&x, &profile_data_store[j], column)<0){
                profile_data_store[i]=profile_data_store[j];
                i=j; j=2*i+1;
            }else break;
        }
        profile_data_store[i] = x;
    }

    return;
}

void heap_sort(int column){

    int i,j,k;
    struct profile x;

    for(k=(profile_data_nitems-1)/2; k>=0; k--){
        i=k; j=2*i+1; x=profile_data_store[i];
        while(j<=profile_data_nitems-1){
            if(j<profile_data_nitems-1 && compare_profile(&profile_data_store[j],
            &profile_data_store[j+1], column)<0)j++;
            if(compare_profile(&x, &profile_data_store[j], column)<0){
                profile_data_store[i]=profile_data_store[j];
                i=j; j=2*i+1;
            }else break;
        }
        profile_data_store[i] = x;
    }
}

int compare_profile(struct profile *p1, struct profile *p2, int column)
{
  switch (column) {

    case 0:
      return p1->num - p2->num; /* num */
    case 1:
      return p1->id - p2->id;   /* id */
    case 2:
      return strcmp(p1->name, p2->name);       /* name */
    case 3:
      return compare_date(&p1->birthday, &p2->birthday); /* birthday */
    case 4:
      return strcmp(p1->adress, p2->adress);       /* address */
    case 5:
      return strcmp(p1->comment, p2->comment);       /* comment */
    }

    return 0;
}

int compare_date(struct date *p1, struct date *p2){

    if(p1->y != p2->y){
        return p1->y - p2->y;
    }else{
        if(p1->m != p2->m){
            return p1->m - p2->m;
        }else{
            return p1->d - p2->d;
        }
    }
}

void cmd_delete(char *param){
    int n,i=0;
    char ans;

    n = myatoi(param);
    if(n==-10001){
        fprintf(stderr,"Input a proper argument．\n");
        return;
    }

    while(i<profile_data_nitems){
        if(profile_data_store[i].id==n)break;
        else i++;
    }
    if(i==profile_data_nitems){
        printf("Data is not found．\n");
        return;
    }else{
        printf("Id\t:\t%d\nName\t:\t%s\nBirth\t:\t%d-%d-%d\nAddr.\t:\t%s\nComm.\t:\t%s\n\n",
        profile_data_store[i].id, profile_data_store[i].name, profile_data_store[i].birthday.y,
        profile_data_store[i].birthday.m, profile_data_store[i].birthday.d,
        profile_data_store[i].adress, profile_data_store[i].comment);
        printf("Are you sure you want to delete？(Y/N)　");
        scanf("%c", &ans);
        if(ans=='Y'){
            profile_data_nitems--;
            swap_profile(&profile_data_store[i], &profile_data_store[profile_data_nitems]);
            printf("Deleted．\n");
        }else{
            printf("Not Deleted．\n");
            return;
        }
    }
    return;
}

void swap_profile(struct profile *p1, struct profile *p2){

    struct profile tmp;

    tmp = *p2;
    *p2 = *p1;
    *p1 = tmp;

    return;
}

void cmd_edit(char *param){
    int n,i=0,j,y1,m1,d1;
    char s[4],*c=NULL,line[MAX_LINE_LEN+1];
    char *s1 = "ID";
    char *s2 = "氏名";
    char *s3 = "誕生日";
    char *s4 = "住所";
    char *s5 = "備考";

    n = myatoi(param);
    if(n==-10001){
        fprintf(stderr,"適切な引数を入力してください．\n");
        return;
    }

    while(i<profile_data_nitems){
        if(profile_data_store[i].id==n)break;
        else i++;
    }
    if(i==profile_data_nitems){
        printf("該当するデータがありませんでした．\n");
        return;
    }
    printf("Id\t:\t%d\nName\t:\t%s\nBirth\t:\t%d-%d-%d\nAddr.\t:\t%s\nComm.\t:\t%s\n\n",
        profile_data_store[i].id, profile_data_store[i].name, profile_data_store[i].birthday.y,
        profile_data_store[i].birthday.m, profile_data_store[i].birthday.d,
        profile_data_store[i].adress, profile_data_store[i].comment);
    printf("編集するデータ: "); scanf(" %s", s);
    while(strcmp(s,s1)!=0&&strcmp(s,s2)!=0&&strcmp(s,s3)!=0
    &&strcmp(s,s4)!=0&&strcmp(s,s5)!=0&&get_line(line, stdin)){
        printf("正しい値を入力してください\n");
        printf("編集するデータ: "); scanf("%s", s);
    }
    if(strcmp(s,s1)==0){
        printf("編集後のデータ: "); scanf("%d", &j);
        profile_data_store[i].id = j;
    }else if(strcmp(s,s2)==0){
        c = (char*)malloc(sizeof(char)*max_len);
        printf("編集後のデータ: "); scanf("%s", c);
        strncpy(profile_data_store[i].name,c,max_len);
        profile_data_store[i].name[max_len] = '\0';
        free(c);
    }else if(strcmp(s,s3)==0){
        printf("編集後のデータ: "); scanf("%d-%d-%d", &y1, &m1, &d1);
        profile_data_store[i].birthday.y = y1;
        profile_data_store[i].birthday.m = m1;
        profile_data_store[i].birthday.d = d1;
    }else if(strcmp(s,s4)==0){
        c = (char*)malloc(sizeof(char)*max_len);
        printf("編集後のデータ: "); scanf("%s", c);
        strncpy(profile_data_store[i].adress,c,max_len);
        profile_data_store[i].adress[max_len] = '\0';
        free(c);
    }else if(strcmp(s,s5)==0){
        free(profile_data_store[i].comment);
        printf("編集後のデータ: ");
        c = (char*)malloc(sizeof(char)*(MAX_LINE_LEN-13));
        scanf("%s", c);
        subst(c,'\n','\0');
        profile_data_store[i].comment = (char*)malloc(sizeof(char)*(strlen(c)+1));
        strcpy(profile_data_store[i].comment,c);
        free(c);
    }
    printf("データを編集しました．\n");
    printf("Id\t:\t%d\nName\t:\t%s\nBirth\t:\t%d-%d-%d\nAddr.\t:\t%s\nComm.\t:\t%s\n\n",
        profile_data_store[i].id, profile_data_store[i].name, profile_data_store[i].birthday.y,
        profile_data_store[i].birthday.m, profile_data_store[i].birthday.d,
        profile_data_store[i].adress, profile_data_store[i].comment);

    return;
}

void exec_command(char cmd, char *param){

    switch (cmd){
        case 'Q': cmd_quit();
        case 'C': cmd_check();
                break;
        case 'P': cmd_print(param);
                break;
        case 'R': cmd_read(param);
                break;
        case 'W': cmd_write(param);
                break;
        case 'F': cmd_find(param);
                break;
        case 'S': cmd_sort(param);
                break;
        case 'D': cmd_delete(param);
                break;
        case 'E': cmd_edit(param);
                break;
        default: break;
    }
    return;

}

struct profile *new_profile(struct profile *p, char *line){
    char *ret[5],*birth[3];
    int n;

    split(line,ret,',',5);
    if(myatoi(ret[0])==-10001){
        fprintf(stderr,"Input a proper ID．\n");
        return NULL;
    }
    p -> id = myatoi(ret[0]);
    strncpy(p->name,ret[1],max_len); p->name[max_len] = '\0';
    n = split(ret[2],birth,'-',3);
    if(n != 3){
        fprintf(stderr,"Input a proper birthday．\n");
        return NULL;
    }
    if(myatoi(birth[0])==-10001||myatoi(birth[1])==-10001||myatoi(birth[2])==-10001){
        fprintf(stderr,"Input a proper birthday．\n");
        return NULL;
    }
    p->birthday.y = myatoi(birth[0]);
    p->birthday.m = myatoi(birth[1]);
    p->birthday.d = myatoi(birth[2]);
    strncpy(p->adress,ret[3],max_len); p->adress[max_len] = '\0';
    free(p->comment);
    p->comment = (char*)malloc(sizeof(char)*(strlen(ret[4])+1)); strcpy(p->comment,ret[4]);
    profile_data_nitems++;
    input_number++;
    p->num = input_number;

    return p;
}

int split(char *str,char *ret[],char sep,int max){
    int n=0;

    ret[n] = str;
    n++;
    while(*str != '\0' && n<max){
        if(*str==sep){
            *str='\0';
            ret[n] = str + 1;
            n++;
        }
        str++;
    }
    return n;
}

int myatoi(char *str){
    int value = 0, sign = 1, a = 0;

    if(*str == '+')str++;
    else if(*str == '-'){
        sign = -1;
        str++;
    }

    while(*str != '\0'){
        if(*str < 48 || *str > 57){
            return -10001;
        }
        value += *str - 48;
        value *= 10;
        str++;
        a++;
    }
    value /= 10;
    value *= sign;
    if(a>=11)return -10001;
    return value;
}
