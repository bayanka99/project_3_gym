#include "../include/Trainer.h"
#include <algorithm>
Trainer::Trainer(int t_capacity) {
    capacity=t_capacity;
    open= false;

}


int Trainer::getCapacity() const {
    return capacity;
}

void Trainer::addCustomer(Customer *customer) {


    if(static_cast<int>(customersList.size())<capacity)
        customersList.push_back(customer);
}

void Trainer::removeCustomer(int id) {
    for(auto iter=customersList.begin();iter!=customersList.end();iter++){
        if((*iter)->getId()==id){
            delete *iter;
            customersList.erase(iter);
        }
    }
    std::vector<OrderPair> neworderlist;
    for(auto order:this->orderList)
    {
        if(order.first!=id)
        {
            neworderlist.push_back(order);
        }
    }

    this->orderList=std::move(neworderlist);


}

Customer *Trainer::getCustomer(int id) {
    std::vector<Customer*>::iterator iter;
    for(iter=customersList.begin();iter!=customersList.end();iter++){
        if((*iter)->getId()==id)
            return *iter;
    }
    return nullptr;//check if we need to return something else if we don't find the customers in the list
}

std::vector<Customer *> &Trainer::getCustomers() {
    std::cout<<"my size when getcustoemrs is "<<this->customersList.size()<<std::endl;

    return this->customersList;
}

std::vector<OrderPair> &Trainer::getOrders() {
    return  orderList;
}

void
Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for(auto iter=workout_options.begin();iter!=workout_options.end();iter++){
        if(*std::find(workout_ids.begin(),workout_ids.end(),(*iter).getId())==(*iter).getId()){
            OrderPair pair= OrderPair(customer_id,*iter);
            orderList.push_back(pair);
            std::cout<<getCustomer(customer_id)->getId()<<" Is Doing "<<(*iter).getName()<<std::endl;
        }
    }
}

void Trainer::openTrainer() {
    open= true;
}

void Trainer::closeTrainer() {
    open= false;
}

int Trainer::getSalary() {
    int salary=0;
    for(auto iter=orderList.begin();iter!=orderList.end();iter++){
        salary+=iter->second.getPrice();
    }
    return salary;
}

bool Trainer::isOpen() {
    return open;
}

Trainer::~Trainer() {
    for(auto iter=customersList.begin();iter!=customersList.end();iter++){
        delete *iter;
    }
    customersList.clear();
    orderList.clear();
}

Trainer::Trainer(const Trainer &other):capacity(other.capacity),open(other.open),orderList(other.orderList)
{
    for(auto iter=other.customersList.begin();iter!=other.customersList.end();iter++){
        Customer* customer((*iter)->clone());
        customersList.push_back(customer);
    }
}

Trainer::Trainer(Trainer &&other): capacity(other.getCapacity()), open(other.open){
    //other.capacity=0;
    //other.open= false;
    orderList=std::move(other.orderList);
    customersList=std::move(other.customersList);
}

Trainer &Trainer::operator=(const Trainer& other) {
    if(this!=&other){
        delete this;
        capacity=other.capacity;
        open=other.open;
        for(auto iter=other.orderList.begin();iter!=other.orderList.end();iter++)
        {
            OrderPair ordercopy(iter->first,iter->second);
            this->orderList.push_back(ordercopy);
        }
      //  orderList=other.orderList;
        for(auto iter=other.customersList.begin();iter!=other.customersList.end();iter++) {
            Customer *customer((*iter)->clone());
            customersList.push_back(customer);
        }
    }
    return  *this;
}

Trainer &Trainer::operator=(Trainer &&other) {
    if(this!=&other){
        delete this;
        capacity=other.capacity;
        open=other.open;
        orderList=std::move(other.orderList);
        customersList=std::move(other.customersList);
        //other.capacity=0;
        //other.open= false;
    }
    return *this;
}



