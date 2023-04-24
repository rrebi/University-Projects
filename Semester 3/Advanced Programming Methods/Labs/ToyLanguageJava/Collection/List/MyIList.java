package Collection.List;

import java.util.List;

public interface MyIList<T> {
    int size();
    boolean isEmpty();
    boolean add(T e);
    void clear();
    T get(int index);

    List<T> getList();
    String toString();
}
