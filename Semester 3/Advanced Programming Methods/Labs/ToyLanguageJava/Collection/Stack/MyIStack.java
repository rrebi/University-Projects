package Collection.Stack;

import Model.Exception.ADTEmptyException;

import java.util.List;

public interface MyIStack<T> {
    T pop() throws ADTEmptyException;
    void push(T v);
    List<T> getValues();
    boolean isEmpty();
    String toString();

    List<T> getReversed();

    int size();

}
