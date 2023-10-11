#include "bench.h"
void _random_key(char *key,int length) {
	int i;
	char salt[36]= "abcdefghijklmnopqrstuvwxyz0123456789";

	for (i = 0; i < length; i++)
		key[i] = salt[rand() % 36];
}

void _print_header(int count)
{
	double index_size = (double)((double)(KSIZE + 8 + 1) * count) / 1048576.0;
	double data_size = (double)((double)(VSIZE + 4) * count) / 1048576.0;

	printf("Keys:\t\t%d bytes each\n", 
			KSIZE);
	printf("Values: \t%d bytes each\n", 
			VSIZE);
	printf("Entries:\t%d\n", 
			count);
	printf("IndexSize:\t%.1f MB (estimated)\n",
			index_size);
	printf("DataSize:\t%.1f MB (estimated)\n",
			data_size);

	printf(LINE1);
}

void _print_environment()
{
	time_t now = time(NULL);

	printf("Date:\t\t%s", 
			(char*)ctime(&now));

	int num_cpus = 0;
	char cpu_type[256] = {0};
	char cache_size[256] = {0};

	FILE* cpuinfo = fopen("/proc/cpuinfo", "r");
	if (cpuinfo) {
		char line[1024] = {0};
		while (fgets(line, sizeof(line), cpuinfo) != NULL) {
			const char* sep = strchr(line, ':');
			if (sep == NULL || strlen(sep) < 10)
				continue;

			char key[1024] = {0};
			char val[1024] = {0};
			strncpy(key, line, sep-1-line);
			strncpy(val, sep+1, strlen(sep)-1);
			if (strcmp("model name", key) == 0) {
				num_cpus++;
				strcpy(cpu_type, val);
			}
			else if (strcmp("cache size", key) == 0)
				strncpy(cache_size, val + 1, strlen(val) - 1);	
		}

		fclose(cpuinfo);
		printf("CPU:\t\t%d * %s", 
				num_cpus, 
				cpu_type);

		printf("CPUCache:\t%s\n", 
				cache_size);
	}
}

int main(int argc,char** argv)
{
	long int count;
	pthread_t id[THREADSNUMBER];//arxikopoioume ton arithmo twn nhmatwn pou tha xrhsimopoihsoume
	struct argumentsThread argTh;//arxikopoioume thn struct pou dhlwsame sto arxeio bench.h
	
	srand(time(NULL));
	if (argc < 3) {
		fprintf(stderr,"Usage: db-bench <write | read | readwrite> <count>\n");
		exit(1);
	}
	//4o erwthma
	double arg1;
	int erwthma3;
	if (argc == 4) { // chekaroume an o xrhsths valei 4o orisma
		arg1 = atoi(strtok(argv[3],"-")); // pairnoume to prwto skelos tou posostou pou tha valei o xrhsths
		double arg2 = atoi(strtok(NULL,"-")); //pairnoume to deutero skelos
		if (arg1 + arg2 != 100){//elenxoume an to athrisma tous einai iso me 100,gia tuxon lathos eisagwgh tou orismatos apo ton xrhsth
			printf("PutGetRate is wrong, Example: 60-40 or 20-80\n");
			exit(1);	
		}
		arg1 = arg1/100;//pairnoume to dekadiko tou arg1 gia pio eukolh xrhsh parakatw
		erwthma3 = 1;//8etoume to erwthma3 iso me 1 otan uparxei tetarto orisma kai etsi trexei to 4o erwthma
	}else{//an o xrhsths den dwsei 4o orisma ekteleitai me pososto put-get 50-50
		arg1 = 0.5;
		erwthma3 = 2;//8etoume to erwthma3 iso me 2 otan den uparxei tetarto orisma kai etsi trexei to 3o erwthma
	}
	//
	
	if (strcmp(argv[1], "write") == 0) {
		int r = 0;

		count = atoi(argv[2]);
		_print_header(count);
		_print_environment();
		if (argc == 4)
			r = 1;
		
		argTh.count = count;//pername thn metavlhth count sthn struct
		argTh.r = r;        //pername thn metavlhth r sthn struct
		argTh.untilNumber = count/THREADSNUMBER;//pairname mia metavlhth  sthn struct pou ka8orizei ton arithmo twn keys pou 8a epexergasth kathe nhma
		int startNumTh  = -(count/THREADSNUMBER);//arxikopoioume mia metavlhth pou ka8orizei ton arithmo tou key pou 8a xekinaei na epexergazetai to kathe nhma
		for (int i = 0;i<THREADSNUMBER;i++){ //dhmiourgoume ta nhmata
			pthread_mutex_lock(&threadArgNumberSafe); //kleidwnoume , wste na perastoun swsta ta orismata sto kathe nhma
			startNumTh  = startNumTh  + count/THREADSNUMBER; //auxanoume thn metavlhth analoga me ton ari8mo kleidiwn pou theloume na epexergastei to kathe nhma
			argTh.startNumTh = startNumTh; //pername thn metavlhth sthn struct
			pthread_create(&id[i],NULL,_write_test,(void *)&argTh);//dhmiourgoume to nhma me orisma thn struct		
		}
		for (int i = 0;i<THREADSNUMBER;i++){//perimenoume ta nhmata na teleiwsoun
			pthread_join(id[i],NULL);		
		}
		
	} else if (strcmp(argv[1], "read") == 0) {
		int r = 0;

		count = atoi(argv[2]);
		_print_header(count);
		_print_environment();
		if (argc == 4)
			r = 1;
			
		argTh.count = count;//pername thn metavlhth count sthn struct
		argTh.r = r;        //pername thn metavlhth r sthn struct
		argTh.untilNumber = count/THREADSNUMBER;//pairname mia metavlhth  sthn struct pou ka8orizei ton arithmo twn keys pou 8a epexergasth kathe nhma
		int startNumTh  = -(count/THREADSNUMBER);//arxikopoioume mia metavlhth pou ka8orizei ton arithmo tou key pou 8a xekinaei na epexergazetai to kathe nhma
		for (int i = 0;i<THREADSNUMBER;i++){//dhmiourgoume ta nhmata
			pthread_mutex_lock(&threadArgNumberSafe);//kleidwnoume , wste na perastoun swsta ta orismata sto kathe nhma
			startNumTh  = startNumTh  + count/THREADSNUMBER;//auxanoume thn metavlhth analoga me twn ari8mo kleidiwn pou theloume na epexergasth to kathe nhma
			argTh.startNumTh = startNumTh;  //pername thn metavlhth sthn struct
			pthread_create(&id[i],NULL,_read_test,(void *) &argTh);	//dhmiourgoume to nhma me orisma thn struct
			
		}
		for (int i = 0;i<THREADSNUMBER;i++){//perimenoume ta nhmata na teleiwsoun
			pthread_join(id[i],NULL);
		}
	}else if (strcmp(argv[1], "readwrite") == 0) {
		int r = 0;
		count = atoi(argv[2]);
		_print_header(count);
		_print_environment();
		if (argc == 5)//to 8esame iso me 5 ,wste na mhn pairnei random keys
			r = 1;

		argTh.count = count*arg1*erwthma3;//pername thn metavlhth count sthn struct
		argTh.r = r;        //pername thn metavlhth r sthn struct
		argTh.untilNumber = (count/THREADSNUMBER)*erwthma3;//pairname mia metavlhth  sthn struct pou ka8orizei ton arithmo twn keys pou 8a epexergasth kathe nhma
		int startNumThWr  = -(count/THREADSNUMBER)*erwthma3;//arxikopoioume mia metavlhth pou ka8orizei ton arithmo tou key pou 8a xekinaei na epexergazetai to kathe nhma put
		int startNumThRe  = -(count/THREADSNUMBER)*erwthma3;//arxikopoioume mia metavlhth pou ka8orizei ton arithmo tou key pou 8a xekinaei na epexergazetai to kathe nhma get
		
		for (int i = 0;i<THREADSNUMBER; i++){//dhmiourgoume ta nhmata
			pthread_mutex_lock(&threadArgNumberSafe);//kleidwnoume , wste na perastoun swsta ta orismata sto kathe nhma
			if(i<THREADSNUMBER*arg1){
				startNumThWr  = startNumThWr  + (count/THREADSNUMBER)*erwthma3;//auxanoume thn metavlhth analoga me twn ari8mo kleidiwn pou theloume na epexergasth to kathe nhma
				argTh.startNumTh = startNumThWr;  //pername thn metavlhth sthn struct
				pthread_create(&id[i],NULL,_write_test,(void *) &argTh);	//dhmiourgoume to nhma me orisma thn struct
			}else{
				startNumThRe  = startNumThRe  + (count/THREADSNUMBER)*erwthma3;//auxanoume thn metavlhth analoga me twn ari8mo kleidiwn pou theloume na epexergasth to kathe nhma
				argTh.startNumTh = startNumThRe;  //pername thn metavlhth sthn struct
				pthread_create(&id[i],NULL,_read_test,(void *) &argTh);	//dhmiourgoume to nhma me orisma thn struct
			}	
		}
		for (int i = 0;i<THREADSNUMBER;i++){//perimenoume ta nhmata na teleiwsoun
			pthread_join(id[i],NULL);
		}
	}else {
		fprintf(stderr,"Usage: db-bench <write | read | readwrite> <count> \n");
		exit(1);
	}

	return 1;
}
