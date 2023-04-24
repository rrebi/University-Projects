package Model.Expression;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Model.Exception.*;
import Model.Type.IntType;
import Model.Type.Type;
import Model.Value.IntValue;
import Model.Value.Value;

public class ArithmeticExpression implements IExpression {
    private IExpression expression1;
    private IExpression expression2;

    char operation;

    public ArithmeticExpression(char operation, IExpression expression1, IExpression expression2){
        this.expression1=expression1;
        this.expression2=expression2;
        this.operation=operation;
    }

    @Override
    public Value evaluate(MyIDictionary<String,Value> symbolTable, MyIHeap heap) throws ToyLanguageInterpreterException {
        Value value1, value2;
        value1 = this.expression1.evaluate(symbolTable, heap);

        if (value1.getType().equals(new IntType())){
            value2 = this.expression2.evaluate(symbolTable, heap);
            if (value2.getType().equals(new IntType())){
                IntValue int1 = (IntValue) value1;
                IntValue int2 = (IntValue) value2;

                int n1,n2;
                n1 = int1.getVal();
                n2 = int2.getVal();

                if (this.operation == '+'){
                    return new IntValue(n1+n2);
                }
                else if (this.operation == '-'){
                    return new IntValue(n1-n2);
                }
                else if (this.operation == '*'){
                    return new IntValue(n1*n2);
                }
                else if (this.operation == '/'){
                    if (n2 == 0){
                        throw new DivisionByZeroException("Division by zero!");
                    }
                    else {
                        return new IntValue(n1 / n2);
                    }
                }

            }
            else {
                throw new VariableException("Second operand is not an integer!");
            }
        }
        else {
            throw new VariableException("First operand is not an integer!");
        }
        return null;
    }

    public IExpression deepCopy(){

        return new ArithmeticExpression(operation,expression1.deepCopy(),expression2.deepCopy());
    }

    public Type typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        Type typ1,typ2;
        typ1=expression1.typeCheck(typeEnv);
        typ2=expression2.typeCheck(typeEnv);
        if(typ1.equals(new IntType()))
        {
            if(typ2.equals(new IntType()))
                return new IntType();
            else throw new ToyLanguageInterpreterException("second operand not integer");
        }
        else throw new ToyLanguageInterpreterException("first operand not integer");

    }

    @Override
    public String toString(){
        return expression1.toString() + " " + operation + " " + expression2.toString();
    }
}
