/*
	@author w
	@date 2019.6.17
	���������������������� �� ��֤�ķ�����
*/
#include "common_header.h"
using namespace std;

//�ķ�����
extern string grammar[maxnum];
//��ά���飬Ԥ���������Ų���ʽ�����±꣬û�еĵط�����Ϊ -1
extern int table[maxnum][maxnum];
//��ʼ����
extern char start_char;
//��ӡ��ǰ״̬
void printCurrentStatus(const char* s1, const char* s2, const string& s3) {
	cout << setw(Table_width) << s1 << setw(Table_width) << s2 << setw(Table_width) << s3 << endl;
}
// ��������
// ����ɹ���������� ��������
void analyze(const char* sentence, int len) {
	char str[300];
	strcpy(str, sentence);
	if (len == -1)
		len = strlen(str);
	str[len++] = '$'; // ��ĩβ���� '$'
	str[len] = 0;
	char stk[200] = {0}; //����ģ��ջ
	int pos = 0;
	// ��ջ�м���'$'�Ϳ�ʼ����
	stk[pos++] = '$';
	stk[pos++] = start_char;
	cout << setw(Table_width) << "ջ" << setw(Table_width) << "����" << setw(Table_width) << "����" << endl;
	//��ӡ ��ǰջ������ + ʣ������ + ��������
	printCurrentStatus(stk, str, string("��ʼ"));
	for (int i = 0;i < len;) {
		stk[pos] = 0;
		char top = stk[--pos];
		if (top == '$') {
			if (str[i] == '$') {
				printCurrentStatus(stk, str + i, string("����"));
				cout << "�����ɹ���" << endl;
				break;
			}
			else {
				//��ӡ ��ǰջ������ + ʣ������ + ��������
				printCurrentStatus(stk, str + i, string("����"));
				cerr << "����ջջ��Ϊ'$'������������δ�����������˳�..." << endl;
				exit(EXIT_FAILURE);
			}
		}
		// ���ջ������ '$'
		int current_type = typeOf(top);
		if (current_type == Terminator) {
			if (top == str[i]) {
				i++; //�����ַ���ȡ��
				stk[pos] = 0;
				string res("ƥ�� ");
				//��ӡ ��ǰջ������ + ʣ������ + ��������
				printCurrentStatus(stk, str + i, res + top);
			}
			else {
				//��ӡ ��ǰջ������ + ʣ������ + ��������
				printCurrentStatus(stk, str + i, string("����"));
				cerr << "����ջջ��Ϊ�ս�� '" << top << "'�������������Ϊ '" << str[i] << "'�������˳�..." << endl;
				exit(EXIT_FAILURE);
			}
		}
		else if (current_type == NonTerminator) {
			int g_index = table[indexOfNonT(top)][indexOfTerm(str[i])];
			if (g_index != -1) {
				if (grammar[g_index][3] != '@') { // ����ұ� �� @����ô����ջ�����Ӷ���
					// ������ʽ���Ҳ����� ���� ��ջ
					for (int i = grammar[g_index].size() - 1; i >= 3;i--) {
						stk[pos++] = grammar[g_index][i];
					}
				}
				//��ӡ ��ǰջ������ + ʣ������ + ��������
				printCurrentStatus(stk, str + i, grammar[g_index]);

			}
			else {
				//��ӡ ��ǰջ������ + ʣ������ + ��������
				printCurrentStatus(stk, str + i, string("����"));
				cerr << "������ table[" << top << "][" << str[i] << "] ��Ϊ�ա������˳�..." << endl;
				exit(EXIT_FAILURE);
			}
		}
		else {
			cerr << "��������������ֹ����..." << endl;
			exit(EXIT_FAILURE);
		}
	}

}
