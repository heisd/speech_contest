//
// Created by 延年易廋 on 2025/8/19.
//
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
void menu(){
    cout<<"*****************"<<endl;
    cout<<"**欢迎参加演讲比赛**"<<endl;
    cout<<"** 1.开始演讲比赛**"<<endl;
    cout<<"** 2.查看往届比赛**"<<endl;
    cout<<"** 3.清空比赛记录**"<<endl;
    cout<<"** 0.退出比赛程序**"<<endl;
    cout<<"*****************"<<endl;
}
class contestant{
public:
    //重载小括号
    bool operator<(const contestant&c)const{
        return this->m_score<c.m_score;
    }
    //使用int类型的数据要初始化一下
    string m_name;
    int m_id=0;
    int m_score=0;
    contestant(string name,int id){
        this->m_name=std::move(name);
        this->m_id=id;
    }
    contestant()= default;
    // 转换为 CSV 字符串的方法
    string to_csv_string() const {
        stringstream ss;
        ss << m_name << "," << m_id << "," << m_score;
        return ss.str();
    }
};
//为了对结构体进行比较我们可以使用一个函数来定义
bool MYCompare(contestant &s1,contestant&s2){
    return s1.m_score>s2.m_score;
}
class MyPrint{
public:
    void operator()(contestant &c){
        cout<<c.m_id<<" ";
    }
};
class MyPrintImage{
public:
    void operator()(contestant &c){
        cout<<"编号 :"<<c.m_id<<"姓名 :"<<c.m_name<<"成绩 :"<<c.m_score<<endl;
    }
};
//改进版
void contest_start() {
    //初始化12名选手的信息
    string NameSeed = "ABCDEFGHIJKL";
    vector<contestant> contestants;
    for (int i = 0; i < 12; ++i) {
        contestant contestantImage("选手 " + string(1, NameSeed[i]), 10001 + i);
        contestants.push_back(contestantImage);
    }
    //比赛详情
    int choose=1;
    for (int i = 1; i <=2 ; ++i) {
        cout<<"第"<<i<<"轮比赛正在抽签"<<endl;
        cout<<"-------------------"<<endl;
        shuffle(contestants.begin(),contestants.end(), std::mt19937(std::random_device()()));
        for_each(contestants.begin(),contestants.end(),MyPrint());
        cout<<"--------------------"<<endl;
        system("pause");
        cout<<"-------第"<<i<<"轮比赛正式开始------"<<endl;
        for (int j = 0; j < contestants.size(); ++j) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<>dis(60,90);
            //如果在写代码的时候已经数据并且初始化好了可以使用这种方法把新的数据存入结构体中
            for(auto& contestant:contestants){
                contestant.m_score=dis(gen);
            }
        }
        if(i==1) {
            //第一组一共有
            vector<contestant> group1;
            cout << "第一组比赛名次" << endl;
            group1.assign(contestants.begin(), contestants.begin() + 6);
            sort(group1.begin(), group1.end(), MYCompare);
            for_each(group1.begin(), group1.end(), MyPrintImage());
            cout << "第二组比赛名次" << endl;
            vector<contestant> group2;
            group2.assign(contestants.begin() + 6, contestants.end());
            sort(group2.begin(), group2.end(), MYCompare);
            for_each(group2.begin(), group2.end(), MyPrintImage());
        }else if(i==2){

        }


    }




}