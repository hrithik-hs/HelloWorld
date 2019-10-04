#include<bits/stdc++.h>
#define ll long long int
#define F first
#define S second
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);
using namespace std;

template <class T>
class bit{
	public:
		int size;
		vector <T> v;
		bit(int n){
			size=n;
			v.resize(n+1,0);
		}
		int parent(int i){
			return i+(i & (-1*i));
		}
		int child(int i){
			return i-(i & (-1*i));	
		}

		void build(vector<T> a,int n){
			for(int i=0;i<n;i++){
				int j=i+1;
				//cout<<1<<" ";
				while(j<=n){
					//cout<<j<<" ";
					v[j]+=a[i];
					j=parent(j);
				}
			}
		}
		
		void update(vector<T> &a,int i,T x,int n){
			T diff=x-a[i];
			a[i]=x;
			i++;
			while(i<=n){
				v[i]+=diff;
				i=parent(i);
			}			
		}

		T query(int i){
			T sum=0;
			i++;
			//cout<<i<<" ";
			while(i>0){
				//cout<<i<<" ";
				sum+=v[i];
				i=child(i);
			}
			return sum;
		}
};
/*
	build(vector a,size n);
	update(vector a,index ,value,size n);
	query(index);

*/

int main(){
	//vector<int> a{0,0,0,0,0};
	vector<int> a{1,2,3,4,5};
	bit<int> t(5);
	t.build(a,5);
	// t.update(a,0,1,5);
	 t.update(a,1,6,5);
	// t.update(a,2,3,5);
	// t.update(a,3,4,5);
	// t.update(a,4,5,5);
	for(int i=0;i<5;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
	for(int i=1;i<=5;i++){
		cout<<t.v[i]<<" ";
	}
	cout<<endl;
	cout<<t.query(4)<<endl;

		
	return 0;
}