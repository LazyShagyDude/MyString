#include <QStringList>
#include <QString>
#include <QTextStream>
#include <QChar>
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

class MyString {
protected:
    int len;
    QString pointer;
public:
    MyString()//конструктор по умолчанию
    {
    }

    MyString(char *str)// принимает строку
    {
        QString str_new (str);
        pointer = str_new;
        len = str_new.length();

    }

    MyString(char symbol)
    { //принимает символ
        QString str_new (symbol);
        pointer = str_new;
    }

   explicit MyString(const MyString* copy)
      : pointer(copy->pointer) {}


    int MyStringLength()
    {
       return len;
    }

    QString getpointer()
    {
       return pointer;
    }

   ~MyString()
    {
        pointer = nullptr;
        len = 0;
    }
};
class StringIdentify : public MyString
{
public:

    StringIdentify() : MyString()
    {

    }

    StringIdentify(char *str)
    {

        QString str_new (str);
        pointer = str_new;
        len = str_new.length();
    }

    StringIdentify(const StringIdentify &copy)
    {
        pointer= copy.pointer;
    }

    void Uppercase() {
        pointer = pointer.toUpper();
    }

    bool operator<(const StringIdentify &one) const
    {
        return this->len < one.len;
    }
    bool operator>(const StringIdentify &one) const
    {
        return this->len > one.len;
    }

    ~StringIdentify()
    {

    }

};
class Eight : public MyString
{
public:

    Eight() : MyString()
    {
    }

    Eight(const char *str)
    {
        QString str_new (str);
        pointer = str_new;
        len = str_new.length();
    }

    Eight(const Eight &copy)
    {
        pointer= copy.pointer;
    }


    bool ChangeChar()
    {
        bool ok;
        int oct = pointer.toInt(&ok,8);
        if (oct != 1){
            return false;
        }
        else{
            return true;
        }
    }


    ~Eight()
    {

    }
};
int main()
{
    QTextStream out(stdout);
    QTextStream cin(stdin);
    int number = 0;
    do {

        cout << "Input number of pointers to String (4-6 pointers): "; //количество указателей
        cin >> number;
    } while (number != 4 && number != 5 && number != 6);

    MyString **p = new MyString *[number];
    char str[100]; //значение, задаваемое пользователем
    int mainMenu; //главное меню
    int record; //номер записи
    char type; //тип записи
    int mystr[6] = {0};
    int strid[6] = {0};
    int eight[6] = {0};
    do {
            int choose;
            int counter = 0; //счетчик для смены значения (отслеживает, впервые ли оно задано или повторно)

            cout << "1. New value" << endl; //задаем значение указателям
            cout << "2. MyString" << endl; //тестируем MyString
            cout << "3. StringIdentify" << endl; //тестируем MyString
            cout << "4. Eight" << endl; //тестируем MyString
            cout << "5. Exit" << endl;//тестируем StringIdentify

            cin >> mainMenu;

            switch (mainMenu) {
            case 1: {
                                do {
                                    system("cls");
                                    cout << "Input number of the record (from 0 to " << number - 1 << "): ";
                                    cin >> record;
                                } while (record < 0 || record >= number);

                if (mystr[record] != 1 && strid[record] != 1 && eight[record] != 1){
                                    cout << "Choose a class:\ns - String\ni - StringIdentify\ne - Eight" << endl; //����� ������ ����� ������
                                    do {
                                        cin >> type;
                                    } while (type != 's' && type != 'i' && type != 'e');
                                }

                                cout << "Input value: "; //значение нового объекта
                                cin >> str;

                                if (mystr[record]) {
                                                    if (str[1] == '\0'){
                                                        char symbol = str[0];
                                                        MyString msTestSy(symbol);
                                                        *p[record] = msTestSy;
                                                    } else {
                                                        MyString msTestSt(str);
                                                        *p[record] = msTestSt;
                                                    }
                                                }

                                                if (type == 's' && mystr[record] != 1) {
                                                    if (str[1] == '\0'){
                                                        char symbol = str[0];
                                                        p[record] = new MyString(symbol);
                                                    } else p[record] = new MyString(str);
                                                    mystr[record] = 1;
                                                }

                                                if (strid[record]){
                                                    StringIdentify siTest(str);
                                                    static_cast<StringIdentify&>(*p[record]) = siTest;
                                                }

                                                if (type == 'i' && strid[record] != 1) {
                                                    p[record] = new StringIdentify(str);
                                                    strid[record] = 1;
                                                }

                                                if (eight[record]){
                                                    Eight cnTest(str);
                                                    static_cast<Eight&>(*p[record]) = cnTest;
                                                }

                                                if (type == 'e' && eight[record] != 1) {
                                                    p[record] = new Eight(str);
                                                    eight[record] = 1;
                                                }

                                                system("pause");
                                                break;

                             }
                case 2: {
                    cout << "Choose a number of testing record: ";
                    for (int i = 0; i < number; i++) {
                        if (mystr[i]) {
                            cout << i << " ";
                            counter++;
                        }
                    }

                    if (!counter){
                        cout << "Error: data isn't exist" << endl;
                        system("pause");
                        break;
                    }

                    cout << endl;
                    cin >> choose;
                    while (!mystr[choose] || choose >= number || choose < 0){
                        cout << "Enter number of exist testing record: ";
                        cin >> choose;
                    }

                    int msMenu;
                    do {
                        system("cls");
                        cout << "1. Length of string" << endl;
                        cout << "2. Exit" << endl;

                        cin >> msMenu;
                        switch(msMenu){
                            case 1: {
                                cout<<"Str: "<<p[record]->getpointer().toStdString()<< endl;
                                cout <<"Len: " << p[choose]->MyStringLength() << endl;
                                system("pause");
                                break;
                            }
                        }
                    } while (msMenu != 2);
                    break;
                }

            case 3: {
                            cout << "Choose a number of testing record: ";
                            for (int i = 0; i < number; i++) {
                                if (strid[i]) {
                                    cout << i << " ";
                                    counter++;
                                }
                            }

                            if (!counter){
                                cout << "Error: data isn't exist" << endl;
                                system("pause");
                                break;
                            }

                            cout << endl;
                            cin >> choose;
                            while (!strid[choose] || choose >= number || choose < 0){
                                cout << "Enter number of exist testing record: ";
                                cin >> choose;
                            }

                            int siMenu;
                            do {
                                system("cls");
                                cout << "1. Uppercase" << endl;
                                cout << "2. Exit" << endl;

                                cin >> siMenu;
                                switch(siMenu){
                                    case 1: {
                                    StringIdentify *dd = (StringIdentify*)p[choose];
                                    dd->Uppercase();
                                        cout<<"Str: "<<dd->getpointer().toStdString()<< endl;
                                        system("pause");
                                        break;
                                    }
                                }
                            } while (siMenu != 2);
                            system("cls");
                            break;
                        }
            case 4: {
                           cout << "Choose a number of testing record: ";
                           for (int i = 0; i < number; i++) {
                               if (eight[i]) {
                                   cout << i << " ";
                                   counter++;
                               }
                           }

                           if (!counter){
                               cout << "Error: data isn't exist" << endl;
                               system("pause");
                               break;
                           }

                           cout << endl;
                           cin >> choose;
                           while (!eight[choose] || choose >= number || choose < 0){
                               cout << "Enter number of exist testing record: ";
                               cin >> choose;
                           }

                           int siMenu;
                           do {
                               system("cls");
                               cout << "1. ChangeChar" << endl;
                               cout << "2. Exit" << endl;

                               cin >> siMenu;
                               switch(siMenu){
                                   case 1: {
                                   Eight *dd = (Eight*)p[choose];
                                   dd->ChangeChar();
                                   if(dd)
                                     cout << "Result: True";
                                    else
                                     cout << "Result: False";
                                       system("pause");
                                       break;
                                   }
                               }
                           } while (siMenu != 2);

                           system("cls");
                           break;
                       }
            }

        } while (mainMenu != 5);



    return 0;
}
