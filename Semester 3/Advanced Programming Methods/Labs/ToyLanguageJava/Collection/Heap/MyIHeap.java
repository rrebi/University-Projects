package Collection.Heap;

import Model.Exception.ToyLanguageInterpreterException;
import Model.Value.Value;

import java.util.HashMap;
import java.util.Set;

public interface MyIHeap {
    int getFreeValue();
    HashMap<Integer, Value> getContent();
    void setContent(HashMap<Integer,Value> newMap);
    int add(Value value);
    void update(Integer pos, Value val) throws ToyLanguageInterpreterException;
    Value get(Integer pos ) throws ToyLanguageInterpreterException;

    boolean containsKey(Integer pos);
    void remove(Integer key) throws ToyLanguageInterpreterException;
    Set<Integer> keySet();
}
