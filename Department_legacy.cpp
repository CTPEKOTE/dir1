#include <iostream>
#include <vector>

using namespace std;
string NoDepartment(string err){
    cout << err << endl;
};
class Department {//impossible to create object of abstract class because of func = 0
protected:
    int threshold[3];
    virtual string GetValue() = 0;

public:
    virtual string DepartmentName() = 0;
    Department(){

    };

    ~Department(){

    };

    bool IsEnoughScores(int math, int phys, int rus){
        if(math > threshold[0] && phys > threshold[1] && rus > threshold[2]){
            return 1;
        }
        else return 0;
    }
    void Say() {
        cout << GetValue() << endl;
    }
};

class DPQE : public Department {
private:
    string GetValue() override {
        return "My boleem za kvanty potomu chto my kvanty";
    }
public:
    string DepartmentName() override {
        return "DPQE";
    }
  
    DPQE(){
        threshold[0] = 60;
        threshold[1] = 60;
        threshold[2] = 60;
    };
};

class DPBM : public Department {
private: 
    string GetValue() override {
        return "Zdes' doljen byt' hymn bmov";
    }
public:
    string DepartmentName() override {
        return "DPBM";
    }

    DPBM(){
        threshold[0] = 50;
        threshold[1] = 50;
        threshold[2] = 50;
    };
};

class DMCP : public Department {
private:
    string GetValue() override {
        return "Zdes' doljen byt' hymn hfov";
    }
public:
    string DepartmentName() override {
        return "DMCP";
    }

    DMCP(){
        threshold[0] = 55;
        threshold[1] = 55;
        threshold[2] = 55;
    };
};

Department* GetDepartment (const string& a){
    if (a == "DPQE"){
        return new DPQE;
    } else if(a == "DPBM"){
        return new DPBM;
    } else if(a == "DMCP"){
        return new DMCP;
    } else {
        throw NoDepartment("No such Department");
    }
}

int main() {
    Department *Temp1 = GetDepartment("DPQE"), *Temp2 = GetDepartment("DPBM"), *Temp3 = GetDepartment("DMCP");
    vector <Department*> v;
    int math, phys, rus;
    cin >> math >> phys >> rus;
    if(Temp1->IsEnoughScores(math, phys, rus)){
        v.push_back(Temp1);
    }
    if(Temp2->IsEnoughScores(math, phys, rus)){
        v.push_back(Temp2);
    }
    if(Temp3->IsEnoughScores(math, phys, rus)){
        v.push_back(Temp3);
    }
    cout << "You can attend:" << endl;
    for (unsigned int i = 0; i < v.size(); i++){
        cout << i << ") " << v[i]->DepartmentName() << endl;
    }
    cout << "Enter your choice" << endl;
    int otv;
    cin >> otv;
    v[otv]->Say();
    return 0;
}