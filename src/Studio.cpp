#include "../include/Studio.h"
//#include "../include/Action.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "algorithm"

Studio::Studio():open(false),id(0) {

}
Studio::Studio(const std::string &configFilePath):open(false),id(0)
{
    std::string configfilepath=configFilePath;// here we define the path to our desired data
    std::ifstream file(configfilepath);//here we save the whole text file as one string
    char line[500];
    bool i_am_empty_or_hashtag=true;
        file.getline(line,500);
        while(i_am_empty_or_hashtag) {
            if (line[0] == '#' || line[0] == '\0')// if there is a row that starts with # or and empty row
                file.getline(line,500);
            else
            {
                i_am_empty_or_hashtag=false;
            }
        }
        //first of all we are expecting to get number of trainers
        std::string numberoftrainers=line;
    numberoftrainers.erase(std::remove(numberoftrainers.begin(), numberoftrainers.end(), ' '), numberoftrainers.end());
    int numberoftrainerss=std::stoi(numberoftrainers);
    id=numberoftrainerss-1;

    file.getline(line,500);
    i_am_empty_or_hashtag=true;
    while(i_am_empty_or_hashtag) {
        if (line[0] == '#' || line[0]=='\0')// if there is a row that starts with # or and empty row
            file.getline(line,500);
        else
        {
            i_am_empty_or_hashtag=false;
        }
    }
     //now we want to fill our trainers with thier capacity,with row 4,5,6,5... and removing ',' or ' '(space)
        std::string capacity_of_trainers=line;
    capacity_of_trainers.erase(std::remove(capacity_of_trainers.begin(), capacity_of_trainers.end(), ' '), capacity_of_trainers.end());

        std::string currentcapacity;
        int size=static_cast<int>(capacity_of_trainers.size()); // i did cast because capacity_of_trainers.size() returns long type

        for(int currentindex=0;currentindex<size;currentindex++)
        {

            if(capacity_of_trainers.at(currentindex)==',')
            {
                trainers.push_back(new Trainer(std::stoi(currentcapacity)));
                currentcapacity="";

            }
            else
            {
                currentcapacity+=(capacity_of_trainers.at(currentindex));
            }
        }
    trainers.push_back(new Trainer(std::stoi(currentcapacity)));
    currentcapacity="";
    i_am_empty_or_hashtag=true;
    while(i_am_empty_or_hashtag) {
        if (line[0] == '#' || line[0] == '\0')// if there is a row that starts with # or and empty row
            file.getline(line, 500);
        else {
            i_am_empty_or_hashtag = false;
        }
    }
    //now we are expecting to get work options (thier id's is by order)
    std::string workout_option=line;
    workout_option.erase(std::remove(workout_option.begin(), workout_option.end(), ' '), workout_option.end());
    std::vector<std::string> array_of_strings;
    int i=0;
    while(!i_am_empty_or_hashtag)
    {
        int current_string_length=static_cast<int>(workout_option.size());
        std::string current_word;
        char current_char;
        while(i<current_string_length)
        {
            current_char = workout_option.at(i);
            if(current_char!=',')
            {
                current_word +=current_char;
                i++;
            }
            else
            {
                array_of_strings.push_back(current_word);
                i++;
            }

        }

        file.getline(line,500);
        workout_option=line;


        workout_option.erase(std::remove(workout_option.begin(), workout_option.end(), ' '), workout_option.end());

        if (line[0] == '#' || line[0] == '\0')// if there is a row that starts with # or and empty row
            i_am_empty_or_hashtag=true;
        i=0;
    }
    int number_of_workouts=static_cast<int>(array_of_strings.size())/3;
    int current_workout_id=0;
    int current_index=0;
    while(number_of_workouts>0)
    {
        int price=std::stoi(array_of_strings.at(current_index+2));
        WorkoutType worktype;

        if(array_of_strings.at(current_index+1)=="anaerobic")
        {
            worktype=ANAEROBIC;
        }
        else
        {
            if(array_of_strings.at(current_index+1)=="mixed")
            {
                worktype=MIXED;
            }
            else
            {
                worktype=CARDIO;
            }
        }
        this->workout_options.push_back(Workout(current_workout_id,array_of_strings.at(current_index),price,worktype));
        current_index=current_index+3;
        current_workout_id=current_workout_id+1;
        number_of_workouts=number_of_workouts-1;
    }
    }

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ we did act 2 times once in start and once in buildaction
void Studio::start()
{
    std::cout<<"studio is now open"<<std::endl;
    this->open=true;
    char command[500];
    while(true)
    {
      std::cin.getline(command,500);// the input that a person types when software is running
        BaseAction* act=buildAction(command);//we must implement buildaction
      this->actionsLog.push_back(act);
        //std::cout<<"wtf   "<<std::endl;
      act->act(*this);
      std::string commandString=command;
      if(commandString=="closeall") {
          this->open=false;
          break;
      }
      //this loop will stop only when there is an order close all, we decide how to do it
    }
}

BaseAction* Studio::buildAction(char command[]) {
    std::string line = command;
        int index = 0;
    std::string actionType;
    while (line.at(index) != ' ') {
        actionType += line.at(index);
        index++;
    }
    int linesize=line.size();
    index++;
    if (actionType == "open" || actionType == "Open") {
        while (line.at(index) == ' ') {
            index++;
        }
        std::string trainerId;
        while (line.at(index) != ' ') {
            trainerId += line.at(index);
            index++;
        }
        int id = std::stoi(trainerId);

        std::vector<Customer *> customersList;

        while (index<linesize && line.at(index) != '\0') {

            while (line.at(index) == ' ') {
                index++;
            }
            std::string customerName;
            while (line.at(index) != ',') {
                customerName += line.at(index);
                index++;
            }
            std::string customerType;
            index++;
            while (index<linesize && line.at(index) != ' ') {
                customerType += line.at(index);
                index++;
            }
            Customer *customerToInsert;
            if (customerType=="swt")
                customerToInsert = new SweatyCustomer(customerName, id);
            if (customerType=="chp")
                customerToInsert = new CheapCustomer(customerName, id);
            if (customerType=="mcl")
                customerToInsert = new HeavyMuscleCustomer(customerName, id);
            if (customerType=="fbd")
                customerToInsert = new FullBodyCustomer(customerName, id);

            id++;

            customersList.push_back(customerToInsert);
        }
        std::cout<<"customer list size supsoted to be 4 "<<customersList.size()<<std::endl;
        OpenTrainer* openTrainer=new OpenTrainer(std::stoi(trainerId), customersList);
        return openTrainer;

    }
    if (actionType == "order" || actionType == "Order") {
        std::string trainerId;

        while (index<linesize && line.at(index) != ' ') {
            trainerId += line.at(index);
            index++;
        }
        Order* order=new Order(std::stoi(trainerId));
        return order;

    }
    if (actionType == "close" || actionType == "Close") {
        std::string trainerId;
        while (line.at(index) != ' ') {
            trainerId += line.at(index);
            index++;
        }
        Close* close=new Close(std::stoi(trainerId));
        return close;
       // close.act(*this);
    }
    if (actionType == "move" || actionType == "Move") {
        std::string srcTrainerId;
        std::string dstTrainerId;
        std::string customerId;
        while (line.at(index) != ' ') {
            srcTrainerId += line.at(index);
            index++;
        }
        while (line.at(index) == ' ') {
            index++;
        }
        while (line.at(index) != ' ') {
            dstTrainerId += line.at(index);
            index++;
        }
        while (line.at(index) == ' ') {
            index++;
        }
        while (line.at(index) != ' ') {
            customerId += line.at(index);
            index++;
        }
        MoveCustomer* moveCustomer=new MoveCustomer(std::stoi(srcTrainerId), std::stoi(dstTrainerId), std::stoi(customerId));
        return moveCustomer;
      //  moveCustomer.act(*this);
    }
    if (actionType == "closeall" || actionType == "CloseAll" || actionType == "Closeall") {

        CloseAll* closeAll=new CloseAll();
        return closeAll;

       // return reinterpret_cast<BaseAction *>(&closeAll);

    }
    if(actionType=="workout_options")
    {
      PrintWorkoutOptions* printworkouts=new PrintWorkoutOptions();
        return printworkouts;
    }



    if(actionType=="status")
    {
        std::string trainerid;
        index=index+1;
        while(line.at(index)!=' ')
        {
            trainerid+=line.at(index);
            index=index+1;
        }

        PrintTrainerStatus* printtrainerstatus=new PrintTrainerStatus(std::stoi(trainerid));
        return printtrainerstatus;
     //   printtrainerstatus.act(*this);
    }


    if(actionType=="log")
    {
        PrintActionsLog* print=new PrintActionsLog();
        return print;
        //print.act(*this);
    }


    if(actionType=="backup")
    {
        BackupStudio* backup=new BackupStudio();
        return backup;
       // backup.act(*this);
    }

    if(actionType=="restore")
    {
        RestoreStudio* restore=new RestoreStudio();
        return restore;
       // restore.act(*this);
    }

    return nullptr;

}

Trainer *Studio::getTrainer(int tid) {

    int mysize=static_cast<int>(this->trainers.size());
    if(mysize>tid)
    {
        std::cout<<"before levaing studio my customers are "<<this->trainers.at(tid)->getCustomers().size()<<std::endl;
        return this->trainers.at(tid);
    }
    return nullptr;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return this->workout_options;
}



Studio::~Studio() {
    this->workout_options.clear();
    for(auto & trainer : this->trainers)
    {
        delete trainer;
    }
    this->trainers.clear();
    for(auto & iter : this->actionsLog)
    {
        delete iter;
    }
    this->actionsLog.clear();
}

Studio::Studio(const Studio &other) {
    this->open=other.open;
    this->id=other.id;
    for(auto trainer : other.trainers)
    {
        this->trainers.push_back(trainer);
    }
    for(auto iter : other.actionsLog)
    {
        this->actionsLog.push_back(iter);
    }
    for(const auto & workout_option : other.workout_options)
    {
        Workout workoutcopy(workout_option.getId(),workout_option.getName(),workout_option.getPrice(),workout_option.getType());
        this->workout_options.push_back(workoutcopy);
    }
   // this->workout_options=other.workout_options;
}

Studio::Studio(Studio &&other) {
    this->open=other.open;
    this->id=other.id;
    for(auto & trainer : other.trainers)
    {
        this->trainers.push_back(trainer);
    }
    for(auto & iter : other.actionsLog)
    {
        this->actionsLog.push_back(iter);
    }
    this->workout_options=std::move(other.workout_options);
    other.trainers.clear();
    other.actionsLog.clear();
}

Studio &Studio::operator=(const Studio &other) {

    if(this!=&other) {
        delete this;
        for (auto trainer : other.trainers) {
            this->trainers.push_back(trainer);
        }
        for (auto iter : other.actionsLog) {
            this->actionsLog.push_back(iter);
        }
        for(const auto & workout_option : other.workout_options)
        {
            Workout workoutcopy(workout_option.getId(),workout_option.getName(),workout_option.getPrice(),workout_option.getType());
            this->workout_options.push_back(workoutcopy);
        }

        //this->workout_options = other.workout_options;
        this->open = other.open;
        this->id=other.id;
    }
    return *this;
}

Studio &Studio::operator=(Studio &&other) {
    if(this!=&other)
    {
        for (auto & trainer : other.trainers) {
            this->trainers.push_back(trainer);
        }
        for (auto & iter : other.actionsLog) {
            this->actionsLog.push_back(iter);
        }
        this->id=other.id;
        this->workout_options = std::move(other.workout_options);
        this->open = other.open;
    }
    other.trainers.clear();
    other.actionsLog.clear();

    return *this;

}

int Studio::getNumOfTrainers() const {
    return static_cast<int>(this->trainers.size());
}

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return this->actionsLog;
}

std::vector<Trainer *> Studio::getTrainers() {
    return this->trainers;
}

