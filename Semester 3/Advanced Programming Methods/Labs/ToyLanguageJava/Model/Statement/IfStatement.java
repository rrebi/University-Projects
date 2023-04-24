package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Collection.Stack.MyIStack;
import Model.Exception.*;
import Model.Expression.IExpression;
import Model.State.ProgramState;
import Model.Type.BooleanType;
import Model.Type.Type;
import Model.Value.BooleanValue;

import Model.Value.Value;

public class IfStatement implements IStatement {
    IExpression expression;
    IStatement thenStatement;
    IStatement elseStatement;

    public IfStatement(IExpression expression, IStatement thenStatement, IStatement elseStatement){
        this.expression=expression;
        this.thenStatement=thenStatement;
        this.elseStatement=elseStatement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException {
        Value result = this.expression.evaluate(state.getSymbolTable(), state.getHeap());

        if (result instanceof BooleanValue boolResult) {
            IStatement statement;

            if (boolResult.getValue()) {
                statement = thenStatement;
            } else {
                statement = elseStatement;
            }

            MyIStack<IStatement> stack = state.getExecutionStack();
            stack.push(statement);
            state.setExecutionStack(stack);
            return null;
        }
        else{
            throw new StatementExecutionException("Please provide a boolean expression in an if statement.");
        }
    }
    public  IStatement deepCopy(){return new IfStatement(expression.deepCopy(),thenStatement.deepCopy(),elseStatement.deepCopy());}

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        Type typeExpr= expression.typeCheck(typeEnv);
        if(typeExpr.equals(new BooleanType()))
        {
            thenStatement.typeCheck(typeEnv.clone_dict());
            elseStatement.typeCheck(typeEnv.clone_dict());
            return typeEnv;
        }else throw new ToyLanguageInterpreterException("The condition of IF does not have type bool");
    }

    @Override
    public String toString(){
        return String.format("if(%s){%s}else{%s}", expression.toString(), thenStatement.toString(), elseStatement.toString());    }
}
