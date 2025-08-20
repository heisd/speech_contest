
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
void contest_start(){
    //初始化12名选手的信息
    string NameSeed="ABCDEFGHIJKL";
    vector<contestant>contestants;
    for (int i = 0; i < 12; ++i) {
        contestant contestantImage("选手 " + string(1, NameSeed[i]),10001+i);
        contestants.push_back(contestantImage);
    }
    //开始比赛
        cout<<"第1轮比赛正在抽签"<<endl;
        cout<<"-------------------"<<endl;
        shuffle(contestants.begin(),contestants.end(), std::mt19937(std::random_device()()));
        for_each(contestants.begin(),contestants.end(),MyPrint());
        cout<<"--------------------"<<endl;
        system("pause");
        cout<<"-------第1轮比赛正式开始------"<<endl;
        //初始化成绩
        //成绩在80~90
        //使用c++风格的随机数
        for (int j = 0; j < 12; ++j) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<>dis(60,90);
            //如果在写代码的时候已经数据并且初始化好了可以使用这种方法把新的数据存入结构体中
            for(auto& contestant:contestants){
                contestant.m_score=dis(gen);
            }
        }
        vector<contestant>group1;
        //第一组一共有
        cout<<"第一组比赛名次"<<endl;
        group1.assign(contestants.begin(),contestants.begin()+6);
        sort(group1.begin(),group1.end(), MYCompare);
        for_each(group1.begin(),group1.end(),MyPrintImage());
        cout<<"第二组比赛名次"<<endl;
        vector<contestant>group2;
        group2.assign(contestants.begin()+6,contestants.end());
        sort(group2.begin(),group2.end(), MYCompare);
        for_each(group2.begin(),group2.end(),MyPrintImage());
        cout<<"---------第一轮比赛结束------------"<<endl;
        system("pause");
        cout<<"---------第一轮晋级选手如下---------"<<endl;
        vector<contestant>success_group1;
        success_group1.assign(group1.begin(),group1.begin()+3);
        for_each(success_group1.begin(),success_group1.end(),MyPrintImage());
        vector<contestant>success_group2;
        success_group2.assign(group2.begin(),group2.begin()+3);
        for_each(success_group2.begin(),success_group2.end(),MyPrintImage());
        vector<contestant>success_groups;
        //在使用resize的时候需要默认构造
        success_groups.resize(success_group1.size()+success_group2.size());
        //在使用merge是会需要比较元素
        //因为merge不是简单的拼接而是有序合并
        //所以说需要重载<的定义
        merge(success_group1.begin(),success_group1.end(),success_group2.begin(),success_group2.end(),success_groups.begin());
        system("pause");
        cout<<"第2轮比赛正在抽签"<<endl;
        cout<<"-------------------"<<endl;
        //c++风格的洗牌操作==random_shuffle
        shuffle(success_groups.begin(),success_groups.end(), std::mt19937(std::random_device()()));
        for_each(success_groups.begin(),success_groups.end(),MyPrint());
        cout<<"--------------------"<<endl;
        system("pause");
        cout<<"-------第2轮比赛正式开始------"<<endl;
        for (int j = 0; j < 6; ++j) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<>dis(60,90);
        //如果在写代码的时候已经数据并且初始化好了可以使用这种方法把新的数据存入结构体中
        for(auto& contestant:success_groups){
            contestant.m_score=dis(gen);
        }
    }
        cout<<"第一组比赛名次"<<endl;
    sort(success_groups.begin(),success_groups.end(), MYCompare);
    for_each(success_groups.begin(),success_groups.end(),MyPrintImage());
    cout<<"第二轮比赛完毕"<<endl;
    system("pause");
    cout<<"第二组晋级情况如下"<<endl;
    vector<contestant>winners;
    winners.assign(success_groups.begin(),success_groups.begin()+3);
    for_each(winners.begin(),winners.end(),MyPrintImage());
    system("pause");
    //保存到csv文件中
    ofstream file;
    file.open("speech.csv",ios::out);
    if(!file.is_open()){
        cerr<<"无法打开文件: "<<"speech.csv"<<endl;
        return;
    }
    //写入表头
    file<<"姓名,ID,分数"<<endl;
    //写入数据
    for(const auto&contestant:winners){
        file<<contestant.to_csv_string()<<endl;
    }
    file.close();
    system("cls");
    menu();
    cout<<"记录已经保存"<<endl;
    cout<<"本届比赛完毕"<<endl;
    system("pause");
}
void show_contest(){
    ifstream file;
    if(!file.is_open()){
        cerr<<"无法打开文件"<<"speech.csv"<<endl;
        return;
    }
    file.open("speech.csv",ios::in);
    string line;
    cout << "=== " << "speech.csv" << " 内容 ===" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
};
int main(){


    show_contest();
}