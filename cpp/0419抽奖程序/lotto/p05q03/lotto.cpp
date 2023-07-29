#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <cstdlib> // 通用函数头文件
#include <Windows.h>
using namespace std;

#define N 100

// functions to set a fancy color
void setConsoleColor(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄
    SetConsoleTextAttribute(hConsole, color); // 设置控制台颜色
}
void setConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄
    SetConsoleTextAttribute(hConsole, color); // 设置控制台颜色
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
        //vector<string> numbers;//所有候选人的电话号
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
        int index1 = rand() % numbers.size();//随机生成一个下标
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
    // 1、编程生成文本文件data.txt，文件内容是10个手机号码（手机号码前4位为1871，后面随机生成）（尝试用多种方式实现）（利用上一道题的程序来做）
    ofstream fout("data.txt");
    if (!fout.is_open())
    {
        cout << "Failed to open file." << endl;
        return 1;
    }
    random_device rd2;  //用于获取真随机数种子
    mt19937 gen2(rd2()); //以真随机数种子为基础创建随机数引擎
    uniform_int_distribution<> dist2(0, 9999999); //random number 0-9999999
    srand(time(0)); //使用当前时间作为随机数种子
    for (int i = 0; i < N; i++) //文件内容是10个手机号码（手机号码前4位为1871，后面随机生成）
    {
        fout << "1871";
        int num = dist2(gen2); //random number 0-9999999
        fout.width(7); //输出宽度7，不足7位自动用空格填充
        fout.fill('0'); //填充字符0
        fout << num << endl;
    }
    fout.close();
    //将上一道题的10改成100或是更大的数字



    // 3、预设一、二、三等奖的人数（一等奖 1 名、二等奖 2 名、三等奖 5名）（需要用类来实现）
    Prize prix(1, 2, 5); // initialize the number of the prizes

    // 2、编程：从文本文件data.txt中读取抽奖者的个人信息 （尝试用多种方式实现）
    int t = prix.candidates("data.txt"); // read the candidates' information from the file
    if (t == 0)
    {
        // 4、按下任意键开始抽奖，并把中奖人的手机号显示在屏幕上，反复抽出一、二、三等奖。如果抽完就不能再抽。
        prix.draw();
    }
    else
    {
        //cout << "information error!" << endl;
    }

    return 0;
}