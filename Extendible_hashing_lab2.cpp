#include <bits/stdc++.h>
using namespace std;
#define srt(a) sort(a.begin(),a.end())
#define rsrt(a) sort(a.begin(),a.end(),greater<int>())
#define f(i,n) for(int i=0;i<n;i++)
#define vint vector<int>
#define pb push_back
#define mnv(v) *min_element(v.begin(),v.end())
#define mxv(v) *max_element(v.begin(),v.end())
#define P cout<<
#define C cin>>

    vector<int> local_depth;
	int global_depth;
	int size_bucket;
    vector<vector<int>> hashing;

	void split_table(){
		int k= hashing.size();
		for(int i=0;i<k;i++){
			vector<int> v;
			hashing.pb(v);
			local_depth.pb(global_depth);
		}
	}
    
	void insert_key(int k){

		int m = (int)(k & ((1<< global_depth) - 1));

		if(hashing[m].size() < size_bucket){
	    	hashing[m].pb(k);
		}else if( local_depth[m]<global_depth){
            local_depth[m]++;

			vector<int> vg;

			for(int i=0;i<hashing[m].size();i++){
				vg.pb(hashing[m][i]);
			}


			int hj=hashing[m].size();

			for(int i=0;i<hj;i++){
				hashing[m].pop_back();
			}

			for(int i=0;i<hashing[m].size();i++){
				insert_key(vg[i]);
			}
			insert_key(k);
		}else if(global_depth==local_depth[m]){
		   global_depth++;
		   local_depth[m]++;
           split_table();
		   
		    vector<int> vg;
			for(int i=0;i<size_bucket;i++){
				vg.pb(hashing[m][i]);
			}

			hashing[m].clear();

			for(int i=0;i<size_bucket;i++){
				insert_key(vg[i]);
			}

			insert_key(k);
		}
	}


    int search_key(int k){
      int m = (k & ((1 << global_depth)-1));
	  for(int i=0;i<hashing[m].size();i++){
		  if(hashing[m][i]==k){
			  return 1;
		  }
	  }
       return 0;
	}

    void delete_key(int k){
		int m = (k & ((1<< global_depth) - 1));
		int n=hashing[m].size();
        for(int i=0;i<n;i++){
			if(hashing[m][i]==k){
				int j=hashing[m][n-1];
				hashing[m][i]=j;
				hashing[m][n-1]=k;
                break;
			}
		}
		hashing[m].pop_back();
	}
   
    void print_tablee(){
      P global_depth<<"\n";
	  int m=0;
	  vector<pair<int,int>> vp;
	  for(int i=0;i<(1 << global_depth);i++){
		  if(hashing[i].size()>0){ 
			  m++;
		  vp.pb({local_depth[i],hashing[i].size()});
		  }
	  }
	  P m<<"\n";
      for(int i=0;i<vp.size();i++){
		  P vp[i].second<<" "<<vp[i].first<<"\n";
	  }
	}


int main(){

	C global_depth>>size_bucket;
    
	for(int i=0;i< (1 << global_depth); i++){
        vector<int> v;
		hashing.pb(v);
		local_depth.pb(global_depth);
	}

    
	while(1){
		int k=0;
		C k;
		int n=0;
		if(k==2){
			 C n;
			 insert_key(n);
		}else if(k==4){
            C n;
			if(search_key(n)==1){
				delete_key(n);
			}

	
		}else if(k==5){
			print_tablee();
		}else if(k==6){
			break;
		}
	}
    
	
	return 0;
}