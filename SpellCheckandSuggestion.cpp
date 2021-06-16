// By : ViditBhardwaj
#include<bits/stdc++.h>
using namespace std;

#define pb       push_back
#define popb     pop_back

vector<string> suggested_str;

class trie{
public:
    trie *child[26];
    bool isterminal;

    trie(){
        for(int i=0;i<=26;i++){
            child[i]=NULL;
        }

        isterminal=false;
    }
};

trie *root=new trie();

void insert(string str){

    trie *temp=root;

    for(int i=0;i<str.length();i++){

        if(temp->child[str[i]-'a']==NULL){

            temp->child[str[i]-'a']=new trie();
        }

        temp=temp->child[str[i]-'a'];
    }

    temp->isterminal=true;
}

bool is_present(string str){

    trie *temp=root;

    for(int i=0;i<str.length();i++){

        if(temp->child[str[i]-'a']==NULL){
            return false;
        }

        temp=temp->child[str[i]-'a'];
    }

    return temp->isterminal;
}

void get_Str(trie *temp,string str){

    if(temp->isterminal){

        suggested_str.pb(str);
    }

    for(int i=0;i<26;i++){
        if(temp->child[i]!=NULL){

            str.pb((char)(i+'a'));

            get_Str(temp->child[i],str);

            str.popb();
        }
    }
}

bool Suggest(string str){

    trie *temp=root;

    for(int i=0;i<str.size();i++){

        if(temp->child[str[i]-'a']==NULL){

            get_Str(temp,str.substr(0,i));
            return false;
        }

        temp=temp->child[str[i]-'a'];
    }

    if(temp->isterminal) return true;

    get_Str(temp,str);

    return false;
}

signed main(){

    int Tc=1;
    cin>>Tc;
    while(Tc--){
        string str; 
        cin>>str;

        insert(str);
    }

    string str;
    cin>>str;

    if(is_present(str)){
        cout<<"String "<<str<<" is present";   
    }else{

        Suggest(str);

        cout<<"Suggested Strings are:"<<endl;
        for(int i=0;i<suggested_str.size();i++){
            cout<<suggested_str[i]<<endl;
        }
    }
    
    return 0;
}

/*

i/p->

8
chile 
china
chinagate
chicken
canada
paris
panda
chi

*/
