#include<stdio.h>
#include<stdlib.h>

struct Student {
   int sno;
   char name[10];
   int score;
};

int main() {
   int numStudent;
   printf("학생 수 입력 : ");
   scanf_s("%d", &numStudent);

   struct Student* std;
   std = (struct Student *)malloc(sizeof(struct Student) * numStudent);

   for (int i = 0; i < numStudent; i++) {
      printf("학생 #%d-%d 학번 입력: ", numStudent, i + 1);
      scanf_s("%d", &(std[i].sno));

      printf("학생 #%d-%d 이름 입력: ", numStudent, i + 1);
      scanf_s("%s", std[i].name, 10);

      printf("학생 #%d-%d 성적 입력: ", numStudent, i + 1);
      scanf_s("%d", &(std[i].score));
   }

   int sum = 0;
   for (int i = 0; i < numStudent; i++) {
      sum += std[i].score;
   }
   printf("%d\n", sum);
   return 0;
}
