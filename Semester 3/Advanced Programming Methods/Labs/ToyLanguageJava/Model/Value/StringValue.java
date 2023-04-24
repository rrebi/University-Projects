package Model.Value;

import Model.Type.StringType;
import Model.Type.Type;

public class StringValue implements Value{
    private final String value;

    public StringValue(String value){
        this.value=value;
    }

    @Override
    public Type getType(){
        return new StringType();
    }

    @Override
    public boolean equals(Object anotherValue){
        if (!(anotherValue instanceof StringValue))
            return false;
        StringValue castValue = (StringValue) anotherValue;

        return this.value.equals(castValue.value);
    }

    public String getValue(){
        return this.value;
    }

    public Value deepCopy()
    {
        return new StringValue(value);
    }

    @Override
    public String toString(){
        return "\"" + this.value + "\"";
    }

}
