#define MAX_STK_SIZE   5
struct student
{
  int id;
  int phone;
  char name[30];
};
enum {SUCCESS,STK_FULL_ERR,STK_EMPTY_ERR};
enum {PUSH=1,POP,DISPALL,EXIT};
int pushItem(const struct student *ps);
int popItem(struct student *ps);
