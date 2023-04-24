package Model.Value;
import Model.Type.Type;
import Model.Type.BooleanType;

public class BooleanValue implements Value{

    private boolean val;

    public BooleanValue(boolean value){
        val=value;
    }

    public Boolean getValue(){
        return val;
    }

    @Override
    public boolean equals(Object anotherValue){
        if (!(anotherValue instanceof BooleanValue))
            return false;
        BooleanValue castValue = (BooleanValue) anotherValue;
        return this.val == castValue.val;
    }

    public String toString(){
        return String.valueOf(val);
    }
    public Value deepCopy() {
        return new BooleanValue(val);
    }

    public Type getType(){
        return new BooleanType();
    }

}
