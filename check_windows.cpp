#include <bits/stdc++.h>
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

const string attribute[]={"n","v","vt","vi","prep","adj","adv","abbr","pron"};
const int attributeSize=9;
const string space="___";

bool isEmpty(string str){
	for (int i=0;i<str.size();++i){
		if (str[i]!='<'&&str[i]!=' '&&str[i]!='\n'&&str[i]!='#') return false;
	}
	return true;
}
int type(string str){
	if (str.size()>=3&&str[0]=='#'&&str[1]=='#'&&str[2]!='#') return 0;
	else if (str.size()>=4&&str[0]=='#'&&str[1]=='#'&&str[2]=='#'&&str[3]!='#') return 1;
	else if (str.size()>=1&&str[0]=='>') return 2;
	else return 3;
}
bool isAlphabet(char c){
	if (c=='\'') return true;
	if (c=='(') return true;
	if (c==')') return true;
	return ('a'<=c&&c<='z')||('A'<=c&&c<='Z');
}

string _explaination[MAXN],_query[MAXN],_answer[MAXN],_full[MAXN];
string explaination[MAXN],query[MAXN],answer[MAXN],full[MAXN];
int order[MAXN],belong[MAXN],choosed[MAXN];

void parse(int index,string str){
	string ask="",words="",word="";
	bool head=true,use=true;
	for (int i=0;i<str.size();++i){
		if (!use){
			ask+=str[i];
			continue;
		}
		if (isAlphabet(str[i])){
			word+=str[i];
		}
		else if (str[i]==' '||str[i]=='.'&&word.size()!=0){
			for (int j=0;j<attributeSize;++j){
				if (word==attribute[j]){
					use=false;
					break;
				}
			}
			if (!use){
				ask+=word;
				ask+=str[i];
				continue;
			}

			if (head) head=false;
			else words+=" ";
			words+=word;

			ask+=word[0];
			if (word.size()!=1) ask+=space;
			ask+=" ";

			word="";
		}
		else {
			ask+=str[i];
		}
	}
	_answer[index]=words;
	_query[index]=ask;
	_full[index]=str;
}
ifstream words("英语必修一到必修十一_gb.md");
ofstream wrong("wrong.md");
string title[MAXN];
int totTitle;
int main(){
	string nowLine="";
	int last=0,tot=0;
	totTitle=0;
	while (getline(words,nowLine)){
		if (isEmpty(nowLine)) continue;
		int t=type(nowLine);
		if (t==0){
			totTitle++;
			title[totTitle]=nowLine.substr(2);
			continue;
		}
		if (t==1) continue;
		if (t==2) _explaination[last]+=nowLine+"\n";
		if (t==3) last=++tot,belong[last]=totTitle,parse(tot,nowLine);
	}

	printf("Read %d words\n",tot);
	printf("Read is ok.\nPlease input the full word.\nInput QUIT to quit.\nPress enter to continue.\n");
	getchar();
	system("cls");

	printf("Choose lists:\n");
	for (int i=1;i<=totTitle;++i){
		cout<<i<<":"<<title[i]<<endl;
	}
	printf("Enter tot choose:");
	int totChoose;
	scanf("%d",&totChoose);
	for (int i=1;i<=totChoose;++i){
		int choose;
		scanf("%d",&choose);
		choosed[choose]=true;
	}
	int all=0;
	for (int i=1;i<=tot;++i){
		if (choosed[belong[i]]){
			++all;
			explaination[all]=_explaination[all];
			answer[all]=_answer[all];
			full[all]=_full[all];
			query[all]=_query[all];
			cout<<full[all]<<endl;
		}
	}
	getchar();
	system("cls");

	srand(time(NULL));
	while (true){
		for (int i=1;i<=all;++i) order[i]=i;
		random_shuffle(order+1,order+1+all);
		for (int i=1;i<=all;++i){
			int index=order[i];
			cout<<query[index]<<endl;

			string user_in;
			getline(cin,user_in);
			if (user_in=="QUIT") return 0;

			if (user_in==answer[index]) printf("Correct!\n");
			else printf("Wrong!\n"),cout<<answer[index]<<endl,wrong<<full[index]<<endl,wrong<<explaination[index]<<endl;
			cout<<explaination[index]<<endl;

			getchar();
			system("cls");
		}
	}
	return 0;
}
