/*
	@author w
	@date 2019.6.17
	�����������ϸ����ֹ���
*/
#include "common_header.h"
#define bufsize 300
using namespace std;
char sentence[bufsize];
int main() {
	cout << "�������ķ���ÿ��һ���������װ� Ctrl+Z ��������һ���ķ������ַ�������Ϊ��ʼ����" << endl;
	input_grammer();
	pick_up();
	getFirstN();
	getFirstP();
	getFollow();
	generateTable();
	printAllTerminator();
	printAllNonTerminator();
	printAllFirstN();
	printAllFirstP();
	printAllFollow();
	printTable();
	cout << "---���Ӳ���---" << endl;
	while (true) {
		cout << "������һ�����ӣ����м䲻���ո񣬻س�����, �˳������� quit��" << endl;
		cin >> sentence;
		if (strcmp("quit", sentence) == 0)
			break;
		analyze(sentence);
	}

}