/*
 * Simple example 
 * 
 */
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sht31-d.h"

#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)

void printtempandhumidity(int file);
void printstatus(int file);
void printserialnum(int file);
void printBitStatus(uint16_t stat);

void printusage(char *selfname)
{
  printf("%s (options)\n", selfname);
  printf("\ts - print status\n");
  printf("\tr - soft reset\n");
  printf("\tc - clear status\n");
  printf("\te - enable heater\n");
  printf("\td - disable heater\n");
  printf("\tn - print serial#\n");
  printf("\tp - print temp & humid\n");
  printf("\t-h this\n\n");
  printf("Example to print temperaturehum & humidity, serial number & status\n  %s p n s\n\n", selfname);
}

int main(int argc, char *argv[])
{
  int file;
  int i;
  
  if (argc <= 1) {
    printusage(argv[0]);
    exit (EXIT_SUCCESS);
  }
  
  file = sht31_open(SHT31_INTERFACE_ADDR, SHT31_DEFAULT_ADDR);
  
  for (i = 1; i < argc; i++)
  {
    if (strcmp (argv[i], "-h") == 0)
    {
      printusage(argv[0]);
      sht31_close(file);
      exit (EXIT_SUCCESS);
    } else if (strcmp (argv[i], "s") == 0) {
      printstatus(file);
    } else if (strcmp (argv[i], "r") == 0) {
      printf("Soft reset :- ");
      (softreset(file)==SHT31_OK)?printf("OK\n"):printf("Failed\n");
    } else if (strcmp (argv[i], "c") == 0) {
      printf("Status cleared :- ");
      (clearstatus(file)==SHT31_OK)?printf("OK\n"):printf("Failed\n");
    } else if (strcmp (argv[i], "e") == 0) {
      printf("Heater enabled :- ");
      (enableheater(file)==SHT31_OK)?printf("OK\n"):printf("Failed\n");
    } else if (strcmp (argv[i], "d") == 0) {
      printf("Heater disabled :- ");
      (disableheater(file)==SHT31_OK)?printf("OK\n"):printf("Failed\n");
    } else if (strcmp (argv[i], "p") == 0) {
      printtempandhumidity(file);
    } else if (strcmp (argv[i], "n") == 0) {
      printserialnum(file);
    } else {
      printf("ERROR :- '%s' unknown option\n",argv[i]);
    }
      
    delay(30);
  }
  
  sht31_close(file);
  
  return 0;
}

void printtempandhumidity(int file)
{
  float tempC;
  float tempF;
  float humid;
  
  int rtn = gettempandhumidity(file, &tempC, &humid);
  
  if ( rtn != SHT31_OK && rtn != SHT31_CRC_CHECK_FAILED) {
    printf("ERROR:- Get temp/humidity failed\n!");
    return;
  }
    
  if ( rtn == SHT31_CRC_CHECK_FAILED) {
    printf("WARNING:- Get status CRC check failed, don't trust results\n");
  }
    
  if ( rtn == SHT31_OK || rtn == SHT31_CRC_CHECK_FAILED) {
    tempF =  tempC * 9 / 5 + 32;
    printf("Temperature %.2fc - %.2ff\n",tempC,tempF);
    printf("Humidity %.2f%%\n",humid);
  }
}



void printBitStatus(uint16_t stat)
{
  printf("Status :-\n");
  printf("    Checksum status %d\n", CHECK_BIT(stat,0));
  printf("    Last command status %d\n", CHECK_BIT(stat,1));
  printf("    Reset detected status %d\n", CHECK_BIT(stat,4));
  printf("    'T' tracking alert %d\n", CHECK_BIT(stat,10));
  printf("    'RH' tracking alert %d\n", CHECK_BIT(stat,11));
  printf("    Heater status %d\n", CHECK_BIT(stat,13));
  printf("    Alert pending status %d\n", CHECK_BIT(stat,15));
}

void printstatus(int file)
{
  uint16_t stat;

  int rtn = getstatus(file, &stat);
  
  if ( rtn != SHT31_OK && rtn != SHT31_CRC_CHECK_FAILED) {
     printf("ERROR:- Get status failed!\n");
     return;
  }
  
  if ( rtn == SHT31_CRC_CHECK_FAILED) {
    printf("WARNING:- Get status CRC check failed, don't trust results\n");
  }
    
  if ( rtn == SHT31_OK || rtn == SHT31_CRC_CHECK_FAILED) {
    printBitStatus(stat);
  }
}


void printserialnum(int file)
{
  uint32_t serialNo;

  int rtn = getserialnum(file, &serialNo);
  
  if ( rtn == SHT31_CRC_CHECK_FAILED) {
    printf("WARNING:- Get getserial# CRC check failed, don't trust results\n");
  }
    
  if ( rtn == SHT31_OK || rtn == SHT31_CRC_CHECK_FAILED) {
    printf("Serial# = 0x%x\n",serialNo);
  }
  
}


