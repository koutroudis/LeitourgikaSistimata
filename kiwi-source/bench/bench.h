/*
xrhsimopoihsame thn sunthhkh
ifndef wste na apofugoume ta pollapla 
include tis bench.h
*/
#ifndef BENCH_H 
#define BENCH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define KSIZE (16)
#define VSIZE (1000)
#define THREADSNUMBER (10)//arithmos nhmatwn (pou eisagei o xrhsths)

#define LINE "+-----------------------------+----------------+------------------------------+-------------------+\n"
#define LINE1 "---------------------------------------------------------------------------------------------------\n"

long long get_ustime_sec(void);
void _random_key(char *key,int length);
void _write_test(void *arguments);//dhlwnoume thn sunarthsh _write_test me ta orismata tis
void _read_test(void *arguments);//dhlwnoume thn sunarthsh _read_test me ta orismata tis

struct argumentsThread{//dhlwnoume mia struct, wste na perasoume ta orismata twn sunarthsewn _write_test kai _read_test kata thn diarkeia tis dhmiourgias twn nhmatwn
	long int count;
	int r;
	int startNumTh;//o arithmos pou tha xekinhsei h for sto kathe nhma
	int untilNumber;//o aritmos twn kleidiwn pou tha epexergasth to kathe nhma
};

//dhlwnoume ta exhs mutexes pou 8a xrhsimopoihsoume sta arxeia bench.c kai kiwi.c
pthread_mutex_t threadArgNumberSafe;//xrhsimopoihtai gia na parei ta swsta orismata h sunarthsh _read_test kai _write_test
pthread_mutex_t numberSafe;//xrhsimopoihtai gia na prostatepsoume thn global metavlhth checkCloseDb
pthread_mutex_t putSafe;//xrhsimopoihtai gia na prostatepsoume thn domh tis db_add
pthread_mutex_t globalGetSafe;//xrhsimopoihtai gia na prostatepsoume thn global metavlhth found

#endif