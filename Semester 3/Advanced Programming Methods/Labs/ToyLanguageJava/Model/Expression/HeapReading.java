package Model.Expression;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Model.Exception.ToyLanguageInterpreterException;
import Model.Type.RefType;
import Model.Type.Type;
import Model.Value.RefValue;
import Model.Value.Value;

public class HeapReading implements IExpression{

    private final IExpression expression;

    public HeapReading(IExpression e){
        this.expression=e;
    }

    public Value evaluate(MyIDictionary<String,Value> symbolTable, MyIHeap heap) throws ToyLanguageInterpreterException{
        Value val = expression.evaluate(symbolTable,heap);

        if(!(val instanceof RefValue)){
            throw new ToyLanguageInterpreterException(String.format("%s not of RefType",val));
        }

        RefValue refValue=(RefValue) val;
        return heap.get(refValue.getAddress());
    }

    public IExpression deepCopy()
    {
        return new HeapReading(expression.deepCopy());
    }



    public Type typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        Type typ=expression.typeCheck(typeEnv);
        if(typ instanceof RefType)
        {
            RefType reft=(RefType) typ;
            return reft.getInner();
        } else throw new ToyLanguageInterpreterException("The RH Argument is not a RefType");


    }public String toString()
    {
        return String.format("ReadHeap(%s)",expression);
    }
}
