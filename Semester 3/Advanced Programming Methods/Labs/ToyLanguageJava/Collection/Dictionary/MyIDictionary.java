package Collection.Dictionary;

import Model.Exception.ToyLanguageInterpreterException;

import java.util.Collection;
import java.util.Set;
import java.util.Map;

public interface MyIDictionary<K, V>{
    V get(K key) throws ToyLanguageInterpreterException;
    V put(K key,V value) throws ToyLanguageInterpreterException;
    String toString();
    int size();
    boolean containsKey(K name);
    void remove(K key) throws ToyLanguageInterpreterException;
    Collection<V> values();
    boolean containsValue(V element);
    Set<K> keySet();
    Set<Map.Entry<K,V>> entrySet();
    Map<K, V> getContent();
    void setContent(Set<Map.Entry<K,V>> set) throws ToyLanguageInterpreterException;
    K getKey(V value);
    MyIDictionary<K, V> clone_dict() throws ToyLanguageInterpreterException;

}
