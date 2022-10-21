#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "../include/Customer.h"


enum ActionStatus{
    COMPLETED, ERROR
};

//Forward declaration
class Studio;



class BaseAction{
public:
    BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Studio& studio)=0;
    virtual std::string toString() const=0;
    virtual BaseAction* clone() const=0;
    virtual ~BaseAction()=default;
protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;

private:
    std::string errorMsg;
    ActionStatus status;

};


class OpenTrainer : public BaseAction {
public:
    OpenTrainer(int id, std::vector<Customer *> &customersList);
    void act(Studio &studio) override;
    std::string toString() const override;
    BaseAction* clone() const override;
    ~OpenTrainer()override=default;
private:
	const int trainerId;
	std::vector<Customer *> customers;
};


class Order : public BaseAction {
public:
    Order(int id);
    void act(Studio &studio)override;
    std::string toString() const override;
    BaseAction* clone() const override;
    ~Order()override=default;
private:
    const int trainerId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    void act(Studio &studio)override;
    std::string toString() const override;
    BaseAction* clone() const override;
    ~MoveCustomer()override=default;
private:
    const int srcTrainer;
    const int dstTrainer;
    const int id;
};


class Close : public BaseAction {
public:
    Close(int id);
    void act(Studio &studio) override;
    std::string toString() const override;
    BaseAction* clone() const override;
    ~Close()override=default;
private:
    const int trainerId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    void act(Studio &studio) override;
    std::string toString() const override;
    BaseAction* clone() const override;
    ~CloseAll()override=default;
private:
};


class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions();
    void act(Studio &studio)override;
    std::string toString() const override;
    BaseAction* clone() const override;
    ~PrintWorkoutOptions()override=default;
private:
};


class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
    void act(Studio &studio) override;
    std::string toString() const override;
    BaseAction* clone() const override;
    ~PrintTrainerStatus()override=default;
private:
    const int trainerId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    void act(Studio &studio)override;
    std::string toString() const override;
    BaseAction* clone() const override;
    ~PrintActionsLog()override=default;
private:
};


class BackupStudio : public BaseAction {
public:
    BackupStudio();
    void act(Studio &studio)override;
    std::string toString() const override;
    BaseAction* clone() const override;
    ~BackupStudio()override=default;
private:
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio();
    void act(Studio &studio)override;
    std::string toString() const override;
    BaseAction* clone() const override;
    ~RestoreStudio()override=default;
};


#endif