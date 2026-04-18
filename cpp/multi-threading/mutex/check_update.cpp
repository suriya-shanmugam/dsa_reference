#include <iostream>
#include <thread>

class Account {
    private:
        int balance;
        std::mutex balMutex;
    public :
        Account(int amount):balance(amount){}

        void withDraw(int amount){
            std::lock_guard<std::mutex> lock(balMutex);
            if (balance >= amount){
                std::this_thread::sleep_for(std::chrono::seconds(2));
                balance -= amount;
                std::cout << "Withdrawl success " << " current balance " << balance << std::endl;
            }else{
                std::cout << "Insufficient balance " << " current balance " << balance << " requested amount " << amount << std::endl;
            }
        }
        void printBalance(){
            std::cout << balance << std::endl;
        }
};

int main(){
    Account a(1000);
    std::thread t1(&Account::withDraw, &a, 1000);
    std::thread t2(&Account::withDraw, &a, 1000);
    
    t1.join();
    t2.join();
    
    a.printBalance();
    return 0;
}