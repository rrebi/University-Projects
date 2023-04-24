package Model.Expression;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Model.Exception.*;
import Model.Type.Type;
import Model.Value.BooleanValue;
import Model.Value.Value;
import Model.Type.BooleanType;

import java.util.Objects;

public class LogicExpression implements IExpression{
    IExpression expression1;
    IExpression expression2;

    String operation;

    public LogicExpression(String operation, IExpression expression1, IExpression expression2){
        this.expression1=expression1;
        this.expression2=expression2;
        this.operation=operation;
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap heap) throws ToyLanguageInterpreterException {
        Value value1, value2;
        value1 = this.expression1.evaluate(symbolTable, heap);

        if (value1.getType().equals(new BooleanType())){
            value2 = this.expression2.evaluate(symbolTable, heap);

            if (value2.getType().equals(new BooleanType())){
                BooleanValue bool1 = (BooleanValue) value1;
                BooleanValue bool2 = (BooleanValue) value2;

                boolean b1, b2;
                b1 = bool1.getValue();
                b2 = bool2.getValue();

                if (Objects.equals(this.operation,"and")){
                    return new BooleanValue(b1 && b2);
                }
                else if (Objects.equals(this.operation, "or")){
                    return new BooleanValue(b1 || b2);
                }
            }
            else {
                throw new VariableException("Second operand is not a boolean!");
            }
        }
        else {
            throw new VariableException("First operand is not a boolean!");
        }
        return null;
    }

    public IExpression deepCopy(){

        return new LogicExpression(operation,expression1.deepCopy(),expression2.deepCopy());
    }

    public Type typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        Type typ1,typ2;
        typ1=expression1.typeCheck(typeEnv);
        typ2=expression2.typeCheck(typeEnv);
        if(typ1.equals(new BooleanType()))
        {
            if(typ2.equals(new BooleanType()))
                return new BooleanType();
            else throw new ToyLanguageInterpreterException("second operand not bool");
        }
        else throw new ToyLanguageInterpreterException("first operand not bool");

    }

    @Override
    public String toString(){
        return expression1.toString() + " " + operation + " " + expression2.toString();
    }
}
