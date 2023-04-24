package Collection.Stack;

import Model.Exception.ADTEmptyException;
import Model.Exception.ToyLanguageInterpreterException;

import java.util.*;

public class MyStack<T> implements MyIStack<T> {

    private Stack<T> stack;

    public MyStack(){
        stack = new Stack<T>();
    }

    @Override
    public T pop() throws ADTEmptyException {
        if(stack.isEmpty())
            throw new ADTEmptyException("Stack is empty");
        return this.stack.pop();
    }

    @Override
    public void push(T v){
        stack.push(v);
    }

    public List getValues(){
        return stack.subList(0,stack.size());
    }

    @Override
    public boolean isEmpty(){
        return stack.isEmpty();
    }

    @Override
    public String toString(){
        return stack.toString();
    }

    public int size(){
        return stack.size();
    }

    public List<T> getReversed(){
        List<T> list = Arrays.asList((T[]) stack.toArray());
        Collections.reverse(list);
        return list;
    }
}
