#include "sqlCon.h"
#include <iostream>
#include <string.h>
#include <vector>
 int sqlCon::callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    fprintf(stderr,"%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

sqlCon::sqlCon(char*){
  stmt = 0;
  zErrMsg = 0;

   fprintf(stderr, "Opening DB \n");
    rc = sqlite3_open( "ha.db", &db);
    if( rc ){
        fprintf(stderr,"Can't open database: %s\n", sqlite3_errmsg(db));
  }
     fprintf(stderr, "DB READY \n");

}

int sqlCon::execute(char *command){

  //char **result;
  int nrow;
  int ncol;
   fprintf(stderr, "Executing Command \n");

    rc = sqlite3_prepare(db, "PRAGMA table_info(learnss)", strlen(command), &stmt, 0);
    int col_cnt = sqlite3_column_count(stmt);
    printf("do tokanizing on  #%i Cols\n",col_cnt);



            sqlite3_reset(stmt);
            int result;

            for ( int i=0; i < col_cnt/2  ;i++){
                    rc = sqlite3_step(stmt);

                const  unsigned char* vp = sqlite3_column_text(stmt, i);
                printf( "%s ", vp);
            };
            printf("   =-=");
       //     sqlite3_finalize(stmt);


   rc = sqlite3_prepare(db, command, strlen(command), &stmt, 0); // -1 for the string length seems to work too.
    //  rc = sqlite3_exec(db, command, sqlCon::callback, 0, &zErrMsg);



/*  <<they should make coment folding into CB for certain things
      rc = sqlite3_get_table(
			db,              // An open database
			command,        //SQL to be executed
			&result,        //Result written to a char *[]  that this points to
			&nrow,          //    Number of result rows written here
			&ncol,           //Number of result columns written here
			&zErrMsg          // Error msg written here
			);

	  printf("nrow=%d ncol=%d\n",nrow,ncol);
	 // printf("PRINTING 2 ROWS ONLY \n");
        for(int i=0 ; i < nrow+ncol; ++i){
            printf("#%i ",i);
            printf("%s ",result[i]);
            //++i;
            //printf("#%i ",i);
            //printf("%s \n",result[i]);
        }
*/

printf("   =-=");
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

    int rowcount;
   col_cnt = sqlite3_column_count(stmt);
printf("there is #%i columns \n",col_cnt);
bool  finished = false;
  while (!finished) {
      if(col_cnt !=0){
    rc = sqlite3_step(stmt);
    switch (rc) {
      case SQLITE_DONE:     //Execution finished.
        finished = true;
        sqlite3_reset(stmt);  //Resets the compiled statement for re-use.
        //Execute logic for end of data set.
        break;
      case SQLITE_ROW:      //We have a row.
        if (rowcount == 0) {
         // Execute code for start of data set

        }

        //Scan all the columns.  Return value in "strg"
        for (int a = 0; a < col_cnt; a++) {
          //Get actual type.
          switch (sqlite3_column_type(stmt, a)) {
            case SQLITE_INTEGER:
              result = sqlite3_column_int(stmt, a);
              printf( "%d ", result);
              break;
            case SQLITE_FLOAT:
              {
                //Float to string.
                double  dub;
                dub = sqlite3_column_double(stmt, a);
                printf( "%f", dub);
              }
              break;
            case SQLITE_TEXT:
             {
                const  unsigned char* vp = sqlite3_column_text(stmt, a);
                //  sqlite3_stmt *p = stmt;
                printf( "%s ", vp);
                //  while (*vp > 0)            //        { *p++ = *vp++;}
              break;
              }
            case SQLITE_BLOB:
              //Write to a file, dynamic memory ...
              break;
            case SQLITE_NULL:
             {
        //   stmt[0] = 0;
              break;
             }
          }  //switch
        }    //for
 printf( "\n");
       rowcount++;
        break;
             default:
             {
        sqlite3_finalize(stmt);
        break;
             }
    };
  } else {
      printf( "EXECUTED A COMMAND WITH NULL RESULTS\n");
     finished = true;};
 };

//  sqlite3_finalize(stmt);
//  sqlite3_free_table(result);
//  rc = sqlite3_step(stmt);
}

sqlCon::~sqlCon(){
  sqlite3_close(db);
}

std::vector<std::string> tokens2;

std::vector<std::string> tokenize(const std::string & delim , const std::string & str )
{
  using namespace std;
  vector<string> tokens;

  size_t p0 = 0, p1 = string::npos;
  while(p0 != string::npos)
  {
    p1 = str.find_first_of(delim, p0);
    if(p1 != p0)
    {
      string token = str.substr(p0, p1 - p0);
      tokens.push_back(token);
    }
    p0 = str.find_first_not_of(delim, p1);
  }

  return tokens;
}



/* THREADED EXAMPLE

#include <stdio.h>
#include <pthread.h>
#include "sqlite3.h"

void* myInsert(void* arg)
{
   sqlite3*      db = 0;
   sqlite3_stmt* stmt = 0;
   int val = (int)arg;
   char SQL[100];
   int rc;
   rc = sqlite3_open("MyDB", &db); // Open a database named MyDB
   if (rc != SQLITE_OK) {
     fprintf(stderr, "Thread[%d] fails to open the database\n",   val);
     goto errorRet;
   }

   // Create the SQL string. If you were using string values,
   //   you would need to use sqlite3_prepare() and sqlite3_bind_*
   //   to avoid an SQL injection vulnerability. However %d
   //   guarantees an integer value, so this use of sprintf is
  //    safe.

   sprintf(SQL, "insert into Students values(%d)", val);

   // Prepare the insert statement
   rc = sqlite3_prepare(db, SQL, -1, &stmt, 0);
   if (rc != SQLITE_OK) {
     fprintf(stderr, "Thread[%d] fails to prepare SQL: %s ->
return code %d\n", val, SQL, rc);
     goto errorRet;
   }
   rc = sqlite3_step(stmt);
   if (rc != SQLITE_DONE) {
     fprintf(stderr,
       "Thread[%d] fails to execute SQL: %s -> return code %d\n", val, SQL, rc);
   }
   else {
     printf("Thread[%d] successfully executes SQL: %s\n", val,
       SQL);
   }
   errorRet:
      sqlite3_close(db);
      return (void*)rc;
}


int main(void)
{
   pthread_t t[10];
   int i;
   for (i=0; i < 10; i++)
     pthread_create(&t[i], 0, myInsert, (void*)i); // Pass the value of i

   // wait for all threads to finish
   for (i=0; i<10; i++)  pthread_join(t[i], 0);
   return 0;
}

*/
