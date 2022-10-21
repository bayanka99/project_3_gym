//
// Created by idanl on 15/11/2021.
//

#include "../include/Workout.h"

Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):id(w_id),name(w_name),price(w_price),type(w_type) {

}

int Workout::getId() const {
    return id;
}

std::string Workout::getName() const {
    return name;
}

int Workout::getPrice() const {
    return price;
}

WorkoutType Workout::getType() const {
    return type;
}

std::string Workout::Tostring() {
    std::string me_in_string;
    me_in_string += this->name;
    me_in_string += " , ";
    me_in_string += this->type;
    me_in_string += " , ";
    me_in_string += this->price;

    return std::string();
}

//Workout::Workout(const Workout &&workout):id(static_cast<const int>(workout.getId())),name(static_cast<const std::string>(workout.getName())),price(static_cast<const int>(workout.getPrice())),type(static_cast<const WorkoutType>(workout.getType())){
//
//
//}
//
