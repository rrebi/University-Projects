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

public class HeapWriting implements IStatement{

    private final String varName;

    private final IExpression expression;

    public HeapWriting(String varName, IExpression exp){
        this.varName=varName;
        this.expression=exp;
    }

    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException{
        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        MyIHeap heap = state.getHeap();

        if (!symbolTable.containsKey(varName)){
            throw new ToyLanguageInterpreterException(String.format("%s not present",varName));
        }
        Value val = symbolTable.get(varName);
        if(!(val instanceof RefValue)){
            throw new ToyLanguageInterpreterException(String.format("%s not of RefType",val));
        }
        RefValue refV =(RefValue) val;
        Value evaluated = expression.evaluate(symbolTable,heap);

        if(!evaluated.getType().equals(refV.getLocationType())){
            throw new ToyLanguageInterpreterException(String.format("%s not of %s",evaluated,refV.getLocationType()));
        }
        heap.update(refV.getAddress(),evaluated);
        state.setHeap(heap);
        return null;

    }
    public IStatement deepCopy()
    {
        return new HeapWriting(varName,expression.deepCopy());
    }

    public String toString()
    {
        return String.format("WriteHeap(%s,%s)",varName,expression);
    }

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        if(typeEnv.get(varName).toString().equals(new RefType(expression.typeCheck(typeEnv)).toString()))
            return typeEnv;
        else
            throw new ToyLanguageInterpreterException("WriteHeap: right hside and left hside different types");
    }

}
