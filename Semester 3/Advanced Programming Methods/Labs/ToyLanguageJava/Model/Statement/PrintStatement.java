package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Collection.List.MyIList;
import Model.Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;
import Model.Expression.IExpression;

import Model.Type.Type;
import Model.Value.Value;

public class PrintStatement implements IStatement{
    IExpression expression;

    public PrintStatement(IExpression expression){
        this.expression=expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException{
        MyIList<Value> out = state.getOutputList();
        out.add(expression.evaluate(state.getSymbolTable(), state.getHeap()));
        state.setOutputList(out);
        return null;
    }

    @Override
    public String toString(){
        return String.format("Print(%s)", expression.toString());
    }
    public IStatement deepCopy(){return new PrintStatement(expression.deepCopy());}

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        expression.typeCheck(typeEnv);
        return typeEnv;
    }
}
