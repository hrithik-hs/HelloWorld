#include<bits/stdc++.h>
#define ll long long int
using namespace std;

struct tree{
	int data;
	struct tree *lc;
	struct tree *rc;
	int flag = 0;
	//struct tree *p;
};

void visit(struct tree *node){
	cout<<node->data<<"  ";
};



//recursive
void r_inorder(struct tree *node){
	if(node!=NULL){
		r_inorder(node->lc);
		visit(node);
		r_inorder(node->rc);
	}
	return;
}
void r_preorder(struct tree *node){
	if(node!=NULL){
		visit(node);
		r_preorder(node->lc);
		r_preorder(node->rc);
	}
	return;
}
void r_postorder(struct tree *node){
	if(node!=NULL){
		r_postorder(node->lc);
		r_postorder(node->rc);
		visit(node);
	}
	return;
}
// inorder---lc,node,rc    preorder---node,lc,rc   postorder---lc,rc,node;
//to find level---preorder    height---postorder

//irerative
//pre,post,in order stack  levelorder queue

void preorder(struct tree *node){
	stack <struct tree*>s;
	s.push(node);
	while(!s.empty()){
		struct tree *x=(struct tree*)malloc(sizeof(struct tree));
		x=s.top();
		s.pop();
		visit(x);
		if(x->rc!=NULL) s.push(x->rc);
		if(x->lc!=NULL) s.push(x->lc);
	}
}

void postorder(struct tree *node){
	stack <struct tree*>s;
	s.push(node);
	while(!s.empty())
	{
		struct tree *x=(struct tree*)malloc(sizeof(struct tree));
		x=s.top();
		if(x->flag==0)
		{
			if(x->rc!=NULL) s.push(x->rc);
			if(x->lc!=NULL) s.push(x->lc);
			x->flag = 1;
		}
		else
		{
			visit(x);
			x->flag=0;
			s.pop();
		}
	}
}
void inorder(struct tree *node)
{
	stack <struct tree*> s;
	s.push(node);
	while(!s.empty())
	{
		struct tree *x=(struct tree*)malloc(sizeof(struct tree));
		x=s.top();
		if(x->flag==0)
		{
			s.pop();
			x->flag=1;
			if(x->rc!=NULL) s.push(x->rc);
			s.push(x);
			if(x->lc!=NULL) s.push(x->lc);
		}
		else
		{
			visit(x);
			x->flag=0;
			s.pop();
		}
	}
}
void levelorder(struct tree *node){
	queue <struct tree*> q;
	q.push(node);
	struct tree *x=(struct tree*)malloc(sizeof(struct tree));
	while(!q.empty()){
		x=q.front();
		q.pop();
		visit(x);
		if(x->lc!=NULL) q.push(x->lc);
		if(x->rc!=NULL) q.push(x->rc);
	}
}


struct tree* build_bst(vector <int>&a,int i,int j){
	struct tree *x=(struct tree*)malloc(sizeof(struct tree));
	if(i<j){
		int k=(i+j)/2;
		x->data=a[k];
		if(i<=k-1){
			x->lc=build_bst(a,i,k-1);
		}
		else x->lc=NULL;
		if (k+1<=j){
			x->rc=build_bst(a,k+1,j);
		}
		else x->rc=NULL;
	}
	else{
		i=j;
		x->data=a[i];
		x->lc=NULL;
		x->rc=NULL;
	}
	return x;
}



int main(){
	vector<int>a{3,5,9,20,6,8,10,18,12};
	sort(a.begin(),a.end());
	struct tree *root=(struct tree*)malloc(sizeof(struct tree));
	root=build_bst(a,0,a.size()-1);
	// cout<<(root->data)<<endl;
	//  levelorder(root);
	//  cout<<endl;
	//  r_preorder(root);
	//  cout<<endl;
	// preorder(root);
	//  cout<<endl;
	r_postorder(root);
	cout<<endl;
	postorder(root);
	cout<<endl;
	inorder(root);
	cout<<endl;
	return 0;
}