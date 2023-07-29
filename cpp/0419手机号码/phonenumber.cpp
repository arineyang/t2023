/*     手机号码自动生成

 编程生成文本文件data.txt，文件内容是10个手机号码（手机号码前4位为1871，后面随机生成）（尝试用多种方式实现，至少2种方式）

以word文档形式提交*/


#include <iostream>
#include <fstream>
#include <random> // for random_device and mt19937
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <iomanip>
using namespace std;

int main()
{
    //-------第一种方法：ofstream-------

    ofstream fout1("data1.txt");
    srand(time(0)); //使用当前时间作为随机数种子

    for (int i = 0; i < 10; i++) //文件内容是10个手机号码（手机号码前4位为1871，后面随机生成）
    {
        fout1 << "1871";
        for (int j = 0; j < 7; j++)
        {
            fout1 << rand() % 10; //random number 0-9
        }
        fout1 << endl;
    }

    fout1.close();


    //-------第二种方法：ofstream-------

    ofstream fout2("data2.txt");
    if (!fout2.is_open())
    {
        cout << "Failed to open file." << endl;
        return 1;
    }

    random_device rd2;  //用于获取真随机数种子
    mt19937 gen2(rd2()); //以真随机数种子为基础创建随机数引擎
    uniform_int_distribution<> dist2(0, 9999999); //random number 0-9999999
    srand(time(0)); //使用当前时间作为随机数种子

    for (int i = 0; i < 10; i++) //文件内容是10个手机号码（手机号码前4位为1871，后面随机生成）
    {
        fout2 << "1871";
        int num = dist2(gen2); //random number 0-9999999
        fout2.width(7); //输出宽度7，不足7位自动用空格填充
        fout2.fill('0'); //填充字符0
        fout2 << num << endl;
    }
    fout2.close();


    //-------第三种方法：iostream/fstream-------

    fstream fout3("data3.txt", ios::out); // 创建输入输出流对象
    srand(time(NULL)); //设置随机种子

    for (int i = 0; i < 10; i++)
    {
        fout3 << "1871" << setw(7) << setfill('0') << rand() % 100000000 << endl;
        //fout3 << "1871" << rand() % 100000000 << endl; //生成手机号并写入文件
    }

    fout3.close(); //关闭输入输出流对象


    //-------第四种方法：使用stdio.h库-------
    FILE* fp = fopen("data4.txt", "w"); //创建输出文件指针
    srand(time(NULL)); // 设置随机种子

    for (int i = 0; i < 10; i++)
    {
        fprintf(fp, "1871%07d\n", rand() % 100000000); //生成手机号并写入文件
    }

    fclose(fp); //关闭输出文件指针


    return 0;
}