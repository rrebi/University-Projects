package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Model.Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;
import Model.Type.Type;

public class NopStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }

    @Override
    public String toString() {
        return "NopStatement";
    }

    @Override
    public IStatement deepCopy() {
        return null;
    }

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        return typeEnv;
    }
}
