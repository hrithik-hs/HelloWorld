#include<bits/stdc++.h>
using namespace std;

void merge(long long int a[],long long int i,long long int mid,long long int j){//j exclusive indexing 
	//cout<<i<<" "<<mid<<" "<<j<<endl;
	long long int l=i,r=mid,p=0;
	long long int b[j-i];
	while(l<mid && r<j){
		if(a[l]<=a[r]){
			b[p++]=a[l++];
		}
		else
			b[p++]=a[r++];
	}
	while(l<mid) b[p++]=a[l++];
	while(r<j) b[p++]=a[r++];
	p=0;l=i;
	while(l<j){
		a[l++]=b[p++];
	}
	// for(int ii=i;ii<j;ii++){
	// 	cout<<a[ii]<<" ";
	// }
	// cout<<endl;
}

void merge_sort(long long int a[],long long int i,long long int j){//j exclusive indexing 
	//cout<<i<<" "<<j<<endl;
	if(i<j-1){
		long long int mid=(i+j)/2;
		merge_sort(a,i,mid);
		merge_sort(a,mid,j);
		merge(a,i,mid,j);

	}
	return;
}

long long int partition(long long int a[],long long int i,long long int j){//j exclusive indexing 
	long long int p=a[i];
	long long int l=i+1,r=j-1;
	while(l<=r){
		while(l<=r && a[l]<=p)l++;
		while(l<=r && a[r]>p)r--;
		if(l<=r){
			long long int temp=a[l];
			a[l]=a[r];
			a[r]=temp;
			l++;r--;
		}
	}
	long long int temp=a[r];
	a[r]=a[i];
	a[i]=temp;
	return r;

}

void r_quick_sort(long long int a[],long long int i,long long int j){//j exclusive indexing 
	if(i<j-1){
		long long int p=i+rand()%(j-i);
		long long int temp=a[i];
		a[i]=a[p];
		a[p]=temp;
		long long int k=partition(a,i,j);
		r_quick_sort(a,i,k);
		r_quick_sort(a,k,j);
	}
	return;
}


int main(){
	srand(time(NULL));
	long long int a[]={5,4,38,2,1,9880,87,22,22};
	//merge_sort(a,0,7);
	r_quick_sort(a,0,9);
	for(int i=0;i<9;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
	return 0;
}