//#define MAX_Q_SIZE   5
#define MAX_CQ_SIZE 10
struct student
{
  int id;
  int phone;
  char name[30];
};
enum {SUCCESS,CIRQ_FULL_ERR,CIRQ_EMPTY_ERR};
enum {ENTER=1,DELETE,DISPALL,EXIT};
int enqItem(const struct student *ps);
int deqItem(struct student *ps);
