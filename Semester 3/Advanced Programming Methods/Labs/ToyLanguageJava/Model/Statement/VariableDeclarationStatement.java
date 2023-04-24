package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Model.Exception.StatementExecutionException;
import Model.Exception.ToyLanguageInterpreterException;
import Model.Expression.VariableExpression;
import Model.State.ProgramState;
import Model.Type.Type;
import Model.Value.Value;


public class VariableDeclarationStatement implements IStatement{

    String name;

    Type type;

    public VariableDeclarationStatement(String name, Type type){
        this.type=type;
        this.name=name;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException {
        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        if (symbolTable.containsKey(name)){
            throw new StatementExecutionException("Variable " + name + " already exists.");
        }
        symbolTable.put(name,type.defaultValue());
        state.setSymbolTable(symbolTable);
        return null;
    }
    @Override
    public String toString() {
        return String.format("%s %s", type.toString(), name);
    }

    public IStatement deepCopy(){
        return new VariableDeclarationStatement(name,type);
    }

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        typeEnv.put(name,type);
        return typeEnv;
    }
}
