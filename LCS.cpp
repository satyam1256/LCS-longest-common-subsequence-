#include<bits/stdc++.h>
using namespace std;
// BRUTE FORCE METHOD
int lcs(string S , string T){
    // base case
    if(S.size()==0 || T.size()==0){
        return 0;
    }
    // small check
    if(S[0]==T[0]){
        return 1+ lcs(S.substr(1) , T.substr(1));
    }
    else{
        // recurssive calls
        int a = lcs(S.substr(1) ,T);
        int b = lcs(S ,T.substr(1));
        int c = lcs(S.substr(1) , T.substr(1));

        return max(a , max(b,c));

    }
    
    
}

// MEMOIZATION APPROACH TOP TO BOTTOM
int LCS_mem_helper(string s, string t , int**output){
    // base case
    if(s.size()==0 || t.size()==0){
        return 0;
    }
    int m = s.size();
    int n = t.size();
    // check if already exists
    if(output[m][n]!= -1){
        return output[m][n];
    }
    int ans;
    // recurssive calls
    if(s[0]==t[0]){
        ans = 1+ LCS_mem_helper(s.substr(1) , t.substr(1) , output);
    }
    else{
        int a = LCS_mem_helper(s.substr(1) , t , output);
        int b = LCS_mem_helper(s , t.substr(1) , output);
        int c = LCS_mem_helper(s.substr(1) , t.substr(1) , output);

        ans = max( a , max(b,c));
    }
    // save for future use
    output[m][n] = ans;
    
    // returning output
    return output[m][n];
}
int LCS_mem(string s , string t){
    int m = s.size();
    int n = t.size();
    int **output = new int*[m+1];
    for(int i=0;i<=m;i++){
        output[i] = new int[n+1];
        for(int j=0;j<=n;j++){
            output[i][j] = -1;
        }
    }
    return LCS_mem_helper(s , t , output);

}
// USING DYNAMIC PROGRAMMING

int lcs_DP_helper(string s  ,string t , int**output){
    int m = s.size();
    int n = t.size();
    if(s.size()==0 || t.size()==0){
        return 0;
    }
    // filling 1st row leeft to right
    int row1=0;
    for(int j=0;j<=n;j++){
        output[row1][j]=0;
    }
    // filling 1st column top to bottom
    int col1 =0;
    for(int i=0;i<=m;i++){
        output[i][col1] = 0;
    }
    // filling rest places left to right
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            // here i , j represents the length of the strings ..so while comparing the first character we should think of the current s and current t.
            // s eqauls here s.substr(m-1)...this is the s at current psition when i and j is their length.
            if(s.substr(m-i)[0]==t.substr(n-j)[0]){
                output[i][j] = output[i-1][j-1] + 1;
            }
            else{
                output[i][j] = max(output[i-1][j] , max(output[i][j-1] , output[i-1][j-1]));
            }
        }
    }
    return output[m][n];


}

int lcs_DP(string s , string t){
    int m =s.size();
    int n =t.size();
    int **output = new int*[m+1];
    for(int i=0;i<=m;i++){
        output[i] = new int[n+1];
    }
    return lcs_DP_helper(s ,t ,output);
}
int main(){
    string s , t;
    cin>>s>>t;
    cout<<"Brute force-------"<<endl<<lcs(s,t)<<endl;
    cout<<"Memoization method"<<endl<<LCS_mem(s,t)<<endl;
    cout<<"DP method"<<endl<<lcs_DP(s,t);
}