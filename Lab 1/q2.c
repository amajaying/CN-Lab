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

void callbyvalue(struct student_info s2){
    printf("Printing student details using call by value \n");
    printf("Roll no: %d \n", s2.roll_no);
    printf("Name: %s \n",s2.name);
    printf("CGPA: %f \n",s2.CGPA);
    printf("DOB \n Year: %d \n Month: %d \n Day: %d \n",s2.age.year,s2.age.month,s2.age.day);
}

void callbyaddress(struct student_info *s2){
    printf("Printing student details using call by address \n");
    printf("Roll no: %d \n", (*s2).roll_no);
    printf("Name: %s \n",(*s2).name);
    printf("CGPA: %f \n",(*s2).CGPA);
    printf("DOB \n Year: %d \n Month: %d \n Day: %d \n",(*s2).age.year,(*s2).age.month,(*s2).age.day);
}

int main(){
    struct student_info s1;
    s1.roll_no= 7;
    strncpy(s1.name,"Unik",32);
    s1.CGPA = 9.0;
    s1.age.day = 12;
    s1.age.month = 8;
    s1.age.year = 2004;
    callbyvalue(s1);
    callbyaddress(&s1);
}
