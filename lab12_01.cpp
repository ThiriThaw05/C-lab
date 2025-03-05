#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Book{
protected:
    string bookId;
    double baseFineRate;
public:
    Book(string id, double rate) : bookId(id), baseFineRate(rate){}
    virtual double calculateFine(int daysOverdue)const = 0;
    virtual void displayInfo()const{
        cout<<" (ID: "<<bookId<<")"<<endl;
        cout<<"Base Fine Rate: $ "<<baseFineRate<<endl;
    };
    virtual ~Book(){};
};

class TextBook : public Book{
private:
    string subject;
public:
    using Book::Book;
    TextBook(string id, double rate, string sub) : Book(id,rate),subject(sub){}
    double calculateFine(int daysOverdue)const override{
        return baseFineRate + (0.50*daysOverdue);
    }
    void displayInfo()const override{
        cout<<"TextBook";
        Book::displayInfo();
        cout<<"Subject: "<<subject<<endl;
    }
};

class Novel : public Book{
private:
    string genre;
public:
    Novel(string id, double rate, string gen) : Book(id,rate),genre(gen){}
    double calculateFine(int daysOverdue)const override{
        return baseFineRate + (0.20*daysOverdue);
    }
    void displayInfo()const override{
        cout<<"Novel";
        Book::displayInfo();
        cout<<"Genre: "<<genre<<endl;
    }
};

int main(){
    vector<Book*> books;
    books.push_back(new TextBook("T001",1,"Physics"));
    books.push_back(new Novel("N001",0.5,"Mystery"));
    for (auto book : books){
        book->displayInfo();
        cout<<"Fine for 5 days overdue: $ "<<book->calculateFine(5)<<endl;
        cout<<"-------------------------"<<endl;
    }
}