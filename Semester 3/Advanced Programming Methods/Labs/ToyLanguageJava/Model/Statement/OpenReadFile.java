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
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenReadFile implements IStatement{

    private final IExpression expression;

    public OpenReadFile(IExpression expression){
        this.expression=expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException {
        Value value = expression.evaluate(state.getSymbolTable(), state.getHeap());

        if (value.getType().toString().equals(new StringType().toString())){
            StringValue fileName = (StringValue) value;
            MyIDictionary<String, BufferedReader> fileTable = state.getFileTable();
            if (!fileTable.containsKey(fileName.getValue())){
                BufferedReader br;
                try{
                    br = new BufferedReader(new FileReader(fileName.getValue()));
                }catch (FileNotFoundException e){
                    throw new StatementExecutionException(String.format("%s couldn't be opened", fileName.getValue()));
                }
                fileTable.put(fileName.getValue(),br);
                state.setFileTable(fileTable);
            }
            else{
                throw new StatementExecutionException(String.format("%s is already opened", fileName.getValue()));

            }
        }
        else{
            throw new StatementExecutionException(String.format("%s does not evaluate to StringType", expression.toString()));
        }

        return null;
    }

    @Override
    public String toString() {
        return String.format("OpenReadFile(%s)", expression.toString());

    }

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        if(expression.typeCheck(typeEnv).equals(new StringType()))
            return typeEnv;
        else
            throw new ToyLanguageInterpreterException("OpenReadFile requires string expression");
    }

    public IStatement deepCopy() {
        return new OpenReadFile(expression.deepCopy());
    }

}
