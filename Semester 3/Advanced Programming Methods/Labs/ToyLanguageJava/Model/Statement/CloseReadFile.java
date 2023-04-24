package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Model.Exception.StatementExecutionException;
import Model.Exception.ToyLanguageInterpreterException;
import Model.Expression.IExpression;
import Model.State.ProgramState;
import Model.Type.StringType;
import Model.Type.Type;
import Model.Value.StringValue;
import Model.Value.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseReadFile implements IStatement{

    private final IExpression expression;

    public CloseReadFile(IExpression expression){
        this.expression=expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException {
        Value value = expression.evaluate(state.getSymbolTable(), state.getHeap());
        if (!value.getType().toString().equals(new StringType().toString())){
            throw new StatementExecutionException(String.format("%s does not evaluate to StringValue", expression));
        }
        StringValue fileName = (StringValue) value;
        MyIDictionary<String, BufferedReader> fileTable = state.getFileTable();

        if (!fileTable.containsKey(fileName.getValue())) {
            throw new StatementExecutionException(String.format("%s is not present in the FileTable", value));
        }
        BufferedReader br = fileTable.get(fileName.getValue());
        try{
            br.close();
        } catch (IOException e){
            throw new StatementExecutionException(String.format("Unexpected error in closing %s", value));
        }
        fileTable.remove(fileName.getValue());
        state.setFileTable(fileTable);
        return null;
    }
    public IStatement deepCopy()
    {
        return new CloseReadFile(expression.deepCopy());
    }


    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        if(expression.typeCheck(typeEnv).equals(new StringType()))
            return typeEnv;
        else throw new ToyLanguageInterpreterException("CloseReadFile requires a string expression");
    }
}
