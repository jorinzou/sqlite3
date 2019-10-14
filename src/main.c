#include <stdio.h>

#include "sqlite3.h"
#include "main.h"

#define DEBUG_INFO(fmt, args...) printf("\033[33m[%s:%s:%d]\033[0m "#fmt"\r\n", __FILE__,__FUNCTION__, __LINE__, ##args)

int mycallback(void *data, int argc, char **argv, char **azColName)
{
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

//创建或者打开已存在的数据库文件
int OpenSqlite(const char *DbFilePath,sqlite3 **db)
{
    int ret = 0;
    ret = sqlite3_open(DbFilePath,db);
    if(ret != SQLITE_OK){
        fprintf(stderr,"Cannot open db: %s\n",sqlite3_errmsg(*db));
        return -1;
    }
    DEBUG_INFO("Open database\n");
    return 0;
}

//创建一个数据库表
int CreateSqliteTable(sqlite3 *db,const char *sql)
{
   if (NULL == db)
        return -1;
   
   int ret = 0;
   char *zErrMsg = 0;
   ret = sqlite3_exec(db, sql, mycallback, 0, &zErrMsg);
   if(ret != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return -1;
   }else{
      fprintf(stdout, "Table created successfully\n");
      return 0;
   }
}

//sqlite表插入数据
int InsertSqliteata(sqlite3 *db,const char *sql)
{
   if (NULL == db)
        return -1;
   
   int ret = 0;
   char *zErrMsg = NULL;
   ret = sqlite3_exec(db, sql, mycallback, 0, &zErrMsg);
   if( ret != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return -1;
   }else{
      fprintf(stdout, "Records created successfully\n");
      return 0;
   }
}

//查询数据库
int LookUpSqlite(sqlite3 *db,const char *sql)
{
   if(NULL == db)
     return -1;
   
   int ret = 0;
   char *zErrMsg = NULL;
   const char* data = "Callback function called";
   ret = sqlite3_exec(db, sql, mycallback, (void*)data, &zErrMsg);
   if( ret != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return -1;
   }else{
      fprintf(stdout, "Operation done successfully\n");
      return 0;
   }
}

//删除数据库表中某条数据
int DeleteSqlite(sqlite3 *db,const char *sql)
{
    if (NULL == db)
        return -1;
   
   int ret = 0;
   char *zErrMsg = NULL;
   ret = sqlite3_exec(db, sql, mycallback, 0, &zErrMsg);
   if( ret != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return -1;
   }else{
      fprintf(stdout, "Records created successfully\n");
      return 0;
   }
}

//sqlite修改操作
int UpdateSqlite(sqlite3 *db,const char *sql)
{
  if (NULL == db)
        return -1;
   
   int ret = 0;
   char *zErrMsg = NULL;
   ret = sqlite3_exec(db, sql, mycallback, 0, &zErrMsg);
   if( ret != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return -1;
   }else{
      fprintf(stdout, "Records created successfully\n");
      return 0;
   }  
}

int main(void)
{
    
    sqlite3 *db = 0;
    OpenSqlite("./db/company.db",&db);

    const char *sql = NULL;
    char *errmsg = 0;
    
   /* 创建数据库表格 */
   sql = "CREATE TABLE COMPANY("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SALARY         REAL );";
   CreateSqliteTable(db, sql);

   /* 在数据库表中插入数据 */
   sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
   InsertSqliteata(db,sql);

    /*查询整个表格数据*/
   //sql = "select * from COMPANY";
   /*查询id=1的数据*/
   sql = "SELECT * FROM COMPANY WHERE ID=1";
   /*查询id=1,或者id=2的数据*/
   //sql = "SELECT * FROM COMPANY WHERE ID=1 OR ID=2";
   DEBUG_INFO("sql=%s",sql);
   LookUpSqlite(db,sql);

   //删除表中某条数据
   sql = "DELETE from COMPANY WHERE ID = 1";
   DeleteSqlite(db,sql);

   //sql = "SELECT * FROM COMPANY WHERE ID=1";
   //LookUpSqlite(db,sql);


   sql = "UPDATE COMPANY SET SALARY = 888888888.00 WHERE ID = 2;";
   UpdateSqlite(db,sql);
   
   sqlite3_close(db);

    return 0;
}



































