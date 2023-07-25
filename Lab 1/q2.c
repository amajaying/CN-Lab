// Write a C program to assign values to each member of the following structure. Pass the populated structure to a function Using call-by-value and another function using call-by-address and print the value of each member of the structure.
// struct student_info{
// int roll_no;
// char name[50];
// float CGPA;
// struct dob age;
// };

#include <stdio.h>

struct dob{
    int day;
    int month;
    int year;
};

struct student_info{
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

void callByValue(struct student_info s2){
    printf("Printing the details of each student using call by value:");
    printf("Roll No: %d", s2.roll_no);
    printf("Name: %s", s2.name);
    printf("CGPA: %f", s2.CGPA);
    printf("Age: %d Years, %d Months, %d Days");
}

void callBy(struct student_info s2){
    printf("Printing the details of each student using call by value:");
    printf("Roll No: %d", s2.roll_no);
    printf("Name: %s", s2.name);
    printf("CGPA: %f", s2.CGPA);
    printf("Age: %d Years, %d Months, %d Days");
}

int main(){

}