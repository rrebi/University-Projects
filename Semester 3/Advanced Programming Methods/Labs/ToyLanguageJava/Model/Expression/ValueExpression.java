package Model.Expression;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Model.Exception.ToyLanguageInterpreterException;
import Model.Type.Type;
import Model.Value.Value;


public class ValueExpression implements IExpression{
    Value value;

    public ValueExpression(Value value) {
        this.value = value;
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap heap){
        return this.value;
    }


    public IExpression deepCopy(){return new ValueExpression(value);}

    public Type typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        return value.getType();
    }
    @Override
    public String toString(){return this.value.toString();}
}
