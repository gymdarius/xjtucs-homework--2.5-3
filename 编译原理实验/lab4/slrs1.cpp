#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;
/*
//第一种文法:
string action[12][6] = {"S5", "0", "0", "S4", "0", "0",
                        "0", "S6", "0", "0", "0", "acc",
                        "0", "r2", "S7", "0", "r2", "r2",
                        "0", "r4", "r4", "0", "r4", "r4",
                        "S5", "0", "0", "S4", "0", "0",
                        "0", "r6", "r6", "0", "r6", "r6",
                        "S5", "0", "0", "S4", "0", "0",
                        "S5", "0", "0", "S4", "0", "0",
                        "0", "S6", "0", "0", "S11", "0",
                        "0", "r1", "S7", "0", "r1", "r1",
                        "0", "r3", "r3", "0", "r3", "r3",
                        "0", "r5", "r5", "0", "r5", "r5"};
int gotoarr[12][3] = {1, 2, 3, //GOTO 表
                      0, 0, 0,
                      0, 0, 0,
                      0, 0, 0,
                      8, 2, 3,
                      0, 0, 0,
                      0, 9, 3,
                      0, 0, 10,
                      0, 0, 0,
                      0, 0, 0,
                      0, 0, 0,
                      0, 0, 0};
char vt[6] = {'i', '+', '*', '(', ')', '#'}; //存放终结符
char vn[3] = {'E', 'T', 'F'}; //存放非终结符
string Production[6] = {"E->E+T", "E->T", "T->T*F", "T->F", "F->(E)", "F->i"};//产生式集合
*/

//第二种文法:
string action[18][9] = {"0", "0", "0", "0", "0", "0","0","S1","0",
						"0", "0", "0", "0", "0", "0","S2","0","0",
						"S3", "0", "0", "0", "0", "0","0","S7","0",
						"S3", "0", "0", "0", "0", "0","0","S7","0",
						"0", "0", "0", "S9", "S10", "0","0","0","acc",
						"0", "r7", "r7", "r7", "r7", "r7","0","0","r7",
						"0", "r4", "S11", "r4", "r4", "S12","0","0","r4",
						"0", "r9", "r9", "r9", "r9", "r9","0","0","r9",
						"0", "S13", "0", "S9", "S10", "0","0","0","0",
						"S3", "0", "0", "0", "0", "0","0","S7","0",
						"S3", "0", "0", "0", "0", "0","0","S7","0",
						"S3", "0", "0", "0", "0", "0","0","S7","0",
						"S3", "0", "0", "0", "0", "0","0","S7","0",
						"0", "r8", "r8", "r8", "r8", "r8","0","0","r8",
						"0", "r3", "S11", "r3", "r3", "S12","0","0","r3",
						"0", "r2", "S11", "r2", "r2", "S12","0","0","r2",
						"0", "r6", "r6", "r6", "r6", "r6","0","0","r6",
						"0", "r5", "r5", "r5", "r5", "r5","0","0","r5"
                        };
int gotoarr[18][4] = {0,0,0,0,
					  0,0,0,0,
					  5,6,0,7,
					  9,6,0,7,
					  0,0,0,0,
					  0,0,0,0,
					  0,0,0,0,
					  0,0,0,0,
					  0,0,0,0,
					  0,6,0,15,
					  0,6,0,16,
					  0,17,0,0,
					  0,18,0,0,
					  0,0,0,0,
					  0,0,0,0,
					  0,0,0,0,
					  0,0,0,0,
					  0,0,0,0
					};
char vt[9] = {'(', ')', '*', '+','-', '/', '=','i', '#'}; //存放终结符
char vn[4] = {'E','F', 'S', 'T'}; //存放非终结符
string Production[9] = {"S->i=E","E->E-T", "E->E+T","E->T", "T->T/F","T->T*F", "T->F", "F->(E)", "F->i"};//产生式集合

int com = 0;
int line = 1;//记录处理的步骤数
bool flag = false;
int StatusNumber = 1;//栈中状态数
string StackString = "#";//记录符号栈中内容
int Status[50] = {0};//记录状态栈
stack<char> Stack;//创建一个符号栈
stack<int> status;//创建一个状态栈

void Judge(int &i, int j, const char arr[], char ch, string s) {//判断输入串是否由文法终结符组成
    flag = false;
    for (int l = 0; l < j; l++) {
        if (ch == arr[l]) {
            flag = true;
            i = l;
            break;
        }
    }
    if (!flag) {
        cout << "\tError" << endl;
        com = s.size();
    }
}
 
void OutputStatus() {//输出状态集
    for (int i = 0; i < StatusNumber; i++)
        cout << Status[i];
}
 
void OutputString(string s) {//输出未处理的字符串
    for (int i = com; i < s.size(); i++)
        cout << s.at(i);
}
 
void Output(string s) {//输出步骤、 状态集、 符号集、 输入串
    cout << line << "\t";
    OutputStatus();
    cout << "\t" << StackString << "\t";
    OutputString(s);
    cout << "\t\t";
    line++;
}
 
void Shift(int i, string s) {//移进函数 S
    Output(s);
    cout << "ACTION[" << status.top() << "," << s.at(com) << "]=S" << i << ",状态" << i << "入栈" << endl;
    status.push(i);//将状态 i 压进状态
    Status[StatusNumber] = i;//Status 记录状态栈的内容
    Stack.push(s.at(com));//将当前面临的输入串符号压进符号栈
    StackString = StackString + s.at(com);//StackString 记录符号栈的内容
    com++;//当前面临的输入串字符往后移一位
    StatusNumber++;//状态数加一
}
 
void Goto(stack<int> st1, stack<char> st2, string s) {//GoTo 语句
    int j = -1;
    int ch1 = st1.top();
    char ch2 = st2.top();
    Judge(j, 4, vn, ch2, s);//求得 ch2 在非终结符表中的位置
    if (gotoarr[ch1][j] == 0) {
        cout << "\tError" << endl;
        com = s.size();
    } else {
        status.push(gotoarr[ch1][j]);//新状态进栈
        Status[StatusNumber] = gotoarr[ch1][j];
        StatusNumber++;
    }
}
 
void Reduction(int i, string s) {//归约函数 R
    Output(s);
    cout << "r" << i << ":" << Production[i - 1] << "归约， GoTo(";
    int N = Production[i - 1].length() - 3;
    for (int j = 0; j < N; j++) {//消除要归约的状态及符号
        status.pop();
        Stack.pop();
        StatusNumber--;
        StackString.erase(StackString.length() - 1);
    }
    cout << status.top() << "," << Production[i - 1].at(0) << ")=";
    Stack.push(Production[i - 1].at(0));//符号进栈
    StackString = StackString + Stack.top();
    Goto(status, Stack, s);
    cout << status.top() << "入栈" << endl;
    Status[StatusNumber] = status.top();
}
 
void Analyse(string s) {//具体分析函数
    Stack.push('#');//初始化
    status.push(0);
    s = s + "#";
    int t = -1;//记录 ch 在数组 vt 的位置
    while (com < s.size()) {
        int i = status.top();
        char ch = s.at(com);
        Judge(t, 9, vt, ch, s);
        if (flag) {
            if (action[i][t] != "acc" && action[i][t] != "0") {
                if (action[i][t].at(0) == 'S') {
                    action[i][t].erase(0, 1); //删除 action[i][t]的首字母 S
                    Shift(atoi(action[i][t].c_str()), s);//atoi(action[i][t].c_str())， 将action[i][t]转换为整型
                    action[i][t].insert(0, "S");//将 S 添加回 action[i][t]
                } else if (action[i][t].at(0) == 'r') {
                    action[i][t].erase(0, 1);//删除 action[i][t]的首字母 r
                    Reduction(atoi(action[i][t].c_str()), s);//atoi(action[i][t].c_str())， 将action[i][t]转换为整型
                    action[i][t].insert(0, "r");//将 r 添加回 action[i][t]
                }
            } else if (action[i][t] == "0") {
                cout << "\tError" << endl;
                break;
            } else if (action[i][t] == "acc") {
                Output(s);
                cout << "acc" << "\t 分析成功" << endl;
                break;
            }
        } else if (!flag)
            break;
    }
}

void printTable() {
    cout << "\n------------------ Action Table -----------------\n" << endl;
    for(int i = 0; i < 16; i++){
    	if(i < 10) {
        	cout << "State " << i << ": ";    		
		} else {
			cout << "State " << i << ":"; 
		}
        for(int j = 0; j < 9; j++){
            cout << setw(10) << action[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n------------------ Goto Table ------------------\n" << endl;
    for(int i = 0; i < 16; i++){
        if(i < 10) {
        	cout << "State " << i << ": ";    		
		} else {
			cout << "State " << i << ":"; 
		}
        for(int j = 0; j < 4; j++){
            cout << setw(10) << gotoarr[i][j] << " ";
        }
        cout << "\n";
    }

    
	cout << "\n------------------四元式生成--------------------\n" << endl;
}
 
int main() {
    string s;
    cout << "输入的文法" << endl;
    for (int j = 0; j < 9; j++)
        cout << Production[j] << endl;
    cout << "VT:" << endl;
    for (int i = 0; i < 9; i++)
        cout << vt[i] << " ";
    cout << endl;
    cout << "VN:" << endl;
    for (int i = 0; i < 4; i++)
        cout << vn[i] << " ";
    cout << endl;
    cout << "****************************LR(1)****************************" << endl;
    char T;
    cout << "Enter String" << endl;
    cin >> s;
    cout << "**************************Analyzer***************************" << endl;
    cout << "Step" << "\t" << "StateStack" << "\t" << "SymbolStack" << "\t" << "RemainingString" << "\t" << "Info"
         << endl;
    Analyse(s);
    com = 0;
    line = 1;
    StackString = "#";
    StatusNumber = 1;
    while (!Stack.empty())
        Stack.pop();
    while (!status.empty())
        status.pop();
        
    printTable();  // 调用打印函数
    
    return 0;
}

