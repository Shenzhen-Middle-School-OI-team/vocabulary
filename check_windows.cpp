#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <fstream>
#define MAXN 1000005
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
bool isEmpty(string str){
	for (int i=0;i<str.size();++i){
		if (str[i]!='<'&&str[i]!=' '&&str[i]!='\n'&&str[i]!='#') return false;
	}
	return true;
}
int type(string str){
	if (str.size()>=2&&str[0]=='#'&&str[1]=='#') return 0;
	else if (str.size()>=1&&str[0]=='>') return 1;
	else return 2;
}
string explaination[MAXN],query[MAXN],answer[MAXN],full[MAXN];
int order[MAXN];
void Notice(string note){
	cout<<note<<endl;
}
bool isAlphabet(char c){
	return ('a'<=c&&c<='z')||('A'<=c&&c<='Z');
}
void parse(int index,string str){
	bool flag=false,need=false;
	string ans="",ask=str;
	for (int i=0;i<ask.size();++i){
		bool f=isAlphabet(ask[i]);
		if (need&&!f) break;
		if (f){
			need=true;
			ans+=ask[i];
			if (flag) ask[i]='_';
			else flag=true;
		}
	}
	answer[index]=ans;
	query[index]=ask;
	full[index]=str;
}
ifstream words("words.md");
ofstream wrong("wrong2.md");
int main(){
	string nowLine="";
	int last=0,tot=0;
	while (getline(words,nowLine)){
		if (isEmpty(nowLine)) continue;
		int t=type(nowLine);
		if (t==0) continue;
		if (t==1) explaination[last]+=nowLine+"\n";
		if (t==2) last=++tot,parse(tot,nowLine);
	}
	printf("Read %d words\n",tot);
	cerr<<"Read is ok.\nPlease input the full word.\nInput QUIT to quit.\nPress enter to continue."<<endl;
	getchar();
	system("cls");
	srand(time(NULL));
	while (true){
		for (int i=1;i<=tot;++i) order[i]=i;
		random_shuffle(order+1,order+1+tot);
		for (int i=1;i<=tot;++i){
			int index=order[i];
			Notice(query[index]);
			string user_in;
			cin>>user_in;
			if (user_in=="QUIT") break;
			if (user_in==answer[index]) Notice("Correct!\n");
			else Notice("Wrong!\n"),Notice(answer[index]),wrong<<full[index]<<endl,wrong<<explaination[index]<<endl;
			Notice(explaination[index]);
			getchar();
			getchar();
			system("cls");
		}
	}
	return 0;
}
