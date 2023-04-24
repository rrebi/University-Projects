package Model.Statement;

import Collection.Dictionary.MyDictionary;
import Collection.Dictionary.MyIDictionary;
import Collection.Stack.MyIStack;
import Collection.Stack.MyStack;
import Model.Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;
import Model.Type.Type;
import Model.Value.Value;

import java.util.Map;

public class ForkStatement implements IStatement{
    private final IStatement statement;

    public ForkStatement(IStatement stm){
        this.statement=stm;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException{
        MyIStack<IStatement> newStack = new MyStack<>();
        MyIDictionary<String, Value> newSymTable= new MyDictionary<>();
        newStack.push(statement);

        for (Map.Entry<String, Value> entry: state.getSymbolTable().getContent().entrySet()){
            newSymTable.put(entry.getKey(), entry.getValue().deepCopy());
        }
        return new ProgramState(newStack, newSymTable, state.getOutputList(), state.getFileTable(), state.getHeap());
    }

    public IStatement deepCopy(){
        return new ForkStatement(statement.deepCopy());
    }

    public String toString(){
        return String.format("Fork(%s)",statement.toString());
    }

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException{
        statement.typeCheck(typeEnv.clone_dict());
        return typeEnv;
    }
}
