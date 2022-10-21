#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "../include/Workout.h"
#include "../include/Trainer.h"
#include "../include/Action.h"





class Studio{		
public:
	Studio();
    Studio(const std::string &configFilePath);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
    std::vector<Trainer*> getTrainers();//check if I can add getter for trainers list. If not, use the destructor of studio
    BaseAction* buildAction(char command[]);
    ~Studio();
    Studio(const Studio &other);//copy constructor
    Studio(Studio &&other);//move constructor
    Studio& operator=(const Studio &other);//copy assigment
    Studio& operator=(Studio &&other);//move assigment
private:
    bool open;
    int id;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
};

#endif