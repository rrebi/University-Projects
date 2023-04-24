package Model.Expression;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Model.Exception.ToyLanguageInterpreterException;
import Model.Type.Type;
import Model.Value.Value;

public class VariableExpression implements  IExpression{
    String key;

    public VariableExpression(String key){
        this.key = key;
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap heap) throws ToyLanguageInterpreterException {
        return symbolTable.get(key);
    }

    public IExpression deepCopy(){
        return new VariableExpression(key);
    }

    public Type typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        return typeEnv.get(key);
    }

    @Override
    public String toString(){
        return key;
    }
}
