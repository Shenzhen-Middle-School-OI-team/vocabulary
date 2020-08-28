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
	for (int i=0;i<(int)str.size();++i){
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
	return ('a'<=c&&c<='z')||('A'<=c&&c<='Z');
}

string _explaination[MAXN],_query[MAXN],_answer[MAXN],_full[MAXN];
string explaination[MAXN],query[MAXN],answer[MAXN],full[MAXN];
int order[MAXN],belong[MAXN],choosed[MAXN];
vector<pair<int,string> >divided;//分成英语,空格/括号,英语 
void divide(string str){
	divided.clear();
	string now="";
	for (int i=0;i<(int)str.size()-1;++i){
		now+=str[i];
		if (isAlphabet(str[i])&&!isAlphabet(str[i+1])) divided.push_back(make_pair(1,now)),now="";
		if (!isAlphabet(str[i])&&isAlphabet(str[i+1])) divided.push_back(make_pair(0,now)),now="";
	}
	now+=str[(int)(str.size())-1];
	if (isAlphabet(str[(int)(str.size())-1])) divided.push_back(make_pair(1,now));
	else divided.push_back(make_pair(0,now));
}
string hollow(string str){
	return str[0]+space;
}
bool isAttribute(string str){
	for (int i=0;i<attributeSize;++i){
		if (str==attribute[i]) return true;
	}
	return false;
}
string delSpace(string str){
	int p=str.size()-1;
	while (str[p]==' ') p--;
	return str.substr(0,p+1);
}
void parse(int index,string str){
	string ask="",ans="";
	divide(str);
	bool flag=false;
	for (int i=0;i<(int)divided.size();++i){
		if (i==0&&divided[i].first==0) continue;//去除前导空格
		if (divided[i].first==1&&!flag){
			if (isAttribute(divided[i].second)){
				ask+=divided[i].second;
				flag=true;
			}
			else if (i+1==(int)divided.size()-1&&divided[i+1].first==0){
				ans+=divided[i].second;
				ask+=hollow(divided[i].second);
				flag=true;
			}
			else {
				ans+=divided[i].second;
				ask+=hollow(divided[i].second);
			}
		}
		else {
			ask+=divided[i].second;
			if (!flag) ans+=divided[i].second;
		} 
	}
	_answer[index]=delSpace(ans);
	_query[index]=ask;
	_full[index]=str;
}
ifstream words("英语必修一到必修十一_gb.md");
ofstream wrong("test_wrong.md");
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
	printf("Enter choose:");
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
		}
	}
//	getchar();
	getchar();
	system("cls");

	srand(time(NULL));
	while (true){
		for (int i=1;i<=all;++i) order[i]=i;
		random_shuffle(order+1,order+1+all);
		for (int i=1;i<=all;++i){
			int index=order[i];
			
			cout<<i<<"/"<<all<<endl;
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
