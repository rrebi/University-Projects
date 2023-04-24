package Model.Expression;

import Collection.Heap.MyIHeap;
import Model.Exception.*;
import Model.Type.Type;
import Model.Value.Value;

import Collection.Dictionary.MyIDictionary;

public interface IExpression {
    public Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap heap) throws ToyLanguageInterpreterException;
    public String toString();

    Type typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException;

    IExpression deepCopy();
}
