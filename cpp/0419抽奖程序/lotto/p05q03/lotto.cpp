#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <cstdlib> // ͨ�ú���ͷ�ļ�
#include <Windows.h>
using namespace std;

#define N 100

// functions to set a fancy color
void setConsoleColor(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ����̨���
    SetConsoleTextAttribute(hConsole, color); // ���ÿ���̨��ɫ
}
void setConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ����̨���
    SetConsoleTextAttribute(hConsole, color); // ���ÿ���̨��ɫ
}

class Winner
{
    int prizeType;
    string phoneNumber;
public:
    Winner(int num, string phone) : prizeType(num), phoneNumber(phone) {}
};

class Prize
{
    // number of each level of prize
    int gold;
    int silver;
    int bronze;
public:
    vector<string> numbers; // the candidates vector
    vector<Winner> winners; // the winners vector
public:
    Prize(int g = 0, int s = 0, int b = 0) : gold(g), silver(s), bronze(b) {}
    int goldPrize() { return gold; }
    int silverPrize() { return silver; }
    int bronzePrize() { return bronze; }

    int candidates(string filename)
    {
        ifstream fin(filename);
        if (!fin.is_open())
        {
            cerr << "Error: failed to open data.txt" << endl;
            return 1;
        }
        //vector<string> numbers;//���к�ѡ�˵ĵ绰��
        string line;
        while (getline(fin, line))
        {
            numbers.push_back(line);
        }
        fin.close();
        return 0;
    }

    void draw()
    {
        // start the lottery draw
        cout << "Press any key to start the lottery draw..." << endl;
        cin.get();
        cout << "now drawing..." << endl;

        // draw the first prize
        Sleep(3000);
        setConsoleColor(14);
        int index1 = rand() % numbers.size();//�������һ���±�
        string goldWinner = numbers[index1];//
        numbers.erase(numbers.begin() + index1);//
        winners.emplace_back(gold, goldWinner);
        cout << "Gold prize winner: " << goldWinner << endl;

        // draw the second prize
        Sleep(3000);
        setConsoleColor(15);
        for (int i = 0; i < silver; i++)
        {
            int index2 = rand() % numbers.size();
            string silverWinner = numbers[index2];
            numbers.erase(numbers.begin() + index2);
            winners.emplace_back(silver, silverWinner);
            cout << "Silver prize winner " << i + 1 << ": " << silverWinner << endl;
            Sleep(1000);
        }

        // draw the third prize
        Sleep(3000);
        setConsoleColor(6);
        for (int i = 0; i < bronze; i++)
        {
            int index3 = rand() % numbers.size();
            string bronzeWinner = numbers[index3];
            numbers.erase(numbers.begin() + index3);
            winners.emplace_back(bronze, bronzeWinner);
            cout << "Bronze prize winner " << i + 1 << ": " << bronzeWinner << endl;
            Sleep(1000);
        }

        setConsoleColor(8);
        cout << "\nLottery ends! Thank you for your participation!" << endl;
    }
};



int main()
{
    // 1����������ı��ļ�data.txt���ļ�������10���ֻ����루�ֻ�����ǰ4λΪ1871������������ɣ��������ö��ַ�ʽʵ�֣���������һ����ĳ���������
    ofstream fout("data.txt");
    if (!fout.is_open())
    {
        cout << "Failed to open file." << endl;
        return 1;
    }
    random_device rd2;  //���ڻ�ȡ�����������
    mt19937 gen2(rd2()); //�������������Ϊ�����������������
    uniform_int_distribution<> dist2(0, 9999999); //random number 0-9999999
    srand(time(0)); //ʹ�õ�ǰʱ����Ϊ���������
    for (int i = 0; i < N; i++) //�ļ�������10���ֻ����루�ֻ�����ǰ4λΪ1871������������ɣ�
    {
        fout << "1871";
        int num = dist2(gen2); //random number 0-9999999
        fout.width(7); //������7������7λ�Զ��ÿո����
        fout.fill('0'); //����ַ�0
        fout << num << endl;
    }
    fout.close();
    //����һ�����10�ĳ�100���Ǹ��������



    // 3��Ԥ��һ���������Ƚ���������һ�Ƚ� 1 �������Ƚ� 2 �������Ƚ� 5��������Ҫ������ʵ�֣�
    Prize prix(1, 2, 5); // initialize the number of the prizes

    // 2����̣����ı��ļ�data.txt�ж�ȡ�齱�ߵĸ�����Ϣ �������ö��ַ�ʽʵ�֣�
    int t = prix.candidates("data.txt"); // read the candidates' information from the file
    if (t == 0)
    {
        // 4�������������ʼ�齱�������н��˵��ֻ�����ʾ����Ļ�ϣ��������һ���������Ƚ����������Ͳ����ٳ顣
        prix.draw();
    }
    else
    {
        //cout << "information error!" << endl;
    }

    return 0;
}