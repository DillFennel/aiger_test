import aigsim  

def info_model(model):
    print("______________________________")
    print("IN:", model.num_inputs) #model.inputs
    for i in model.inputs:
        print("\tcurVal:", i.curVal, "gID:", i.gID, "gName:", i.gName, "type:", i.type, "myInput:", i.myInput.gName, "myInputNeg", i.myInputNeg)
    print("LAT:", model.num_latches) #model.latches
    for i in model.latches:
        print("\tcurVal:", i.curVal, "gID:", i.gID, "gName:", i.gName, "type:", i.type, "myInput:", i.myInput.gName, "myInputNeg", i.myInputNeg)
    print("AND:", model.num_ands) #model.ands
    for i in model.ands:
        print("\tcurVal:", i.curVal, "gID:", i.gID, "gName:", i.gName, "type:", i.type, "in0:", i.in0.gName, "in0Neg:", i.in0Neg, "in1:", i.in1.gName, "in1Neg:", i.in1Neg)
    print("OUT:", model.num_outputs) #model.outputs
    for i in model.outputs:
        print("\tcurVal:", i.curVal, "gID:", i.gID, "gName:", i.gName, "type:", i.type, "myInput:", i.myInput.gName, "myInputNeg", i.myInputNeg)
    print("______________________________")
    print("BAD:", model.num_bad) #model.bad
    for i in model.bad:
        print("\tcurVal:", i.curVal, "gID:", i.gID, "gName:", i.gName, "type:", i.type, "myInput:", i.myInput.gName, "myInputNeg", i.myInputNeg)
    print("CON:", model.num_constraints) #model.constraint
    for i in model.constraint:
        print("\tcurVal:", i.curVal, "gID:", i.gID, "gName:", i.gName, "type:", i.type, "myInput:", i.myInput.gName, "myInputNeg", i.myInputNeg)
    print("FAIR:", model.num_fairness) #model.num_fairness
    print("INCTL:", model.num_inputsCtl)
    print("______________________________")
model = aigsim.Model()

reader = aigsim.Reader()
reader.openFile("examples/aigTestSMV2.aag.txt")
reader.readHeader(model)
reader.readModel(model)
#reader.procModelNames(model)
#model.printSelf() #Вывод aiger
info_model(model)
#model.writeGraph("output.txt") #Сохраняет граф в виде digraph