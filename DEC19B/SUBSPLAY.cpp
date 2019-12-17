
/*    
 
  December Challenge 2019 Division 2
  problem 3-- Easy Subsequence Selection
  solution by -- RITIK DAGAR
                 SRM IST NCR CAMPUS
                 contact -- 9958152151
        
*/




#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		int m,j;
		cin>>m;
		string s;
		cin>>s;
		vector<int> count(26,-1);
		int minn=m;
		for( j=0;j<m;j++){
			if(count[(s[j]-'a')]!=-1) 
				if(j-count[(s[j]-'a')]<minn) minn=j-count[(s[j]-'a')];
			count[(s[j]-'a')]=j;
		}
		//if(minn==m+1) cout<<0<<"\n";
		cout<<m-(minn)<<"\n";
	}
return 0;
}
