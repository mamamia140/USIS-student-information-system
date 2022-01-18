#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct student{
	char Name[20];
	char SurName[20];
	int StudentID; 
	int CoursesTaken;
	int Credit;
	
	struct student* next;
}STUDENTS;


typedef struct course{
	char CourseCode[40];
	char CourseName[40];
	int Credit;
	int Quota;
	int LecturerID;
	
	struct course* next;
}COURSES;

typedef struct lecturer{
	char Name[30];
	char SurName[30];
	int LecturerID;
	char Title[30];
	
	struct lecturer* next;
}LECTURERS;

typedef struct record{
	int StudentID;
	char CourseCode[20];
	char State[10];
	struct record* next;
}RECORD;

void add_student_to_the_list(STUDENTS *new_node, STUDENTS **head);
void add_course_to_the_list(COURSES *new_node,COURSES **chead);
void add_record_to_the_list(RECORD *new_node,RECORD **rhead);
void delete_course(char *code,STUDENTS **head,COURSES **chead,RECORD **rhead);
void print_to_the_file_record(RECORD **rhead);
void print_to_the_file(STUDENTS **head);


STUDENTS* create_student(){	//this function creates elemts of the particular structure and returns pointer to it.
	STUDENTS *stu;
	int i; 
	char junk;
	stu = (STUDENTS*) malloc( sizeof( STUDENTS ) );
	if( stu == NULL ) {
		printf("create_student: out of memory.");
		exit(1);
	}
	printf("Enter name of the student: ");
	scanf("%c",&junk);
	scanf("%[^\n]", stu->Name);
	printf("Enter surname of the student: ");
	scanf("%s", stu->SurName);
	printf("Enter StudentID of the student: ");
	scanf("%d", &i); stu->StudentID = i;
	stu->CoursesTaken = 0;
	stu->Credit = 0;
	stu->next = NULL;
	return stu;
}

void create_student_from_file(STUDENTS **head){
	STUDENTS *stu;
	char junk;
	FILE* f = fopen("students.txt","r");

	stu = (STUDENTS*) malloc( sizeof( STUDENTS ) );
	if( stu == NULL ) {
		printf("create_student: out of memory.");
		exit(1);	
	}
	if(fscanf(f,"%c",&junk) != 1){
		free(stu);
		return;
	}
	fscanf(f,"%[^-]%*c",stu->Name);
	fscanf(f,"%[^-]%*c",stu->SurName);
	fscanf(f,"%d%*c",&(stu->StudentID));
	fscanf(f,"%d%*c",&(stu->CoursesTaken));
	fscanf(f,"%d%*c",&(stu->Credit));
	stu->next = NULL;
	add_student_to_the_list(stu,head);

	if(fscanf(f,"%c",&junk) != 1){
		return;
	}
	
	while(1){
	stu = (STUDENTS*) malloc( sizeof( STUDENTS ) );
	if( stu == NULL ) {
		printf("create_student: out of memory.");
		exit(1);	
	}
	fscanf(f,"%[^-]%*c",stu->Name);
	fscanf(f,"%[^-]%*c",stu->SurName);
	fscanf(f,"%d%*c",&(stu->StudentID));
	fscanf(f,"%d%*c",&(stu->CoursesTaken));
	fscanf(f,"%d%*c",&(stu->Credit));
	stu->next = NULL;
	add_student_to_the_list(stu,head);
	if(fscanf(f,"%c",&junk) != 1){
		return;
		}
	}
}

void create_course_from_file(COURSES **chead){
	COURSES *cs;
	char junk;
	FILE* f = fopen("courses.txt","r");

	cs = (COURSES*) malloc( sizeof( COURSES ) );
	if( cs == NULL ) {
		printf("create_course: out of memory.");
		exit(1);	
	}
	if(fscanf(f,"%c",&junk) != 1){
		free(cs);
		return;
	}
	fscanf(f,"%[^-]%*c",cs->CourseCode);
	fscanf(f,"%[^-]%*c",cs->CourseName);
	fscanf(f,"%d%*c",&(cs->Credit));
	fscanf(f,"%d%*c",&(cs->Quota));
	fscanf(f,"%d%*c",&(cs->LecturerID));
	cs->next = NULL;
	add_course_to_the_list(cs,chead);
	if(fscanf(f,"%c",&junk) != 1){
		return;
	}
	
	while(1){
	cs = (COURSES*) malloc( sizeof( COURSES ) );
	if( cs == NULL ) {
		printf("create_course: out of memory.");
		exit(1);	
	}
	fscanf(f,"%[^-]%*c",cs->CourseCode);
	fscanf(f,"%[^-]%*c",cs->CourseName);
	fscanf(f,"%d%*c",&(cs->Credit));
	fscanf(f,"%d%*c",&(cs->Quota));
	fscanf(f,"%d%*c",&(cs->LecturerID));
	cs->next = NULL;
	add_course_to_the_list(cs,chead);
	if(fscanf(f,"%c",&junk) != 1){
		return;
		}
	}
	
}



COURSES *create_course(){
	COURSES *cs;
	int i;
	char junk;
	cs = (COURSES*) malloc( sizeof( COURSES ) );
	if( cs == NULL ) {
		printf("create_course: out of memory.");
		exit(1);
	}
	printf("Enter CourseCode: ");
	scanf("%s",cs->CourseCode);
	printf("Enter Name of The Course: ");
	scanf("%c",&junk);
	scanf("%[^\n]",cs->CourseName); 
	printf("Enter the credit of the course: ");
	scanf("%d", &i); cs->Credit = i;
	printf("Enter the quota of the course: ");
	scanf("%d", &i); cs->Quota = i;
	printf("Enter the lecturerID: ");
	scanf("%d", &i); cs->LecturerID = i;
	cs->next = NULL;
	return cs;
	
	
}


void add_student_to_the_list(STUDENTS *new_node, STUDENTS **head){


	STUDENTS *var_head = (*head);
	if((*head) == NULL)
	{	
		(*head) = new_node;
		return;
	}
	
	else 
	{
		while(var_head->next != NULL && var_head->StudentID != new_node->StudentID) 
		{
			var_head = var_head->next;
		}
		if(var_head->StudentID == new_node->StudentID){
			return;
		}
		var_head->next = new_node;
	}
}

void add_course_to_the_list(COURSES *new_node,COURSES **chead){
	COURSES *varhead = (*chead);
	
	if((*chead) == NULL)
	{	
		(*chead) = new_node;
		return;
	}
	
	else 
	{
		while(varhead->next != NULL )
		{	
			varhead = varhead->next;
		}
	
		varhead->next = new_node;
	}	
}

void display_all_informations(STUDENTS **head){
	printf("a student succesfully added.\n");
	STUDENTS *tempo = *head;
	while(1){
	printf("name:%s\n",tempo->Name);
	printf("surname:%s\n",tempo->SurName);
	printf("studentno:%d\n",tempo->StudentID);
	printf("number of courses:%d\n",tempo->CoursesTaken);
	printf("credit:%d\n",tempo->Credit);
	if((tempo->next)==NULL){
		break;
	}
	else{
		tempo = tempo->next;
	}	

	}
	
}


STUDENTS* create_student_node(){
		STUDENTS *s;
		s = (STUDENTS*) malloc( sizeof( STUDENTS ) );
		if( s == NULL ) {
			printf("create_course: out of memory.");
			exit(1);
		}	
		return s;
}



void delete_student(int number , STUDENTS **head){
	STUDENTS *temp = NULL, *var_head;

	var_head = (*head);
	while(var_head != NULL)
	{
		if(var_head->StudentID == number){
			temp = var_head;
			break;
		}
			
		var_head = var_head->next;
	}
	
	if(temp == (*head))
		(*head) = (*head)->next;
	else
	{
	
		if(temp == NULL)
		{
			printf("\nCould not find the student with that number");
			return;	
		}
		var_head = (*head);
		
		while(var_head->next != temp)
		{
			var_head = var_head->next;
		}

		var_head->next = var_head->next->next;
		free(temp);
	}
}

COURSES* create_course_node(){
		COURSES *cs;
		cs = (COURSES*) malloc( sizeof( COURSES ) );
		if( cs == NULL ) {
			printf("create_course: out of memory.");
			exit(1);
		}	
		return cs;
}

void create_record_from_file(RECORD **rhead){
	FILE *f = fopen("ogrenciderskayit.txt","r");
	
	RECORD *r;
	char junk;

	r = (RECORD*) malloc( sizeof( RECORD ) );
	if( r == NULL ) {
		printf("create_record: out of memory.");
		exit(1);	
	}
	if(fscanf(f,"%c",&junk) != 1){
		free(r);
		return;
	}
	fscanf(f,"%d%*c",&(r->StudentID));
	fscanf(f,"%[^-]%*c",r->CourseCode);
	fscanf(f,"%[^>]%*c",r->State);
	r->next = NULL;
	add_record_to_the_list(r,rhead);

	if(fscanf(f,"%c",&junk) != 1){
		return;
	}
	
	while(1){
	r = (RECORD*) malloc( sizeof( RECORD ) );
	if( r == NULL ) {
		printf("create_student: out of memory.");
		exit(1);	
	}
	fscanf(f,"%d%*c",&(r->StudentID));
	fscanf(f,"%[^-]%*c",r->CourseCode);
	fscanf(f,"%[^>]%*c",r->State);
	r->next = NULL;
	add_record_to_the_list(r,rhead);
	if(fscanf(f,"%c",&junk) != 1){
		return;
		}
	}
	
	
}

void delete_course(char *code,STUDENTS **head,COURSES **chead,RECORD **rhead){
	int kredi;
	COURSES *temp = NULL, *var_head;
	RECORD *r,*r2,**temp2;
	STUDENTS *st;
	var_head = (*chead);
	
	if(*chead == NULL){
		printf("there are no course");
		return;
	}
	while(var_head != NULL){
		if(strcmp(var_head->CourseCode,code) == 0){
			kredi = var_head->Credit;
		}
		var_head = var_head->next;
	}
	
	
	
	var_head = (*chead);
	
	while(var_head != NULL)
	{
		if(strcmp(var_head->CourseCode,code)==0){
			temp = var_head;
			break;
		}
			
		var_head = var_head->next;
	}
	
	if(temp == (*chead)){
		(*chead) = (*chead)->next;
		if(*rhead == NULL){
			create_record_from_file(rhead);
		}
		r = *rhead;

		while(r != NULL){
			if(strcmp(r->CourseCode,code) == 0){

				if(r == (*rhead)){
					(*rhead) = (*rhead)->next;
					if(*head == NULL){
						create_student_from_file(head);
					}
					st = *head;
					
					while(st != NULL){
						if(r->StudentID == st->StudentID){
							st->CoursesTaken = st->CoursesTaken - 1;
							st->Credit = st->Credit -kredi;
							print_to_the_file(head);
						}
						st = st->next;
					}	
					
					
					}
				else
				{
					r2 = (*rhead);

					while(r2->next->CourseCode != code)
						{
						r2->next = r2->next->next;
					}
					temp2 = &(r2->next);
					r2->next = r2->next->next;
					free(*temp2);
					if(*head == NULL){
						create_student_from_file(head);
					}
					st = *head;
					while(st != NULL){
						if(r->StudentID == st->StudentID){
							st->CoursesTaken = st->CoursesTaken - 1;
							st->Credit = st->Credit -kredi;
						}
						st = st->next;
					}
				}
			}
			r = r->next;
		}
		
		print_to_the_file_record(rhead);

		
		
	}
		
		
	else
	{
	
		if(temp == NULL)
		{
			printf("\nCould not find the course with that code");
			return;	
		}
		var_head = (*chead);
		
		while(var_head->next != temp)
		{
			var_head = var_head->next;
		}

		var_head->next = var_head->next->next;
		free(temp);
		
		if(*rhead == NULL){
			create_record_from_file(rhead);
		}
		r = *rhead;

		while(r != NULL){
			if(strcmp(r->CourseCode,code) == 0){

				if(r == (*rhead)){
					(*rhead) = (*rhead)->next;
					if(*head == NULL){
						create_student_from_file(head);
					}
					st = *head;
					while(st != NULL){
						if(r->StudentID == st->StudentID){
							st->CoursesTaken = st->CoursesTaken - 1;
							st->Credit = st->Credit -kredi;
							print_to_the_file(head);
						}
						st = st->next;
					}	
					
					
					}
				else
				{
					r2 = (*rhead);

					while(r2->next->CourseCode != code)
						{
						r2->next = r2->next->next;
					}
					temp2 = &(r2->next);
					r2->next = r2->next->next;
					free(*temp2);
					st = *head;
					if(*head == NULL){
						create_student_from_file(head);
					}
					st = *head;
					while(st != NULL){
						if(r->StudentID == st->StudentID){
							st->CoursesTaken = st->CoursesTaken - 1;
							st->Credit = st->Credit -kredi;
						}
						st = st->next;
					}
				}
			}
			r = r->next;
		}
		
		print_to_the_file_record(rhead);
	}
	
}

void print_to_the_file(STUDENTS **head){
	FILE *fp=fopen ("students.txt","w");
	if (fp==NULL)
	{
		printf("File cannot be opened\n");
		exit(0);
	}
	
	STUDENTS *var_head = (*head);
	while(var_head != NULL)
	{

		fprintf(fp,"-%s-",var_head->Name);
		fprintf(fp,"%s-",var_head->SurName);
		fprintf(fp,"%d-",var_head->StudentID);
		fprintf(fp,"%d-",var_head->CoursesTaken);
		fprintf(fp,"%d-",var_head->Credit);
		var_head = var_head->next;		
	}
	fclose(fp);
	printf("\nFile is updated\n");
}
// This function is used for reading from file.
void read_from_file(){
	STUDENTS stu;
	char junk;
	FILE *fs=fopen ("students.txt","r");
	if (fs==NULL)
	{
		printf("File cannot be opened\n");
		exit(0);
	}
	if(fscanf(fs,"%c",&junk) != 1){
		return;
	}
	fscanf(fs,"%[^-]%*c",stu.Name);
	fscanf(fs,"%[^-]%*c",stu.SurName);
	fscanf(fs,"%d%*c",&(stu.StudentID));
	fscanf(fs,"%d%*c",&(stu.CoursesTaken));
	fscanf(fs,"%d%*c",&(stu.Credit));
	
	printf("Student information:\n");
	printf("Name: %s\n",stu.Name);
	printf("Sur Name: %s\n",stu.SurName);
	printf("StudentID: %d\n",stu.StudentID);
	printf("Total Courses: %d\n",stu.CoursesTaken);
	printf("Total credits: %d\n\n",stu.Credit);

	if(fscanf(fs,"%c",&junk) != 1){
		return;
	}
	while(1){
		
	fscanf(fs,"%[^-]%*c",stu.Name);
	fscanf(fs,"%[^-]%*c",stu.SurName);
	fscanf(fs,"%d%*c",&(stu.StudentID));
	fscanf(fs,"%d%*c",&(stu.CoursesTaken));
	fscanf(fs,"%d%*c",&(stu.Credit));
	
	printf("Student information:\n");
	printf("Name: %s\n",stu.Name);
	printf("Sur Name: %s\n",stu.SurName);
	printf("StudentID: %d\n",stu.StudentID);
	printf("Total Courses: %d\n",stu.CoursesTaken);
	printf("Total credits: %d\n\n",stu.Credit);

	
	if(fscanf(fs,"%c",&junk) != 1){
		return;
		}
	}
	fclose(fs);
}

void print_to_the_file_courses(COURSES **chead){
	FILE *fp=fopen ("courses.txt","w+");
	if (fp==NULL)
	{
		printf("File cannot be opened\n");
		exit(0);
	}
	
	COURSES *varhead = (*chead);
	
	while(varhead != NULL)
	{
		fprintf(fp,"-%s-",(varhead->CourseCode)); 
		fprintf(fp,"%s-",(varhead->CourseName)); 
		fprintf(fp,"%d-",(varhead->Credit)); 
		fprintf(fp,"%d-",(varhead->Quota)); 
		fprintf(fp,"%d-",(varhead->LecturerID)); 
		varhead = varhead->next;		
	}
	fclose(fp);
	printf("\nFile is updated\n");
	
}

void read_from_file_courses(){
	COURSES cs;
	char junk;
	FILE *fs=fopen ("courses.txt","r");
	if (fs==NULL)
	{
		printf("File cannot be opened\n");
		exit(0);
	}
	if(fscanf(fs,"%c",&junk) != 1){
		return;
	}
	fscanf(fs,"%[^-]%*c",cs.CourseCode);
	fscanf(fs,"%[^-]%*c",cs.CourseName);
	fscanf(fs,"%d%*c",&(cs.Credit));
	fscanf(fs,"%d%*c",&(cs.Quota));
	fscanf(fs,"%d%*c",&(cs.LecturerID));
	
	printf("Course informations: \n");
	printf("Course Code: %s\n",cs.CourseCode);
	printf("Course Name: %s\n",cs.CourseName);
	printf("Credit: %d\n",cs.Credit);
	printf("Quota: %d\n",cs.Quota);
	printf("Lecturer ID: %d\n\n",cs.LecturerID);

	if(fscanf(fs,"%c",&junk) != 1){
		return;
	}
	while(1){
		
	fscanf(fs,"%[^-]%*c",cs.CourseCode);
	fscanf(fs,"%[^-]%*c",cs.CourseName);
	fscanf(fs,"%d%*c",&(cs.Credit));
	fscanf(fs,"%d%*c",&(cs.Quota));
	fscanf(fs,"%d%*c",&(cs.LecturerID));
	
	printf("Course informations: \n");
	printf("Course Code: %s\n",cs.CourseCode);
	printf("Course Name: %s\n",cs.CourseName);
	printf("Credit: %d\n",cs.Credit);
	printf("Quota: %d\n",cs.Quota);
	printf("Lecturer ID: %d\n\n",cs.LecturerID);

	
	if(fscanf(fs,"%c",&junk) != 1){
		return;
		}
	}
	fclose(fs);
	
}

RECORD* create_record(int number,char* code,char* state){	//this function creates elemts of the particular structure and returns pointer to it.
	RECORD *r;
	r = (RECORD*) malloc( sizeof( RECORD ) );
	if( r == NULL ) {
		printf("create_student: out of memory.");
		exit(1);
	}
	
	r->StudentID = number;
	strcpy(r->CourseCode,code);
	strcpy(r->State,state);

	r->next = NULL;
	return r;
}



void add_record_to_the_list(RECORD *new_node,RECORD **rhead){
	RECORD *varhead = (*rhead);
	if((*rhead) == NULL)
	{
		(*rhead) = new_node;
		return;
	}
	
	else 
	{
		while(varhead->next != NULL && ( (varhead->StudentID != new_node->StudentID) || (strcmp(varhead->CourseCode,new_node->CourseCode) == 1)))
		{	
			varhead = varhead->next;
		}
		if((varhead->StudentID == new_node->StudentID) && (strcmp(varhead->CourseCode,new_node->CourseCode) == 0) && (strcmp(varhead->State,"BIRAKTI") == 0)){
			strcpy(varhead->State,"ALDI");
		}
		if((varhead->StudentID == new_node->StudentID) && (strcmp(varhead->CourseCode,new_node->CourseCode) == 0)){
			return;
		}
	
		varhead->next = new_node;
	}
	
	
}


void print_to_the_file_record(RECORD **rhead){
	FILE *fp=fopen ("ogrenciderskayit.txt","w");
	if (fp==NULL)
	{
		printf("File cannot be opened\n");
		exit(0);
	}
	
	RECORD *var_head = (*rhead);
	while(var_head != NULL)
	{

		fprintf(fp,"<%d-",var_head->StudentID);
		fprintf(fp,"%s-",var_head->CourseCode);
		fprintf(fp,"%s>",var_head->State);
		var_head = var_head->next;		
	}
	fclose(fp);
	printf("\nFile is updated\n");
}



void RegisterTheCourse(RECORD **rhead,COURSES **chead,STUDENTS **head,int MAX_COURSE,int MAX_CREDIT){
	int number,kredi,ogrenci = 0,count = 0;
	char code[10];
	printf("\nCourses you can take:\n");
	read_from_file_courses();
	if(*chead==NULL){
	create_course_from_file(chead);
	}
	if(*chead == NULL){
		printf("there are no course\n");
		return;
	}
	printf("Enter the student number: ");
	scanf("%d",&number);
	printf("Enter the course code of the course you want to take:\n");
	scanf("%s",code);
	if((*rhead) == NULL){
		create_record_from_file(rhead);
	}
	if(*head==NULL){
		create_student_from_file(head);
	}
	RECORD *v;
	v = *rhead;
	COURSES* var_head;
	var_head = *chead;
	STUDENTS* varhead;
	varhead = *head;
	while(varhead != NULL){
		ogrenci++;
		if(varhead->StudentID != number){
			count++;
		}
		varhead = varhead->next;
	}
	if(ogrenci==count){
		printf("\nthere is no student with that number\n");
		return;
	}
	varhead = *head;
	
	while(v != NULL){
		if((v->StudentID == number) && (strcmp(v->CourseCode,code) == 0) && (strcmp(v->State,"ALDI") == 0)){
			printf("this course is already taken by the student\n");
			return;
		}
		v = v->next;
	}
	
	
	
	while(var_head != NULL){
		if(strcmp(var_head->CourseCode,code) == 0){
			kredi = var_head->Credit;
		}	
		var_head = var_head->next;	
	}
	
	
	
	while(varhead != NULL){
		if(varhead->StudentID == number){
			if(varhead->Credit + kredi <= MAX_CREDIT && varhead->CoursesTaken + 1 <= MAX_COURSE){
				varhead->Credit = varhead->Credit + kredi;
				varhead->CoursesTaken = varhead->CoursesTaken + 1;
				print_to_the_file(head);
			}
		}	
		varhead = varhead->next;	
	}

	
	add_record_to_the_list(create_record(number,code,"ALDI"), rhead);
	print_to_the_file_record(rhead);
	
}


void display_all_courses_taken_by_student_before_unregister(int num,RECORD **rhead){

	if((*rhead) == NULL){
		create_record_from_file(rhead);
	}
	
	RECORD *var_head;
	var_head = *rhead;
	printf("\nYOUR COURSES:\n");
	while(var_head != NULL){
	
		if(var_head->StudentID == num){
				if(strcmp(var_head->State,"ALDI")==0){
					printf("%s\n",var_head->CourseCode);
				}
			}
		var_head = var_head->next;
		
	}
	printf("\n");
}

void UnregisterTheCourse(RECORD **rhead,COURSES **chead,STUDENTS **head){
	int num,kredi;
	char cod[10];
	if((*rhead) == NULL){
		create_record_from_file(rhead);
	}
	
	if((*chead) == NULL){
		create_course_from_file(chead);
	}
	
	if((*head) == NULL){
		create_student_from_file(head);
	}
	
	printf("Enter the student number: ");
	scanf("%d",&num);
	display_all_courses_taken_by_student_before_unregister(num,rhead);
	
	printf("Enter the course code of the course you want to drop: ");
	scanf("%s",cod);
	
	RECORD *var_head;
	var_head = *rhead;
	STUDENTS *varhead;
	varhead = *head;
	COURSES *var;
	var = *chead;
	
	while(var != NULL){
		if(strcmp(var->CourseCode,cod) == 0){
			kredi = var->Credit;
		}
		var = var->next;
		
	}
	
	while(var_head != NULL){
	
		if(var_head->StudentID == num){
			if(strcmp(var_head->CourseCode,cod) == 0 ){
				strcpy(var_head->State,"BIRAKTI");
				print_to_the_file_record(rhead);
				while(varhead != NULL){
					if(varhead->StudentID == num){
						varhead->CoursesTaken = varhead->CoursesTaken - 1;
						varhead->Credit = varhead->Credit - kredi;
						
					}
					varhead = varhead->next;
				}
				print_to_the_file(head);
				
				
				return;
			}
		}
		var_head = var_head->next;
		
	}
	
	
}

void display_all_courses_taken_by_student(RECORD **rhead){

	int num;
	if((*rhead) == NULL){
		create_record_from_file(rhead);
	}
	printf("Enter the student number: ");
	scanf("%d",&num);
	
	RECORD *var_head;
	var_head = *rhead;
	printf("\nCOURSES:\n");
	while(var_head != NULL){
	
		if(var_head->StudentID == num){
				if(strcmp(var_head->State,"ALDI")==0){
					printf("%s\n",var_head->CourseCode);
				}
			}
		var_head = var_head->next;
		
	}
	printf("\n");
}

void studentlist(char *code,RECORD **rhead){
	if((*rhead)==NULL){
		create_record_from_file(rhead);
	}
	printf("\nStudent List:\n");
	RECORD *var;
	var = (*rhead);
	while(var != NULL){
		if(strcmp(var->CourseCode,code) == 0 && strcmp(var->State,"ALDI") == 0){
			printf("%d\n",var->StudentID);
			
		}
		var = var->next;
	}
		
}


void add_lecturer_to_the_list(LECTURERS* new_node,LECTURERS **lhead){
	
	LECTURERS *varhead = (*lhead);
	
	if((*lhead) == NULL)
	{	
		(*lhead) = new_node;
		return;
	}
	
	else 
	{
		while(varhead->next != NULL )
		{	
			varhead = varhead->next;
		}
	
		varhead->next = new_node;
	}
}


void create_lecturer_from_file(LECTURERS **lhead){

	FILE *f = fopen("lecturers.txt","r");
	
	LECTURERS *l;
	char junk;

	l = (LECTURERS*) malloc( sizeof( LECTURERS ) );
	if( l == NULL ) {
		printf("create_lecturers: out of memory.");
		exit(1);	
	}
	if(fscanf(f,"%c",&junk) != 1){
		free(l);
		fclose(f);
		return;
	}
	fscanf(f,"%[^-]%*c",l->Name);
	fscanf(f,"%[^-]%*c",l->SurName);
	fscanf(f,"%d%*c",&l->LecturerID);
	fscanf(f,"%[^-]%*c",l->Title);
	l->next = NULL;
	add_lecturer_to_the_list(l,lhead);

	if(fscanf(f,"%c",&junk) != 1){
		return;
	}
	
	while(1){
	l = (LECTURERS*) malloc( sizeof( LECTURERS ) );
	if( l == NULL ) {
		printf("create_lecturer: out of memory.");
		fclose(f);
		exit(1);	
	}
	fscanf(f,"%[^-]%*c",l->Name);
	fscanf(f,"%[^-]%*c",l->SurName);
	fscanf(f,"%d%*c",&l->LecturerID);
	fscanf(f,"%[^-]%*c",l->Title);
	l->next = NULL;
	add_lecturer_to_the_list(l,lhead);
	if(fscanf(f,"%c",&junk) != 1){
		fclose(f);
		return;
		}
	}
	
}

LECTURERS* create_lecturer(){
	char junk;
	LECTURERS *lect;
	lect = (LECTURERS*) malloc( sizeof( LECTURERS ) );
	if( lect == NULL ) {
		printf("create_lecturer: out of memory.");
		exit(1);
	}
	printf("Enter the lecturer's name: ");
	scanf("%c",&junk);
	scanf("%[^\n]",lect->Name);
	printf("Enter the lecturer's surname: ");
	scanf("%c",&junk);
	scanf("%[^\n]",lect->SurName); 
	printf("Enter the lecturer's ID': ");
	scanf("%d", &(lect->LecturerID)); 
	printf("Enter the lecturer's title': ");
	scanf("%c",&junk);
	scanf("%[^\n]",lect->Title);
	lect->next = NULL;
	return lect;
	
}


void print_to_the_file_lecturers(LECTURERS **lhead){
	
	FILE *fp=fopen ("lecturers.txt","w+");
	if (fp==NULL)
	{
		printf("File cannot be opened\n");
		exit(0);
	}
	
	LECTURERS *varhead = (*lhead);
	
	while(varhead != NULL)
	{
		fprintf(fp,"-%s-",varhead->Name); 
		fprintf(fp,"%s-",(varhead->SurName)); 
		fprintf(fp,"%d-",(varhead->LecturerID)); 
		fprintf(fp,"%s-",(varhead->Title)); 
		varhead = varhead->next;		
	}
	fclose(fp);
	printf("\nFile is updated\n");
	
	
	
}

void delete_lecturer(int number,STUDENTS**head,LECTURERS **lhead,COURSES **chead,RECORD **rhead){
	
	LECTURERS *temp = NULL, *var_head;
	COURSES *c;
	var_head = (*lhead);
	while(var_head != NULL)
	{
		if(var_head->LecturerID == number){
			temp = var_head;
			break;
		}
			
		var_head = var_head->next;
	}
	
	if(temp == (*lhead)){
		(*lhead) = (*lhead)->next;
		if(*chead == NULL)
			create_course_from_file(chead);
		c = *chead;
		while(c != NULL){
			if(c->LecturerID == number){
				delete_course(c->CourseCode,head,chead,rhead);
				print_to_the_file_courses(chead);
			}
			c = c->next;
		}
	}
	else
	{
	
		if(temp == NULL)
		{
			printf("\nCould not find the lecturer with that number");
			return;	
		}
		var_head = (*lhead);
		
		while(var_head->next != temp)
		{
			var_head = var_head->next;
		}

		var_head->next = var_head->next->next;
		if(*chead == NULL)
			create_course_from_file(chead);
		c = *chead;
		while(c != NULL){
			if(c->LecturerID == number){
				delete_course(c->CourseCode,head,chead,rhead);
				print_to_the_file_courses(chead);
			}
			c = c->next;
		}
		free(temp);
	}
}
void list_courses(COURSES **chead,int id){
	if(*chead == NULL){
		create_course_from_file(chead);
	}
	COURSES *var_head;
	var_head = *chead;
	printf("\nlecturer's courses:\n");
	while(var_head != NULL){
		if(var_head->LecturerID == id){
			printf("%s  (%s)\n",var_head->CourseName,var_head->CourseCode);

		}
		var_head = var_head->next;
	}

}
void read_from_file_lecturers(){
	
	LECTURERS lec;
	char junk;
	FILE *fs=fopen ("lecturers.txt","r");
	if (fs==NULL)
	{
		printf("File cannot be opened\n");
		exit(0);
	}
	if(fscanf(fs,"%c",&junk) != 1){
		return;
	}
	fscanf(fs,"%[^-]%*c",lec.Name);
	fscanf(fs,"%[^-]%*c",lec.SurName);
	fscanf(fs,"%d%*c",&(lec.LecturerID));
	fscanf(fs,"%[^-]%*c",(lec.Title));
	
	printf("\nLecturer's Information:\n");
	printf("Name: %s\n",lec.Name);
	printf("SurName: %s\n",lec.SurName);
	printf("LecturerID: %d\n",lec.LecturerID);
	printf("Title: %s\n",lec.Title);

	if(fscanf(fs,"%c",&junk) != 1){
		return;
	}
	while(1){
		
	fscanf(fs,"%[^-]%*c",lec.Name);
	fscanf(fs,"%[^-]%*c",lec.SurName);
	fscanf(fs,"%d%*c",&(lec.LecturerID));
	fscanf(fs,"%[^-]%*c",(lec.Title));
	
	printf("Lecturer's Information:\n");
	printf("Name: %s\n",lec.Name);
	printf("SurName: %s\n",lec.SurName);
	printf("LecturerID: %d\n",lec.LecturerID);
	printf("Title: %s\n",lec.Title);;

	
	if(fscanf(fs,"%c",&junk) != 1){
		return;
		}
	}
	fclose(fs);
	
}


void student_list_of_a_course(STUDENTS **head,COURSES **chead,RECORD **rhead){
	int id;
	char code[20];
	COURSES *css;
	RECORD *rec;
	STUDENTS *st;
	FILE *f = fopen("coursecode_classlist.txt","w+");
	if (f==NULL)
	{
		printf("File cannot be opened\n");
		exit(0);
	}
	if(*head==NULL){
		create_student_from_file(head);
	}
	st = *head;
	if(*chead==NULL){
		create_course_from_file(chead);
	}
	css = (*chead);
	if(*rhead==NULL){
		create_record_from_file(rhead);
	}
	rec = *rhead;
	
	printf("Enter The Lecturer's ID:\n");
	scanf("%d",&id);
	//display lecturers courses
	printf("Lecturer's Courses:\n\n");
	
	while(css != NULL){
		if(css->LecturerID == id){
			printf("%s\n",css->CourseCode);
		}
		css = css->next;		
	}
	

	printf("Enter the CourseCode: \n");
	scanf("%s",code);
	
	while(rec != NULL){
		if(strcmp(rec->CourseCode,code) == 0){
			if(strcmp(rec->State,"ALDI") == 0){
				st = *head;
				while(st != NULL){
					if(st->StudentID == rec->StudentID){
						fprintf(f,"-%s-",st->Name);
						fprintf(f,"%s-",st->SurName);
						fprintf(f,"%d-",st->StudentID);
					}
					st = st->next;
				}
			}
		}
		rec = rec->next;
	}
	fclose(f);
		
	
}

void read_student_list(){
	FILE *fs = fopen("coursecode_classlist.txt","r");
	STUDENTS stu;
	char junk;
	if (fs==NULL)
	{
		printf("File cannot be opened\n");
		exit(0);
	}
	if(fscanf(fs,"%c",&junk) != 1){
		return;
	}
	fscanf(fs,"%[^-]%*c",stu.Name);
	fscanf(fs,"%[^-]%*c",stu.SurName);
	fscanf(fs,"%d%*c",&(stu.StudentID));
	
	printf("\nClass List:\n");
	printf("Name: %s ",stu.Name);
	printf("%s(",stu.SurName);
	printf("%d)\n",stu.StudentID);


	if(fscanf(fs,"%c",&junk) != 1){
		return;
	}
	while(1){
		
	fscanf(fs,"%[^-]%*c",stu.Name);
	fscanf(fs,"%[^-]%*c",stu.SurName);
	fscanf(fs,"%d%*c",&(stu.StudentID));
	
	printf("Name: %s ",stu.Name);
	printf("%s(",stu.SurName);
	printf("%d)\n",stu.StudentID);

	
	if(fscanf(fs,"%c",&junk) != 1){
		return;
		}
	}
	fclose(fs);
	
}



int main(){
	STUDENTS *head = NULL;
	COURSES *chead = NULL;
	LECTURERS *lhead = NULL;
	RECORD *rhead = NULL;
	char name[20];
	char junkie;
	int number,MAX_COURSE,MAX_CREDIT;
	char co[20];
	int c,d;
	printf("Enter The Maximum Courses A Student Can Take:\n");
	scanf("%d",&MAX_COURSE);
	printf("Enter The Maximum Credit A Student Can Take:\n");
	scanf("%d",&MAX_CREDIT);
	
while(1){
	printf("Select the thing you want to do operations on.\n");
	printf("For students press 1...\n");
	printf("For courses press 2...\n");
	printf("For lecturers press 3...\n");
	printf("To quit press 4...\n");
	scanf("%d",&c);
	switch(c){
		case 1:
			while(1){
				printf("To add a new student press 1...\n");
				printf("To delete a student press 2...\n");
				printf("To register to a course press 3...\n");
				printf("To unregister from a course press 4...\n");
				printf("To see the courses taken by a student press 5...\n");
				printf("To display all the students press 6...\n");
				printf("To jump previous menu presss 7... \n");
				scanf("%d",&c);
				switch(c){
					case 1:
						create_student_from_file(&head);
						add_student_to_the_list(create_student(), &head);
						print_to_the_file(&head);
						break;	
					case 2:
						printf("Enter the number of the student you want to delete from list: ");
						scanf("%d",&d);
						create_student_from_file(&head);
						delete_student(d,&head);
						print_to_the_file(&head);
						break;
					case 3:
						RegisterTheCourse(&rhead,&chead,&head,MAX_COURSE,MAX_CREDIT);
						break;
						
					case 4:
						UnregisterTheCourse(&rhead,&chead,&head);
						break;
					case 5:
						display_all_courses_taken_by_student(&rhead);
						break;
					case 6:
						read_from_file();
						break;
					case 7:
						break;	
				}
				if(c == 7)
					break;
				
			}
			break;
			
		case 2:
			while(1){
				printf("To add a new course press 1...\n");
				printf("To delete a course press 2...\n");
				printf("To display all students which takes course whose code is given press 3...\n");
				printf("To display all courses press 4...\n");
				printf("To jump to previous menu presss 5... \n");
				scanf("%d",&c);	
				switch(c){
					case 1:
						if(chead==NULL)
							create_course_from_file(&chead);
						add_course_to_the_list(create_course(), &chead);
						print_to_the_file_courses(&chead);	
						break;	
					case 2:
						printf("Enter the course code of the course you want to delete from list: ");
						scanf("%s",co);
						if(chead == NULL)
							create_course_from_file(&chead);
						delete_course(co,&head,&chead,&rhead);
						print_to_the_file_courses(&chead);
						break;
					case 3:
						printf("type the course code: ");
						scanf("%s",co);
						studentlist(co,&rhead);
						
						break;
					case 4:
						read_from_file_courses();
						break;
					case 5:
						break;
				}	
				if (c == 5)
					break;
		
		}
			break;
		case 3:
			while(1){
				printf("\nTo add a new lecturer press 1...\n");
				printf("To delete a lecturer press 2...\n");
				printf("To display all the courses given by one particular lecturer press 3...\n");
				printf("To display all the lecturers press 4...\n");
				printf("To display student list of a course given by particular lecturer press 5...\n");
				printf("To jump to previous menu press 6...\n");
				scanf("%d",&c);
				switch(c){
					case 1:
						if(lhead==NULL)
							create_lecturer_from_file(&lhead);
						add_lecturer_to_the_list(create_lecturer(), &lhead);
						print_to_the_file_lecturers(&lhead);
						break;
					case 2:
						printf("Enter the lecturer's ID you want to delete from list: ");
						scanf("%d",&d);
						if(lhead==NULL)
							create_lecturer_from_file(&lhead);
						delete_lecturer(d,&head,&lhead,&chead,&rhead);
						print_to_the_file_lecturers(&lhead);
						break;
					case 3:
						printf("Enter the lecturer's ID: ");
						scanf("%d",&d);
						list_courses(&chead,d);
						break;
					case 4:
						read_from_file_lecturers();
						break;
					case 5:
						student_list_of_a_course(&head,&chead,&rhead);
						read_student_list();
						break;
					case 6:
						break;	
				}
				if(c == 6)
					break;
				
			}
			break;	
		
				
		case 4:
			return 0;
		}
	
	}	

	
}
