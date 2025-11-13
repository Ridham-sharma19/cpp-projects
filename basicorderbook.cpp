#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Order {
    string type;   //two types  "buy" or "sell"
    double price;
    int quantity;
};


class orderBook{

    public:
    vector<Order>buying;
    vector<Order>selling;


    //to make buy or sell order which will be stored in the in memeory vectors

    void makeOrder(Order currentOrder){
        if(currentOrder.type=="buy"){
             buying.push_back(currentOrder);
        }
        else if(currentOrder.type=="sell"){
            selling.push_back(currentOrder);
        }
        matchingOrders();
    }

    //now checking 
    void matchingOrders(){

        sort(buying.begin(), buying.end(), [](Order a, Order b) {
            return a.price > b.price;
        });

        sort(selling.begin(), selling.end(), [](Order a, Order b) {
            return a.price < b.price;
        });

        while (!buying.empty() && !selling.empty() &&
               buying[0].price >= selling[0].price) {

            int tradeQty = min(buying[0].quantity, selling[0].quantity);
            double tradePrice = selling[0].price; // trade happens at sell price

            cout << "Trade executed: " << tradeQty << " $ " << tradePrice << endl;

           
            buying[0].quantity -= tradeQty;
            selling[0].quantity -= tradeQty;

            // Remove completed orders
            if (buying[0].quantity == 0)
                buying.erase(buying.begin());
            if (selling[0].quantity == 0)
                selling.erase(selling.begin());
        }
    }
    
    // shows the current state of the buying and selling orders from the two respective vectores

     void showCurrentOrderBook() {
        cout << "\n#######----- BUY ORDERS ----########\n";
        for (auto &o : buying)
            cout << "Buy " << o.quantity << " $ " << o.price << endl;

        cout << "\n#######----- SELL ORDERS ----########\n";
        for (auto &o : selling)
            cout << "Sell " << o.quantity << " $ " << o.price << endl;
    }
};



int main(){
   
    orderBook ob;
    string type;
    double price;
    int quantity;

    while (true) {
        cout << "\nEnter order (type price quantity) or 'exit': ";
        cin >> type;
        if (type == "exit") break;
        cin >> price >> quantity;

        Order o = {type, price, quantity};
        ob.makeOrder(o);
        ob.showCurrentOrderBook();
    }
    return 0;
}
