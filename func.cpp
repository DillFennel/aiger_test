#include <iostream>
#include <stdio.h>
#include "aiger.h"

using namespace std;

unsigned get_ind(aiger* model, unsigned lit){
    unsigned q = aiger_lit2var(lit);
    switch(aiger_lit2tag(model, lit)){
        case 0:{
            return q;
            break;
        }
        case 1:{
            return q;
            break;
        }
        case 2:{
            return q - model->num_inputs;
            break;
        }
        case 3:{
            return q - model->num_inputs - model->num_latches;
            break;
        }
        default:{
            exit(1);
        }
    } 
}
void info_model(aiger* model){//Show basic information about aiger model
    printf("------------------------------\n");
    printf("maxvar: %d\n", model->maxvar);
    printf("IN: %d\n", model->num_inputs); //model->inputs
    for (int i=0; i<model->num_inputs; i++){
        printf("\tlit: %d | %d | %d | %d  name: %s\n", model->inputs[i].lit, 
                                            aiger_lit2var(model->inputs[i].lit), 
                                            aiger_lit2tag(model, model->inputs[i].lit),
                                            get_ind(model, model->inputs[i].lit),
                                            model->inputs[i].name);
    }
    printf("LAT: %d\n", model->num_latches);  //model->latches
    for (int i=0; i<model->num_latches; i++){
        printf("\tlit: %d | %d | %d | %d   name: %s   next: %d | %d | %d | %d   reset: %d\n", model->latches[i].lit, 
                                                                        aiger_lit2var(model->latches[i].lit),
                                                                        aiger_lit2tag(model, model->inputs[i].lit),
                                                                        get_ind(model, model->inputs[i].lit),
                                                                        model->latches[i].name,
                                                                        model->latches[i].next,
                                                                        aiger_lit2var(model->latches[i].next),
                                                                        aiger_lit2tag(model, model->latches[i].next),
                                                                        get_ind(model, model->latches[i].next),
                                                                        model->latches[i].reset);
    }
    printf("AND: %d\n", model->num_ands);  //model->ands
    for (int i=0; i<model->num_ands; i++){
        printf("\tlhs: %d | %d | %d | %d   rhs0: %d | %d | %d | %d   rhs1: %d | %d | %d | %d\n", model->ands[i].lhs,
                                                                    aiger_lit2var(model->ands[i].lhs),
                                                                    aiger_lit2tag(model, model->ands[i].lhs),
                                                                    get_ind(model, model->ands[i].lhs),
                                                                    model->ands[i].rhs0,
                                                                    aiger_lit2var(model->ands[i].rhs0),
                                                                    aiger_lit2tag(model, model->ands[i].rhs0),
                                                                    get_ind(model, model->ands[i].rhs0),
                                                                    model->ands[i].rhs1,
                                                                    aiger_lit2var(model->ands[i].rhs1),
                                                                    aiger_lit2tag(model, model->ands[i].rhs1),
                                                                    get_ind(model, model->ands[i].rhs1));
    }
    printf("OUT: %d\n", model->num_outputs);  //model->outputs
    for (int i=0; i<model->num_outputs; i++){
        printf("\tlit: %d | %d | %d | %d   name: %s\n", model->outputs[i].lit,
                                                aiger_lit2var(model->outputs[i].lit),
                                                aiger_lit2tag(model, model->outputs[i].lit),
                                                get_ind(model, model->outputs[i].lit),
                                                model->outputs[i].name);
    }
    printf("------------------------------\n");
    printf("BAD: %d\n", model->num_bad); //model->bad
    for (int i=0; i<model->num_bad; i++){
        printf("\tlit: %d | %d | %d | %d   name: %s\n", model->bad[i].lit,
                                                aiger_lit2var(model->bad[i].lit),
                                                aiger_lit2tag(model, model->bad[i].lit),
                                                get_ind(model, model->bad[i].lit),
                                                model->bad[i].name);
    }
    printf("CON: %d\n", model->num_constraints); //model->constraint
    for (int i=0; i<model->num_constraints; i++){
        printf("\tlit: %d | %d | %d | %d   name: %s\n", model->constraints[i].lit,
                                                aiger_lit2var(model->constraints[i].lit),
                                                aiger_lit2tag(model, model->constraints[i].lit),
                                                get_ind(model, model->constraints[i].lit),
                                                model->constraints[i].name);
    }
    printf("FAIR: %d\n", model->num_fairness); //model->num_fairness
    for (int i=0; i<model->num_fairness; i++){
        printf("\tlit: %d | %d | %d | %d   name: %s\n", model->fairness[i].lit,
                                                aiger_lit2var(model->fairness[i].lit),
                                                aiger_lit2tag(model, model->fairness[i].lit),
                                                get_ind(model, model->fairness[i].lit),
                                                model->fairness[i].name);
    }
    printf("------------------------------\n");
}

int main(){
    //  input/and.aig

    FILE *file, *out;
    file = fopen("input/and.aig", "r"); //Input file
    out = fopen("output/out.aig", "w"); //File to output
    aiger* model = aiger_init(); //Initilase model
    printf("Model BEFORE reading input file:\n");
    info_model(model);
    aiger_read_from_file(model, file); //Read aiger from file
    printf("Model AFTER reading input file:\n");
    info_model(model);
    aiger_write_to_file(model, aiger_mode(1), out); //Write aiger to file
    return 0;
}