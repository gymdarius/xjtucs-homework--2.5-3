#include <iostream>
#include <stack>
#include <string>
 
using namespace std;
 
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
int gotoarr[12][3] = {1, 2, 3, //GOTO ��
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
char vt[6] = {'i', '+', '*', '(', ')', '#'}; //����ս��
char vn[3] = {'E', 'T', 'F'}; //��ŷ��ս��
string Production[6] = {"E->E+T", "E->T", "T->T*F", "T->F", "F->(E)", "F->i"};//����ʽ����
int com = 0;
int line = 1;//��¼����Ĳ�����
bool flag = false;
int StatusNumber = 1;//ջ��״̬��
string StackString = "#";//��¼����ջ������
int Status[50] = {0};//��¼״̬ջ
stack<char> Stack;//����һ������ջ
stack<int> status;//����һ��״̬ջ
void Judge(int &i, int j, const char arr[], char ch, string s) {//�ж����봮�Ƿ����ķ��ս�����
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
 
void OutputStatus() {//���״̬��
    for (int i = 0; i < StatusNumber; i++)
        cout << Status[i];
}
 
void OutputString(string s) {//���δ������ַ���
    for (int i = com; i < s.size(); i++)
        cout << s.at(i);
}
 
void Output(string s) {//������衢 ״̬���� ���ż��� ���봮
    cout << line << "\t";
    OutputStatus();
    cout << "\t" << StackString << "\t";
    OutputString(s);
    cout << "\t\t";
    line++;
}
 
void Shift(int i, string s) {//�ƽ����� S
    Output(s);
    cout << "ACTION[" << status.top() << "," << s.at(com) << "]=S" << i << ",״̬" << i << "��ջ" << endl;
    status.push(i);//��״̬ i ѹ��״̬
    Status[StatusNumber] = i;//Status ��¼״̬ջ������
    Stack.push(s.at(com));//����ǰ���ٵ����봮����ѹ������ջ
    StackString = StackString + s.at(com);//StackString ��¼����ջ������
    com++;//��ǰ���ٵ����봮�ַ�������һλ
    StatusNumber++;//״̬����һ
}
 
void Goto(stack<int> st1, stack<char> st2, string s) {//GoTo ���
    int j = -1;
    int ch1 = st1.top();
    char ch2 = st2.top();
    Judge(j, 3, vn, ch2, s);//��� ch2 �ڷ��ս�����е�λ��
    if (gotoarr[ch1][j] == 0) {
        cout << "\tError" << endl;
        com = s.size();
    } else {
        status.push(gotoarr[ch1][j]);//��״̬��ջ
        Status[StatusNumber] = gotoarr[ch1][j];
        StatusNumber++;
    }
}
 
void Reduction(int i, string s) {//��Լ���� R
    Output(s);
    cout << "r" << i << ":" << Production[i - 1] << "��Լ�� GoTo(";
    int N = Production[i - 1].length() - 3;
    for (int j = 0; j < N; j++) {//����Ҫ��Լ��״̬������
        status.pop();
        Stack.pop();
        StatusNumber--;
        StackString.erase(StackString.length() - 1);
    }
    cout << status.top() << "," << Production[i - 1].at(0) << ")=";
    Stack.push(Production[i - 1].at(0));//���Ž�ջ
    StackString = StackString + Stack.top();
    Goto(status, Stack, s);
    cout << status.top() << "��ջ" << endl;
    Status[StatusNumber] = status.top();
}
 
void Analyse(string s) {//�����������
    Stack.push('#');//��ʼ��
    status.push(0);
    s = s + "#";
    int t = -1;//��¼ ch ������ vt ��λ��
    while (com < s.size()) {
        int i = status.top();
        char ch = s.at(com);
        Judge(t, 6, vt, ch, s);
        if (flag) {
            if (action[i][t] != "acc" && action[i][t] != "0") {
                if (action[i][t].at(0) == 'S') {
                    action[i][t].erase(0, 1); //ɾ�� action[i][t]������ĸ S
                    Shift(atoi(action[i][t].c_str()), s);//atoi(action[i][t].c_str())�� ��action[i][t]ת��Ϊ����
                    action[i][t].insert(0, "S");//�� S ��ӻ� action[i][t]
                } else if (action[i][t].at(0) == 'r') {
                    action[i][t].erase(0, 1);//ɾ�� action[i][t]������ĸ r
                    Reduction(atoi(action[i][t].c_str()), s);//atoi(action[i][t].c_str())�� ��action[i][t]ת��Ϊ����
                    action[i][t].insert(0, "r");//�� r ��ӻ� action[i][t]
                }
            } else if (action[i][t] == "0") {
                cout << "\tError" << endl;
                break;
            } else if (action[i][t] == "acc") {
                Output(s);
                cout << "acc" << "\t �����ɹ�" << endl;
                break;
            }
        } else if (!flag)
            break;
    }
}
 
int main() {
    string s;
    cout << "������ķ�" << endl;
    for (int j = 0; j < 6; j++)
        cout << Production[j] << endl;
    cout << "VT:" << endl;
    for (int i = 0; i < 6; i++)
        cout << vt[i] << " ";
    cout << endl;
    for (int i = 0; i < 3; i++)
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
    return 0;
}