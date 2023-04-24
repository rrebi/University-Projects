package Model.Value;

import Model.Type.IntType;
import Model.Type.Type;

public class IntValue implements Value {
    int val;

    public IntValue(int v){val=v;}

    public int getVal() {return val;}

    @Override
    public boolean equals(Object anotherValue){
        if (!(anotherValue instanceof IntValue))
            return false;
        IntValue castValue = (IntValue) anotherValue;
        return this.val == castValue.val;
    }

    public String toString(){
        return String.valueOf(val);
    }
    public Value deepCopy(){
        return new IntValue(val);
    }

    public Type getType(){
        return new IntType();
    }
}
