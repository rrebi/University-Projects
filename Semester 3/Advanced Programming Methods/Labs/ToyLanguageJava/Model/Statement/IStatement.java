package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Model.Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;
import Model.Type.Type;

public interface IStatement {
    ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException;
    String toString();

    IStatement deepCopy();

    MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException;


}

