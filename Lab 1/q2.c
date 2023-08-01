#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct dob{
    int day;
    int month;
    int year;
};

struct student_info{
    int roll_no;
    char name[20];
    float CGPA;
    struct dob age;
};

void callbyValue(struct student_info s2){
    printf("Using call by value \n");
    printf("Roll no: %d \n", s2.roll_no);
    printf("Name: %s \n",s2.name);
    printf("CGPA: %2f \n",s2.CGPA);
    printf("DOB: \nYear: %d \nMonth: %d \nDay: %d \n",s2.age.year,s2.age.month,s2.age.day);
}

void callbyAddress(struct student_info *s2){
    printf("\nUsing call by address \n");
    printf("Roll no: %d \n", (*s2).roll_no);
    printf("Name: %s \n",(*s2).name);
    printf("CGPA: %2f \n",(*s2).CGPA);
    printf("DOB: \nYear: %d \nMonth: %d \nDay: %d \n",(*s2).age.year,(*s2).age.month,(*s2).age.day);
}

int main(){
    struct student_info s1;
    s1.roll_no= 7;
    strncpy(s1.name,"Ajay",32);
    s1.CGPA = 9.5;
    s1.age.day = 15;
    s1.age.month = 01;
    s1.age.year = 2003;
    callbyValue(s1);
    callbyAddress(&s1);
}
