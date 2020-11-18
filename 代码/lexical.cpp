#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

/*���

	1	procedure,

	2	begin,

	3	const,

	4	var,

	5	end,

	6	odd,	

	7	if,

	8	else,

	9	then,

	10	do,

	11	while,

	12	read,

	13	write,

	14  program,

	15  call��


	16	NUM,	//����

	17	ID,	//��ʶ��



	//�����

	18	ADD,	//'+'

	19	SUB,	//'-'

	20	MUL,	//'*'

	21	DIV,	//'/'

	22	EQUAL,	//'='��

	23	LESS,	//'<'

	24	GREAT,	//'>'

	25	LESSEQUAL,	//'<='

	26  GREATEQUAL,//'>='
	
	27  NOTEQUAL,	//'<>������

	
	28  ASSIGN,		//':='   ��ֵ

	



	//���

	29  SEMICOLON //';'

	30  COMMA	//','

	31 	LPAR,	//'('

	32  RPAR,	//')'


	33	.		//������

	
*/

fstream datafile;
string line;   //ÿһ���ַ���
int len;  //��ǰ�ַ�������
int row;    //��
int index;  //������ĳһ�е��ַ����
char ch;    //��ǰ�ַ�
vector<string>ID;   //��ʶ����
vector<int>NUM;     //������
string word;        //��ŵ���
int indexID = 0;
int indexNUM = 0;
string keyword[15] = { "procedure","begin","const","var","end","odd","if","else","then","do","while","read","write","program","call" };

int IsKeyWord(string word)
{//�ж��Ƿ�Ϊ�ؼ��֣����򷵻�λ�ã������򷵻�0
	int i;
	for (i = 0; i < 15; i++)
	{
		if (word.compare(keyword[i]) == 0)
		{
			return (i+1);
		}
	}
	return 0;
}
void GetChar()
{//������һ�ַ�����������ָʾ��ǰ��
	ch = tolower(line[index]); //���Сд��ĸ
	index++;    //ָʾ��ǰ��
}
void GetBC()
{//����Ƿ�Ϊ�ո����
	while ((ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r') && (index < len))
	{//��ֹ�հ��ж�ȡԽ��
		GetChar();
	}
}
void Retract()
{  //����ָʾ���ص�һ���ַ�������ch��Ϊ���ַ�
	index--;
	ch = ' ';
}
/*bool IsLetter(char ch)
{
	if (ch > 'a' && ch < 'z')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool IsDigit(char ch)
{
	if (ch > '0' && ch < '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}*/
void GetSYM()
{//�ʷ�����
	
	while (index <= len - 1)
	{
		GetChar();
		GetBC();   //�õ��ǿհ׻����ַ�
		if (index > len)
		{//˵���Ѷ��걾�У���������
			return;
		}
		if(isalpha(ch))
		{//��ĸ��ͷ��Ϊ��ʶ����ؼ���
			word = "";
			while (isalpha(ch) || isdigit(ch))
			{//������Ϊ��ĸ�����֣���һֱ���룬ֱ������
				word = word + ch;   //��ch�ӵ�wordβ��
				GetChar();
			}
			Retract();   //����ָʾ�����ص�һ���ַ�
			int n = IsKeyWord(word);    //����䷵��ֵ��λ�û�0

			if (n > 0)  //˵���õ����ǹؼ���
			{
				datafile << word << "\t" << "�ؼ���" << "\t" << n << endl;
			}
			else    //˵���õ���Ϊ��ʶ��
			{
				vector <string>::iterator iter_str;
				iter_str = find(ID.begin(), ID.end(), word);
				if (iter_str != ID.end())
				{//˵���ҵ��˸�Ԫ��
					datafile << word << "\t" << "��ʶ��" << "\t" << distance(ID.begin(), iter_str) << endl;
				}
				else
				{
					datafile << word << "\t" << "��ʶ��" << "\t" << indexID<< endl;
					indexID++;
					ID.push_back(word);
					//��һ���µ�Ԫ�ؼӵ�vector������棬λ��Ϊ��ǰԪ�ص���һ��Ԫ��
				}
			}
		}
		else if (isdigit(ch))  //��ͷΪ����
		{
			word = "";
			while (isdigit(ch))
			{
				word = word + ch;
				GetChar();
			}
			if (isalpha(ch))
			{//���ֺ����ĸ
				datafile << "error:��ʶ�����淶" << "    ��" << row << "�е�" << index << "��" << endl;
				while (isdigit(ch) || isalpha(ch))
				{
					index++;
					GetChar();
				}
			}
			else
			{
				Retract();  //�ص�һ���ַ�
				int num = atoi(word.c_str());
				//c_str()��������һ��ָ������C�ַ�����ָ�볣�� 
				//Ϊ����c���Լ��ݣ���c������û��string���ͣ��ʱ���ͨ��string�����ĳ�Ա����c_str()��string ����ת����c�е��ַ�����ʽ��
				vector <int>::iterator iter_digit;
				iter_digit = std::find(NUM.begin(), NUM.end(), num);//�鳣����
				if (iter_digit == NUM.end())  //����δ�ҵ��˳���
				{
					datafile << word << "\t" << "����" << "\t" << indexNUM << endl;
					indexNUM++;
					NUM.push_back(num);
				}
				else
				{
					datafile << word << "\t" << "����" << "\t" << distance(NUM.begin(), iter_digit) << endl;
				}
			}
		}
		else if(ch == '+')
		{
			
			datafile << "+" << "\t" << "18" << "\t"<< "~" << endl;
		}
		else if (ch == '-')
		{
			datafile << "-" << "\t" << "19" << "\t" << "~" << endl;
		}
		else if (ch == '*')
		{
			datafile << "*" << "\t" << "20" << "\t" << "~" << endl;
		}
		else if (ch == '/')
		{
			datafile << "/" << "\t" << "21" << "\t" << "~" << endl;
		}
		else if (ch == '=')
		{
			datafile << "=" << "\t" << "22" << "\t" << "~" << endl;
		}
		else if (ch == '<')
		{
			if (line[index] == '=')  //idexʼ��ָ����һ�������ַ�
			{
				datafile << "<=" << "\t" << "25" << "\t" << "~" << endl;
				index++;
			}
			else if (line[index] == '>')
			{
				datafile << "<>" << "\t" << "27" << "\t" << "~" << endl;
				index++;
			}
			else
			{
				datafile << "<" << "\t" << "23" << "\t" << "~" << endl;
			}
		}
		else if (ch == '>')
		{
			if (line[index] == '=')
			{
				datafile << ">=" << "\t" << "26" << "\t" << "~" << endl;
				index++;
			}
			else
			{
				datafile << ">" << "\t" << "24" << "\t" << "~" << endl;
			}
		}
		else if (ch == ':')
		{
			if (line[index] == '=')
			{
				datafile << ":=" << "\t" << "27" << "\t" << "~" << endl;
				index++;
			}
			else
			{
				datafile << "error:��ֵ�Ŵ���ӦΪ :=" << "    ��" << row << "�е�" << index << "��" << endl;
			}
		}
		else if (ch == ';')
		{
			datafile << ";" << "\t" << "29" << "\t" << "~" << endl;
		}
		else if (ch == ',')
		{
			datafile << "," << "\t" << "30" << "\t" << "~" << endl;
		}
		else if (ch == '(')
		{
			datafile << "(" << "\t" << "31" << "\t" << "~" << endl;
		}
		else if (ch == ')')
		{
			datafile << ")" << "\t" << "32" << "\t" << "~" << endl;
		}
		else if (ch == '.')
		{
			datafile << "." << "\t" << "33" << "\t" << "~" << endl;
			datafile << "END" << endl;
			return ;
		}
		else
		{
			datafile << "error:�Ƿ��ַ���" << "    ��" << row << "�е�" << index << "��" << endl;
		}
	}
}
int main()
{
	fstream read_file;
	char filename[100];   //�ļ���
	cout << "������Ҫ������ļ�����";
	cin >> filename;
	read_file.open(filename, ios::in);
	if (read_file.fail())
	{
		cout << "�������ļ�ʧ��\n";
		return 0;
	}
	datafile.open("C:\\Users\\a\\Desktop\\lex_out.txt", ios::out);
	if (datafile.fail())
	{
		cout << "����ļ���ʧ��\n";
		return 0;
	}
	row = 1;//�ӵ�һ�п�ʼ
	while (getline(read_file, line))
	{
		len = line.length();  //��ǰ���ַ�������
		index = 0;
		GetSYM();
		row++;
	}
	cout << "�ļ��������" << endl;
	read_file.close();
	datafile.close();
	return 0;
}