package Model.Value;

import Model.Type.RefType;
import Model.Type.Type;

public class RefValue implements Value{
    private final int address;

    private final Type locationType;

    public RefValue(int addr, Type locType){
        this.address=addr;
        this.locationType=locType;
    }

    public Type getType(){
        return new RefType(locationType);
    }

    public int getAddress(){
        return address;
    }
    public Type getLocationType(){
        return locationType;
    }
    public Value deepCopy()
    {
        return new RefValue(address,locationType.deepCopy());
    }
    public String toString()
    {
        return String.format("(%d,%s)",address,locationType);
    }
}
