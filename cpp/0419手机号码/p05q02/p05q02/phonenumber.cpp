/*     �ֻ������Զ�����

 ��������ı��ļ�data.txt���ļ�������10���ֻ����루�ֻ�����ǰ4λΪ1871������������ɣ��������ö��ַ�ʽʵ�֣�����2�ַ�ʽ��

��word�ĵ���ʽ�ύ*/


#include <iostream>
#include <fstream>
#include <random> // for random_device and mt19937
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <iomanip>
using namespace std;

int main()
{
    //-------��һ�ַ�����ofstream-------

    ofstream fout1("data1.txt");
    srand(time(0)); //ʹ�õ�ǰʱ����Ϊ���������

    for (int i = 0; i < 10; i++) //�ļ�������10���ֻ����루�ֻ�����ǰ4λΪ1871������������ɣ�
    {
        fout1 << "1871";
        for (int j = 0; j < 7; j++)
        {
            fout1 << rand() % 10; //random number 0-9
        }
        fout1 << endl;
    }

    fout1.close();


    //-------�ڶ��ַ�����ofstream-------

    ofstream fout2("data2.txt");
    if (!fout2.is_open())
    {
        cout << "Failed to open file." << endl;
        return 1;
    }

    random_device rd2;  //���ڻ�ȡ�����������
    mt19937 gen2(rd2()); //�������������Ϊ�����������������
    uniform_int_distribution<> dist2(0, 9999999); //random number 0-9999999
    srand(time(0)); //ʹ�õ�ǰʱ����Ϊ���������

    for (int i = 0; i < 10; i++) //�ļ�������10���ֻ����루�ֻ�����ǰ4λΪ1871������������ɣ�
    {
        fout2 << "1871";
        int num = dist2(gen2); //random number 0-9999999
        fout2.width(7); //������7������7λ�Զ��ÿո����
        fout2.fill('0'); //����ַ�0
        fout2 << num << endl;
    }
    fout2.close();


    //-------�����ַ�����iostream/fstream-------

    fstream fout3("data3.txt", ios::out); // �����������������
    srand(time(NULL)); //�����������

    for (int i = 0; i < 10; i++)
    {
        fout3 << "1871" << setw(7) << setfill('0') << rand() % 100000000 << endl;
        //fout3 << "1871" << rand() % 100000000 << endl; //�����ֻ��Ų�д���ļ�
    }

    fout3.close(); //�ر��������������


    //-------�����ַ�����ʹ��stdio.h��-------
    FILE* fp = fopen("data4.txt", "w"); //��������ļ�ָ��
    srand(time(NULL)); // �����������

    for (int i = 0; i < 10; i++)
    {
        fprintf(fp, "1871%07d\n", rand() % 100000000); //�����ֻ��Ų�д���ļ�
    }

    fclose(fp); //�ر�����ļ�ָ��


    return 0;
}