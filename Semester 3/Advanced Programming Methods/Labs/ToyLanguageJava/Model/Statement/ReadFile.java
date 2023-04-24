package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Model.Exception.StatementExecutionException;
import Model.Exception.ToyLanguageInterpreterException;
import Model.Expression.IExpression;
import Model.State.ProgramState;
import Model.Type.IntType;
import Model.Type.StringType;
import Model.Type.Type;
import Model.Value.IntValue;
import Model.Value.StringValue;
import Model.Value.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFile implements IStatement{
    private final IExpression expression;

    private final String varName;

    public ReadFile(IExpression expression, String varName){
        this.expression=expression;
        this.varName=varName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException {
        MyIDictionary<String, Value> symbolTable=state.getSymbolTable();
        MyIDictionary<String, BufferedReader> fileTable = state.getFileTable();

        if (symbolTable.containsKey(varName)){
            Value value = symbolTable.get(varName);
            if (value.getType().equals(new IntType())){
                value = expression.evaluate(symbolTable, state.getHeap());
                if (value.getType().toString().equals(new StringType().toString())){
                    StringValue castValue = (StringValue) value;
                    if (fileTable.containsKey(castValue.getValue())){
                        BufferedReader br = fileTable.get(castValue.getValue());
                        try{
                            String line = br.readLine();
                            if (line == null)
                                line = "0";
                            symbolTable.put(varName,new IntValue(Integer.parseInt(line)));
                        }
                        catch (IOException e){
                            throw new StatementExecutionException(String.format("Couldn't read from file %s", castValue));
                        }
                    } else {
                        throw new StatementExecutionException(String.format("The file table does not contain %s", castValue));
                    }
                }else {
                    throw new StatementExecutionException(String.format("%s does not evaluate to StringType", value));
                }
            }else {
                throw new StatementExecutionException(String.format("%s is not of type IntType", value));
            }
        }else {
            throw new StatementExecutionException(String.format("%s is not present in the symTable.", varName));
        }
        return null;
    }

    @Override
    public String toString(){
        return String.format("ReadFile(%s, %s)", expression.toString(), varName);

    }
    public IStatement deepCopy() {
        return new ReadFile(expression.deepCopy(), varName);
    }

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        if(expression.typeCheck(typeEnv).equals(new StringType()))
            if(typeEnv.get(varName).equals(new IntType()))
                return typeEnv;
            else throw new ToyLanguageInterpreterException("ReadFile needs an integer  as var parameter");
        else throw new ToyLanguageInterpreterException("ReadFile needs string as expression parameter");
    }
}
