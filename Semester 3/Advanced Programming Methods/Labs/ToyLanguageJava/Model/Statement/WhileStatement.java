package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Collection.Stack.MyIStack;
import Model.Exception.ToyLanguageInterpreterException;
import Model.Expression.IExpression;
import Model.State.ProgramState;
import Model.Type.BooleanType;
import Model.Type.Type;
import Model.Value.BooleanValue;
import Model.Value.Value;

public class WhileStatement implements IStatement{
    private final IExpression expression;
    private final IStatement statement;

    public WhileStatement(IExpression e, IStatement s){
        this.expression=e;
        this.statement=s;
    }

    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException{
        Value value = expression.evaluate(state.getSymbolTable(),state.getHeap());
        MyIStack<IStatement> stack = state.getExecutionStack();

        if (!value.getType().equals(new BooleanType())){
            throw new ToyLanguageInterpreterException(String.format("%s is not of BoolType",value));
        }

        BooleanValue boolVal=(BooleanValue) value;
        if (boolVal.getValue()){
            stack.push(this);
            stack.push(statement);
        }
        return null;
    }

    public String toString(){
        return String.format("while(%s){%s}", expression ,statement);
    }

    public IStatement deepCopy()
    {
        return new WhileStatement(expression.deepCopy(),statement.deepCopy());
    }


    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        Type typeExpr=expression.typeCheck(typeEnv);
        if(typeExpr.equals(new BooleanType()))
        {
            statement.typeCheck(typeEnv.clone_dict());
            return typeEnv;

        }
        else throw new ToyLanguageInterpreterException("Condition of WHILE does not have the type Bool.");
    }

}
