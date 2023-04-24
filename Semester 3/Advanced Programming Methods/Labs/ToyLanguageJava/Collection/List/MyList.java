package Collection.List;

import java.util.List;
import java.util.ArrayList;

public class MyList<T> implements MyIList<T> {
    private ArrayList<T> list;

    public MyList(){
        list = new ArrayList<T>();
    }

    @Override
    public int size(){
        return list.size();
    }

    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }

    @Override
    public boolean add(T e){
        return list.add(e);
    }

    @Override
    public void clear(){
        list.clear();
    }

    @Override
    public T get(int index){
        return list.get(index);
    }

    @Override
    public List<T> getList(){
        return list;
    }

    @Override
    public String toString(){
        return list.toString();
    }
}
