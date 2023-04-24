package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Collection.Stack.MyIStack;
import Model.Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;
import Model.Type.Type;

public class CompoundStatement implements IStatement {
    private IStatement first;
    private IStatement second;

    public CompoundStatement(IStatement first, IStatement second){
        this.first = first;
        this.second = second;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException {
        MyIStack<IStatement> stack = state.getExecutionStack();
        stack.push(second);
        stack.push(first);
        state.setExecutionStack(stack);
        return null;
    }

    @Override
    public String toString(){
        return first.toString() + "; " + second.toString();
    }

    public IStatement deepCopy(){return new CompoundStatement(first.deepCopy(),second.deepCopy());}

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        return second.typeCheck(first.typeCheck(typeEnv));
    }
}
