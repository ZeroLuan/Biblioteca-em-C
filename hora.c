#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void data_hora(){

  struct tm *data_hora_atual;

  time_t segundos;
  time(&segundos);

  data_hora_atual = localtime(&segundos);

  printf("%d/%d/%d",data_hora_atual->tm_mday,
    data_hora_atual->tm_mon += 1,
    data_hora_atual->tm_year += 1900);

  printf("     %d:%d", data_hora_atual->tm_hour -= 3, data_hora_atual->tm_min);

}