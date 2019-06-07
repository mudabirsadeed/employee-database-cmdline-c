#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* maximum number of employees that can be stored at once (relevant only
   to storage using an array) */
#define MAX_EMPLOYEES 200
#define MAX_EMPLOYEE_AGE 130
#define MAX_NAME_LENGTH 100
#define MAX_JOB_LENGTH  100

/* Employee structure
 */
struct Employee
{
   /* Employee details */
   char name[MAX_NAME_LENGTH+1]; /* name string */
   char sex;                     /* sex identifier, either 'M' or 'F' */
   int  age;                     /* age */
   char job[MAX_JOB_LENGTH+1];   /* job string */
   
   /* pointers to previous and next employee structures in the linked list
      (for if you use a linked list instead of an array) */
   struct Employee *prev, *next;
};

static struct Employee list[MAX_EMPLOYEES];
static int total_employees=0;
static void bubble_sort(void);
static void blank_erase(void);


/* read_line():
 *
 * Read line of characters from file pointer "fp", copying the characters
 * into the "line" string, up to a maximum of "max_length" characters, plus
 * one for the string termination character '\0'. Reading stops upon
 * encountering the end-of-line character '\n', for which '\0' is substituted
 * in the string. If the end of file character EOF is reached before the end
 * of the line, the failure condition (-1) is returned. If the line is longer
 * than the maximum length "max_length" of the string, the extra characters
 * are read but ignored. Success is returned (0) on successfully reading
 * a line.
 */
static int read_line ( FILE *fp, char *line, int max_length )
{
   int i;
   char ch;

   /* initialize index to string character */
   i = 0;

   /* read to end of line, filling in characters in string up to its
      maximum length, and ignoring the rest, if any */
   for(;;)
   {
      /* read next character */
      ch = fgetc(fp);

      /* check for end of file error */
      if ( ch == EOF )
	 return -1;

      /* check for end of line */
      if ( ch == '\n' )
      {
	 /* terminate string and return */
	 line[i] = '\0';
	 return 0;
      }

      /* fill character in string if it is not already full*/
      if ( i < max_length )
	 line[i++] = ch;
   }

   /* the program should never reach here */
   return -1;
}

/* read_string():
 *
 * Reads a line from the input file pointer "fp", starting with the "prefix"
 * string, and filling the string "string" with the remainder of the contents
 * of the line. If the start of the line does not match the "prefix" string,
 * the error condition (-1) is returned. Having read the prefix string,
 * read_string() calls read_line() to read the remainder of the line into
 * "string", up to a maximum length "max_length", and returns the result.
 */
static int read_string ( FILE *fp,
			 char *prefix, char *string, int max_length )
{
   int i;

   /* read prefix string */
   for ( i = 0; i < strlen(prefix); i++ )
      if ( fgetc(fp) != prefix[i] )
	 /* file input doesn't match prefix */
	 return -1;

   /* read remaining part of line of input into string */
   return ( read_line ( fp, string, max_length ) );
}

/* menu_add_employee():
 *
 * Add new employee to database
 */
static void menu_add_employee(void)
{
  struct Employee employee;
    
    
    char age[200];
 /*reads the name from stdin and copies it into employee, while also checking for errors*/
  fprintf(stderr,"Enter Name (Surname first):");
  read_line(stdin,employee.name, MAX_NAME_LENGTH);
  while(strlen(employee.name) == 0 || strlen(employee.name) >= MAX_NAME_LENGTH )
  {
   fprintf(stderr, "Invalid name. Please enter a valid name (Surname first):");
   read_line(stdin,employee.name, MAX_NAME_LENGTH);
  }

 /*reads the sex from stdin and copies it into employee, while also checking for errors*/
  fprintf(stderr, "Enter Sex:");
  read_line(stdin,&employee.sex, 1);
  while(employee.sex != 'M' && employee.sex != 'm' && employee.sex != 'F' && employee.sex != 'f')
   {
    fprintf(stderr, "Invalid Sex. Please enter valid sex (M or F):");
    read_line(stdin,&employee.sex, 1);
   }

/*reads the age from stdin and copies it into employee, while also checking for errors and being over-limit.*/
 fprintf(stderr, "Enter Age:");
  read_line(stdin, age, 199);
  sscanf(age, "%i", &employee.age);
  while(employee.age <= 0 || employee.age >= 130)
   {
    fprintf(stderr, "Invalid Age. Please enter valid age (0<age<130):");
    read_line(stdin, age, 199);
    sscanf(age, "%i", &employee.age);
   }
  

 /*reads the job from stdin and copies it into employee, while also checking for errors*/
  fprintf(stderr, "Enter Job Description:");
  read_line(stdin, employee.job, MAX_JOB_LENGTH);
  while(strlen(employee.job) >= MAX_JOB_LENGTH || strlen(employee.job) == 0)
   {
    fprintf(stderr, "Invalid Job. Please enter valid job:");
    read_line(stdin,&employee.job, 199);
   }
   /*copies employee into the list array*/
  list[total_employees]=employee;
  
  total_employees++;
  bubble_sort();
  fprintf(stderr, "\n");
 
 
}

/* menu_print_database():
 *
 * Print database of employees to standard output.
 */
static void menu_print_database(void)
{
	/*prints each entry in list array up to total_employees*/
   int i;
 for(i = 0; i<total_employees;i++) 
 {
  printf("Name:%s\n",list[i].name);
  printf("Sex:%c\n", list[i].sex);  
  printf("Age:%i\n", list[i].age);
  printf("Job:%s\n", list[i].job);
  printf("\n");
 }
 /*if there are no employees, the below message is printed*/
 if(total_employees==0)
 {
	 fprintf(stderr, "\nNo Employees in Database\n");
 }
 
}	    

/* menu_delete_employee():
 *
 * Delete new employee from database.
 */
static void menu_delete_employee(void)
{
  char name[MAX_NAME_LENGTH+1];
  int i=0,j, k, l=0;
 
  fprintf(stderr,"Enter Name to be deleted(Surname first and exact):");
  read_line(stdin, name, MAX_NAME_LENGTH);

  for (i=0;i<total_employees;i++)
   {
	/*compares the input to all the names in array up to total_employees*/  
    j=strcmp(name, list[i].name);
    /*if a match is found, all of its fields are set to 0, resorted and the blank entry erased. l changes to show that a deletion has taken place*/
    if(j == 0)
     {
		 for(k=0;k<=MAX_NAME_LENGTH+1;k++)
			{  
				list[i].name[k]=0;
			}
   		 for(k=0;k<=MAX_JOB_LENGTH+1;k++)
   			{  
   				list[i].job[k]=0;
   			}
		 list[i].age=0;
		 list[i].sex=0;
		 bubble_sort();
		 blank_erase();
		 
		 fprintf(stderr,"\nEmployee Deleted\n");
		 l=1;
     }
 }/*if a match hasnt been found and a deletion hasnt taken place then the message below is displayed on the console*/
 if (j!=0 && l!=1)
    {
     fprintf(stderr, "\nEmployee Not Found\n");
    }
	
}

/* read file containing database of employees */
static void read_employee_database ( char *file_name ) 
{
	int flag=0;
	FILE *fp;
	
	char arbitrary[200];
	char age[200];
	
	
	fp=fopen(file_name, "r");
	
	while(flag != -1)
	{
		/*reads the name from the file and copies it into the list array, while also checking for errors*/
	flag=read_string(fp,"Name: ",list[total_employees].name, MAX_NAME_LENGTH);
    while((strlen(list[total_employees].name) == 0 || strlen(list[total_employees].name) >= MAX_NAME_LENGTH) && flag !=-1)
    {
     fprintf(stderr, "Invalid Name detected. Terminating program.\n");
     exit(EXIT_FAILURE);
    }
   
		/*reads the sex from the file and copies it into the list array, while also checking for errors*/    
	flag=read_string(fp,"Sex: ", &list[total_employees].sex, 1);
	while((list[total_employees].sex != 'M' && list[total_employees].sex != 'm' && list[total_employees].sex != 'F' && list[total_employees].sex != 'f')&& flag !=-1)
     {
      fprintf(stderr, "Invalid Sex detected. Terminating program.\n");
      exit(EXIT_FAILURE);
     }
		
		/*reads the age from the file and copies it into the list array, while also checking for errors and being over-limit. */
	flag=read_string(fp,"Age: ",age,199);
	sscanf(age, "%i", &list[total_employees].age);
	while((list[total_employees].age <= 0 || list[total_employees].age >= MAX_EMPLOYEE_AGE)&& flag !=-1)
     {
      fprintf(stderr, "Invalid Age detected. Terminating program.\n");
      exit(EXIT_FAILURE);
     }
	
		/*reads the job from the file and copies it into the list array, while also checking for errors*/
	flag=read_string(fp,"Job: ", list[total_employees].job, MAX_JOB_LENGTH);
	while((strlen(list[total_employees].job) >= MAX_JOB_LENGTH || strlen(list[total_employees].job) == 0)&& flag !=-1)
     {
      fprintf(stderr, "Invalid Job detected. Terminating program.\n");
      exit(EXIT_FAILURE);
     }
	
	 /*an arbitrary read_string, to skip the blank lines between each entry*/
	read_string(fp,"Name: ",arbitrary ,MAX_NAME_LENGTH);
	
	
	total_employees++;
	bubble_sort();
	
    }
	/*the loop iterates one time too many, so once the list is fully sorted the blank comes to the top and is erased by blank_erase*/
	blank_erase();
	fclose(fp);
}

/* codes for menu */
#define ADD_CODE    0
#define DELETE_CODE 1
#define PRINT_CODE  2
#define EXIT_CODE   3

int main ( int argc, char *argv[] )
{
   /* check arguments */
   if ( argc != 1 && argc != 2 )
   {
      fprintf ( stderr, "Usage: %s [<database-file>]\n", argv[0] );
      exit(-1);
   }

   /* read database file if provided, or start with empty database */
   if ( argc == 2 )
      read_employee_database ( argv[1] );

   for(;;)
   {
      int choice, result;
      char line[301];

      /* print menu to standard error */
      fprintf ( stderr, "\nOptions:\n" );
      fprintf ( stderr, "%d: Add new employee to database\n", ADD_CODE );
      fprintf ( stderr, "%d: Delete employee from database\n", DELETE_CODE );
      fprintf ( stderr, "%d: Print database to screen\n", PRINT_CODE );
      fprintf ( stderr, "%d: Exit database program\n", EXIT_CODE );
      fprintf ( stderr, "\nEnter option: " );

      if ( read_line ( stdin, line, 300 ) != 0 ) continue;

      result = sscanf ( line, "%d", &choice );
      if ( result != 1 )
      {
	 fprintf ( stderr, "corrupted menu choice\n" );
	 continue;
      }

      switch ( choice )
      {
         case ADD_CODE: /* add employee to database */
	 menu_add_employee();
	 break;

         case DELETE_CODE: /* delete employee from database */
	 menu_delete_employee();
	 break;

         case PRINT_CODE: /* print database contents to screen
			     (standard output) */
	 menu_print_database();
	 break;

	 /* exit */
         case EXIT_CODE:
	 break;

         default:
	 fprintf ( stderr, "illegal choice %d\n", choice );
	 break;
      }

      /* check for exit menu choice */
      if ( choice == EXIT_CODE )
	 break;
   }

   return 0;   
}
/*sorts the list array up to total_employees*/
static void bubble_sort(void)
{
int i,j;
struct Employee temp;
for(i=0; i<total_employees; i++)
        for(j=0; j<total_employees-1; j++)
        {
            if(strcmp(list[j].name,list[j+1].name)>0)
            {
                strcpy(temp.name,list[j+1].name);
                temp.sex=list[j+1].sex; 
                temp.age=list[j+1].age;
                strcpy(temp.job,list[j+1].job);

                strcpy(list[j+1].name,list[j].name);
                list[j+1].sex=list[j].sex; 
                list[j+1].age=list[j].age;
                strcpy(list[j+1].job,list[j].job);

                strcpy(list[j].name,temp.name);
                list[j].sex=temp.sex; 
                list[j].age=temp.age;
                strcpy(list[j].job,temp.job);
            }   
        }
}
/*once an entry in the database is deleted and resorted, this moves all the entries up by one so as to overwrite the blank space*/
static void blank_erase(void)
{
	int j;
	struct Employee temp;
	
			for(j=0;j<=total_employees;j++)
			{
                strcpy(temp.name,list[j].name);
                temp.sex=list[j].sex; 
                temp.age=list[j].age;
                strcpy(temp.job,list[j].job);

                strcpy(list[j].name,list[j+1].name);
                list[j].sex=list[j+1].sex; 
                list[j].age=list[j+1].age;
                strcpy(list[j].job,list[j+1].job);

                strcpy(list[j+1].name,temp.name);
                list[j+1].sex=temp.sex; 
                list[j+1].age=temp.age;
                strcpy(list[j+1].job,temp.job);
			}
			
			total_employees--;
}