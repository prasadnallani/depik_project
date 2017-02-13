#define MAX_RECORDS    5 // 10
enum {SUCCESS,ARRAY_OVERFLOW_ERR,PH_NUM_NOT_FOUND_ERR};
enum {ADD_TO_END=1,ADD_TO_START,DELETE,GET,INSERT,DISPLAY_ALL,EXIT};

struct phoneRec
{
  int phoneNo;
  char name[20];
  char addrs[40];
 };
int addRecToEnd(const struct phoneRec *pr);
int addRecToStart(const struct phoneRec *pr);
int deleteRec(int phNo);
int insertRec(const struct phoneRec *pr);
int getPhoneRec(int phNo,struct phoneRec *pr);
void displayAllRecs();
