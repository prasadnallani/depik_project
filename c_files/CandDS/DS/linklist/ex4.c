
/********************************************************************
         	Operations on linked lists 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>

/************ macros ************/
#define SUCESS 	0
#define ERR	1
#define NODE_NOT_FOUND 2
#define NO_NODES_ERR    3
/********* global variables ***********/

typedef struct sampNode
{

  int 		info;
  struct sampNode *pPrevNode;
  struct sampNode *pNxtNode;

} sampNode_t;

sampNode_t *pHead;
sampNode_t *pTail;

/********* function prototypes ***********/
void addNodeToHead(sampNode_t *pNode);
void dispNode(sampNode_t *pNode);
void fillNode(sampNode_t *pNode);
sampNode_t *allocateMemory4Node(void);
void dispNodes(void);
int getValue(void);


/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void addNodeToHead(sampNode_t *pNode)
{
   if(!pHead)
   {
     pHead = pNode;
     pTail = pNode;
     pNode->pPrevNode = NULL;
     pNode->pNxtNode = NULL;
     return;
   }
   pNode->pPrevNode = NULL;
   pNode ->pNxtNode = pHead;
   pHead = pNode;
}   
/***********************************************************************
* Name 	      : void fillNode(sampNode_t *pNode)
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void fillNode(sampNode_t *pNode)
{
  printf("**Fill Node**\n");
  printf("Enter info(int)\n");
  scanf("%d", &pNode->info);
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void dispNode(sampNode_t *pNode)
{
  printf("info = %d\n", pNode->info);
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void dispNodes(void)
{
  sampNode_t *tmp;
  printf("**Display Nodes**\n");

  tmp = pHead;
  while(tmp)
  {
    dispNode(tmp);
    tmp = tmp->pNxtNode;
  }
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void addNodeToTail(sampNode_t *pNode)
{
  sampNode_t *tmp;

  if(!pHead)
  {
    pHead = pNode;
    pTail = pNode;
    pNode->pPrevNode = NULL;
    pNode->pNxtNode = NULL;
    return;
  }

  tmp = pHead;
  
  while(tmp->pNxtNode)
    tmp = tmp->pNxtNode;
    
   tmp->pNxtNode = pNode;
   pTail = pNode;
   pNode->pPrevNode = tmp; 
   pNode->pNxtNode = NULL;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
int deleteNode(int val)
{
  sampNode_t *tmp;

  if(!pHead)
   return NO_NODES_ERR;

  if(pHead->info == val)
  {
   // free(pHead);
    pHead = pHead->pNxtNode;
    return SUCESS;
  }
  tmp = pHead;
  while(tmp->pNxtNode)
  {
     if(tmp->pNxtNode->info == val)
     { 
     //  free(tmp->pNxtNode);
       tmp->pNxtNode = tmp->pNxtNode->pNxtNode;
       return SUCESS;
     }
     tmp = tmp->pNxtNode;
   }
   return NODE_NOT_FOUND;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void deleteNodeFromDll(sampNode_t *pNode)
{
   if(!pHead)
     return;
   if(!pHead->pNxtNode)
   {
       pHead = NULL;
       pTail = NULL;
       return;
   }
   else if(pNode->pPrevNode == NULL)
   {
     pNode->pNxtNode->pPrevNode = pNode->pPrevNode;
     pHead = pNode->pNxtNode;   
     return;
   }
   if(pNode->pNxtNode == NULL)
   {
     pTail = pNode->pPrevNode;
     pTail->pNxtNode = NULL;
     return;
   }

   pNode->pNxtNode->pPrevNode = pNode->pPrevNode;
   pNode->pPrevNode->pNxtNode = pNode->pNxtNode;
}
  
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
sampNode_t *searchNode(int val)
{
  sampNode_t *tmp;
    
  tmp = pHead;

  while(tmp)
  {
    if(tmp->info == val)
      return tmp;

    tmp = tmp->pNxtNode;
  } 
  return NULL;
}  
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
sampNode_t *allocateMemory4Node(void)
{
  sampNode_t *new;
    
  if((new = (sampNode_t *)malloc(sizeof(sampNode_t))) == NULL)
  {
    printf("Memory not allocated for new Node\n");
    exit(1);
  }
  return new;
} 

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
int getValue(void)
{
  int iTmp;

  scanf("%d", &iTmp);
  return iTmp;
}
  
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
main(void)
{
  int ii, status, choice, noOfNodes; 
  sampNode_t *new;
 /* 
  printf("Enter no of Nodes to be stored\n");
  scanf("%d", &noOfNodes);

  for(ii = 0; ii < noOfNodes; ii++)
  {
    new = allocateMemory4Node();
    fillNode(new);
    addNodeToTail(new);
  }
*/
  while(1)
  {
    printf("\n\n**** Operations On Linked lists ***\n");
    printf("0.Add node to Head\n");
    printf("1.Add node to Tail\n");
    printf("2.Delete node with given value\n");
    printf("3.Search for the given node\n");
    printf("4.Display all the nodes in linked list\n");
    printf("5.Exit\n");
    
    printf("Enter ur Choice\n");
    scanf("%d", &choice);
    printf("\n\n\n");
    
    switch(choice)
    {
    	case 0:
    		new = allocateMemory4Node();
                fillNode(new); 
    		addNodeToHead(new);
                break;
    	case 1:
    		new = allocateMemory4Node();
                fillNode(new); 
    		addNodeToTail(new);
                break;
    	case 2:
 		printf("Eneter val to delete\n");
                ii = getValue(); 
		new = searchNode(ii);
		deleteNodeFromDll(new);
               
                printf("\n$$$$$$$$ Delete Node $$$$$$$$$$\n\n");
    	        printf("Node deleted successfully\n");
    		break;	
    	case 3:
                printf("Eneter val to Search\n");
                ii = getValue();
		new = searchNode(ii);
                printf("\n$$$$$$$$ Search Node $$$$$$$$$$\n");

                if(new)
                {
                  printf("Node found and is\n");
                  dispNode(new);
                }
		else
		   printf("Zero Nodes or Node Not Found\n");
    		break;	
    	case 4:
                dispNodes(); 
                break;
    	case 5:
		exit(1);
                break;
	default:
		printf("Invalid Choice\n");
                break;
     }
  }
}
  
      
    
    
        
  
  
