#include <iostream>
#include "/home/user1/work/tools/aiger/aiger.h"
#include <string.h>
#include <fstream>
#include <assert.h>

using namespace std;

unsigned lit2ind_old(aiger* model, unsigned lit){ //Note: Outputs indexes don't match this rule. For them, use simple search
    unsigned q = aiger_lit2var(lit) - 1;
    switch(aiger_lit2tag(model, lit)){
        case 0:
        case 1:{ //Working with constant(0) or input(1) format
            return q;
            break;
        }
        case 2:{ //Working with latch(2) format
            return q - model->num_inputs;
            break;
        }
        case 3:{ //Working with and(3) format
            return q - model->num_inputs - model->num_latches;
            break;
        }
        default:{ //aiger_lit2tag can't return any valuable exept 0,1,2 or 3
            exit(1);
        }
    } 
}

unsigned lit2ind(aiger* model, unsigned lit){ //Note: Outputs indexes don't match this rule. For them, use simple search
    return aiger_get_ind(model, lit);
}


unsigned lit2ind_independant(aiger* model, unsigned lit){
    return 0;
}

void info_model(aiger* model){//Show basic information about aiger model
    printf("------------------------------\n");
    printf("maxvar: %d\n", model->maxvar);
    printf("IN: %d\n", model->num_inputs); //model->inputs
    for (int i=0; i<model->num_inputs; i++){
        printf("\tlit: %d | %d | %d | %d  name: %s\n", model->inputs[i].lit, 
                                            aiger_lit2var(model->inputs[i].lit), 
                                            aiger_lit2tag(model, model->inputs[i].lit),
                                            lit2ind(model, model->inputs[i].lit),
                                            model->inputs[i].name);
    }
    printf("LAT: %d\n", model->num_latches);  //model->latches
    for (int i=0; i<model->num_latches; i++){
        printf("\tlit: %d | %d | %d | %d   name: %s   next: %d | %d | %d | %d   reset: %d\n", model->latches[i].lit, 
                                                                        aiger_lit2var(model->latches[i].lit),
                                                                        aiger_lit2tag(model, model->latches[i].lit),
                                                                        lit2ind(model, model->latches[i].lit),
                                                                        model->latches[i].name,
                                                                        model->latches[i].next,
                                                                        aiger_lit2var(model->latches[i].next),
                                                                        aiger_lit2tag(model, model->latches[i].next),
                                                                        lit2ind(model, model->latches[i].next),
                                                                        model->latches[i].reset);
    }
    printf("OUT: %d\n", model->num_outputs);  //model->outputs
    for (int i=0; i<model->num_outputs; i++){
        printf("\tlit: %d | %d | %d | %d   name: %s\n", model->outputs[i].lit,
                                                aiger_lit2var(model->outputs[i].lit),
                                                aiger_lit2tag(model, model->outputs[i].lit),
                                                lit2ind(model, model->outputs[i].lit),
                                                model->outputs[i].name);
    }
    printf("AND: %d\n", model->num_ands);  //model->ands
    for (int i=0; i<model->num_ands; i++){
        printf("\tlhs: %d | %d | %d | %d   rhs0: %d | %d | %d | %d   rhs1: %d | %d | %d | %d\n", model->ands[i].lhs,
                                                                    aiger_lit2var(model->ands[i].lhs),
                                                                    aiger_lit2tag(model, model->ands[i].lhs),
                                                                    lit2ind(model, model->ands[i].lhs),
                                                                    model->ands[i].rhs0,
                                                                    aiger_lit2var(model->ands[i].rhs0),
                                                                    aiger_lit2tag(model, model->ands[i].rhs0),
                                                                    lit2ind(model, model->ands[i].rhs0),
                                                                    model->ands[i].rhs1,
                                                                    aiger_lit2var(model->ands[i].rhs1),
                                                                    aiger_lit2tag(model, model->ands[i].rhs1),
                                                                    lit2ind(model, model->ands[i].rhs1));
    }
    printf("------------------------------\n");
    printf("BAD: %d\n", model->num_bad); //model->bad
    for (int i=0; i<model->num_bad; i++){
        printf("\tlit: %d | %d | %d | %d   name: %s\n", model->bad[i].lit,
                                                aiger_lit2var(model->bad[i].lit),
                                                aiger_lit2tag(model, model->bad[i].lit),
                                                lit2ind(model, model->bad[i].lit),
                                                model->bad[i].name);
    }
    printf("CON: %d\n", model->num_constraints); //model->constraint
    for (int i=0; i<model->num_constraints; i++){
        printf("\tlit: %d | %d | %d | %d   name: %s\n", model->constraints[i].lit,
                                                aiger_lit2var(model->constraints[i].lit),
                                                aiger_lit2tag(model, model->constraints[i].lit),
                                                lit2ind(model, model->constraints[i].lit),
                                                model->constraints[i].name);
    }
    printf("FAIR: %d\n", model->num_fairness); //model->num_fairness
    for (int i=0; i<model->num_fairness; i++){
        printf("\tlit: %d | %d | %d | %d   name: %s\n", model->fairness[i].lit,
                                                aiger_lit2var(model->fairness[i].lit),
                                                aiger_lit2tag(model, model->fairness[i].lit),
                                                lit2ind(model, model->fairness[i].lit),
                                                model->fairness[i].name);
    }
    printf("------------------------------\n");
}
void check_ind(aiger* model){//Show basic information about aiger model
    printf("------------------------------\n");
    printf("maxvar: %d\n", model->maxvar);
    printf("IN: %d\n", model->num_inputs); //model->inputs
    for (int i=0; i<model->num_inputs; i++){
        printf("\tlit: %d | %d  name: %s CHECK:%d\n", model->inputs[i].lit, 
                                            lit2ind(model, model->inputs[i].lit),
                                            model->inputs[i].name,
                                            (i == lit2ind(model, model->inputs[i].lit)));
    }
    printf("LAT: %d\n", model->num_latches);  //model->latches
    for (int i=0; i<model->num_latches; i++){
        printf("\tlit: %d | %d   name: %s   next: %d | %d   reset: %d CHECK:%d\n", model->latches[i].lit, 
                                                                        lit2ind(model, model->latches[i].lit),
                                                                        model->latches[i].name,
                                                                        model->latches[i].next,
                                                                        lit2ind(model, model->latches[i].next),
                                                                        model->latches[i].reset,
                                                                        (i == lit2ind(model, model->latches[i].lit)));
    }
    printf("OUT: %d\n", model->num_outputs);  //model->outputs
    for (int i=0; i<model->num_outputs; i++){
        printf("\tlit: %d   name: %s\n", model->outputs[i].lit,
                                                model->outputs[i].name);
    }
    printf("AND: %d\n", model->num_ands);  //model->ands
    for (int i=0; i<model->num_ands; i++){
        printf("\tlhs: %d | %d   rhs0: %d | %d   rhs1: %d | %d CHECK:%d\n", model->ands[i].lhs,
                                                                    lit2ind(model, model->ands[i].lhs),
                                                                    model->ands[i].rhs0,
                                                                    lit2ind(model, model->ands[i].rhs0),
                                                                    model->ands[i].rhs1,
                                                                    lit2ind(model, model->ands[i].rhs1),
                                                                    (i == lit2ind(model, model->ands[i].lhs)));
    }
    printf("------------------------------\n");
    printf("BAD: %d\n", model->num_bad); //model->bad
    for (int i=0; i<model->num_bad; i++){
        printf("\tlit: %d | %d   name: %s CHECK:%d\n", model->bad[i].lit,
                                                lit2ind(model, model->bad[i].lit),
                                                model->bad[i].name,
                                                (i == lit2ind(model, model->bad[i].lit)));
    }
    printf("CON: %d\n", model->num_constraints); //model->constraint
    for (int i=0; i<model->num_constraints; i++){
        printf("\tlit: %d | %d   name: %s CHECK:%d\n", model->constraints[i].lit,
                                                lit2ind(model, model->constraints[i].lit),
                                                model->constraints[i].name,
                                                (i == lit2ind(model, model->constraints[i].lit)));
    }
    printf("FAIR: %d\n", model->num_fairness); //model->num_fairness
    for (int i=0; i<model->num_fairness; i++){
        printf("\tlit: %d | %d   name: %s CHECK:%d\n", model->fairness[i].lit,
                                                lit2ind(model, model->fairness[i].lit),
                                                model->fairness[i].name,
                                                (i == lit2ind(model, model->fairness[i].lit)));
    }
    printf("------------------------------\n");
}
/*
void bfs_model(aiger* model, unsigned lit){
    queue<unsigned> to_go; //Queue with lits of verces, to that go
    to_go.push(lit);
    while(!(to_go.empty())){
        printf("1");
    }
}
*/
void read_and_print_file(const char * inp){
    FILE *file;
    file = fopen(inp, "r"); //Input file
    aiger* model = aiger_init(); //Initilase model
    aiger_read_from_file(model, file); //Read aiger from file
    printf("Model info:\n");
    info_model(model);
}
void read_and_check_ind(const char * inp){
    FILE *file;
    file = fopen(inp, "r"); //Input file
    aiger* model = aiger_init(); //Initilase model
    aiger_read_from_file(model, file); //Read aiger from file
    printf("Model info:\n");
    check_ind(model);
}
int test_work_with_file(){
    //  input/and.aig

    FILE *file, *out;
    file = fopen("/home/user1/work/tools/aiger/input/and.aig", "r"); //Input file
    out = fopen("/home/user1/work/tools/aiger/output/out.aig", "w"); //File to output
    aiger* model = aiger_init(); //Initilase model
    printf("Model BEFORE reading input file:\n");
    info_model(model);
    aiger_read_from_file(model, file); //Read aiger from file
    printf("Model AFTER reading input file:\n");
    info_model(model);
    aiger_write_to_file(model, aiger_mode(1), out); //Write aiger to file
    return 0;
}

int test(){
    FILE *file, *out;
    file = fopen("input/and.aig", "r"); //Input file
    out = fopen("output/out.aig", "w"); //File to output
    aiger* model = aiger_init(); //Initilase model
    aiger_read_from_file(model, file);
    info_model(model);

    printf("\n%s %d %d\n", aiger_get_symbol(model, 14), aiger_lit2tag(model, 14), aiger_lit2var(14));
    return 0;
}
void test_all_aiger_tests(){
    string tests[16] = {"and.aag", "buffer.aag",  "cnt1.aag",  "cnt1e.aag",  "empty.aag",  "false.aag",  "halfadder.aag",  "inverter.aag",  "notcnt1.aag",  "notcnt1e.aag",  "or.aag",  "toggle.aag",  "toggle-re.aag",  "true.aag" , "xor1.aag", "xorxormiter.aag"};
    ifstream myfile;
    string middle_data;
    for(auto test_file: tests){
        cout<<("\n\033[1;31mInfo in model: "+ test_file+"\033[0;0m\n");
        read_and_check_ind(("/home/user1/work/aiger_tests/aiger_test_files/"+test_file).c_str());
        myfile.open("/home/user1/work/aiger_tests/aiger_test_files/"+test_file);
        cout<<("\n\033[1;35mInfo in file: "+ test_file+"\033[0;0m\n");
        while (getline (myfile, middle_data)) {
            cout << middle_data << endl;
        }
        myfile.close();
    }
}
int main(){
    cout<<("\n\033[1;327mQQQQQQQQ\033[0;0m\nQQQQQQQQ\n");
    return 0;
}