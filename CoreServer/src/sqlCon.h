#ifndef SQLCON_H
#define SQLCON_H

#include <string>
#include <stdio.h>
#include <sqlite3.h>


class sqlCon
{
public:
    sqlCon(char*);
    ~sqlCon();
    sqlite3_stmt* stmt;
char *zErrMsg;
  int rc;
  sqlite3 *db;
  int execute(char*);
  static int callback(void *, int , char **, char **);
};

#endif
