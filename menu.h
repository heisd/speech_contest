//
// Created by 延年易廋 on 2025/8/19.
//

#pragma once
#include <iostream>
#include <sstream>
using namespace std;
class contestant{
public:
    string m_name;
    int m_id;
    int m_score;
    contestant(string name,int id){
        this->m_name=std::move(name);
        this->m_id=id;
    }
    //重载小括号
    bool operator<(const contestant&c)const{
        return this->m_score<c.m_score;
    }
    //提供将原来数据转换成为csv数据的形式
    string to_csv_string()const{
        stringstream ss;
        ss<<m_name<<","<<m_id<<","<<m_score<<endl;
        return ss.str();
    }
    contestant(){

    };
};
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
void exit();
bool MYCompare(contestant &s1,contestant&s2);
void menu();
void contest_start();
void menu_show();
void show_contest();
void clear_contest();
