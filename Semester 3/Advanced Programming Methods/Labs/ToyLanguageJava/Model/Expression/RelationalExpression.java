package Model.Expression;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Model.Exception.ToyLanguageInterpreterException;
import Model.Type.BooleanType;
import Model.Type.IntType;
import Model.Type.Type;
import Model.Value.BooleanValue;
import Model.Value.IntValue;
import Model.Value.Value;

import java.util.Objects;

public class RelationalExpression implements IExpression {

    IExpression expression1;
    IExpression expression2;

    String operator;

    public RelationalExpression(IExpression e1, IExpression e2, String op){
        this.expression1=e1;
        this.expression2=e2;
        this.operator=op;
    }

    @Override
    public Value evaluate(MyIDictionary<String,Value> symbolTable, MyIHeap heap) throws ToyLanguageInterpreterException {
        Value val1,val2;
        val1=this.expression1.evaluate(symbolTable, heap);
        if(val1.getType().equals(new IntType()))
        {
            val2=this.expression2.evaluate(symbolTable, heap);
            if(val2.getType().equals(new IntType()))
            {
                IntValue vall1=(IntValue) val1;
                IntValue vall2=(IntValue) val2;
                int v1,v2;
                v1=vall1.getVal();
                v2=vall2.getVal();
                if(Objects.equals(this.operator,"<"))
                    return new BooleanValue(v1<v2);
                else if (Objects.equals(this.operator,"<="))
                    return new BooleanValue(v1<=v2);
                else if (Objects.equals(this.operator,"=="))
                    return new BooleanValue(v1==v2);
                else if (Objects.equals(this.operator,"!="))
                    return new BooleanValue(v1!=v2);
                else if (Objects.equals(this.operator,">"))
                    return new BooleanValue(v1>v2);
                else if (Objects.equals(this.operator,">="))
                    return new BooleanValue(v1>=v2);


            }
            else {
                throw new ToyLanguageInterpreterException("Second operand is not integer.");
            }

        }
        else
        {
            throw new ToyLanguageInterpreterException("First operand is not an integer.");

        }
        return null;
    }

    public IExpression deepCopy()
    {
        return new RelationalExpression(expression1.deepCopy(),expression2.deepCopy(),operator);

    }

    public Type typeCheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException
    {
        Type typ1,typ2;
        typ1=expression1.typeCheck(typeEnv);
        typ2=expression2.typeCheck(typeEnv);
        if(typ1.equals(new IntType()))
        {
            if(typ2.equals(new IntType()))
                return new BooleanType();
            else throw new ToyLanguageInterpreterException("second operand not integer");
        }
        else throw new ToyLanguageInterpreterException("first operand not integer");

    }

    public String toString()
    {
        return this.expression1.toString()+" "+this.operator+" "+this.expression1.toString();
    }
}
