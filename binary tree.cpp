#include<iostream>
#include<process.h>

using namespace std;

class Stack;              //forward declaration for linked stack
class Tree;               //forward declaration of tree

//tree node representation
class TNode{
    TNode *left;
    TNode *right;
    int data;
    friend class Tree;
    public:
       TNode()
         {
             left=NULL;
             right=NULL;
         }
       TNode(int d, TNode *l=NULL, TNode *r=NULL)
         {
             data=d;
             left=l;
             right=r;
         }
};

//Node representation for stack
class SNode
{
   TNode *data;    //holds address of tree node
   SNode *link;    //self reference
   public:
     SNode()
       {
           data=NULL;
           link=NULL;
       }
     SNode(TNode *d, SNode* l=NULL)
       {
           data=d;
           link=l;
       } 
     friend class Stack;
};


//linked stack instead of static stack
class Stack
{
    SNode *top;   
    public:
      Stack()
        {
            top=NULL;
        }
      bool isEmpty();
      void push(TNode*);
      TNode* pop();
      void display();
};

class Tree{
    TNode* root;
    public:
       Tree()
         {
             root=NULL;
         }
        
        void create();
        TNode* getRoot()
         {
           return root;
         }

         void preorderRecursive(TNode*);
         void inorderRecursive(TNode*);
         void postorderRecursive(TNode*);
         void inorderNonRecursive(TNode*);
         void postorderNonRecursive(TNode*);
         void preorderNonRecursive(TNode*);
};

bool Stack::isEmpty()    //returns true if stack is empty
{
    return top==NULL;
}

TNode* Stack::pop()
{
    if(isEmpty())
      {
          cout<<"\nStack Underflow!";
          exit(-1);
      }
    SNode *temp=top;
    TNode *d=temp->data;    //address of Tree node at top of stack
    top=top->link;   //move top one node ahead
    delete temp;
    return d;
}

//each new node is added before the current node, and top points to the new node
void Stack::push(TNode* data)    
{
   SNode *newSNode=new SNode(data,top); 
   top=newSNode;
}

void Tree::preorderRecursive(TNode* temp)   //DLR
{
  if(root==NULL)
    {
      cout<<"\nTree is empty!";
      return;
    }
  if(temp!=NULL)
   {
     cout<<"\t"<<temp->data;           //data
     preorderRecursive(temp->left);         //left
     preorderRecursive(temp->right);        //right
   }
}

void Tree::inorderRecursive(TNode* temp)   //LDR
{
  if(root==NULL)
    {
      cout<<"\nTree is empty!";
      return;
    }
  if(temp!=NULL)
    {
      inorderRecursive(temp->left);          //left
      cout<<"\t"<<temp->data;          //data
      inorderRecursive(temp->right);         //right
    }
}

void Tree::postorderRecursive(TNode *temp)    //LRD
{
  if(root==NULL)
    {
      cout<<"\nTree is empty!";
      return;
    }
  if(temp!=NULL)                      
   {
     postorderRecursive(temp->left);          //left
     postorderRecursive(temp->right);         //right
     cout<<"\t"<<temp->data;            //data
   }
}

void Tree::create()
{
   char ans,choice;
   int d;
   do{
    cout<<"\nEnter data to be inserted: ";
    cin>>d;
    TNode *newTNode=new TNode(d);
    if(root==NULL)
      {
          root=newTNode;
      }
    else
      {
         TNode* temp=root;
         while(true)
          {
              cout<<"\nLeft or right(l/r) of "<<temp->data<<" : ";
              cin>>ans;
              if(ans=='l')
                if(temp->left==NULL)
                  {
                      temp->left=newTNode;
                      break;
                  }
                else
                    temp=temp->left;
              else
                if(temp->right==NULL)
                  {
                      temp->right=newTNode;
                      break;
                  }
                else 
                  temp=temp->right;       
          }
      }
    cout<<"\nAny more TNodes?(y or n)";  
    cin>>choice;
   }while(choice=='y' || choice == 'Y');
}

void Tree::preorderNonRecursive(TNode *temp) 
{
  //display data of TNode in first visit of Tnode
    if(temp==NULL)
      {
        cout<<"\nTree is empty";
        return;
      }

    Stack S;
    cout<<"\nThe non-recursive preorder traversal is: ";
    while(true)
     {
       while(temp!=NULL)
         {
           cout<<temp->data<<"\t";  //first visit
           S.push(temp);
           temp=temp->left;
         }
         if(S.isEmpty())
           break;
          temp = S.pop();
          temp=temp->right;
     }
}


//display data of TNode in second visit of TNode
void Tree::inorderNonRecursive(TNode *temp)
{
    if(temp==NULL)
      {
        cout<<"\nTree is empty";
        return;
      }

    Stack S;
    cout<<"\nThe non-recursive inorder traversal is: ";
    while(true)
     {
       while(temp!=NULL)
         {
           S.push(temp);
           temp=temp->left;
         }
         if(S.isEmpty())
           break;
          temp = S.pop();
          cout<<temp->data<<"\t";   //second visit
          temp=temp->right;
     }
}

void Tree::postorderNonRecursive(TNode *temp)  
{
  //two stack implementation
    if(temp==NULL)
      {
        cout<<"\nTree is empty";
        return;
      }
      
    Stack S1,S2;
    cout<<"\nThe non-recursive postorder traversal is: ";
    S1.push(temp);
    while(!S1.isEmpty())
      {
        temp=S1.pop();
        S2.push(temp);
        if(temp->left != NULL)
          {
             S1.push(temp->left);
          }
        if(temp->right != NULL)
          {
           S1.push(temp->right);
          }
      }
    
    //Stack S2 contains the address of nodes in reverse order for postorder traversal
    while(!S2.isEmpty())
      {
        cout<<(S2.pop())->data<<"\t";
      }
}

int main()
{
    Tree T;
    int ch;
    while(true)
     {
       cout<<"\n\n\t\tBinary Tree traversal menu";
       cout<<"\n1.Create Binary Tree";
       cout<<"\n2.Recursive preorder";
       cout<<"\n3.Recursive inorder";
       cout<<"\n4.Recursive postorder";
       cout<<"\n5.Non-Recursive preorder";
       cout<<"\n6.Non-Recursive inorder";
       cout<<"\n7.Non-Recursive postorder";
       cout<<"\n8.Exit";
       cout<<"\n\nEnter your choice: ";
       cin>>ch;
       switch(ch)
        {
           case 1:
               T.create();
               break;

           case 2:
              cout<<"\nRecursive Preorder: ";
              T.preorderRecursive(T.getRoot());
              break;

           case 3:
              cout<<"\nRecursive Inorder: ";
              T.inorderRecursive(T.getRoot());
              break;

           case 4:
               cout<<"\nRecursive Postorder: ";
               T.postorderRecursive(T.getRoot());
               break;

           case 5:
              T.preorderNonRecursive(T.getRoot());
              break;

           case 6:
              T.inorderNonRecursive(T.getRoot());
              break;

           case 7:
              T.postorderNonRecursive(T.getRoot());
              break;
            
           case 8:
              exit(0);

           default:
              cout<<"\nInvalid value";          
        }
    }   
}