#include <iostream>
#include <malloc.h>
#include <cstring>
using namespace std;
typedef int KeyType;

typedef struct node {
    KeyType key;
    char data[10];
    struct node *lchild, *rchild;
} BSTNode;

BSTNode * InsertBST(BSTNode *&bt, KeyType k,char s[]) {
    if (bt == NULL) {
        bt = (BSTNode *)malloc(sizeof(BSTNode));
        bt->key = k;
		strcpy(bt->data,s);
        bt->lchild = bt->rchild = NULL;
    } else if (k<bt->key) 
        bt->lchild=InsertBST(bt->lchild, k,s);
     else if(k>bt->key)
        bt->rchild= InsertBST(bt->rchild, k,s);
	return bt;
}
BSTNode * InsertBST(BSTNode *&bt, KeyType k) {
    if (bt == NULL) {
        bt = (BSTNode *)malloc(sizeof(BSTNode));
        bt->key = k;
        bt->lchild = bt->rchild = NULL;
    } else if (k<bt->key) 
        bt->lchild=InsertBST(bt->lchild, k);
     else if(k>bt->key)
        bt->rchild= InsertBST(bt->rchild, k);
	return bt;
}

BSTNode *CreateBST(KeyType A[], int n) {
    BSTNode *bt = NULL;
    int i = 0;
    while (i < n) {
        InsertBST(bt, A[i]);
        i++;
    }
    return bt;
}

void showBST(BSTNode *bt) {
	printf("your bst:");
    if (bt != NULL) {
        if(bt->lchild) showBST(bt->lchild);
		printf("%d ",bt->key);
		if(bt->rchild) showBST(bt->rchild);
    }
}

BSTNode * DeleteBST(BSTNode * bt,KeyType k){
	if(bt==NULL) return bt;
	BSTNode * p=bt,*f=NULL;
	while(p!=NULL){
		if(p->key==k) break;
		f=p;
		if(k<p->key) p=p->lchild;
		else p=p->rchild;
	}
	if(p==NULL) return bt;
	if(p->lchild==NULL&&p->rchild==NULL){
		if(p==bt) bt=NULL;
		else{
			if(f->lchild==p) f->lchild=NULL;
			else f->rchild=NULL;
		}
		free(p);
	}
	else if(p->rchild==NULL){
		if(f==NULL) bt=bt->lchild;
		else{
			if(f->lchild==p) f->lchild=p->lchild;
			else f->rchild=p->lchild;
		}
		free(p);
	}
	else if(p->lchild==NULL){
		if(f==NULL) bt=bt->rchild;
		else{
			if(f->lchild==p) f->lchild=p->rchild;
			else f->rchild=p->rchild;
		}
		free(p);
	}
	else{
		BSTNode *q=p->lchild;
		f=p;
		while(q->rchild!=NULL){
			f=q;
			q=q->rchild;
		}
		p->key=q->key;
		if(q==f->lchild) f->lchild=q->lchild;
		else f->rchild=q->lchild;
		free(q);
	}
	return bt;
}
BSTNode *SearchBST(BSTNode *bt,KeyType k)
{ 
    if (bt==NULL || bt->key==k)      	
		return bt;
	if (k<bt->key)
       	return SearchBST(bt->lchild,k);  
    else
     	return SearchBST(bt->rchild,k);  
}

void DestroyBST(BSTNode *&bt) {
    if (bt != NULL) {
        DestroyBST(bt->lchild);
        DestroyBST(bt->rchild);
        free(bt);
    }
}
int main(){
	int a[]={10,39,20,45,35,40};
	BSTNode *head=CreateBST(a,6);
	showBST(head);
	InsertBST(head,38);
	InsertBST(head,37,"text");
	InsertBST(head,36,"text");
	InsertBST(head,36);
	
	char s[10];
	cin>>s;

	cout<<SearchBST(head,10)->data<<endl;
}