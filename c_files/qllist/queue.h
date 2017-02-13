#define MAX_Q_SIZE   5
struct student
{
  int id;
  int phone;
  char name[30];
};
enum {SUCCESS,QUEUE_FULL_ERR,QUEUE_EMPTY_ERR};
enum {ENTER=1,DELETE,DISPALL,EXIT};
int enqItem(const struct student *ps);
int deqItem(struct student *ps);
