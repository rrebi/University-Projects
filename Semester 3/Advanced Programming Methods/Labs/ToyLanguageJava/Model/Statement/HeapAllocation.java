package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Model.Exception.ToyLanguageInterpreterException;
import Model.Expression.IExpression;
import Model.State.ProgramState;
import Model.Type.RefType;
import Model.Type.Type;
import Model.Value.RefValue;
import Model.Value.Value;

import java.beans.Expression;

public class HeapAllocation implements  IStatement{

    private final String varName;

    private final IExpression exp;

    public HeapAllocation(String varName, IExpression ex){
        this.varName = varName;
        this.exp=ex;
    }

    public ProgramState execute (ProgramState state) throws ToyLanguageInterpreterException{
        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        MyIHeap heap = state.getHeap();

        if (!symbolTable.containsKey(varName)){
            throw new ToyLanguageInterpreterException(String.format("%s not in symTable", varName));
        }

        Value varVal = symbolTable.get(varName);
        if (!(varVal.getType() instanceof RefType)){
            throw new ToyLanguageInterpreterException(String.format("%s in not of RefType", varName));
        }

        Value evaluated = exp.evaluate(symbolTable,heap);
        Type locationType = ((RefValue) varVal).getLocationType();

        if (!locationType.toString().equals(evaluated.getType().toString())){
            throw new ToyLanguageInterpreterException(String.format("%s not of %s", varName, evaluated.getType()));
        }

        int newPos = heap.add(evaluated);
        symbolTable.put(varName, new RefValue(newPos, locationType));
        state.setSymbolTable(symbolTable);
        state.setHeap(heap);
        return null;
    }
    public String toString()
    {
        return String.format("New(%s,%s)",varName,exp);
    }

    public IStatement deepCopy()
    {
        return new HeapAllocation(varName,exp.deepCopy());
    }

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        Type typevar=typeEnv.get(varName);
        Type typeexp=exp.typeCheck(typeEnv);
        if(typevar.toString().equals(new RefType(typeexp).toString()))
            return typeEnv;
        else
            throw new ToyLanguageInterpreterException("Heap allocation statement: right hand side and left hand side have different types");
    }
}
