package Model.Type;
import Model.Value.Value;
import Model.Value.BooleanValue;

public class BooleanType implements Type {

    public boolean equals(Object another){
        if (another instanceof BooleanType)
            return true;
        else
            return false;
    }

    public String toString(){
        return "bool";
    }
    public Type deepCopy()
    {
        return new BooleanType();
    }

    public BooleanValue defaultValue(){
        return new BooleanValue(false);
    }

}
