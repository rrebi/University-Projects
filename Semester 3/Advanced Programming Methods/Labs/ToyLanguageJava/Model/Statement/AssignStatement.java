package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Model.Exception.*;
import Model.Expression.IExpression;
import Model.State.ProgramState;
import Model.Type.Type;
import Model.Value.Value;

public class AssignStatement implements IStatement{

    private final String key;

    private final IExpression expression;

    public AssignStatement(String key, IExpression expression){
        this.key = key;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException {
        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();

        if (symbolTable.containsKey(key)){
            Value value = expression.evaluate(symbolTable, state.getHeap());
            Type typeId = (symbolTable.get(key)).getType();

            if ((value.getType().toString()).equals((typeId).toString())){
                symbolTable.put(key,value);
            }
            else{
                throw new StatementExecutionException("Declared type of variable " + key + " and type of the assigned expression do not match.");
            }
        }
        else{
            throw new StatementExecutionException("The used variable " + key + " isn't declared.");
        }
        state.setSymbolTable(symbolTable);
        return null;
    }
    public IStatement deepCopy(){return new AssignStatement(key,expression.deepCopy());}

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        Type typevar=typeEnv.get(key);
        Type typexp=expression.typeCheck(typeEnv);
        if(typevar.equals(typexp))
            return typeEnv;
        else
            throw new ToyLanguageInterpreterException("Assignment: left handside and right handside have different types");
    }

    @Override
    public String toString(){
        return key + " = " + expression.toString();
    }

}
