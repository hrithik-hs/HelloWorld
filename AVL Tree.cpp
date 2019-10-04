#include<bits/stdc++.h>
#define ll long long int
#define v vector
using namespace std;
struct AVLNode
{
	ll data;
	AVLNode* lc;
	AVLNode* rc;
	ll height,num;
};
AVLNode* AVLCreate(ll k)
{
	AVLNode* temp = new AVLNode;
	temp->lc = NULL;
	temp->rc = NULL;
	temp->height = 0;
	temp->num = 1;
	temp->data = k;
	return temp;
}
ll AVLNum(AVLNode* node)
{
	if(node==NULL) return 0;
	else return node->num;
}
ll AVLHeight(AVLNode* node)
{
	if(node==NULL) return -1;
	else return node->height;
}
ll AVLBalance(AVLNode* node)
{
	if(node==NULL) return 0;
	else return AVLHeight(node->lc) - AVLHeight(node->rc);
}
AVLNode* AVLRRotate(AVLNode* node)
{
	AVLNode* tnode = node->lc;
	AVLNode* rtnode = tnode->rc;
	tnode->rc = node;
	node-> lc = rtnode;
	node->height = 1 + max(AVLHeight(node->lc),AVLHeight(node->rc));
	tnode->height = 1 + max(AVLHeight(tnode->lc),AVLHeight(tnode->rc));
	node->num = 1 + AVLNum(node->lc)+AVLNum(node->rc);
	tnode->num = 1 + AVLNum(tnode->lc)+AVLNum(tnode->rc);
	return tnode;
}
AVLNode* AVLLRotate(AVLNode* node)
{
	AVLNode* tnode = node->rc;
	AVLNode* ltnode = tnode->lc;
	tnode->lc = node;
	node-> rc = ltnode;
	node->height = 1 + max(AVLHeight(node->lc),AVLHeight(node->rc));
	tnode->height = 1 + max(AVLHeight(tnode->lc),AVLHeight(tnode->rc));
	node->num = 1 + AVLNum(node->lc)+AVLNum(node->rc);
	tnode->num = 1 + AVLNum(tnode->lc)+AVLNum(tnode->rc);
	return tnode;
}
AVLNode* AVLInsert(AVLNode* node,ll k)
{
	if(node==NULL) return AVLCreate(k);
	if(k<=node->data) node->lc = AVLInsert(node->lc,k);
	else if (k>node->data) node->rc = AVLInsert(node->rc,k);
	else return node;
	
	node->height = 1 + max(AVLHeight(node->lc),AVLHeight(node->rc));
	ll balance = AVLBalance(node);
	node->num = 1 + AVLNum(node->lc)+AVLNum(node->rc);
	if(balance > 1)
	{
		if(k <= (node->lc)->data) return AVLRRotate(node);
		if(k > (node->lc)->data)
		{
			node->lc = AVLLRotate(node->lc);
			return AVLRRotate(node);
		}	
	}

	if(balance < -1)
	{
		if(k > (node->rc)->data) return AVLLRotate(node);
		if(k <= (node->rc)->data)
		{
			node->rc = AVLRRotate(node->rc);
			return AVLLRotate(node);
		}
	}
	return node;
}
AVLNode* AVLMinValueNode(AVLNode* node)
{
	AVLNode* cur = node;
	while(cur->lc!=NULL)
		cur = cur->lc;
	return cur;
} 
AVLNode* AVLDelete(AVLNode* root,ll k)
{
	if(root == NULL) return root;
	if(k < root->data) root->lc = AVLDelete(root->lc,k);
	else if (k > root->data) root->rc = AVLDelete(root->rc,k);
	else
	{
		if(root->lc==NULL || root->rc==NULL)
		{
			if(root->lc==NULL && root->rc==NULL)
			{
				AVLNode* temp = root;
				root = NULL;
				free(temp);
			}
			else
			{
				AVLNode* temp = root->lc ? root->lc : root->rc; 
				*root = *temp;
				free(temp);
			}
		}
		else
		{
			AVLNode* temp = AVLMinValueNode(root);
			root->data = temp->data;
			root->rc = AVLDelete(root->rc,temp->data);
		}
	}
	if(root==NULL) return root;
	root->num = 1 + AVLNum(root->lc)+AVLNum(root->rc);
	root->height = 1 + max(AVLHeight(root->lc),AVLHeight(root->rc));
	ll balance = AVLBalance(root);

	if(balance > 1)
	{
		if(AVLBalance(root->lc)>=0) return AVLRRotate(root);
		if(AVLBalance(root->lc)<0)
		{
			root->lc = AVLLRotate(root->lc);
			return AVLRRotate(root);
		}	
	}

	if(balance < -1)
	{
		if(AVLBalance(root->rc)<=0) return AVLLRotate(root);
		if(AVLBalance(root->rc)>0)
		{
			root->rc = AVLRRotate(root->rc);
			return AVLLRotate(root);
		}
	}
	return root;
}
void Preorder(AVLNode* root)
{
	if(root!=NULL)
	{
		cout<<root->data<<" "<<root->num<<"\n";
		Preorder(root->lc);
		Preorder(root->rc);
	}
}
int main()
{

	AVLNode *root = NULL;  
    root = AVLInsert(root, 9); 
    root = AVLInsert(root, 5); 
    root = AVLInsert(root, 10); 
    root = AVLInsert(root, 0); 
    root = AVLInsert(root, 6); 
    root = AVLInsert(root, 11); 
    root = AVLInsert(root, -1); 
    root = AVLInsert(root, 1); 
    root = AVLInsert(root, 2);   
    cout << "Preorder traversal of the constructed AVL tree is \n";  
    Preorder(root); 
    root = AVLDelete(root, 10);
    cout<<"\nPreorder traversal after deletion of 10 \n";
    Preorder(root);
    return 0;
}