package Model.Type;

import Model.Value.StringValue;
import Model.Value.Value;

public class StringType implements Type{

    public boolean equals(Type anotherType){
        return anotherType instanceof StringType;
    }

    @Override
    public Value defaultValue(){
        return new StringValue("");
    }
    public Type deepCopy(){
        return new StringType();
    }

    @Override
    public String toString(){
        return "string";
    }
}
