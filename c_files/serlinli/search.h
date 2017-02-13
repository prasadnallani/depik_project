#define MAX_RECORDS  10
struct record
{
  int phone;
  char name[30];
};
enum {SER=1,ADD,DEL,DISP,XIT};
enum {SUCCESS,OVRFLOW_ERR,REC_NOT_FOUND_ERR,NO_MEMORY_ERR};

int searchRec(int phone,struct record *prec);
int addRec(const struct record *prec);
int delRec(int phone);
void displayAllRecs();
