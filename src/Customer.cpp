#include <algorithm>
#include "../include/Customer.h"

Customer::Customer(std::string c_name, int c_id):name(c_name),id(c_id) {

}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

bool compareWorkouts(Workout&  w1, Workout&  w2){
    return w1.getPrice() < w2.getPrice();
}



SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> orderList;
    for(auto iter=workout_options.begin();iter!=workout_options.end();iter++){
        if(iter->getType()==CARDIO){
            orderList.push_back(iter->getId());
        }
    }
    return  orderList;
}

std::string SweatyCustomer::toString() const {
    std::string returnVal=getName()+",swt";
    return  returnVal;
}

Customer *SweatyCustomer::clone() const {
    return new SweatyCustomer(getName(),getId());
}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> orderList;
    int minPrice=workout_options.begin()->getPrice();
    int minId=workout_options.begin()->getId();
    for(auto iter=workout_options.begin();iter!=workout_options.end();iter++){
        if(iter->getPrice()<minPrice){
            minPrice=iter->getPrice();
            minId=iter->getId();
        }
    }
    orderList.push_back(minId);
    return orderList;
}

std::string CheapCustomer::toString() const {
    std::string returnVal=getName()+", chp";
    return  returnVal;
}

Customer *CheapCustomer::clone() const{
    return new CheapCustomer(getName(),getId());
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}
//
//std::vector<Workout> sortme_bigfirst(std::vector<Workout> workouts)
//{
//
//    std::vector<Workout> sorted;
//    int current_max_price;
//    int current_index;
//    int current_price;
//    int current_max_index=0;
//    int loop=workouts.size();
//    while(loop>0)
//    {
//       current_max_price=workouts.at(0).getPrice();
//        for(Workout work:workouts)
//        {
//            current_index++;
//            current_price=work.getPrice();
//            if(current_max_price<current_price)
//            {
//                current_max_price=current_price;
//                current_max_index=current_index;
//            }
//        }
//        sorted.push_back(workouts.at(current_max_index));
//        workouts.at(current_max_index);//deletes workout at index current_max_index
//        loop--;
//        current_max_index=0;
//        current_index=0;
//    }
//return sorted;
//}

std::vector<std::pair<int,int>> sortme(std::vector<std::pair<int,int>> pricesandid)
{
    std::sort(pricesandid.begin(),pricesandid.end());
    return pricesandid;
}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> ordersList;
   std::vector<Workout> workoutOptionsSorted;
   std::vector<std::pair<int,int>> prices_and_id;
    for(auto iter=workout_options.begin();iter!=workout_options.end();iter++){
        if(iter->getType()==ANAEROBIC){
            int id=static_cast<const int>(iter->getId());
            int price=static_cast<const int>(iter->getPrice());
            prices_and_id.push_back(std::pair<int,int>(price,id));
        }
    }
    prices_and_id= sortme(prices_and_id);
    for(auto p: prices_and_id)
    {
        ordersList.push_back(p.second);
    }

    return  ordersList;

}

std::string HeavyMuscleCustomer::toString() const {
    std::string returnVal=getName()+",mcl";
    return  returnVal;
}

Customer *HeavyMuscleCustomer::clone() const{
    return new HeavyMuscleCustomer(getName(),getId());
}



FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<std::pair<int,int>> cardioList;
    std:: vector<std::pair<int,int>> mixedList;
    std:: vector<std::pair<int,int>> anaerobicList;

  for(auto iter=workout_options.begin();iter!=workout_options.end();iter++){
      int id=static_cast<const int>(iter->getId());
      int price=static_cast<const int>(iter->getPrice());
       if(iter->getType()==ANAEROBIC){
           anaerobicList.push_back(std::pair<int,int>(price,id));
        } else{
            if(iter->getType()==MIXED)
                mixedList.push_back(std::pair<int,int>(price,id));
            else
                cardioList.push_back(std::pair<int,int>(price,id));
        }
    }
   std::vector<int> ordersList;
  std::sort(cardioList.begin(),cardioList.end());
    std::sort(mixedList.begin(),mixedList.end());
    std::sort(anaerobicList.begin(),anaerobicList.end());
    ordersList.push_back((cardioList.at(cardioList.size()-1)).first);//min
    ordersList.push_back(mixedList.at(0).first);//max
    ordersList.push_back((anaerobicList.at(anaerobicList.size()-1)).first);//min

    return  ordersList;
}

std::string FullBodyCustomer::toString() const {
    std::string returnVal=getName()+",fbd";
    return  returnVal;
}

Customer *FullBodyCustomer::clone() const {
    return new FullBodyCustomer(getName(),getId());
}

bool compareWorkouts::operator()(const Workout &w1, const Workout &w2) {
    return w1.getPrice()<=w2.getPrice();
}
